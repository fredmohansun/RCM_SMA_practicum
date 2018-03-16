/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/TradeReport.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_TRADE_H_ 
#define _STRATEGY_STUDIO_LIB_TRADE_H_ 

#include "DataTypes.h"
#include <string>
#include <ostream>

namespace LimeBrokerage {
namespace StrategyStudio {

namespace Utilities {
class SerializedStream;
}

enum TradeState {
    TRADE_STATE_UNKNOWN = -1,
    TRADE_STATE_OPENED = 0,
    TRADE_STATE_ACTIVE = 1,
    TRADE_STATE_CLOSED = 2
};

/**
 * TradeReport is a construct for helping us track pnls by trades 
 *
 * Entry and exit prices are net of fees and are 
 * adjusted for splits and dividends that occur during the life of the TradeReport. 
 */ 
class TradeReport {
public:
    TradeReport();
    explicit TradeReport(TradeID tradeID);
    TradeReport(TradeID tradeID, double entryPrice, int entryQuantity);
    TradeReport(TradeID tradeID, double entryPrice, int entryQuantity, TimeType entryTime);
    TradeReport(const TradeReport& msg);
    
    TradeID id() const									{ return m_tradeID; }    

    /**
     * Returns the realized PnL attributable to the trade report
     */
    double realized_pnl() const						{ return m_fRPL; }
    
    /**
     * Returns average entry price net of fees, adjusted for splits and dividends that occured between open and close time
     */
    double average_entry_price() const			    { return m_entryPrice; }

    /**
     * Returns average exit price net of fees, adjusted for splits and dividends that occured between open and close time
     */
    double average_exit_price() const	            { return m_exitPrice; }

    /**
     * Returns split adjusted cumulative entry quantity, corresponding the maximum shares/contract position size that 
     * had been carried during the life of the trade. 
     *
     * This number will be negative for shorts
     */
    int entry_quantity() const					    { return m_entryQuantity; }
    void set_entry_quantity(int qty)		        { m_entryQuantity = qty; }

    /**
     * Returns split adjusted quantity that remains open for this trade report.
     * 
     * This number will be negative for shorts
     */
    int open_position() const				        { return m_openQuantity; }
    void set_open_position(int qty)		            { m_openQuantity = qty; }

    /**
     * Returns the amount of the entry quantity that has been filled against, representing how much of
     * the trade has been closed out.
     * 
     * This number will be negative for shorts
     */
    int filled_quantity() const					    { return (m_entryQuantity - m_openQuantity); }
    
    /**
     * Returns the timestamp of the first entry fill that created the trade report.
     */
    TimeType entry_time() const				        { return m_entryTime; }
    void set_entry_time(TimeType time)		        { m_entryTime = time; }

    /**
     * Returns the timestamp of the last exit fill that closed the trade report.
     */
    TimeType exit_time() const					    { return m_exitTime; }
    void set_exit_time(TimeType time)		        { m_exitTime = time; }
    
    /**
     * Returns whether the trade is opened or closed.
     */
    TradeState trade_state() const                  { return m_tradeState; }
    void set_trade_state(TradeState state)          { m_tradeState = state; }
    
    /**
     * Apply dividend
     */ 
    void ApplyDividend(double div);

    /**
     * Apply split 
     */ 
    void ApplySplit(double splitRatio);

    /**
     * Open an additional position in the trade 
     */ 
    void OpenPosition(double price, int quantity, double multiplier = 1);

    /**
     * Closes a position (via a fill)
     * @param price Price at which the trade occurred
     * @param quantity Positive indicates that we were buying, negative means we were selling
     */ 
    void ClosePosition(double price, int quantity, double rate, double multiplier = 1);

    /**
     * Save to stream 
     */
    void SaveToBinaryStream(Utilities::SerializedStream& out) const;

    /**
     * Load from stream    
     */ 
    void LoadFromBinaryStream(Utilities::SerializedStream& in);

    TradeReport& operator=(const TradeReport& data);

    bool operator==(const TradeReport& data) const; 

    friend std::ostream& operator<<(std::ostream& out, const TradeReport& trade); 

private: 
    TradeID m_tradeID;
    double m_entryPrice;
    double m_exitPrice; 
    int m_entryQuantity;  
    int m_openQuantity;    
    double m_fRPL;
    TradeState m_tradeState;

    TimeType m_entryTime;
    TimeType m_exitTime;
};

inline std::ostream& operator<<(std::ostream& out, const TradeReport& trade)
{
    out << "ID " << trade.m_tradeID        
        << " AvgEntryPrice: " << trade.m_entryPrice
        << " EntryQty: " << trade.m_entryQuantity
        << " AvgExitPrice: " << trade.m_exitPrice
        << " OpenQty: " << trade.m_openQuantity
        << " RPL: " << trade.m_fRPL 
        << " EntryTime: " << Utilities::ToString(trade.m_entryTime) 
        << " ExitTime: " << Utilities::ToString(trade.m_exitTime);
        
    return out;
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
