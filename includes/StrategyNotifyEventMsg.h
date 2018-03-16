/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/StrategyNotifyEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_STRATEGY_NOTIFY_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_STRATEGY_NOTIFY_EVENT_MSG_H_

#include "TimePrioritizedEventMsg.h"
#include "Event.h"
#include "DataTypes.h"
#include <ostream>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * StrategyNotifyEventMsg delivers messages from one strategy to another
 */ 
class StrategyNotifyEventMsg : public TimePrioritizedEventMsg {
public:
    static const int TIMED_EVENT_PRIORITY = 4;

public:

	StrategyNotifyEventMsg(const std::string& sender, 
                           const std::string& target, 
                           const std::string& msg,
                           Event* evt);

    StrategyNotifyEventMsg(const std::string& sender, 
                           const std::string& target, 
                           const std::string& msg,
                           void* closure,
                           Event* evt);

    StrategyNotifyEventMsg(const StrategyNotifyEventMsg& msg);

	~StrategyNotifyEventMsg();

    /**
     * Name of the strategy that sent the message
     */
    const std::string& sender() const                { return m_sender; }

    /**
     * Name of the destination strategy
     */
    const std::string& target() const                { return m_target; }        

    /**
     * Contents of the inter-strategy message
     */
    const std::string& msg() const                   { return m_msg; }

    /**
     * Arbitrary closure object passed along with the message.
     */
    void* closure() const                            { return m_closure; }

    /**
     * Checks whether the message has an associated closure object
     */
    bool HasClosure() const                          { return (m_closure != NULL); }

    bool Trigger(TimeType currTime);
    
    StrategyNotifyEventMsg& operator=(const StrategyNotifyEventMsg& msg);

private:
    std::string m_sender; 
    std::string m_target;
    std::string m_msg;    
    void* m_closure;
};

inline std::ostream& operator<<(std::ostream& out, const StrategyNotifyEventMsg& msg)
{
    out << "Strategy notify event. Sender: " << msg.sender() << " Target: " << msg.target() << 
        " Msg: " << msg.msg(); 
   
    return out;
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
