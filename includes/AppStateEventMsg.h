/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/AppStateEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_APP_STATE_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_APP_STATE_EVENT_MSG_H_

#include "EventMsg.h"
#include "AppState.h"
#include "Event.h"

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * AppStateEventMsg is an event message containing information about the state of the Strategy Server process.
 */ 
class AppStateEventMsg: public EventMsg {
public:

    AppStateEventMsg(AppState state, Event* ev);

    AppStateEventMsg(const AppStateEventMsg& msg);
    
    ~AppStateEventMsg();

    std::string name() const;

    AppState State() const { return m_appState; }

    AppStateEventMsg& operator=(const AppStateEventMsg& msg);

private:
    AppState m_appState;
};

inline std::string AppStateEventMsg::name() const
{
    return "AppStateEvent_" + AppStateUtils::ToString(m_appState);
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
