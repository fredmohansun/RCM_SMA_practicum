/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/StrategyCommands.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_STATEGY_COMMANDS_H_
#define _STRATEGY_STUDIO_LIB_STATEGY_COMMANDS_H_

#include "DataTypes.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <string>
#include <map>

namespace LimeBrokerage {
namespace StrategyStudio {

class StrategyCommands;

/**
 * Information encapsulating data for strategy command 
 */ 
class StrategyCommand {	
public:

    StrategyCommand();

    StrategyCommand(StrategyStudioUInt32 commandID,
                    const std::string& commandName,
                    InputType inputType = INPUT_TYPE_NO_INPUT,
                    const std::string& inputPrompt = "");

    StrategyCommand(const StrategyCommand& rhs);

    StrategyStudioUInt32 command_id() const                         { return m_commandID; }
    void set_command_id(StrategyStudioUInt32 id)                    { m_commandID = id; } 
    
    const std::string& command_name() const                 { return m_commandName; } 
    void set_command_name(const std::string& commandName)   { m_commandName = commandName; }

    const std::string& input_prompt() const                 { return m_inputPrompt; }
    void set_input_prompt(const std::string& inputPrompt)   { m_inputPrompt = inputPrompt; }

    InputType input_type() const                            { return m_inputType; }
    void set_input_type(InputType inputType)                { m_inputType = inputType; }
        
    StrategyCommand& operator=(const StrategyCommand& rhs); 

    bool operator<(const StrategyCommand& rhs) const        { return (m_commandID < rhs.m_commandID); }

    friend class StrategyCommands;

private:
    StrategyStudioUInt32 m_commandID;
    std::string m_commandName;		
    std::string m_inputPrompt;
    InputType m_inputType; 
};

/**
 * StrategyCommands is a collection for holding and managing individual strategy commands
 */ 
class StrategyCommands {
public:
    typedef boost::multi_index::multi_index_container<StrategyCommand,  
        boost::multi_index::indexed_by<
            // sort by StrategyCommand::operator <
            boost::multi_index::ordered_unique<boost::multi_index::member<StrategyCommand,
                StrategyStudioUInt32, &StrategyCommand::m_commandID> >,
            boost::multi_index::hashed_unique<boost::multi_index::member<StrategyCommand, 
                std::string, &StrategyCommand::m_commandName> >
            >
        > StrategyCommandSet;
    
    typedef StrategyCommandSet::iterator StrategyCommandSetIter;
    typedef StrategyCommandSet::const_iterator StrategyCommandSetConstIter;

public:
    StrategyCommands();
    ~StrategyCommands();
    StrategyCommands(const StrategyCommands& rhs);
           
    StrategyCommandSetIter begin()              { return m_commands.begin(); }
    StrategyCommandSetIter end()                { return m_commands.end(); }

    StrategyCommandSetConstIter begin() const   { return m_commands.begin(); }
    StrategyCommandSetConstIter end() const     { return m_commands.end(); }

    /**
     * Adds a strategy command to the commands collection 
     * Note: Name and ID need to be unique within the system 
     * @returns Ptr to strategy command if created, NULL otherwise
     */ 
    const StrategyCommand* AddCommand(const StrategyCommand& command);

    /**
     * Check if command exists by name 
     */ 
    bool Contains(const std::string& commandName) const; 

    /**
     * Check if command exists by name 
     */ 
    bool Contains(StrategyStudioUInt32 commandID) const; 

    /**
     * Retrieve command by id 
     * @returns Ptr to command 
     */     
    const StrategyCommand* GetCommand(StrategyStudioUInt32 id) const;
    
    StrategyCommands& operator=(const StrategyCommands& commands);

private: 
    StrategyCommandSet m_commands;    
};

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
