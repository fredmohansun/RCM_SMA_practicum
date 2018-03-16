/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/MarketCenterFees.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_MARKET_CENTER_FEES_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_MARKET_CENTER_FEES_H_

#include "MarketCenterTypes.h"

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * Contains exchange specific params for customizing behavior by different exchanges 
 */ 
struct MarketCenterFees {
public:

    MarketCenterFees();

    MarketCenterFees(MarketCenterID exchange,                      
                 double fFeeForTakingPerContract,
                 double fFeeForPostingPerContract,
                 double fFeeForOpeningAuctionPerContract,
                 double fFeeForClosingAuctionPerContract);

    MarketCenterFees(const MarketCenterFees& params);

    MarketCenterFees& operator=(const MarketCenterFees& params); 
    
public:

    MarketCenterID market_id;   

    /**
     * The fee per share or contract for removing/taking liquidity on the market center
     *
     * Note: negative numbers indicate a rebate
     */
    double taking_fee_per_contract;

    /**
     * The fee per share or contract for adding/posting liquidity on the market center
     *
     * Note: negative numbers indicate a rebate
     */
    double posting_fee_per_contract; 

    /**
     * The fee per share or contract for participating in the opening auction on the market center
     *
     * Note: negative numbers indicate a rebate
     */
    double opening_auction_fee_per_contract;

    /**
     * The fee per share or contract for participating in the closing auction on the market center
     *
     * Note: negative numbers indicate a rebate
     */
    double closing_auction_fee_per_contract;
};

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
