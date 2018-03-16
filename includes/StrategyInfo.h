/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/StrategyInfo.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_STRATEGYINFO_H_
#define _STRATEGY_STUDIO_LIB_STRATEGYINFO_H_

#include "DataTypes.h"
#include <set>
#include <string>
#include <vector>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * Holds information before strategy is created 
 */ 
struct StrategyInfo {
public:
    typedef std::set<std::string> SymbolSet; 
    typedef SymbolSet::iterator SymbolSetIter;
    typedef SymbolSet::const_iterator SymbolSetConstIter;

public:
    StrategyInfo();

    StrategyInfo(StrategyID strategyID, const std::string& name, const std::string& type, const std::string& group);

    StrategyInfo(StrategyID strategyID, 
                 const std::string& name, 
                 const std::string& type, 
                 const std::string& group,
                 const std::string& account,
                 const std::string& instOwner);

    StrategyInfo(const StrategyInfo& strategyInfo); 

    ~StrategyInfo();

    SymbolSetIter symbols_begin()				{ return m_symbolSet.begin(); }
    SymbolSetConstIter symbols_begin() const	{ return m_symbolSet.begin(); }
    SymbolSetIter symbols_end()					{ return m_symbolSet.end(); }
    SymbolSetConstIter symbols_end() const		{ return m_symbolSet.end(); }
    
    bool AddSymbol(const std::string& symbol); 

    /**
     * Creates a comma-delimited list of symbols 
     */ 
    std::string CreateSymbolString() const;

    StrategyInfo& operator=(const StrategyInfo& strategyInfo);

public:
    StrategyRunMode m_runMode;
    StrategyID m_strategyID; 
    std::string m_name;     
    std::string m_type;
    std::string m_group;
    std::string m_account;
    std::string m_instOwner;	    
    int m_processorID;
    std::string m_settingsFile;
    SymbolSet m_symbolSet;
    int m_subscriptionMode;
    double m_initialEquity;
};

/**
 * Holds information for a list of strategies
 */ 
class StrategyInformation {
public:
    typedef std::vector<StrategyInfo*> StrategyInfoList;
    typedef StrategyInfoList::iterator StrategyInfoListIter;
    typedef StrategyInfoList::const_iterator StrategyInfoListConstIter;

public:
    StrategyInformation();
    ~StrategyInformation();

    StrategyInfoListIter begin()			{ return m_strategyInfoList.begin(); } 
    StrategyInfoListIter end()				{ return m_strategyInfoList.end(); }

    StrategyInfoListConstIter begin() const { return m_strategyInfoList.begin(); } 
    StrategyInfoListConstIter end() const	{ return m_strategyInfoList.end(); }

    size_t size() const						{ return m_strategyInfoList.size(); }

    void clear()                            { m_strategyInfoList.clear(); }

    /**
     * Add the strategy info to the collection
     */ 
    void Add(StrategyInfo* strategyInfo);

    /**
     * Remove the strategy info from the collection
     */
    void Remove(StrategyInfoListIter iter);

    /**
     * Find strategy information by ID
     */
    StrategyInfoListIter Find(StrategyID strategyID);

    void Sort();

private:
    StrategyInfoList m_strategyInfoList;
};

class StrategyInfoLoadOrder :  public std::binary_function<StrategyInfo*, StrategyInfo*, bool> {
public:
    bool operator()(const StrategyInfo* x, const StrategyInfo* y) const 
    { 
        if (x->m_processorID >= 0) {
            return (y->m_processorID < 0);
        } else if (y->m_processorID >= 0) {
            return false;
        } else {
            return (x->m_symbolSet.size() > y->m_symbolSet.size());
        }
    }
};

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
