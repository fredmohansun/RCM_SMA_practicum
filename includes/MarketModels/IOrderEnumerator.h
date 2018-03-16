/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/IOrderEnumerator.h                               
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_IORDER_ENUMERATOR_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_IORDER_ENUMERATOR_H_

#include <memory>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

class IBookOrder;

/**
 * IOrderEnumerator is an enumerator interface for iterating through book orders 
 */
class IOrderEnumerator {
public:
    IOrderEnumerator();
    virtual ~IOrderEnumerator();

public: /* Public interface */

    /**
     * Returns the current book order 
     * @returns pointer to curr book order, NULL if at end 
     */
    virtual IBookOrder* Curr() = 0;

    /**
     * Returns the next book order 
     * @returns pointer to next book order, NULL if at end
     */
    virtual IBookOrder* Next() = 0;
};

typedef std::auto_ptr<IOrderEnumerator> IOrderEnumeratorPtr;

/**
 * IOrderEnumerator is an enumerator interface for iterating through book orders 
 */
class IOrderConstEnumerator {
public:
    IOrderConstEnumerator();
    virtual ~IOrderConstEnumerator();

public: /* Public interface */

    /**
     * Returns the current book order 
     * @returns pointer to curr book order, NULL if at end 
     */
    virtual const IBookOrder* Curr() = 0;

    /**
     * Returns the next book order 
     * @returns pointer to next book order, NULL if at end
     */
    virtual const IBookOrder* Next() = 0;
};

typedef std::auto_ptr<IOrderConstEnumerator> IOrderConstEnumeratorPtr;

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
