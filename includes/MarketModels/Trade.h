/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/Trade.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_TRADE_DATA_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_TRADE_DATA_H_ 

#include "MarketCenterTypes.h"
#include "ConditionCodes.h"
#include <Utilities/TimeType.h>
#include "MDBaseObject.h"
#include <string>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

#define NUM_TRADE_CONDITION_FIELDS 4

/**
 * Contains information on trades ticks
 */
class Trade : public MDBaseObject {
public:

    Trade();
    
    Trade(double lastPrice, 
              int quantity,
              MarketCenterID market_center);
   
    Trade(double lastPrice, 
              int quantity,
              MarketCenterID market_center,
              TimeType sourceTime,
              TimeType feedHandlerTime,
              TimeType adapterTime);  

    Trade(const Trade& msg);
    
    /**
     * Gets the price of the trade
     */
    double price() const								{ return m_price; }
    void set_price(double price)					    { m_price = price; }

    /**
     * Gets the quantity of the trade
     */
    int size() const									{ return m_quantity; }
    void set_size(int quantity)							{ m_quantity = quantity; }
    
    /**
     * Gets the market center on which the trade occurred
     */
    MarketCenterID market_id() const					{ return m_market_center; }
    void set_market_id(MarketCenterID market_center)	{ m_market_center = market_center; }

    /**
     * Verify that price and quantity are non-zero 
     */ 
    bool IsValid() const;

    /**
     * Checks whether the trade tick carries with it an associated trade condition
     *
     * Since some datafeeds have multiple condition fields, this allows you to check 
     * for the existence of a trade condition without having to worry about which field
     * should contain which subset of the trade conditions.
     *
     * @param condition The trade condition to check on
     * @returns whether the supplied condition is associated with the trade tick
     */
    bool HasSpecifiedTradeCondition(TradeCondition condition) const			{return m_conditions[kTradeConditionHash[condition]] == static_cast<StrategyStudioUInt8>(condition);}

    /**
     * Accessors for the trade conditions
     */
    TradeCondition trade_condition() const				{ return static_cast<TradeCondition>(m_conditions[0]); }
    TradeCondition trade_condition2() const				{ return static_cast<TradeCondition>(m_conditions[1]); }
    TradeCondition trade_condition3() const				{ return static_cast<TradeCondition>(m_conditions[2]); }	 
    TradeCondition trade_condition4() const				{ return static_cast<TradeCondition>(m_conditions[3]); }	

    /**
     * Checks whether trade's conditions indicate trade  was reported late, at a delay
     */
    bool IsTradeReportedLate() const;

    /**
     * Checks whether trade's conditions indicate a cancellation print
     */
    bool IsTradeACancel() const;

    /**
     * Checks whether trade's conditions indicate trade was reported out of sequence
     */
    bool IsTradeReportedOutOfSequence() const;

    /**
     * Checks whether trade's conditions indicate trade was executed as a block
     */
    bool IsTradeABlockTrade() const;

    /**
     * Checks whether trade's conditions indicate trade was executed during a crossing session
     */
    bool IsTradeFromCrossingSession() const;

    /**
     * Is trade official open print, based on trade conditions. 
     */
    bool IsTradeOfficialOpen() const;

    /**
     * Is trade official close print, based on trade conditions. 
     */
    bool IsTradeOfficialClose() const;

    /**
     * Checks whether trade's conditions indicate trade may not be straightforwardly comparable to the current state of the market
     */
    bool IsTradePriceNonCurrent() const;

    /**
     * Checks whether a trade's conditions indicate trade has non-standard settlement terms
     */
    bool IsTradeSettlementNonStandard() const;

    /**
     * Checks whether trade's conditions indicate trade was exempt from RegNMS checks
     */
    bool IsTradeThroughExempt() const;

    /**
     * Checks whether trade's conditions indicate trade should be used to update daily volume stats
     */
    bool DoesTradeUpdateVolume() const;

    /**
     * Checks whether trade's conditions indicate trade should be used to update the consolidated Highs and Lows for the day
     *
     * Note when trade conditions are present, this will return false for extended hour and odd lot trades, per SIAC/UTP guidelines
     */
    bool DoesTradeUpdateConsolidatedHighLows() const;

    /**
     * Checks whether trade's conditions indicate trade should be used to update the consolidated last price print
     */
    bool DoesTradeUpdateConsolidatedLast(bool isFirstTradeOfDay) const;

    /**
     * Checks whether trade's conditions indicate trade should be used to update the highs and lows for the MarketCenter on which the trade occurred
     *
     * Note when trade conditions are present, this will return false for extended hour and odd lot trades, per SIAC/UTP guidelines
     */
    bool DoesTradeUpdateMarketCenterHighLows() const;

    /**
     * Checks whether trade's conditions indicate trade should be used to update the last price print for the MarketCenter on which the trade occurred
     */
    bool DoesTradeUpdateMarketCenterLast(bool isFirstTradeOfDay) const;

    void InsertTradeCondition(TradeCondition condition)							{m_conditions[kTradeConditionHash[condition]] = static_cast<StrategyStudioUInt8>(condition);}

    //can be called when feedhandler's already using standard indexing; note no bounds checking occurs
    void InsertTradeCondition(TradeCondition condition, StrategyStudioUInt8 index)		{m_conditions[index] = static_cast<StrategyStudioUInt8>(condition);}

    /**
     * Update trade data with contents of another trade data 
     */ 
    bool UpdateTradeData(const Trade& entry); 

    Trade& operator=(const Trade& data);

    bool operator==(const Trade& rhs) const;

    void Reset(); 

private: 
    double m_price;
    int m_quantity;
    MarketCenterID m_market_center; 
    StrategyStudioUInt8 m_conditions[NUM_TRADE_CONDITION_FIELDS];
    static const StrategyStudioUInt8 kTradeConditionHash[];
};

inline bool Trade::IsValid() const
{
    return ( m_quantity != 0 );
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
