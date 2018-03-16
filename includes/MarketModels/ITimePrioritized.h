/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/ITimePrioritized.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_ITIME_PRIORITIZED_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_ITIME_PRIORITIZED_H_

#include <Utilities/TimeType.h>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

using LimeBrokerage::StrategyStudio::Utilities::TimeType;
using LimeBrokerage::StrategyStudio::Utilities::TimeDuration;

struct TimePrioritizedGreaterPtrCmp;

/**
 * Abstract interface for implementing events that can be prioritzed by time 
 */ 
class ITimePrioritized {
public:
    static const int DEFAULT_PRIORITY = 5;

public:
    ITimePrioritized(int priority = DEFAULT_PRIORITY);
    ITimePrioritized(const ITimePrioritized& rhs);
    ~ITimePrioritized();

    TimeType NextFireTime() const                   { return m_nextFireTime; }
    void SetNextFireTime(TimeType fireTime)         { m_nextFireTime = fireTime; }

    TimeType LastFireTime() const                   { return m_lastFireTime; }

    bool IsRecurring() const                        { return m_bIsRecurring; }
    void SetIsRecurring(bool isRecurring)           { m_bIsRecurring = isRecurring; }
    
    int priority() const                            { return m_priority; }
    void set_priority(int flag)                     { m_priority = flag; }

    boost::uint64_t sequence() const                { return m_sequence; }
    void set_sequence(boost::uint64_t sequence)     { m_sequence = sequence; }

    /**
     * Add time duration to next fire time
     */ 
    void IncrNextFireTime(TimeDuration td);

    /**
     * Reset fire times 
     */
    void ResetFireTimes(); 

    /**
     * Triggers any logic related to firing 
     * Note: This should appropriately set the next fire time 
     * @returns true if further processing should occur, false otherwise 
     */ 
    virtual bool Trigger(TimeType currTime)=0;

    /**
     * Triggers any logic after the firing 
     * Note: Empty by default 
     */ 
    virtual void PostTrigger(TimeType) {}

    ITimePrioritized& operator=(const ITimePrioritized& rhs);

    bool operator<(const ITimePrioritized& rhs) const;

    friend struct TimePrioritizedGreaterPtrCmp;

protected:   
    int m_priority;
    TimeType m_nextFireTime;
    TimeType m_lastFireTime;
    boost::uint64_t m_sequence;
    bool m_bIsRecurring;
};

inline void ITimePrioritized::IncrNextFireTime(TimeDuration td)
{
    m_lastFireTime = m_nextFireTime;
    m_nextFireTime += td;
}

inline bool ITimePrioritized::operator<(const ITimePrioritized& rhs) const
{
    return (m_nextFireTime < rhs.m_nextFireTime);
}

struct TimePrioritizedGreaterPtrCmp
{
public:

    bool operator()(const ITimePrioritized* lhs, const ITimePrioritized* rhs) const 
    {
        if (lhs->m_nextFireTime == rhs->m_nextFireTime) {
            if (lhs->m_priority == rhs->m_priority) {
                return lhs->m_sequence > rhs->m_sequence;
            } else {
                return lhs->m_priority > rhs->m_priority;
            }
        } else {
            return lhs->m_nextFireTime > rhs->m_nextFireTime;
        }
    }
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
