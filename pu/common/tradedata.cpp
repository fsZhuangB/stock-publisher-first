/**
 * @file    tradedata.h
 *
 * 交易代理的基础数据结构定义
 *
 * @version 0.1.1      2019/09/20
 *          - 定义了用于上游策略模块与交易代理之间交互的基础数据结构
 **/

#include "tradedata.h"

namespace TD // trade data
{
    inline std::string getTypeString(const ReqMsgType& reqMsgType)
    {
        switch (reqMsgType)
        {
        case ReqMsgType::REQ_NEW_ORDER:
            return "REQ_NEW_ORDER";
        case ReqMsgType::REQ_ORDER_ACTION:
            return "REQ_ORDER_ACTION";
        case ReqMsgType::REQ_QRY_POSITION:
            return "REQ_QRY_POSITION";
        case ReqMsgType::REQ_QRY_TRADE_INFO:
            return "REQ_QRY_TRADE_INFO";
        case ReqMsgType::REQ_QRY_CASH_ASSET:
            return "REQ_QRY_CASH_ASSET";
        case ReqMsgType::REQ_QRY_SEC_INFO:
            return "REQ_QRY_SEC_INFO";
        case ReqMsgType::REQ_QRY_ORDER_HISTORY:
            return "REQ_QRY_ORDER_HISTORY";
        case ReqMsgType::REQ_QRY_TRADE_HISTORY:
            return "REQ_QRY_TRADE_HISTORY";
        default:
            return "UNKNOWN";
        }
    }

    inline std::string getTypeString(const RtnMsgType& rtnMsgType)
    {
        switch (rtnMsgType)
        {
        case RtnMsgType::RTN_ORDER:
            return "RTN_ORDER";
        case RtnMsgType::RTN_TRADE:
            return "RTN_TRADE";
        case RtnMsgType::RTN_POSITION:
            return "RTN_POSITION";
        case RtnMsgType::RTN_TRADE_INFO:
            return "RTN_TRADE_INFO";
        case RtnMsgType::RTN_CASH_ASSET:
            return "RTN_CASH_ASSET";
        case RtnMsgType::RTN_SEC_INFO:
            return "RTN_SEC_INFO";
        case RtnMsgType::RTN_ORDER_HISTORY:
            return "RTN_ORDER_HISTORY";
        case RtnMsgType::RTN_TRADE_HISTORY:
            return "RTN_TRADE_HISTORY";
        case RtnMsgType::RTN_OPEN_VAL_CHANGE:
            return "RTN_OPEN_VAL_CHANGE";
        default:
            return "UNKNOWN";
        }
    }

    inline std::string getOrderStatus(const OrderStatus& order_status)
    {
        switch (order_status)
        {
        case TD::OrderStatus::Sended:
            return "Sended";
        case TD::OrderStatus::Submitted:
            return "Submitted";
        case TD::OrderStatus::Placed:
            return "Placed";
        case TD::OrderStatus::Cancelled:
            return "Cancelled";
        case TD::OrderStatus::Error:
            return "Error";
        case TD::OrderStatus::Rejected:
            return "Rejected";
        case TD::OrderStatus::PartialFilled:
            return "PartialFilled";
        case TD::OrderStatus::Filled:
            return "Filled";
        default:
            return "InvalidStatus";
        }
    }

    inline std::string getBSType(const BSType &bs_type)
    {
        switch(bs_type)
        {
        case TD::BSType::Buy:
            return "Buy";
        case TD::BSType::Sell:
            return "Sell";
        case TD::BSType::CancelOrder:
            return "Cancel";
        default: 
            return "Unknown";
        }
    }

    std::ostream& operator<<(std::ostream& ostream, const ReqMsgType& reqMsgType)
    {
        return ostream << getTypeString(reqMsgType);
    }

    std::ostream& operator<<(std::ostream& ostream, const RtnMsgType& rtnMsgType)
    {
        return ostream << getTypeString(rtnMsgType);
    }

    std::ostream& operator<<(std::ostream& ostream, const OrderStatus& order_status)
    {
        return ostream << getOrderStatus(order_status);
    }

}
