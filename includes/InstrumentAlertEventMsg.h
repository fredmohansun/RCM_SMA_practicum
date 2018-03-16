/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/InstrumentAlertEventMsg.h
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

#ifndef _STRATEGY_STUDIO_LIB_INSTRUMENT_ALERT_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_INSTRUMENT_ALERT_EVENT_MSG_H_

#include "DataTypes.h"
#include "DataTypesUtils.h"
#include "Event.h"
#include "MarketDataBaseEventMsg.h"

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * InstrumentAlertEventMsg informs strategies instrument specific alerts from a 
 * market data feed. Alerts include updates to trading status (halts), short sale restrictions, etc.
 */ 
class InstrumentAlertEventMsg : public MarketDataBaseEventMsg {
public:

    InstrumentAlertEventMsg(Event* evt,
                            Instrument* instrument, 	
                            MarketCenterID market_center,
                            FeedType feed_type,
                            InstrumentStatus instrument_status,
                            ShortSaleRestrictionIndicator short_sale_status,                              
                            TimeType source_time,
                            TimeType feed_handler_time,                  
                            TimeType adapter_time,
                            const std::string& reason = "");

    InstrumentAlertEventMsg(const InstrumentAlertEventMsg& msg);
    
    ~InstrumentAlertEventMsg();

    std::string name() const;

    const Instrument& instrument() const			{ return *m_instrument; }

    InstrumentStatus instrument_status() const                          { return m_instrument_status; } 

    ShortSaleRestrictionIndicator short_sale_status() const { return m_short_sale_status; }

    const std::string& reason() const				 { return m_reason; }

    /**
     * Returns which market center the alert pertains to
     */
    MarketCenterID market_center() const		{ return m_market_center; }

    /**
     * Identifies which type of data feed is delivering an alert
     */
    FeedType feed_type() const					{ return m_feed_type; }

    /**
     * Gets the market data source's timestamp for the market data event (eg the exchange feed's timestamp)
     */
    TimeType source_time() const				{ return m_source_time; }
    
    /**
     * Gets the time the feedhandler processed the market data event, if applicable and available 
     */
    TimeType feed_handler_time() const			{ return m_feed_handler_time; }
    
    /**
     * Gets the time when the Strategy Server's data adapter received the market data event
     */
    TimeType adapter_time() const				{ return m_adapter_time; }
       
    InstrumentAlertEventMsg& operator=(const InstrumentAlertEventMsg& msg);

private:
    std::string m_reason;

    Instrument* m_instrument;

    TimeType m_source_time;
    TimeType m_feed_handler_time;
    TimeType m_adapter_time;

    InstrumentStatus m_instrument_status;
    ShortSaleRestrictionIndicator m_short_sale_status;
    FeedType m_feed_type;
    MarketCenterID m_market_center;
};

inline std::string InstrumentAlertEventMsg::name() const
{
    return "INSTRUMENT_ALERT_EVENT_" + m_instrument->symbol();
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
