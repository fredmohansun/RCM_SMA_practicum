#ifndef _STRATEGY_STUDIO_PRACTICUM_SENTIMENT_EVENT_MSG_H_ 
#define _STRATEGY_STUDIO_PRACTICUM_SENTIMENT_EVENT_MSG_H_

#include<vector>
#include<string>
#include<sstream>

/**
 * PSentimentEventMsg is an event message,used in backtest, that gets triggered when a Sentiment event arrives
 */
class PSentimentEventMsg{
public:
    PSentimentEventMsg(std::string line){
    	std::stringstream split_helper(line);
	std::vector <std::string> split((std::istream_iterator<std::string>(split_helper)), std::istream_iterator<std::string>());
        for(std::vector <std::string>::iterator it = split.begin(); it != split.end(); it++){
            std::stringstream temp(*it);
            switch(it - split.begin()){
                case 0: break;
                case 1: break;
                case 2: break;
                case 3: temp>>raw_s_; break;
                case 4: temp>>raw_s_mean_; break;
                case 5: temp>>raw_s_volatility_; break;
                case 6: temp>>raw_s_score_; break;
                case 7: temp>>s_; break;
                case 8: temp>>s_mean_; break;
                case 9: temp>>s_volatility_; break;
                case 10: temp>>s_score_; break;
                case 11: temp>>s_volume_; break;
                case 12: temp>>s_vmean_; break;
                case 13: temp>>s_vvolatility_; break;
                case 14: temp>>s_vscore_; break;
                case 15: temp>>s_dispersion_; break;
                case 16: temp>>s_buzz_; break;
                case 17: temp>>s_delta_; break;
                case 18: break;
                case 19: break;
                case 20: break;
                default: break;
            }
        }
    }

    ~PSentimentEventMsg(){
    }

public:

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
#endif
