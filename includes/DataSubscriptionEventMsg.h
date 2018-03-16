/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/DataSubscriptionDataEventMsg.h
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

#ifndef _STRATEGY_STUDIO_LIB_DATA_SUBSCRIPTION_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_DATA_SUBSCRIPTION_EVENT_MSG_H_

#include "DataTypes.h"
#include "DataSourceTypes.h"
#include "EventMsg.h"
#include "Event.h"

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * DataSubscriptionEventMsg informs strategies of changes in state for a particular 
 * data subscription from a data adapter.
 */ 
class DataSubscriptionEventMsg : public EventMsg {
public:

    DataSubscriptionEventMsg(DataSubscriptionState state, 
                             DataSubscriptionAlert alert, 
                             FeedType feed_type,
                             MarketCenterID market_center,
                             Event* ev);

    DataSubscriptionEventMsg(DataSubscriptionState state, 
                             DataSubscriptionAlert alert, 
                             FeedType feed_type,
                             MarketCenterID market_center,
                             const std::string& description,
                             StrategyStudioInt32 severity,
                             Instrument* instrument,
                             Event* ev);

    DataSubscriptionEventMsg(const DataSubscriptionEventMsg& msg);
    
    ~DataSubscriptionEventMsg();

    std::string name() const;

    /** 
     * Returns the current state of the data subscription
     */
    DataSubscriptionState state() const         { return m_state; }
    
    /**
     * This classifies the type of alert coming from the data source
     */
    DataSubscriptionAlert alert() const         { return m_alert; }
    
    /**
     * Identifies which type of data feed is delivering an alert
     */
    FeedType feed_type() const					{ return m_feed_type; }
    
    /**
     * Returns which market center's feed is delivering an alert
     *
     * Returns MARKET_CENTER_ID_UNKNOWN for consoloidated data feeds
     */
    MarketCenterID market_center() const		{ return m_market_center; }

    /**
     * Provides additional information about the alert when applicable
     */
    const std::string& description() const		{ return m_description; }

    /**
     * Returns a number used to indicate the severity of the data alert.
     *
     * Typically this field is used for the number of messages lost when
     * the alert is DATA_SUBSCRIPTION_ALERT_DATA_GAP_DETECTED
     */
    const StrategyStudioInt32 severity() const			{ return m_severity; }

    /**
     * Returns the instrument affected by the data alert if attributable, null otherwise
     */
    const Instrument* instrument() const        { return m_instrument; }
    
    DataSubscriptionEventMsg& operator=(const DataSubscriptionEventMsg& msg);

private:
    DataSubscriptionState m_state;
    DataSubscriptionAlert m_alert; 
    FeedType m_feed_type;
    MarketCenterID m_market_center;
    std::string m_description;
    StrategyStudioInt32 m_severity;
    Instrument* m_instrument;                           
};

inline std::string DataSubscriptionEventMsg::name() const
{
    return "DATA_SUBSCRIPTION_EVENT_" + 
        DataSubscriptionStateToString(m_state) + "_" +
        DataSubscriptionAlertToString(m_alert) + 
        ( (m_instrument != NULL) ? ("_" + m_instrument->symbol()) : "");
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
