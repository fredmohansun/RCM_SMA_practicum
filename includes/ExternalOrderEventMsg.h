/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/ExternalOrderEventMsg.h
*     Last Update: 2012/07/24 13:55:14 	                                                                       
*     Contents:                                     
*     Distribution:          
*                                                                                                                
*                                                                                                                
*     Copyright (c) Lime Brokerage LLC, 2011 - 2012.                                                    
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

#ifndef _STRATEGY_STUDIO_LIB_EXTERNAL_ORDER_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_EXTERNAL_ORDER_EVENT_MSG_H_

#include "EventMsg.h"
#include "DataTypes.h"
#include "DataTypesUtils.h"
#include "Event.h"
#include "ExecutionTypes.h"
#include <Utilities/IParams.h>
#include <boost/tuple/tuple.hpp>
#include "OrderParams.h"
#include <FlashProtocol/FlashTypes.h>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * ExternalOrderEventMsg is an event message containing order submissions coming from
 * the Strategy Manager manual order entry dialog or from a 3rd party trading platform
 */ 
class ExternalOrderEventMsg : public EventMsg {
public:
    typedef boost::unordered_map<int, std::string> TagFieldPair;
    typedef TagFieldPair::iterator TagFieldPairIterator;
    typedef TagFieldPair::const_iterator TagFieldPairConstIterator;
    
    enum ExternalOrderSource { EXTERNAL_ORDER_SOURCE_STRATEGY_MANAGER, EXTERNAL_ORDER_SOURCE_FIX };

    ExternalOrderEventMsg(FlashProtocol::OrderRequestType orderRequestType, const std::string &clientOrderID, const OrderParams &orderParams, Event* ev);
    ExternalOrderEventMsg(FlashProtocol::OrderRequestType orderRequestType, const std::string &topic, void *closure);
    ~ExternalOrderEventMsg() {}

private:
    ExternalOrderEventMsg(const ExternalOrderEventMsg& msg);
    ExternalOrderEventMsg& operator=(const ExternalOrderEventMsg& msg);

public:

    /**
     * Identifies whether the order submission is a new order vs a cancel or replace request
     */
    FlashProtocol::OrderRequestType order_request_type() const {return orderRequestType_;}

    /**
     * Identifies whether the order came from Strategy Manager or a 3rd party platform
     */
    ExternalOrderSource			source() const {return source_;}

    /**
     * Identifies the instrument the order submission pertains to
     */
    const Instrument*			instrument() const {return instrument_;}

    /**
     * Parameters of the order submission
     */
    OrderParams&				params() {return order_;}

    /**
     * Returns the client order ID, ie the order ID used by the system submitting the order
     */
    const std::string&			client_order_id() const {return clientOrderId_;}
        
    /**
     * Returns the account for which the order was submitted
     */
    const std::string&			account() const { return account_; }

    /**
     * Tags contain additional fields used when the order comes from a 3rd party platform
     *
     * Not used when orders come from Strategy Manager
     */
    const TagFieldPair&			tags() const { return tags_; }
        
    /**
     * Retrieves a specified tag from the collection of additional fields sent in from the 3rd party platform.
     *
     * Not used when orders come from Strategy Manager
     */
    std::string					GetTag(int tag) const {TagFieldPairConstIterator iter = tags_.find(tag); if (iter != tags_.end()) return iter->second; return "";}

    /**
     * Returns the topic to use to publish updates back to the 3rd party requester. 
     *
     * Not used when orders come from Strategy Manager
     */
    const std::string&			topic() const {return topic_;}

    /**
     * Closure contains identification information to send back with topic messages when publishing updates to a 3rd party requester
     *
     * Not used when orders come from Strategy Manager
     */
    void*						closure() const {return closure_;}

    void						set_instrument(const Instrument* instrument) { instrument_ = instrument; }
    void						set_account(const std::string& account) { account_ = account; }
    void						AddTag(int tag, const std::string& field) {tags_[tag] = field;}
        
private:
    FlashProtocol::OrderRequestType orderRequestType_;
    ExternalOrderSource			source_;
    TagFieldPair				tags_;
    const Instrument*			instrument_;
    std::string					clientOrderId_;
    std::string                 account_;
                                                // objects for coordinating between strategy and order data adapter
    std::string					topic_;			// string that strategy publishes to that order adapter subscribes to
    void*						closure_;		// order id used by the order adapter, possibly complex.  This object is not cleaned up by this class.
    OrderParams					order_;
};

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif