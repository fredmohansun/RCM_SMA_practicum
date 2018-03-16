/*================================================================================                               
*     Source: ../Lime/StrategyStudio/includes/MarketModels/MarketCenterTypes.h                                                        
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

#ifndef _STRATEGY_STUDIO_MARKET_MODELS_MARKET_CENTER_TYPES_H_ 
#define _STRATEGY_STUDIO_MARKET_MODELS_MARKET_CENTER_TYPES_H_ 

#include <Utilities/StrategyStudioException.h>
#include <string>

namespace LimeBrokerage {
namespace StrategyStudio {
namespace MarketModels {

/**
 * Lists the supported market centers
 */
enum MarketCenterID {
    MARKET_CENTER_ID_UNKNOWN = 0,
    //US EQUITY MARKET_CENTER_IDS
    MARKET_CENTER_ID_AMEX = 1, //MIC:XASE
    MARKET_CENTER_ID_BATS = 2, //MIC:BATS
    MARKET_CENTER_ID_BYX = 3,  //MIC:BATY
    MARKET_CENTER_ID_BSE = 4, //MIC:XBOS
    MARKET_CENTER_ID_EDGA = 5, //MIC:EDGA
    MARKET_CENTER_ID_EDGX = 6, //MIC:EDGX
    MARKET_CENTER_ID_NSX = 7,  //MIC:XCIS
    MARKET_CENTER_ID_FINRA = 8,//MIC: XADF
    MARKET_CENTER_ID_ISE = 9, //MIC:XISE
    MARKET_CENTER_ID_CHICAGO = 10, //MIC:XCHI
    MARKET_CENTER_ID_NYSE = 11, //MIC:XNYS
    MARKET_CENTER_ID_ARCA = 12, //MIC:ARCX
    MARKET_CENTER_ID_NASDAQ = 13, //MIC:XNAS
    MARKET_CENTER_ID_CONSOLIDATED_CTS = 14,
    MARKET_CENTER_ID_CONSOLIDATED_SIP = 15,
    MARKET_CENTER_ID_PHLX = 16, //MIC:XPHL //Note this was rebranded PSX in 2010
    MARKET_CENTER_ID_CBOESTOCK = 17, //MIC:CBSX
    MARKET_CENTER_ID_IEX = 18, //MIC:IEXG
    //FUTURES MARKET_CENTER_IDS
    MARKET_CENTER_ID_CME_GLOBEX = 19, //MIC:GLBX
    MARKET_CENTER_ID_ICE_FUTURES = 20, //MIC:IFUS
    MARKET_CENTER_ID_EUREX = 21, //MIC:XEUR
    MARKET_CENTER_ID_CBOE_FUTURES = 22, //MIC:XCBF
    MARKET_CENTER_ID_ASX = 23, //MIC:XASX
    MARKET_CENTER_ID_MONTREAL = 24, //MIX:XMOD
    MARKET_CENTER_ID_NASDAQ_FUTURES = 25, //MIC:XPBT
    MARKET_CENTER_ID_TOCOM = 26, //MIC:XTKT
    MARKET_CENTER_ID_SGX = 27, //MIC::XSCE
    //FIXED INCOME VENUES
    MARKET_CENTER_ID_BOND_BTEC = 28, //MIC:BTEC, BrokerTec
    MARKET_CENTER_ID_BOND_ESPD = 29, //MIC:ESPD, Nasdaq OMX eSpeed
    //US OPTIONS MARKET_CENTER_IDS
    MARKET_CENTER_ID_AMEX_OPTIONS = 30, //MIC:AMXO
    MARKET_CENTER_ID_ARCA_OPTIONS = 31, //MIC:ARCO
    MARKET_CENTER_ID_BATS_OPTIONS = 32, //MIC:BATO
    MARKET_CENTER_ID_BOX_OPTIONS = 33, //MIC:XBOX
    MARKET_CENTER_ID_CBOE_OPTIONS = 34, //MIC:XCBO
    MARKET_CENTER_ID_C2_OPTIONS = 35, //MIC:C2OX
    MARKET_CENTER_ID_ISE_OPTIONS = 36, //MIC:XISX
    MARKET_CENTER_ID_OPRA_OPTIONS = 37, //MIC:XFINO
    MARKET_CENTER_ID_NASDAQ_OPTIONS = 38, //MIC:XNDQ
    MARKET_CENTER_ID_PHLX_OPTIONS = 39, //MIC:XPHO
    MARKET_CENTER_ID_GEMINI_OPTIONS = 40, //MIC:GMNI
    MARKET_CENTER_ID_MIAMI_OPTIONS = 41, //MIC:XMIO
    MARKET_CENTER_ID_OMX_BX_OPTIONS = 42, //MIC:XBXO
    MARKET_CENTER_ID_EDGX_OPTIONS = 43, //MIC:EDGO
    MARKET_CENTER_ID_MERCURY_OPTIONS = 44, //MIC:MCRY
    MARKET_CENTER_ID_PEARL_OPTIONS = 45, //MIC:MPRL
    //US Equity ATS/DARK POOL CENTERS/SmartOrderRouter
    MARKET_CENTER_ID_SMART_ROUTER = 46,
    MARKET_CENTER_ID_ATS_BIDS = 47, //MIC:BIDS, BIDS Trading
    MARKET_CENTER_ID_ATS_CBX = 48, //MIC:ICBX, Instinet CBX
    MARKET_CENTER_ID_ATS_CRSF = 49, //MIC:CAES, Credit Suisse Crossfinder
    MARKET_CENTER_ID_ATS_CSLP = 50, //MIC:CSLP, Credit Suisse Light Pool
    MARKET_CENTER_ID_ATS_KLINK = 51, //MIC:KNLI, Knight Link
    MARKET_CENTER_ID_ATS_KMATCH = 52, //MIC:KNMX, Knight Match
    MARKET_CENTER_ID_ATS_LAVA = 53, //MIC:LAFL, Lavaflow
    MARKET_CENTER_ID_ATS_LEVEL = 54, //MIC:LEVL, Level ATS
    MARKET_CENTER_ID_ATS_LX = 55, //MIC:BARX, Barlclays LX
    MARKET_CENTER_ID_ATS_MILM = 56, //MIC:NYFX, ConvergEx Millennium
    MARKET_CENTER_ID_ATS_MLXN = 57, //MIC:BAML, Merrill Lynch ATS
    MARKET_CENTER_ID_ATS_POSIT = 58, //MIC:ITGI, ITG POSIT
    MARKET_CENTER_ID_ATS_SIGMA_X = 59, //MIC:SIGX, Goldman Sachs Sigma X MTF
    MARKET_CENTER_ID_ATS_VORTX = 60, //MIC:VTEX, ConvergEx Vortex
    MARKET_CENTER_ID_ATS_CDEL = 61, //MIC:CDEL, Citadel Apogee Dark Pool
    MARKET_CENTER_ID_ATS_DBSX = 62, //MIC:DBSX, Deutsche Bank SuperX Dark Pool
    MARKET_CENTER_ID_ATS_GTCO = 63, //MIC:GTCO, GETCO GETMatched Dark Pool
    MARKET_CENTER_ID_ATS_JPMX = 64, //MIC:JPMX, JP Morgan Dark Pool
    MARKET_CENTER_ID_ATS_PDQ = 65, //MIC:PDQX, PDQ Dark Pool
    MARKET_CENTER_ID_ATS_UBSA = 66, //MIC:UBSA, UBS ATWS Dark Pool
    MARKET_CENTER_ID_MM_TWOSIGMA = 67, //MIC:SOHO
    MARKET_CENTER_ID_MM_VIRTU = 68, //MIC:VFCM
    //Canadian dark ATS
    MARKET_CENTER_ID_CA_DARK_ICX = 69, //MIC::XICX, Instinet Canada Cross
    MARKET_CENTER_ID_CA_DARK_LIQUIDNET = 70, //MIC::LICA, Liquidnet Canada ATS
    MARKET_CENTER_ID_CA_DARK_MATCHNOW = 71, //MIC::MATN, Match Now
    MARKET_CENTER_ID_CA_DARK_NASDAQ_CXD = 72, //MIC::XCXD, Nasdaq CXD
    //US Options ATS and Routing Engines
    MARKET_CENTER_ID_SMART_ROUTER_OPTIONS = 73,
    //FX SPOT TRADING VENUES
    MARKET_CENTER_ID_FX_CURRENEX = 74, //MIC:XCUR, Currenex
    MARKET_CENTER_ID_FX_HOTSPOT = 75, //MIC:HSFX, Hotspot FX
    MARKET_CENTER_ID_FX_EBS = 76,
    MARKET_CENTER_ID_FX_REUTERS = 77,
    MARKET_CENTER_ID_FX_FXALL = 78, //MIC:FXAL
    MARKET_CENTER_ID_FX_LMAX = 79, //MIC:LMAX
    MARKET_CENTER_ID_FX_OTC = 80, //General OTC bank market data
    //International Equities
    MARKET_CENTER_ID_CA_AEQUITAS_LIT = 81,
    MARKET_CENTER_ID_CA_AEQUITAS_NEO = 82, //MIC:NEOE
    MARKET_CENTER_ID_CA_ALPHA = 83, //MIC:XATS
    MARKET_CENTER_ID_CA_CSE = 84, //MIC:XCNQ
    MARKET_CENTER_ID_CA_LYNX = 85, //MIC::LYNX
    MARKET_CENTER_ID_CA_NASDAQ_CXC = 86, //MIC:CHIC
    MARKET_CENTER_ID_CA_NASDAQ_CX2 = 87, //MIC:XCX2
    MARKET_CENTER_ID_CA_OMEGA = 88, //MIC::OMGA
    MARKET_CENTER_ID_CA_TSX = 89, //MIC::XTSE
    MARKET_CENTER_ID_CA_TSXV = 90, //MIC::XTSX
    MARKET_CENTER_ID_BOVESPA = 91, //MIC:BVMF
    MARKET_CENTER_ID_LSE = 92, //MIC:XLON, London Stock Exchange
    MARKET_CENTER_ID_EU_XETR = 93, //MIC:XETR
    MARKET_CENTER_ID_EU_XPAR = 94, //MIC:XPAR, Euronext Paris
    MARKET_CENTER_ID_EU_XAMS = 95, //MIC:XAMS, Euronext Amsterdam
    MARKET_CENTER_ID_EU_XBRU = 96, //MIC:XBRU, Euronext Brussels
    MARKET_CENTER_ID_EU_XLIS = 97, //MIC:XLIS, Euronext Lisbon
    MARKET_CENTER_ID_EU_MTAA = 98, //MIC:MTAA, Borsa Italiana
    MARKET_CENTER_ID_EU_XSWX = 99, //MIC:XSWX, SIX Swiss Exchange
    MARKET_CENTER_ID_EU_XVTX = 100, //MIC:XVTX, SIX Swiss Exchange Blue Chip
    MARKET_CENTER_ID_EU_XMCE = 101, //MIC:XMCE, Bolsa de Madrid
    MARKET_CENTER_ID_EU_XSTO = 102, //MIC:XSTO, OMX Stockholm
    MARKET_CENTER_ID_EU_XHEL = 103, //MIC:XHEL, OMX Helsinki
    MARKET_CENTER_ID_EU_XCSE = 104, //MIC:XCSE, OMX Copenhagon
    MARKET_CENTER_ID_EU_TRQX = 105, //MIC:TRQX, Turquoise
    MARKET_CENTER_ID_EU_CHIX = 106, //MIC:CHIX, Chi-X Europe
    MARKET_CENTER_ID_EU_BATE = 107, //MIC:BATE, BATS Europe
    MARKET_CENTER_ID_AP_XIDX = 108, //MIC:XIDX, Indonesia Stock Exchange
    MARKET_CENTER_ID_AP_XKLS = 109,//MIC:XKLS, Bursa Malaysia
    MARKET_CENTER_ID_AP_XSES = 110 //MIC:XSES, Singapore Exchange
};

