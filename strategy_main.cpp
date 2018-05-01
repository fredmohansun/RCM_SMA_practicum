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

const double Level[5] = {0.0, 0.25, 0.50, 0.75, 1.0};
const int L_count = 5;

typedef std::map<TimeType, PSentimentEventMsg> SMAmap;
ofstream output_file("result.csv", std::fstream::out);

TimeType TimeHelper(std::string line){
    std::stringstream split_helper(line);
    std::vector <std::string> split((std::istream_iterator<std::string>(split_helper)), std::istream_iterator<std::string>());
    std::string mytime = split[1]+' '+split[2]+".000";
    TimeType res = TimeType(boost::posix_time::time_from_string(mytime));
    return res;
}

SentiMom::SentiMom(StrategyID strategyID, const std::string& strategyName, const std::string& groupName):
    Strategy(strategyID, strategyName, groupName),
    m_spState(),
    m_bars(),
    m_instrumentX(NULL),
    m_srollingWindow(7*24*4),
    m_mrollingWindow(7*24*4),
    m_SentiThreshold(0.5),
    m_MomThreshold(0.5),
    m_nOrdersOutstanding(0),
    m_DebugOn(true),
    m_stoplossthreshold(0.985),
    sma_data()
{
    output_file<<"Date,Equity,Close,Level\n";
    ifstream input_file("BTC.X.txt", std::fstream::in);
    std::string line;
    getline(input_file, line);//Get metadata
    while(!input_file.eof()){
        getline(input_file, line);
	if(line[0]=='e') break;
        PSentimentEventMsg SMA_entry = PSentimentEventMsg(line);
        TimeType SMA_time = TimeHelper(line);
        sma_data.insert(std::pair<TimeType, PSentimentEventMsg>(SMA_time, SMA_entry));
    }
    // note: assume market state is active
    m_spState.marketActive = true;
    this->set_enabled_pre_open_data_flag(true);
    this->set_enabled_pre_open_trade_flag(true);
    this->set_enabled_post_close_data_flag(true);
    this->set_enabled_post_close_trade_flag(true);
}

SentiMom::~SentiMom()
{
}

void SentiMom::OnResetStrategyState()
{
    m_spState.marketActive = true;
    m_spState.unitDesired = 0.0;
    m_spState.level = 0;
    m_spState.stop_loss = 0.0;
    m_spState.stop_or_not = false;
    m_spState.nstoploss = 0;

    m_srollingWindow.clear();
    m_mrollingWindow.clear();
    m_bars.clear();
}

void SentiMom::DefineStrategyParams()
{
    CreateStrategyParamArgs arg1("Price Threshold", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_MomThreshold);
    params().CreateParam(arg1);

    CreateStrategyParamArgs arg2("Sentiment Threshold", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, m_SentiThreshold);
    params().CreateParam(arg2);

    CreateStrategyParamArgs arg3("debug", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_BOOL, m_DebugOn);
    params().CreateParam(arg3);
}

void SentiMom::DefineStrategyGraphs()
{
    // graphs().series().add("Mean"); 
    // graphs().series().add("Level");
}

void SentiMom::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate)
{   
    for (SymbolSetConstIter it = symbols_begin(); it != symbols_end(); ++it) {
        EventInstrumentPair retVal = eventRegister->RegisterForBars(*it, BAR_TYPE_TIME, 60 * 15, 2.0, ConvertLocalToUTC(TimeType(currDate))+ boost::posix_time::minutes(10));    
        m_instrumentX = retVal.second;
    }
    eventRegister->RegisterForRecurringScheduledEvents("End_Day_Adjustment", ConvertLocalToUTC(TimeType(currDate)), NULL_TIME_TYPE, boost::posix_time::hours(24));
    eventRegister->RegisterForRecurringScheduledEvents("Stop_Loss_Adjustment", ConvertLocalToUTC(TimeType(currDate)), NULL_TIME_TYPE, boost::posix_time::minutes(1));
}

void SentiMom::OnTopQuote(const QuoteEventMsg& msg)
{
}

