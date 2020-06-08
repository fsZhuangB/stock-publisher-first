/**
 *源程序名称:sdk_tag.h
 *软件著作权:恒生电子股份有限公司
 *系统名称:H5行情协议
 *模块名称:H5行情协议
 *功能说明:定义H5行情协议中的字段TAG
 *作    者: 彭小豪
 *开发日期: 2018/9/20 13:18:48
 *版 本 号: 1.0.0.127
 *备    注: 根据文档《H5行情服务协议(修订版).xls》生成
 */

#ifndef __H5_SDK_TAG_H__
#define __H5_SDK_TAG_H__

#include "hscomm_message_interface.h"

#define MESSAGE_TEMPLATE_VERSION	"1.0.0.127"


/*****************功能消息域定义*******************/
const int H5PROTO_HEAD_INFO = 0 ; // 
const int H5SDK_MSG_LOGIN = 1001 ; // 登入请求
const int H5SDK_MSG_LOGOUT = 1002 ; // 登出信息
const int H5SDK_MSG_HEARTBEAT = 1003 ; // 心跳
const int H5SDK_SERVER_INFO = 1004 ; // 请求服务器信息
const int H5SDK_MSG_BATCH = 1006 ; // 批处理
const int H5SDK_MSG_REGISTER = 1005 ; // 注册请求
const int H5SDK_MSG_CHANGE_USER_INFO = 1007 ; // 修改用户信息
const int H5SDK_MSG_USER_KICK_OFF = 1008 ; // 行情服务器主动踢人消息（主推）
const int H5SDK_MSG_PUSH_USER_AUTH = 1009 ; // 客户端权限变更（主推）
const int H5SDK_MSG_PUSH_USER_REQ = 1010 ; // 客户端权限请求
const int H5SDK_MSG_CLIENT_INFO = 1011 ; // 客户端信息查询
const int H5SDK_MSG_FILE = 2001 ; // 请求静态文件
const int H5SDK_MSG_MARKET_TYPES = 2002 ; // 市场分类信息
const int H5SDK_MSG_MARKET_REFERENCE = 2003 ; // 市场代码表
const int H5SDK_MSG_UNDERLYING_CODE = 2004 ; // 通过代码查找关联代码
const int H5SDK_MSG_EXER = 2005 ; // 除权信息
const int H5SDK_MSG_F10_INDEX = 2006 ; // 资讯信息索引
const int H5SDK_MSG_F10_TXT = 2007 ; // 资讯内容
const int H5SDK_MSG_CODE_PROPERTY = 2008 ; // 商品属性信息
const int H5SDK_MSG_EXER_BY_DATE = 2009 ; // 按日期查询除权信息
const int H5SDK_MSG_USER_INFOSHEET = 2010 ; // 获取用户信息
const int H5SDK_MSG_EXER_EXT = 2011 ; // 拓展除权信息
const int H5SDK_MSG_SNAPSHOT = 3001 ; // 行情快照
const int H5SDK_KEYBOARD_WIZARD = 3002 ; // 键盘精灵消息
const int H5SDK_MSG_L2_TRANSCATION = 3003 ; // 逐笔成交
const int H5SDK_MSG_L2_ORDER = 3004 ; // 逐笔委托
const int H5SDK_MSG_NEEQ_XYZRSB = 3005 ; // 新三板协议转让申报
const int H5SDK_MSG_HK_BROKER_QUEUE = 3006 ; // 港股经纪队列
const int H5SDK_MSG_HK_VCM = 3007 ; // 港股市调
const int H5SDK_MSG_HK_CAS = 3008 ; // 港股收市竞价
const int H5SDK_MSG_THOUSAND_LEVEL_QUOTES_SNAPSHOT = 3009 ; // 千档行情档位快照
const int H5SDK_MSG_THOUSAND_LEVEL_QUOTES_DETAIL_ENTRUST_SNAPSHOT = 3010 ; // 千档行情详细委托队列快照
const int H5SDK_MSG_THOUSAND_LEVEL_QUOTES_DETAIL_ENTRUST_RANGE_SNAPSHOT = 3011 ; // 千档行情按档位查询详细委托队列
const int H5SDK_MSG_SUBSCRIBE = 4001 ; // 行情快照订阅
const int H5SDK_MSG_SUBSCRIBE_L2_TRANSCATION = 4002 ; // l2逐笔成交订阅
const int H5SDK_MSG_SUBSCRIBE_L2_ORDER = 4003 ; // l2逐笔委托订阅
const int H5SDK_MSG_SUBSCRIBE_NEEQ_XYZRSB = 4004 ; // 新三板协议转让申报订阅
const int H5SDK_MSG_SUBSCRIBE_HK_BQ = 4005 ; // 港股经纪队列订阅
const int H5SDK_MSG_SUBSCRIBE_HK_VCM = 4006 ; // 港股市调订阅
const int H5SDK_MSG_SUBSCRIBE_HK_CAS = 4007 ; // 港股收市竞价订阅
const int H5SDK_MSG_SUBSCRIBE_L2_TRANSCATION_BY_MARKET = 4008 ; // 按市场订阅l2逐笔成交
const int H5SDK_MSG_SUBSCRIBE_L2_ORDER_BY_MARKET = 4009 ; // 按市场订阅l2逐笔委托
const int H5SDK_MSG_SUBSCRIBE_NEEQ_XYZRSB_BY_MARKET = 4010 ; // 按市场订阅新三板协议转让申报
const int H5SDK_MSG_SUBSCRIBE_BY_MARKET = 4011 ; // 按市场订阅行情快照
const int H5SDK_MSG_SUBSCRIBE_US_REALTIME = 4012 ; // 美股实时行情行情快照订阅
const int H5SDK_MSG_SUBSCRIBE_HK_BQ_BY_MARKET = 4013 ; // 按市场订阅港股经纪队列
const int H5SDK_MSG_SUBSCRIBE_HK_VCM_BY_MARKET = 4014 ; // 按市场订阅港股市调
const int H5SDK_MSG_SUBSCRIBE_HK_CAS_BY_MARKET = 4015 ; // 按市场订阅港股收市竞价
const int H5SDK_MSG_SUBSCRIBE_US_REALTIME_BY_MARKET = 4016 ; // 按市场订美股实时行情快照
const int H5SDK_MSG_SORT = 5001 ; // 排序请求
const int H5SDK_MSG_TREND = 6001 ; // 按指定的日期或偏移取分时数据
const int H5SDK_MSG_CANDLE_BY_OFFSET = 6002 ; // 按偏移取K线
const int H5SDK_MSG_CANDLE_BY_RANGE = 6003 ; // 按日期时间范围取K线
const int H5SDK_MSG_TICK_MIN = 6004 ; // 指定分钟的分笔
const int H5SDK_MSG_TICK_DIRECTION = 6005 ; // 按偏移取分笔
const int H5SDK_MSG_CANDLE_BY_RANGE_MAINTAIN = 6006 ; // 补线使用_分钟k线
const int H5SDK_MSG_DAY5_TREND = 6007 ; // 5日分时
const int H5SDK_MSG_TICK_SNAPSHOT = 6008 ; // snapshot tick表
const int H5SDK_MSG_HISTICK_SNAPSHOT_DATETIME = 6009 ; // 按时间取历史快照分笔
const int H5SDK_MSG_TICK_SNAPSHOT_DIRECTION = 6010 ; // 按偏移取分笔快照
const int H5SDK_MSG_HISTICK_SNAPSHOT_TRADE = 6011 ; // 按交易日取历史快照分笔
const int H5SDK_MSG_OCALLTICK_TRADEDAY = 6012 ; // 集合竟价的分笔
const int H5SDK_MSG_SETTLE_CANDLE_BY_RANGE = 6013 ; // 按日期时间范围取结算K线
const int H5SDK_MSG_SETTLE_CANDLE_BY_OFFSET = 6014 ; // 按偏移取结算K线
const int H5SDK_MSG_HISTICK_TRADE = 6015 ; // 按日期查找的分笔
const int H5SDK_MSG_REALTIME_TREND = 6016 ; // 获取实时或偏移取分时数据
const int H5SDK_MAINTAIN_RETURN = 7001 ; // 补线返回
const int H5SDK_MSG_CANDLE_BY_RANGE_EXT = 7002 ; // 按日期时间范围取K线(扩展)
const int H5SDK_MSG_BLOCK_SORT = 8001 ; // 板块成分股排序
const int H5SDK_MSG_STOCK_BLOCKS = 8002 ; // 通过代码查找所属板块集
const int H5SDK_MSG_ORDER_FUNDFLOW_SNAPSHOT = 9001 ; // 逐单资金流快照
const int H5SDK_MSG_SNAPSHOT_INDEX_CODESELECT = 9002 ; // 当日指标选股快照
const int H5SDK_MSG_SNAPSHOT_SHAPE_CODESELECT = 9003 ; // 当日K线形态选股快照
const int H5SDK_MSG_SNAPSHOT_INDEXRESONANCE_CODESELECT = 9004 ; // 当日指标共振选股快照
const int H5SDK_MSG_QUERY_MA_INFLEXION = 9005 ; // 查询均线拐点状态结果
const int H5SDK_MSG_MAX_WIN_RATE = 9006 ; // 查询胜率最高结果
const int H5SDK_MSG_MA_INFLEXION_TRADE_LIST = 9007 ; // 查询均线拐点交易状态股票集合
const int H5SDK_MSG_BLOCK_ORDER_FUNDFLOW_RANK_SNAPSHOT = 9008 ; // 查询板块逐单资金流排序
const int H5SDK_MSG_TRANS_FUNDFLOW_SNAPSHOT = 9009 ; // 逐笔资金流快照
const int H5SDK_MSG_BLOCK_TRANS_FUNDFLOW_RANK_SNAPSHOT = 9010 ; // 查询板块逐笔资金流排序
const int H5SDK_MSG_ORDER_FUNDFLOW_RANK_BY_CLASSIFY_SNAPSHOT = 9011 ; // 按分类进行逐单资金流排序(个股、板块分类)
const int H5SDK_MSG_TRANS_FUNDFLOW_RANK_BY_CLASSIFY_SNAPSHOT = 9012 ; // 按分类进行逐笔资金流排序(个股、板块分类)
const int H5SDK_MSG_QPLUS_MARKET_EXT_INFO = 9013 ; // 增值行情市场扩展信息
const int H5SDK_MSG_QPLUS_MARKET_EXT_TREND = 9014 ; // 增值行情市场扩展分时数据
const int H5SDK_MSG_MARKET_CHG_DIAGRAM = 9015 ; // 沪深市场的涨跌幅分布图
const int H5SDK_MSG_SNAPSHOT_RISE_FALL_COUNT = 9016 ; // 增值涨跌停家数快照表
const int H5SDK_MSG_FUNDFLOW_MIN_ORDER = 10001 ; // 按偏移天数或指定日期取分时分钟逐单资金流
const int H5SDK_MSG_FUNDFLOW_MIN_TRANS = 10002 ; // 按偏移天数或指定日期取分时分钟逐笔资金流
const int H5SDK_MSG_FUNDFLOW_MIN_DDE = 10003 ; // 按偏移天数或指定日期取分时分钟DDE资金流
const int H5SDK_MSG_FUNDFLOW_DAY_ORDER = 10004 ; // 按照日期范围取日线逐单资金流
const int H5SDK_MSG_FUNDFLOW_DAY_TRANS = 10005 ; // 按照日期范围取日线逐笔资金流
const int H5SDK_MSG_FUNDFLOW_DAY_DDE = 10006 ; // 按照日期范围取日线DDE资金流
const int H5SDK_MSG_INDEX_HIS_BACKTEST = 10007 ; // 取个股指标历史回测结果
const int H5SDK_MSG_INDEXRESONANCE_HIS_BACKTEST = 10008 ; // 取个股指标共振历史回测结果
const int H5SDK_MSG_KLINESHAPE_HIS_CODESELECT = 10009 ; // 查询个股历史K线形态选股结果
const int H5SDK_MSG_FUNDFLOW_DAY_ORDER_BY_OFFSET = 10010 ; // 按照偏移取日线逐单资金流
const int H5SDK_MSG_FUNDFLOW_DAY_TRANS_BY_OFFSET = 10011 ; // 按照偏移取日线逐笔资金流
const int H5SDK_MSG_FUNDFLOW_DAY_DDE_BY_OFFSET = 10012 ; // 按照偏移取日线DDE资金流
const int H5SDK_MSG_INDEX_BUY_SELL_POINT_LIST = 10013 ; // 按照指定日期范围买卖点日期列表
const int H5SDK_MSG_FUNDFLOW_DAY5_MIN_ORDER = 10014 ; // 5日分时分钟逐单资金流
const int H5SDK_MSG_FUNDFLOW_DAY5_MIN_TRANS = 10015 ; // 5日分时分钟逐笔资金流
const int H5SDK_MSG_FUNDFLOW_MIN_ORDER_EXT = 10016 ; // 按偏移天数或指定日期取分时分钟逐单资金流
const int H5SDK_MSG_FUNDFLOW_MIN_TRANS_EXT = 10017 ; // 按偏移天数或指定日期取分时分钟逐笔资金流
const int H5SDK_REQ_SUBCRIBE_LIST = 11001 ; // 请求订阅列表
const int H5SDK_MSG_CHECK_SESSION = 11002 ; // 检测zookeepersession
const int H5SDK_MSG_DEL_SESSION = 11003 ; // 通知zookeepersession删除
const int H5SDK_REQ_BACK_SERVER_INFO = 11004 ; // 请求服务器信息
const int H5SDK_MSG_SUPPORT_SIGNAL_LIST = 12001 ; // 服务器支持的异动信号列表
const int H5SDK_MSG_SUBSCRIBE_SIGNAL_BY_CODE = 12002 ; // 按代码订阅异动监控信号
const int H5SDK_MSG_SUBSCRIBE_SIGNAL_BY_MARKET = 12003 ; // 按市场订阅异动监控信号
const int H5SDK_MSG_SUBSCRIBE_SIGNAL_BY_BLOCK = 12004 ; // 按板块订阅异动监控信号
const int H5SDK_MSG_QUERY_SIGNAL_BY_TIME = 12005 ; // 按时间查询异动信号
const int H5SDK_MSG_QUERY_SIGNAL_BY_OFFSET = 12006 ; // 按偏移查询异动信号
const int H5SDK_MSG_SIGNAL_RESULT_FORMAT_MAPPING = 12007 ; // 获取信号结果信息格式对照表
const int H5SDK_MSG_MONITORING_SUBSCRIBE = 12008 ; // 批量智能盯盘订阅
const int H5SDK_MSG_MONITORING_UNSUBSCRIBE = 12009 ; // 批量智能盯盘退订
const int H5SDK_MSG_MONITORING_PUSH = 12010 ; // 智能盯盘推送
const int H5SDK_MSG_HQ_ANALYSIS_UPDOWN_DAYS_STATISTIC = 13001 ; // 连续涨跌停家数分析统计
const int H5SDK_MSG_HQ_ANALYSIS_UPDOWN_REASON = 13002 ; // 行情分析查询涨跌停原因
const int H5SDK_MSG_HQ_ANALYSIS_YESTERDAY_STATISTIC = 13003 ; // 昨日涨停今日分析
const int H5SDK_MSG_HQ_ANALYSIS_STOCK_HIS_STATISTIC = 13004 ; // 个股历史涨停统计分析
const int H5SDK_MSG_HQ_HOT_STATISTIC = 13005 ; // 行情热度统计
const int H5SDK_MSG_FILE_INDEX_BY_RANGE = 14001 ; // 按日查询数据文件索引信息
const int H5SDK_MSG_LOCAL_CANDLE_COUNT_BY_RANGE = 14002 ; // 按日获取本地缓存K线根数
const int H5SDK_MSG_LOCAL_CANDLE_BY_RANGE = 14003 ; // 按日查询本地缓存历史k线
const int H5SDK_MSG_DOWNLOAD_CANDLE_BY_RANGE = 14004 ; // 下载K线
const int H5SDK_MSG_REQ_CANDLE_BY_RANGE = 14005 ; // 请求K线
const int H5SDK_MSG_DEL_LOCAL_CANDLE_BY_RANGE = 14006 ; // 按代码删除本地缓存数据
const int H5SDK_MSG_GET_LOCAL_CANDLE_INFO = 14007 ; // 获取本地缓存数据信息
const int H5SDK_MSG_GET_CANDLE_INFO = 14008 ; // 获取数据信息
const int H5SDK_MSG_CLICK_PRICE = 20001 ; // 点击报价实时行情一档
const int H5SDK_MSG_CLICK_PRICE_TEN = 20002 ; // 点击报价实时行情十档
const int H5SDK_MSG_CLICK_PRICE_TEN_BROKER_QUEUE = 20003 ; // 点击报价实时行情十档和经济队列
const int H5SDK_MSG_PUSH_HK_CLICK = 20004 ; // 港股点击报价客户信息(推送)
const int H5SDK_MSG_HK_CLICK = 20005 ; // 港股点击报价客户信息请求


