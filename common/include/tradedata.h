/**
 * @file    tradedata.h
 *
 * ���״���Ļ������ݽṹ����
 *
 * @version 0.1.1      2019/09/20
 *          - �������������β���ģ���뽻�״���֮�佻���Ļ������ݽṹ
 **/

#include <stdint.h>
#include <string>
#include <iostream>
#ifndef TRADE_DATA_TYPE_H
#define TRADE_DATA_TYPE_H

namespace TD // trade data
{
    //�������order_id�����ڲ���ģ��/���״���/��̨API֮�������������
    //32λ�������order_id�����bitλ�����估����
    //bit 31 30 29 ...........15  14  13  12   11 10 ....0
    //   [ ���״����ڲ�������    ][���Խ�������][ ���Զ����� ]
    //���Խ���������Ϊbit12~14, ��3λ��ʵ��֧�ֵ������Խ�����Ϊ7������Ϊ��Ҫ�����7����Ϊ�ڲ�ʹ��

#define STRATEGY_INFO_BIT_COUNT 15
//������index����������Ϣռ�õ�λ�������ڴӷ��ص�order_id�л�ȡindex
#define STRATEGY_INFO_BIT_COUNT_EXINDEX 12
#define DEFAULT_ORDERREF_START 0x1

//�������ڸ�����ò��Խ���index�ĺ�
#define INNER_REF_BIT_COUNT (32 - STRATEGY_INFO_BIT_COUNT)
#define STRATEGY_INDEX_MASK ((0xFFFFFFFF << STRATEGY_INFO_BIT_COUNT_EXINDEX) & (0xFFFFFFFF >> INNER_REF_BIT_COUNT))
#define STRATEGY_CTX_MASK (0xFFFFFFFF >> (INNER_REF_BIT_COUNT + STRATEGY_INFO_BIT_COUNT - STRATEGY_INFO_BIT_COUNT_EXINDEX))
#define INNER_ORDERREF_MASK (0xFFFFFFFF << STRATEGY_INFO_BIT_COUNT)
#define TOTAL_STRATEGY_PROCESS_COUNT ((STRATEGY_INDEX_MASK >> STRATEGY_INFO_BIT_COUNT_EXINDEX) + 1)
#define MAX_SUSPEND_COUNT (STRATEGY_CTX_MASK + 1)
#define SYS_MIN_REF (DEFAULT_ORDERREF_START << STRATEGY_INFO_BIT_COUNT)
//�Ӷ�������ȡ�ò��Խ�������
#define GET_STRATEGY_ID(order_id) ((order_id & STRATEGY_INDEX_MASK) >> STRATEGY_INFO_BIT_COUNT_EXINDEX)

#define CACHE_LINE_SIZE 64			        //�����г���

