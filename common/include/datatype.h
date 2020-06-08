#include <stdint.h>
#ifndef DATATYPE_H
#define DATATYPE_H

typedef struct {
    int price;
    int vol;
    int seq_num;
    int last;
    int next;
} RBT_PV;

typedef struct {
    int idx_pv = -1;//idx_pv为-1，则表示没有这个价格的订单了，需要删除这个节点
    int idx_end;
    int vol = 0;
} RBT_NODE;

typedef struct {
    int suspend_max_order_count;
    RBT_PV* pv_data;
    int empty_head_idx;//空闲队列头
} ARR_CACHE;

typedef struct {
    int instrId;
    char code[32];
    int type;
    int price;//snapshot:open_price
    uint64_t vol; 
    int update_time;
    int direction;
    int64_t seq_num;
    uint64_t recv_nano;
    int pre_close;
    int bid_prices[10];
    int bid_vols[10];
    int ask_prices[10];
    int ask_vols[10];
    //最新成交价
    int last_price;
} PVO;

#ifndef NEW_TRADEMODULE

#define TYPE_ORDER 1
#define TYPE_TRADE 2
#define TYPE_CANCLE 3
#define TYPE_POSITION 4
#define TYPE_SNAPSHOT 5
#define TYPE_INDEX 6
#define TYPE_SNAPSHOT_L1 7

#define DIRECTION_BUY 1
#define DIRECTION_SELL 2

//======================OrderPriceType 报单类型==========================
///任意价
#define U_AnyPrice '1'
///限价
#define U_LimitPrice '2'

//======================Direction 买卖方向==========================
///买
#define U_Buy 'B'
///卖
#define U_Sell 'S'
///撤单
#define U_CancelOrder 'C'

//======================Date 持仓日期==========================
//今日
#define U_Today '1'
///昨日
#define U_Yesterday '2'



//=======================委托状态==============================
//订单拒绝
#define U_Reject 'r'
//未知
#define U_Unknown 'e'
//已发送
#define U_Sended 's'
//未成交还在队列中,柜台收到
#define U_In_Queue 'a'
//交易所确认订单
#define U_In_Exchange 'b'
//全部成交
#define U_Complete 'c'
//部分成交还在队列中
#define U_PartTraded 'p'
//撤单
#define U_Cancel 'd'



//策略相关信息占用的位数，用于算出内部OrderRef
#define STRATEGY_INFO_BIT_COUNT 15
//除进程index外策略相关信息占用的位数，用于从返回的OrderRef中获取index
#define STRATEGY_INFO_BIT_COUNT_EXINDEX 12
#define DEFAULT_ORDERREF_START 0x1

#define INNER_REF_BIT_COUNT (32 - STRATEGY_INFO_BIT_COUNT)
//策略进程index
#define STRATEGY_INDEX_MASK ((0xFFFFFFFF << STRATEGY_INFO_BIT_COUNT_EXINDEX) & (0xFFFFFFFF >> INNER_REF_BIT_COUNT))
#define STRATEGY_CTX_MASK (0xFFFFFFFF >> (INNER_REF_BIT_COUNT + STRATEGY_INFO_BIT_COUNT - STRATEGY_INFO_BIT_COUNT_EXINDEX))
#define INNER_ORDERREF_MASK (0xFFFFFFFF << STRATEGY_INFO_BIT_COUNT)
#define TOTAL_STRATEGY_PROCESS_COUNT ((STRATEGY_INDEX_MASK >> STRATEGY_INFO_BIT_COUNT_EXINDEX) + 1)
#define MAX_SUSPEND_COUNT (STRATEGY_CTX_MASK + 1)
#define SYS_MIN_REF (DEFAULT_ORDERREF_START << STRATEGY_INFO_BIT_COUNT)
#define getIndex(OrderRef) ((OrderRef & STRATEGY_INDEX_MASK) >> STRATEGY_INFO_BIT_COUNT_EXINDEX)

