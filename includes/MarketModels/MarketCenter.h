/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/MarketCenter.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_MARKET_CENTER_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_MARKET_CENTER_H_ 

#include "MarketBase.h"
#include "MarketCenterTypes.h"
#include "Quote.h"
#include "Trade.h"
#include "IOrderBook.h"
#include "IOrderBookBuilder.h"
#include "MarketCenterInfo.h"
#include <Utilities/utils.h>
#include <utility>
#include <ostream>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

class IOrderBookListener;

/**
 * This class constains information about the trading, quoting, and order book activity for an instrument
 * on a particular markect center.
 */
class MarketCenter : public MarketBase {
public:

    MarketCenter(MarketCenterID mktCenterID, 
                 IOrderBookBuilderPtr pOrderBookBuilder, 
                 MarketCenterInfo* marketCenterInfo,
                 IOrderBookListener* listener);

    MarketCenter(const MarketCenter& marketCenter);
    ~MarketCenter();
      
    virtual void set_preferred_quote_source(FeedType type);
    
    virtual void set_withdraw_crossed_book(bool flag);

    /**
     * Update the quote type 
     */ 
    virtual void UpdateQuote(FeedType type, const Quote& quote); 

    /**
     * Gets the market center's identifier
     */
    MarketCenterID market_id() const                { return m_mktCenterID; }

    // Non-const accessor for order book
    IOrderBook& order_book() { return *m_mktOrderBook; }

    /**
     * Retrieve the market center's order book
     */     
    const IOrderBook& order_book() const { return *m_mktOrderBook; }
    
    // Non-const accessor for MarketCenterInfo
    MarketCenterInfo& market_center_info() { return *m_marketCenterInfo; }

    /**
     * Retrieve the market center's MarketCenterInfo
     */     
    const MarketCenterInfo& market_center_info() const { return *m_marketCenterInfo; }
    
    /**
     * Check if this market center has any quote data
     */
    bool HasQuoteData() const; 

    /**
     * Process a depth update and updates our best depth quote 
     * @returns pair<bool, bool>
     *    - first bool true if depth update caused change to order book state
     *    - second bool true if caused change to best quote
     */
    std::pair<bool, bool> ProcessDepthUpdate(const DepthUpdate& update);

    /**
     * Reset state of market center 
     */
    void Reset();

    /**
     * Get the number of depth updates processed 
     */ 
    long num_depth_updates_processed() const    { return m_numDepthUpdatesProcessed; }

    /**
     * Compare by mktCenterID 
     */ 
    bool operator<(const MarketCenter& marketCenter) const;

    MarketCenter& operator=(const MarketCenter& marketCenter);

private: 
    MarketCenterID m_mktCenterID;
    IOrderBookBuilderPtr pOrderBookBuilder;          // used for constructing the order book
    IOrderBook* m_mktOrderBook;                      // order book for holding depth
    IOrderBookListener* m_orderBookListener;         // aggregate order book listener
    Utilities::PriceToIntKeyFunc<7> m_hashFunc;      // hasher for price comparisons - should probably use IOrderBook::PriceHashFunc
    MarketCenterInfo* m_marketCenterInfo;			 // fees and hours for this market
    long m_numDepthUpdatesProcessed;                 // debug variable counter 
};

inline std::ostream& operator<<(std::ostream& out, const MarketCenter& market)
{
    out << MarketCenterToString(market.market_id())         
        << ":: " << market.quote(FEED_TYPE_CONSOLIDATED);

    return out;
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