#define MAX_EXCHANGES 111

/**
 * Converts a MarketCenterID to its string representation
 */
inline std::string MarketCenterToString(MarketCenterID market)
{
    switch (market) {
        case MARKET_CENTER_ID_AMEX:
            return "AMEX";
        case MARKET_CENTER_ID_BATS:
            return "BATS";
        case MARKET_CENTER_ID_BYX:
            return "BYX";
        case MARKET_CENTER_ID_BSE:
            return "BSE";
        case MARKET_CENTER_ID_EDGA:
            return "EDGA";
        case MARKET_CENTER_ID_EDGX:
            return "EDGX";
        case MARKET_CENTER_ID_NSX:
            return "NSX";
        case MARKET_CENTER_ID_FINRA:
            return "FINRA";
        case MARKET_CENTER_ID_ISE:
            return "ISE";
        case MARKET_CENTER_ID_CHICAGO:
            return "CHICAGO";
        case MARKET_CENTER_ID_NYSE:
            return "NYSE";
        case MARKET_CENTER_ID_ARCA:
            return "ARCA";
        case MARKET_CENTER_ID_NASDAQ:
            return "NASDAQ";
        case MARKET_CENTER_ID_CONSOLIDATED_CTS:
            return "CONSOLIDATED_CTS";
        case MARKET_CENTER_ID_CONSOLIDATED_SIP:
            return "CONSOLIDATED_SIP";
        case MARKET_CENTER_ID_PHLX:
            return "PHLX";
        case MARKET_CENTER_ID_CBOESTOCK:
            return "CBOESTOCK";
        case MARKET_CENTER_ID_IEX:
            return "IEX";
        case MARKET_CENTER_ID_CME_GLOBEX:
            return "CME_GLOBEX";
        case MARKET_CENTER_ID_ICE_FUTURES:
            return "ICE_FUTURES";
        case MARKET_CENTER_ID_EUREX:
            return "EUREX";
        case MARKET_CENTER_ID_CBOE_FUTURES:
            return "CBOE_FUTURES";
        case MARKET_CENTER_ID_ASX:
            return "ASX";
        case MARKET_CENTER_ID_MONTREAL:
            return "MONTREAL";
        case MARKET_CENTER_ID_NASDAQ_FUTURES:
            return "NASDAQ_FUTURES";
        case MARKET_CENTER_ID_TOCOM:
            return "TOCOM";
        case MARKET_CENTER_ID_SGX:
            return "SGX";
        case MARKET_CENTER_ID_BOND_BTEC:
            return "BOND_BTEC";
        case MARKET_CENTER_ID_BOND_ESPD:
            return "BOND_ESPD";
        case MARKET_CENTER_ID_AMEX_OPTIONS: 
            return "AMEX_OPTIONS";
        case MARKET_CENTER_ID_ARCA_OPTIONS:
            return "ARCA_OPTIONS";
        case MARKET_CENTER_ID_BATS_OPTIONS:
            return "BATS_OPTIONS";
        case MARKET_CENTER_ID_BOX_OPTIONS:
            return "BOX_OPTIONS";
        case MARKET_CENTER_ID_CBOE_OPTIONS:
            return "CBOE_OPTIONS";
        case MARKET_CENTER_ID_C2_OPTIONS:
            return "C2_OPTIONS";
        case MARKET_CENTER_ID_ISE_OPTIONS:
            return "ISE_OPTIONS";
        case MARKET_CENTER_ID_OPRA_OPTIONS:
            return "OPRA_OPTIONS";
        case MARKET_CENTER_ID_NASDAQ_OPTIONS:
            return "NASDAQ_OPTIONS";
        case MARKET_CENTER_ID_PHLX_OPTIONS:
            return "PHLX_OPTIONS";
        case MARKET_CENTER_ID_GEMINI_OPTIONS:
            return "GEMINI_OPTIONS";
        case MARKET_CENTER_ID_MIAMI_OPTIONS:
            return "MIAMI_OPTIONS";
        case MARKET_CENTER_ID_OMX_BX_OPTIONS:
            return "OMX_BX_OPTIONS";
        case MARKET_CENTER_ID_EDGX_OPTIONS:
            return "EDGX_OPTIONS";
        case MARKET_CENTER_ID_MERCURY_OPTIONS:
            return "MERCURY_OPTIONS";
        case MARKET_CENTER_ID_PEARL_OPTIONS:
            return "PEARL_OPTIONS";
        case MARKET_CENTER_ID_SMART_ROUTER:
            return "SMART_ROUTER";
        case MARKET_CENTER_ID_ATS_BIDS:
            return "ATS_BIDS";
        case MARKET_CENTER_ID_ATS_CBX:
            return "ATS_CBX";
        case MARKET_CENTER_ID_ATS_CRSF:
            return "ATS_CRSF";
        case MARKET_CENTER_ID_ATS_CSLP:
            return "ATS_CSLP";
        case MARKET_CENTER_ID_ATS_KLINK:
            return "ATS_KLINK";
        case MARKET_CENTER_ID_ATS_KMATCH:
            return "ATS_KMATCH";
        case MARKET_CENTER_ID_ATS_LAVA:
            return "ATS_LAVA";
        case MARKET_CENTER_ID_ATS_LEVEL:
            return "ATS_LEVEL";
        case MARKET_CENTER_ID_ATS_LX:
            return "ATS_LX";
        case MARKET_CENTER_ID_ATS_MILM:
            return "ATS_MILM";
        case MARKET_CENTER_ID_ATS_MLXN:
            return "ATS_MLXN";
        case MARKET_CENTER_ID_ATS_POSIT:
            return "ATS_POSIT";
        case MARKET_CENTER_ID_ATS_SIGMA_X:
            return "ATS_SIGMA_X";
        case MARKET_CENTER_ID_ATS_VORTX:
            return "ATS_VORTX";
        case MARKET_CENTER_ID_ATS_CDEL:
            return "ATS_CDEL";
        case MARKET_CENTER_ID_ATS_DBSX:
            return "ATS_DBSX";
        case MARKET_CENTER_ID_ATS_GTCO:
            return "ATS_GTCO";
        case MARKET_CENTER_ID_ATS_JPMX:
            return "ATS_JPMX";
        case MARKET_CENTER_ID_ATS_PDQ:
            return "ATS_PDQ";
        case MARKET_CENTER_ID_ATS_UBSA:
            return "ATS_UBSA";
        case MARKET_CENTER_ID_MM_TWOSIGMA:
            return "MM_TWOSIGMA";
        case MARKET_CENTER_ID_MM_VIRTU:
            return "MM_VIRTU";
        case MARKET_CENTER_ID_CA_DARK_ICX:
            return "CA_DARK_ICX";
        case MARKET_CENTER_ID_CA_DARK_LIQUIDNET:
            return "CA_DARK_LIQUIDNET";
        case MARKET_CENTER_ID_CA_DARK_MATCHNOW:
            return "CA_DARK_MATCHNOW";
        case MARKET_CENTER_ID_CA_DARK_NASDAQ_CXD:
            return "CA_DARK_NASDAQ_CXD";
        case MARKET_CENTER_ID_SMART_ROUTER_OPTIONS:
            return "SMART_ROUTER_OPTIONS";
        case MARKET_CENTER_ID_FX_CURRENEX:
            return "FX_CURRENEX";
        case MARKET_CENTER_ID_FX_HOTSPOT:
            return "FX_HOTSPOT";
        case MARKET_CENTER_ID_FX_EBS:
            return "FX_EBS";
        case MARKET_CENTER_ID_FX_REUTERS:
            return "FX_REUTERS";
        case MARKET_CENTER_ID_FX_FXALL:
            return "FX_FXALL";
        case MARKET_CENTER_ID_FX_LMAX:
            return "FX_LMAX";
        case MARKET_CENTER_ID_FX_OTC:
            return "FX_OTC";
        case MARKET_CENTER_ID_CA_AEQUITAS_LIT:
            return "CA_AEQUITAS_LIT";
        case MARKET_CENTER_ID_CA_AEQUITAS_NEO:
            return "CA_AEQUITAS_NEO";
        case MARKET_CENTER_ID_CA_ALPHA:
            return "CA_ALPHA";
        case MARKET_CENTER_ID_CA_CSE:
            return "CA_CSE";
        case MARKET_CENTER_ID_CA_LYNX:
            return "CA_LYNX";
        case MARKET_CENTER_ID_CA_NASDAQ_CXC:
            return "CA_NASDAQ_CXC";
        case MARKET_CENTER_ID_CA_NASDAQ_CX2:
            return "CA_NASDAQ_CX2";
        case MARKET_CENTER_ID_CA_OMEGA:
            return "CA_OMEGA";
        case MARKET_CENTER_ID_CA_TSX:
            return "CA_TSX";
        case MARKET_CENTER_ID_CA_TSXV:
            return "CA_TSXV";
        case MARKET_CENTER_ID_BOVESPA:
            return "BOVESPA";
        case MARKET_CENTER_ID_LSE:
            return "LSE";
        case MARKET_CENTER_ID_EU_XETR:
            return "EU_XETR";
        case MARKET_CENTER_ID_EU_XPAR:
            return "EU_XPAR";
        case MARKET_CENTER_ID_EU_XAMS:
            return "EU_XAMS";
        case MARKET_CENTER_ID_EU_XBRU:
            return "EU_XBRU";
        case MARKET_CENTER_ID_EU_XLIS:
            return "EU_XLIS";
        case MARKET_CENTER_ID_EU_MTAA:
            return "EU_MTAA";
        case MARKET_CENTER_ID_EU_XSWX:
            return "EU_XSWX";
        case MARKET_CENTER_ID_EU_XVTX:
            return "EU_XVTX";
        case MARKET_CENTER_ID_EU_XMCE:
            return "EU_XMCE";
        case MARKET_CENTER_ID_EU_XSTO:
            return "EU_XSTO";
        case MARKET_CENTER_ID_EU_XHEL:
            return "EU_XHEL";
        case MARKET_CENTER_ID_EU_XCSE:
            return "EU_XCSE";
        case MARKET_CENTER_ID_EU_TRQX:
            return "EU_TRQX";
        case MARKET_CENTER_ID_EU_CHIX:
            return "EU_CHIX";
        case MARKET_CENTER_ID_EU_BATE:
            return "EU_BATE";
        case MARKET_CENTER_ID_AP_XIDX:
            return "AP_XIDX";
        case MARKET_CENTER_ID_AP_XKLS:
            return "AP_XKLS";
        case MARKET_CENTER_ID_AP_XSES:
            return "AP_XSES";
        default:
            return "UNKNOWN";
    }
}

