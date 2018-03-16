/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/StrategyInitInfo.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_STRATEGYINITINFO_H_
#define _STRATEGY_STUDIO_LIB_STRATEGYINITINFO_H_

#include "DataTypes.h"
#include "StrategyCommands.h"
#include <Utilities/GenericMap.h>
#include <string>
#include <map>

namespace LimeBrokerage {
namespace StrategyStudio {

class StrategyParam;
class ParamDescriptor;

class StrategyInitInfo : public Utilities::GenericMap<std::string, StrategyParam*> {
public:
    typedef Container ParamInfo;
    typedef ParamInfo::iterator ParamInfoIter;
    typedef ParamInfo::const_iterator ParamInfoConstIter;

public:
    StrategyInitInfo();
    StrategyInitInfo(const std::string& name);
    ~StrategyInitInfo();

    /*std::string GetGroup() const			{ return m_group; }
    void SetGroup(const std::string& group) { m_group = group; }*/

    bool GetParamSetFlag() const            { return m_bParamsSet; }
    void SetParamSetFlag(bool flag)         { m_bParamsSet = flag; }

    const std::string& GetName() const		{ return m_name; }
    void SetName(const std::string& name)	{ m_name = name; }

    StrategyCommands& commands()                   { return m_strategyCommands; }
    const StrategyCommands& commands() const       { return m_strategyCommands; }
    void set_commands(const StrategyCommands& rhs) { m_strategyCommands = rhs; }

    /**
     * Initialize this object from an init line 
     */ 
    void InitFromString(const std::string& buf);

    /**
     * Convert this object into an init string 
     */ 
    std::string ToInitString() const;

private:
    std::string m_group;
    std::string m_name;
    bool m_bParamsSet;
    StrategyCommands m_strategyCommands;
};

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
