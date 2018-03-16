/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/Utilities/MutexPthreadImpl.h                                                        
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

#ifndef _STRATEGY_STUDIO_UTILITIES_MUTEX_PTHREAD_IMPL_H_
#define _STRATEGY_STUDIO_UTILITIES_MUTEX_PTHREAD_IMPL_H_

#ifdef ND_LIB_USE_PTHREAD

#include <pthread.h>
#include <string>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace Utilities {

/**
 * This class is a wrapper around the pthread mutex, essentially providing 
 * RAII paradigm for initializing the mutex 
 */ 
class Mutex {
public:
	Mutex();
	~Mutex();

	void Lock();
	void Unlock();

	pthread_mutex_t& GetMutex(); 
	const pthread_mutex_t& GetMutex() const; 

private:
	pthread_mutex_t m_mutex; 
};

inline pthread_mutex_t& Mutex::GetMutex()
{
	return m_mutex;
}

inline const pthread_mutex_t& Mutex::GetMutex() const
{
	return m_mutex;
}

inline void Mutex::Lock()
{
	pthread_mutex_lock (&m_mutex);
}

inline void Mutex::Unlock()
{
	pthread_mutex_unlock (&m_mutex);
}

/*----------------------------------------------------------------------------*/

/**
 * This class is provides the scoped locking paradigm for the mutex 
 */ 
class ScopedLock {
public:

	ScopedLock(Mutex& mutex): m_mutex(mutex)
	{
		m_mutex.Lock(); 
	}
		
	~ScopedLock()
	{
		m_mutex.Unlock();
	}

    Mutex& GetLock() { return m_mutex; }
    const Mutex& GetLock() const { return m_mutex; }
	
private:

	Mutex& m_mutex; 
}; 

/*----------------------------------------------------------------------------*/

template<bool> 
class ConditionalScopedLock 
{
};

/**
 * Provides conditional scoped locking functionality, only if needed
 */ 
template<> 
class ConditionalScopedLock<true> {
public:

	ConditionalScopedLock(Mutex& mutex): m_mutex(mutex)
	{
		m_mutex.Lock(); 
	}
		
	~ConditionalScopedLock()
	{
		m_mutex.Unlock();
	}
	
    Mutex& GetLock() { return m_mutex; }
    const Mutex& GetLock() const { return m_mutex; }
	
private:
	Mutex& m_mutex; 
}; 

/**
 * Provides conditional scoped locking functionality, only if needed
 */ 
template<> 
class ConditionalScopedLock<false> {
public:

	ConditionalScopedLock(Mutex&)
	{
	}
		
	~ConditionalScopedLock()
	{
	}
};

} // namespace Utilities
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif

#endif