/**
 * Converts a string to a MarketCenterID, expecting a string as the portion of the enum name following 'MARKET_CENTER_ID_'
 */
MarketCenterID MarketCenterFromString(const std::string& market_center);  

/**
 * Converts a MIC string to a MarketCenterID
 */
MarketCenterID MarketCenterFromMic(const std::string& mic);

inline MarketCenterID USEquityExchangeFromChar(char chrExchange)
{
    switch (chrExchange) {
    case 'A':
        return MARKET_CENTER_ID_AMEX;
    case 'B':
        return MARKET_CENTER_ID_BSE;
    case 'C':
        return MARKET_CENTER_ID_NSX;
    case 'D':
        return MARKET_CENTER_ID_FINRA;
    case 'E':
        return MARKET_CENTER_ID_CONSOLIDATED_SIP;
    case 'I':
        return MARKET_CENTER_ID_ISE;
    case 'J':
        return MARKET_CENTER_ID_EDGA;
    case 'K':
        return MARKET_CENTER_ID_EDGX;
    case 'M':
        return MARKET_CENTER_ID_CHICAGO;
    case 'N':
        return MARKET_CENTER_ID_NYSE;
    case 'P':
        return MARKET_CENTER_ID_ARCA;
    case 'Q':
        return MARKET_CENTER_ID_NASDAQ;
    case 'S':
        return MARKET_CENTER_ID_CONSOLIDATED_CTS;
    case 'T':
        return MARKET_CENTER_ID_NASDAQ;
    case 'V':
        return MARKET_CENTER_ID_IEX;
    case 'W':
        return MARKET_CENTER_ID_CBOESTOCK;
    case 'X':
        return MARKET_CENTER_ID_PHLX;
    case 'Y':
        return MARKET_CENTER_ID_BYX;
    case 'Z':
        return MARKET_CENTER_ID_BATS;
    default:
        return MARKET_CENTER_ID_UNKNOWN;
    }
}

