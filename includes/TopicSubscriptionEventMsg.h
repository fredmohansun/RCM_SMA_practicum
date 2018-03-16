/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/TopicSubscriptionEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_TOPIC_SUBSCRIPTION_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_TOPIC_SUBSCRIPTION_EVENT_MSG_H_

#include "TimePrioritizedEventMsg.h"
#include "Event.h"
#include "DataTypes.h"
#include <boost/any.hpp>
#include <ostream>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * TopicSubscriptionEventMsg delivers the contents of a message broadcast to a named topic
 */ 
class TopicSubscriptionEventMsg : public TimePrioritizedEventMsg {
public:
    static const int TIMED_EVENT_PRIORITY = 4;

public:

    TopicSubscriptionEventMsg(const std::string& topic, 
                              const std::string& msg,
                              Event* evt);

    TopicSubscriptionEventMsg(const std::string& topic, 
                              const std::string& msg,
                              const boost::any& closure,
                              Event* evt);
    
    TopicSubscriptionEventMsg(const TopicSubscriptionEventMsg& msg);

    ~TopicSubscriptionEventMsg();

    /**
     * Name of the topic to which the message was broadcast
     */
    const std::string& topic() const                 { return m_topic; }    

    /**
     * Contents of the message
     */
    const std::string& msg() const                   { return m_msg; }

    /**
     * Arbitrary closure object passed along with the message.
     */
    const boost::any& closure() const                { return m_closure; }

    bool Trigger(TimeType currTime);
    
    TopicSubscriptionEventMsg& operator=(const TopicSubscriptionEventMsg& msg);

private:
    std::string m_topic;
    std::string m_msg;    
    boost::any m_closure;
};

inline std::ostream& operator<<(std::ostream& out, const TopicSubscriptionEventMsg& msg)
{
    out << "Topic subscription event. Topic: " << msg.topic() << " Msg: " << msg.msg();           
    return out;
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
