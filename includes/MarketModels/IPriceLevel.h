/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/IPriceLevel.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_IPRICE_LEVEL_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_IPRICE_LEVEL_H_

#include "DepthDataTypes.h"
#include "IBookEntry.h"
#include "IOrderEnumerator.h"

#pragma warning (push)
#pragma warning( disable: 4127 )

#include <boost/pool/pool_alloc.hpp>

#include <set>
#include <list>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

class IBookOrder;
class IOrderEnumerator;

/**
 * IPriceLevel is an interface to be implemented by market data order books for storing summaries about the orders present at a particular price level in 
 * a Depth-Of-Book market data source
 */
class IPriceLevel : public IBookEntry {
public:
    typedef std::set<MarketCenterID> ParticipatingMarkets; 
    typedef ParticipatingMarkets::iterator ParticipatingMarketsIter;
    typedef ParticipatingMarkets::const_iterator ParticipatingMarketsConstIter;

    typedef std::list<IBookOrder*, boost::fast_pool_allocator<IBookOrder*> > BookOrders;
    typedef BookOrders::iterator BookOrdersIter;
    typedef BookOrders::const_iterator BookOrdersConstIter;

public:
    IPriceLevel();
    virtual ~IPriceLevel();

public: /* Additions to public interface of IBookEntry */

    /**
     * Adds the amount to current value of size 
     */
    virtual void AccumSize(int size) = 0;

     /**
     * Adds the amount to current value of num orders
     */
    virtual void AccumNumOrders(int size) = 0;

    /**
     * Add a book order to this price level     
     */ 
    virtual bool AddBookOrder(IBookOrder* order) = 0;

    /**
     * Add a book order to this price level 
     * Second argument is an out iterator that is set to iterator location if order added 
     */ 
    virtual bool AddBookOrder(IBookOrder* order, BookOrdersIter* outIt) = 0;

    /**
     * Check if contains order id 
     */
    virtual bool ContainsOrderID(DepthOrderID orderID) const = 0;

    /**
     * Find the book order by order id 
     * @returns pointer to book order, NULL if not found 
     */ 
    virtual IBookOrder* FindByOrderID(DepthOrderID orderID) = 0;
    virtual const IBookOrder* FindByOrderID(DepthOrderID orderID) const = 0;

    /**
     * Get order enumerator for iterating through orders
     */
    virtual IOrderEnumeratorPtr GetOrderEnumerator() = 0;
    virtual IOrderConstEnumeratorPtr GetOrderEnumerator() const = 0;

    /**
     * Return the number of orders that make up this price level
     *
     * Note depth-by-price-level feeds may deliver an order count without actually delivering individual orders,
     * so this count will not always match the number of orders enumerable via GetOrderEnumerator()
     */
    virtual int num_orders() const = 0;


    /**
     * Remove by order id when we have an iterator as a hint 
     * @returns true if order was removed, false otherwise
     */ 
    virtual bool RemoveBookOrder(DepthOrderID orderID, BookOrdersIter it) = 0;

    /**
     * Retrieve set of participating markets 
     * Optionally can return NULL if participating markets not supported by given price level
     */ 
    virtual const ParticipatingMarkets* participating_markets() const = 0;

    /**
     * Price of level 
     */
    virtual double price() const = 0;

    /**
     * Size at level 
     */ 
    virtual int size() const = 0;
     
    /**
     * Update the size on an order 
     * @returns true if order size was updated, false otherwise 
     */ 
    virtual bool UpdateOrderSize(DepthOrderID orderID, int currSize) = 0;
};

inline bool operator<(const IPriceLevel& lhs, const IPriceLevel& rhs)
{
    return (lhs.price() < rhs.price());
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#pragma warning (pop)

#endif
