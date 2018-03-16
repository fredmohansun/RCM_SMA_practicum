/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/PreprocessorOptions.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_PREPROCESSOR_OPTIONS_H_
#define _STRATEGY_STUDIO_LIB_PREPROCESSOR_OPTIONS_H_

// toggle to enable fill simulator logging
//#define STRATEGY_STUDIO_OPTIONS_ENABLE_FILL_SIMULATOR_LOGGING

// toggle to enable reading strategies from file or from database 
// note: one of the two options must be enabled 
//#define STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_FILE
#define STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_DATABASE

// validity checks for preprocessor here 
#if !defined(STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_FILE) && !defined(STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_DATABASE)
#error Either STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_FILE or STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_DATABASE must be defined
#endif 

#if defined(STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_FILE) && defined(STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_DATABASE)
#error Cannot define both STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_FILE and STRATEGY_STUDIO_OPTIONS_READ_STRATEGIES_FROM_DATABASE
#endif 

#define DOUBLE_SERIALIZATION_PRECISION 4

// DEBUG OPTIONS
//#define DEBUG_STRATEGY_STUDIO_ORDER_HANDLING

#define STRATEGY_SERVER_MAJOR_VERSION_RELEASE 2
#define STRATEGY_SERVER_MINOR_VERSION_RELEASE 18
#define STRATEGY_SERVER_MAJOR_REVISION_RELEASE 0
#define STRATEGY_SERVER_MINOR_REVISION_RELEASE 0

#endif