/*****************系统域定义*******************/

/// 数据类型：uint32(枚举); 域名：业务prod_code,用以找合适的模板
const int H5PROTO_TAG_BUSINESS_ID = 1 ;
    const uint32 BIZ_H5PROTO = 3 ; // H5行情服务协议

/// 数据类型：uint32(枚举); 域名：报文类型
const int H5PROTO_TAG_PACKET_TYPE = 3 ;
    const uint32 REQUEST = 0 ; // 请求
    const uint32 ANSWER = 1 ; // 应答
    const uint32 PUSH = 4 ; // 主推报文

/// 数据类型：uint32; 域名：功能号
const int H5PROTO_TAG_FUNCTION_ID = 5 ;

/// 数据类型：rawdata; 域名：客户端KEY
const int H5PROTO_TAG_USER_KEY = 7 ;

/// 数据类型：rawdata; 域名：会话号
const int H5PROTO_TAG_SESSION_ID = 8 ;

/// 数据类型：uint32; 域名：错误号
const int H5PROTO_TAG_ERROR_NO = 19 ;

/// 数据类型：bytevector; 域名：错误信息
const int H5PROTO_TAG_ERROR_INFO = 20 ;

/// 数据类型：array; 数组项缺省类型：uint32; 域名：发送者的标识信息,表示信息从哪个适配器的哪个通道的哪个连接获得,一般通信适配器在接收到消息后,负责IDX_CONNECTID和IDX_CHANNEL_INDEX这两个成员的
const int H5PROTO_TAG_SEND_INFO_ARRAY = 100 ;

/// 数据类型：array; 数组项缺省类型：uint32; 域名：处理时间，计算异步返回时间
const int H5PROTO_TAG_TIME_STAMP_ARRAY = 52 ;

/// 数据类型：uint32; 域名：批处理号
const int H5PROTO_TAG_BATCH_NO = 21 ;

/// 数据类型：uint32; 域名：同步调用编号
const int H5PROTO_TAG_SYNC_NO = 22 ;

/// 数据类型：rawdata; 域名：流水信息
const int H5PROTO_TAG_SERIAL_INFO = 23 ;


/*****************消息域定义*******************/

/// 数据类型：string; 域名：用户名
const int H5SDK_TAG_USER_NAME = 20001 ;

/// 数据类型：string; 域名：密码
const int H5SDK_TAG_PASSWORD = 20002 ;

/// 数据类型：string; 域名：动态密码
const int H5SDK_TAG_DYNMIC_PASSWORD = 20003 ;

/// 数据类型：bytevector; 域名：原始数据
const int H5SDK_TAG_ORGINAL_DATA = 96 ;

/// 数据类型：uint32; 域名：心跳间隔
const int H5SDK_TAG_HEARTBEAT_INTERVAL = 108 ;

/// 数据类型：uint32; 域名：SDK版本（如1.3.2.1）（103002001）
const int H5SDK_TAG_SDK_VERSION = 20005 ;

/// 数据类型：bytevector; 域名：操作系统版本
const int H5SDK_TAG_OS_VERSION = 20006 ;

/// 数据类型：bytevector; 域名：服务器名称
const int H5SDK_TAG_SERVER_NAME = 20007 ;

/// 数据类型：uint64; 域名：服务器时间。Unix时间戳
const int H5SDK_TAG_SERVER_TIME = 20008 ;

/// 数据类型：uint32; 域名：当前在线
const int H5SDK_TAG_CURR_ONLINE_COUNT = 20009 ;

/// 数据类型：uint32; 域名：最大在线
const int H5SDK_TAG_MAX_ONLINE_COUNT = 20010 ;

/// 数据类型：uint32(枚举); 域名：文件类型
const int H5SDK_TAG_HQ_FILE_TYPE = 20011 ;
    const uint32 H5SDK_ENUM_FT_COMMON_FILE = 0 ; // 普通文件。需要使用文件名、相对路径信息进行访问
    const uint32 H5SDK_ENUM_FT_FINDATA_FILE = 1 ; // 财务数据文件
    const uint32 H5SDK_ENUM_FT_EXRIGHT_FILE = 2 ; // 除权数据文件
    const uint32 H5SDK_ENUM_FT_INFO_CONFIG_FILE = 3 ; // 资讯配置文件
    const uint32 H5SDK_ENUM_FT_WELCOME_FILE = 4 ; // 欢迎文件
    const uint32 H5SDK_ENUM_FT_DYNAMIC_NEWS_FILE = 5 ; // 流动条信息文件
    const uint32 H5SDK_ENUM_FT_SYS_BLOCK_FILE = 6 ; // 系统板块文件
    const uint32 H5SDK_ENUM_FT_USR_BLOCK_FILE = 7 ; // 自定义板块文件
    const uint32 H5SDK_ENUM_FT_BLOCK_CODE_FILE = 8 ; // 板块组织关系文件
    const uint32 H5SDK_ENUM_FT_MARKET_MONITOR_CONFIG_FILE = 9 ; // 短线精灵配置文件
    const uint32 H5SDK_ENUM_FT_CALL_AUCTION_TIME_FILE = 10 ; // 集合竞价时段配置文件

/// 数据类型：bytevector; 域名：文件名称
const int H5SDK_TAG_HQ_FILE_NAME = 16001 ;

/// 数据类型：uint64; 域名：文件偏移
const int H5SDK_TAG_FILE_OFFSET = 20012 ;

/// 数据类型：uint32; 域名：文件长度
const int H5SDK_TAG_FILE_LENGTH = 20013 ;

/// 数据类型：uint32; 域名：成交时间
const int H5SDK_TAG_BUSINESS_TIME = 20014 ;

/// 数据类型：uint32; 域名：数据CRC
const int H5SDK_TAG_CRC = 20015 ;

/// 数据类型：uint32; 域名：错误号
const int H5SDK_TAG_ERROR_NO = 20016 ;

/// 数据类型：bytevector; 域名：错误描述字符串
const int H5SDK_TAG_ERROR_INFO = 20017 ;

/// 数据类型：bytevector; 域名：交易所代码
const int H5SDK_TAG_FINANCE_MIC = 20018 ;

/// 数据类型：bytevector; 域名：交易所名称
const int H5SDK_TAG_FINANCE_NAME = 20019 ;

/// 数据类型：uint32; 域名：市场日期
const int H5SDK_TAG_MARKET_DATE = 230 ;

/// 数据类型：uint32; 域名：交易日期
const int H5SDK_TAG_INIT_DATE = 75 ;

/// 数据类型：int32; 域名：时区
const int H5SDK_TAG_TIMEZONE = 20020 ;

/// 数据类型：uint8; 域名：夏令时标志
const int H5SDK_TAG_DST_FLAG = 20021 ;

/// 数据类型：sequence; 域名：类型重复组
const int H5SDK_TAG_TYPE_GRP = 20022 ;

/// 数据类型：sequence; 域名：排序类型重复组
const int H5SDK_TAG_SORT_TYPE_GRP = 20071 ;

/// 数据类型：bytevector; 域名：类型代码
const int H5SDK_TAG_HQ_TYPE_CODE = 167 ;

/// 数据类型：bytevector; 域名：类型名称
const int H5SDK_TAG_HQ_TYPE_NAME = 20023 ;

/// 数据类型：uint32; 域名：价格放大倍数
const int H5SDK_TAG_PRICE_SCALE = 20024 ;

/// 数据类型：sequence; 域名：交易时间段
const int H5SDK_TAG_TRADE_SECTION_GRP = 20025 ;

/// 数据类型：uint32; 域名：开市时间
const int H5SDK_TAG_OPEN_TIME = 20026 ;

/// 数据类型：uint32; 域名：闭市时间
const int H5SDK_TAG_CLOSE_TIME = 20027 ;

/// 数据类型：int64; 域名：昨收价
const int H5SDK_TAG_PRECLOSE_PX = 140 ;

/// 数据类型：int64; 域名：涨停价格
const int H5SDK_TAG_UP_PRICE = 20028 ;

/// 数据类型：int64; 域名：跌停价格
const int H5SDK_TAG_DOWN_PRICE = 20029 ;

/// 数据类型：uint8(枚举); 域名：行情等级-仅美股有效
const int H5SDK_TAG_HQ_LEVEL = 61 ;
    const uint8 H5SDK_ENUM_LEVEL_1 = 1 ; // 基础行情
    const uint8 H5SDK_ENUM_LEVEL_2 = 2 ; // 2级行情

/// 数据类型：sequence; 域名：股票集重复组
const int H5SDK_TAG_PROD_GRP = 20030 ;

/// 数据类型：sequence; 域名：排序股票集重复组
const int H5SDK_TAG_SORT_PROD_GRP = 20070 ;

/// 数据类型：bytevector; 域名：股票代码
const int H5SDK_TAG_PROD_CODE = 48 ;

/// 数据类型：string; 域名：行业代码
const int H5SDK_TAG_INDUSTRY_CODE = 20031 ;

/// 数据类型：string; 域名：货币
const int H5SDK_TAG_MONEY_TYPE = 20032 ;

/// 数据类型：uint32; 域名：时间戳
const int H5SDK_TAG_DATA_TIMESTAMP = 10178 ;

/// 数据类型：string; 域名：/*交易状态  START;   ///< 市场启动(初始化之后,集合竞价前)
   //  PRETR;   ///< 盘前
   //  OCALL;   ///< 开始集合竞价
   //  TRADE;   ///< 交易(连续撮合)
   //  HALT;    ///< 暂停交易
   //  SUSP;    ///< 停盘
   //  BREAK;   ///< 休市
   //  POSTR;   ///< 盘后
   //  ENDTR;   ///< 交易结束
   //  STOPT;   ///< 长期停盘，停盘n天,n>=1 
   //  DELISTED;///< 退市 */
const int H5SDK_TAG_TRADE_STATUS = 10135 ;

/// 数据类型：int64; 域名：开盘价
const int H5SDK_TAG_OPEN_PX = 10018 ;

/// 数据类型：int64; 域名：最新价
const int H5SDK_TAG_LAST_PX = 31 ;

/// 数据类型：int64; 域名：最高价
const int H5SDK_TAG_HIGH_PX = 332 ;

/// 数据类型：int64; 域名：最低价
const int H5SDK_TAG_LOW_PX = 333 ;

/// 数据类型：int64; 域名：收盘价
const int H5SDK_TAG_CLOSE_PX = 10204 ;

/// 数据类型：int64; 域名：平均价
const int H5SDK_TAG_AVG_PX = 49 ;

/// 数据类型：int64; 域名：加权平均价
const int H5SDK_TAG_WAVG_PX = 50 ;

/// 数据类型：uint32; 域名：成交笔数
const int H5SDK_TAG_BUSINESS_COUNT = 8503 ;

/// 数据类型：uint64; 域名：成交量
const int H5SDK_TAG_BUSINESS_AMOUNT = 387 ;

/// 数据类型：uint64; 域名：成交额
const int H5SDK_TAG_BUSINESS_BALANCE = 8504 ;

/// 数据类型：uint64; 域名：现手
const int H5SDK_TAG_CURRENT_AMOUNT = 30 ;

/// 数据类型：uint64; 域名：内盘成交量
const int H5SDK_TAG_BUSINESS_AMOUNT_IN = 20033 ;

