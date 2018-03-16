/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/Instrument.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_INSTRUMENT_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_INSTRUMENT_H_ 

#include <Utilities/TimeType.h>
#include "QuoteSide.h"
#include "Quote.h"
#include "Markets.h"
#include "MarketCenter.h"
#include "MarketCenterInfoFactory.h"
#include "IAggrOrderBook.h"
#include "NBBOQuote.h"
#include "IOrderBookBuilder.h"
#include "CurrencyTypes.h"

#include <time.h>
#include <map>
#include <string> 
#include <set>
#include <ostream>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

class ConversionRate;

typedef std::string SymbolTag;
typedef unsigned InstrumentID;
typedef std::map<StrategyStudioInt64, double> TickSizes;  // Price-TickSize pairs - this must be an ordered container

/**
 * Lists the supported instrument types
 */
enum InstrumentType {
    INSTRUMENT_TYPE_UNKNOWN = 0,
    INSTRUMENT_TYPE_EQUITY = 1,
    INSTRUMENT_TYPE_FUTURE = 2,
    INSTRUMENT_TYPE_OPTION = 3,
    INSTRUMENT_TYPE_FX = 4,
    INSTRUMENT_TYPE_BOND = 5,
    INSTRUMENT_TYPE_INDEX = 6,
    INSTRUMENT_TYPE_FUND = 7
};

/**
 * Converts InstrumentType into its string representation
 */
inline std::string InstrumentTypeToString(InstrumentType secType) {
    switch (secType) {
        case INSTRUMENT_TYPE_EQUITY:
            return "INSTRUMENT_TYPE_EQUITY";
        case INSTRUMENT_TYPE_FUTURE:
            return "INSTRUMENT_TYPE_FUTURE";
        case INSTRUMENT_TYPE_OPTION:
            return "INSTRUMENT_TYPE_OPTION";
        case INSTRUMENT_TYPE_FX:
            return "INSTRUMENT_TYPE_FX";
        case INSTRUMENT_TYPE_BOND:
            return "INSTRUMENT_TYPE_BOND";
        default:
            return "INSTRUMENT_TYPE_UNKNOWN";
    }
}

/**
 * Provides the base functionality for all instrument types. 
 *
 * It contains the instrument's basic descriptive information and the current state of its
 * market activity. 
 */ 
class Instrument {
public:
    typedef std::set<Instrument*> Children; 
    typedef Children::iterator ChildrenIter; 
    typedef Children::const_iterator ChildrenConstIter; 

    typedef Markets::QuoteUpdateResult QuoteUpdateResult;

public:
    Instrument(InstrumentID instrID, 
               const SymbolTag& symbol, 
               const InstrumentType secType,
               MarketType marketType,
               const Markets::MarketCenterIDCollection& marketCenterIDs,
               IOrderBookBuilderPtr pOrderBookBuilder,
               MarketCenterInfoFactory* marketCenterInfoFactory);

    virtual ~Instrument();

    IAggrOrderBook& aggregate_order_book()              { return m_markets.aggregate_order_book(); }
    const IAggrOrderBook& aggregate_order_book() const  { return m_markets.aggregate_order_book(); }
          
    SymbolTag symbol()      							 { return m_strSymbol; } 

    /**
     * Gets the instrument's symbol
     */
    const SymbolTag& symbol() const	                    { return m_strSymbol; } 

    /**
     * Sets the instrument's symbol
     */
    void set_symbol(const SymbolTag& symbol)            { m_strSymbol = symbol; }

    /**
     * Gets the instrument's id
     */
    InstrumentID id() const                             { return m_instrID; }
    
    /**
     * Retrieves the instrument's type
     *
     * This can be checked to cast to the appropriate Instrument specialization to look up
     * more specialized instrument information
     */
    InstrumentType type() const	                        { return m_instrumentType; } 

    ///
    /// Non-const accessor to the underlier 
    ///
    Instrument* underlier() const                        { return m_pUnderlier; }

    /**
     * Retrieves the instrument's underlier
     *
     * @return null if the instrument is an underlier, or if the instrument's underlier is not registered
     */	
    void set_underlier(Instrument* instrument)           { m_pUnderlier = instrument; } 
    
    ///
    /// Non-const accessor to the markets collection
    ///
    Markets& markets()                                   { return m_markets; }

    /**
     * Retrieve the markets collection 
     */ 
    const Markets& markets() const                       { return m_markets; }

    MarketType market_type() const                       { return m_marketType; }

    /**
     * Retrieves the last time the instrument's state was updated, according to the timestamp of the last update's data source
     */
    TimeType source_time() const                         { return m_sourceUpdateTime; }
    void set_source_time(TimeType time)                  { m_sourceUpdateTime = time; }

    /**
     * Retrieves the last time the instrument's state was updated, according to the Strategy Studio server's local timestamp
     */
    TimeType internal_time() const                       { return m_internalUpdateTime; }
    void set_internal_time(TimeType time)                { m_internalUpdateTime = time; }
    
    /** 
     * Returns Strategy Studio's calculated TopQuote for the instrument.
     *
     * This is a synthetic quote Strategy Studio maintains; it provides a summary of total quote liquidity at the best bid and best offered prices, summed 
     * across all market centers quoting at those prices. Strategy Studio bases this calculation on the 
     * best available quote source for each market center.
     *
     * If the quote datasources only provide ticks that change the NBBO, top quote will be set to NBBO prices and sizes
     */
    const Quote& top_quote() const                      { return m_markets.top_quote(); }        

    NBBOQuote& nbbo()                                   { return m_nbboQuote; }

    /**
     * Retrieves the official NBBO quote for the instrument, if available. If not it returns an empty quote.
     *
     * This is the National Best Bid/Best Offer as calculated and disseminated by the SIP (for example, CTA, UTP, OPRA)
     */
    const NBBOQuote& nbbo() const                       { return m_nbboQuote; }

    /**
     * Retrieves the most recent trade received from the preferred source of trade tick data
     */
    const Trade& last_trade() const                     { return m_markets.last_trade(); }

    /**
     * Retrieves daily trading statistics
     */
    const TradeStats& trade_stats() const               { return m_markets.trade_stats(); }
                    
    bool is_first_trade_received() const                { return m_bFirstTradeReceived; }
    void set_is_first_trade_received()                  { m_bFirstTradeReceived = true; }

    /**
     * Retrieves the instrument's current tick size
     */
    double min_tick_size() const;

	/**
     * Get/Set tick sizes based on price
     */
	double min_tick_size(double price) const;
    void set_tick_sizes(const TickSizes* tickSizes);

    /*
     * Controls whether crossed order books contribute to the aggregate
     */
    bool withdraw_crossed_books() const                 { return m_markets.withdraw_crossed_books(); }
    void set_withdraw_crossed_books(bool flag);

    const ConversionRate* conversion_rate() const       { return m_quoteConversionRate; }
    void set_conversion_rate(const ConversionRate* conversionRate) { m_quoteConversionRate = conversionRate; }

    /**
    * Retrieves the instrument's quoting currency
    */
    CurrencyType currency() const;

    virtual const ConversionRate* base_conversion_rate() const { return 0; }   // override for currency

    /**
     * Retrieves the instrument's contract value multiplier
     */
    double multiplier() const                           { return m_fMultiplier; }
    void set_multiplier(double mult)                    { m_fMultiplier = mult; }

    ChildrenIter children_begin()			            { return m_children.begin(); } 
    ChildrenIter children_end()				            { return m_children.end(); } 
    ChildrenConstIter children_begin() const            { return m_children.begin(); } 
    ChildrenConstIter children_end() const              { return m_children.end(); } 

    FeedType preferred_quote_feed(MarketCenterID marketCenter) const  { return m_markets.preferred_quote_feed(marketCenter); }
    FeedType preferred_trade_feed(MarketCenterID marketCenter) const  { return m_markets.preferred_quote_feed(marketCenter); }
         
    void set_preferred_quote_feed(MarketCenterID marketCenter, FeedType quoteFeedType);
    void set_preferred_trade_feed(MarketCenterID marketCenter, FeedType tradeFeedType);

