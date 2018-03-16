/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/IAggrOrderBook.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_I_AGGR_MDORDERBOOK_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_I_AGGR_MDORDERBOOK_H_

#include "IOrderBook.h"
#include "IOrderBookListener.h"

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * IAggrOrderBook is an interface representing an order book aggregated from the Depth-Of-Book feeds of multiple market centers
 */
class IAggrOrderBook : public IOrderBook, public IOrderBookListener {
public:
    IAggrOrderBook();
    virtual ~IAggrOrderBook();

public: /* Additions to IOrderBook interface */
    
    /**
     * Returns true if quote's price and size for each side equal the Aggregate's best
     */ 
    virtual bool EqualsBest(double bidPrice, int bidSize, double askPrice, int askSize) const = 0;

    /**
     * Return the amount of number of market centers participating at bid at a given price level 
     */ 
    virtual int NumBidMarketCentersAtPrice(double price) const = 0;

    /**
     * Return the amount of number of market centers participating at ask at a given price level 
     */ 
    virtual int NumAskMarketCentersAtPrice(double price) const = 0;

    /**
     * Return the amount of number of market centers participating at bid at a given price level 
     * Level is zero-indexed (first level starts at zero)
     */ 
    virtual int NumBidMarketCentersAtLevel(unsigned level) const = 0;

    /**
     * Return the amount of number of market centers participating at ask at a given price level 
     * Level is zero-indexed (first level starts at zero)
     */ 
    virtual int NumAskMarketCentersAtLevel(unsigned level) const = 0;      
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
