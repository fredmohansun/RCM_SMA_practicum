/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/NewsEventMsg.h                                                        
*     Last Update: 2011/09/12 13:55:14 	                                                                       
*     Contents:                                     
*     Distribution:          
*                                                                                                                
*                                                                                                                
*     Copyright (c) Lime Brokerage LLC, 2009 - 2011.                                                    
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

#ifndef _STRATEGY_STUDIO_LIB_NEWS_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_NEWS_EVENT_MSG_H_

#include "EventMsg.h"

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * NewsEventMsg is an event message that gets triggered when a News event arrives
 */
class NewsEventMsg : public EventMsg {
public:
    NewsEventMsg(Event* ev,
                 Utilities::TimeType eventTime);

    virtual ~NewsEventMsg();

public:

    /**
     * Check the validity of each of the three possible measurements values
     */
    bool is_min_valid() const		{ return m_frStatus.status.m_minValid; }
    bool is_mid_valid() const		{ return m_frStatus.status.m_midValid; }
    bool is_max_valid() const		{ return m_frStatus.status.m_maxValid; }

    /**
     * Determine how to interpret the three numeric measurement values
     */
    bool is_min_exclusive() const	{ return m_frStatus.status.m_minExclusive; }
    bool is_max_exclusive() const	{ return m_frStatus.status.m_maxExclusive; }
    bool is_approximate() const		{ return m_frStatus.status.m_approximate; }

    // set the status byte for the observation, which describes its validity
    // and whether the measurement value was verified and/or derived
    void set_status(boost::uint8_t byte)			{ m_obsStatus.byte = byte; }

    // set the flex-range status byte, including which values are valid
    // and the characteristics of the values
    void set_flex_range_status(boost::uint8_t byte)	{ m_frStatus.byte = byte; }

    /**
     * Returns a string describing the data type of the measurement values
     * (e.g., decimal, boolean, flex_range, etc.)
     */
    const std::string& measurement_type() const		{ return m_measurementType; }
    void set_measurement_type(const std::string& type)	{ m_measurementType = type; }

    /**
     * Returns the entity for this News Event as represented in the news feed
     */
    const std::string& entity() const				{ return m_entity; }
    void set_entity(const std::string& entity)		{ m_entity = entity; }

    /**
     * Returns the metric this event is reporting, e.g., FIN.EPS, FIN.REV, etc.
     */
    const std::string& measure() const				{ return m_measure; }
    void set_measure(const std::string& measure)	{ m_measure = measure; }

    /**
     * Describes the period for the measurement
     */
    const std::string& period() const				{ return m_period; }
    void set_period(const std::string& period)		{ m_period = period; }

    /**
     * Returns the lower-bound measurement value; only valid if is_min_valid() == true
     */
    double lower_bound() const						{ return m_lowerBound; }
    void set_lower_bound(double lowerBound)			{ m_frStatus.status.m_minValid = true; m_lowerBound = lowerBound; }

    /**
     * Returns the mid measurement value; only valid if is_mid_valid() == true
     */
    double mid() const								{ return m_mid; }
    void set_mid(double mid)						{ m_frStatus.status.m_midValid = true; m_mid = mid; }

    /**
     * Returns the upper-bound measurement value; only valid if is_max_valid() == true
     */
    double upper_bound() const						{ return m_upperBound; }
    void set_upper_bound(double upperBound)			{ m_frStatus.status.m_maxValid = true; m_upperBound = upperBound; }

public:

    /**
     * Checks several characteristics of the message to determine whether it is complete and valid
     */
    bool IsValid() const;

private:

    struct ObservationStatus {
        bool m_observed : 1;
        bool m_valid : 1;
        bool m_verified : 1;
        bool m_derived : 1;
        boost::uint8_t m_bits0to3 : 4;
    };

    struct FlexRangeStatus {
        bool m_minValid : 1;
        bool m_midValid : 1;
        bool m_maxValid : 1;
        boost::uint8_t m_bit4 : 1;
        bool m_minExclusive : 1;
        bool m_approximate : 1;
        bool m_maxExclusive : 1;
        boost::uint8_t m_bit0 : 1;
    };

    union FRStatusUnion	{
        FlexRangeStatus status;
        boost::uint8_t byte;
    } m_frStatus;

    union ObservationStatusUnion {
        ObservationStatus status;
        boost::uint8_t byte;
    } m_obsStatus;

    std::string m_measurementType;
    std::string m_entity;
    std::string m_measure;
    std::string m_period;
    double m_lowerBound;
    double m_mid;
    double m_upperBound;
};

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
