/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/IPriceLevelEnumerator.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_IPRICE_LEVEL_ENUMERATOR_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_IPRICE_LEVEL_ENUMERATOR_H_

#include <boost/shared_ptr.hpp>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

class IPriceLevel;

/**
 * IPriceLevelEnumerator is an enumerator interface for iterating through price levels within a book
 */
class IPriceLevelEnumerator {
public:
    IPriceLevelEnumerator();
    virtual ~IPriceLevelEnumerator();

public: /* Public interface */

    /**
     * Returns the curr price level
     * @returns pointer to curr price level, NULL if at end
     */
    virtual IPriceLevel* Curr() = 0; 

    /**
     * Returns the next price level
     * @returns pointer to next price level, NULL if at end
     */
    virtual IPriceLevel* Next() = 0;
};

typedef boost::shared_ptr<IPriceLevelEnumerator> IPriceLevelEnumeratorPtr;

/**
 * IPriceLevelEnumerator is an enumerator interface for iterating through book orders 
 */
class IPriceLevelConstEnumerator {
public:
    IPriceLevelConstEnumerator();
    virtual ~IPriceLevelConstEnumerator();

public: /* Public interface */

    /**
     * Returns the curr price level
     * @returns pointer to curr price level, NULL if at end
     */
    virtual const IPriceLevel* Curr() = 0; 

    /**
     * Returns the next price level
     * @returns pointer to next price level, NULL if at end
     */
    virtual const IPriceLevel* Next() = 0;
};

typedef boost::shared_ptr<IPriceLevelConstEnumerator> IPriceLevelConstEnumeratorPtr;

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
