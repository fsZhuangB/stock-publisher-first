/**
 * @file    tradedata.h
 *
 * 交易代理的基础数据结构定义
 *
 * @version 0.1.1      2019/09/20
 *          - 定义了用于上游策略模块与交易代理之间交互的基础数据结构
 **/

#include <stdint.h>
#include <string>
#include <iostream>
#ifndef TRADE_DATA_TYPE_H
#define TRADE_DATA_TYPE_H

namespace TD // trade data
{
    //订单编号order_id被用于策略模块/交易代理/柜台API之间关联订单请求
    //32位订单编号order_id中相关bit位数分配及含义
    //bit 31 30 29 ...........15  14  13  12   11 10 ....0
    //   [ 交易代理内部递增数    ][策略进程索引][ 策略订单号 ]
    //策略进程索引号为bit12~14, 共3位，实际支持的最大策略进程数为7个，因为需要最大数7保留为内部使用

#define STRATEGY_INFO_BIT_COUNT 15
//除进程index外策略相关信息占用的位数，用于从返回的order_id中获取index
#define STRATEGY_INFO_BIT_COUNT_EXINDEX 12
#define DEFAULT_ORDERREF_START 0x1

//定义用于辅助获得策略进程index的宏
#define INNER_REF_BIT_COUNT (32 - STRATEGY_INFO_BIT_COUNT)
#define STRATEGY_INDEX_MASK ((0xFFFFFFFF << STRATEGY_INFO_BIT_COUNT_EXINDEX) & (0xFFFFFFFF >> INNER_REF_BIT_COUNT))
#define STRATEGY_CTX_MASK (0xFFFFFFFF >> (INNER_REF_BIT_COUNT + STRATEGY_INFO_BIT_COUNT - STRATEGY_INFO_BIT_COUNT_EXINDEX))
#define INNER_ORDERREF_MASK (0xFFFFFFFF << STRATEGY_INFO_BIT_COUNT)
#define TOTAL_STRATEGY_PROCESS_COUNT ((STRATEGY_INDEX_MASK >> STRATEGY_INFO_BIT_COUNT_EXINDEX) + 1)
#define MAX_SUSPEND_COUNT (STRATEGY_CTX_MASK + 1)
#define SYS_MIN_REF (DEFAULT_ORDERREF_START << STRATEGY_INFO_BIT_COUNT)
//从订单号中取得策略进程索引
#define GET_STRATEGY_ID(order_id) ((order_id & STRATEGY_INDEX_MASK) >> STRATEGY_INFO_BIT_COUNT_EXINDEX)

#define CACHE_LINE_SIZE 64			        //缓存行长度

