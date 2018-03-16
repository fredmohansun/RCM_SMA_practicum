/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/StrategyStateControlEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_STRATEGY_STATE_CONTROL_STATE_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_STRATEGY_STATE_CONTROL_STATE_EVENT_MSG_H_

#include "EventMsg.h"
#include "DataTypes.h"
#include "DataTypesUtils.h"
#include "Event.h"
#include <Utilities/IParams.h>

namespace LimeBrokerage {
namespace StrategyStudio {

enum StrategyStateControlEventType {   
    STRATEGY_STATE_CONTROL_EVENT_TYPE_UNKNOWN = 0,
    STRATEGY_STATE_CONTROL_EVENT_NOTIFY = 1,                // used to notify strategy of a state change 
    STRATEGY_STATE_CONTROL_EVENT_REQUEST = 2,               // used when client requests strategy to trade  
    STRATEGY_STATE_CONTROL_EVENT_RESET_FOR_BACKTEST = 3,    // used to change back to start after back test done 
    STRATEGY_STATE_CONTROL_EVENT_RESET_LIVE = 4
};


/**
 * StrategyStateControlEventMsg is an event type for notifying Strategies about a change in their state, for instance when the 
 * Strategy Studio client application (eg Strategy Manager) instructs a strategy to start or stop.
 */ 
class StrategyStateControlEventMsg : public EventMsg {
public:

    StrategyStateControlEventMsg(StrategyStateControlEventType eventType, Event* ev);

    StrategyStateControlEventMsg(StrategyStateControlEventType eventType, StrategyState strategyState, Event* ev);

    StrategyStateControlEventMsg(StrategyStateControlEventType eventType, StrategyState strategyState, const Utilities::IParams* params, Event* ev);
    
    StrategyStateControlEventMsg(const StrategyStateControlEventMsg& msg);

    ~StrategyStateControlEventMsg();

    std::string name() const;

    /**
     * Returns the current state of the strategy
     */
    const StrategyState& strategy_state() const			{ return m_strategyState; }
    void set_strategy_state(const StrategyState& state) { m_strategyState = state; }

    int local_tag() const         { return m_nLocalTag; }
    void set_local_tag(int tag)       { m_nLocalTag = tag; }

    void* closure() const            { return m_closure; }
    void set_closure(void* closure)  { m_closure = closure; }

    //TimeType time_tag() const        { return m_timeTag; }
    //void set_time_tag(TimeType tag)  { m_timeTag = tag; }

    const Utilities::IParams* params() const           { return m_params; }
    void set_params(const Utilities::IParams* params)  { m_params = params; }
    
    StrategyStateControlEventType control_event_type() const { return m_strategyControlType; }

    StrategyStateControlEventMsg& operator=(const StrategyStateControlEventMsg& msg);

private:
    StrategyStateControlEventType m_strategyControlType;
    StrategyState m_strategyState;
    int m_nLocalTag; 
    void *m_closure; 
    //TimeType m_timeTag;
    const Utilities::IParams* m_params;
};

inline std::string StrategyStateControlEventMsg::name() const
{
    return "StrategyStateCntl_State_" + DataTypesUtils::ToString(m_strategyState);
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
