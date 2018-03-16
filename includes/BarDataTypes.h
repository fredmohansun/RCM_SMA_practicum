/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/BarDataTypes.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_BAR_DATA_TYPES_H_
#define _STRATEGY_STUDIO_LIB_BAR_DATA_TYPES_H_

#include <Utilities/StdTypes.h>
#include <Utilities/TimeType.h>
#include <MarketModels/MarketCenterHours.h>
#include <string> 
#include <iostream>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * Lists the types of bar intervals supported by Strategy Studio
 */
enum BarType {
    BAR_TYPE_UNKNOWN = 0,

	/**
	 * Time bars, with intervals specified in seconds (with fractional seconds up to the millisecond supported)
	 */
    BAR_TYPE_TIME = 1,

    BAR_TYPE_DAILY = 2,

	/**
	 * Bars based off the number of trade ticks
	 */
    BAR_TYPE_TICK_COUNT = 3,

	/**
	 * Bars based off the number of contracts/shares traded
	 */
    BAR_TYPE_VOLUME = 4,
 
	/**
	 * Realized variance bars trigger based off the tick-by-tick variance of
	 * mid-price log returns, sampled every trade tick. In absence of quote data,
	 * we substitute last trade price for mid-price.
	 */
	BAR_TYPE_VARIANCE = 5,

	/**
	 * Bars based off price range
	 */
    BAR_TYPE_RANGE = 6
};

/**
 * BarDefinition contains configuration settings for market data bars
 */
struct BarDefinition {
    // Millisecond granularity for bar intervals
    static const int BAR_INTERVAL_PRECISION = 3;

	BarDefinition() : type(BAR_TYPE_UNKNOWN),interval(0.0),p_value(2.0),alignment_time(){}

	BarDefinition(BarType type, double interval, double p_value = 2.0) : type(type),interval(interval),p_value(p_value),alignment_time(){}

	BarDefinition(BarType type, double interval, boost::posix_time::ptime alignment_time) : type(type),interval(interval),p_value(2.0),alignment_time(alignment_time){}

	/**
	 * Type of interval the bar is calculated over
	 */
	BarType type;

	/**
	 * Size of the bar's interval
	 */
	double interval;

	/**
	 * Relevant only for BAR_TYPE_VARIANCE
	 *
	 * The realized variance formula is Sum(|logReturn|^p_value).
	 * p defaults to 2, corresponding to a normal Euclidean variance, and should be p>=1 in order to 
	 * define a p-norm when exponentiating by 1/p.
	 */ 
	double p_value;

	/**
	 * Relevant only for BAR_TYPE_TIME
	 *
	 * The time of day in UTC to which time bars will align.
	 */ 
	boost::posix_time::ptime alignment_time;

	std::string ToString() const;
};


inline std::string BarTypeToString(BarType barType)
{
    switch (barType) {
        case BAR_TYPE_TIME:
            return "BAR_TYPE_TIME";
        case BAR_TYPE_DAILY:
            return "BAR_TYPE_DAILY";
        case BAR_TYPE_TICK_COUNT:
            return "BAR_TYPE_TICK_COUNT";
        case BAR_TYPE_VOLUME:
            return "BAR_TYPE_VOLUME";
        case BAR_TYPE_VARIANCE:
            return "BAR_TYPE_VARIANCE";
        case BAR_TYPE_UNKNOWN: // fall-through
        default: 
            return "BAR_TYPE_UNKNOWN";
    }
}

inline std::string BarTypeToShortString(BarType barType)
{
    switch (barType) {
        case BAR_TYPE_TIME:
            return "INTERVAL";
        case BAR_TYPE_DAILY:
            return "DAILY";
        case BAR_TYPE_TICK_COUNT:
            return "COUNT";
        case BAR_TYPE_VOLUME:
            return "VOLUME";
        case BAR_TYPE_VARIANCE:
            return "VARIANCE";
        case BAR_TYPE_UNKNOWN: // fall-through
        default: 
            return "UNKNOWN";
    }
}

class BarBaseComponent;
class BarVolumeComponent;
class BarRVarComponent;

/**
 * Contains summary of market activity of a user defined interval.
 */
class Bar {
public:
	friend class BarBaseComponent;
	friend class BarVolumeComponent;
	friend class BarRVarComponent;
    friend class BarTimeIntervalComponent;

    Bar();

    Bar(double open, double close, double high, double low, double curr);

    Bar(const Bar& bar);

	/**
	 * Returns the price of the first trade tick within the Bar
	 *
	 * Note: for volume and variance bars that have a remainder quantity, open
	 * will be the same as the close of the last bar.
	 */
    double open() const         { return m_fOpen; }


	/**
	 * Returns the highest price of all trade ticks within the Bar
	 */
    double high() const         { return m_fHigh; }

	/**
	 * Returns the lowest price of all trade ticks within the Bar
	 */
    double low() const          { return m_fLow; }

	/**
	 * Returns the price of the last trade tick within the Bar
	 */
    double close() const        { return m_fClose; }

	/**
	 * Returns the volume traded within the Bar
	 *
	 * Note: for a Volume based bar, the remainder gets applied to the next bar,
	 * so this number will return interval*multiplier.
	 */
	int volume() const          { return m_nVolume; }

	/**
	 * This accessor is used for volume and variance bars, where a large
	 * trade or a price gap can jump past the bar interval definition. In these cases
	 * Strategy Studio will generate a single bar event, and this field describes the multiple 
	 * of the bar interval represented by the bar event.
	 * 
	 * @return multiple of the bar interval represented by the current bar
	 */
    int multiplier() const		{ return m_nMult; }