    constexpr int MAX_STRATEGY = 8;             //最大策略数目+1
    constexpr int MAX_TRADER = 16;              //最大交易账号数目
    constexpr int INSTRUMENT_ID_LEN = 32;		//合约代码长度
    constexpr int ACCOUNT_ID_LEN = 32;			//资金账号长度
    constexpr int ERROR_MSG_LEN = 128;			//错误消息字符串长度
    constexpr int QUEUE_NAME_LEN = 128;			//队列名称字符串长度
    constexpr int QRY_RTN_CONTINUE = 0;			//查询回报非结尾标志
    constexpr int QRY_RTN_EOF = 1;      		//查询回报结尾标志

//======================BSType 买卖类型==========================
enum class BSType : int8_t
{
    Unknown = '0',
    Buy,		//买
    Sell,		//卖
    CancelOrder //撤单
};

//======================Offset 开平方向==========================
enum class Offset : int8_t
{
    Unknown = '0',
    Open,
    Close,
    CloseToday,
    CloseYesterday
};

//======================Direction 多空方向==========================
enum class Direction : int8_t
{
    Unknown = '0',
    Long,
    Short
};

enum class OrderActionFlag : int8_t
{
    Cancel = '0',
    Update
};

/**
| 报单类型 |  上交所  |  深交所  | 上期所 |  中金所  |  大商所  |  郑商所  |
| :----: | :----: | :----: | :----: | :----: | :----: | :----: |
| Limit |限价|限价|限价|限价|限价|限价|
| Any |最优五档剩余撤销|即时成交剩余撤销|市价|市价|市价|市价|
| FakBest5 |最优五档即时成交剩余撤销|最优五档即时成交剩余撤销|不支持|不支持|不支持|不支持|
| ForwardBest |最优五档即时成交剩余转限价|对手方最优价格申报|不支持|不支持|不支持|不支持|
| ReverseBest |本方最优价格申报|不支持|不支持|不支持|不支持|不支持|
| Fak |不支持|(市价)即时成交剩余撤销|(限价)即时成交剩余撤销|(限价)即时成交剩余撤销|(限价)即时成交剩余撤销|(限价)即时成交剩余撤销|
| Fok |不支持|(市价)全额成交或者撤销|(限价)全额成交或者撤销|(限价)全额成交或者撤销|(限价)全额成交或者撤销|(限价)全额成交或者撤销|

期货fok与fak
报单价格为限价，报单时间和交易量条件如下

| 报单类型 | PriceType  |  TimeCondition  |  VolumeCondition  |
| :----: | :----: | :----: | :----: |
| Fok |Limit|IOC|All|
| Fak |Limit|IOC|Any|
**/

//======================OrderType 报单类型==========================
enum class OrderType : int8_t
{
    UnKnown = '0',
    Limit,                  //限价,证券通用
    Market,                 //市价，证券通用，对于股票上海为最优五档剩余撤销，深圳为即时成交剩余撤销
    FakBest5,               //上海深圳最优五档即时成交剩余撤销，不需要报价
    ForwardBest,            //深圳本方最优价格申报, 不需要报价
    ReverseBest,            //上海最优五档即时成交剩余转限价, 深圳对手方最优价格申报，不需要报价
    Fak,                    //深圳即时成交剩余撤销，不需要报价
    Fok                     //深圳市价全额成交或者撤销，不需要报价
};

//=======================订单状态==============================
enum class OrderStatus : int8_t
{
    Unknown = '0',	//未知
    Sended,			//已发送到交易代理
    Submitted,		//交易已提交到柜台
    Placed,			//柜台通知订单已被交易所确认
    Cancelled,		//订单已撤单
    Error,			//订单出错
    Rejected,		//订单拒绝
    PartialFilled,  //部分成交
    Filled			//全部成交
};

enum class InstrumentType : int8_t
{
    Unknown = '0',
    Stock,      //股票
    Bond,		//债券
    ETF,		//ETF
    Fund,		//基金
    ETFOption,  //ETF期权
    StockOption,//个股期权
    FutureOption//期货期权
};

enum class MarketId : int8_t
{
    Unknown = '0',
    MKT_SH_ASHARE,        //上海A股
    MKT_SZ_ASHARE,        //深圳A股
    MKT_SH_OPTION,        //上海期权
};

//新报单/新订单
struct NewOrderField
{
	char instrument_id[INSTRUMENT_ID_LEN];		//合约代码，A股股票只含有数字部分，不含前缀“SH” 和“SZ”
	unsigned int order_id;						//订单编号/报单引用
    InstrumentType instrument_type;				//合约类型
    MarketId market_id;							//市场id
	BSType side;								//买卖方向
	Offset offset;								//开平方向
	OrderType order_type;						//下单类型
	OrderStatus order_status;					//报单状态
	int limit_price;							//委托价格, 单位精确到元后四位, 即1元 = 10000
	int64_t quantity;							//委托数量, 单位：股，已经对齐到100的整数倍
	int64_t filled_quantity;					//已成交数量
	int64_t update_time;						//内部订单状态更新时间戳，纳秒级，形如 1560144011373015000
};

//订单操作（撤单/改单等）
struct OrderActionField
{
	char instrument_id[INSTRUMENT_ID_LEN];		//合约代码，A股股票只含有数字部分，不含前缀“SH” 和“SZ”
	unsigned int order_id;						//本订单编号/报单引用
	unsigned int action_order_id;				//待操作的订单编号/报单引用
	OrderActionFlag action_flag;				//订单操作类型
    InstrumentType instrument_type;				//合约类型
    MarketId market_id;							//市场id
	BSType side;								//买卖方向
	Offset offset;								//开平方向
	OrderType order_type;						//下单类型
	int limit_price;							//委托价格, 单位精确到元后四位, 即1元 = 10000
	int64_t quantity;							//委托数量, 单位： 股，已经对齐到100的整数倍
};

//查询请求的数据字段
struct QueryDataField
{
    char instrument_id[INSTRUMENT_ID_LEN];		//合约代码
	InstrumentType instrument_type;				//合约类型
	MarketId market_id;							//市场id
};

enum class Status : int8_t
{
	OK = 0,
	ERROR
};

//返回证券信息的回报字段
struct RtnSecInfoField
{
    char instrument_id[INSTRUMENT_ID_LEN];		//合约代码
	Status status;								//回报执行状态
    InstrumentType instrument_type;				//合约类型
	MarketId market_id;							//市场id
    int ceil_price;								//涨停价, 单位精确到元后四位, 即1元 = 10000
    int floor_price;							//跌停价, 单位精确到元后四位, 即1元 = 10000
	bool is_last;								//是否最后一条消息
	int error_id;								//错误id
};

//委托回报字段
struct RtnOrderField
{
    char instrument_id[INSTRUMENT_ID_LEN];		//合约代码
	unsigned int order_id;						//订单编号/报单引用
    InstrumentType instrument_type;				//合约类型
	BSType side;								//买卖方向
	Offset offset;								//开平方向
	OrderType order_type;						//下单类型
	OrderStatus order_status;					//报单状态
	int limit_price;							//价格, 单位精确到元后四位, 即1元 = 10000
	int64_t quantity;							//数量
	int filled_quantity;						//已成交数量
	int leave_quantity;							//剩余未成交数量
	int64_t update_time;						//内部订单状态更新时间戳，纳秒级，形如 1569578501097222774
	int order_time;								//从柜台返回的订单委托时间 (格式为 HHMMSSsss, 形如 141205000)
	int confirmed_time;							//从柜台返回的订单委托确认时间 (格式为 HHMMSSsss, 形如 141206000)
	int error_id;								//错误ID
};

//成交回报字段
struct RtnTradeField
{
    char instrument_id[INSTRUMENT_ID_LEN];		//合约代码
	unsigned int order_id;						//订单编号/报单引用
    InstrumentType instrument_type;				//合约类型
	BSType side;								//买卖方向
	Offset offset;								//开平方向
	OrderType order_type;						//下单类型
	OrderStatus order_status;					//报单状态
	int price;									//成交价格, 单位精确到元后四位, 即1元 = 10000
	int64_t quantity;							//成交数量
	int64_t filled_quantity;					//已成交数量
	int64_t leave_quantity;						//剩余未成交数量
	int64_t update_time;						//内部订单状态更新时间戳，纳秒级，形如 1569578501097222774
	int execution_time;							//从柜台返回的订单成交时间 (格式为 HHMMSSsss, 形如 141205000)
};

//投资者持仓回报结构体
struct RtnPositionField
{
	char instrument_id[INSTRUMENT_ID_LEN];		//合约代码
	Status status;								//回报执行状态
	int64_t total_quantity;						//总持仓
	int64_t cost_price;							//持仓成本价
	int64_t yesterday_quantity;					//日初持仓/昨仓数量
    int64_t today_buy_quantity;					//今日累计买入
    int64_t today_sell_quantity;				//今日累计卖出
	InstrumentType instrument_type;				//合约类型
	BSType side;								//持仓方向
	bool is_last;								//是否最后一条消息
	int error_id;								//错误id
};

//策略下单信息回报字段
struct RtnTradeInfoField
{
	unsigned int last_order_id;					//某一策略的最新下单编号（低12位全部置为0）
	unsigned int trade_date;					//交易日期，形如20190928
};

//账户信息回报字段
struct RtnCashAssetField
{
	char account[ACCOUNT_ID_LEN];			//资金账号
	Status status;								//回报执行状态
	int64_t total_cash;							//当前总余额，单位精确到元后四位, 即1元 = 10000
	int64_t avail_cash;							//当前可用余额，单位精确到元后四位, 即1元 = 10000
	bool is_last;								//是否最后一条消息
	int error_id;								//错误id
};

//历史成交信息回报字段
struct RtnTradeHistory
{
	char instrument_id[INSTRUMENT_ID_LEN];		//合约代码
	Status status;								//回报执行状态
	unsigned int order_id;						//订单编号/报单引用
    InstrumentType instrument_type;				//合约类型
	BSType side;								//买卖方向
	Offset offset;								//开平方向(期货)
	int price;									//成交价格, 单位精确到元后四位, 即1元 = 10000
	int64_t quantity;							//成交数量
	int execution_time;							//从柜台返回的订单成交时间 (格式为 HHMMSSsss, 形如 141205000)
	bool is_last;								//是否最后一条消息
	int error_id;								//错误id
};

//订单历史回报字段
struct RtnOrderHistory
{
	char instrument_id[INSTRUMENT_ID_LEN];		//合约代码
	Status status;								//回报执行状态
	unsigned int order_id;						//订单编号/报单引用
    InstrumentType instrument_type;				//合约类型
	BSType side;								//买卖方向
	Offset offset;								//开平方向
	OrderType order_type;						//下单类型
	OrderStatus order_status;					//报单状态
	char order_completed_flag;					//订单结束标志, 1:结束，0：未结束
	int price;							        //委托价格, 单位精确到元后四位, 即1元 = 10000
	int64_t quantity;							//委托数量
	int filled_quantity;						//已成交数量
	int cancelled_quantity;						//已撤单数量
	bool is_last;								//是否最后一条消息
	int error_id;								//错误id
};

//实时风控指标回报字段
struct RtnOpenValChange
{
    uint64_t curr_traded_value;					//当前策略全部合约的交易成交总金额
    uint64_t curr_open_value;					//当前策略全部合约的持仓和开仓挂单总金额
    uint64_t limit_open_value;					//策略持仓总金额限制
};

//请求消息类型定义
enum class ReqMsgType : int32_t
{
	REQ_NEW_ORDER = 0,					//下单输入/新订单,
	REQ_ORDER_ACTION,						//订单修改（撤单or改单）
											//对应的回报消息 RTN_ORDER 订单委托回报消息
											//				RTN_TRADE 订单成交回报消息