/**
 * Returns the MarketCenterID corresponding to a US equity options exchange's character code
 *
 * @param exchange_code A character corresponding to the OPRA Participant ID field
 */
inline MarketModels::MarketCenterID USOptionsExchangeFromChar(char exchange_code)
{
    switch (exchange_code) {
    case 'A':
        return MARKET_CENTER_ID_AMEX_OPTIONS;
    case 'B':
        return MARKET_CENTER_ID_BOX_OPTIONS;
    case 'C':
        return MARKET_CENTER_ID_CBOE_OPTIONS;
    case 'E':
        return MARKET_CENTER_ID_EDGX_OPTIONS;
    case 'H':
        return MARKET_CENTER_ID_GEMINI_OPTIONS;
    case 'I':
        return MARKET_CENTER_ID_ISE_OPTIONS;
    case 'J':
        return MARKET_CENTER_ID_MERCURY_OPTIONS;
    case 'M':
        return MARKET_CENTER_ID_MIAMI_OPTIONS;
    case 'N':
        return MARKET_CENTER_ID_ARCA_OPTIONS;
    case 'O':
        return MARKET_CENTER_ID_OPRA_OPTIONS;
    case 'P':
        return MARKET_CENTER_ID_PEARL_OPTIONS;
    case 'Q':
        return MARKET_CENTER_ID_NASDAQ_OPTIONS;
    case 'T':
        return MARKET_CENTER_ID_OMX_BX_OPTIONS;
    case 'W':
        return MARKET_CENTER_ID_C2_OPTIONS;
    case 'X':
        return MARKET_CENTER_ID_PHLX_OPTIONS;
    case 'Z':
        return MARKET_CENTER_ID_BATS_OPTIONS;
    default:
        return MARKET_CENTER_ID_UNKNOWN;
    }
}

