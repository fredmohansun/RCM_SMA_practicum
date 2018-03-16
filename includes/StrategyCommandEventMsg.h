/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/StrategyCommandEventMsg.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_STRATEGY_COMMAND_STATE_EVENT_MSG_H_
#define _STRATEGY_STUDIO_LIB_STRATEGY_COMMAND_STATE_EVENT_MSG_H_

#include "EventMsg.h"
#include "DataTypes.h"
#include "Event.h"
#include "StrategyCommands.h"
#include <Utilities/Cast.h>
#include <boost/any.hpp>

namespace LimeBrokerage {
namespace StrategyStudio {

/**
 * StrategyCommandEventMsg encapsulates a custom command request from the GUI
 */ 
class StrategyCommandEventMsg : public EventMsg {
public:

    StrategyCommandEventMsg(Event* ev);

    StrategyCommandEventMsg(StrategyStudioUInt32 commandID,
                            const boost::any& input,
                            Event* ev);
        
    StrategyCommandEventMsg(const StrategyCommandEventMsg& rhs);

    ~StrategyCommandEventMsg();

    std::string name() const;
     
    StrategyStudioUInt32 command_id() const                                           { return m_commandID; }
    void set_command_id(StrategyStudioUInt32 id)                                      { m_commandID = id; } 
    
    boost::any& input_data()                                                  { return m_input; }
    const boost::any& input_data() const                                      { return m_input; }
    void set_input_data(const boost::any& data)                               { m_input = data; }

    const StrategyCommand* command() const                                    { return m_command; }
    void set_command(const StrategyCommand* cmd) const                        { m_command = cmd; }


    StrategyCommandEventMsg& operator=(const StrategyCommandEventMsg& msg);

private:
    StrategyStudioUInt32 m_commandID;
    boost::any m_input;
    mutable const StrategyCommand* m_command; // ND 7-17: Declared mutable to facilitate setting by strategy
};

inline std::string StrategyCommandEventMsg::name() const
{
    return "StrategyCommand_" + Utilities::Cast<std::string>()(command_id());
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