#define RTN_MEMQUEUE_LEN 65536
//#define REQ_MEMQUEUE_LEN 256
#define REQ_MEMQUEUE_LEN 4096

#define INSTRUMENTID_LEN_MAX 18

#define SUCCESS 0
#define CANCEL_LATE 1
#define CANCEL_ERROR 2
#define NOT_IMPL -1

#define QRY_RTN_CONTINUE 0
#define QRY_RTN_EOF 1
//报单
struct InputOrderField {
    char	InstrumentID[32];

    ///报单引用
    unsigned int	OrderRef;
    ///买卖方向
    char	Direction;
    ///价格
    int	LimitPrice;
    ///数量
    int	Volume;
    //已成交数量
    int TradedVolume;
    unsigned long int update_time;
        ///报单状态
    char	OrderStatus;
    int GetSuspendedVolume() const {
        return Volume - TradedVolume;
    }
};
//撤单结构体
struct CancelField {
    ///报单状态
    char	OrderStatus;
    char	InstrumentID[INSTRUMENTID_LEN_MAX]; 
    unsigned int	OrderRef;
    unsigned int	Orig_OrderRef;
};



typedef enum JQSecurityType {
    JQ_SECURITY_TYPE_UNDEFINED             = 0,
    JQ_SECURITY_TYPE_STOCK                 = 1,        /**< 股票 */
    JQ_SECURITY_TYPE_BOND                  = 2,        /**< 债券 */
    JQ_SECURITY_TYPE_ETF                   = 3,        /**< ETF */
    JQ_SECURITY_TYPE_FUND                  = 4,        /**< 基金 */
    JQ_SECURITY_TYPE_OPTION                = 5,        /**< 期权 */
    JQ_SECURITY_TYPE_MAX_                = 6,        /**< 期权 */
} JQSecurityType;

typedef enum JQMarketId {
    JQ_MKT_SH_ASHARE                       = 1,        /**< 上海A股 */
    JQ_MKT_SZ_ASHARE                       = 2,        /**< 深圳A股 */
    JQ_MKT_SH_OPTION                       = 3,        /**< 上海期权 */
} JQMarketId;

struct QryDataField {
    char	InstrumentID[INSTRUMENTID_LEN_MAX];
    int  securiryType;
    int marketId;
};

struct RtnSecurityInfo {
    char                InstrumentID[INSTRUMENTID_LEN_MAX];
    int               mktId;
    int               securityType;
    //涨停价
    int               ceilPrice;
    //跌停价
    int               floorPrice;
};

//委托回报
struct RtnOrderField {
    ///合约代码
    char	InstrumentID[INSTRUMENTID_LEN_MAX];
    ///报单引用
    unsigned int	OrderRef;
    ///买卖方向
    char	Direction;
    char    BsType;
    ///报单编号
    char	OrderNo[21];
    ///开平标志
    char	OffsetFlag;
    ///价格
    double	LimitPrice;
    ///报单状态
    char	OrderStatus;
    ///数量
    int	VolumeOriginal;
    ///今成交数量
    int	VolumeTraded;
    ///剩余数量
    int	VolumeRemain;
    int OrdTime; 
    int OrdCnfmTime;

};

//struct RspOrderField
//{
    //RtnOrderField RtnOrder;
    //bool brtn_valid;
    //bool bLast;
//};

//成交回报
struct RtnTradeField {
    ///合约代码
    char	InstrumentID[18];
    ///报单引用
    unsigned int	OrderRef;
    ///买卖方向
    char	Direction;
    ///报单编号
    char	OrderNo[21];
    ///开平标志
    char	OffsetFlag;
    ///价格
    double	Price;
    ///数量
    int	Volume;
    ///成交时间
    int	TrdTime;
};

