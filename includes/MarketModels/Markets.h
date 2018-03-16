/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/Markets.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_MARKETS_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_MARKETS_H_ 

#include "MarketCenterTypes.h"
#include "MarketCenter.h"
#include "IAggrOrderBook.h"
#include "NBBOQuote.h"
#include "IOrderBookBuilder.h"
#include "TradeStats.h"
#include <Utilities/utils.h>
#include <Utilities/StdTypes.h>
#include <vector>
#include <map>
#include <ostream>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

class Instrument;
class MarketCenterInfoFactory;

/**
 * This is a collection which holds the MarketCenters with activity in a given instrument.
 * The particular MarketCenter is accessible via the MarketCenterID enum.
 *
 * By default, Markets maintains a top quote calculation, which sums quote liquidity accross market centers quoting 
 * at the best bid or best offered prices.
 *
 * This class also offers liquidity aggregation functionality.
 */
class Markets {
public:
    typedef std::vector<MarketCenter*> MarketCenterCollection;
    typedef MarketCenterCollection::iterator MarketCenterCollectionIter;
    typedef MarketCenterCollection::const_iterator MarketCenterCollectionConstIter; 

    typedef std::vector<MarketCenterID> MarketCenterIDCollection;
    typedef MarketCenterIDCollection::iterator MarketCenterIDCollectionIter;
    typedef MarketCenterIDCollection::const_iterator MarketCenterIDCollectionConstIter; 
    
    /**
     * Result from updating BBO
     * first bool indicates if quote caused an update to regional bbo to occur
     * second bool indicates if top quote was updated as a result 
     */ 
    typedef std::pair<bool, bool> QuoteUpdateResult; 

public:

    /**
     * Markets constructor
     */ 
    Markets(IOrderBookBuilderPtr pOrderBookBuilder,
            MarketCenterInfoFactory* marketCenterInfoFactory,
            MarketType marketType,
            const MarketCenterIDCollection& marketCenterIDs);

    ~Markets();

    /** 
     * Returns a reference to the MarketCenter corresponding to the specified id.
     *
     * If the corresponding MarketCenter does not exist, will return a market_center object corresponding to MARKET_CENTER_ID_UNKNONW
     */
    MarketCenter& market_center(MarketCenterID market_center)                 { return *m_marketCentersHash[market_center]; }
    const MarketCenter& market_center(MarketCenterID market_center) const     { return *m_marketCentersHash[market_center]; }

    /** 
     * Returns a reference to the MarketCenter corresponding to the specified id.
     *
     * If the corresponding MarketCenter does not exist, will return a market_center object corresponding to MARKET_CENTER_ID_UNKNONW
     */
    MarketCenter& operator[](MarketCenterID market_center)                    { return *m_marketCentersHash[market_center]; }

    const MarketCenter& operator[](MarketCenterID market_center) const        { return *m_marketCentersHash[market_center]; }

    MarketCenterCollectionIter begin()                                       { return m_marketCenters.begin(); }
    MarketCenterCollectionConstIter begin() const                            { return m_marketCenters.begin(); }

    MarketCenterCollectionIter end()                                         { return m_marketCenters.end(); }
    MarketCenterCollectionConstIter end() const                              { return m_marketCenters.end(); }

    /** 
     * Returns the number of market center objects present for the instrument.
     *
     * Note not all market centers will necessarily have trades/quote/depth data present.
     */
    MarketCenterCollection::size_type num_market_centers() const     { return m_marketCenters.size(); }
    
    /**
     * Retrieves the aggregate order book for the instrument.
     *
     * Strategy Studio's aggregate order book summarizes the combination of the order books from the individual
     * exchanges, and keeps track of which market centers have order book liquidity at each price level.
     */
    const IAggrOrderBook& aggregate_order_book() const               { return *m_aggrOrderBook; }
    IAggrOrderBook& aggregate_order_book()                           { return *m_aggrOrderBook; }
    
    FeedType preferred_quote_feed(MarketCenterID marketCenter) const  { return m_marketCentersHash[marketCenter]->preferred_quote_source(); }
    FeedType preferred_trade_feed(MarketCenterID marketCenter) const  { return m_marketCentersHash[marketCenter]->preferred_trade_source(); }
    
    /**
     * Set the preferred quote feed to contribute to the aggregate
     */ 
    void set_preferred_quote_feed(MarketCenterID marketCenter, FeedType quoteFeedType);
    
    /**
     * Set the preferred trade feed for marketCenter for last trade
     */ 
    void set_preferred_trade_feed(MarketCenterID marketCenter, FeedType tradeFeedType);

    bool withdraw_crossed_books() const                              { return m_withdrawCrossedBooks; }
    void set_withdraw_crossed_books(bool flag);

