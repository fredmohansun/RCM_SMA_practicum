/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/Utilities/SafeQueue.h                                                        
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

#ifndef _STRATEGY_STUDIO_UTILITIES_SAFE_QUEUE_H_
#define _STRATEGY_STUDIO_UTILITIES_SAFE_QUEUE_H_

#include "Mutex.h"
#include "Condition.h"
#include "StrategyStudioException.h"
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <queue> 

namespace LimeBrokerage {
namespace StrategyStudio {
namespace Utilities {

template<typename T> 
class SafeQueue {
public:
	SafeQueue();
	~SafeQueue();

    /**
     * Clear out contents 
     */ 
    void Clear();

	/**
	 * Test whether container is empty
	 */ 
	bool IsEmpty() const; 

	/**
	 * Return size (public member function) 
	 */
	size_t size() const;  

	/**
	 * Access next element (public member function) 
	 */
	T* Front() const; 

	/**
	 * Access last element (public member function) 
	 */
	T* Back () const; 

	/**
	 * Insert element (public member function) 
	 */ 
	bool Push(T* datum); 

	/**
	 * Pop the next element 
	 * @returns Next item in queue, NULL if timed out 
	 */ 
	T* Pop();

	/**
	 * Pop the next element 
	 * @param ms Indicates how long we want to block for in milliseconds, optional
	 *			if set to a negative number, then will block until something 
	 *			is pushed onto the queue
	 * @returns Next item in queue, NULL if timed out 
	 */ 
	T* Pop(int timeoutInMilliseconds, bool &timedOut);

    T* Pop(boost::posix_time::ptime absTime, bool &timedOut);

	/**
	 * Pop the next element if present, else if none present, return immediately
	 * @returns Next item in queue, NULL if empty 
	 */
	T* PopNoWait(); 

	/**
	 * Informs the queue and any watiers that queue is going to shut down 
	 */ 
	void Shutdown(); 

    /**
     * Start up usage of safe queue if shutdown 
     */ 
    void Start();

private: 
	std::queue<T*> m_queue;
	mutable Mutex m_mutex;
	Condition m_cond; 
	bool m_bShutDown;
};

template<typename T>
SafeQueue<T>::SafeQueue():
	m_queue(),
	m_mutex(),
	m_cond(),
	m_bShutDown(false)
{
}

template<typename T>
SafeQueue<T>::~SafeQueue()
{
	// trigger any threads waiting on pop to shutdown
	Shutdown();
	Clear();
}

template<typename T>
void SafeQueue<T>::Clear()
{
	// wait for any threads to exit 
	ScopedLock lock(m_mutex);

	// free any remaining objects in queues
	while (!m_queue.empty()) {
		T* datum = m_queue.front();
		m_queue.pop();
		delete datum;
	}
}

template<typename T>
bool SafeQueue<T>::IsEmpty() const
{
	ScopedLock lock(m_mutex);
	return m_queue.empty();
}

template<typename T>
size_t SafeQueue<T>::size() const
{
	ScopedLock lock(m_mutex);
	return m_queue.size();
}

template<typename T>
T* SafeQueue<T>::Front() const
{
	ScopedLock lock(m_mutex);
	return m_queue.front();
}

template<typename T>
T* SafeQueue<T>::Back() const
{
	ScopedLock lock(m_mutex);
	return m_queue.back();
}

template<typename T>
bool SafeQueue<T>::Push(T* datum)
{
	bool result = false;
	ScopedLock lock(m_mutex);

	if(!m_bShutDown) {
		m_queue.push(datum);
		result = true;
	}

	m_cond.Notify();

	return result;
}

template<typename T>
T* SafeQueue<T>::Pop()
{
	T* datum = NULL;
	ScopedLock lock(m_mutex);

	if(m_bShutDown)	{
		if(m_queue.empty()) {
			return NULL;
        } else 	{
            // Keep returning values until we are empty
	        datum = m_queue.front();
		    m_queue.pop();
		}
	} else { // We are not shutting down
		while(!m_bShutDown && m_queue.empty())
			m_cond.Wait(lock);

		if (!m_queue.empty()) {
			datum = m_queue.front();
			m_queue.pop();
		}
	}

	return datum;
}

template<typename T>
T* SafeQueue<T>::Pop(int timeout, bool &timedOut)
{
	T* datum = NULL;
	ScopedLock lock(m_mutex);
	timedOut = false;

	if(m_bShutDown)	{
		if(!m_queue.empty()) {
			datum = m_queue.front();
			m_queue.pop();
		}
	} else { // We are not shutting down
		if(m_queue.empty()) {
			int waitTime = timeout;

			do {
				boost::posix_time::ptime oldTime(boost::posix_time::microsec_clock::universal_time());
	
				// Returns false if we waited the full time, true if the condition variable was signaled (by Push or Shutdown being called)
				if(!m_cond.TimedWait(lock, waitTime))
					timedOut = true;
				else // Code to deal with spurrious wakeups
					waitTime = (int)(waitTime - (boost::posix_time::microsec_clock::universal_time() - oldTime).total_milliseconds() );
			} while(m_queue.empty() && !timedOut && !m_bShutDown);
			// We may not need to check empty and shutdown here because those should coincide with condition variable being signaled
		}

		if (!m_queue.empty()) {
			datum = m_queue.front();
			m_queue.pop();
		}
	}

	return datum;
}

template<typename T>
T* SafeQueue<T>::Pop(boost::posix_time::ptime absTime, bool &timedOut)
{
	T* datum = NULL;
	ScopedLock lock(m_mutex);
	timedOut = false;

	if(m_bShutDown)	{
		if(!m_queue.empty()) {
			datum = m_queue.front();
			m_queue.pop();
		}
	} else { // We are not shutting down
		if(m_queue.empty()) {
            // we need a loop here to cope with spurious wakeups
			do {
				// Returns false if we waited the full time, true if the condition variable was signaled (by Push or Shutdown being called)
				timedOut = !m_cond.TimedWait(lock, absTime);
			} while(m_queue.empty() && !timedOut && !m_bShutDown);
			// We may not need to check empty and shutdown here because those should coincide with condition variable being signaled
		}

		if (!m_queue.empty()) {
			datum = m_queue.front();
			m_queue.pop();
		}
	}

	return datum;
}

template<typename T>
T* SafeQueue<T>::PopNoWait()
{
    T* datum = NULL;
	ScopedLock lock(m_mutex);

	if (!m_queue.empty()) {
		datum = m_queue.front();
		m_queue.pop();
	}

	return datum;
}

template<typename T>
void SafeQueue<T>::Shutdown()
{
    ScopedLock lock(m_mutex);

	if (m_bShutDown) return;

	m_bShutDown = true;
    m_cond.NotifyAll();
}

template<typename T>
void SafeQueue<T>::Start()
{
    ScopedLock lock(m_mutex);

    if (!m_bShutDown) return;

    m_bShutDown = false;
}

} // namespace Utilities
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