	/**
	 * This accessor is used for volume and variance bars, where a large
	 * trade or a price gap can jump past the bar interval definition. In these cases
	 * Strategy Studio will generate a single bar event, and this field describes the amount of
	 * volume or variance left over, beyond multiplier*interval. 
	 *
	 * This remainder WILL count towards the triggering of the next bar. For volume bars, the remainder is also very 
	 * likely to 'carry forward' to the next bar if the bar interval is a small multiple of round lot size.
	 * 
	 * @return remainder of the bar interval left over after the triggering of the current bar
	 */
    double remainder() const    { return m_fRemainder; }

	/**
	 * Only set if the bar type is realized variance
	 *
	 * Returns the realized variance contained within the bar, which will always be
	 * the interval*multiplier
	 */
	double realized_variance() const  { return m_fRVar; }

    void set_open(double val)      { m_fOpen = val; }
	void set_high(double val)      { m_fHigh = val; }
	void set_low(double val)       { m_fLow = val; }
    void set_close(double val)     { m_fClose = val; }
	void set_volume(int val)       { m_nVolume = val; }

    void set_multiplier(int val)         { m_nMult = val; }
    void set_remainder(double val) { m_fRemainder = val; }
	void set_realized_variance(double val) { m_fRVar = val; }

    /**
     * Resets all values of the bar 
     */ 
    void Clear(); 

    /**
     * Check if the bar is valid 
     */
    bool IsValid() const; 

    /**
     * Reset all values on bar 
     */ 
    void Reset();

    /**
     * Resets the open price of the bar to val
     * and clears out other fields 
     */ 
    void ResetOpen(double val);     

    Bar& operator=(const Bar& bar);

    friend std::ostream& operator<<(std::ostream& out, const Bar& bar);

private:
    double current() const			{ return m_fCurr; }
    void set_current(double val)    { m_fCurr = val; }
    void AccumVolume(int val)		{ m_nVolume += val; }

    double m_fOpen;
    double m_fClose;
    double m_fHigh;
    double m_fLow;
    double m_fCurr;
    int m_nMult;
    double m_fRemainder;
    double m_fRVar;
    int m_nVolume; 
};

inline std::ostream& operator<<(std::ostream& out, const Bar& bar)
{
    out << " Open: " << bar.m_fOpen
        << " Close: " << bar.m_fClose
        << " High: " << bar.m_fHigh
        << " Low: " << bar.m_fLow
        << " Curr: " << bar.m_fCurr
        << " Vol: " << bar.m_nVolume
        << " Mult: " << bar.m_nMult
        << " Rnd: " << bar.m_fRemainder
        << " RVol: " << bar.m_fRVar;

    return out;
}

inline Utilities::TimeType NextAlignedTimeSecs(Utilities::TimeType currTime, 
                                           double alignSeconds, 
                                           Utilities::TimeType openTime)
{
    // the minimum granularity we want to align to is per second 
    int alignTime = ((alignSeconds < 1) ? 1 : static_cast<int>(alignSeconds));
        
    boost::posix_time::time_duration td = currTime - openTime;
    long secDiff = td.total_seconds();    
    int remainder = std::abs(secDiff) % alignTime;
    long adjSeconds = (secDiff < 0) ? ((!remainder) ? alignTime : remainder) : 
        (alignTime - remainder);      
    boost::posix_time::time_duration adjTD = boost::posix_time::seconds(adjSeconds);
    return currTime + adjTD;
}

inline Utilities::TimeType NextAlignedTimeMilliSecs(Utilities::TimeType currTime, 
                                                    int alignMilliSeconds, 
                                                    Utilities::TimeType openTime)
{        
    boost::posix_time::time_duration td = currTime - openTime;
    StrategyStudioInt64 msecDiff = td.total_milliseconds();    
    StrategyStudioInt64 remainder = std::abs(msecDiff) % alignMilliSeconds;
    StrategyStudioInt64 adjMilliSeconds = (msecDiff < 0) ? ((!remainder) ? alignMilliSeconds : remainder) : 
        (alignMilliSeconds - remainder);      
    boost::posix_time::time_duration adjTD = boost::posix_time::milliseconds(adjMilliSeconds);
    return currTime + adjTD;
}

inline Utilities::TimeType NextAlignedTimeUTCSecs(Utilities::TimeType currTime, 
                                              double alignSeconds, 
                                              Utilities::TimeType openTime = MarketModels::USEquityOpenUTCTime())
{
    return NextAlignedTimeSecs(currTime, alignSeconds, openTime);
}  
    
inline Utilities::TimeType NextAlignedTimeCentralSecs(Utilities::TimeType currTime, 
                                                  double alignSeconds, 
                                                  Utilities::TimeType openTime = MarketModels::USEquityOpenCentralTime())
{
    return NextAlignedTimeSecs(currTime, alignSeconds, openTime);
}

inline Utilities::TimeType NextAlignedTimeUTCMilliSecs(Utilities::TimeType currTime, 
                                              int alignMilliSecs, 
                                              Utilities::TimeType openTime = MarketModels::USEquityOpenUTCTime())
{
    return NextAlignedTimeMilliSecs(currTime, alignMilliSecs, openTime);
}  
    
inline Utilities::TimeType NextAlignedTimeCentralMilliSecs(Utilities::TimeType currTime, 
                                                  int alignMilliSecs, 
                                                  Utilities::TimeType openTime = MarketModels::USEquityOpenCentralTime())
{
    return NextAlignedTimeMilliSecs(currTime, alignMilliSecs, openTime);
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
