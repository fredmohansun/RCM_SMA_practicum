/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/CurrencyPair.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_FX_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_FX_H_ 

#include "Instrument.h"
#include <string> 

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * Represent forex currency pair 
 */ 
class CurrencyPair : public Instrument {
public:

    CurrencyPair(InstrumentID instrID, 
           const SymbolTag& symbol, 
           CurrencyType ccy1, 
           MarketType marketType,
           const Markets::MarketCenterIDCollection& marketCenterIDs,
           IOrderBookBuilderPtr pOrderBookBuilder,
           MarketCenterInfoFactory* marketCenterInfoFactory);

    virtual ~CurrencyPair();

    /**
     * Retrieves the ccy1 (base currency)
     */ 
    CurrencyType ccy1() const  { return m_ccy1; } 
    void set_ccy1(CurrencyType currency)   { m_ccy1 = currency; }
    
    /**
     * Retrieves the ccy2 (quote currency)
     */ 
    CurrencyType ccy2() const { return currency(); } 

    virtual CurrencyType base_currency() const          { return m_ccy1; }
    const ConversionRate* base_conversion_rate() const { return m_baseConversionRate; }
    void set_base_conversion_rate(const ConversionRate* conversionRate) { m_baseConversionRate = conversionRate; }

protected:
    // this is duplicated with the value in 'm_baseConversionRate' to allow
    // 'm_baseConversionRate' to be null when it is the same as the home currency
    CurrencyType m_ccy1;
	const ConversionRate* m_baseConversionRate;    // to convert from ccy1 to home currency
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage 

#endif
