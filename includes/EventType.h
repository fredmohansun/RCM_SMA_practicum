/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/EventType.h
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

#ifndef _STRATEGY_STUDIO_LIB_EVENT_TYPE_INFO_H_
#define _STRATEGY_STUDIO_LIB_EVENT_TYPE_INFO_H_

#include <string>

namespace LimeBrokerage {
namespace StrategyStudio {

enum EventType {
    EVENT_TYPE_UNKNOWN = 0,
    EVENT_TYPE_DATA_SOURCE = 1,
    EVENT_TYPE_ORDER_UPDATE = 2,
    EVENT_TYPE_CONTROL = 3,
    EVENT_TYPE_BROADCAST_CONTROL = 4,
    EVENT_TYPE_BAR = 5,    
    EVENT_TYPE_STRATEGY_STATE_CHANGE = 6,
    EVENT_TYPE_CORP_ACTION = 7,
    EVENT_TYPE_APP_STATE_CHANGE = 8,
    EVENT_TYPE_MARKET_DATA = 9,
    EVENT_TYPE_REFERENCE_DATA_SOURCE = 10,
    EVENT_TYPE_NEWS_SOURCE = 11,
    EVENT_TYPE_SENTIMENT = 12,
	EVENT_TYPE_REPLAY = 13,
	EVENT_TYPE_ORDER_RESYNC = 14,
    EVENT_TYPE_SCHEDULED = 15,
    EVENT_TYPE_STRATEGY_NOTIFY = 16,
    EVENT_TYPE_STRATEGY_INSTANCE_STATE_CHANGE = 17,
	EVENT_TYPE_STRATEGY_EXTERNAL_FILL_NOTIFY = 18,
	EVENT_TYPE_EXTERNAL_ORDER = 19,
	EVENT_TYPE_ACCOUNT_FEES_CHANGE = 20,
    EVENT_TYPE_TOPIC_SUBSCRIPTION = 21,
    EVENT_TYPE_INTERNAL_SERVER_NOTIFY = 22,
    EVENT_TYPE_EVENT_CLOSURE = 23
};

enum ScheduledEventType {
    SCHEDULED_EVENT_TYPE_UNKNOWN = 0,
    SCHEDULED_EVENT_TYPE_SINGLE = 1,
    SCHEDULED_EVENT_TYPE_RECURRING = 2
};

class EventTypeUtils {
public:
    static const std::string& ToString(EventType type);
    static const std::string& ToString(ScheduledEventType type);
};

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif 