/**
 * Returns whether the market center id is for an equity exchange
 *
 * @param market_center Strategy Studio's market center identifier
 */
inline bool IsEquityExchange(MarketCenterID market_center)
{
    if (market_center != MARKET_CENTER_ID_UNKNOWN && (market_center <= MARKET_CENTER_ID_IEX || market_center >= MARKET_CENTER_ID_CA_AEQUITAS_LIT))
        return true;
    else
        return false;
}

/**
 * Returns whether the market center id is for an equity ATS (dark pool) or smart order router
 *
 * @param market_center Strategy Studio's market center identifier
 */
inline bool IsEquityATS(MarketCenterID market_center)
{
    if (market_center >= MARKET_CENTER_ID_SMART_ROUTER && market_center <= MARKET_CENTER_ID_CA_DARK_NASDAQ_CXD)
        return true;
    else
        return false;
}

/**
 * Returns whether the market center id is for a futures exchange
 *
 * @param market_center Strategy Studio's market center identifier
 */
inline bool IsFuturesExchange(MarketCenterID market_center)
{
    if (market_center >= MARKET_CENTER_ID_CME_GLOBEX && market_center <= MARKET_CENTER_ID_SGX)
        return true;
    else
        return false;
}

/**
 * Returns whether the market center id is for an options exchange
 *
 * @param market_center Strategy Studio's market center identifier
 */