/// 数据类型：uint64; 域名：外盘成交量
const int H5SDK_TAG_BUSINESS_AMOUNT_OUT = 20034 ;

/// 数据类型：uint64; 域名：总委买量
const int H5SDK_TAG_TOTAL_BUY_AMOUNT = 10043 ;

/// 数据类型：uint64; 域名：总委卖量
const int H5SDK_TAG_TOTAL_SELL_AMOUNT = 10044 ;

/// 数据类型：int64; 域名：加权平均委买价
const int H5SDK_TAG_WAVG_BID_PX = 10039 ;

/// 数据类型：int64; 域名：加权平均委卖价
const int H5SDK_TAG_WAVG_OFFER_PX = 10040 ;

/// 数据类型：sequence; 域名：委买档位
const int H5SDK_TAG_BID_GRP = 10068 ;

/// 数据类型：sequence; 域名：委卖档位
const int H5SDK_TAG_OFFER_GRP = 10069 ;

/// 数据类型：uint32; 域名：价格
const int H5SDK_TAG_HQ_PRICE = 44 ;

/// 数据类型：uint64; 域名：委托量
const int H5SDK_TAG_TOTAL_ENTRUST_AMOUNT = 39 ;

/// 数据类型：sequence; 域名：委托单重复组
const int H5SDK_TAG_ENTRUST_GRP = 73 ;

/// 数据类型：int64; 域名：委托价格
const int H5SDK_TAG_ENTRUST_PX = 20067 ;

/// 数据类型：uint32; 域名：委托单量
const int H5SDK_TAG_ENTRUST_AMOUNT = 38 ;

/// 数据类型：int64; 域名：52周最低价
const int H5SDK_TAG_WEEK52_LOW_PX = 20035 ;

/// 数据类型：int64; 域名：52周最高价
const int H5SDK_TAG_WEEK52_HIGH_PX = 20036 ;

/// 数据类型：int64; 域名：价格涨跌
const int H5SDK_TAG_PX_CHANGE = 20037 ;

/// 数据类型：int32; 域名：涨跌幅
const int H5SDK_TAG_PX_CHANGE_RATE = 20038 ;

/// 数据类型：int64; 域名：盘前/盘后价格
const int H5SDK_TAG_POPC_PX = 20039 ;

/// 数据类型：uint64; 域名：当前阶段的成交量
const int H5SDK_TAG_SESSION_VOLUMUE = 20040 ;

/// 数据类型：uint32; 域名：日期: YYYYMMDD，0：表示当前日期
const int H5SDK_TAG_DATE = 20041 ;

/// 数据类型：int32; 域名：日期偏移天数
const int H5SDK_TAG_DATE_OFFSET = 20042 ;

/// 数据类型：sequence; 域名：分时数据重复组
const int H5SDK_TAG_TREND_GRP = 20043 ;

/// 数据类型：uint32(枚举); 域名：K线周期
const int H5SDK_TAG_CANDLE_PEROID = 20044 ;
    const uint32 H5SDK_ENUM_PERIOD_NONE = 0 ; // 无周期
    const uint32 H5SDK_ENUM_PEROID_1MIN = 1 ; // 一分钟
    const uint32 H5SDK_ENUM_PEROID_5MIN = 2 ; // 5分钟
    const uint32 H5SDK_ENUM_PEROID_15MIN = 3 ; // 15分钟
    const uint32 H5SDK_ENUM_PEROID_30MIN = 4 ; // 30分钟
    const uint32 H5SDK_ENUM_PEROID_60MIN = 5 ; // 60分钟
    const uint32 H5SDK_ENUM_PEROID_DAY = 6 ; // 日线
    const uint32 H5SDK_ENUM_PEROID_WEEK = 7 ; // 周线
    const uint32 H5SDK_ENUM_PEROID_MONTH = 8 ; // 月线
    const uint32 H5SDK_ENUM_PEROID_YEAR = 9 ; // 年线
    const uint32 H5SDK_ENUM_PEROID_10SEC = 10 ; // 10秒
    const uint32 H5SDK_ENUM_PEROID_3MIN = 11 ; // 3分钟
    const uint32 H5SDK_ENUM_PEROID_10MIN = 12 ; // 10分钟
    const uint32 H5SDK_ENUM_PEROID_120MIN = 13 ; // 120分钟
    const uint32 H5SDK_ENUM_PEROID_240MIN = 14 ; // 240分钟
    const uint32 H5SDK_ENUM_PEROID_QUARTER = 15 ; // 季线

/// 数据类型：uint32(枚举); 域名：结算K线周期
const int H5SDK_TAG_SETTLE_CANDLE_PEROID = 20045 ;
    const uint32 H5SDK_ENUM_PEROID_SETTLEMENT_DAY = 106 ; // 日结算

/// 数据类型：uint8(枚举); 域名：K线搜索方向
const int H5SDK_TAG_DIRECTION = 20046 ;
    const uint8 H5SDK_ENUM_FORWARD = 1 ; // 向前
    const uint8 H5SDK_ENUM_BACKWARD = 2 ; // 向后

/// 数据类型：uint32; 域名：数据个数
const int H5SDK_TAG_DATA_COUNT = 20047 ;

/// 数据类型：uint32; 域名：起始日期,YYYYMMDD
const int H5SDK_TAG_START_DATE = 20048 ;

/// 数据类型：uint32; 域名：结束日期,YYYYMMDD
const int H5SDK_TAG_END_DATE = 20049 ;

/// 数据类型：sequence; 域名：K线重复组
const int H5SDK_TAG_CANDLE_GRP = 20050 ;

/// 数据类型：bytevector; 域名：访问TOKEN
const int H5SDK_TAG_HQ_TOKEN = 20051 ;

/// 数据类型：sequence; 域名：交易所重复组
const int H5SDK_TAG_FINANCE_GRP = 20052 ;

/// 数据类型：bytevector; 域名：退出原因
const int H5SDK_TAG_QUIT_REASON = 20053 ;

/// 数据类型：sequence; 域名：批
const int H5SDK_TAG_BATCH_GRP = 20055 ;

/// 数据类型：rawdata; 域名：子包
const int H5SDK_TAG_SUB_PACKET = 20056 ;

/// 数据类型：sequence; 域名：字段集重复组
const int H5SDK_TAG_FIELD_GRP = 20057 ;

/// 数据类型：bytevector; 域名：字段名称
const int H5SDK_TAG_FIELD_NAME = 20058 ;

/// 数据类型：bytevector; 域名：证券名称
const int H5SDK_TAG_PROD_NAME = 55 ;

/// 数据类型：uint32; 域名：委托单数
const int H5SDK_TAG_ENTRUST_COUNT = 10067 ;

/// 数据类型：uint32; 域名：交易分钟数
const int H5SDK_TAG_TRADE_MINS = 20059 ;

/// 数据类型：int32; 域名：交易阶段
const int H5SDK_TAG_TRADE_SECTION = 20060 ;

/// 数据类型：uint8(枚举); 域名：K线模式
const int H5SDK_TAG_CANDLE_MODE = 20061 ;
    const uint8 H5SDK_ENUM_CANDLE_ORIGINAL = 0 ; // 原始K线
    const uint8 H5SDK_ENUM_CANDLE_FORWARD = 1 ; // 前复权K线
    const uint8 H5SDK_ENUM_CANDLE_BACKWARD = 2 ; // 后复权K线
    const uint8 H5SDK_ENUM_CANDLE_FORWAEX = 3 ; // 前复权比例因子K线
    const uint8 H5SDK_ENUM_CANDLE_BACKWAEX = 4 ; // 后复权比例因子K线

/// 数据类型：uint32; 域名：最大值
const int H5SDK_TAG_MAX_VALUE = 20062 ;

/// 数据类型：uint64; 域名：总股本
const int H5SDK_TAG_TOTAL_SHARES = 20063 ;

/// 数据类型：int32; 域名：市盈率
const int H5SDK_TAG_PE_RATE = 20064 ;

/// 数据类型：sequence; 域名：市场重复组
const int H5SDK_FINANCE_MIC_GRP = 30065 ;

/// 数据类型：uint32(枚举); 域名：订阅还是退订, 如果是退订,允许SubscriberKey为空,表示该连接的所有已订阅信息都取消
const int H5SDK_TAG_SUB_TYPE = 13 ;
    const uint32 HSUB_ENUM_SUB_OVER = 0 ; // 覆盖订阅(当前客户端的订阅模式)
    const uint32 HSUB_ENUM_SUB = 1 ; // 追加订阅
    const uint32 HSUB_ENUM_UNSUB = 2 ; // 退订

/// 数据类型：uint32; 域名：起始位置
const int H5SDK_TAG_START_POS = 50002 ;

/// 数据类型：bytevector; 域名：字段名称
const int H5SDK_TAG_SORT_FIELD_NAME = 20066 ;

/// 数据类型：int32; 域名：量比
const int H5SDK_TAG_VOL_RATIO = 34 ;

/// 数据类型：int64; 域名：五日量
const int H5SDK_TAG_DAY5_VOL = 35 ;

/// 数据类型：int32; 域名：振幅
const int H5SDK_TAG_AMPLITUDE = 46 ;

/// 数据类型：int64; 域名：持仓量
const int H5SDK_TAG_AMOUNT = 95 ;

/// 数据类型：int32; 域名：换手率
const int H5SDK_TAG_TURNOVER_RATIO = 97 ;

/// 数据类型：int32; 域名：委比
const int H5SDK_TAG_ENTRUST_RATE = 99 ;

/// 数据类型：int64; 域名：委差
const int H5SDK_TAG_ENTRUST_DIFF = 101 ;

/// 数据类型：int8(枚举); 域名：排序方式
const int H5SDK_TAG_SORT_TYPE = 102 ;
    const int8 HSUB_ENUM_SORT_ASC = 0 ; // 升序
    const int8 HSUB_ENUM_SORT_DESC = 1 ; // 降序

/// 数据类型：bytevector; 域名：MIC_ABBR
const int H5SDK_TAG_MIC_ABBR = 103 ;

/// 数据类型：uint32; 域名：起始分钟数
const int H5SDK_TAG_START_MIN = 104 ;

/// 数据类型：uint32; 域名：介绍分钟数
const int H5SDK_TAG_END_MIN = 105 ;

/// 数据类型：sequence; 域名：分笔数据重复组
const int H5SDK_TAG_TICK_GRP = 106 ;

/// 数据类型：uint32; 域名：分笔序号
const int H5SDK_TAG_BUSINESS_NO = 107 ;

/// 数据类型：int32; 域名：成交方向
const int H5SDK_TAG_BUSINESS_DIRECTION = 109 ;

/// 数据类型：int32; 域名：每手股数
const int H5SDK_TAG_SHARES_PER_HAND = 72 ;

/// 数据类型：int32; 域名：价格精度
const int H5SDK_TAG_PX_PRECISION = 71 ;

/// 数据类型：int64; 域名：流通股本
const int H5SDK_TAG_CIRCULATION_AMOUNT = 110 ;

/// 数据类型：int64; 域名：市值
const int H5SDK_TAG_MARKET_VALUE = 91 ;

/// 数据类型：int64; 域名：流通市值
const int H5SDK_TAG_CIRCULATION_VALUE = 111 ;

/// 数据类型：int32; 域名：每股股收益
const int HSSDK_TAG_EPS = 112 ;

/// 数据类型：int32; 域名：每股净资产
const int HSSDK_TAG_BPS = 94 ;

/// 数据类型：int32; 域名：市净率
const int HSSDK_TAG_DYN_PB_RATE = 45 ;

/// 数据类型：int32; 域名：财务季度
const int HSSDK_TAG_FIN_QUARTER = 113 ;

/// 数据类型：int32; 域名：财务截至日期
const int HSSDK_TAG_FIN_END_DATE = 114 ;

/// 数据类型：int8; 域名：数据是否获取完全
const int HSSDK_TAG_ALL_DATA_FLAG = 115 ;

/// 数据类型：int32; 域名：上涨家数
const int HSSDK_TAG_RISE_COUNT = 124 ;

/// 数据类型：int32; 域名：下跌家数
const int HSSDK_TAG_FALL_COUNT = 125 ;

/// 数据类型：int32; 域名：成员个数
const int HSSDK_TAG_MEMBER_COUNT = 126 ;

/// 数据类型：sequence; 域名：领涨股
const int H5SDK_TAG_RISE_FIRST_GRP = 1009 ;

/// 数据类型：sequence; 域名：领跌股
const int H5SDK_TAG_FALL_FIRST_GRP = 1010 ;

/// 数据类型：string; 域名：时区码
const int H5SDK_TAG_TIMEZONE_CODE = 128 ;

/// 数据类型：uint32; 域名：分钟时间
const int H5SDK_TAG_MIN_TIME = 10014 ;

/// 数据类型：uint32; 域名：排序字段ID
const int H5SDK_TAG_SORT_FIELD_ID = 20068 ;

/// 数据类型：uint32; 域名：字段id
const int H5SDK_TAG_FIELD_ID = 20069 ;

/// 数据类型：int64; 域名：昨持仓（期货、期权）
const int HSSDK_TAG_PREV_AMOUNT = 122 ;

/// 数据类型：int64; 域名：日增持（期货、期权）
const int HSSDK_TAG_AMOUNT_DELTA = 123 ;

/// 数据类型：int64; 域名：IOPV
const int HSSDK_TAG_IOPV = 29 ;

/// 数据类型：int64; 域名：国债基金净值
const int HSSDK_TAG_DEBT_FUND_VALUE = 90 ;

/// 数据类型：int64; 域名：昨结算
const int HSSDK_TAG_PREV_SETTLEMENT = 28 ;

/// 数据类型：int64; 域名：今结算价
const int HSSDK_TAG_SETTLEMENT = 27 ;

/// 数据类型：uint16; 域名：补线类型
const int H5SDK_TAG_SUB_KIND = 676 ;

/// 数据类型：int32; 域名：返回值
const int H5SDK_TAG_MAINTAIN_RETURN_VALUE = 767 ;

/// 数据类型：bytevector; 域名：应用名称
const int H5SDK_TAG_APP_NAME = 20072 ;