	REQ_QRY_POSITION,						//查询持仓
											//对应的回报消息 RTN_POSITION 持仓回报

	REQ_QRY_TRADE_INFO,						//查询内部交易信息（比如内部订单号etc）
											//对应的回报消息 RTN_TRADE_INFO 内部交易信息回报

	REQ_QRY_CASH_ASSET,						//查询账户
											//对应的回报消息 RTN_CASH_ASSET 账户回报

	REQ_QRY_SEC_INFO,						//查询证券品种信息
											//对应的回报消息 RTN_SEC_INFO 证券品种信息回报

	REQ_QRY_ORDER_HISTORY,					//查询订单历史信息
											//对应的回报消息 RTN_ORDER_HISTORY 订单历史信息回报

	REQ_QRY_TRADE_HISTORY,					//查询成交历史信息
											//对应的回报消息 RTN_TRADE_HISTORY 成交历史信息回报
};

//回报消息类型定义
enum class RtnMsgType : int32_t
{
	RTN_ORDER = 0,						//订单委托回报消息
	RTN_TRADE,								//订单成交回报消息
	RTN_POSITION,							//持仓回报
	RTN_TRADE_INFO,							//内部交易信息回报
	RTN_CASH_ASSET,							//账户回报
	RTN_SEC_INFO,							//证券品种信息回报
	RTN_ORDER_HISTORY,						//订单历史信息回报
	RTN_TRADE_HISTORY,						//成交历史信息回报
    RTN_OPEN_VAL_CHANGE                     //持仓金额信息回报
};

std::string getTypeString(const ReqMsgType& reqMsgType);
std::string getTypeString(const RtnMsgType& rtnMsgType);

std::string getOrderStatus(const OrderStatus& order_status);
std::string getBSType(const BSType& bs_type);

std::ostream& operator<<(std::ostream& ostream, const ReqMsgType& reqMsgType);
std::ostream& operator<<(std::ostream& ostream, const RtnMsgType& rtnMsgType);
std::ostream& operator<<(std::ostream& ostream, const OrderStatus& order_status);

struct TradeReqMsg
{
	ReqMsgType type __attribute__( ( aligned( CACHE_LINE_SIZE ) ) );//消息类型
    int request_id;							//请求编号
    int dest_account_id;                   //请求对应的账号ID
    union
    {
        struct NewOrderField new_order;
        struct OrderActionField order_action;
        struct QueryDataField qry_data;
    } data; // access with some_info_object.data.a or some_info_object.data.b
    int reserved[4];                        //方便未来的字段扩充
};

struct TradeRtnMsg
{
	RtnMsgType type __attribute__( ( aligned( CACHE_LINE_SIZE ) ) );//消息类型
	int request_id;							//请求编号
    int dest_account_id;					//回报对应的账号ID
    union
    {
        struct RtnOrderField order;
        struct RtnTradeField trade;
        struct RtnPositionField position;
        struct RtnTradeInfoField trade_info;
        struct RtnCashAssetField asset;
        struct RtnTradeHistory trade_history;
        struct RtnOrderHistory order_history;
        struct RtnOpenValChange open_val_chg;                   
        struct RtnSecInfoField sec_info;
    } data;
    int reserved[4];                        //方便未来的字段扩充
};

//定义内部错误号码
enum ErrorType
{
    ERROR_ID_START = 10000,         //起始错误号
    REQ_SEND_FAILURE,               //请求发送失败
};
}; // end of namespace TD

#endif /* TRADE_DATA_TYPE_H */