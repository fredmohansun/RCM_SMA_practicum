/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/DailyPnlSnapshot.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_DAILY_SNAPSHOT_H_
#define _STRATEGY_STUDIO_LIB_DAILY_SNAPSHOT_H_

#include "DataTypes.h"

#include <fstream>

namespace LimeBrokerage {
namespace StrategyStudio {

class IPortfolioTracker;

namespace Utilities {
class SerializedStream;
}

/**
 * Contains pnl snapshot 
 */ 
struct DailyPnlSnapshot {
public:

    DailyPnlSnapshot();

    explicit DailyPnlSnapshot(const boost::gregorian::date& date);

    DailyPnlSnapshot(const boost::gregorian::date& date,
        double fAcctEquity,
        double fTotalPnl,
        double fDailyPnl,
        double fLongNotional,
        double fShortNotional,
        double fCashBalance,
        double fBorrowBalance,
        double fRebateBalance);    

    DailyPnlSnapshot(const DailyPnlSnapshot& fillInfo);

    /**
     * Check if this daily pnl snapshot has the same date as another one 
     */ 
    bool EqualsDate(const DailyPnlSnapshot& rhs) const;

    /**
     * Save to stream 
     */
    void SaveToBinaryStream(Utilities::SerializedStream& out) const;

    /**
     * Load from stream 
     */ 
    void LoadFromBinaryStream(Utilities::SerializedStream& in);

    /**
     * DailyPnlSnapshot is ordered by date 
     */ 
    bool operator<(const DailyPnlSnapshot& rhs) const;

    DailyPnlSnapshot& operator=(const DailyPnlSnapshot& fillInfo);

    /**
     * Check if all members of this struct are equivalent to another DailyPnlSnapshot
     */ 
    bool operator==(const DailyPnlSnapshot& rhs) const; 

    /**
     * Create DailyPnlSnapshot using data from IPortfolioTracker 
     */ 
    static DailyPnlSnapshot Create(boost::gregorian::date date, const IPortfolioTracker& portTracker); 

public:
    boost::gregorian::date m_date; 
    double m_fAcctEquity;     
    double m_fTotalPnl;
    double m_fDailyPnl;
    double m_fLongNotional;
    double m_fShortNotional;
    double m_fCashBalance;
    double m_fBorrowBalance; 
    double m_fRebateBalance;    
};

inline std::ostream& operator<<(std::ostream& out, const DailyPnlSnapshot& daily)
{
    out << "Date: " << to_simple_string(daily.m_date) << " ";
    out << "Account equity: " << daily.m_fAcctEquity << " ";
    out << "TotalPnl: " << daily.m_fTotalPnl << " ";    
    out << "DailyPnl: " << daily.m_fDailyPnl << " ";
    out << "Long Notional: " << daily.m_fLongNotional << " ";
    out << "Short Notional: " << daily.m_fShortNotional << " ";
    out << "Cash Balance: " << daily.m_fCashBalance << " ";
    out << "Borrow Balance: " << daily.m_fBorrowBalance << " ";
    out << "Rebate Balance: " << daily.m_fRebateBalance << " ";
    
    
    
    return out; 
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
