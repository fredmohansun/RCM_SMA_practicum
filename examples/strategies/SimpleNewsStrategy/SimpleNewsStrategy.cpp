/*================================================================================                               
*     Source: ../Lime/StrategyStudio/examples/strategies/SimpleNewsStrategy/SimpleNewsStrategy.cpp                                                        
*     Last Update: 2010/09/30 13:55:14                                                                            
*     Contents:                                     
*     Distribution:          
*                                                                                                                
*                                                                                                                
*     Copyright (c) Lime Brokerage LLC, 2011 - 2012.                                                 
*     All rights reserved.                                                                                       
*                                                                                                                
*     This software is part of Licensed material, which is the property of Lime Brokerage LLC ("Company"), 
*     and constitutes Confidential Information of the Company.                                                  
*     Unauthorized use, modification, duplication or distribution is strictly prohibited by Federal law.         
*     No title to or ownership of this software is hereby transferred.                                          
*                                                                                                                
*     The software is provided "as is", and in no event shall the Company or any of its affiliates or successors be liable for any 
*     damages, including any lost profits or other incidental or consequential damages relating to the use of this software.       
*     The Company makes no representations or warranties, express or implied, with regards to this software.                        
/*================================================================================*/   

#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "SimpleNewsStrategy.h"

#include "FillInfo.h"
#include "AllEventMsg.h"
#include "ExecutionTypes.h"
#include <Utilities/Cast.h>
#include <Utilities/utils.h>

#include <math.h>
#include <iostream>
#include <cassert>

using namespace LimeBrokerage::StrategyStudio;
using namespace LimeBrokerage::StrategyStudio::MarketModels;
using namespace LimeBrokerage::StrategyStudio::Utilities;

using namespace std;

SimpleNews::SimpleNews(StrategyID strategyID, const std::string& strategyName, const std::string& groupName):
    Strategy(strategyID, strategyName, groupName),
    m_snState(),
    m_bar(),
    m_instrument(NULL),
    m_rollingWindow(15),
    m_tradeTime(),
    m_measure("FIN.EPS"),
    m_zScore(0),
    m_zScoreThreshold(1.5),
    m_tradeSize(100),
    m_nOrdersOutstanding(0),
    m_expectedValue(0),
    m_stdDevEstimate(.01),
    m_holdTime(0)
{
    // note: assume market state is active
    m_snState.marketActive = true;
    this->set_enabled_pre_open_data_flag(true);
    this->set_enabled_pre_open_trade_flag(true);
    this->set_enabled_post_close_data_flag(true);
    this->set_enabled_post_close_trade_flag(true);
}

SimpleNews::~SimpleNews()
{
}

void SimpleNews::OnResetStrategyState()
{
    m_snState.marketActive = true;

    m_rollingWindow.clear();
    m_bar.Clear();
}

void SimpleNews::DefineStrategyParams()
{
    CreateStrategyParamArgs arg1("z_score_threshold", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_zScoreThreshold);
    params().CreateParam(arg1);

    CreateStrategyParamArgs arg2("trade_size", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_INT, m_tradeSize);
    params().CreateParam(arg2);

    CreateStrategyParamArgs arg3("expected_number", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_expectedValue);
    params().CreateParam(arg3);

    CreateStrategyParamArgs arg4("stddev_estimate", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_stdDevEstimate);
    params().CreateParam(arg4);
    
    CreateStrategyParamArgs arg5("hold_time", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_INT, m_holdTime);
    params().CreateParam(arg5);

    CreateStrategyParamArgs arg6("measure", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_STRING, m_measure);
    params().CreateParam(arg6);
}

void SimpleNews::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate)
{    
    for(SymbolSetConstIter it = symbols_begin(); it != symbols_end(); ++it) {
        eventRegister->RegisterForNews(*it);
        EventInstrumentPair retVal = eventRegister->RegisterForBars(*it, BAR_TYPE_TIME, 1);    
        m_instrument = retVal.second;
    }
}

void SimpleNews::OnTrade(const TradeDataEventMsg& )
{
}

void SimpleNews::OnTopQuote(const QuoteEventMsg& )
{
}

