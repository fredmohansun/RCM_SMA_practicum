/*================================================================================                               
*     Source: ../Lime/StrategyStudio/examples/strategies/SentiMomStrategy/SentiMomExample.cpp                                                        
*     Last Update: 2010/09/30 13:55:14                                                                            
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
================================================================================*/   

#ifdef _WIN32
    #include "stdafx.h"
#endif

#include "strategy_main.h"
#include "backtest_class.h"

#include "FillInfo.h"
#include "AllEventMsg.h"
#include "ExecutionTypes.h"
#include <Utilities/Cast.h>
#include <Utilities/utils.h>

#include <math.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>

using namespace LimeBrokerage::StrategyStudio;
using namespace LimeBrokerage::StrategyStudio::MarketModels;
using namespace LimeBrokerage::StrategyStudio::Utilities;

using namespace std;

typedef std::map<TimeType, PSentimentEventMsg> SMAmap;

SentiMom::SentiMom(StrategyID strategyID, const std::string& strategyName, const std::string& groupName):
    Strategy(strategyID, strategyName, groupName),
    m_spState(),
    m_bars(),
    m_instrumentX(NULL),
    m_rollingWindow(50),
    m_SentiThreshold(0.5),
    m_MomThreshold(0.5),
    m_tradeSize(100),
    m_nOrdersOutstanding(0),
    m_DebugOn(true)
{
    ifstream input_file("BTC.X.txt", std::ifstream::in);
    std::string line;
    getline(input_file, line);//Get metadata
    SMAmap sma_data;
    while(!input_file.eof()){
	getline(input_file, line);
	PSentimentEventMsg SMA_entry = PSentimentEventMsg(line);
	TimeType SMA_time = TimeHelper(line);
	sma_data[SMA_time] = SMA_entry
    }
    // note: assume market state is active
    m_spState.marketActive = true;
    this->set_enabled_pre_open_data_flag(true);
    this->set_enabled_pre_open_trade_flag(true);
    this->set_enabled_post_close_data_flag(true);
    this->set_enabled_post_close_trade_flag(true);
}

SentiMom::~SentiMom()
{
}

double str2num(std::string str){
    std::stringstream ss(str);
    double num;
    ss>>num;
    return num;
}

void data_helper(std::string line){
    std::stringstream mystring(line);
    std::vector<std::string> results((std::istream_iterator<std::string>(mystring)), std::istream_iterator<std::string>());
}
