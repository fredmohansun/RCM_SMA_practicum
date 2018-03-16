/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/MarketBase.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_MARKET_BASE_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_MARKET_BASE_H_ 

#include "MarketCenterTypes.h"
#include "NBBOQuote.h"
#include "Trade.h"
#include <vector>
#include <utility>
#include <ostream>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * Contains base market price info on quotes/trades used for types of markets 
 */
class MarketBase {
public:
    typedef std::vector<Quote> Quotes;
    typedef Quotes::iterator QuotesIter;
    typedef Quotes::const_iterator QuotesConstIter;

    typedef std::vector<Trade> Trades;
    typedef Trades::iterator TradesIter;
    typedef Trades::const_iterator TradesConstIter;

public:
    MarketBase();
    MarketBase(const MarketBase& market);
    virtual ~MarketBase();
   
    QuotesIter quotes_begin()                                { return m_quotes.begin(); }
    QuotesIter quotes_end()                                  { return m_quotes.end(); }

    QuotesConstIter quotes_begin() const                     { return m_quotes.begin(); }
    QuotesConstIter quotes_end() const                       { return m_quotes.end(); }

    FeedType preferred_quote_source() const                  { return m_preferredQuoteFeedType; }
    virtual void set_preferred_quote_source(FeedType type)   { m_preferredQuoteFeedType = type; }

    FeedType preferred_trade_source() const                  { return m_preferredTradeFeedType; }
    virtual void set_preferred_trade_source(FeedType type)   { m_preferredTradeFeedType = type; }

    bool withdraw_crossed_book() const                       { return m_withdrawCrossedBook; }
    virtual void set_withdraw_crossed_book(bool flag) = 0;

    // non-const accessors for 
    Quote& quote(FeedType type)                              { return m_quotes[type]; }
    Trade& trade(FeedType type)                              { return m_trades[type]; }

    /**
     * Gets the market center's quote from the best available data source
     */
    const Quote& quote() const                               { return m_quotes[m_preferredQuoteFeedType]; }

    /**
     * Retrieve the quote based on the type we want 
     */
    const Quote& quote(FeedType type) const                 { return m_quotes[type]; }
            
    /**
     * Gets the preferred trade type we want to use 
     */ 
    const Trade& last_trade() const                           { return m_trades[m_preferredTradeFeedType]; }

    /**
     * Retrieve the trade based on the type we want 
     */
    const Trade& last_trade(FeedType type) const             { return m_trades[type]; }

    /**
     * Check if there has been activity on this market center 
     */ 
    bool IsActive() const { return m_bIsActive; }

    /**
     * Reset state of market objects 
     */
    void Reset();

    /**
     * Update the quote type 
     */ 
    virtual void UpdateQuote(FeedType type, const Quote& quote); 
    
    /**
     * Update the trade data 
     * @returns true if update occurred, false otherwise 
     */ 
    virtual bool UpdateTrade(FeedType type, const Trade& quote); 
    
    MarketBase& operator=(const MarketBase& marketCenter);

private:
    virtual void InitQuotes();
    virtual void InitTrades();

protected: 
    Quotes m_quotes;
    Trades m_trades;
    bool m_bIsActive;

    FeedType m_preferredQuoteFeedType;                  // set the preferred quote type 
    FeedType m_preferredTradeFeedType;                  // set the preferred trade type 
    bool m_withdrawCrossedBook;
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
