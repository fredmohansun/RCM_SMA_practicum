/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/QuoteSide.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_QUOTE_SIDE_H_
#define _STRATEGY_STUDIO_MARKET_MODELS_QUOTE_SIDE_H_

#include "OrderTypes.h"
#include "IBookEntry.h"
#include <Utilities/TimeType.h>
#include <ostream>
#include <functional>
#include <cmath>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * Represents a the bid side or offer side of a quote.
 * 
 * Note: This will probably be renamed soon to avoid confusion with the Depth-Of-Book classes
 */ 
class QuoteSide : public IBookEntry {
public:
    QuoteSide();
    QuoteSide(double price, int qty);
    QuoteSide(double price, int qty, TimeType sourceTime, TimeType feedTime, TimeType adapterTime);
    QuoteSide(const QuoteSide& entry);
    ~QuoteSide();

    double price() const                { return m_fPrice; }
    void set_price(double val)          { m_fPrice = val; }

    int size() const                    { return m_nQty; }
    void set_size(int val)              { m_nQty = val; }

    /**
     * Clone this object
     */ 
    QuoteSide* Clone() const;

    /**
     * Compare order book entries based on price and size 
     * @returns true if price and size equal 
     */
    bool Compare(const QuoteSide& rhs, double epsilon = .00000001) const; 

    /**
     * Check if we have any data
     */
    bool HasData() const;

    /**
     * Make sure quote has non-zero size
     */ 
    bool IsValid() const; 

    /**
     * Reset prices 
     */ 
    void Reset(); 

    QuoteSide& operator=(const QuoteSide& entry);

    /**
     * Comparators (all compare on price)
     * Note: intuitively == and != should compare on qty but they do not     
     */ 
    bool operator<(const QuoteSide& entry) const;
    bool operator<=(const QuoteSide& entry) const;
    bool operator>(const QuoteSide& entry) const;
    bool operator>=(const QuoteSide& entry) const;
    bool operator==(const QuoteSide& entry) const;
    bool operator!=(const QuoteSide& entry) const;

private:
    double m_fPrice; 
    int m_nQty;
};

inline bool QuoteSide::HasData() const
{
    return !((m_fPrice == 0) && (m_nQty == 0));
}

inline bool QuoteSide::IsValid() const
{
    return (m_nQty != 0);
}

inline bool Compare(const QuoteSide& lhs, const QuoteSide& rhs)
{
    return lhs.Compare(rhs);
}

inline std::ostream& operator<<(std::ostream& out, const QuoteSide& entry)
{
    out << entry.size() << " @ " << entry.price();   
    return out;
}

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
