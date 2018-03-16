/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/ExternalFillEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_EXTERNAL_FILL_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_EXTERNAL_FILL_EVENT_MSG_H_

#include "EventMsg.h"
#include "Event.h"
#include "FillInfo.h"
#include "TimePrioritizedEventMsg.h"
#include <Utilities/IParams.h>

namespace LimeBrokerage {
namespace StrategyStudio {

class IInstrumentFactory;

/**
 * ExternalFillEventMsg delivers notifications of fills made outside of the Strategy Studio platform that 
 * are being reported for attribution to a Strategy Studio strategy.
 */ 
class ExternalFillEventMsg : public TimePrioritizedEventMsg {
public:
    static const int TIMED_EVENT_PRIORITY = 4;

public:

    ExternalFillEventMsg(const std::string& symbol,
                         const FillInfo& fillInfo,
                         Event* ev,
                         bool applyFees = true,
                         int expectedLegCount = 1,
                         const std::string& legId = "");

    ExternalFillEventMsg(const ExternalFillEventMsg& msg);

    ~ExternalFillEventMsg();

    std::string name() const;

    const std::string& symbol() const { return m_symbol; }

    const FillInfo& fill() const { return m_fillInfo; }

    /**
     * the leg count on a best effort basis
     * complex orders will be 0 if unknown
     * all other orders default to 1
     */
    int expected_leg_count() const { return m_expectedLegCount; }

    const std::string& leg_id() const { return m_legId; }

    bool apply_fees() const { return m_applyFees; }

    ExternalFillEventMsg& operator=(const ExternalFillEventMsg& msg);

public: //from TimePrioritizedEventMsg

    bool Trigger(TimeType currTime);

private:
    std::string m_symbol;
    FillInfo m_fillInfo;
    int m_expectedLegCount;
    std::string m_legId;
    bool m_applyFees;
};

inline std::string ExternalFillEventMsg::name() const
{
    return "ExternalFillEventMsg";
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