    /** 
     * Returns Strategy Studio's calculated TopQuote for the instrument.
     *
     * This is a synthetic quote Strategy Studio maintains; it provides a summary of total quote liquidity at the best bid and best offered prices, summed 
     * across all market centers quoting at those prices. Strategy Studio bases this calculation on the 
     * best available quote source for each market center.
     *
     * If the quote datasources only provide ticks that change the NBBO, top quote will be set to NBBO prices and sizes
     */
    const Quote& top_quote() const          { return m_topQuote; }

    /**
     * Retrieves the most recent trade received from the preferred source of trade tick data
     */
    const Trade& last_trade() const         { return m_lastTrade; }
    
    /**
     * Retrieves daily trading activity statistics
     */
    const TradeStats& trade_stats() const   { return m_tradeStats; }

    TradeStats& trade_stats()               { return m_tradeStats; }

    /**
     * Get the number of depth updates processed 
     */ 
    long num_depth_updates_processed() const    { return m_numDepthUpdatesProcessed; }

    /**
     * Under normal circumstances, this shouldn't be called and update of top 
     * quote should occur internally. However, market centers can be used as a 
     * simple collection. In which case, usage is then permissible. 
     */
    void set_top_quote(const Quote& topQuote)     { m_topQuote = topQuote; }

    /**
     * Get minimum bid size on all exchanges for a given price 
     */ 
    int MinExchangeBidSize(double price) const;

    /**
     * Get minimum ask size on all exchanges for a given price 
     */ 
    int MinExchangeAskSize(double price) const; 

    /**
     * Process a depth update
     * @returns DepthUpdateResult (see typedef)  
     */
    DepthUpdateResult ProcessDepthUpdate(const DepthUpdate& update);

    // Reset prices on all market centers  
    void ResetPrices();

    /**
     * Updates the consolidated regional bbo for a market center 
     * Will calculate a new top quote 
     * @returns QuoteUpdateResult (see typedef)  
     */
    QuoteUpdateResult UpdateQuote(MarketCenterID exch, const Quote& quote, FeedType feedType);

    // Used to set top_quote to NBBO in the case where NBBO ticks are the only ticks in the consolidated feed sources
    // @returns whether NBBO was used to update the top_quote 
    bool UpdateTopQuoteFromNBBO(const NBBOQuote& oldNbboQuote, const NBBOQuote& newNbboQuote, FeedType feedType);

    // Updates the last trade
    bool UpdateLastTradeData(const Trade& trade);

    // Update the trade data 
    bool UpdateTradeData(FeedType feedType, const Trade& data);

    // Dump contents of market centers  
    void DumpMarketInfo(std::ostream& out) const;

    // return depth update result
    const DepthUpdateResult& depth_update_result() const { return m_depthUpdateResult; }
    // reset depth update result
    void reset_depth_update_result() { m_depthUpdateResult.Reset(); }

private:

    // Updates top quote using aggr book and returns true if top quote changed
    bool UpdateTopQuote(TimeType bidSourceTime,
                        TimeType bidFeedHandlerTime,                        
                        TimeType askSourceTime,
                        TimeType askFeedHandlerTime,
                        TimeType adapterTime);

    // Initializes the available market centers and aggr order book
    void InitMarkets(const MarketCenterIDCollection& marketCenterIds);

    // Initializes market center 
    MarketCenter* InitMarketCenter(MarketCenterID marketCenterID);

    Markets(const Markets& marketCenters);				// not implemented
    Markets& operator=(const Markets& marketCenters);	// not implemented
   
private:
    IOrderBookBuilderPtr m_pOrderBookBuilder;            // used to customize the aggr order book and orderbooks
    MarketCenter m_defaultMarketCenter;				 
    MarketCenterCollection m_marketCenters;				 // collection of market centers for the particular instrument
    MarketCenterCollection m_marketCentersHash;          // used for quick indexing for market centers based on market center id enum
    Quote m_topQuote;  
    Trade m_lastTrade;							         // last trade that occurred on consolidated feed   
    TradeStats m_tradeStats;                             // keeps track of daily high/low/open/close
    IAggrOrderBook* m_aggrOrderBook;                     // aggregate depth order book 
    long m_numDepthUpdatesProcessed;                     // debug variable counter 
    bool m_initialized;
    bool m_withdrawCrossedBooks;                         // controls whether crossed books contribute to the aggregate
    MarketCenterInfoFactory* m_marketCenterInfoFactory;  // market center factory used 

    DepthUpdateResult m_depthUpdateResult;
};

inline std::ostream& operator<<(std::ostream& out, const Markets& markets)
{
    markets.DumpMarketInfo(out);
    return out;
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