inline bool IsOptionsExchange(MarketCenterID market_center)
{
    if (market_center >= MARKET_CENTER_ID_AMEX_OPTIONS && market_center <= MARKET_CENTER_ID_PEARL_OPTIONS)
        return true;
    else
        return false;
}

/**
 * Returns whether the market center id is for an optinos ATS (dark pool) or smart order router
 *
 * @param market_center Strategy Studio's market center identifier
 */
inline bool IsOptionsATS(MarketCenterID market_center)
{
    return (market_center == MARKET_CENTER_ID_SMART_ROUTER_OPTIONS);
}

inline bool IsDerivativesExchange(MarketCenterID market_center)
{
    if (IsFuturesExchange(market_center) || IsOptionsExchange(market_center))
        return true;
    else
        return false;
}

inline bool IsFXMarketCenter(MarketCenterID market_center)
{
    if (market_center >= MARKET_CENTER_ID_FX_CURRENEX && market_center <= MARKET_CENTER_ID_FX_OTC)
        return true;
    else
        return false;
}

inline bool IsBondMarketCenter(MarketCenterID market_center)
{
    if (market_center >= MARKET_CENTER_ID_BOND_BTEC && market_center <= MARKET_CENTER_ID_BOND_ESPD)
        return true;
    else
        return false;
}

