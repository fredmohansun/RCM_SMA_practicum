/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/EventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_EVENT_MSG_H_

#include "ServerDebugLogBase.h"
#include <Utilities/TimeType.h>

#define MAX_EVENT_LEVELS 3

namespace LimeBrokerage {
namespace StrategyStudio {

enum EventMsgType {
    EVENT_MSG_TYPE_UNKNOWN = 0,
    EVENT_MSG_TYPE_DEPTH_DATA,
    EVENT_MSG_TYPE_QUOTE_DATA,
    EVENT_MSG_TYPE_TRADE_DATA,
    EVENT_MSG_TYPE_OPTIONS_ANALYTICS,
    EVENT_MSG_TYPE_WORKUP_DATA,
    EVENT_MSG_TYPE_IMBALANCE_DATA,
    EVENT_MSG_TYPE_INSTRUMENT_ALERT,
    EVENT_MSG_TYPE_PRICE_BAND,
    EVENT_MSG_TYPE_INDEX,
    EVENT_MSG_TYPE_ORDER_UPDATE,
    EVENT_MSG_TYPE_BAR_DATA,
    EVENT_MSG_TYPE_SERVER_HEARTBEAT,
    EVENT_MSG_TYPE_NEWS,
    EVENT_MSG_TYPE_SENTIMENT,
    EVENT_MSG_TYPE_SCHEDULED,
    EVENT_MSG_TYPE_STRATEGY_NOTIFY,
    EVENT_MSG_TYPE_CONTROL,
    EVENT_MSG_TYPE_TRADE_STATS_INIT,
    EVENT_MSG_TYPE_APP_STATE,
    EVENT_MSG_TYPE_BACKTESTER,
    EVENT_MSG_TYPE_STRATEGY_STATE_CONTROL,	
    EVENT_MSG_TYPE_STRATEGY_CREATE,
    EVENT_MSG_TYPE_MARKET_STATE,
    EVENT_MSG_TYPE_CORP_ACTION,
    EVENT_MSG_TYPE_EXCHANGE_FEES,
    EVENT_MSG_TYPE_SIM_PARAMS,
    EVENT_MSG_TYPE_REPLAY,
    EVENT_MSG_TYPE_ORDER_RESYNC,
    EVENT_MSG_TYPE_DATA_SUBSCRIPTION,
    EVENT_MSG_TYPE_STRATEGY_EXTERNAL_FILL_NOTIFY,
    EVENT_MSG_TYPE_EXTERNAL_ORDER,
    EVENT_MSG_TYPE_EXTERNAL_BASKET_ORDER,
    EVENT_MSG_TYPE_ACCOUNT_FEES_CHANGE,
    EVENT_MSG_TYPE_ACCOUNT_CHANGE,
    EVENT_MSG_TYPE_PREFERRED_FEED_TYPE_CHANGE,
    EVENT_MSG_TYPE_TOPIC_SUBSCRIPTION,
    EVENT_MSG_TYPE_STRATEGY_COMMAND,
    EVENT_MSG_TYPE_CLOSURE,
    EVENT_MSG_TYPE_INSTRUMENT_REF_UPDATE
};

class EventMsgTypeUtils {
public:
    static const std::string& ToString(EventMsgType type);
};

class Event;

/**
 * EventMsg is the base class for event messages which hold the information for a given 
 * event. 
 */ 
class EventMsg : protected ServerDebugLogBase {
public:
    EventMsg(EventMsgType eventMsgType, Event* evt);
    EventMsg(EventMsgType eventMsgType, Event* evt, bool needsDelete);
    EventMsg(EventMsgType eventMsgType, Event* evt, Utilities::TimeType eventTime);
    EventMsg(EventMsgType eventMsgType, Event* evt, bool needsDelete, Utilities::TimeType eventTime);
    EventMsg(const EventMsg& eventMsg);
    virtual ~EventMsg();
    
    Event* get_event();
    const Event* get_event() const;

    void set_event(Event* evt)								 { m_event = evt; }

    EventMsgType event_message_type() const                  { return m_eventMsgType; }
    
    Utilities::TimeType event_time() const                   { return m_eventTime; }
    void set_event_time(Utilities::TimeType timeType)        { m_eventTime = timeType; }

    bool needs_delete() const                                { return m_bNeedsDelete; }
    void set_needs_delete(bool flag)                         { m_bNeedsDelete = flag; }

    virtual std::string name() const                         { return EventMsgTypeUtils::ToString(m_eventMsgType); }

    /**
     * Check if this is a market data type of event 
     */ 
    virtual bool IsMarketDataTypeEvent() const; 

    /**
     * Push event as active event 
     * Note: This does no checking for levels, so we can't exceed the max levels 
     */
    void PushActiveEvent(Event* evt);

    /**
     * Pop last event 
     * Note: This does no checking for levels, so we can't pop more than we have pushed
     */ 
    void PopActiveEvent();

    /**
     * Publish this message to all registered listeners 
     */ 
    virtual bool Process(); 

    EventMsg& operator=(const EventMsg& msg);

private: /* Hook functions */

    /**
     * This is an optional hook that derived messages can implement. 
     * Allows child message to customize some behavior before message is sent to listeners 
     * Optionally this function returns a bool signifying if this message should be propagated to listeners 
     * This allows custom filtering to be done based on event logic 
     * @returns true if message should be propagated to event listeners, false otherwise 
     */ 
    virtual bool PreProcess(); 

    /**
     * This is an optional hook that derived messages can implement. 
     * Allows child message to customize some behavior after message is sent to listeners 
     */ 
    virtual void PostProcess(); 

    // Meant just to avoid circular references 
    bool TriggerEvent();

private:
    EventMsgType m_eventMsgType;
    Event* m_event;
    Event* m_eventCache[MAX_EVENT_LEVELS];
    int m_eventLevel;                       // used for stacking events 
    Utilities::TimeType m_eventTime;        // signifies time that the event was created     
    bool m_bNeedsDelete;
};

inline Event* EventMsg::get_event()
{ 
    return ( (m_eventLevel == 0) ? m_event : m_eventCache[m_eventLevel - 1] ); 
}

inline const Event* EventMsg::get_event() const		 
{ 
    return ( (m_eventLevel == 0) ? m_event : m_eventCache[m_eventLevel - 1] ); 
} 

inline bool EventMsg::IsMarketDataTypeEvent() const
{	
    return ( (m_eventMsgType >= EVENT_MSG_TYPE_DEPTH_DATA) &&
             (m_eventMsgType <= EVENT_MSG_TYPE_INDEX) );
}

inline void EventMsg::PushActiveEvent(Event* evt)
{
    m_eventCache[++m_eventLevel - 1] = evt;
    assert(m_eventLevel <= MAX_EVENT_LEVELS); 
}
   
inline void EventMsg::PopActiveEvent()
{
    --m_eventLevel;
    assert(m_eventLevel >= 0);
}

inline bool EventMsg::Process()
{
    bool processed = false;

    // allow customized child behavior before msg is processed
    if (PreProcess())
    {        
        processed = TriggerEvent();
    }
    
    // allow customized child behavior after msg is processed
    PostProcess();

    return processed;
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
