/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/Utilities/StdTypes.h                                                        
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

#ifndef _STRATEGY_STUDIO_UTILITIES_STD_TYPES_H_ 
#define _STRATEGY_STUDIO_UTILITIES_STD_TYPES_H_ 

#include <boost/cstdint.hpp>

typedef boost::int8_t StrategyStudioInt8;
typedef boost::uint8_t StrategyStudioUInt8;

typedef boost::int16_t StrategyStudioInt16;
typedef boost::uint16_t StrategyStudioUInt16;

typedef boost::int64_t StrategyStudioInt64;
typedef boost::uint64_t StrategyStudioUInt64;

typedef boost::int32_t StrategyStudioInt32;
typedef boost::uint32_t StrategyStudioUInt32;

#endif