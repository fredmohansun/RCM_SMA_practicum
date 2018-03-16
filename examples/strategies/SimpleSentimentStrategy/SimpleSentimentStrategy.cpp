/*================================================================================                               
*     Source: ../Lime/StrategyStudio/examples/strategies/SimpleSentimentStrategy/SimpleSentimentStrategy.cpp                                                        
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

#include "SimpleSentimentStrategy.h"

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

SimpleSentiment::SimpleSentiment(StrategyID strategyID, const std::string& strategyName, const std::string& groupName):
    Strategy(strategyID, strategyName, groupName),
    position_targets_(),
    sentiment_threshold_(1.5),
    min_buzz_(.5),
    min_sentiment_volume_(3),
    position_size_(100),
    hold_overnight_positions_(false),
    debug_(false),
    nearing_close_time_(false)
{
    //this->set_enabled_pre_open_data_flag(true);
    //this->set_enabled_pre_open_trade_flag(true);
    //this->set_enabled_post_close_data_flag(true);
    //this->set_enabled_post_close_trade_flag(true);
}

SimpleSentiment::~SimpleSentiment()
{
}

void SimpleSentiment::OnResetStrategyState()
{
    position_targets_.clear();
    nearing_close_time_ = false;
}

void SimpleSentiment::DefineStrategyParams()
{
    CreateStrategyParamArgs arg1("sentiment_threshold", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, sentiment_threshold_, .001);
    params().CreateParam(arg1);

    CreateStrategyParamArgs arg2("min_buzz", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_DOUBLE, min_buzz_);
    params().CreateParam(arg2);

    CreateStrategyParamArgs arg3("min_sentiment_volume", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_INT, min_sentiment_volume_, 1);
    params().CreateParam(arg3);

    CreateStrategyParamArgs arg5("position_size", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_INT, position_size_, 1, 1000);
    params().CreateParam(arg5);

    CreateStrategyParamArgs arg6("hold_overnight_positions", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_BOOL, hold_overnight_positions_);
    params().CreateParam(arg6);

    CreateStrategyParamArgs arg7("debug", STRATEGY_PARAM_TYPE_RUNTIME, VALUE_TYPE_BOOL, debug_);
    params().CreateParam(arg7);
}

void SimpleSentiment::RegisterForStrategyEvents(StrategyEventRegister* eventRegister, DateType currDate)
{    
    nearing_close_time_ = false;

    for(SymbolSetConstIter it = symbols_begin(); it != symbols_end(); ++it) {
        eventRegister->RegisterForSentiment(*it);
    }

    eventRegister->RegisterForRecurringScheduledEvents("AdjustOrders", USEquityOpenUTCTime(currDate) + boost::posix_time::minutes(10), USEquityCloseUTCTime(currDate), boost::posix_time::seconds(10));
    eventRegister->RegisterForSingleScheduledEvent("NearingClose", USEquityCloseUTCTime(currDate) - boost::posix_time::minutes(10), true);
}

void SimpleSentiment::OnSentiment(const SentimentEventMsg& msg)
{
    //lookup instrument from SMA symbol
    InstrumentSetConstIter instr_it = instrument_find(msg.entity());

    if (instr_it != instrument_end()) {
        int desiredPosition = 0;
        if (msg.s_buzz() >= min_buzz_ && msg.s_volume() >= min_sentiment_volume_) {
            if (msg.s_score() > sentiment_threshold_) {
                desiredPosition = position_size_;
            } else if (msg.s_score() < -sentiment_threshold_) {
                desiredPosition = -position_size_;
            }
        }
        position_targets_[instr_it->second] = desiredPosition;

        if (debug_) {
            std::stringstream ss;
            ss << "Received sentiment for " << msg.entity() << " s_score:" << msg.s_score() << " s_buzz: " << msg.s_buzz() << " s_volume " << msg.s_volume() << " targetPos: " << desiredPosition;
            logger().LogToClient(LOGDEBUG, ss.str());
        }
    }
}

void SimpleSentiment::OnScheduledEvent(const ScheduledEventMsg& msg)
{
    if (msg.scheduled_event_name() == "AdjustOrders") {
        for (InstrumentSetConstIter cit = instrument_begin(); cit != instrument_end(); ++cit) {
            AdjustOrder(cit->second);
        }
    } else if (msg.scheduled_event_name() == "NearingClose") {
        nearing_close_time_ = true;
    }
}

void SimpleSentiment::AdjustOrder(const Instrument* instrument)
{
    const IOrderStatistics& order_stats = orders().stats(instrument);

    int target_position = (nearing_close_time_ && !hold_overnight_positions_) ? 0 : position_targets_[instrument];

    int shares_needed = target_position - portfolio().position(instrument);
    int shares_working = order_stats.net_working_order_size();

    // if we're trying to get out of positions at end of day, send more aggressive orders
    double aggressiveness = (nearing_close_time_ && !hold_overnight_positions_) ? .10 : 0;

    // if we're working the wrong side of the market or working too much, cancel orders, wait to refresh orders until next time
    if ((shares_needed * shares_working) < 0 || (abs(shares_working) > abs(shares_needed))) {
        trade_actions()->SendCancelAll(instrument);
    } else if (shares_working == shares_needed) {
        // if we're already working the appropriate quantity, look  to cancel any stale orders
        for (IOrderTracker::WorkingOrdersConstIter orders_it = orders().working_orders_begin(instrument); orders_it != orders().working_orders_end(instrument); ++orders_it) {
            const Order* ord = (*orders_it);
            if (ord->order_side() == ORDER_SIDE_BUY) {
                if (bid(instrument) + aggressiveness - ord->price() > .05) {
                    trade_actions()->SendCancelOrder(ord->order_id());
                }
            } else if (ord->price() - ask(instrument) - aggressiveness > .05) {
                trade_actions()->SendCancelOrder(ord->order_id());
            }
        }
    } else {
        // need to send an order 
        int tradeSize = shares_needed - shares_working;
        OrderParams params(*instrument, 
            abs(tradeSize),
            tradeSize > 0 ? bid(instrument) + aggressiveness : ask(instrument) - aggressiveness, 
            MARKET_CENTER_ID_ARCA,
            tradeSize > 0 ? ORDER_SIDE_BUY : ORDER_SIDE_SELL,
            ORDER_TIF_DAY,
            ORDER_TYPE_LIMIT);

        trade_actions()->SendNewOrder(params);
    }   
}

void SimpleSentiment::OnMarketState(const MarketStateEventMsg& )
{
}

void SimpleSentiment::OnOrderUpdate(const OrderUpdateEventMsg& )  
{
}

void SimpleSentiment::OnParamChanged(StrategyParam& param)
{    
    if (param.param_name() == "sentiment_threshold") {
        if (!param.Get(&sentiment_threshold_))
            throw StrategyStudioException("Could not get sentiment_threshold");
    } else if (param.param_name() == "min_buzz") {
        if (!param.Get(&min_buzz_))
            throw StrategyStudioException("Could not get min_buzz");
    } else if (param.param_name() == "min_sentiment_volume") {
        if (!param.Get(&min_sentiment_volume_))
            throw StrategyStudioException("Could not get min_sentiment_volume");
    } else if (param.param_name() == "position_size") {
        if (!param.Get(&position_size_))
            throw StrategyStudioException("Could not get position_size_");
    } else if (param.param_name() == "hold_overnight_positions") {
        if (!param.Get(&hold_overnight_positions_))
            throw StrategyStudioException("Could not get hold_overnight_positions");
    } else if (param.param_name() == "debug") {
        if (!param.Get(&debug_))
            throw StrategyStudioException("Could not get debug");
    }
}
