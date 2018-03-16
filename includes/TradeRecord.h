/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/TradeRecord.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_TRADERECORD_H_
#define _STRATEGY_STUDIO_LIB_TRADERECORD_H_

#include "TradeReport.h"
#include <list>
#include <vector> 
#include <utility>

namespace LimeBrokerage {
namespace StrategyStudio {

namespace Utilities {
class SerializedStream;
}

class IInstrumentFactory; 

/**
 * TradeRecord holds the list of trade reports associated with a particular instrument
 */  
class TradeRecord {
public:
    typedef std::list<TradeReport> TradeList; 
    typedef TradeList::iterator TradeListIter; 
    typedef TradeList::const_iterator TradeListConstIter; 

    typedef std::vector<TradeReport> HistoricalTrades;
    typedef HistoricalTrades::iterator HistoricalTradesIter;
    typedef HistoricalTrades::const_iterator HistoricalTradesConstIter;

public:
    explicit TradeRecord(bool saveHistory = false);
    explicit TradeRecord(const Instrument* instrument, bool saveHistory = false);
    TradeRecord(const TradeRecord& portRecord);
    ~TradeRecord();

    const Instrument* instrument() const                { return m_instrument; }
    void set_instrument(const Instrument* instrument)   { m_instrument = instrument; }

    TradeListIter trade_open_begin()                        { return m_openTrades.begin(); }
    TradeListConstIter trade_open_begin() const             { return m_openTrades.begin(); }
    
    TradeListIter trade_open_end()                          { return m_openTrades.end(); }
    TradeListConstIter trade_open_end() const               { return m_openTrades.end(); }

    TradeListIter trade_notify_begin()                      { return m_notifyTrades.begin(); }
    TradeListConstIter trade_notify_begin() const           { return m_notifyTrades.begin(); }
    
    TradeListIter trade_notify_end()                        { return m_notifyTrades.end(); }
    TradeListConstIter trade_notify_end() const             { return m_notifyTrades.end(); }

    HistoricalTradesIter trade_closed_begin()               { return m_closedTrades.begin(); }
    HistoricalTradesConstIter trade_closed_begin() const    { return m_closedTrades.begin(); }

    HistoricalTradesIter trade_closed_end()                 { return m_closedTrades.end(); }
    HistoricalTradesConstIter trade_closed_end() const      { return m_closedTrades.end(); }

    size_t num_open_trades() const                            { return m_openTrades.size(); }
    size_t num_notify_trades() const                          { return m_notifyTrades.size(); }
    size_t num_closed_trades() const                          { return m_closedTrades.size(); }

    bool save_history_flag() const                                    { return m_bSaveHistory; }
    void set_save_history_flag(bool flag)                             { m_bSaveHistory = flag; } 

    /**
     * Returns the trade at the front of the record    
     */ 
    TradeReport& FrontTrade()                                     { assert(m_openTrades.size() > 0); return m_openTrades.front(); }
    const TradeReport& FrontTrade() const                         { assert(m_openTrades.size() > 0); return m_openTrades.front(); }

    /**
     * Returns the trade at the back of the record    
     */ 
    TradeReport& BackTrade()                                     { assert(m_openTrades.size() > 0); return m_openTrades.back(); }
    const TradeReport& BackTrade() const                         { assert(m_openTrades.size() > 0); return m_openTrades.back(); }

    /**
     * Get most current closed trade
     */ 
    TradeReport& LastTrade()                                      { assert(m_closedTrades.size() > 0); return m_closedTrades.back(); }
    const TradeReport& LastTrade() const                          { assert(m_closedTrades.size() > 0); return m_closedTrades.back(); }

    /**
     * Pops all contents of notify trades to an out iterator 
     */ 
    template<typename Iter>
    void PopNotifyTrades(Iter outIter);

    std::pair<bool, bool> AddTrade(TradeID tradeID, double price, int quantity, bool leggingIn);

    /**
     * Adds a new trade for record keeping with given trade id
     * @returns pair <true if trade id was used, false otherwise : true if close occurred, false otherwise>
     */
    std::pair<bool, bool> AddTrade(TradeID tradeID, double price, int quantity, TimeType updateTime, bool leggingIn);

    /**
     * Apply dividend to each trade 
     */ 
    void ApplyDividend(double div);

    /**
     * Apply split to each trade if instruments match 
     */ 
    void ApplySplit(double splitRatio);

    void ClearOpenTrades();

    void ClearNotifyTrades();

    void ClearClosedTrades();
    
    /**
     * Reset all associated state 
     */ 
    void ResetState();

    /**
     * Save to stream 
     */
    void SaveToBinaryStream(Utilities::SerializedStream& out, bool saveOnlyOpen = false) const;

    /**
     * Load from stream    
     */ 
    void LoadFromBinaryStream(Utilities::SerializedStream& in, const IInstrumentFactory& factory);
    
    bool operator==(const TradeRecord& record) const;
   
    TradeRecord& operator=(const TradeRecord& record);

private:
    const Instrument* m_instrument;
    TradeList m_openTrades;             // list of open trades 
    TradeList m_notifyTrades;           // list of trades that were recently closed for notifying clients 
    HistoricalTrades m_closedTrades;    // historical list of trades that were closed 
    bool m_bSaveHistory;                // flag for letting us know if we should save history 
};

 template<typename Iter>
 void TradeRecord::PopNotifyTrades(Iter outIter)
 {
     while (!m_notifyTrades.empty()) {
        *outIter = m_notifyTrades.front();
        m_notifyTrades.pop_front();
     }
 }

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