/// 数据类型：bytevector; 域名：手机号
const int H5SDK_TAG_PHONE_NUMBER = 20073 ;

/// 数据类型：bytevector; 域名：MAC地址，作为用户识别标志
const int H5SDK_TAG_MAC_ADDRESS = 20074 ;

/// 数据类型：int8; 域名：是否有子版块
const int H5SDK_TAG_BLOCK_CHILDREN_FLAG = 20075 ;

/// 数据类型：int64; 域名：特殊标记
/*Special Maker宏定义
#define SM_DELIST_WARNING             0x01  ///< 退市警示标的
#define SM_RISK_WARNING               0x02  ///< 风险警示标的
#define SM_CRD_BUY                    0x04  ///< 融资标的
#define SM_CRD_SELL                   0x08  ///< 融券标的
#define SM_SH2HK                      0x10  ///< 沪股通标的(可买可卖)
#define SM_HK2SH                      0x20  ///< 港股通标的(可买可卖)
#define SM_SH2HK_ONLY_SELL            0x40  ///< 沪股通标的(只可卖)
#define SM_HK2SH_ONLY_SELL            0x80  ///< 港股通标的(只可卖)
#define SM_H_TARGET                  0x100  ///< H股标的
#define SM_B_TARGET                  0x200  ///< B股标的
#define SM_A_TARGET                  0x400  ///< A股标的
#define SM_HK_DW_C                   0x800  ///< 港股-认购
#define SM_HK_DW_P                  0x1000  ///< 港股-认沽
#define SM_HK_CBBC_C                0x2000  ///< 港股-牛证
#define SM_HK_CBBC_P                0x4000  ///< 港股-熊证
#define SM_NEEQ_BASE                0x10000  ///< 新三板-基础层
#define SM_NEEQ_CREATE              0x20000  ///< 新三板-创新层
#define SM_HK_VCM_FLAG              0x40000  ///< 港股-冷静期标记
#define SM_HK_CAS_FLAG              0x80000  ///< 港股-收盘竞价标记
#define SM_HK2SZ                   0x100000  ///< 港股通标的(可买可卖)
#define SM_HK2SZ_ONLY_SELL         0x200000  ///< 港股通标的(只可卖)
#define SM_SZ2HK_FRACTIONAL_SELL   0x400000  ///< 港股通零股（可买可卖）
#define SM_SZ2HK_FRACTIONAL_ONLY_SELL  0x800000  ///< 港股通零股（只可卖）
#define SM_SZ2HK                       0x1000000  ///< 深股通标的(可买可卖)
#define SM_SZ2HK_ONLY_SELL             0x2000000  ///<深股通标的(只可卖)
#define SM_UNISSUED_STATE             0x4000000  ///< 未发行
#define SM_PURCHASE_STATE             0x8000000  ///< 当日申购
#define SM_ISSUED_STATE             0x10000000  ///< 已发行-未上市
#define SM_INVESTOR_ALL        0x20000000   ///<包括公众投资者、合格投资者在内的所有投资者都可以认购和交易
#define SM_QUALIFICATION_ONLY  0x40000000   ///<仅合格投资者可以认购和交易
#define SM_ORGANIZATION_QUALIFICATION_ONLY  0x80000000   ///<仅合格投资者中的机构投资者可以认购和交易
#define SM_MAIN_CONTRACT_STATE  0x100000000       ///<期货主力合约标记
#define SM_NIGHT_CONTRACT_STATE  0x200000000    ///<期货夜盘合约标记
#define SM_FATHER_BLOCK_STATE  0x400000000      ///<板块市场父板块标记
#define SM_UP_LIMIT_STATE  0x800000000          ///<正常涨停标记
#define SM_DOWN_LIMIT_STATE  0x1000000000       ///<正常跌停标记
#define SM_TOUCH_UP_LIMIT_STATE  0x2000000000   ///<触板涨停标记
#define SM_TOUCH_DOWN_LIMIT_STATE  0x4000000000 ///<触板跌停标记
*/
const int H5SDK_TAG_SPECIAL_MARKER = 20100 ;

/// 数据类型：bytevector; 域名：标的证券
const int H5SDK_TAG_UNDERLYING = 20101 ;

/// 数据类型：uint32; 域名：行权日期
const int H5SDK_TAG_EXERCISE_DATE = 20102 ;

/// 数据类型：int64; 域名：行权价格
const int H5SDK_TAG_EXERCISE_PRICE = 20103 ;

/// 数据类型：uint32; 域名：合约乘数
const int H5SDK_TAG_CONTRACT_UNIT = 20104 ;

/// 数据类型：bytevector; 域名：合约代码
const int H5SDK_TAG_CONTRACT_CODE = 20105 ;

/// 数据类型：bytevector; 域名：行权方式：若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”
const int H5SDK_TAG_EXERCISE_TYPE = 20106 ;

/// 数据类型：bytevector; 域名：认购认沽，认购，则本字段为“C”；若为认沽，则本字段为“P”
const int H5SDK_TAG_CALL_PUT = 20107 ;

/// 数据类型：uint32; 域名：首个交易日
const int H5SDK_TAG_START_TRADE_DATE = 20108 ;

/// 数据类型：uint32; 域名：最后交易日
const int H5SDK_TAG_END_TRADE_DATE = 20109 ;

/// 数据类型：uint32; 域名：到期日期
const int H5SDK_TAG_EXPIRE_DATE = 20110 ;

/// 数据类型：uint32; 域名：期权合约状态信息
const int H5SDK_TAG_SECURITY_STATUS_FLAG = 20111 ;

/// 数据类型：int32; 域名：最小报价单位
const int H5SDK_TAG_TICK_SIZE = 20112 ;

/// 数据类型：bytevector; 域名：产品实施标志，该字段为4位字符串，左起每位表示特定的含义，无定义则填空格。
//第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示//连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘V’表示波动性中断，‘P’表示临时停牌、‘U’表示收盘集合竞价。
//第2位：‘0’表示未连续停牌，‘1’表示连续停牌。（预留，暂填空格）
//第3位：‘0’表示不限制开仓，‘1’表示限制备兑开仓，‘2’表示卖出开仓，‘3’表示限制卖出开仓、备兑开仓，‘4’表示限制买入开仓，‘5’表示限制买入开仓、备兑开仓，‘6’表示限制买入开仓、卖出开仓，‘7’表示限制买入开仓、卖出开仓、备兑开仓

const int H5SDK_TAG_TRADING_PHASE_CODE = 20113 ;

/// 数据类型：int32; 域名：动态参考价
const int H5SDK_TAG_AUCTION_PRICE = 20114 ;

/// 数据类型：int64; 域名：虚拟匹配数量
const int H5SDK_TAG_MATCHED_QTY = 20115 ;

/// 数据类型：int32; 域名：五分钟涨跌幅
const int H5SDK_TAG_MIN5_CHGPCT = 47 ;

/// 数据类型：int32; 域名：开市分钟数，相对对交易日0点
const int H5SDK_TAG_OPEN_MIN = 74 ;

/// 数据类型：int32; 域名：闭市分钟数，相对对交易日0点
const int H5SDK_TAG_CLOSE_MIN = 76 ;

/// 数据类型：uint32(枚举); 域名：关联类型
const int H5SDK_TAG_UNDERLYING_TYPE = 20116 ;
    const uint32 H5SDK_ENUM_UNDERLYING_A = 0 ; // A股
    const uint32 H5SDK_ENUM_UNDERLYING_B = 1 ; // B股
    const uint32 H5SDK_ENUM_UNDERLYING_H = 2 ; // H股
    const uint32 H5SDK_ENUM_UNDERLYING_F = 3 ; // 期货
    const uint32 H5SDK_ENUM_UNDERLYING_OPT = 4 ; // 期权
    const uint32 H5SDK_ENUM_UNDERLYING_DW_C = 5 ; // 港股-认购
    const uint32 H5SDK_ENUM_UNDERLYING_DW_P = 6 ; // 港股-认沽
    const uint32 H5SDK_ENUM_UNDERLYING_CBBC_C = 7 ; // 港股-牛证
    const uint32 H5SDK_ENUM_UNDERLYING_CBBC_P = 8 ; // 港股-熊证

/// 数据类型：sequence; 域名：关联代码重复组
const int H5SDK_TAG_UNDERLYING_GRP = 20117 ;

/// 数据类型：sequence; 域名：除权信息
const int H5SDK_TAG_EXER_GREP = 20118 ;

/// 数据类型：int32; 域名：每股送股
const int H5SDK_TAG_ALLOTTED_PS = 51 ;

/// 数据类型：int32; 域名：每股配股数
const int H5SDK_TAG_RATIONED_PS = 52 ;

/// 数据类型：int64; 域名：配股价
const int H5SDK_TAG_RATIONED_PX = 53 ;

/// 数据类型：int32; 域名：每股分红
const int H5SDK_TAG_BONUS_PS = 54 ;

/// 数据类型：bytevector; 域名：拼音简称
const int H5SDK_TAG_CHI_SPELLING = 20119 ;

/// 数据类型：int32; 域名：上市日期
const int H5SDK_TAG_ISSUE_DATE = 20120 ;

/// 数据类型：int64; 域名：IPO价格
const int H5SDK_TAG_IPO_PRICE = 20121 ;

/// 数据类型：sequence; 域名：拼音简称重复组
const int H5SDK_TAG_CHI_SPELLING_GRP = 20122 ;

/// 数据类型：rawdata; 域名：用户信息
const int H5SDK_TAG_USER_INFO = 20123 ;

/// 数据类型：rawdata; 域名：应用识别符
const int H5SDK_TAG_APP_KEY = 20124 ;

/// 数据类型：int64; 域名：gamma指标
const int H5SDK_TAG_GAMMA_INDEX = 20130 ;

/// 数据类型：int64; 域名：delta指标
const int H5SDK_TAG_DELTA_INDEX = 20131 ;

/// 数据类型：int64; 域名：真实杠杆率
const int H5SDK_TAG_REAL_LEVERAGE = 20132 ;

/// 数据类型：int64; 域名：期权定价
const int H5SDK_TAG_OPTION_PRICE = 20133 ;

/// 数据类型：sequence; 域名：逐笔重复组
const int H5SDK_TAG_TRANSCATION_GRP = 20134 ;

/// 数据类型：int32; 域名：委托类别
const int H5SDK_TAG_TRANS_KIND = 20135 ;

/// 数据类型：bytevector; 域名：权限信息
const int H5SDK_TAG_AUTH_STRING = 1095 ;

/// 数据类型：int32; 域名：市场相对分钟数
const int H5SDK_TAG_MARKET_MIN = 20136 ;

/// 数据类型：sequence; 域名：F10索引重复组
const int H5SDK_TAG_F10_INDEX_GRP = 20137 ;

/// 数据类型：int8; 域名：//消息类型
//Bit0-3信息类型              0x00交易所公告
//0x01财经新闻0x02 个股历史资讯 (公司大事记)
//0x03个股实时资讯
//0x04  F1资料
//0x05-0x0保留
//0x0f  其它

const int H5SDK_TAG_F10_GROUP = 20138 ;

/// 数据类型：int8; 域名：市场对应bit位
//0 上海
//1 深圳
//2 创业
//3 香港
//4 台湾
//5 美国
//6 保留
//7 其它

const int H5SDK_TAG_F10_MARKET = 20139 ;

/// 数据类型：int64; 域名：委买一价
const int H5SDK_TAG_BID_PRICE1 = 20140 ;

/// 数据类型：int64; 域名：委卖一价
const int H5SDK_TAG_OFFER_PRICE1 = 20141 ;

/// 数据类型：int64; 域名：委买一量
const int H5SDK_TAG_BID_QTY1 = 20142 ;

/// 数据类型：int64; 域名：委卖一量
const int H5SDK_TAG_OFFER_QTY1 = 20143 ;

/// 数据类型：bytevector; 域名：标题，最大64字节
const int H5SDK_TAG_F10_TILTLE = 20144 ;

/// 数据类型：int64; 域名：消息序号，新闻序号（当天新闻序号唯一，不保证连续）(易富新闻序号)
const int H5SDK_TAG_F10_FILEPK = 20145 ;

/// 数据类型：uint32; 域名：HHMMSS
const int H5SDK_TAG_TIME = 20146 ;

/// 数据类型：sequence; 域名：F10索引重复组
const int H5SDK_TAG_F10_FILEPK_GRP = 20147 ;

/// 数据类型：sequence; 域名：F10索引内容重复组
const int H5SDK_TAG_F10_TXT_GRP = 20148 ;

/// 数据类型：uint32(枚举); 域名：资讯数据类型
const int H5SDK_TAG_F10_TYPE = 20149 ;
    const uint32 H5SDK_ENUM_TYPE_F10 = 1 ; // F10数据
    const uint32 H5SDK_ENUM_TYPE_RID = 2 ; // 分时资讯
    const uint32 H5SDK_ENUM_TYPE_HID = 3 ; // 港股分时资讯

/// 数据类型：uint64; 域名：成交额(放大1000倍)
const int H5SDK_TAG_BUSINESS_BALANCE_SCALE = 20150 ;

/// 数据类型：int32(枚举); 域名：记录状态
const int H5SDK_TAG_RECORD_STATUS = 20151 ;
    const int32 H5SDK_ENUM_RECORD_STATUS_INVALID = 0 ; // 记录状态无效
    const int32 H6SDK_ENUM_RECORD_STATUS_VALID = 1 ; // 记录状态有效

/// 数据类型：uint32; 域名：股转作市商数量
const int H5SDK_TAG_NEEQ_MAKER_COUNT = 20152 ;

/// 数据类型：int32; 域名：档位编号
const int H5SDK_TAG_SPREAD_LEVEL = 20153 ;

/// 数据类型：bytevector; 域名：股票单位名称
const int H5SDK_TAG_FINANCE_UNITNAME = 20154 ;

/// 数据类型：uint32; 域名：请求模式（0位请求特定期货合约，1为整个交易所）
const int H5SDK_CODE_PROPERTY_MODEL = 20155 ;

/// 数据类型：bytevector; 域名：关联代码
const int H5SDK_TAG_RELATIVECODE = 20156 ;

