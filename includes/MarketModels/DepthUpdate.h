/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/DepthUpdate.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_DEPTH_UPDATE_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_DEPTH_UPDATE_H_

#include <Utilities/TimeType.h>
#include "DepthDataTypes.h"
#include "MarketCenterTypes.h"
#include "MDBaseObject.h"

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * This class describes an update to an order book
 */
class DepthUpdate : public MDBaseObject {
public:

    DepthUpdate();
    DepthUpdate(DepthSide side, double price, int size, int numOrders, MarketCenterID mktCenter);
    DepthUpdate(DepthSide side, double price, int size, int numOrders, MarketCenterID mktCenter, TimeType sourceTime, TimeType feedTime, TimeType adapterTime);
    DepthUpdate(DepthSide side, double price, int size, int numOrders, MarketCenterID mktCenter, DepthReasonForChange reason);
    DepthUpdate(DepthSide side, double price, int size, int numOrders,  MarketCenterID mktCenter, DepthReasonForChange reason, TimeType sourceTime, TimeType feedTime, TimeType adapterTime);
    DepthUpdate(DepthOrderID orderID, DepthSide side, double price, int size, MarketCenterID mktCenter);
    DepthUpdate(DepthOrderID orderID, DepthSide side, double price, int size, MarketCenterID mktCenter, TimeType sourceTime, TimeType feedTime, TimeType adapterTime);
    DepthUpdate(DepthOrderID orderID, DepthSide side, double price, int size, MarketCenterID mktCenter, DepthReasonForChange reason);
    DepthUpdate(DepthOrderID orderID, DepthSide side, double price, int size, MarketCenterID mktCenter, DepthReasonForChange reason, TimeType sourceTime, TimeType feedTime, TimeType adapterTime);
    DepthUpdate(const DepthUpdate& update);

    /**
     * Returns whether the depth update is by price level or by individual order, or whether this update resets the order book
     */
    DepthUpdateType update_type() const                 { return m_updateType; }
    void set_update_type(DepthUpdateType updateType)    { m_updateType = updateType; }

    /**
     * Returns the order id of the order in the order book that has updated, zero if not applicable
     */
    DepthOrderID order_id() const                       { return m_orderID; }
    void set_order_id(DepthOrderID orderID)             { m_orderID = orderID; }

    /**
     * If a cancel/replace has occurred, this returns the original order ID of the order
     */
    DepthOrderID old_order_id() const                   { return m_oldOrderID; }
    void set_old_order_id(DepthOrderID orderID)         { m_oldOrderID = orderID; }

    /**
     * If a cancel/replace has occurred, this returns the original price of the order
     */
    double old_price() const                            { return m_fOldPrice; }
    void set_old_price(double oldPrice)                 { m_fOldPrice = oldPrice; }

    /**
     * Returns the side of the order book that is being updated
     */
    DepthSide side() const                              { return m_side; }
    void set_side(DepthSide side)                       { m_side = side; }

    /**
     * Returns the price of the order book entry that is updating
     */
    double price() const                                { return m_fPrice; }
    void set_price(double price)                        { m_fPrice = price; }
    
    /**
     * Returns the new size of the order book entry that is updating
     */
    int size() const                                    { return m_nSize; }
    void set_size(int size)                             { m_nSize = size; }

    /**
     * Returns the number of orders when update type is depth-by-price-level; returns 0 for depth-by-order
     */
    int num_orders() const                                    { return m_numOrders; }
    void set_num_orders(int numOrders)                        { m_numOrders = numOrders; }

    /**
     * Returns an enumerator describing the type of change that triggered the depth-of-book tick
     */
    DepthReasonForChange reason() const                 { return m_reason; }
    void set_reason(DepthReasonForChange reason)        { m_reason = reason; }

    /**
     * When a new order is being added, returns the MPID associated with the order, if applicable, an empty string otherwise
     */
    const std::string& market_participant_id() const        { return m_mpid; }
    void set_market_participant_id(const std::string& mpid) { m_mpid = mpid; }

    /**
     * Returns the market center whose Order Book is updating
     */
    MarketCenterID market_center() const                { return m_marketCenter; }
    void set_market_center(MarketCenterID mktCenter)    { m_marketCenter = mktCenter; }
       
    void Reset();

    /**
     * Returns whether or not this is an implied-originated update
     */
    bool is_implied() const;
        
    bool operator==(const DepthUpdate& update) const; 
    
    DepthUpdate& operator=(const DepthUpdate& update);

private:
    std::string m_mpid;                // market participant id if needed 
    double m_fPrice;
    double m_fOldPrice;                 // if price was changed, old price here
    DepthOrderID m_orderID;
    DepthOrderID m_oldOrderID;          // if order if was changed, old id contained here 
    int m_nSize;
    int m_numOrders;
    MarketCenterID m_marketCenter;     // market center of which update occurs 
    DepthUpdateType m_updateType;
    DepthSide m_side;
    DepthReasonForChange m_reason;
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
