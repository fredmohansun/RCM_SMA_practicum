/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/IStrategyGraphs.h                                                        
*     Last Update: 2013/02/20                                                                 
*     Contents:                                     
*     Distribution:          
*                                                                                                                
*                                                                                                                
*     Copyright (c) Lime Brokerage LLC, 2013.                                                    
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

#ifndef _STRATEGY_STUDIO_LIB_ISTRATEGYGRAPHS_H_
#define _STRATEGY_STUDIO_LIB_ISTRATEGYGRAPHS_H_

#include <string>
#include "DataTypes.h"
#include "IGraphSeriesCollection.h"

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * Provides an interface that allows strategies to add custom graphing series to the Strategy Manager
 */	
class IStrategyGraphs {
public:
    IStrategyGraphs(){}
    virtual ~IStrategyGraphs(){}

    /**
     * Gets the collection of graphable data series
     */
    virtual IGraphSeriesCollection& series() = 0; 
};

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