/// 数据类型：bytevector; 域名：商品描述
const int H5SDK_TAG_SYMBOL_DETAIL = 20177 ;

/// 数据类型：uint32; 域名：有效标识
const int H5SDK_TAG_ENABLE = 20159 ;

/// 数据类型：uint32; 域名：是否可以交易
const int H5SDK_TAG_CAN_TRADE = 20160 ;

/// 数据类型：uint32; 域名：最小变动单位
const int H5SDK_TAG_MIN_MOVE = 20174 ;

/// 数据类型：uint32; 域名：每个整数点价值
const int H5SDK_TAG_BIG_POINT_VALUE = 20175 ;

/// 数据类型：uint32; 域名：买卖盘个数
const int H5SDK_TAG_BID_ASK_DEPTH = 20176 ;

/// 数据类型：uint32; 域名：单笔市价交易最大限量
const int H5SDK_TAG_MAX_MARKET_ORDER_VOLUME = 20161 ;

/// 数据类型：uint32; 域名：单笔限价交易最大限量
const int H5SDK_TAG_LIMIT_MARKET_ORDER_VOLUME = 20162 ;

/// 数据类型：uint32; 域名：最大单笔限量
const int H5SDK_TAG_MAX_LIMIT_SHARES = 20163 ;

/// 数据类型：bytevector; 域名：保证金比率
const int H5SDK_TAG_MARGIN_RATE = 20164 ;

/// 数据类型：uint32; 域名：保证金比率的计算方式
const int H5SDK_TAG_MARGIN_MODEL = 20165 ;

/// 数据类型：uint32; 域名：期货代码类型
const int H5SDK_TAG_CODE_TYPE = 20166 ;

/// 数据类型：uint32; 域名：合约交割年份
const int H5SDK_TAG_CONTRACT_YEAR = 20167 ;

/// 数据类型：uint32; 域名：合约交割月份
const int H5SDK_TAG_CONTRACT_MONTH = 20168 ;

/// 数据类型：uint32; 域名：是否是连续
const int H5SDK_TAG_IS_SERIES = 20169 ;

/// 数据类型：uint32; 域名：期权类型
const int H5SDK_TAG_OP_TYPE = 20170 ;

/// 数据类型：uint32; 域名：期权行权方式
const int H5SDK_TAG_OP_STYLE = 20171 ;

/// 数据类型：bytevector; 域名：合约交易代码
const int H5SDK_TAG_BROKER_CODE = 20172 ;

/// 数据类型：bytevector; 域名：价格精度单位
const int H5SDK_TAG_PRICE_SCALE_UNIT = 20173 ;

/// 数据类型：int64; 域名：委卖量
const int H5SDK_TAG_TOTAL_OFFERQTY = 20179 ;

/// 数据类型：int64; 域名：委买量
const int H5SDK_TAG_TOTAL_BIDQTY = 20180 ;

/// 数据类型：int64; 域名：委卖金额
const int H5SDK_TAG_TOTAL_OFFER_TURNOVER = 20181 ;

/// 数据类型：int64; 域名：委买金额
const int H5SDK_TAG_TOTAL_BID_TURNOVER = 20182 ;

/// 数据类型：uint64; 域名：开始时间YYYYMMDDHHMMSS
const int H5SDK_TAG_START_DATE_TIME = 20286 ;

/// 数据类型：uint64; 域名：结束时间YYYYMMDDHHMMSS
const int H5SDK_TAG_END_DATE_TIME = 20287 ;

/// 数据类型：bytevector; 域名：最小价格变动单位精度
const int H5SDK_TAG_MIN_MOVE_SCALE = 20288 ;

/// 数据类型：int32(枚举); 域名：港股状态
const int H5SDK_TAG_HK_STATUS = 20289 ;
    const int32 H5SDK_ENUM_HK_NORMAL_STATUS = 0 ; // 港股正常交易状态
    const int32 H5SDK_ENUM_HK_VCM_STATUS = 1 ; // 港股市调状态
    const int32 H5SDK_ENUM_HK_CAS_STATUS = 2 ; // 港股收市竞价状态

/// 数据类型：string; 域名：CAS未能配对买卖盘的方向
//N = 买卖盘量相等
//B = 买盘比卖盘多
//S = 卖盘比买盘多
//空格 = 不适用(未有参考平衡价格)

const int H5SDK_TAG_ORD_IMB_DIRECTION = 20290 ;

/// 数据类型：int64; 域名：参考价格
const int H5SDK_TAG_REFERENCE_PX = 20291 ;

/// 数据类型：uint32; 域名：起始时间,HHMMSS
const int H5SDK_TAG_START_TIME = 20292 ;

/// 数据类型：uint32; 域名：结束时间,HHMMSS
const int H5SDK_TAG_END_TIME = 20293 ;

/// 数据类型：uint64; 域名：累积成交金额(1000倍)
const int H5SDK_TAG_ACCUMULATE_TURNOVER = 20190 ;

/// 数据类型：bytevector; 域名：前复权除权因子A
const int H5SDK_TAG_EXER_FORWARD_A = 20294 ;

/// 数据类型：int64; 域名：前复权除权因子B
const int H5SDK_TAG_EXER_FORWARD_B = 20295 ;

/// 数据类型：bytevector; 域名：后复权除权因子A
const int H5SDK_TAG_EXER_BACKWARD_A = 20296 ;

/// 数据类型：int64; 域名：后复权除权因子B
const int H5SDK_TAG_EXER_BACKWARD_B = 20297 ;

/// 数据类型：int64; 域名：成交量增量
const int H5SDK_TAG_BUSINESS_AMOUNT_DIFF = 20298 ;

/// 数据类型：int64; 域名：成交额增量
const int H5SDK_TAG_BUSINESS_BALANCE_DIFF = 20299 ;

/// 数据类型：int32; 域名：成交笔数增量
const int H5SDK_TAG_BUSINESS_COUNT_DIFF = 20300 ;

/// 数据类型：int64; 域名：资金流ddx(放大1000倍)
const int H5SDK_TAG_FUNDFLOW_DDX = 55000 ;

/// 数据类型：int64; 域名：资金流ddy(放大1000倍)
const int H5SDK_TAG_FUNDFLOW_DDY = 55001 ;

/// 数据类型：int64; 域名：资金流ddz(放大1000倍)
const int H5SDK_TAG_FUNDFLOW_DDZ = 55002 ;

/// 数据类型：int32; 域名：最近10日内DDX飘红天数
const int H5SDK_TAG_RISEDAYS_PAST10_DDX = 55003 ;

/// 数据类型：int32; 域名：DDX连续飘红天数
const int H5SDK_TAG_RISEDAYS_CONTINUES = 55004 ;

/// 数据类型：sequence; 域名：扩展资金流指标
const int H5SDK_TAG_FUNDFLOW_INDEX_EXT_GRP = 55005 ;

/// 数据类型：uint32(枚举); 域名：资金流指标类型:0 = 5日;1 = 10日
const int H5SDK_TAG_FUNDFLOW_INDEX_TYPE = 55006 ;
    const uint32 H5SDK_ENUM_FUNDFLOW_FIVE_TYPE = 0 ; // 5日
    const uint32 H5SDK_ENUM_FUNDFLOW_TEN_TYPE = 1 ; // 10日

/// 数据类型：sequence; 域名：逐单流入分类统计
const int H5SDK_TAG_CLASSIFY_ORDER_BID_GRP = 55007 ;

/// 数据类型：sequence; 域名：逐单流出分类统计
const int H5SDK_TAG_CLASSIFY_ORDER_OFFER_GRP = 55008 ;

/// 数据类型：sequence; 域名：逐笔流入分类统计
const int H5SDK_TAG_CLASSIFY_TRANS_BID_GRP = 55009 ;

/// 数据类型：sequence; 域名：逐笔流出分类统计
const int H5SDK_TAG_CLASSIFY_TRANS_OFFER_GRP = 55010 ;

/// 数据类型：int8(枚举); 域名：选股类型
const int H5SDK_TAG_SELECTCODE_TYPE = 55011 ;
    const int8 H5SDK_ENUM_SELECTCODE_INDEX_TYPE = 0 ; // 指标选股
    const int8 H5SDK_ENUM_SELECTCODE_INDEX_RESONNACE_TYPE = 1 ; // 指标共振选股
    const int8 H5SDK_ENUM_SELECTCODE_SHAPE_TYPE = 2 ; // K线形态选股

/// 数据类型：int8(枚举); 域名：选股参数类型（默认为：0）
const int H5SDK_TAG_SELECTCODE_PARAM_TYPE = 55012 ;
    const int8 H5SDK_ENUM_SELECTCODE_PARAM_DEF = 0 ; // def：默认指标
    const int8 H5SDK_ENUM_SELECTCODE_PARAM_OPT = 1 ; // opt：最优指标

/// 数据类型：int32; 域名：指定返回代码数
const int H5SDK_TAG_RETURN_CODE_COUNT = 55013 ;

/// 数据类型：int32; 域名：按字段ID排序返回
const int H5SDK_TAG_ORDER_BY_FIELD = 55014 ;

/// 数据类型：sequence; 域名：指标列表
const int H5SDK_TAG_INDEX_LIST_GRP = 55015 ;

/// 数据类型：int8(枚举); 域名：指标类型（不填的话默认为全部指标）
const int H5SDK_TAG_INDEX_TYPE = 55016 ;
    const int8 H5SDK_ENUM_INDEX_MACD_TYPE = 0 ; // MACD指标
    const int8 H5SDK_ENUM_INDEX_KDJ_TYPE = 1 ; // KDJ指标
    const int8 H5SDK_ENUM_INDEX_RSI_TYPE = 2 ; // RSI指标
    const int8 H5SDK_ENUM_INDEX_MA_TYPE = 3 ; // MA指标
    const int8 H5SDK_ENUM_INDEX_BOLL_TYPE = 4 ; // BOLL指标

/// 数据类型：sequence; 域名：选股结果集
const int H5SDK_TAG_SELECTCODE_RESULT_GRP = 55017 ;

/// 数据类型：int32; 域名：回测中交易次数
const int H5SDK_TAG_TRADE_COUNT = 55018 ;

/// 数据类型：int32; 域名：回测中盈利次数
const int H5SDK_TAG_WIN_COUNT = 55019 ;

/// 数据类型：int32; 域名：回测中盈利的概率，扩大100倍
const int H5SDK_TAG_WIN_RATE = 55020 ;

/// 数据类型：int32; 域名：期望收益率，扩到100000倍
const int H5SDK_TAG_EXP_REVENUE = 55021 ;

/// 数据类型：int32(枚举); 域名：交易操作方法
const int H5SDK_TAG_TRADE_OPERATOR = 55022 ;
    const int32 H5SDK_ENUM_BUY_OPERATOR = 0 ; // 买入
    const int32 H5SDK_ENUM_SELL_OPERATOR = 1 ; // 卖出
    const int32 H5SDK_ENUM_CASH_OPERATOR = 2 ; // 持币
    const int32 H5SDK_ENUM_STOCK_OPERATOR = 3 ; // 持股
    const int32 H5SDK_ENUM_NOBS_OPERATOR = 4 ; // 非买非卖

/// 数据类型：int32; 域名：指标共振分数
const int H5SDK_TAG_INDEXRESONANCE_SCORE = 55023 ;

/// 数据类型：int32(枚举); 域名：回测年限（默认为3）
const int H5SDK_TAG_BACKTEST_YEARS = 55024 ;
    const int32 H5SDK_ENUM_BACKTEST_SHORT_YEARS = 0 ; // 1年
    const int32 H5SDK_ENUM_BACKTEST_MID_YEARS = 1 ; // 3年
    const int32 H5SDK_ENUM_BACKTEST_LONG_YEARS = 2 ; // 7年

/// 数据类型：int32; 域名：回测日期
const int H5SDK_TAG_BACKTEST_DATE = 55025 ;

/// 数据类型：int32; 域名：回测时间
const int H5SDK_TAG_BACKTEST_TIME = 55026 ;

/// 数据类型：int32; 域名：总收益率
const int H5SDK_TAG_TOTAL_REVENUE = 55027 ;

/// 数据类型：int32; 域名：回测年化收益
const int H5SDK_TAG_YEARLY_REVENUE = 55028 ;

/// 数据类型：int32; 域名：基准收益率
const int H5SDK_TAG_BENCHMARK_REVENUE = 55029 ;

/// 数据类型：int32; 域名：回测索提若比率
const int H5SDK_TAG_SORTINO = 55030 ;

/// 数据类型：int32; 域名：回测信息比率
const int H5SDK_TAG_INFO_RATIO = 55031 ;

/// 数据类型：int32; 域名：回测算法波动率
const int H5SDK_TAG_ALGO_VOLATILITY = 55032 ;

/// 数据类型：int32; 域名：回测基准波动率
const int H5SDK_TAG_BENCHMARK_VOLATILITY = 55033 ;

/// 数据类型：int32; 域名：回测换手率
const int H5SDK_TAG_TURNOVER_RATE = 55034 ;

/// 数据类型：int32; 域名：回测最大回撤
const int H5SDK_TAG_MAX_DRAWDOWN = 55035 ;

/// 数据类型：sequence; 域名：形态列表
const int H5SDK_TAG_SHAPE_LIST = 55036 ;

/// 数据类型：int8(枚举); 域名：形态名称
const int H5SDK_TAG_SHAPE_TYPE = 55037 ;
    const int8 H5SDK_ENUM_SHAPE_SJZX = 0 ; // 射击之星
    const int8 H5SDK_ENUM_SHAPE_SDX = 1 ; // 上吊线
    const int8 H5SDK_ENUM_SHAPE_HHZX = 2 ; // 黄昏之星
    const int8 H5SDK_ENUM_SHAPE_MBX = 3 ; // 墓碑线
    const int8 H5SDK_ENUM_SHAPE_WYGD = 4 ; // 乌云盖顶
    const int8 H5SDK_ENUM_SHAPE_TMXT = 5 ; // 吞没形态
    const int8 H5SDK_ENUM_SHAPE_SZWY = 6 ; // 三只乌鸦
    const int8 H5SDK_ENUM_SHAPE_CTX = 7 ; // 锤头线
    const int8 H5SDK_ENUM_SHAPE_ZCZX = 8 ; // 早晨之星
    const int8 H5SDK_ENUM_SHAPE_SGCX = 9 ; // 曙光初现
    const int8 H5SDK_ENUM_SHAPE_CTXT = 10 ; // 刺透形态
    const int8 H5SDK_ENUM_SHAPE_HSB = 11 ; // 红三兵