//投资者持仓回报结构体
struct PositionField
{
    ///合约代码
    char	InstrumentID[18];
    ///日初持仓
    int64_t	InitPosition; 
    //持仓日期
    //char Date;
    ///持仓多空方向
    char	PosiDirection;
    ///今日累计买入
    int64_t	TodayBuyVol;
    ///今日累计卖出
    int64_t	TodaySellVol;    
    ///今日持仓
    int64_t	TodayPosition;
    ///总持仓
    int64_t	Position;
    int64_t CostPrice;
    
};

struct RtnTraderInfoField {
    uint32_t LastOrderRef;
    uint32_t TradeDate;
};

struct RtnCashAssetField {
    uint64_t CashAvailable;    
    char Account[32];        
};

struct RtnTradeHistory {
    char InstrumentID[INSTRUMENTID_LEN_MAX];   
    char Direction; 
    uint32_t OrderRef;    
    int	Price;
    int	Volume;

};


struct RtnOrderHistory {  
    char InstrumentID[INSTRUMENTID_LEN_MAX];
    ///买卖方向
    char Direction;
    char BsType;
    ///报单状态
    uint32_t OrderRef;
    char OrderStatus;
    char OrderCompleted;   
    ///价格
    int	Price;
    ///数量
    int	Volume;
    int	VolumeTraded;
    int	CanceledVolume;
};

struct RtnOpenValChange {
    uint64_t cur_traded_val;
    uint64_t cur_open_val;
    uint64_t limit_open_val;
};

enum err_type_t { ET_NORMAL,ET_CANCEL_LATE,ET_CANCEL_ERROR };
struct RtnErrorField {
    ///报单引用
    unsigned int OrderRef;
    char contract[50];
    int type;
    ///错误代码
    int	ErrorID;
    ///错误信息
    char ErrorMsg[100];
};


enum REQ_TYPE {
    REQ_INPUT, REQ_CANCEL, REQ_POSITION, REQ_PENDING, REQ_TRADER_INFO, REQ_CASHASSET, REQ_ORDER_HISTORY, REQ_TRADE_HISTORY, REQ_SECURITY_INFO
};

enum RTN_TYPE {
    RTN_ORDER, RTN_TRADE, RTN_POSITION, RTN_ERROR, RTN_PENDING, RTN_TRADER_INFO,RTN_CASHASSET,RTN_ORDER_HISTORY,RTN_TRADE_HISTORY,RTN_OPEN_VAL_CHANGE, RTN_SECURITY_INFO
};

#define CACHE_LINE_SIZE 64

struct Trader_Req_Field {
  int type __attribute__((aligned(CACHE_LINE_SIZE))); // 0--InputOrderField 1--CancelField
  ///请求编号
  int requestID;
  union {
    struct InputOrderField input;
    struct CancelField cancel;
    struct QryDataField qryData;
  } data; // access with some_info_object.data.a or some_info_object.data.b
};

struct Trader_Rtn_Field {
    Trader_Rtn_Field(){};
    int type __attribute__((aligned(CACHE_LINE_SIZE)));
    ///请求编号
    unsigned int requestID;
    //针对qry的请求的返回，判断是否是最后一条数据
    bool is_last ;
    uint64_t trade_recv_order;
    uint64_t trade_recv_desk;
    uint64_t trade_recv_exchange;
    union {
      struct RtnOrderField rtnOrder;
      struct RtnTradeField rtnTrade;
      struct PositionField position;
      struct RtnErrorField rtnError;
      struct RtnTraderInfoField rtnTraderInfo;
      struct RtnCashAssetField rtnCasshAssert;
      struct RtnTradeHistory rtnTradeHistory;
      struct RtnOrderHistory rtnOrderHistory; 
      struct RtnOpenValChange rtnOpenValChange;
      struct RtnSecurityInfo rtnSecurityInfo;
    } data;
};
#else
#include "tradedata.h"
#endif //end of NEW_TRADEMODULE

#endif /* DATATYPE_H */

