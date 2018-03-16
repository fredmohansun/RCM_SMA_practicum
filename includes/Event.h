/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/Event.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_EVENT_H_
#define _STRATEGY_STUDIO_LIB_EVENT_H_

#include "DataTypes.h"
#include "IEventCallback.h"
#include "EventType.h"
#include "EventMsg.h"
#include "ServerDebugLogBase.h"

namespace LimeBrokerage {
namespace StrategyStudio {
       
/** 
 * Identifies an event within the Strategy Server 
 *
 * Events allow chaining, thus an Event is also a listener, if it receives an event 
 * then it can forward the event to all its listeners 
 */
class Event : public IEventCallback, protected ServerDebugLogBase {
public:

	Event(EventType type, const std::string& eventName);
	
    Event(const Event& ev);

	~Event();

    EventType type() const { return m_eventType; }
	const std::string& name() const { return m_eventName; }
    const std::string& event_listener_name() const { return m_eventName; }

    /**
     * Gets/Sets processor id  
     */ 
    ProcessorID processor_id() { return m_procID; }
    void set_processor_id(ProcessorID procID) { m_procID = procID; }

    /**
     * Gets/Sets the event callback for this processor 
     */ 
	IEventCallback* proc_closure() const { return m_procClosure; }
	void set_proc_closure(IEventCallback* evtCallback);

	EventListenersIter listener_begin() { return m_eventListeners.begin(); } 
	EventListenersIter listener_end()   { return m_eventListeners.end(); } 
	
	EventListenersConstIter listener_begin() const { return m_eventListeners.begin(); } 
	EventListenersConstIter listener_end() const   { return m_eventListeners.end(); } 

	/**
	 * Adds the event listener to the event 
	 */ 
	bool AddEventListener(int priority, IEventCallback* eventListener);

    /**
     * Remove the event listener 
     * @returns true if event listener was removed, false otherwise
     */
    bool RemoveEventListener(IEventCallback* eventListener);

    Event& operator=(const Event& ev);
    
public: /* From IEventCallback */

    /**
	 * This is the interface to be implemented when an event msg is received
	 * @returns true if event processed, false otherwise
	 */ 
	virtual bool OnEvent(EventMsg* eventMsg);  

    virtual void OnVisit(EventMsg* eventMsg) {}

private:
    EventType m_eventType;
	std::string m_eventName; 
	EventListeners m_eventListeners;   
	IEventCallback* m_procClosure;      // optional member, used in some cases to represent a processor
    ProcessorID m_procID;               // associated processor id for this event
};

inline bool Event::OnEvent(EventMsg* eventMsg)
{
    bool retval = false;
    EventListenersIter end_it = m_eventListeners.end(); 
    for(EventListenersIter it = m_eventListeners.begin(); it != end_it; ++it)
    {
        eventMsg->PushActiveEvent(this);
        
        SERVER_DEBUG_LOG("Sending event to listener " + it->second->event_listener_name());
        retval |= it->second->OnEvent(eventMsg);
        SERVER_DEBUG_LOG("Finished sending event to listener " + it->second->event_listener_name());
        
        eventMsg->PopActiveEvent();
    }

    return retval;
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