/// 数据类型：int32; 域名：5日盈利次数
const int H5SDK_TAG_5DAY_WIN_COUNT = 55038 ;

/// 数据类型：int32; 域名：10日期望收益率，扩到100000倍
const int H5SDK_TAG_5DAY_EXP_REVENUE = 55039 ;

/// 数据类型：int32; 域名：10日盈利次数
const int H5SDK_TAG_10DAY_WIN_COUNT = 55040 ;

/// 数据类型：int32; 域名：10日期望收益率，扩到100000倍
const int H5SDK_TAG_10DAY_EXP_REVENUE = 55041 ;

/// 数据类型：sequence; 域名：日期列表
const int H5SDK_TAG_DATE_GRP = 55042 ;

/// 数据类型：sequence; 域名：均线拐点集
const int H5SDK_MSG_MA_INFLEXTION_GRP = 55043 ;

/// 数据类型：int32; 域名：选股时间
const int H5SDK_TAG_SELECTCODE_TIME = 55044 ;

/// 数据类型：bytevector; 域名：指标参数
const int H5SDK_TAG_INDEX_VALUE = 55045 ;

/// 数据类型：sequence; 域名：每日收益率集（只有指标共振有）
const int H5SDK_MSG_DAY_REVENUE_GRP = 55046 ;

/// 数据类型：int64; 域名：每日盈亏
const int H5SDK_TAG_DAY_PROFIT_LOSS = 55047 ;

/// 数据类型：sequence; 域名：选股参数列表
const int H5SDK_TAG_SELECTCODE_PARAM_TYPE_GRP = 55048 ;

/// 数据类型：sequence; 域名：选股类型列表
const int H5SDK_TAG_SELECTCODE_TYPE_GRP = 55049 ;

/// 数据类型：sequence; 域名：买卖结果集
const int H5SDK_TAG_BS_GRP = 55050 ;

/// 数据类型：int8(枚举); 域名：获取收益类型 0:5日 1:10日 默认为5日
const int H5SDK_TAG_SHAPE_REVENUE_TYPE = 55051 ;
    const int8 H5SDK_ENUM_SHAPE_FIVE_DAY_REVENUE = 0 ; // 获取5日收益率
    const int8 H5SDK_ENUM_SHAPE_TEN_DAY_REVENUE = 1 ; // 获取10日收益率

/// 数据类型：bytevector; 域名：形态名称
const int H5SDK_TAG_SHAPE_NAME = 55052 ;

/// 数据类型：int32; 域名：持续天数
const int H5SDK_TAG_CONTINUOUS_DAY = 55053 ;

/// 数据类型：sequence; 域名：交易操作集合
const int H5SDK_TAG_TRADE_OPERATOR_GRP = 55054 ;

/// 数据类型：int32(枚举); 域名：选择是否返回每日收益集（默认为0 不返回）1:返回
const int H5SDK_TAG_SELECT_RETURN_DAILY = 55055 ;
    const int32 H5SDK_ENUM_RETURN_DAILY_NO = 0 ; // 不返回
    const int32 H5SDK_ENUM_RETURN_DAILY_YES = 1 ; // 返回

/// 数据类型：int64; 域名：逐单大单成交额净量
const int H5SDK_TAG_ORDER_LARGER_NET_TURNOVER = 55057 ;

/// 数据类型：sequence; 域名：逐单分类成交额净量 数组0:超大单;数组1:大单;数组2:中单;数组3:小单
const int H5SDK_TAG_CLASSIFY_ORDER_NET_TURNOVER = 55058 ;

/// 数据类型：int64; 域名：成交额净量
const int H5SDK_TAG_NET_TURNOVER = 55059 ;

/// 数据类型：int64; 域名：逐笔大单成交额净量
const int H5SDK_TAG_TRANS_LARGER_NET_TURNOVER = 55060 ;

/// 数据类型：sequence; 域名：逐笔分类成交额净量 数组0:超大单;数组1:大单;数组2:中单;数组3:小单
const int H5SDK_TAG_CLASSIFY_TRANS_NET_TURNOVER = 55061 ;

/// 数据类型：int32; 域名：期货行情源时间（仅期货使用）
const int H5SDK_TAG_RECORD_TIME = 20228 ;

/// 数据类型：int64; 域名：今开
const int H5SDK_TAG_OPEN_VOL = 20229 ;

/// 数据类型：int64; 域名：今平
const int H5SDK_TAG_CLOSE_VOL = 20230 ;

/// 数据类型：int64; 域名：主力切换
const int H5SDK_TAG_CHANGE_MAIN_FLAG = 20231 ;

/// 数据类型：int32; 域名：合约创建日期
const int H5SDK_TAG_STOCK_CREATE_DATE = 20332 ;

/// 数据类型：int32; 域名：合约上市日期
const int H5SDK_TAG_STOCK_LIST_DATE = 20334 ;

/// 数据类型：bytevector; 域名：客户端ip地址
const int H5SDK_TAG_CLIENT_IP = 20335 ;

/// 数据类型：sequence; 域名：5日逐单流入分类统计 依次表示超大单;大单;中单;小单
const int H5SDK_TAG_CLASSIFY_ORDER_BID_PAST5 = 55062 ;

/// 数据类型：sequence; 域名：5日逐单流出分类统计 依次表示超大单;大单;中单;小单
const int H5SDK_TAG_CLASSIFY_ORDER_OFFER_PAST5 = 55063 ;

/// 数据类型：sequence; 域名：10日逐单流入分类统计 依次表示超大单;大单;中单;小单
const int H5SDK_TAG_CLASSIFY_ORDER_BID_PAST10 = 55064 ;

/// 数据类型：sequence; 域名：10日逐单流出分类统计 依次表示超大单;大单;中单;小单
const int H5SDK_TAG_CLASSIFY_ORDER_OFFER_PAST10 = 55065 ;

/// 数据类型：sequence; 域名：逐单扩展数据  依次表示当日 5日 10日加总
const int H5SDK_TAG_ORDER_EXT_DATA = 55066 ;

/// 数据类型：int32; 域名：连续流入天数，正数为连续流入天数，负数为连续流出天数
const int H5SDK_TAG_CONTINUE_IN_DAYS = 55067 ;

/// 数据类型：int32; 域名：资金流入家数
const int H5SDK_TAG_TURNOVER_IN_COUNT = 55068 ;

/// 数据类型：int32; 域名：资金流出家数
const int H5SDK_TAG_TURNOVER_OUT_COUNT = 55069 ;

/// 数据类型：int64; 域名：主力总流入
const int H5SDK_TAG_MAIN_TOTAL_IN = 55070 ;

/// 数据类型：int64; 域名：主力总流出
const int H5SDK_TAG_MAIN_TOTAL_OUT = 55071 ;

/// 数据类型：int64; 域名：主力净流入
const int H5SDK_TAG_MAIN_NET_IN = 55072 ;

/// 数据类型：int64; 域名：散户总流入
const int H5SDK_TAG_RETAIL_TOTAL_IN = 55073 ;

/// 数据类型：int64; 域名：散户总流出
const int H5SDK_TAG_RETAIL_TOTAL_OUT = 55074 ;

/// 数据类型：int64; 域名：散户净流入
const int H5SDK_TAG_RETAIL_NET_IN = 55075 ;

/// 数据类型：int32; 域名：涨停家数
const int H5SDK_TAG_UPLIMIT_COUNT = 55077 ;

/// 数据类型：int32; 域名：跌停家数
const int H5SDK_TAG_DOWNLIMIT_COUNT = 55078 ;

/// 数据类型：int32; 域名：涨跌幅的档位：9表示大于9的涨幅，8表示大于8小于9的涨幅，-9表示小于-9的涨幅，-8表示小于-8大于-9的涨幅
const int H5SDK_TAG_CHG_LEVEL = 55079 ;

/// 数据类型：bytevector; 域名：市场类别(L1、L2)
const int H5SDK_TAG_MARKET_LEVEL = 20336 ;

/// 数据类型：int32; 域名：市场延时时间(0,15)分钟
const int H5SDK_TAG_MARKET_DELAY_MINS = 20337 ;

/// 数据类型：int32; 域名：基金T-1日期
const int H5SDK_TAG_FUND_T1_DATE = 20338 ;

/// 数据类型：uint64; 域名：基金T-1净值
const int H5SDK_TAG_FUND_T1_VALUE = 20339 ;

/// 数据类型：int32; 域名：基金T-2日期
const int H5SDK_TAG_FUND_T2_DATE = 20340 ;

/// 数据类型：uint64; 域名：基金T-2净值
const int H5SDK_TAG_FUND_T2_VALUE = 20341 ;

/// 数据类型：int32; 域名：基金开始日期
const int H5SDK_TAG_FUND_START_DATE = 20342 ;

/// 数据类型：int32; 域名：基金类型
/*0-未知;1-股票型;2-混合型;3-债券型;4-保本型;*/
const int H5SDK_TAG_FUND_TYPE = 20343 ;

/// 数据类型：int32; 域名：基金买状态
/*0-未知;1-开放;2-暂停;3-恢复;*/
const int H5SDK_TAG_FUND_BUY_STATUS = 20344 ;

/// 数据类型：int32; 域名：基金卖状态
/*0-未知;1-开放;2-暂停;3-恢复;*/
const int H5SDK_TAG_FUND_SELL_STATUS = 20345 ;

/// 数据类型：int64; 域名：基金估值涨跌幅(100倍)
const int H5SDK_TAG_FUND_ASSESS_CHANGE = 20346 ;

/// 数据类型：int64; 域名：基金实时涨跌幅(100倍)
const int H5SDK_TAG_FUND_REAL_CHANGE = 20347 ;

/// 数据类型：int64; 域名：逐笔成交额净量
const int H5SDK_TAG_TRANS_TOTAL_NET_TURNOVER = 55080 ;

/// 数据类型：int32; 域名：平盘家数
const int H5SDK_TAG_FLAT_COUNT = 55081 ;

/// 数据类型：uint32; 域名：成交编号
const int H5SDK_TAG_TRADE_INDEX = 20301 ;

/// 数据类型：uint32; 域名：叫买方编号
const int H5SDK_TAG_BUY_NO = 20302 ;

/// 数据类型：uint32; 域名：叫卖方编号
const int H5SDK_TAG_SELL_NO = 20303 ;

/// 数据类型：uint32; 域名：委托编号
const int H5SDK_TAG_ORDER_NO = 20304 ;

/// 数据类型：int64; 域名：基金净值基数
const int H5SDK_TAG_FUND_UNVT_BASE = 20349 ;

/// 数据类型：uint64; 域名：资金流入
const int H5SDK_TAG_MON_IN = 20350 ;

/// 数据类型：uint64; 域名：资金流出
const int H5SDK_TAG_MON_OUT = 20351 ;

/// 数据类型：int64; 域名：资金净流入
const int H5SDK_TAG_MON_PUREIN = 20352 ;

/// 数据类型：int32; 域名：开始档位
const int H5SDK_TAG_LEVEL_START = 20353 ;

/// 数据类型：int32; 域名：结束档位
const int H5SDK_TAG_LEVEL_END = 20354 ;

/// 数据类型：int8; 域名：是否（是/存在）大单  1:是/存在 2：不是/不存在
const int H5SDK_TAG_LAGER_ORDER = 20355 ;

/// 数据类型：int8; 域名：委买/卖方向 0:buy 1:sell
const int H5SDK_TAG_ENTRUST_BS_SIDE = 20356 ;

/// 数据类型：int64; 域名：指数上涨趋势 (多空指标)
const int H5SDK_TAG_INDEX_RISE_TREND = 20361 ;

/// 数据类型：int64; 域名：指数下跌趋势 (强弱度)
const int H5SDK_TAG_INDEX_FALL_TREND = 20362 ;

/// 数据类型：int32; 域名：服务类型（0：客户端1:网关服务器2:订阅服务器）
const int H5SDK_TAG_LOGIN_FLAG = 22001 ;

/// 数据类型：int32; 域名：登陆下载标志(第一位 0:不下载订阅列表，1：下载订阅列表)
const int H5SDK_TAG_CONTENT_FLAG = 22002 ;

/// 数据类型：rawdata; 域名：登陆内容，有登陆标志决定
const int H5SDK_TAG_LOGIN_CONTENT = 22003 ;

/// 数据类型：rawdata; 域名：订阅列表{"subscribes": [{"serverId": "subscribe1","ip": "192.168.0.1","port": "9991","marketMic": ["XDCE", "CCFX"],"funcNo": ["4001","4002","4003"]},{"serverId": "subscribe2","ip": "192.168.0.2","port": "9991","marketMic": ["DEFAULT"],"funcNo": ["4001"]}]}
const int H5SDK_TAG_SUBCRIBE_LIST = 22004 ;

/// 数据类型：rawdata; 域名：客户端session
const int H5SDK_TAG_CLIENT_SESSION = 22005 ;

/// 数据类型：uint32; 域名：best协议路由层crc检验码
const int GW_ROUTE_TEMPLET_CRC = 22006 ;

/// 数据类型：string; 域名：best协议路由层服务器ID
const int GW_ROUTE_SERVER_ID = 22007 ;

/// 数据类型：string; 域名：session节点在zookeeper中的路径
const int GW_ROUTE_SESSION_PATH = 22008 ;

/// 数据类型：string; 域名：市场类型代码
const int GW_ROUTE_HQ_TYPE_CODE = 22009 ;

/// 数据类型：string; 域名：股票或期货代码
const int GW_ROUTE_PROD_CODE = 22010 ;

/// 数据类型：string; 域名：session节点在zookeeper中的路径
const int H5SDK_TAG_SESSION_PATH = 22011 ;

/// 数据类型：uint32; 域名：网关服务：1 订阅服务:2
const int GW_ROUTE_SERVER_TYPE = 22012 ;

