/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/FillInfo.h                                                        
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

#ifndef _STRATEGY_STUDIO_LIB_FILL_INFO_H_
#define _STRATEGY_STUDIO_LIB_FILL_INFO_H_

#include "DataTypes.h"
#include "ExecutionTypes.h"
#include <Utilities/TimeType.h>
#include <MarketModels/MarketCenterTypes.h>
#include <ostream>

namespace LimeBrokerage {
namespace StrategyStudio {

namespace Utilities {
class SerializedStream;
}

class IInstrumentFactory; 
    
/**
 * Contains information related to fills 
 */ 
struct FillInfo {
public:

    FillInfo();

    FillInfo(MarketModels::OrderID id, const Instrument* instrument, int size, double price, LiquidityAction la);

    FillInfo(MarketModels::OrderID id,
             const std::string& execID,
             const Instrument* instrument,
             int size,
             double price,
             TransactionType transactionType,
             LiquidityAction la,
             int liquidityCode,
             const std::string& rawLiquidity,
             double execCosts,
             TimeType time,
             bool isPartial,
             MarketModels::MarketCenterID exchange,
             MarketModels::MarketCenterID lastMarket,
             bool leggingIn);

    FillInfo(const FillInfo& fillInfo);

    const Instrument* instrument() const        { return m_instrument; }
    void set_instrument(const Instrument* instrument) { m_instrument = instrument; }
     
    /**
     * Price with split adjustment 
     */ 
    double price() const                        { return m_adjPrice; }
    
    /**
     * Size with split adjustment 
     */ 
    int size() const                               { return m_adjSize; }

    /**
     * Original price without corporate actions applied 
     */ 
    double fill_price() const                     { return m_price; }

    /**
     * Original size without corporate actions applied
     */ 
    int fill_size() const                         { return m_size; }
    
    /**
     * Indicates whether this FillInfo represents a new fill or a bust or trade correction
     */
    TransactionType transaction_type() const      { return m_transactionType; }

    /**
     * Normalized liquidity code if execution provider liquidity is available
     */
    LiquidityAction liquidity_action() const      { return m_liquidityAction; }

    /**
     * Liquidity code as provided by the execution provider, if available
     */
    int liquidity_code() const                    { return m_liquidityCode; }

    /**
     * Raw liquidity values as reported by the market, if available
     */
    std::string raw_liquidity() const             { return m_rawLiquidity; }

    double exec_costs() const                     { return m_execCosts; }
    void set_exec_costs(double cost)              { m_execCosts = cost; }

    /**
     * The market center where the order was sent
     */
    MarketCenterID fill_market_id() const		  { return m_exchange; }
    void set_fill_market_id(MarketCenterID exch)  { m_exchange = exch; }

    /**
     * The market center where this fill occurred if known
     */
    MarketCenterID last_market() const		      { return m_lastMarket; }

    TimeType fill_time() const                    { return m_time; }
    void set_fill_time(TimeType time)             { m_time = time; }
    
    bool is_partial() const                       { return m_bIsPartial; }
    void set_is_partial(bool flag)                { m_bIsPartial = flag; }
    
    const std::string& order_tag() const          { return m_orderTag; }
    void set_order_tag(const std::string& tag)    { m_orderTag = tag; }
    
    bool is_legging_in() const                    { return m_bLeggingIn; }
    void set_is_legging_in(bool flag)             { m_bLeggingIn = flag; }
    
    double split_adjustment_factor() const                 { return m_fSplitAdj; }

    MarketModels::OrderID order_id() const			  { return m_orderID; }
    void order_id(MarketModels::OrderID id)	      { m_orderID = id; }

    /**
     * The ExecID as reported by the execution provider; empty if not available
     */
    const std::string& exec_id() const            { return m_execID; }
    void set_exec_id(const std::string& id)       { m_execID = id; }

public:
       
    /**
     * Add to execution costs 
     */ 
    void AccumExecCosts(double execCost)         { m_execCosts += execCost; }

    /**
     * Initializes size of the fill, assuming there are no split adjustments applicable when called
     */
    void initialize_fill_size(int size);

    /**
     * Add to current size
     */ 
    void AccumSize(int size);

    /**
     * Sets the dividend adjustment field 
     */
    void ApplyDividend(double div);

    /**
     * Sets the split adjustment field 
     */ 
    void ApplySplit(double split);

    /**
     * Save to binary stream
     */
    void SaveToBinaryStream(Utilities::SerializedStream& out) const;

    /**
     * Load from binary stream
     * Note: InstrumentFactory needed to retrieve instrument
     */ 
    void LoadFromBinaryStream(Utilities::SerializedStream& in, IInstrumentFactory& instrumentFactory);

    /**
     * Load from binary stream
     * Note: Leaves instrument set to NULL
     */ 
    void LoadFromBinaryStream(Utilities::SerializedStream& in);

    FillInfo& operator=(const FillInfo& fillInfo);

    bool operator==(const FillInfo& fillInfo) const;

    /**
     * FillInfo objects are comparable by timestamp 
     */ 
    bool operator<(const FillInfo& fillInfo) const;

private:
    void LoadFromBinaryStreamImpl(Utilities::SerializedStream& in);

private:
    const Instrument* m_instrument;
    std::string m_execID;
    double m_price; 	                // raw fill price 
    int m_size;                         // raw fill size 
    double m_adjPrice;                  // price adjusted for corporate actions
    int m_adjSize;                      // size adjusted for corporate actions 
    double m_execCosts;
    TransactionType m_transactionType;
    LiquidityAction m_liquidityAction;
    int m_liquidityCode;
    std::string m_rawLiquidity;
    MarketCenterID m_exchange;
    MarketCenterID m_lastMarket;
    TimeType m_time;
    bool m_bIsPartial; 
    MarketModels::OrderID m_orderID;
    std::string m_orderTag; 
    bool m_bLeggingIn;
    double m_fSplitAdj;                 // multiplicative adjustment used for when a split occurs
};

inline void FillInfo::AccumSize(int size)                     
{ 
    m_size += static_cast<int>(size*m_fSplitAdj); 
    m_adjSize += size; 
}

inline void FillInfo::initialize_fill_size(int size)                   
{ 
    m_size = size; 
    m_adjSize = size;
}

inline std::ostream& operator<<(std::ostream& out, const FillInfo& fillInfo)
{
    out << fillInfo.instrument()->symbol() << " at qty " << fillInfo.size() << " at price " << fillInfo.price();
    
    if (fillInfo.is_partial()) {
        out << " partial";
    }
    
    return out; 
}

} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