enum FeedType {
    FEED_TYPE_NONE = 0,             // indicates no feed
    FEED_TYPE_CONSOLIDATED = 1,     // US equity consolidated feed 
    FEED_TYPE_DIRECT = 2,           // direct market center feed 
    FEED_TYPE_DEPTH = 3,            // depth of book feed
    FEED_TYPE_TOP = 4,              // internal calculated top of book feed 
    FEED_TYPE_BEST = 5              // uses the best available feed for given data adapter 
};

enum MarketType {
    MARKET_TYPE_UNKNOWN = 0,
    MARKET_TYPE_US_EQUITIES = 1,
    MARKET_TYPE_GLOBEX = 2,
    MARKET_TYPE_US_EQUITY_OPTIONS = 3,
    MARKET_TYPE_SPOT_FX = 4,
    MARKET_TYPE_BRAZIL = 5, 
    MARKET_TYPE_LONDON = 6,
    MARKET_TYPE_FRANKFORT = 7,
    MARKET_TYPE_PARIS = 8,
    MARKET_TYPE_MILAN = 9,
    MARKET_TYPE_ICE = 10,
    MARKET_TYPE_EUREX = 11,
    MARKET_TYPE_CBOE_FUTURES = 12,
    MARKET_TYPE_BOND = 13,
    MARKET_TYPE_INDONESIA = 14,
    MARKET_TYPE_MALAYSIA = 15,
    MARKET_TYPE_SINGAPORE = 16,
    MARKET_TYPE_CA_EQUITIES = 17,
    MARKET_TYPE_ASX = 18,
    MARKET_TYPE_MONTREAL = 19,
    MARKET_TYPE_NASDAQ_FUTURES = 20,
    MARKET_TYPE_TOCOM = 21,
    MARKET_TYPE_SGX = 22
};

inline std::string MarketTypeToString(MarketType marketType)
{
    switch(marketType) {
    case MARKET_TYPE_US_EQUITIES:
        return "USEquities";
    case MARKET_TYPE_GLOBEX:
        return "Globex";
    case MARKET_TYPE_US_EQUITY_OPTIONS:
        return "USEquityOptions";
    case MARKET_TYPE_SPOT_FX:
        return "SpotFX";
    case MARKET_TYPE_BRAZIL:
        return "Brazil";
    case MARKET_TYPE_LONDON:
        return "London";
    case MARKET_TYPE_FRANKFORT:
        return "Frankfort";
    case MARKET_TYPE_PARIS:
        return "Paris";
    case MARKET_TYPE_MILAN:
        return "Milan";
    case MARKET_TYPE_ICE:
        return "Ice";
    case MARKET_TYPE_EUREX:
        return "Eurex";
    case MARKET_TYPE_CBOE_FUTURES:
        return "CBOEFutures";
    case MARKET_TYPE_BOND:
        return "Bond";
    case MARKET_TYPE_INDONESIA:
        return "Indonesia";
    case MARKET_TYPE_MALAYSIA:
        return "Malaysia";
    case MARKET_TYPE_SINGAPORE:
        return "Singapore";
    case MARKET_TYPE_CA_EQUITIES:
        return "CAEquities";
    case MARKET_TYPE_ASX:
        return "ASX";
    case MARKET_TYPE_MONTREAL:
        return "Montreal";
    case MARKET_TYPE_NASDAQ_FUTURES:
        return "NasdaqFutures";
    case MARKET_TYPE_TOCOM:
        return "TOCOM";
    case MARKET_TYPE_SGX:
        return "SGX";
    case MARKET_TYPE_UNKNOWN:
    default:
        return "UNKNOWN";
    }
}

