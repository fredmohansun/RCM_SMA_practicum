/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/SentimentEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_SENTIMENT_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_SENTIMENT_EVENT_MSG_H_

#include "EventMsg.h"

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * SentimentEventMsg is an event message that gets triggered when a Sentiment event arrives
 */
class SentimentEventMsg : public EventMsg {
public:
    SentimentEventMsg(Event* ev, Utilities::TimeType eventTime);
    virtual ~SentimentEventMsg();

public:
    /**
     * Gets and sets the stock's symbol
     * @return returns the stock's symbol
     */
    const std::string& entity() const { return entity_; }
    void set_entity(const std::string& entity) { entity_ = entity; }

    /**
     * Raw-S - Unweighted sentiment estimate provided by SMA
     * @return returns the Raw-S value from SMA
     */
    double raw_s() const { return raw_s_; }
    void set_raw_s(double raw_s) { raw_s_ = raw_s; }

    /**
     * Raw S-Mean - 20 day moving average of Raw-S
     * @return returns the Raw S-Mean
     */
    double raw_s_mean() const { return raw_s_mean_; }
    void set_raw_s_mean(double raw_s_mean) { raw_s_mean_ = raw_s_mean; }

    /**
     * Raw S-Score - Normalized value of Raw-S
     * @return returns the Raw S-Score
     */
    double raw_s_score() const { return raw_s_score_; }
    void set_raw_s_score(double raw_s_score) { raw_s_score_ = raw_s_score; }

    /**
     * Raw S-Volatility - 20 day moving average of Raw-S
     * @return returns the Raw S-Volatility
     */
    double raw_s_volatility() const { return raw_s_volatility_; }
    void set_raw_s_volatility(double raw_s_volatility) { raw_s_volatility_ = raw_s_volatility; }

    /**
     * S - Exponentially weighted sentiment estimate provided by SMA
     * @return returns the S 
     */
    double s() const { return s_; }
    void set_s(double s) { s_ = s; }

    /**
     * S-Buzz - Measurement of unusual volume activity provided by SMA
     * @return returns the S-Buzz
     */
    double s_buzz() const { return s_buzz_; }
    void set_s_buzz(double s_buzz) { s_buzz_ = s_buzz; }

    /**
     * S-Delta - Change in S-Score over a look-back period
     * @return returns the S-Delta
     */
    double s_delta() const { return s_delta_; }
    void set_s_delta(double s_delta) { s_delta_ = s_delta; }

    /**
     * S-Dispersion - Measurement of the tweet source concentration contributing to an S-Score
     * @return returns the S-Dispersion
     */
    double s_dispersion() const { return s_dispersion_; }
    void set_s_dispersion(double s_dispersion) { s_dispersion_ = s_dispersion; }

    /**
     * S-Mean - 20 day moving average of the exponentially weighted sentiment estimate
     * @return returns the S-Mean
     */
    double s_mean() const { return s_mean_; }
    void set_s_mean(double s_mean) { s_mean_ = s_mean; }

    /**
     * S-Score - Normalized value of the exponentially weighted sentiment estimate (SMA's S-Score)
     * @return returns the S-Score
     */
    double s_score() const {  return s_score_; }
    void set_s_score(double s_score) { s_score_ = s_score; }

    /**
     * SV-Mean - 20 day moving average of volume
     * @return returns the SV-Mean
     */
    double s_vmean() const { return s_vmean_; }
    void set_s_vmean(double sv_mean) { s_vmean_ = sv_mean; }

    /**
     * S-Volatility -  20 day moving standard deviation of the exponentially weighted sentiment estimate
     * @return returns the S-Volatility
     */
    double s_volatility() const { return s_volatility_; }
    void set_s_volatility(double s_volatility) { s_volatility_ = s_volatility; }

    /**
     * S-Volume - Indicative tweet volume used to compute the sentiment estimate
     * @return returns the S-Volume
     */
    int s_volume() const { return s_volume_; }
    void set_s_volume(int s_volume) { s_volume_ = s_volume; }

    /**
     * S-VScore - Normalized value of volume
     * @return returns the S-VScore
     */
    double s_vscore() const { return s_vscore_; }
    void set_s_vscore(double s_vscore) { s_vscore_ = s_vscore; }

    /**
     * S-VVolatility - 20 day moving standard deviation of volume
     * @return returns the S-VVolatility
     */
    double s_vvolatility() const { return s_vvolatility_; }
    void set_s_vvolatility(double s_vvolatility) { s_vvolatility_ = s_vvolatility; }

private:
    Utilities::DateType datetime_;
    std::string entity_;

    double raw_s_;
    double raw_s_mean_;
    double raw_s_score_;
    double raw_s_volatility_;
    double s_;
    double s_buzz_;
    double s_delta_;
    double s_dispersion_;
    double s_mean_;
    double s_score_;
    double s_volatility_;
    double s_vmean_;
    double s_vscore_;
    double s_vvolatility_;
    int s_volume_;
};

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif