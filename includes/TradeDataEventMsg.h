/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/TradeDataEventMsg.h                                                        
*     Last Update: 2010/09/30 13:55:14 	                                                                       
*     Contents:                                     
*     Distribution:          
*                                                                                                                
*                                                                                                                
*     Copyright (c) Lime Brokerage LLC, 2009 - 2010.                                                    
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
==================================================================================*/   

#pragma once 

#ifndef _STRATEGY_STUDIO_LIB_TRADE_DATA_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_TRADE_DATA_EVENT_MSG_H_

#include "DataTypes.h"
#include "MarketDataBaseEventMsg.h"
#include "Event.h"

namespace LimeBrokerage {
namespace StrategyStudio {

class Event; 

/**
 * TradeDataEventMsg is the event type representing a Trade event from a market data source
 */ 
class TradeDataEventMsg : public MarketDataBaseEventMsg {
public:

    TradeDataEventMsg(FeedType tradeType, Event* ev, Instrument* instrument);
    
    TradeDataEventMsg(FeedType tradeType, 
                      Event* evt,
                      Instrument* instrument, 			 
                      double lastPrice, 
                      int quantity,
                      MarketCenterID exch,             
                      TradeSide side = TRADE_SIDE_UNKNOWN);

    TradeDataEventMsg(FeedType tradeType, 
                      Event* evt,
                      Instrument* instrument, 			 
                      double lastPrice, 
                      int quantity,
                      MarketCenterID exch,          
                      TimeType sourceTime,
                      TimeType feedHandlerTime,
                      TimeType adapterTime,
                      TradeSide side = TRADE_SIDE_UNKNOWN);

    TradeDataEventMsg(const TradeDataEventMsg& msg);

    ~TradeDataEventMsg();

    std::string name() const;

    /**
     * Returns the type of feed sending the trade tick
     */ 
    FeedType trade_feed_type() const { return m_tradeFeedType; }

    /**
     * Returns a const reference to the instrument which traded
     */
    const Instrument& instrument() const			{ return *m_instrument; }
    
    Trade& trade()                                  { return m_tradeData; }

    /**
     * Returns the trade that occurred
     */
    const Trade& trade() const                      { return m_tradeData; }

    /**
     * Returns the side of the trade, if known
     */ 
    TradeSide side() const                          { return m_side; }

    void set_side(TradeSide side)                   { m_side = side; }

    /**
     * Returns true if this was a trade from a consolidated feed
     */ 
    bool IsConsolidated() const                { return (m_tradeFeedType == FEED_TYPE_CONSOLIDATED); }

    /**
     * Returns true if this was a trade from a direct feed
     */ 
    bool IsDirect() const                      { return (m_tradeFeedType == FEED_TYPE_DIRECT); }

    /**
     * Returns true if this was a trade from a depth feed
     */ 
    bool IsFromDepth() const                   { return (m_tradeFeedType == FEED_TYPE_DEPTH); }
    
    /**
     * Gets the market data source's timestamp for the market data event (eg the exchange feed's timestamp)
     */
    TimeType source_time() const               { return m_tradeData.source_time(); }
    
    /**
     * Gets the time the feedhandler processed the market data event, if applicable and available 
     */
    TimeType feed_handler_time() const         { return m_tradeData.feed_handler_time(); }
    
    /**
     * Gets the time when the Strategy Server's data adapter received the market data event
     */
    TimeType adapter_time() const               { return m_tradeData.adapter_time(); }

    TradeDataEventMsg& operator=(const TradeDataEventMsg& msg);

private: /* Event msg hooks */

    /**
     * Handles updating of the instrument before handing instrument to strategy
     */
    virtual bool PreProcess(); 

private:
    FeedType m_tradeFeedType;
    Instrument* m_instrument; 
    Trade m_tradeData;  
    TradeSide m_side; 
    bool m_bIsConsolidated;
    bool m_bRegionalUpdated;
};

inline std::string TradeDataEventMsg::name() const
{
    return "TradeData_Instr_" + m_instrument->symbol();
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
