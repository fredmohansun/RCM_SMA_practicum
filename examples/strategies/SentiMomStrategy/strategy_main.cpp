/* ================================================================================                               
*     Source: ../Lime/StrategyStudio/examples/strategies/SentiMomStrategy/SentiMomExample.cpp                                                        
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
================================================================================*/   

#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "strategy_main.h"
#include "backtest_class.h"

#include "FillInfo.h"
#include "AllEventMsg.h"
#include "ExecutionTypes.h"
#include <Utilities/Cast.h>
#include <Utilities/utils.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>

using namespace LimeBrokerage::StrategyStudio;
using namespace LimeBrokerage::StrategyStudio::MarketModels;
using namespace LimeBrokerage::StrategyStudio::Utilities;

using namespace std;

typedef std::map<TimeType, PSentimentEventMsg> SMAmap;

TimeType TimeHelper(std::string line){
    std::stringstream split_helper(line);
    std::vector <std::string> split((std::istream_iterator<std::string>(split_helper)), std::istream_iterator<std::string>());
    std::string mytime = split[18]+' '+split[19]+".000";
    TimeType res = TimeType(boost::posix_time::time_from_string(mytime));
    return res;
}

SentiMom::SentiMom(StrategyID strategyID, const std::string& strategyName, const std::string& groupName):
    Strategy(strategyID, strategyName, groupName),
    m_spState(),
    m_bars(),
    m_instrumentX(NULL),
    m_rollingWindow(50),
    m_SentiThreshold(0.5),
    m_MomThreshold(0.5),
    m_tradeSize(100),
    m_nOrdersOutstanding(0),
    m_DebugOn(true),
    sma_data()
{
    std::cout<<"constructing SentiMom...\n";
    ifstream input_file("BTC.X.txt", std::ifstream::in);
    std::cout<<"BTC sentiment file readed...\n";
    std::string line;
    getline(input_file, line);//Get metadata
    std::cout<<line<<'\n';
    std::cout<<"Metadata got...constructing sma data...\n";
    while(!input_file.eof()){
	getline(input_file, line);
	if(line[0]=='e') break;
	std::cout<<line<<'\n';
	PSentimentEventMsg SMA_entry = PSentimentEventMsg(line);
	TimeType SMA_time = TimeHelper(line);
	sma_data.insert(std::pair<TimeType, PSentimentEventMsg>(SMA_time, SMA_entry));
    }
    std::cout<<"sma_data construction done...\n";
    // note: assume market state is active
    m_spState.marketActive = true;
    this->set_enabled_pre_open_data_flag(true);
    this->set_enabled_pre_open_trade_flag(true);
    this->set_enabled_post_close_data_flag(true);
    this->set_enabled_post_close_trade_flag(true);
    std::cout<<"construction done.\n";
}

SentiMom::~SentiMom()
{
}

void SentiMom::OnResetStrategyState()
{
    m_spState.marketActive = true;
    m_spState.unitsDesired = 0;

    m_rollingWindow.clear();
    m_bars.clear();
}

void SentiMom::DefineStrategyParams()
{
    CreateStrategyParamArgs arg1("Price Threshold", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_MomThreshold);
    params().CreateParam(arg1);

    CreateStrategyParamArgs arg2("Sentiment Threshold", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_SentiThreshold);
    params().CreateParam(arg2);

    CreateStrategyParamArgs arg3("trade_size", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_INT, m_tradeSize);
    params().CreateParam(arg3);

    CreateStrategyParamArgs arg4("debug", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_BOOL, m_DebugOn);
    params().CreateParam(arg4);
}

void SentiMom::DefineStrategyGraphs()
{
    graphs().series().add("Mean");
    graphs().series().add("ZScore");
}

void SentiMom::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate)
{    
    for (SymbolSetConstIter it = symbols_begin(); it != symbols_end(); ++it) {
        EventInstrumentPair retVal = eventRegister->RegisterForBars(*it, BAR_TYPE_TIME, 60*15);    
        m_instrumentX = retVal.second;
    }
}

void SentiMom::OnTrade(const TradeDataEventMsg& msg)
{
}

void SentiMom::OnTopQuote(const QuoteEventMsg& msg)
{
}