/// 数据类型：uint64; 域名：路由层客户端session
const int GW_ROUTE_CLIENT_SESSION = 22013 ;

/// 数据类型：int64; 域名：4位表示一个功能，第一个四位0:level1 1:level 2，第二个四位0:实时1:表示延时 如：0x10 （延时level1行情）
const int GW_ROUTE_HQ_LEVEL = 22014 ;

/// 数据类型：uint32; 域名：路由层错误号
const int GW_ROUTE_ERROR_NO = 22015 ;

/// 数据类型：uint32; 域名：0:自动初始化 1:强制初始化
const int H5SDK_TAG_INIT_FLAG = 22016 ;

/// 数据类型：bytevector; 域名：服务器id
const int H5SDK_TAG_SERVER_ID = 22017 ;

/// 数据类型：rawdata; 域名：网关服务器信息 0:{"markets": ["XDCE","CCFX" ]}
const int H5SDK_TAG_GW_SERVER_INFO = 22018 ;

/// 数据类型：uint32; 域名：服务器信息类型 0：表示市场类型
const int H5SDK_TAG_SERVER_INFO_TYPE = 22019 ;

/// 数据类型：sequence; 域名：服务器信息重复组
const int H5SDK_TAG_SERVER_INFO_GRP = 22020 ;

/// 数据类型：rawdata; 域名：后台服务器信息0:{"markets": [{"market": "XDCE", "tradedate": "20170228"}, {"market": "CCFX", "tradedate": "20170228"}]}
const int H5SDK_TAG_BACK_SERVER_INFO = 22021 ;

/// 数据类型：bytevector; 域名：enable 1:可用 0:不可用 {"markets":[{"market": "XDCE","enable": "1"},{"market": "CCFX","enable": "0"}]}
const int H5SDK_TAG_SERVER_SATAE = 22022 ;

/// 数据类型：bytevector; 域名：用户标志
const int GW_ROUTE_AUTH_ID = 22023 ;

/// 数据类型：bytevector; 域名：用户权限
const int GW_ROUTE_AUTH_STR = 22024 ;

/// 数据类型：rawdata; 域名：用户标志
const int GW_ROUTE_USER_KEY = 22025 ;

/// 数据类型：int16; 域名：数据字段订阅级别
const int H5SDK_TAG_FIELDS_LEVEL = 22026 ;

/// 数据类型：int16; 域名：路由层上的数据字段订阅级别
const int GW_ROUTE_FIELDS_LEVEL = 22027 ;

/// 数据类型：string; 域名：路由层appkey字段
const int GW_ROUTE_APP_KEY = 22028 ;

/// 数据类型：int8(枚举); 域名：取代码范围（默认为0）
const int H5SDK_TAG_STOCK_RANGE = 55082 ;
    const int8 H5SDK_TAG_STOCKESA = 0 ; // 全市场
    const int8 H5SDK_TAG_WITHOUT_SN = 1 ; // 非ST、新股
    const int8 H5SDK_TAG_STOCKST = 2 ; // ST股
    const int8 H5SDK_TAG_STOCKNEW = 3 ; // 新股

/// 数据类型：int8(枚举); 域名：分布类型（默认为0）
const int H5SDK_TAG_DIAGRAM_TYPE = 55083 ;
    const int8 H5SDK_TAG_COMMON_DIAGRAM = 0 ; // 通用分布
    const int8 H5SDK_TAG_STOCKEXST = 1 ; // 排除ST、新股的涨跌停分布

/// 数据类型：int8(枚举); 域名：指定代码关联类型进行获取历史数据
const int H5SDK_TAG_CODE_RELATE_TYPE = 55084 ;
    const int8 H5SDK_TAG_CODE_RELATE_NOMORAL_TYPE = 0 ; // 获取该代码对应的历史数据
    const int8 H5SDK_TAG_CODE_RELATE_CONTNO_TYPE = 1 ; // 获取该代码连1，连3，连4合约历史数据
    const int8 H5SDK_TAG_CODE_RELATE_MONCONTN_TYPE = 2 ; // 获取该代码按月连续历史数据

/// 数据类型：int8(枚举); 域名：控制获取代码表，是否是全量
const int H5SDK_TAG_CODE_FULL = 55085 ;
    const int8 H5SDK_TAG_CODE_NOMORAL = 0 ; // 普通SDK请求代码表，不是全量
    const int8 H5SDK_TAG_CODE_ALL = 1 ; // 全量请求代码表

/// 数据类型：uint32(枚举); 域名：异动信号类型
const int H5SDK_TAG_ANOMALY_SIGNAL_TYPE = 55086 ;

/// 数据类型：bytevector; 域名：异动信号名称
const int H5SDK_TAG_ANOMALY_SIGNAL_NAME = 55087 ;

/// 数据类型：sequence; 域名：异动信号列表
const int H5SDK_TAG_ANOMALY_SIGNAL_GRP = 55090 ;

/// 数据类型：sequence; 域名：异动信号结果列表
const int H5SDK_TAG_ANOMALY_SIGNAL_RESULT_GRP = 55091 ;

/// 数据类型：uint32; 域名：异动信号结果参数key
const int H5SDK_TAG_ANOMALY_SIGNAL_RESULT_KEY = 55092 ;

/// 数据类型：int64; 域名：异动信号结果参数值
const int H5SDK_TAG_ANOMALY_SIGNAL_RESULT_VALUE = 55093 ;

/// 数据类型：uint8(枚举); 域名：异动信号的方向
const int H5SDK_TAG_ANOMALY_SIGNAL_DIRECTION = 55094 ;
    const uint8 H5SDK_ENUM_PLAT_DIRECT = 0 ; // 平
    const uint8 H5SDK_ENUM_UP_DIRECT = 1 ; // 涨
    const uint8 H5SDK_ENUM_DOWN_DIRECT = 2 ; // 跌

/// 数据类型：uint32; 域名：值放大倍数
const int H5SDK_TAG_VALUE_SCALE = 55095 ;

/// 数据类型：int32; 域名：5.0市场类型
const int H5SDK_TAG_HQ50_MARKET_TYPE = 55096 ;

/// 数据类型：sequence; 域名：异动信号结果格式列表
const int H5SDK_TAG_ANOMALY_SIGNAL_FORMAT_GRP = 55097 ;

/// 数据类型：bytevector; 域名：展示前缀
const int H5SDK_TAG_FORMAT_PREFIX = 55098 ;

/// 数据类型：bytevector; 域名：展示后缀
const int H5SDK_TAG_FORMAT_SUFFIX = 55099 ;

/// 数据类型：uint8; 域名：展示小数点位数
const int H5SDK_TAG_FORMAT_DECIMAL_DIGITS = 55100 ;

/// 数据类型：sequence; 域名：板块代码列表
const int H5SDK_TAG_BLOCK_PROD_CODE_GRP = 55101 ;

/// 数据类型：uint32; 域名：标识special_marker请求的时候是需要满足所有的位，或者其中一个位
/*0：满足所有的特殊标志位
1：只需要满足其中一个位*/
const int H5SDK_TAG_MARK_TYPE = 55102 ;

/// 数据类型：uint32; 域名：成交标记，0：普通成交，1：撤单成交
const int H5SDK_TAG_TRANS_FLAG = 55103 ;

/// 数据类型：uint64; 域名：服务器日期
const int H5SDK_TAG_SERVER_DATE = 55104 ;

/// 数据类型：int32; 域名：盘前盘后日期
const int H5SDK_TAG_PREPOST_DATE = 20367 ;

/// 数据类型：int32; 域名：盘前盘后时间
const int H5SDK_TAG_PREPOST_time = 98 ;

/// 数据类型：int32; 域名：投资赢家的市场类型
const int H5SDK_TAG_HQ40_MARKET_TYPE = 55105 ;

/// 数据类型：int32; 域名：涨停家数
const int H5SDK_TAG_UP_LIMIT_COUNT = 20372 ;

/// 数据类型：int32; 域名：触板涨停家数
const int H5SDK_TAG_TOUCH_UP_LIMIT_COUNT = 20373 ;

/// 数据类型：int32; 域名：ST股涨停家数
const int H5SDK_TAG_ST_UP_LIMIT_COUNT = 20374 ;

/// 数据类型：int32; 域名：ST股触板涨停家数
const int H5SDK_TAG_ST_TOUCH_UP_LIMIT_COUNT = 20375 ;

/// 数据类型：int32; 域名：跌停家数
const int H5SDK_TAG_DOWN_LIMIT_COUNT = 20376 ;

/// 数据类型：int32; 域名：触板跌停家数
const int H5SDK_TAG_TOUCH_DOWN_LIMIT_COUNT = 20377 ;

/// 数据类型：int32; 域名：ST股跌停家数
const int H5SDK_TAG_ST_DOWN_LIMIT_COUNT = 20378 ;

/// 数据类型：int32; 域名：ST股触板跌停家数
const int H5SDK_TAG_ST_TOUCH_DOWN_LIMIT_COUNT = 20379 ;

/// 数据类型：sequence; 域名：异动因子数组
const int H5SDK_TAG_ANOMALY_FACTOR_GRP = 55106 ;

/// 数据类型：bytevector; 域名：异动因子名称
const int H5SDK_TAG_ANOMALY_FACTOR_NAME = 55107 ;

/// 数据类型：uint8; 域名：撤销标记，默认为0，表示普通的信号，值为1时表示撤销历史信号，在查询应答中该值永远为0，在主推信号中可以为其他值
const int H5SDK_TAG_CANCEL_FLAG = 55108 ;

/// 数据类型：int64; 域名：唯一标记一个异动信号的校验和
const int H5SDK_TAG_ANOMALY_SIGNAL_CRC = 55109 ;

/// 数据类型：int8(枚举); 域名：分时类别（默认为0）
const int H5SDK_TAG_TREND_TYPE = 55110 ;
    const int8 H5SDK_TAG_TREND_NORMAL = 0 ; // 240分钟类型
    const int8 H5SDK_TAG_TREND_CUSTOM = 1 ; // 241分钟类型

/// 数据类型：sequence; 域名：档位队列
const int H5SDK_TAG_LEVEL_GRP = 55111 ;

/// 数据类型：sequence; 域名：市场类型列表
const int H5SDK_TAG_HQ_MIC_TYPE_GRP = 55112 ;

/// 数据类型：int32; 域名：市场类型 0:全市场 1、上海非ST 2、上海ST 3、深圳非ST 4、深证ST
const int H5SDK_TAG_HQ_MIC_TYPE = 55113 ;

/// 数据类型：int32; 域名：统计类型 0:涨停家数（原因） 1、跌停家数 2、触碰涨停、3、触碰跌停
const int H5SDK_TAG_HQ_STATISTIC_TYPE = 55114 ;

/// 数据类型：int32; 域名：回测幅度
const int H5SDK_TAG_RETURN_RANGE = 55115 ;

/// 数据类型：int32; 域名：涨跌停原因
const int H5SDK_TAG_UPDOWN_REASON = 55116 ;

/// 数据类型：int64; 域名：统计结果
const int H5SDK_TAG_STATISTIC_RESULT = 55117 ;

/// 数据类型：sequence; 域名：涨跌停原因列表
const int H5SDK_TAG_UPDOWN_REASON_GRP = 55118 ;

/// 数据类型：uint8(枚举); 域名：涨跌停原因类型
const int H5SDK_TAG_STATISTIC_REASON_TYPE = 55119 ;
    const uint8 H5SDK_TAG_UP_REASON = 0 ; // 涨停类型
    const uint8 H5SDK_TAG_DOWN_REASON = 1 ; // 跌停类型

/// 数据类型：int32; 域名：平均涨幅
const int H5SDK_TAG_AVERAGE_RISE = 55122 ;

/// 数据类型：int32; 域名：子分类 0：all 1：ST股 2：非ST股
const int H5SDK_TAG_HQ_SUB_TYPE = 55123 ;

/// 数据类型：int32; 域名：昨日涨停的代码中今日涨停的个数
const int H5SDK_TAG_TODAY_UP_NUM = 55124 ;

/// 数据类型：int32; 域名：昨日涨停的代码数
const int H5SDK_TAG_YESTERDAY_UP_NUM = 55125 ;

/// 数据类型：int32; 域名：涨停次数
const int H5SDK_TAG_UP_COUNT = 55126 ;

/// 数据类型：int32; 域名：涨停后次日上涨次数
const int H5SDK_TAG_UP_NEXT_DAY_RISE_COUNT = 55127 ;

/// 数据类型：int32; 域名：涨停后次日平均涨跌幅
const int H5SDK_TAG_UP_NEXT_DAY_AVE_PCHANGE_RATE = 55128 ;

/// 数据类型：int32; 域名：跌停次数
const int H5SDK_TAG_DOWN_COUNT = 55129 ;

/// 数据类型：int32; 域名：跌停后次日上涨次数
const int H5SDK_TAG_DOWN_NEXT_DAY_RISE_COUNT = 55130 ;

/// 数据类型：int32; 域名：跌停后次日平均涨跌幅
const int H5SDK_TAG_DOWN_NEXT_DAY_AVE_PCHANGE_RATE = 55131 ;

/// 数据类型：int32; 域名：打板涨停次数
const int H5SDK_TAG_DBZT_COUNT = 55132 ;

/// 数据类型：int32; 域名：打板涨停后次日上涨次数
const int H5SDK_TAG_DBZT_NEXT_DAY_RISE_COUNT = 55133 ;

/// 数据类型：int32; 域名：打板涨停后次日平均涨跌幅
const int H5SDK_TAG_DBZT_NEXT_DAY_AVE_PCHANGE_RATE = 55134 ;

/// 数据类型：int32; 域名：跌停抄底次数
const int H5SDK_TAG_DTCD_COUNT = 55135 ;

/// 数据类型：int32; 域名：跌停抄底后次日上涨次数
const int H5SDK_TAG_DTCD_NEXT_DAY_RISE_COUNT = 55136 ;

/// 数据类型：int32; 域名：跌停抄底后次日平均涨跌幅
const int H5SDK_TAG_DTCD_NEXT_DAY_AVE_PCHANGE_RATE = 55137 ;

/// 数据类型：int64; 域名：最新成交价
const int H5SDK_TAG_LAST_EXT_PX = 55138 ;

