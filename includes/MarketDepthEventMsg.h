/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketDepthEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_MARKET_DEPTH_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_MARKET_DEPTH_EVENT_MSG_H_

#include "DataTypes.h"
#include "MarketDataBaseEventMsg.h"
#include "Event.h"
#include <MarketModels/DepthUpdate.h>
#include <vector>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * MarketDepthEventMsg is the event message for depth-of-book updates from an order book feed
 */ 
class MarketDepthEventMsg : public MarketDataBaseEventMsg {
public:
    typedef std::vector<MarketModels::DepthUpdate> DepthUpdates;
    typedef DepthUpdates::iterator DepthUpdatesIter;
    typedef DepthUpdates::const_iterator DepthUpdatesConstIter;

public:
        
    MarketDepthEventMsg(Event* ev, Instrument* instrument, TimeType eventTime);
    
    MarketDepthEventMsg(const MarketDepthEventMsg& msg);

    std::string name() const;

    /**
     * Identifies the type of depth event that has occurred
     */
    MarketModels::DepthUpdateType depth_update_type() const        { return m_depthUpdate.update_type(); }
    void set_depth_update_type(MarketModels::DepthUpdateType type) {  m_depthUpdate.set_update_type(type); }

    MarketModels::DepthUpdate& depth_update()                      { return m_depthUpdate; }
    const MarketModels::DepthUpdate& depth_update() const          { return m_depthUpdate; }  

    void set_depth_update(const MarketModels::DepthUpdate& update) { m_depthUpdate = update; }
       
    const Instrument& instrument() const                        { return *m_instrument; }

    bool updated_order_book() const                             { return m_depthUpdateResult.order_book_was_updated; }

    bool updated_top_quote() const                              { return m_depthUpdateResult.top_quote_was_updated; }

    bool updated_market_center_best() const                     { return m_depthUpdateResult.market_center_best_was_updated; }
    
    /**
     * Gets the market data source's timestamp for the market data event (eg the exchange feed's timestamp)
     */
    TimeType source_time() const                                { return m_depthUpdate.source_time(); }
    
    /**
     * Gets the time the feedhandler processed the market data event, if applicable and available 
     */
    TimeType feed_handler_time() const                          { return m_depthUpdate.feed_handler_time(); }
   
    /**
     * Gets the time when the Strategy Server's data adapter received the market data event
     */
    TimeType adapter_time() const                                { return m_depthUpdate.adapter_time(); }

    MarketDepthEventMsg& operator=(const MarketDepthEventMsg& msg);

private: /* Event msg hooks */

    /**
     * Handles updating of the instrument before handing instrument to strategy
     */
    virtual bool PreProcess(); 

    // we use this to reset the instrument's depth result flags for "refresh complete" messages
    virtual void PostProcess();

private:
    Instrument* m_instrument;                           // instrument in question 
    MarketModels::DepthUpdate m_depthUpdate;               // for dealing with just one depth update 
    MarketModels::DepthUpdateResult m_depthUpdateResult;   // result of process depth update  
    bool m_bIsInitData;                                 // tells server this is init data and no event propagation needed 
};

inline std::string MarketDepthEventMsg::name() const
{
    return "MarketDepth_Instr_" + m_instrument->symbol();
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
