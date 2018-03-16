/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/ImbalanceEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_IMBALANCE_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_IMBALANCE_EVENT_MSG_H_

#include "DataTypes.h"
#include "DataTypesUtils.h"
#include "Event.h"
#include "MarketDataBaseEventMsg.h"

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * ImbalanceEventMsg is an event message containing information about the imbalance 
 * quantities related to an exchange's price setting auctions.
 */ 
class ImbalanceEventMsg : public MarketDataBaseEventMsg {
public:

    ImbalanceEventMsg(Event* evt,
                  Instrument* instrument, 	
                  MarketCenterID market_center,
                  FeedType feed_type,
                  AuctionType auction_type,
                  int matched_quantity,
                  int imbalance_size,
                  int imbalance_size2,
                  double clearing_price,
                  double clearing_price2,
                  double reference_price,
                  TimeType source_time,
                  TimeType feed_handler_time,                  
                  TimeType adapter_time);


    ImbalanceEventMsg(Event* evt,
                Instrument* instrument, 	
                MarketCenterID market_center,
                FeedType feed_type,
                TimeType source_time,
                TimeType feed_handler_time,                  
                TimeType adapter_time);
                 

    ImbalanceEventMsg(const ImbalanceEventMsg& msg);

    ~ImbalanceEventMsg();

    std::string name() const;

    /**
     * Returns a const reference to the instrument for which the quote was updated
     */ 
    const Instrument& instrument() const		{ return *m_instrument; }

    /**
     * Returns which market center's auction the imbalance data pertains to
     */
    MarketCenterID market_center() const		{ return m_market_center; }

    /**
     * Identifies which type of data feed is delivering an alert
     */
    FeedType feed_type() const					{ return m_feed_type; }

    /**
     * Identifies the type of auction associated with the imbalance update
     */
    AuctionType auction_type() const			{ return m_auction_type; }

    /**
     * Quantity of shares that are matched/paired off at the refrence price
	 *
	 * For BATS Auction feed, this is normalized from min(BuyShares, SellShares)
     */
    int matched_quantity() const				{ return m_matched_quantity; }

    /**
     * Number of shares that are out of balance
     *
     * Normalized so all feeds have a signed value, positive for more buy orders than sell orders
	 *
	 * For BATS Auction feed, this is normalized from BuyShares - SellShares
     */
    int imbalance_size() const					{ return m_imbalance_size; }

    /**
     * Number of shares that are out of balance based off of just market orders
     *
     * Applicable only on ARCA; a signed value, positive for more buy orders than sell orders
     */
    int imbalance_size2() const					{ return m_imbalance_size2; }

    /**
     * Closest indicative price where imbalance would be zero
     *
     * Contains 'near price' for NASDAQ
     * Contains 'clearing price' for NYSE Open imbalance and 'continuous book clearing price' for closing imbalance
     * Contains 'indicative match price' for ARCA Book Multicast, now called 'reference price' in ARCA Book XDP
	 * Contains 'indicative price' for BATS Auction feed
     */
    double clearing_price() const				{ return m_clearing_price; }

    /**
     * Provides additional indicative measure of clearing price where applicable
     *
     * Contains 'far price' for NASDAQ
     * Contains 'closing only clearing price' for NYSE
	 * Contains 'auction only price' for BATS Auction feed
     */
    double clearing_price2() const				{ return m_clearing_price2; }

    /**
     * Reference price corresponding to the imbalance quantities
     *
     * Not provided in Arca's imbalance data message
     */
    double reference_price() const				{ return m_reference_price; }

    /**
     * Gets the market data source's timestamp for the market data event (eg the exchange feed's timestamp)
     */
    TimeType source_time() const				{ return m_source_time; }
    
    /**
     * Gets the time the feedhandler processed the market data event, if applicable and available 
     */
    TimeType feed_handler_time() const			{ return m_feed_handler_time; }
    
    /**
     * Gets the time when the Strategy Server's data adapter received the market data event
     */
    TimeType adapter_time() const				{ return m_adapter_time; }

    void set_auction_type(AuctionType auction_type) {m_auction_type = auction_type; }
    void set_matched_quantity(int matched_quantity) {m_matched_quantity = matched_quantity;}
    void set_imbalance_size(int imbalance_size) { m_imbalance_size = imbalance_size;}
    void set_imbalance_size2(int imbalance_size2) { m_imbalance_size2 = imbalance_size2; }
    void set_clearing_price(double clearing_price) { m_clearing_price = clearing_price; }
    void set_clearing_price2(double clearing_price2) { m_clearing_price2 = clearing_price2; }
    void set_reference_price(double reference_price) { m_reference_price = reference_price; }	

    ImbalanceEventMsg& operator=(const ImbalanceEventMsg& msg);

private: 
    Instrument* m_instrument;   

    double m_clearing_price;
    double m_clearing_price2;
    double m_reference_price;

    TimeType m_source_time;
    TimeType m_feed_handler_time;
    TimeType m_adapter_time;

    int m_matched_quantity;
    int m_imbalance_size;
    int m_imbalance_size2;

    AuctionType m_auction_type;
    FeedType m_feed_type;
    MarketCenterID m_market_center;
};

inline std::string ImbalanceEventMsg::name() const
{
    return "IMBALANCE_EVENT_" + m_instrument->symbol();
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