void SentiMom::OnBar(const BarEventMsg& msg)
{
    if (m_DebugOn) {
        ostringstream str;
        str << msg.instrument().symbol() << ": "<< msg.bar();
        logger().LogToClient(LOGLEVEL_DEBUG, str.str().c_str());
	std::cout<< str.str().c_str()<<'\n';
    }
    TimeType current_time = msg.bar_time();
    
    std::pair<SMAmap::iterator, SMAmap::iterator> data_iterator = sma_data.equal_range(current_time);
    if (m_DebugOn){
	ostringstream str2;
	str2 << "BTC's S: "<< data_iterator.first->second.s();
	logger().LogToClient(LOGLEVEL_INFO, str2.str().c_str());
    }
    /*
    for(SMAmap::iterator it = data_iterator.first(); it!= data_iterator.second(); it++){
        if (m_DebugOn) {
	    ostringstream str2;
	    str2 << "BTC's Raw-S: "<< it.s();
	    logger().LogToCLient(LOGLEVEL_INFO, str.str().c_str());
	}
    }
    */
    // update our bars collection
    m_bars[&msg.instrument()] = msg.bar();
/*
    double ThisReturn = 0;
    if (m_XLast != 0) {
//      barCloseRatio = m_bars[m_instrumentX].close() / m_bars[m_instrumentY].close();
        ThisReturn = (m_bars[m_instrumentX].close()-m_XLast)/m_XLast;
	m_XLast = m_bars[m_instrumentX].close();
	m_bars.clear();
    } else {
 	m_XLast = m_bars[m_instrumentX].close();
        m_bars.clear();
        return;
    }
    
     m_rollingWindow.push_back(ThisReturn);
   
    // only process when we have a complete rolling window
    if (!m_rollingWindow.full())
        return;

    if (orders().num_working_orders() > 0) 
        return;

    //m_zScore = m_rollingWindow.ZScore();

    //graphs().series()["Mean"]->push_back(msg.event_time(), m_rollingWindow.Mean());
    //graphs().series()["ZScore"]->push_back(msg.event_time(), m_zScore);    
    
    // sell X and buy Y when z widens 
    if (ThisReturn > m_XSDThreshold) {
        m_spState.unitsDesired += m_tradeSize;
    } else if (ThisReturn < -m_XSDThreshold) {
        m_spState.unitsDesired -= m_tradeSize;
    } else {
        m_spState.unitsDesired += 0;
    }

    if (m_spState.marketActive) AdjustPortfolio();
*/
}

void SentiMom::AdjustPortfolio()
{
    // wait until orders are filled before we send out more orders
    if (orders().num_working_orders() > 0) {
        return;
    }

    int unitsNeeded = m_spState.unitsDesired - portfolio().position(m_instrumentX);

    if (unitsNeeded > 0) {
        //SendBuyOrder(m_instrumentX, unitsNeeded);
        SendBuyOrder(m_instrumentX, unitsNeeded);

    } else if (unitsNeeded < 0) {
        //SendSellOrder(m_instrumentX, -unitsNeeded);
        SendSellOrder(m_instrumentX, -unitsNeeded);
    }
}

void SentiMom::SendBuyOrder(const Instrument* instrument, int unitsNeeded)
{
    if (m_DebugOn) {
        std::stringstream ss;
        ss << "Sending buy order for " << instrument->symbol() << " at price " << instrument->top_quote().ask() << " and quantity " << unitsNeeded;   
        logger().LogToClient(LOGLEVEL_DEBUG, ss.str());
	std::cout<<ss.str()<<'\n';
    }

    OrderParams params(*instrument, 
        unitsNeeded,
        (instrument->top_quote().ask() != 0) ? instrument->top_quote().ask() : instrument->last_trade().price(), 
        (instrument->type() == INSTRUMENT_TYPE_EQUITY) ? MARKET_CENTER_ID_NASDAQ : ((instrument->type() == INSTRUMENT_TYPE_OPTION) ? MARKET_CENTER_ID_CBOE_OPTIONS : MARKET_CENTER_ID_CME_GLOBEX),
        ORDER_SIDE_BUY,
        ORDER_TIF_DAY,
        ORDER_TYPE_MARKET);

    trade_actions()->SendNewOrder(params);
}
    
void SentiMom::SendSellOrder(const Instrument* instrument, int unitsNeeded)
{
    if(m_DebugOn) {
        std::stringstream ss;
        ss << "Sending sell order for " << instrument->symbol() << " at price " << instrument->top_quote().bid() << " and quantity " << unitsNeeded;   
        logger().LogToClient(LOGLEVEL_DEBUG, ss.str());
	std:cout<<ss.str()<<'\n';
    }

    OrderParams params(*instrument, 
        unitsNeeded,
        (instrument->top_quote().bid() != 0) ? instrument->top_quote().bid() : instrument->last_trade().price(), 
        (instrument->type() == INSTRUMENT_TYPE_EQUITY) ? MARKET_CENTER_ID_NASDAQ : ((instrument->type() == INSTRUMENT_TYPE_OPTION) ? MARKET_CENTER_ID_CBOE_OPTIONS : MARKET_CENTER_ID_CME_GLOBEX),
        ORDER_SIDE_SELL,
        ORDER_TIF_DAY,
        ORDER_TYPE_MARKET);

    trade_actions()->SendNewOrder(params);
}

void SentiMom::OnMarketState(const MarketStateEventMsg& msg)
{
}

void SentiMom::OnOrderUpdate(const OrderUpdateEventMsg& msg)  
{
}

void SentiMom::OnAppStateChange(const AppStateEventMsg& msg)
{
}

void SentiMom::OnParamChanged(StrategyParam& param)
{    
    if(param.param_name() == "Price_Thershold"){
	if(!param.Get(&m_MomThreshold))
            throw StrategyStudioException("Could not get Price threshold");		
    } else if (param.param_name() == "Sentiment_Threshold") {
        if (!param.Get(&m_SentiThreshold))
            throw StrategyStudioException("Could not get sentiment threshold");
    } else if (param.param_name() == "trade_size") {
        if (!param.Get(&m_tradeSize))
            throw StrategyStudioException("Could not get trade size");
    } else if (param.param_name() == "debug") {
        if (!param.Get(&m_DebugOn))
            throw StrategyStudioException("Could not get trade size");
    }        
}
