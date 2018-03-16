/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/BacktesterEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_BACKTESTER_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_BACKTESTER_EVENT_MSG_H_

#include "EventMsg.h"
#include "Event.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace LimeBrokerage {
namespace StrategyStudio {

enum BacktesterState {
    BACKTESTER_START = 0, 
    BACKTESTER_DAY_START = 1,
    BACKTESTER_DAY_STOP = 2,
    BACKTESTER_STOP = 3
};

inline std::string ToString(BacktesterState state)
{
    switch (state) {
        case BACKTESTER_START:
            return "BACKTESTER_START";
        case BACKTESTER_DAY_START:
            return "BACKTESTER_DAY_START";
        case BACKTESTER_DAY_STOP:
            return "BACKTESTER_DAY_STOP";
        case BACKTESTER_STOP: // fall-through
        default:
            return "BACKTESTER_STOP";
    }
}

class BacktesterEventMsg : public EventMsg {
public:

    BacktesterEventMsg(BacktesterState state, 
                       boost::gregorian::date currDate, 
                       Event* ev);
    
    BacktesterEventMsg(const BacktesterEventMsg& msg);

    ~BacktesterEventMsg();
    
    std::string name() const;

    BacktesterState state() const	{ return m_backtesterState; }
    
    boost::gregorian::date start_date() const			{ return m_startDate; }

    BacktesterEventMsg& operator=(const BacktesterEventMsg& msg);

private:
    BacktesterState m_backtesterState;
    boost::gregorian::date m_startDate; 
};

inline std::string BacktesterEventMsg::name() const
{
    return "BacktesterEvent_State_" + ToString(m_backtesterState) + "_StartDate_" + to_simple_string(m_startDate);
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
