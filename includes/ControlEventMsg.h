/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/ControlEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_CONTROL_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_CONTROL_EVENT_MSG_H_

#include "TimePrioritizedEventMsg.h"
#include "Event.h"
#include "DataTypes.h"
#include <Utilities/IParams.h>
#include <FlashProtocol/FlashBase.h>

namespace LimeBrokerage {
namespace StrategyStudio {

enum ControlEventType {
    CONTROL_EVENT_TYPE_UNKNOWN,
    CONTROL_EVENT_TYPE_PNL_REPORT,         // request strategy to send current pnl information 
    CONTROL_EVENT_TYPE_POS_REPORT,         // request strategy to send current position information 
    CONTROL_EVENT_TYPE_PARAMS_UPDATE,      // request strategy to update params
    CONTROL_EVENT_TYPE_END_OF_DAY_PNL_PERIOD,// request strategy to handle end of day PnL period
    CONTROL_EVENT_TYPE_INITIALIZE_DAY_PNL_PERIOD,// request strategy to send initial day PnL message
    CONTROL_EVENT_TYPE_EXCH_FEES,          // request strategy to set exchange fees
    CONTROL_EVENT_TYPE_EXCH_SIM_PARAMS,    // request strategy to set exchange simulator params  
    CONTROL_EVENT_TYPE_EXCH_REQ_PARAMS,    // request sending of all exchange params 
    CONTROL_EVENT_TYPE_SERIALIZE_STATE,    // request strategy to save snapshots, settings, and results
    CONTROL_EVENT_TYPE_RESET_FOR_NEW_DAY   // request to reset strategy for new day 
};

class ControlEventTypeUtils {
public:
    static const std::string& ToString(ControlEventType type);
};

/**
 * ControlEventMsg an event type for marshalling data about the strategy
 */ 
class ControlEventMsg : public TimePrioritizedEventMsg {
public:

    ControlEventMsg(ControlEventType eventType, Event* ev);

    ControlEventMsg(ControlEventType eventType, TimeType fireTime, Event* ev);

    ControlEventMsg(ControlEventType eventType, const Utilities::IParams* params, Event* ev);

    // This one is used for passing flash messages
    ControlEventMsg(ControlEventType eventType, StrategyStudioUInt16 connID, const FlashProtocol::FlashBase *msg, Event* ev);

    ControlEventMsg(const ControlEventMsg& msg);

    ~ControlEventMsg();

    std::string name() const;

    int local_tag() const				 { return m_nLocalTag; }
    void set_local_tag(int tag)			 { m_nLocalTag = tag; }

    void* closure() const				 { return m_closure; }
    void set_closure(void* closure)		 { m_closure = closure; }

    TimeType time_tag() const			 { return m_timeTag; }
    void set_time_tag(TimeType tag)      { m_timeTag = tag; }

    const Utilities::IParams* params() const           { return m_params; }
    void set_params(const Utilities::IParams* params)  { m_params = params; }

	std::string UserName() const					   { return m_userName; }
	void set_user_name(const std::string& userName)	   { m_userName = userName; }

    const FlashProtocol::FlashBase *Message() const { return m_message; }
    StrategyStudioUInt16 ConnId() const { return m_connId; }

    ControlEventType control_event_type() const { return m_eventType; }

    ControlEventMsg& operator=(const ControlEventMsg& msg);
    
    bool Trigger(TimeType /*currTime*/) { return true; }

private:
    ControlEventType m_eventType;
    int m_nLocalTag; 
    void *m_closure; 
    TimeType m_timeTag;
    const Utilities::IParams* m_params;
    const FlashProtocol::FlashBase *m_message;
    StrategyStudioUInt16 m_connId;
	std::string m_userName;
};

inline std::string ControlEventMsg::name() const
{
    return "Control_" + ControlEventTypeUtils::ToString(m_eventType);
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
