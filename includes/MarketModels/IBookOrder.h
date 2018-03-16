/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/IBookOrder.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_IBOOK_ORDER_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_IBOOK_ORDER_H_

#include "DepthDataTypes.h"
#include "IBookEntry.h"

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

enum BookOrderType {
    BOOK_ORDER_TYPE_UNKNOWN = 0,
    BOOK_ORDER_TYPE_SINGLE = 1,
    BOOK_ORDER_TYPE_AGGR = 2
};

/**
 * IBookOrder is an interface to be implemented by market data order books for storing information about an individual Order in a Depth-Of-Book market data source
 */
class IBookOrder : public IBookEntry {
public:
    IBookOrder();
    virtual ~IBookOrder();  

public: /* Extensions to interface of IBookOrder */

    /**
     * Retrieve boook order id 
     */ 
    virtual DepthOrderID order_id() const = 0;

    /**
     * Get the book order type 
     */
    virtual BookOrderType order_type() const = 0;

    /**
     * Get side of the order 
     */ 
    virtual DepthSide side() const = 0;

};

inline bool operator<(const IBookOrder& lhs, const IBookOrder& rhs)
{
    return (lhs.price() < rhs.price());
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
