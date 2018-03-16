/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/Bond.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_BOND_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_BOND_H_ 

#include "Instrument.h"
#include "DerivativesTypes.h"
#include <string> 

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * Bond represents a bond instrument
 */
class Bond : public Instrument {
public:
    typedef std::vector<boost::gregorian::date> CouponDates;

public:
    Bond(InstrumentID instrID, 
          const SymbolTag& symbol, 
          MarketType marketType,
          const Markets::MarketCenterIDCollection& marketCenterIDs,
          IOrderBookBuilderPtr pOrderBookBuilder,
          MarketCenterInfoFactory* marketCenterInfoFactory);

    virtual ~Bond();

public:
    /**
     * principal is on the same scale as price, typically scaled to par
     */
    double principal() const                        { return m_principal; }
    
    boost::gregorian::date maturity() const         { return m_maturity; }
    
    /**
     * coupon_rate is the percentage of principal that the bond pays per year
     */
    double coupon_rate() const					    	{ return m_couponRate; }
    
    /**
     * coupon_frequency is the number of coupons per year
     */
    int coupon_frequency() const					{ return m_couponFrequency; }

    DayCountConvention day_count_convention() const { return m_dayCountConvention; }
    const CouponDates& coupon_dates() const         { return m_couponDates; }

    boost::gregorian::date call_date() const		{ return m_callDate; }
    double call_strike() const                      { return m_callStrike; }
    boost::gregorian::date put_date() const			{ return m_putDate; }
    double put_strike() const                       { return m_putStrike; }

    // Setters
    void set_principal(double principal)                { m_principal = principal; }
    void set_maturity(boost::gregorian::date maturity)  { m_maturity = maturity; }
    void set_coupon_rate(double couponRate)             { m_couponRate = couponRate; }
    void set_coupon_frequency(int cpnFrequency)         { m_couponFrequency = cpnFrequency; }
    void set_day_count_convention(DayCountConvention dcc) { m_dayCountConvention = dcc; }
    void set_coupon_dates(const CouponDates& couponDates) { m_couponDates = couponDates; }

    void set_call_date(boost::gregorian::date callDate) { m_callDate = callDate; }
    void set_call_strike(double callStrike)             { m_callStrike = callStrike; }
    void set_put_date(boost::gregorian::date putDate)   { m_putDate = putDate; }
    void set_put_strike(double putStrike)               { m_putStrike = putStrike; }


private:
    Bond(const Bond& bond);				// not implemented
    Bond& operator=(const Bond& bond);	// not implemented

protected:
    double m_principal;
    double m_couponRate;
    double m_callStrike;
    double m_putStrike;
    CouponDates m_couponDates;
    boost::gregorian::date m_maturity;
    boost::gregorian::date m_callDate;
    boost::gregorian::date m_putDate;
    DayCountConvention m_dayCountConvention;
    int m_couponFrequency;
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage 

#endif
