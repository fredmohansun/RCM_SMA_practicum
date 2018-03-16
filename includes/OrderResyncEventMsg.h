/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/OrderResyncEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_ORDER_RESYNC_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_ORDER_RESYNC_EVENT_MSG_H_

#include "EventMsg.h"
#include "FillInfo.h"
#include "ExecutionTypes.h"
#include "Event.h"
#include "Order.h"
#include <Utilities/Cast.h>
#include <string>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * OrderResyncEventMsg is an event message for delivering updates about a Strategy's orders, such as fills, rejects, etc
 */ 
class OrderResyncEventMsg : public EventMsg {
public:
        
    OrderResyncEventMsg(const Order* order,
                        OrderUpdateType updateType,
                        const FillInfo& fillInfo, 
                        Event* ev,							
                        StrategyID origStrategyID,
                        TimeType updateTime);
    
    OrderResyncEventMsg(const OrderResyncEventMsg& msg);

    ~OrderResyncEventMsg();

    std::string name() const;

    /**
     * Returns a reference to the order params for the original order 
     */
    const Order* order() const	{ return m_order; }

    /**
     * Returns Strategy Studio's internal OrderID
     */
    OrderID		order_id() const			    { return m_order->order_id(); }

    /**
     * Returns the order id/descripter used by the Execution Provider handling this order
     */
    const OrderTag&	order_tag() const			{ return m_order->order_tag(); }

    /**
     * Returns the order update type for this event
     */
    OrderUpdateType update_type() const		    { return m_updateType; }

    /**
     * Returns the time the order update occurred, according to the Execution Provider's timestamp 
     */
    TimeType    update_time() const		        { return m_orderUpdateTime; }

    /**
     * Check if a fill occurred
     *
     * @return true if a fill occurred (full or partial), false otherwise
     */
    bool fill_occurred() const;

    /**
     * Contains information fill information about the order, if any of its quantity was filled
     */
    const FillInfo&	fill() const				{ return m_fillInfo; }
    
    StrategyID	strategy_id() const				{ return m_origStrategyID; }
    
    OrderResyncEventMsg& operator=(const OrderResyncEventMsg& msg);

private:
    const Order*	m_order;		
    OrderUpdateType	m_updateType;
    const FillInfo&	m_fillInfo;	
    StrategyID		m_origStrategyID;	
    TimeType        m_orderUpdateTime;
};

inline std::string OrderResyncEventMsg::name() const
{
    return "OrderResyncEvent_ID_" + Utilities::Cast<std::string>()(m_order->order_id()) + "_" + OrderUpdateTypeToString(m_updateType);
}

inline bool OrderResyncEventMsg::fill_occurred() const
{
    return ( ( (m_updateType == ORDER_UPDATE_TYPE_FILL) || (m_updateType == ORDER_UPDATE_TYPE_PARTIAL_FILL) ) && 
             (m_fillInfo.size() != 0)
             ) ; 
}
   
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