void SentiMom::OnBar(const BarEventMsg& msg)
{
    TimeType current_time = msg.bar_time();
    std::pair<SMAmap::iterator, SMAmap::iterator> data_iterator = sma_data.equal_range(current_time);
    PSentimentEventMsg this_sma = data_iterator.first->second;
    output_file<<current_time<<','<<portfolio().account_equity()<<','<<m_bars[m_instrumentX].close()<<','<<m_spState.level<<'\n';
    if (m_DebugOn) {
        ostringstream str;
        str <<"At bar_time:"<<current_time<< "received BTC's S: "<<this_sma.s();
        logger().LogToClient(LOGLEVEL_DEBUG, str.str().c_str());
    }
    m_bars[&msg.instrument()] = msg.bar();
    m_spState.stop_loss=m_stoplossthreshold*m_bars[m_instrumentX].close();
    m_spState.stop_or_not=false;

    double this_close = m_bars[m_instrumentX].close();
    m_mrollingWindow.push_back(this_close);
    m_srollingWindow.push_back(this_sma.s());
    if (!m_srollingWindow.full()||!m_mrollingWindow.full())    return;

    if(this_close > m_mrollingWindow.Mean() + m_MomThreshold * m_mrollingWindow.StdDev()){
	if(m_spState.level == 0){
            m_spState.level = 2;
	    m_spState.unitDesired = (Level[m_spState.level] * portfolio().account_equity())/m_bars[m_instrumentX].close()*10000;
            //graphs().series()["Level"]->push_back(msg.event_time(), m_spState.level);
            AdjustPortfolio();
            return;
	}
        if(this_sma.s()>m_srollingWindow.Mean() + 2 * m_SentiThreshold * m_srollingWindow.StdDev()){
            if(m_spState.level + 2 < L_count)
                m_spState.level += 2;
            else
                m_spState.level = L_count-1;
            m_spState.unitDesired = (Level[m_spState.level] * portfolio().account_equity())/m_bars[m_instrumentX].close()*10000;
            AdjustPortfolio();
            return;
        }
        else if(this_sma.s()>m_srollingWindow.Mean() + m_SentiThreshold * m_srollingWindow.StdDev()){
            if(m_spState.level + 1 < L_count)
                m_spState.level++;
            else
                m_spState.level = L_count-1;
            m_spState.unitDesired = (Level[m_spState.level] * portfolio().account_equity())/m_bars[m_instrumentX].close()*10000;
            AdjustPortfolio();
            return;
        }
        else    return; //No adjusting intra day if not confident enough
    }
    else if (this_close < m_mrollingWindow.Mean() - m_MomThreshold * m_mrollingWindow.StdDev()){
        if(this_sma.s()>m_srollingWindow.Mean() - 2 * m_SentiThreshold * m_srollingWindow.StdDev()){
            if(m_spState.level - 2 >= 0)
                m_spState.level -= 2;
            else
                m_spState.level = 0;
            m_spState.unitDesired = (Level[m_spState.level] * portfolio().account_equity())/m_bars[m_instrumentX].close()*10000;
            AdjustPortfolio();
            return;
        }
        else if(this_sma.s()>m_srollingWindow.Mean() - m_SentiThreshold * m_srollingWindow.StdDev()){
            if(m_spState.level - 1 >=0)
                m_spState.level--;
            else
                m_spState.level = 0;
            m_spState.unitDesired = (Level[m_spState.level] * portfolio().account_equity())/m_bars[m_instrumentX].close()*10000;
            AdjustPortfolio();
            return;
        }
        else    return; //No adjusting intra day if not confident enough
    }
	
}

void SentiMom::OnScheduledEvent(const ScheduledEventMsg& msg){
    if(msg.scheduled_event_name() == "End_Day_Adjustment"){
	// AdjustPortfolio();
        return;
    }
    if(msg.scheduled_event_name() == "Stop_Loss_Adjustment"){
	for(SymbolSetConstIter it = symbols_begin(); it != symbols_end(); ++it){
	    const Instrument *ins = instrument_find(*it)->second;
	    double price = ins->last_trade().price();
	    m_spState.stop_loss=m_stoplossthreshold*price;
	}
        return;
    }
}
void SentiMom::OnTrade(const TradeDataEventMsg& msg){
	/*
	 if((msg.trade().price() < m_spState.stop_loss)&&m_spState.stop_or_not==false)
	 {
	    if (m_DebugOn) {
        	ostringstream str;
        	str <<"Price:" <<msg.trade().price()<<",hit "<<m_spState.stop_loss<<", triggered the No."<<++m_spState.nstoploss<<"'s Stoping loss...";
        	logger().LogToClient(LOGLEVEL_INFO, str.str().c_str());
	    }
		m_spState.unitDesired=0;
		m_spState.level=0;
                AdjustPortfolio();
	        m_spState.stop_or_not=true;
	   	return;
	 }
	 */
 }
			 
void SentiMom::AdjustPortfolio()
{
    // wait until orders are filled before we send out more orders
    /*if (orders().num_working_orders() > 0) {
        return;
    }*/
    double temp = m_spState.unitDesired - portfolio().position(m_instrumentX); 
    int unitsNeeded = (temp - (temp/1) >=0.5) ? (temp/1+1) : (temp / 1);
    while(abs(temp)>2147483647){
        if (temp > 0){ 
            SendBuyOrder(m_instrumentX, 2000000000);
	    temp -= 2000000000;
	}
        else if (temp < 0){
            SendSellOrder(m_instrumentX, 2000000000);
	    temp += 2000000000;
	}
    }
    unitsNeeded = (temp - (temp/1) >=0.5) ? (temp/1+1) : (temp / 1);
    if (unitsNeeded > 0) 
        SendBuyOrder(m_instrumentX, unitsNeeded);
    else if (unitsNeeded < 0) 
        SendSellOrder(m_instrumentX, -unitsNeeded);
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
    } else if (param.param_name() == "debug") {
        if (!param.Get(&m_DebugOn))
            throw StrategyStudioException("Could not get trade size");
    }        
}
