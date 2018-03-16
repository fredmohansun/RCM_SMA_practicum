/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/IOrderBook.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_IORDERBOOK_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_IORDERBOOK_H_

#include "IBookOrder.h"
#include "IPriceLevelEnumerator.h"
#include "DepthUpdate.h"
#include "Utilities/utils.h"

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

class IOrderBookListener;
class IPriceLevel;

/**
 * IOrderBook is an interface to be implemented by market data order books 
 */
class IOrderBook {
public:
    IOrderBook();
    virtual ~IOrderBook();

    static const Utilities::PriceToIntKeyFunc<7> PriceHashFunc;      // hasher for price comparisons

public:

    /**
     * Add a buy order to the order book
     * @returns true if order was added, false otherwise 
     */ 
    virtual bool AddBuyOrder(IBookOrder* update) = 0;

    /**
     * Add a sell order to the order book
     * @returns true if order was added, false otherwise 
     */ 
    virtual bool AddSellOrder(IBookOrder* update) = 0;

    /**
     * Retrieve the best bid entry 
     * @returns order book entry pointer, or null if not found 
     */ 
    virtual IPriceLevel* BestBidEntry() = 0;
    virtual const IPriceLevel* BestBidEntry() const = 0;

    /**
     * Retrieve the best ask entry 
     * @returns order book entry pointer, or null if not found 
     */ 
    virtual IPriceLevel* BestAskEntry() = 0;  
    virtual const IPriceLevel* BestAskEntry() const = 0;

    /**
     * Get bid price level at a given level 
     * @returns NULL if price level doesn't exist 
     */ 
    virtual const IPriceLevel* BidPriceLevelAtLevel(int level) const = 0;

    /**
     * Get ask price level at a given level 
     * @returns NULL if price level doesn't exist 
     */ 
    virtual const IPriceLevel* AskPriceLevelAtLevel(int level) const = 0;

    /**
     * Get total bid liquidity in shares/contracts accross all bid levels of the book
     */ 
    virtual int TotalBidSize() const = 0;

    /**
     * Get total ask liquidity in shares/contracts accross all asl levels of the book
     */ 
    virtual int TotalAskSize() const = 0;

    /**
     * Return the amount of bid liquidity at a given price 
     */ 
    virtual int BidSizeAtPrice(double price) const = 0;

    /**
     * Return the amount of ask liquidity at a given price 
     */ 
    virtual int AskSizeAtPrice(double price) const = 0;

    /**
     * Return the amount of bid liquidity at a given price level
     * Level is zero-indexed (first level starts at zero)
     */ 
    virtual int BidSizeAtLevel(int level) const = 0;

    /**
     * Return the amount of ask liquidity at a given price level
     * Level is zero-indexed (first level starts at zero)
     */ 
    virtual int AskSizeAtLevel(int level) const = 0;

    /**
     * Check if order book contains the order id
     * @returns true if order book has given order id, false otherwise 
     */
    virtual bool ContainsOrderID(DepthOrderID orderID) const = 0;

    /**
     * Check if the given buy price level exists 
     */
    virtual bool CheckBuyPriceLevelExists(double price) const = 0;

    /**
     * Check if the given sell price level exists 
     */
    virtual bool CheckSellPriceLevelExists(double price) const = 0;

    /**
     * Find order by order ID
     * @returns pointer to order id if order present, NULL if not present 
     */
    virtual IBookOrder* FindOrderByID(DepthOrderID orderID) = 0;
    virtual const IBookOrder* FindOrderByID(DepthOrderID orderID) const = 0;

    /**
     * Get buy price level enumerator 
     */ 
    virtual IPriceLevelEnumeratorPtr GetBuyPriceLevelEnumerator() = 0;

    /**
     * Get buy price level const enumerator 
     */ 
    virtual IPriceLevelConstEnumeratorPtr GetBuyPriceLevelEnumerator() const = 0;

    /**
     * Get sell price level enumerator 
     */ 
    virtual IPriceLevelEnumeratorPtr GetSellPriceLevelEnumerator() = 0;

    /**
     * Get sell price level const enumerator 
     */ 
    virtual IPriceLevelConstEnumeratorPtr GetSellPriceLevelEnumerator() const = 0;

    /**
     * Retrieve the market center for the order book 
     */ 
    virtual MarketCenterID market_center() const = 0; 

    /**
     * Returns whether the order book is currently in an initialization state
     */
    virtual bool is_initializing() const = 0;

    /**
     * Sets whether the order book is currently in an initialization state
     */
    virtual void set_is_initializing(bool isInitializing) = 0;

    virtual void set_withdrawn_due_to_cross(bool withdraw) = 0;

    /**
     * Get number of bid levels 
     */
    virtual int NumBidLevels() const = 0;

    /**
     * Get number of ask levels 
     */
    virtual int NumAskLevels() const = 0;

    /**
     * Get number of bid orders 
     */ 
    virtual int NumBidOrders() const = 0;

    /**
     * Get number of ask orders 
     */ 
    virtual int NumAskOrders() const = 0;

    /**
     * Get number of total orders 
     */ 
    virtual int NumTotalOrders() const = 0;

    /**
     * Return the amount of number of bid orders at a given price 
     */ 
    virtual int NumBidOrdersAtPrice(double price) const = 0;

    /**
     * Return the amount of number of ask orders at a given price 
     */ 
    virtual int NumAskOrdersAtPrice(double price) const = 0;

    /**
     * Return the amount of number of bid orders at a given price level 
     * Level is zero-indexed (first level starts at zero)
     */ 
    virtual int NumBidOrdersAtLevel(int level) const = 0;

    /**
     * Return the amount of number of ask orders at a given price level
     * Level is zero-indexed (first level starts at zero)
     */ 
    virtual int NumAskOrdersAtLevel(int level) const = 0;    
    
    /**
     * Process modification of order book by depth update 
     */ 
    virtual bool ProcessDepthUpdate(const DepthUpdate& update) = 0; 

    /**
     * Reset the contents of the order book 
     */ 
    virtual void Reset() = 0;

    /**
     * Remove a buy entry from the order book
     * @returns true if entry was removed, false if price not present 
     */ 
    virtual bool RemoveBuyEntry(double price) = 0;

    /**
     * Remove a sell entry from the order book
     * @returns true if entry was removed, false if price not present 
     */ 
    virtual bool RemoveSellEntry(double price) = 0;

    /**
     * Remove a order by order id 
     * @returns true if order was removed, false if order was not present 
     */ 
    virtual bool RemoveOrderByID(DepthOrderID orderID) = 0;

    /**
     * Set the order book listener if one is used 
     */ 
    virtual void set_order_book_listener(IOrderBookListener* listener) = 0;

    /**
     * Update the size on an order 
     * @returns true if order size was updated, false otherwise 
     */ 
    virtual bool UpdateOrderSize(DepthOrderID orderID, int currSize) = 0;
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
