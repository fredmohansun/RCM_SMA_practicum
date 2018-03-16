/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/CorporateActionEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_CORPORATE_ACTION_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_CORPORATE_ACTION_EVENT_MSG_H_

#include "DataTypes.h"
#include "EventMsg.h"

namespace LimeBrokerage {
namespace StrategyStudio {

class Event; 

/**
 * CorporateActionEventMsg delivers events such as dividends, splits, and spin-offs
 */ 
class CorporateActionEventMsg : public EventMsg {
public:

    /**
     * Default empty market data msg 
     */ 
    CorporateActionEventMsg(const MarketModels::CorporateAction& action, Event* ev);
    
    CorporateActionEventMsg(const CorporateActionEventMsg& msg);

    ~CorporateActionEventMsg();
  
    std::string name() const;

    const CorporateAction& corporate_action() const { return m_corpAction; }

    CorporateActionType type() const { return m_corpAction.corporate_action_type; }

    CorporateActionEventMsg& operator=(const CorporateActionEventMsg& msg);

private:

    MarketModels::CorporateAction m_corpAction;
};

inline std::string CorporateActionEventMsg::name() const
{
    return "Corporate_Event_Type_" + MarketModels::CorporateActionTypeUtils::ToString(m_corpAction.corporate_action_type);
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
