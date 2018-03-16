/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/MarketCenterInfo.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_MARKET_CENTER_INFO_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_MARKET_CENTER_INFO_H_ 

#include "MarketCenterTypes.h"
#include "MarketCenterFees.h"
#include "MarketCenterHours.h"

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * This class contains information about the trading fees and hours on a particular market center
 */
class MarketCenterInfo {
public:
    MarketCenterInfo(MarketCenterID marketCenterID, MarketCenterFees *defaultMarketCenterFees);
    MarketCenterInfo(MarketCenterID marketCenterID, MarketCenterFees *defaultMarketCenterFees, const MarketCenterFees& marketCenterFees);
    MarketCenterInfo(const MarketCenterInfo& marketCenterInfo);
    ~MarketCenterInfo();
    
    /**
     * Gets the market center's identifier
     */
    MarketCenterID market_id() const                { return m_marketCenterID; }

    /**
     * Gets the market center's hours
     */
    const MarketCenterHours& market_center_hours() const      { return m_marketCenterHours; }

    /**
     * Gets the market center's fees
     */
    const MarketCenterFees& market_center_fees() const;

    /**
     * Sets the market center's fees
     */
    void set_market_center_fees(const MarketCenterFees& fees)                { m_marketCenterFees = fees; }

    /**
     * Compare by mktCenterID 
     */ 
    bool operator<(const MarketCenterInfo& marketCenterInfo) const;

    MarketCenterInfo& operator=(const MarketCenterInfo& marketCenterInfo);

private: 
    MarketCenterID m_marketCenterID;
    MarketCenterFees m_marketCenterFees;
    MarketCenterFees *m_defaultMarketCenterFees;
    MarketCenterHours m_marketCenterHours;
};

inline const MarketCenterFees& MarketCenterInfo::market_center_fees() const
{
    return m_marketCenterFees.market_id == MARKET_CENTER_ID_UNKNOWN ? *m_defaultMarketCenterFees : m_marketCenterFees;
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