    constexpr int MAX_STRATEGY = 8;             //��������Ŀ+1
    constexpr int MAX_TRADER = 16;              //������˺���Ŀ
    constexpr int INSTRUMENT_ID_LEN = 32;		//��Լ���볤��
    constexpr int ACCOUNT_ID_LEN = 32;			//�ʽ��˺ų���
    constexpr int ERROR_MSG_LEN = 128;			//������Ϣ�ַ�������
    constexpr int QUEUE_NAME_LEN = 128;			//���������ַ�������
    constexpr int QRY_RTN_CONTINUE = 0;			//��ѯ�ر��ǽ�β��־
    constexpr int QRY_RTN_EOF = 1;      		//��ѯ�ر���β��־

//======================BSType ��������==========================
enum class BSType : int8_t
{
    Unknown = '0',
    Buy,		//��
    Sell,		//��
    CancelOrder //����
};

//======================Offset ��ƽ����==========================
enum class Offset : int8_t
{
    Unknown = '0',
    Open,
    Close,
    CloseToday,
    CloseYesterday
};

//======================Direction ��շ���==========================
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
| �������� |  �Ͻ���  |  ���  | ������ |  �н���  |  ������  |  ֣����  |
| :----: | :----: | :----: | :----: | :----: | :----: | :----: |
| Limit |�޼�|�޼�|�޼�|�޼�|�޼�|�޼�|
| Any |�����嵵ʣ�೷��|��ʱ�ɽ�ʣ�೷��|�м�|�м�|�м�|�м�|
| FakBest5 |�����嵵��ʱ�ɽ�ʣ�೷��|�����嵵��ʱ�ɽ�ʣ�೷��|��֧��|��֧��|��֧��|��֧��|
| ForwardBest |�����嵵��ʱ�ɽ�ʣ��ת�޼�|���ַ����ż۸��걨|��֧��|��֧��|��֧��|��֧��|
| ReverseBest |�������ż۸��걨|��֧��|��֧��|��֧��|��֧��|��֧��|
| Fak |��֧��|(�м�)��ʱ�ɽ�ʣ�೷��|(�޼�)��ʱ�ɽ�ʣ�೷��|(�޼�)��ʱ�ɽ�ʣ�೷��|(�޼�)��ʱ�ɽ�ʣ�೷��|(�޼�)��ʱ�ɽ�ʣ�೷��|
| Fok |��֧��|(�м�)ȫ��ɽ����߳���|(�޼�)ȫ��ɽ����߳���|(�޼�)ȫ��ɽ����߳���|(�޼�)ȫ��ɽ����߳���|(�޼�)ȫ��ɽ����߳���|

�ڻ�fok��fak
�����۸�Ϊ�޼ۣ�����ʱ��ͽ�������������

| �������� | PriceType  |  TimeCondition  |  VolumeCondition  |
| :----: | :----: | :----: | :----: |
| Fok |Limit|IOC|All|
| Fak |Limit|IOC|Any|
**/

//======================OrderType ��������==========================
enum class OrderType : int8_t
{
    UnKnown = '0',
    Limit,                  //�޼�,֤ȯͨ��
    Market,                 //�мۣ�֤ȯͨ�ã����ڹ�Ʊ�Ϻ�Ϊ�����嵵ʣ�೷��������Ϊ��ʱ�ɽ�ʣ�೷��
    FakBest5,               //�Ϻ����������嵵��ʱ�ɽ�ʣ�೷��������Ҫ����
    ForwardBest,            //���ڱ������ż۸��걨, ����Ҫ����
    ReverseBest,            //�Ϻ������嵵��ʱ�ɽ�ʣ��ת�޼�, ���ڶ��ַ����ż۸��걨������Ҫ����
    Fak,                    //���ڼ�ʱ�ɽ�ʣ�೷��������Ҫ����
    Fok                     //�����м�ȫ��ɽ����߳���������Ҫ����
};

//=======================����״̬==============================
enum class OrderStatus : int8_t
{
    Unknown = '0',	//δ֪
    Sended,			//�ѷ��͵����״���
    Submitted,		//�������ύ����̨
    Placed,			//��̨֪ͨ�����ѱ�������ȷ��
    Cancelled,		//�����ѳ���
    Error,			//��������
    Rejected,		//�����ܾ�
    PartialFilled,  //���ֳɽ�
    Filled			//ȫ���ɽ�
};

enum class InstrumentType : int8_t
{
    Unknown = '0',
    Stock,      //��Ʊ
    Bond,		//ծȯ
    ETF,		//ETF
    Fund,		//����
    ETFOption,  //ETF��Ȩ
    StockOption,//������Ȩ
    FutureOption//�ڻ���Ȩ
};

enum class MarketId : int8_t
{
    Unknown = '0',
    MKT_SH_ASHARE,        //�Ϻ�A��
    MKT_SZ_ASHARE,        //����A��
    MKT_SH_OPTION,        //�Ϻ���Ȩ
};

//�±���/�¶���
struct NewOrderField
{
	char instrument_id[INSTRUMENT_ID_LEN];		//��Լ���룬A�ɹ�Ʊֻ�������ֲ��֣�����ǰ׺��SH�� �͡�SZ��
	unsigned int order_id;						//�������/��������
    InstrumentType instrument_type;				//��Լ����
    MarketId market_id;							//�г�id
	BSType side;								//��������
	Offset offset;								//��ƽ����
	OrderType order_type;						//�µ�����
	OrderStatus order_status;					//����״̬
	int limit_price;							//ί�м۸�, ��λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	int64_t quantity;							//ί������, ��λ���ɣ��Ѿ����뵽100��������
	int64_t filled_quantity;					//�ѳɽ�����
	int64_t update_time;						//�ڲ�����״̬����ʱ��������뼶������ 1560144011373015000
};

//��������������/�ĵ��ȣ�
struct OrderActionField
{
	char instrument_id[INSTRUMENT_ID_LEN];		//��Լ���룬A�ɹ�Ʊֻ�������ֲ��֣�����ǰ׺��SH�� �͡�SZ��
	unsigned int order_id;						//���������/��������
	unsigned int action_order_id;				//�������Ķ������/��������
	OrderActionFlag action_flag;				//������������
    InstrumentType instrument_type;				//��Լ����
    MarketId market_id;							//�г�id
	BSType side;								//��������
	Offset offset;								//��ƽ����
	OrderType order_type;						//�µ�����
	int limit_price;							//ί�м۸�, ��λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	int64_t quantity;							//ί������, ��λ�� �ɣ��Ѿ����뵽100��������
};

//��ѯ����������ֶ�
struct QueryDataField
{
    char instrument_id[INSTRUMENT_ID_LEN];		//��Լ����
	InstrumentType instrument_type;				//��Լ����
	MarketId market_id;							//�г�id
};

enum class Status : int8_t
{
	OK = 0,
	ERROR
};

//����֤ȯ��Ϣ�Ļر��ֶ�
struct RtnSecInfoField
{
    char instrument_id[INSTRUMENT_ID_LEN];		//��Լ����
	Status status;								//�ر�ִ��״̬
    InstrumentType instrument_type;				//��Լ����
	MarketId market_id;							//�г�id
    int ceil_price;								//��ͣ��, ��λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
    int floor_price;							//��ͣ��, ��λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	bool is_last;								//�Ƿ����һ����Ϣ
	int error_id;								//����id
};

//ί�лر��ֶ�
struct RtnOrderField
{
    char instrument_id[INSTRUMENT_ID_LEN];		//��Լ����
	unsigned int order_id;						//�������/��������
    InstrumentType instrument_type;				//��Լ����
	BSType side;								//��������
	Offset offset;								//��ƽ����
	OrderType order_type;						//�µ�����
	OrderStatus order_status;					//����״̬
	int limit_price;							//�۸�, ��λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	int64_t quantity;							//����
	int filled_quantity;						//�ѳɽ�����
	int leave_quantity;							//ʣ��δ�ɽ�����
	int64_t update_time;						//�ڲ�����״̬����ʱ��������뼶������ 1569578501097222774
	int order_time;								//�ӹ�̨���صĶ���ί��ʱ�� (��ʽΪ HHMMSSsss, ���� 141205000)
	int confirmed_time;							//�ӹ�̨���صĶ���ί��ȷ��ʱ�� (��ʽΪ HHMMSSsss, ���� 141206000)
	int error_id;								//����ID
};

//�ɽ��ر��ֶ�
struct RtnTradeField
{
    char instrument_id[INSTRUMENT_ID_LEN];		//��Լ����
	unsigned int order_id;						//�������/��������
    InstrumentType instrument_type;				//��Լ����
	BSType side;								//��������
	Offset offset;								//��ƽ����
	OrderType order_type;						//�µ�����
	OrderStatus order_status;					//����״̬
	int price;									//�ɽ��۸�, ��λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	int64_t quantity;							//�ɽ�����
	int64_t filled_quantity;					//�ѳɽ�����
	int64_t leave_quantity;						//ʣ��δ�ɽ�����
	int64_t update_time;						//�ڲ�����״̬����ʱ��������뼶������ 1569578501097222774
	int execution_time;							//�ӹ�̨���صĶ����ɽ�ʱ�� (��ʽΪ HHMMSSsss, ���� 141205000)
};

//Ͷ���ֲֻ߳ر��ṹ��
struct RtnPositionField
{
	char instrument_id[INSTRUMENT_ID_LEN];		//��Լ����
	Status status;								//�ر�ִ��״̬
	int64_t total_quantity;						//�ֲܳ�
	int64_t cost_price;							//�ֲֳɱ���
	int64_t yesterday_quantity;					//�ճ��ֲ�/�������
    int64_t today_buy_quantity;					//�����ۼ�����
    int64_t today_sell_quantity;				//�����ۼ�����
	InstrumentType instrument_type;				//��Լ����
	BSType side;								//�ֲַ���
	bool is_last;								//�Ƿ����һ����Ϣ
	int error_id;								//����id
};

//�����µ���Ϣ�ر��ֶ�
struct RtnTradeInfoField
{
	unsigned int last_order_id;					//ĳһ���Ե������µ���ţ���12λȫ����Ϊ0��
	unsigned int trade_date;					//�������ڣ�����20190928
};

//�˻���Ϣ�ر��ֶ�
struct RtnCashAssetField
{
	char account[ACCOUNT_ID_LEN];			//�ʽ��˺�
	Status status;								//�ر�ִ��״̬
	int64_t total_cash;							//��ǰ������λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	int64_t avail_cash;							//��ǰ��������λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	bool is_last;								//�Ƿ����һ����Ϣ
	int error_id;								//����id
};

//��ʷ�ɽ���Ϣ�ر��ֶ�
struct RtnTradeHistory
{
	char instrument_id[INSTRUMENT_ID_LEN];		//��Լ����
	Status status;								//�ر�ִ��״̬
	unsigned int order_id;						//�������/��������
    InstrumentType instrument_type;				//��Լ����
	BSType side;								//��������
	Offset offset;								//��ƽ����(�ڻ�)
	int price;									//�ɽ��۸�, ��λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	int64_t quantity;							//�ɽ�����
	int execution_time;							//�ӹ�̨���صĶ����ɽ�ʱ�� (��ʽΪ HHMMSSsss, ���� 141205000)
	bool is_last;								//�Ƿ����һ����Ϣ
	int error_id;								//����id
};

//������ʷ�ر��ֶ�
struct RtnOrderHistory
{
	char instrument_id[INSTRUMENT_ID_LEN];		//��Լ����
	Status status;								//�ر�ִ��״̬
	unsigned int order_id;						//�������/��������
    InstrumentType instrument_type;				//��Լ����
	BSType side;								//��������
	Offset offset;								//��ƽ����
	OrderType order_type;						//�µ�����
	OrderStatus order_status;					//����״̬
	char order_completed_flag;					//����������־, 1:������0��δ����
	int price;							        //ί�м۸�, ��λ��ȷ��Ԫ����λ, ��1Ԫ = 10000
	int64_t quantity;							//ί������
	int filled_quantity;						//�ѳɽ�����
	int cancelled_quantity;						//�ѳ�������
	bool is_last;								//�Ƿ����һ����Ϣ
	int error_id;								//����id
};

//ʵʱ���ָ��ر��ֶ�
struct RtnOpenValChange
{
    uint64_t curr_traded_value;					//��ǰ����ȫ����Լ�Ľ��׳ɽ��ܽ��
    uint64_t curr_open_value;					//��ǰ����ȫ����Լ�ĳֲֺͿ��ֹҵ��ܽ��
    uint64_t limit_open_value;					//���Գֲ��ܽ������
};

//������Ϣ���Ͷ���
enum class ReqMsgType : int32_t
{
	REQ_NEW_ORDER = 0,					//�µ�����/�¶���,
	REQ_ORDER_ACTION,						//�����޸ģ�����or�ĵ���
											//��Ӧ�Ļر���Ϣ RTN_ORDER ����ί�лر���Ϣ
											//				RTN_TRADE �����ɽ��ر���Ϣ

