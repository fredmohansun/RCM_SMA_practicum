/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/TradeSide.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_TRADE_SIDE_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_TRADE_SIDE_H_ 

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

enum TradeSide {
    TRADE_SIDE_SELL = -1,
    TRADE_SIDE_UNKNOWN = 0,
    TRADE_SIDE_BUY = 1, 
};
      
} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