/// 数据类型：int32; 域名：当前仅作为是否允许按盘价字段的标记
const int H5SDK_TAG_NOMINAL_PX = 55139 ;

/// 数据类型：uint64; 域名：超大单流入成交量
const int H5SDK_TAG_BUSINESS_BID_SUP_AMOUNT = 55140 ;

/// 数据类型：uint64; 域名：超大单流入成交额
const int H5SDK_TAG_BUSINESS_BID_SUP_BALANCE = 55141 ;

/// 数据类型：uint32; 域名：超大单流入成交笔数
const int H5SDK_TAG_BUSINESS_BID_SUP_COUNT = 55142 ;

/// 数据类型：uint32; 域名：超大单流入委托单数
const int H5SDK_TAG_BID_SUP_ENTRUST_COUNT = 55143 ;

/// 数据类型：uint64; 域名：大单流入成交量
const int H5SDK_TAG_BUSINESS_BID_BIG_AMOUNT = 55144 ;

/// 数据类型：uint64; 域名：大单流入成交额
const int H5SDK_TAG_BUSINESS_BID_BIG_BALANCE = 55145 ;

/// 数据类型：uint32; 域名：大单流入成交笔数
const int H5SDK_TAG_BUSINESS_BID_BIG_COUNT = 55146 ;

/// 数据类型：uint32; 域名：大单流入委托单数
const int H5SDK_TAG_BID_BIG_ENTRUST_COUNT = 55147 ;

/// 数据类型：uint64; 域名：中单流入成交量
const int H5SDK_TAG_BUSINESS_BID_MID_AMOUNT = 55148 ;

/// 数据类型：uint64; 域名：中单流入成交额
const int H5SDK_TAG_BUSINESS_BID_MID_BALANCE = 55149 ;

/// 数据类型：uint32; 域名：中单流入成交笔数
const int H5SDK_TAG_BUSINESS_BID_MID_COUNT = 55150 ;

/// 数据类型：uint32; 域名：中单流入委托单数
const int H5SDK_TAG_BID_MID_ENTRUST_COUNT = 55151 ;

/// 数据类型：uint64; 域名：小单流入成交量
const int H5SDK_TAG_BUSINESS_BID_LITTLE_AMOUNT = 55152 ;

/// 数据类型：uint64; 域名：小单流入成交额
const int H5SDK_TAG_BUSINESS_BID_LITTLE_BALANCE = 55153 ;

/// 数据类型：uint32; 域名：小单流入成交笔数
const int H5SDK_TAG_BUSINESS_BID_LITTLE_COUNT = 55154 ;

/// 数据类型：uint32; 域名：小单流入委托单数
const int H5SDK_TAG_BID_LITTLE_ENTRUST_COUNT = 55155 ;

/// 数据类型：uint64; 域名：超大单流出成交量
const int H5SDK_TAG_BUSINESS_OFFER_SUP_AMOUNT = 55156 ;

/// 数据类型：uint64; 域名：超大单流出成交额
const int H5SDK_TAG_BUSINESS_OFFER_SUP_BALANCE = 55157 ;

/// 数据类型：uint32; 域名：超大单流出成交笔数
const int H5SDK_TAG_BUSINESS_OFFER_SUP_COUNT = 55158 ;

/// 数据类型：uint32; 域名：超大单流出委托单数
const int H5SDK_TAG_OFFER_SUP_ENTRUST_COUNT = 55159 ;

/// 数据类型：uint64; 域名：大单流出成交量
const int H5SDK_TAG_BUSINESS_OFFER_BIG_AMOUNT = 55160 ;

/// 数据类型：uint64; 域名：大单流出成交额
const int H5SDK_TAG_BUSINESS_OFFER_BIG_BALANCE = 55161 ;

/// 数据类型：uint32; 域名：大单流出成交笔数
const int H5SDK_TAG_BUSINESS_OFFER_BIG_COUNT = 55162 ;

/// 数据类型：uint32; 域名：大单流出委托单数
const int H5SDK_TAG_OFFER_BIG_ENTRUST_COUNT = 55163 ;

/// 数据类型：uint64; 域名：中单流出成交量
const int H5SDK_TAG_BUSINESS_OFFER_MID_AMOUNT = 55164 ;

/// 数据类型：uint64; 域名：中单流出成交额
const int H5SDK_TAG_BUSINESS_OFFER_MID_BALANCE = 55165 ;

/// 数据类型：uint32; 域名：中单流出成交笔数
const int H5SDK_TAG_BUSINESS_OFFER_MID_COUNT = 55166 ;

/// 数据类型：uint32; 域名：中单流出委托单数
const int H5SDK_TAG_OFFER_MID_ENTRUST_COUNT = 55167 ;

/// 数据类型：uint64; 域名：小单流出成交量
const int H5SDK_TAG_BUSINESS_OFFER_LITTLE_AMOUNT = 55168 ;

/// 数据类型：uint64; 域名：小单流出成交额
const int H5SDK_TAG_BUSINESS_OFFER_LITTLE_BALANCE = 55169 ;

/// 数据类型：uint32; 域名：小单流出成交笔数
const int H5SDK_TAG_BUSINESS_OFFER_LITTLE_COUNT = 55170 ;

/// 数据类型：uint32; 域名：小单流出委托单数
const int H5SDK_TAG_OFFER_LITTLE_ENTRUST_COUNT = 55171 ;

/// 数据类型：sequence; 域名：文件队列
const int H5SDK_TAG_FILE_GRP = 55172 ;

/// 数据类型：bytevector; 域名：文件路径
const int H5SDK_TAG_FILE_PATH = 55173 ;

/// 数据类型：int16(枚举); 域名：文件类型
const int H5SDK_TAG_HQ_FILE_EXT = 55174 ;
    const int16 H5SDK_TAG_HQ_FILE_EXT_NORMAL = 0 ; // 原始数据文件
    const int16 H5SDK_TAG_HQ_FILE_EXT_ZIP = 1 ; // zip压缩文件

/// 数据类型：uint64; 域名：大小
const int H5SDK_TAG_SIZE = 55175 ;

/// 数据类型：sequence; 域名：三方公司或个人信息组
const int H5SDK_TAG_TERM_INFOSHEET_GRP = 55176 ;

/// 数据类型：bytevector; 域名：公司名称
const int H5SDK_TAG_TERM_COMP_NAME = 55177 ;

/// 数据类型：bytevector; 域名：公司完整名称或个人名称
const int H5SDK_TAG_TERM_CORR_NAME = 55178 ;

/// 数据类型：bytevector; 域名：个人title
const int H5SDK_TAG_TERM_CORR_TITLE = 55179 ;

/// 数据类型：bytevector; 域名：EMAIL
const int H5SDK_TAG_TERM_CORR_EMAIL = 55180 ;

/// 数据类型：bytevector; 域名：联系电话
const int H5SDK_TAG_TERM_CORR_PHONE = 55181 ;

/// 数据类型：bytevector; 域名：公司或者个人详细联系地址
const int H5SDK_TAG_TERM_CORR_ADDRESS = 55182 ;

/// 数据类型：bytevector; 域名：用户帐号
const int H5SDK_TAG_TERM_USER_ACCOUNT = 55183 ;

/// 数据类型：bytevector; 域名：使用行情，比如 XHKG-M,XHKG-G等
const int H5SDK_TAG_TERM_QUOTE_MARKET = 55184 ;

/// 数据类型：bytevector; 域名：终端软件名称
const int H5SDK_TAG_TERM_APP_NAME = 55185 ;

/// 数据类型：uint32; 域名：行情热度值
const int H5SDK_TAG_HQ_HOT_SCORE = 55186 ;

/// 数据类型：uint32; 域名：盯盘字段
const int H5SDK_TAG_STARE_FIELD = 55187 ;

/// 数据类型：int16(枚举); 域名：盯盘方向
const int H5SDK_TAG_STARE_DIRECTION = 55188 ;
    const int16 H5SDK_TAG_STARE_DIRECTION_RISE = 0 ; // 盯盘方向向上
    const int16 H5SDK_TAG_STARE_DIRECTION_FALL = 1 ; // 盯盘方向向下

/// 数据类型：int64; 域名：盯盘字段对应的监控值
const int H5SDK_TAG_STARE_VALUE = 55189 ;

/// 数据类型：bytevector; 域名：盯盘触发时的回带数据
const int H5SDK_TAG_STARE_USER_DATA = 55190 ;

/// 数据类型：int64; 域名：盯盘触发时对应的盯盘字段里的快照值
const int H5SDK_TAG_SNAPSHOT_VALUE = 55191 ;

/// 数据类型：sequence; 域名：委买档位
const int H5SDK_TAG_HK_BID_GRP = 55192 ;

/// 数据类型：sequence; 域名：委卖档位
const int H5SDK_TAG_HK_OFFER_GRP = 55193 ;

/// 数据类型：int32; 域名：档位编号
const int H5SDK_TAG_HK_SPREAD_LEVEL = 55194 ;

/// 数据类型：sequence; 域名：委托订单列表
const int H5SDK_TAG_HK_ENTRUST_GRP = 55195 ;

/// 数据类型：uint32; 域名：委托量
const int H5SDK_TAG_HK_ENTRUST_AMOUNT = 55196 ;

/// 数据类型：sequence; 域名：港股点击报价
const int H5SDK_TAG_HK_CLICK_PRICE_GRP = 55197 ;

/// 数据类型：uint32; 域名：实时一档本月总次数
const int H5SDK_TAG_ONE_LEVEL_COUNT = 55198 ;

/// 数据类型：uint32; 域名：实时十档本月总次数
const int H5SDK_TAG_TEN_LEVEL_COUNT = 55199 ;

/// 数据类型：uint32; 域名：实时十档与经济队列本月总次数
const int H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_COUNT = 55200 ;

/// 数据类型：uint32; 域名：实时一档剩余次数
const int H5SDK_TAG_ONE_LEVEL_CURR_NUM = 55201 ;

/// 数据类型：uint32; 域名：实时十档剩余次数
const int H5SDK_TAG_TEN_LEVEL_CURR_NUM = 55202 ;

/// 数据类型：uint32; 域名：实时十档与经济队列剩余次数
const int H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_CURR_NUM = 55203 ;

/// 数据类型：uint32(枚举); 域名：实时一档是否无限次使用
const int H5SDK_TAG_ONE_LEVEL_LIMIT = 55204 ;
    const uint32 H5SDK_TAG_ONE_LEVEL_ENABLE = 0 ; // 
    const uint32 H5SDK_TAG_ONE_LEVEL_DISABLE = 1 ; // 

/// 数据类型：uint32(枚举); 域名：实时十档是否无限次使用
const int H5SDK_TAG_TEN_LEVEL_LIMIT = 55207 ;
    const uint32 H5SDK_TAG_TEN_LEVEL_ENABLE = 0 ; // 
    const uint32 H5SDK_TAG_TEN_LEVEL_DISABLE = 1 ; // 

/// 数据类型：uint32(枚举); 域名：实时十档与经济队列是否无限次使用
const int H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_LIMIT = 55210 ;
    const uint32 H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_ENABLE = 0 ; // 
    const uint32 H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_DISABLE = 1 ; // 

/// 数据类型：sequence; 域名：委买经济档位
const int H5SDK_TAG_BID_BROKER_GRP = 55213 ;

/// 数据类型：sequence; 域名：委卖经济档位
const int H5SDK_TAG_OFFER_BROKER_GRP = 55214 ;

/// 数据类型：int32; 域名：每股转赠（股）
const int H5SDK_TAG_ZZSHARERAIO = 55215 ;

/// 数据类型：int32; 域名：每股对价股票（股）
const int H5SDK_TAG_DJSHARERAIO = 55216 ;

/// 数据类型：int32; 域名：每股对价现金（元）
const int H5SDK_TAG_DJCASHDIVI = 55217 ;

/// 数据类型：int32; 域名：每股缩股（股）
const int H5SDK_TAG_SGSHARERAIO = 55218 ;

/// 数据类型：int32; 域名：每股拆分（股）
const int H5SDK_TAG_CFSHARERAIO = 55219 ;

/// 数据类型：bytevector; 域名：因子
const int H5SDK_TAG_EXER_FACTOR = 55220 ;

/// 数据类型：bytevector; 域名：常数
const int H5SDK_TAG_CONST_VALUE = 55221 ;

/// 数据类型：bytevector; 域名：标记信息
const int H5SDK_TAG_MARK = 55222 ;

/// 数据类型：bytevector; 域名：后复权比例因子
const int H5SDK_TAG_BACKWARD_FACTOR = 55223 ;

/// 数据类型：bytevector; 域名：前复权比例因子
const int H5SDK_TAG_FORWARD_FACTOR = 55224 ;

/// 数据类型：uint32(枚举); 域名：日线九转信号
const int H5SDK_TAG_NINE_TURN_SIGNAL_DAY = 55225 ;
    const uint32 H5SDK_TAG_NINE_TURN_SIGNAL_DAY_BUY = 1 ; // 日线九转买入信号
    const uint32 H5SDK_TAG_NINE_TURN_SIGNAL_DAY_SELL = 2 ; // 日线九转卖出信号

/// 数据类型：uint32(枚举); 域名：分时九转信号
const int H5SDK_TAG_NINE_TURN_SIGNAL_TREND = 55226 ;
    const uint32 H5SDK_TAG_NINE_TURN_SIGNAL_TREND_BUY = 1 ; // 分时九转买入信号
    const uint32 H5SDK_TAG_NINE_TURN_SIGNAL_TREND_SELL = 2 ; // 分时九转卖出信号

/// 数据类型：int32; 域名：板块排序，不填表示混排。1表示对一级板块排序。2表示对二级板块排序
const int H5SDK_TAG_SORT_LEVEL = 55227 ;

/// 数据类型：bytevector; 域名：字符串型前复权常数
const int H5SDK_TAG_EXER_FORWARD_B_STR = 55228 ;

/// 数据类型：bytevector; 域名：字符串型后复权常数
const int H5SDK_TAG_EXER_BACKWARD_B_STR = 55229 ;


#endif /* __H5_SDK_TAG_H__ */