	REQ_QRY_POSITION,						//��ѯ�ֲ�
											//��Ӧ�Ļر���Ϣ RTN_POSITION �ֲֻر�

	REQ_QRY_TRADE_INFO,						//��ѯ�ڲ�������Ϣ�������ڲ�������etc��
											//��Ӧ�Ļر���Ϣ RTN_TRADE_INFO �ڲ�������Ϣ�ر�

	REQ_QRY_CASH_ASSET,						//��ѯ�˻�
											//��Ӧ�Ļر���Ϣ RTN_CASH_ASSET �˻��ر�

	REQ_QRY_SEC_INFO,						//��ѯ֤ȯƷ����Ϣ
											//��Ӧ�Ļر���Ϣ RTN_SEC_INFO ֤ȯƷ����Ϣ�ر�

	REQ_QRY_ORDER_HISTORY,					//��ѯ������ʷ��Ϣ
											//��Ӧ�Ļر���Ϣ RTN_ORDER_HISTORY ������ʷ��Ϣ�ر�

	REQ_QRY_TRADE_HISTORY,					//��ѯ�ɽ���ʷ��Ϣ
											//��Ӧ�Ļر���Ϣ RTN_TRADE_HISTORY �ɽ���ʷ��Ϣ�ر�
};

//�ر���Ϣ���Ͷ���
enum class RtnMsgType : int32_t
{
	RTN_ORDER = 0,						//����ί�лر���Ϣ
	RTN_TRADE,								//�����ɽ��ر���Ϣ
	RTN_POSITION,							//�ֲֻر�
	RTN_TRADE_INFO,							//�ڲ�������Ϣ�ر�
	RTN_CASH_ASSET,							//�˻��ر�
	RTN_SEC_INFO,							//֤ȯƷ����Ϣ�ر�
	RTN_ORDER_HISTORY,						//������ʷ��Ϣ�ر�
	RTN_TRADE_HISTORY,						//�ɽ���ʷ��Ϣ�ر�
    RTN_OPEN_VAL_CHANGE                     //�ֲֽ����Ϣ�ر�
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
	ReqMsgType type __attribute__( ( aligned( CACHE_LINE_SIZE ) ) );//��Ϣ����
    int request_id;							//������
    int dest_account_id;                   //�����Ӧ���˺�ID
    union
    {
        struct NewOrderField new_order;
        struct OrderActionField order_action;
        struct QueryDataField qry_data;
    } data; // access with some_info_object.data.a or some_info_object.data.b
    int reserved[4];                        //����δ�����ֶ�����
};

struct TradeRtnMsg
{
	RtnMsgType type __attribute__( ( aligned( CACHE_LINE_SIZE ) ) );//��Ϣ����
	int request_id;							//������
    int dest_account_id;					//�ر���Ӧ���˺�ID
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
    int reserved[4];                        //����δ�����ֶ�����
};

//�����ڲ��������
enum ErrorType
{
    ERROR_ID_START = 10000,         //��ʼ�����
    REQ_SEND_FAILURE,               //������ʧ��
};
}; // end of namespace TD

#endif /* TRADE_DATA_TYPE_H */