inline MarketType StringToMarketType(const std::string& marketType)
{
    if (marketType.compare("USEquities") == 0) {
        return MARKET_TYPE_US_EQUITIES;
    } else if (marketType.compare("Globex") == 0) {
        return MARKET_TYPE_GLOBEX;
    } else if (marketType.compare("USEquityOptions") == 0) {
        return MARKET_TYPE_US_EQUITY_OPTIONS;
    } else if (marketType.compare("SpotFX") == 0) {
        return MARKET_TYPE_SPOT_FX;
    } else if (marketType.compare("Brazil") == 0) {
        return MARKET_TYPE_BRAZIL;
    } else if (marketType.compare("London") == 0) {
        return MARKET_TYPE_LONDON;
    } else if (marketType.compare("Frankfort") == 0) {
        return MARKET_TYPE_FRANKFORT;
    } else if (marketType.compare("Paris") == 0) {
        return MARKET_TYPE_PARIS;
    } else if (marketType.compare("Milan") == 0) {
        return MARKET_TYPE_MILAN;
    } else if (marketType.compare("Ice") == 0) {
        return MARKET_TYPE_ICE;
    } else if (marketType.compare("Eurex") == 0) {
        return MARKET_TYPE_EUREX;
    } else if (marketType.compare("CBOEFutures") == 0) {
        return MARKET_TYPE_CBOE_FUTURES;
    } else if (marketType.compare("Bond") == 0) {
        return MARKET_TYPE_BOND;
    } else if (marketType.compare("Indonesia") == 0) {
        return MARKET_TYPE_INDONESIA;
    } else if (marketType.compare("Malaysia") == 0) {
        return MARKET_TYPE_MALAYSIA;
    } else if (marketType.compare("Singapore") == 0) {
        return MARKET_TYPE_SINGAPORE;
    } else if (marketType.compare("CAEquities") == 0) {
        return MARKET_TYPE_CA_EQUITIES;
    } else if (marketType.compare("ASX") == 0) {
        return MARKET_TYPE_ASX;
    } else if (marketType.compare("Montreal") == 0) {
        return MARKET_TYPE_MONTREAL;
    } else if (marketType.compare("NasdaqFutures") == 0) {
        return MARKET_TYPE_NASDAQ_FUTURES;
    } else if (marketType.compare("TOCOM") == 0) {
        return MARKET_TYPE_TOCOM;
    } else if (marketType.compare("SGX") == 0) {
        return MARKET_TYPE_SGX;
    } else {
        return MARKET_TYPE_UNKNOWN;
    }
}

inline FeedType StringToFeedType(const std::string& feedType)
{
    if (feedType.compare("CONSOLIDATED") == 0) {
        return FEED_TYPE_CONSOLIDATED;
    } else if (feedType.compare("DIRECT") == 0) {
        return FEED_TYPE_DIRECT;
    } else if (feedType.compare("DEPTH") == 0) {
        return FEED_TYPE_DEPTH;
    } else if (feedType.compare("TOP") == 0) {
        return FEED_TYPE_TOP;
    } else if (feedType.compare("BEST") == 0) {
        return FEED_TYPE_BEST;
    } else if (feedType.compare("NONE") == 0) {
        return FEED_TYPE_NONE;
    } else {
        throw Utilities::StrategyStudioException("Unknown feed type string");
    }
}

inline std::string ToString(FeedType feedType)
{
    switch(feedType) {
    case FEED_TYPE_NONE:
        return "NONE";
    case FEED_TYPE_CONSOLIDATED:
        return "CONSOLIDATED";           
    case FEED_TYPE_DIRECT:
        return "DIRECT";
    case FEED_TYPE_DEPTH:
        return "DEPTH";
    case FEED_TYPE_TOP:
        return "TOP";
    case FEED_TYPE_BEST:
        return"BEST";
    default:
        return "UNKNOWN";
    }
}

/**
 * Converts a MarketCenterID to its string representation
 *
 * Deprecated, use MarketCenterToString
 */
inline std::string ExchangeToString(MarketCenterID exchType) { return MarketCenterToString(exchType); }

} // namespace MarketModels
} // namespace StrategyStudio
} // namespace LimeBrokerage

#endif