void SimpleNews::OnNews(const NewsEventMsg& msg)
{
    if(m_stdDevEstimate < .0005)
        return;

    if (m_snState.state != StrategyLogicState::WAITING || msg.measure().compare(m_measure) != 0)
        return;

    double zScore = (msg.mid() - m_expectedValue) / m_stdDevEstimate;

    std::stringstream ss;
    ss << "Received news event for " << msg.entity() << " (" << msg.period() << ") " << msg.measure() << " --> " << msg.mid();
    logger().LogToClient(LOGDEBUG, ss.str());
    ss.str("");

    if (zScore > m_zScoreThreshold) {
        SendBuyOrder(m_instrument, m_tradeSize);
        m_tradeTime = msg.event_time();
        m_snState.state = StrategyLogicState::OPENED;
        m_snState.side = StrategyLogicState::BUY;
        ss << "Bought " << m_tradeSize << " shares for " << m_instrument->symbol() << m_instrument->top_quote().bid() << " " << m_instrument->top_quote().bid() << m_instrument->last_trade().IsValid();
        logger().LogToClient(LOGDEBUG, ss.str());
    } else if(zScore < -m_zScoreThreshold) {
        SendSellOrder(m_instrument, m_tradeSize);
        m_tradeTime = msg.event_time();
        m_snState.state = StrategyLogicState::OPENED;
        m_snState.side = StrategyLogicState::SELL;
        ss << "Sold " << m_tradeSize << " shares for " << m_instrument->symbol() << m_instrument->top_quote().bid() << " " << m_instrument->top_quote().bid() << m_instrument->last_trade().IsValid();
        logger().LogToClient(LOGDEBUG, ss.str());
    }
}


void SimpleNews::OnBar(const BarEventMsg& msg)
{
    if (m_snState.state == StrategyLogicState::OPENED
        && portfolio().position(m_instrument) != 0
        && (msg.event_time() - m_tradeTime) > boost::posix_time::seconds(m_holdTime)) {
		
        if (m_snState.side == StrategyLogicState::BUY)
            SendSellOrder(m_instrument, m_tradeSize);
        else if (m_snState.side == StrategyLogicState::SELL)
            SendBuyOrder(m_instrument, m_tradeSize);
			
        m_snState.state = StrategyLogicState::CLOSED;
        logger().LogToClient(LOGDEBUG, "closed out position");
    }

    m_bar = msg.bar();
}

void SimpleNews::SendBuyOrder(const Instrument* instrument, int unitsNeeded)
{
    OrderParams params(*instrument, 
        unitsNeeded,
        (instrument->top_quote().ask() != 0) ? instrument->top_quote().ask() : instrument->last_trade().price(), 
        (instrument->type() == INSTRUMENT_TYPE_EQUITY) ? MARKET_CENTER_ID_NASDAQ : ((instrument->type() == INSTRUMENT_TYPE_OPTION) ? MARKET_CENTER_ID_CBOE_OPTIONS : MARKET_CENTER_ID_CME_GLOBEX),
        ORDER_SIDE_BUY,
        ORDER_TIF_DAY,
        ORDER_TYPE_MARKET);

    trade_actions()->SendNewOrder(params);
}
    
void SimpleNews::SendSellOrder(const Instrument* instrument, int unitsNeeded)
{
    OrderParams params(*instrument, 
        unitsNeeded,
        (instrument->top_quote().bid() != 0) ? instrument->top_quote().bid() : instrument->last_trade().price(), 
        (instrument->type() == INSTRUMENT_TYPE_EQUITY) ? MARKET_CENTER_ID_NASDAQ : ((instrument->type() == INSTRUMENT_TYPE_OPTION) ? MARKET_CENTER_ID_CBOE_OPTIONS : MARKET_CENTER_ID_CME_GLOBEX),
        ORDER_SIDE_SELL,
        ORDER_TIF_DAY,
        ORDER_TYPE_MARKET);

    trade_actions()->SendNewOrder(params);
}

void SimpleNews::OnMarketState(const MarketStateEventMsg& )
{
}

void SimpleNews::OnOrderUpdate(const OrderUpdateEventMsg& )  
{
}

void SimpleNews::OnAppStateChange(const AppStateEventMsg& )
{
}

void SimpleNews::OnParamChanged(StrategyParam& param)
{    
    if (param.param_name() == "z_score_threshold") {
        if (!param.Get(&m_zScoreThreshold))
            throw StrategyStudioException("Could not get zscore threshold");
    } else if (param.param_name() == "trade_size") {
        if (!param.Get(&m_tradeSize))
            throw StrategyStudioException("Could not get trade size");
    } else if (param.param_name() == "expected_number") {
        if (!param.Get(&m_expectedValue))
            throw StrategyStudioException("Could not get expected_value");
    } else if (param.param_name() == "stddev_estimate") {
        if (!param.Get(&m_stdDevEstimate))
            throw StrategyStudioException("Could not get stddev_estimate");
    } else if (param.param_name() == "hold_time") {
        if (!param.Get(&m_holdTime))
            throw StrategyStudioException("Could not get hold_time");
    } else if (param.param_name() == "measure") {
        if (!param.Get(&m_measure))
            throw StrategyStudioException("Could not get hold_time");
    }
}
