/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/OrderUpdateEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_ORDER_UPDATE_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_ORDER_UPDATE_EVENT_MSG_H_

#include "TimePrioritizedEventMsg.h"
#include "FillInfo.h"
#include "ExecutionTypes.h"
#include "Event.h"
#include "Order.h"
#include <Utilities/Cast.h>
#include <string>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * OrderUpdateEventMsg is an event message for delivering updates about a Strategy's orders, such as fills, rejects, etc
 */ 
class OrderUpdateEventMsg : public TimePrioritizedEventMsg {
public:
        
    OrderUpdateEventMsg(OrderID orderID,
                        const Order* order,
                        OrderUpdateType updateType,
                        Event* ev,
                        TimeType updateTime);
    
    OrderUpdateEventMsg(OrderID orderID,
                        const Order* order,
                        OrderUpdateType updateType,
                        const FillInfo* fillInfo,
                        Event* ev,
                        TimeType updateTime);
    
    OrderUpdateEventMsg(const OrderUpdateEventMsg& msg);

    ~OrderUpdateEventMsg();

    OrderUpdateEventMsg& operator=(const OrderUpdateEventMsg& msg);

    std::string name() const;

    /**
     * Returns a reference to the original order
     */
    const Order& order() const					{ return *m_order; }
    void set_order(const Order* order)			{ m_order = order; }

    /**
     * Returns Strategy Studio's internal OrderID
     */
    OrderID order_id() const					{ return m_orderID; }

    /**
     * Returns the update type for this event
     */
    OrderUpdateType update_type() const			{ return m_updateType; }

    /**
     * Returns the time the order update occurred, according to the Execution Provider's timestamp 
     */
    TimeType    update_time() const		        { return m_orderUpdateTime; }

    /**
     * Returns the reason text associated with this order update
     */
    const std::string& reason() const			{ static const std::string blankReason; return m_order ? m_order->reason() : blankReason; }

    /**
     * Check if a fill occurred
     *
     * @return true if a fill occurred (full or partial), false otherwise
     */
    bool fill_occurred() const;

    /**
     * Returns a pointer to the fill information, or NULL if no fill occurred
     */
    const FillInfo*	fill() const				{ return m_fillInfo; }

    /**
     * Returns whether this update removes the order from the Working Orders collection
     */
    bool completes_order() const				{ return m_completesOrder; }
    void set_completes_order(bool flag) 		{ m_completesOrder = flag; }

    // From ITimePrioritized - not really used 
    bool Trigger(TimeType)                      { return true; }

private:
    MarketModels::OrderID	m_orderID;
    const Order*		m_order;
    OrderUpdateType		m_updateType;
    const FillInfo*		m_fillInfo;
    bool				m_completesOrder;
    TimeType			m_orderUpdateTime;
};

inline std::string OrderUpdateEventMsg::name() const
{
    return "OrderUpdateEvent_ID_" + Utilities::Cast<std::string>()(m_orderID) + "_" + OrderUpdateTypeToString(m_updateType);
}

inline bool OrderUpdateEventMsg::fill_occurred() const                  
{ 
    return ( ( (m_updateType == ORDER_UPDATE_TYPE_FILL) || (m_updateType == ORDER_UPDATE_TYPE_PARTIAL_FILL) ) && 
             (m_fillInfo->size() != 0)
             ) ; 
}
   
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