    /**
     * Add a instrument as a child to this instrument 
     *
     * Does not register the child instrument if instrument already present in children list
     * Child instruments are used for quick access to an underlier's derivatives 
     *
     * @returns true if instrument registered, false otherwise 
     */ 
    bool AddChildInstrument(Instrument* instrument);

    /**
     * Check if a particular instrument is already registered as a child 
     *
     * @returns true if instrument present in children list, false otherwise 
     */ 
    bool HasChildInstrument(Instrument* instrument) const;

    /**
     * Check if our calculated top quote is better than the consolidated NBBO 
     */ 
    bool IsCalcTopQuoteBetter();
    
    /**
     * Print price data for this instrument 
     */ 
    void PrintMarketPriceData(std::ostream& out) const;

    /**
     * Resets prices on instrument 
     */ 
    void ResetPrices();
        
    /**
     * Simple equality comparison that checks that the securities 
     * symbols are equivalent 
     * @return true if passes equality check, false otherwise
     */ 
    bool SymbolEquals(const Instrument& instrument) const; 
    
    /**
     * Updates last trade info using new trade data, based on whether
     * the trade came from the market center's preferred trade feed source
     * @return true if instrument was updated, false otherwise 
     */ 
    bool UpdateLastTradeData(const Trade& trade);

    /**
     * Updates bid-ask prices and sizes, last trade, qty for an exchange 
     * from a new quote 
     * @return true if instrument was updated, false otherwise 
     */ 
    bool UpdateInstrumentExchTradeData(const Trade& entry, FeedType feedType);

    /**
     * Updates only the bid-ask prices and sizes from a new quote for a market center's data
     * @returns QuoteUpdateResult (see typedef)
     */ 
    QuoteUpdateResult UpdateInstrumentQuote(MarketCenterID exch, const Quote& quote, FeedType feedType);

    // Used to set top_quote to NBBO in the case where NBBO ticks are the only ticks in the consolidated feed sources
    // @returns whether NBBO was used to update the top_quote 
    bool UpdateTopQuoteFromNBBO(const NBBOQuote& quote, FeedType feedType);

    /**
     * Updates only the bid-ask prices and sizes from a new quote 
     */ 
    void UpdateNBBO(const NBBOQuote& quote);

    /**
     * Equality operator, does additional dynamic comparison via Compare()
     */
    bool operator==(const Instrument& instrument) const; 

    friend std::ostream& operator<<(std::ostream& out, const Instrument& sec);
    
private:

    /**
     * Does additional setting of min tick size depending on instrument 
     * Default doesn't do anything
     */ 
    virtual void CalcMinTickSize(); 

    Instrument(const Instrument& instrument);				// not implemented
    Instrument& operator=(const Instrument& instrument);	// not implemented

protected: /* Information common for all securities */ 
    InstrumentID m_instrID;
    SymbolTag m_strSymbol;
    InstrumentType m_instrumentType;     
    NBBOQuote m_nbboQuote;     
    TimeType m_sourceUpdateTime;
    TimeType m_internalUpdateTime;	            // used for indicating when we see times inside our system
    Instrument* m_pUnderlier;		            // Used for derivative instrument 
    Children m_children;		                // Lists children securities 
    bool m_bFirstTradeReceived;                 // set to true when first trade received
    double m_fMinTickSize;                      // minimum tick size 
    double m_fMultiplier;                       // multiplier for instrument    
    IOrderBookBuilderPtr m_pOrderBookBuilder;   // used for constructing orderbooks in derived objects 
    Markets m_markets;
    MarketType m_marketType;
	const ConversionRate* m_quoteConversionRate;    // to convert from quote to home currency
	const TickSizes* m_tickSizes;
};

inline std::ostream& operator<<(std::ostream& out, const Instrument& sec)
{
    out << "SymbolTag: " << sec.symbol() << " ";
    out << "Type: " << InstrumentTypeToString(sec.type()) << std::endl;
    out << "Top quote: " << sec.top_quote() << std::endl;    
    out << "NBBO Consolidated: " << sec.nbbo() << std::endl;	
    out << "Last Trade: " << sec.last_trade().price() << std::endl;
    out << "Last Size: " << sec.last_trade().size() << std::endl;
    out << sec.m_markets << std::endl;
    return out; 
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
