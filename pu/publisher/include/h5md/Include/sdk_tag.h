/**
 *Դ��������:sdk_tag.h
 *�������Ȩ:�������ӹɷ����޹�˾
 *ϵͳ����:H5����Э��
 *ģ������:H5����Э��
 *����˵��:����H5����Э���е��ֶ�TAG
 *��    ��: ��С��
 *��������: 2018/9/20 13:18:48
 *�� �� ��: 1.0.0.127
 *��    ע: �����ĵ���H5�������Э��(�޶���).xls������
 */

#ifndef __H5_SDK_TAG_H__
#define __H5_SDK_TAG_H__

#include "hscomm_message_interface.h"

#define MESSAGE_TEMPLATE_VERSION	"1.0.0.127"


/*****************������Ϣ����*******************/
const int H5PROTO_HEAD_INFO = 0 ; // 
const int H5SDK_MSG_LOGIN = 1001 ; // ��������
const int H5SDK_MSG_LOGOUT = 1002 ; // �ǳ���Ϣ
const int H5SDK_MSG_HEARTBEAT = 1003 ; // ����
const int H5SDK_SERVER_INFO = 1004 ; // �����������Ϣ
const int H5SDK_MSG_BATCH = 1006 ; // ������
const int H5SDK_MSG_REGISTER = 1005 ; // ע������
const int H5SDK_MSG_CHANGE_USER_INFO = 1007 ; // �޸��û���Ϣ
const int H5SDK_MSG_USER_KICK_OFF = 1008 ; // �������������������Ϣ�����ƣ�
const int H5SDK_MSG_PUSH_USER_AUTH = 1009 ; // �ͻ���Ȩ�ޱ�������ƣ�
const int H5SDK_MSG_PUSH_USER_REQ = 1010 ; // �ͻ���Ȩ������
const int H5SDK_MSG_CLIENT_INFO = 1011 ; // �ͻ�����Ϣ��ѯ
const int H5SDK_MSG_FILE = 2001 ; // ����̬�ļ�
const int H5SDK_MSG_MARKET_TYPES = 2002 ; // �г�������Ϣ
const int H5SDK_MSG_MARKET_REFERENCE = 2003 ; // �г������
const int H5SDK_MSG_UNDERLYING_CODE = 2004 ; // ͨ��������ҹ�������
const int H5SDK_MSG_EXER = 2005 ; // ��Ȩ��Ϣ
const int H5SDK_MSG_F10_INDEX = 2006 ; // ��Ѷ��Ϣ����
const int H5SDK_MSG_F10_TXT = 2007 ; // ��Ѷ����
const int H5SDK_MSG_CODE_PROPERTY = 2008 ; // ��Ʒ������Ϣ
const int H5SDK_MSG_EXER_BY_DATE = 2009 ; // �����ڲ�ѯ��Ȩ��Ϣ
const int H5SDK_MSG_USER_INFOSHEET = 2010 ; // ��ȡ�û���Ϣ
const int H5SDK_MSG_EXER_EXT = 2011 ; // ��չ��Ȩ��Ϣ
const int H5SDK_MSG_SNAPSHOT = 3001 ; // �������
const int H5SDK_KEYBOARD_WIZARD = 3002 ; // ���̾�����Ϣ
const int H5SDK_MSG_L2_TRANSCATION = 3003 ; // ��ʳɽ�
const int H5SDK_MSG_L2_ORDER = 3004 ; // ���ί��
const int H5SDK_MSG_NEEQ_XYZRSB = 3005 ; // ������Э��ת���걨
const int H5SDK_MSG_HK_BROKER_QUEUE = 3006 ; // �۹ɾ��Ͷ���
const int H5SDK_MSG_HK_VCM = 3007 ; // �۹��е�
const int H5SDK_MSG_HK_CAS = 3008 ; // �۹����о���
const int H5SDK_MSG_THOUSAND_LEVEL_QUOTES_SNAPSHOT = 3009 ; // ǧ�����鵵λ����
const int H5SDK_MSG_THOUSAND_LEVEL_QUOTES_DETAIL_ENTRUST_SNAPSHOT = 3010 ; // ǧ��������ϸί�ж��п���
const int H5SDK_MSG_THOUSAND_LEVEL_QUOTES_DETAIL_ENTRUST_RANGE_SNAPSHOT = 3011 ; // ǧ�����鰴��λ��ѯ��ϸί�ж���
const int H5SDK_MSG_SUBSCRIBE = 4001 ; // ������ն���
const int H5SDK_MSG_SUBSCRIBE_L2_TRANSCATION = 4002 ; // l2��ʳɽ�����
const int H5SDK_MSG_SUBSCRIBE_L2_ORDER = 4003 ; // l2���ί�ж���
const int H5SDK_MSG_SUBSCRIBE_NEEQ_XYZRSB = 4004 ; // ������Э��ת���걨����
const int H5SDK_MSG_SUBSCRIBE_HK_BQ = 4005 ; // �۹ɾ��Ͷ��ж���
const int H5SDK_MSG_SUBSCRIBE_HK_VCM = 4006 ; // �۹��е�����
const int H5SDK_MSG_SUBSCRIBE_HK_CAS = 4007 ; // �۹����о��۶���
const int H5SDK_MSG_SUBSCRIBE_L2_TRANSCATION_BY_MARKET = 4008 ; // ���г�����l2��ʳɽ�
const int H5SDK_MSG_SUBSCRIBE_L2_ORDER_BY_MARKET = 4009 ; // ���г�����l2���ί��
const int H5SDK_MSG_SUBSCRIBE_NEEQ_XYZRSB_BY_MARKET = 4010 ; // ���г�����������Э��ת���걨
const int H5SDK_MSG_SUBSCRIBE_BY_MARKET = 4011 ; // ���г������������
const int H5SDK_MSG_SUBSCRIBE_US_REALTIME = 4012 ; // ����ʵʱ����������ն���
const int H5SDK_MSG_SUBSCRIBE_HK_BQ_BY_MARKET = 4013 ; // ���г����ĸ۹ɾ��Ͷ���
const int H5SDK_MSG_SUBSCRIBE_HK_VCM_BY_MARKET = 4014 ; // ���г����ĸ۹��е�
const int H5SDK_MSG_SUBSCRIBE_HK_CAS_BY_MARKET = 4015 ; // ���г����ĸ۹����о���
const int H5SDK_MSG_SUBSCRIBE_US_REALTIME_BY_MARKET = 4016 ; // ���г�������ʵʱ�������
const int H5SDK_MSG_SORT = 5001 ; // ��������
const int H5SDK_MSG_TREND = 6001 ; // ��ָ�������ڻ�ƫ��ȡ��ʱ����
const int H5SDK_MSG_CANDLE_BY_OFFSET = 6002 ; // ��ƫ��ȡK��
const int H5SDK_MSG_CANDLE_BY_RANGE = 6003 ; // ������ʱ�䷶ΧȡK��
const int H5SDK_MSG_TICK_MIN = 6004 ; // ָ�����ӵķֱ�
const int H5SDK_MSG_TICK_DIRECTION = 6005 ; // ��ƫ��ȡ�ֱ�
const int H5SDK_MSG_CANDLE_BY_RANGE_MAINTAIN = 6006 ; // ����ʹ��_����k��
const int H5SDK_MSG_DAY5_TREND = 6007 ; // 5�շ�ʱ
const int H5SDK_MSG_TICK_SNAPSHOT = 6008 ; // snapshot tick��
const int H5SDK_MSG_HISTICK_SNAPSHOT_DATETIME = 6009 ; // ��ʱ��ȡ��ʷ���շֱ�
const int H5SDK_MSG_TICK_SNAPSHOT_DIRECTION = 6010 ; // ��ƫ��ȡ�ֱʿ���
const int H5SDK_MSG_HISTICK_SNAPSHOT_TRADE = 6011 ; // ��������ȡ��ʷ���շֱ�
const int H5SDK_MSG_OCALLTICK_TRADEDAY = 6012 ; // ���Ͼ��۵ķֱ�
const int H5SDK_MSG_SETTLE_CANDLE_BY_RANGE = 6013 ; // ������ʱ�䷶Χȡ����K��
const int H5SDK_MSG_SETTLE_CANDLE_BY_OFFSET = 6014 ; // ��ƫ��ȡ����K��
const int H5SDK_MSG_HISTICK_TRADE = 6015 ; // �����ڲ��ҵķֱ�
const int H5SDK_MSG_REALTIME_TREND = 6016 ; // ��ȡʵʱ��ƫ��ȡ��ʱ����
const int H5SDK_MAINTAIN_RETURN = 7001 ; // ���߷���
const int H5SDK_MSG_CANDLE_BY_RANGE_EXT = 7002 ; // ������ʱ�䷶ΧȡK��(��չ)
const int H5SDK_MSG_BLOCK_SORT = 8001 ; // ���ɷֹ�����
const int H5SDK_MSG_STOCK_BLOCKS = 8002 ; // ͨ���������������鼯
const int H5SDK_MSG_ORDER_FUNDFLOW_SNAPSHOT = 9001 ; // ���ʽ�������
const int H5SDK_MSG_SNAPSHOT_INDEX_CODESELECT = 9002 ; // ����ָ��ѡ�ɿ���
const int H5SDK_MSG_SNAPSHOT_SHAPE_CODESELECT = 9003 ; // ����K����̬ѡ�ɿ���
const int H5SDK_MSG_SNAPSHOT_INDEXRESONANCE_CODESELECT = 9004 ; // ����ָ�깲��ѡ�ɿ���
const int H5SDK_MSG_QUERY_MA_INFLEXION = 9005 ; // ��ѯ���߹յ�״̬���
const int H5SDK_MSG_MAX_WIN_RATE = 9006 ; // ��ѯʤ����߽��
const int H5SDK_MSG_MA_INFLEXION_TRADE_LIST = 9007 ; // ��ѯ���߹յ㽻��״̬��Ʊ����
const int H5SDK_MSG_BLOCK_ORDER_FUNDFLOW_RANK_SNAPSHOT = 9008 ; // ��ѯ������ʽ�������
const int H5SDK_MSG_TRANS_FUNDFLOW_SNAPSHOT = 9009 ; // ����ʽ�������
const int H5SDK_MSG_BLOCK_TRANS_FUNDFLOW_RANK_SNAPSHOT = 9010 ; // ��ѯ�������ʽ�������
const int H5SDK_MSG_ORDER_FUNDFLOW_RANK_BY_CLASSIFY_SNAPSHOT = 9011 ; // ������������ʽ�������(���ɡ�������)
const int H5SDK_MSG_TRANS_FUNDFLOW_RANK_BY_CLASSIFY_SNAPSHOT = 9012 ; // �������������ʽ�������(���ɡ�������)
const int H5SDK_MSG_QPLUS_MARKET_EXT_INFO = 9013 ; // ��ֵ�����г���չ��Ϣ
const int H5SDK_MSG_QPLUS_MARKET_EXT_TREND = 9014 ; // ��ֵ�����г���չ��ʱ����
const int H5SDK_MSG_MARKET_CHG_DIAGRAM = 9015 ; // �����г����ǵ����ֲ�ͼ
const int H5SDK_MSG_SNAPSHOT_RISE_FALL_COUNT = 9016 ; // ��ֵ�ǵ�ͣ�������ձ�
const int H5SDK_MSG_FUNDFLOW_MIN_ORDER = 10001 ; // ��ƫ��������ָ������ȡ��ʱ�������ʽ���
const int H5SDK_MSG_FUNDFLOW_MIN_TRANS = 10002 ; // ��ƫ��������ָ������ȡ��ʱ��������ʽ���
const int H5SDK_MSG_FUNDFLOW_MIN_DDE = 10003 ; // ��ƫ��������ָ������ȡ��ʱ����DDE�ʽ���
const int H5SDK_MSG_FUNDFLOW_DAY_ORDER = 10004 ; // �������ڷ�Χȡ�������ʽ���
const int H5SDK_MSG_FUNDFLOW_DAY_TRANS = 10005 ; // �������ڷ�Χȡ��������ʽ���
const int H5SDK_MSG_FUNDFLOW_DAY_DDE = 10006 ; // �������ڷ�Χȡ����DDE�ʽ���
const int H5SDK_MSG_INDEX_HIS_BACKTEST = 10007 ; // ȡ����ָ����ʷ�ز���
const int H5SDK_MSG_INDEXRESONANCE_HIS_BACKTEST = 10008 ; // ȡ����ָ�깲����ʷ�ز���
const int H5SDK_MSG_KLINESHAPE_HIS_CODESELECT = 10009 ; // ��ѯ������ʷK����̬ѡ�ɽ��
const int H5SDK_MSG_FUNDFLOW_DAY_ORDER_BY_OFFSET = 10010 ; // ����ƫ��ȡ�������ʽ���
const int H5SDK_MSG_FUNDFLOW_DAY_TRANS_BY_OFFSET = 10011 ; // ����ƫ��ȡ��������ʽ���
const int H5SDK_MSG_FUNDFLOW_DAY_DDE_BY_OFFSET = 10012 ; // ����ƫ��ȡ����DDE�ʽ���
const int H5SDK_MSG_INDEX_BUY_SELL_POINT_LIST = 10013 ; // ����ָ�����ڷ�Χ�����������б�
const int H5SDK_MSG_FUNDFLOW_DAY5_MIN_ORDER = 10014 ; // 5�շ�ʱ�������ʽ���
const int H5SDK_MSG_FUNDFLOW_DAY5_MIN_TRANS = 10015 ; // 5�շ�ʱ��������ʽ���
const int H5SDK_MSG_FUNDFLOW_MIN_ORDER_EXT = 10016 ; // ��ƫ��������ָ������ȡ��ʱ�������ʽ���
const int H5SDK_MSG_FUNDFLOW_MIN_TRANS_EXT = 10017 ; // ��ƫ��������ָ������ȡ��ʱ��������ʽ���
const int H5SDK_REQ_SUBCRIBE_LIST = 11001 ; // �������б�
const int H5SDK_MSG_CHECK_SESSION = 11002 ; // ���zookeepersession
const int H5SDK_MSG_DEL_SESSION = 11003 ; // ֪ͨzookeepersessionɾ��
const int H5SDK_REQ_BACK_SERVER_INFO = 11004 ; // �����������Ϣ
const int H5SDK_MSG_SUPPORT_SIGNAL_LIST = 12001 ; // ������֧�ֵ��춯�ź��б�
const int H5SDK_MSG_SUBSCRIBE_SIGNAL_BY_CODE = 12002 ; // �����붩���춯����ź�
const int H5SDK_MSG_SUBSCRIBE_SIGNAL_BY_MARKET = 12003 ; // ���г������춯����ź�
const int H5SDK_MSG_SUBSCRIBE_SIGNAL_BY_BLOCK = 12004 ; // ����鶩���춯����ź�
const int H5SDK_MSG_QUERY_SIGNAL_BY_TIME = 12005 ; // ��ʱ���ѯ�춯�ź�
const int H5SDK_MSG_QUERY_SIGNAL_BY_OFFSET = 12006 ; // ��ƫ�Ʋ�ѯ�춯�ź�
const int H5SDK_MSG_SIGNAL_RESULT_FORMAT_MAPPING = 12007 ; // ��ȡ�źŽ����Ϣ��ʽ���ձ�
const int H5SDK_MSG_MONITORING_SUBSCRIBE = 12008 ; // �������ܶ��̶���
const int H5SDK_MSG_MONITORING_UNSUBSCRIBE = 12009 ; // �������ܶ����˶�
const int H5SDK_MSG_MONITORING_PUSH = 12010 ; // ���ܶ�������
const int H5SDK_MSG_HQ_ANALYSIS_UPDOWN_DAYS_STATISTIC = 13001 ; // �����ǵ�ͣ��������ͳ��
const int H5SDK_MSG_HQ_ANALYSIS_UPDOWN_REASON = 13002 ; // ���������ѯ�ǵ�ͣԭ��
const int H5SDK_MSG_HQ_ANALYSIS_YESTERDAY_STATISTIC = 13003 ; // ������ͣ���շ���
const int H5SDK_MSG_HQ_ANALYSIS_STOCK_HIS_STATISTIC = 13004 ; // ������ʷ��ͣͳ�Ʒ���
const int H5SDK_MSG_HQ_HOT_STATISTIC = 13005 ; // �����ȶ�ͳ��
const int H5SDK_MSG_FILE_INDEX_BY_RANGE = 14001 ; // ���ղ�ѯ�����ļ�������Ϣ
const int H5SDK_MSG_LOCAL_CANDLE_COUNT_BY_RANGE = 14002 ; // ���ջ�ȡ���ػ���K�߸���
const int H5SDK_MSG_LOCAL_CANDLE_BY_RANGE = 14003 ; // ���ղ�ѯ���ػ�����ʷk��
const int H5SDK_MSG_DOWNLOAD_CANDLE_BY_RANGE = 14004 ; // ����K��
const int H5SDK_MSG_REQ_CANDLE_BY_RANGE = 14005 ; // ����K��
const int H5SDK_MSG_DEL_LOCAL_CANDLE_BY_RANGE = 14006 ; // ������ɾ�����ػ�������
const int H5SDK_MSG_GET_LOCAL_CANDLE_INFO = 14007 ; // ��ȡ���ػ���������Ϣ
const int H5SDK_MSG_GET_CANDLE_INFO = 14008 ; // ��ȡ������Ϣ
const int H5SDK_MSG_CLICK_PRICE = 20001 ; // �������ʵʱ����һ��
const int H5SDK_MSG_CLICK_PRICE_TEN = 20002 ; // �������ʵʱ����ʮ��
const int H5SDK_MSG_CLICK_PRICE_TEN_BROKER_QUEUE = 20003 ; // �������ʵʱ����ʮ���;��ö���
const int H5SDK_MSG_PUSH_HK_CLICK = 20004 ; // �۹ɵ�����ۿͻ���Ϣ(����)
const int H5SDK_MSG_HK_CLICK = 20005 ; // �۹ɵ�����ۿͻ���Ϣ����


/*****************ϵͳ����*******************/

/// �������ͣ�uint32(ö��); ������ҵ��prod_code,�����Һ��ʵ�ģ��
const int H5PROTO_TAG_BUSINESS_ID = 1 ;
    const uint32 BIZ_H5PROTO = 3 ; // H5�������Э��

/// �������ͣ�uint32(ö��); ��������������
const int H5PROTO_TAG_PACKET_TYPE = 3 ;
    const uint32 REQUEST = 0 ; // ����
    const uint32 ANSWER = 1 ; // Ӧ��
    const uint32 PUSH = 4 ; // ���Ʊ���

/// �������ͣ�uint32; ���������ܺ�
const int H5PROTO_TAG_FUNCTION_ID = 5 ;

/// �������ͣ�rawdata; �������ͻ���KEY
const int H5PROTO_TAG_USER_KEY = 7 ;

/// �������ͣ�rawdata; �������Ự��
const int H5PROTO_TAG_SESSION_ID = 8 ;

/// �������ͣ�uint32; �����������
const int H5PROTO_TAG_ERROR_NO = 19 ;

/// �������ͣ�bytevector; ������������Ϣ
const int H5PROTO_TAG_ERROR_INFO = 20 ;

/// �������ͣ�array; ������ȱʡ���ͣ�uint32; �����������ߵı�ʶ��Ϣ,��ʾ��Ϣ���ĸ����������ĸ�ͨ�����ĸ����ӻ��,һ��ͨ���������ڽ��յ���Ϣ��,����IDX_CONNECTID��IDX_CHANNEL_INDEX��������Ա��
const int H5PROTO_TAG_SEND_INFO_ARRAY = 100 ;

/// �������ͣ�array; ������ȱʡ���ͣ�uint32; ����������ʱ�䣬�����첽����ʱ��
const int H5PROTO_TAG_TIME_STAMP_ARRAY = 52 ;

/// �������ͣ�uint32; �������������
const int H5PROTO_TAG_BATCH_NO = 21 ;

/// �������ͣ�uint32; ������ͬ�����ñ��
const int H5PROTO_TAG_SYNC_NO = 22 ;

/// �������ͣ�rawdata; ��������ˮ��Ϣ
const int H5PROTO_TAG_SERIAL_INFO = 23 ;


/*****************��Ϣ����*******************/

/// �������ͣ�string; �������û���
const int H5SDK_TAG_USER_NAME = 20001 ;

/// �������ͣ�string; ����������
const int H5SDK_TAG_PASSWORD = 20002 ;

/// �������ͣ�string; ��������̬����
const int H5SDK_TAG_DYNMIC_PASSWORD = 20003 ;

/// �������ͣ�bytevector; ������ԭʼ����
const int H5SDK_TAG_ORGINAL_DATA = 96 ;

/// �������ͣ�uint32; �������������
const int H5SDK_TAG_HEARTBEAT_INTERVAL = 108 ;

/// �������ͣ�uint32; ������SDK�汾����1.3.2.1����103002001��
const int H5SDK_TAG_SDK_VERSION = 20005 ;

/// �������ͣ�bytevector; ����������ϵͳ�汾
const int H5SDK_TAG_OS_VERSION = 20006 ;

/// �������ͣ�bytevector; ����������������
const int H5SDK_TAG_SERVER_NAME = 20007 ;

/// �������ͣ�uint64; ������������ʱ�䡣Unixʱ���
const int H5SDK_TAG_SERVER_TIME = 20008 ;

/// �������ͣ�uint32; ��������ǰ����
const int H5SDK_TAG_CURR_ONLINE_COUNT = 20009 ;

/// �������ͣ�uint32; �������������
const int H5SDK_TAG_MAX_ONLINE_COUNT = 20010 ;

/// �������ͣ�uint32(ö��); �������ļ�����
const int H5SDK_TAG_HQ_FILE_TYPE = 20011 ;
    const uint32 H5SDK_ENUM_FT_COMMON_FILE = 0 ; // ��ͨ�ļ�����Ҫʹ���ļ��������·����Ϣ���з���
    const uint32 H5SDK_ENUM_FT_FINDATA_FILE = 1 ; // ���������ļ�
    const uint32 H5SDK_ENUM_FT_EXRIGHT_FILE = 2 ; // ��Ȩ�����ļ�
    const uint32 H5SDK_ENUM_FT_INFO_CONFIG_FILE = 3 ; // ��Ѷ�����ļ�
    const uint32 H5SDK_ENUM_FT_WELCOME_FILE = 4 ; // ��ӭ�ļ�
    const uint32 H5SDK_ENUM_FT_DYNAMIC_NEWS_FILE = 5 ; // ��������Ϣ�ļ�
    const uint32 H5SDK_ENUM_FT_SYS_BLOCK_FILE = 6 ; // ϵͳ����ļ�
    const uint32 H5SDK_ENUM_FT_USR_BLOCK_FILE = 7 ; // �Զ������ļ�
    const uint32 H5SDK_ENUM_FT_BLOCK_CODE_FILE = 8 ; // �����֯��ϵ�ļ�
    const uint32 H5SDK_ENUM_FT_MARKET_MONITOR_CONFIG_FILE = 9 ; // ���߾��������ļ�
    const uint32 H5SDK_ENUM_FT_CALL_AUCTION_TIME_FILE = 10 ; // ���Ͼ���ʱ�������ļ�

/// �������ͣ�bytevector; �������ļ�����
const int H5SDK_TAG_HQ_FILE_NAME = 16001 ;

/// �������ͣ�uint64; �������ļ�ƫ��
const int H5SDK_TAG_FILE_OFFSET = 20012 ;

/// �������ͣ�uint32; �������ļ�����
const int H5SDK_TAG_FILE_LENGTH = 20013 ;

/// �������ͣ�uint32; �������ɽ�ʱ��
const int H5SDK_TAG_BUSINESS_TIME = 20014 ;

/// �������ͣ�uint32; ����������CRC
const int H5SDK_TAG_CRC = 20015 ;

/// �������ͣ�uint32; �����������
const int H5SDK_TAG_ERROR_NO = 20016 ;

/// �������ͣ�bytevector; ���������������ַ���
const int H5SDK_TAG_ERROR_INFO = 20017 ;

/// �������ͣ�bytevector; ����������������
const int H5SDK_TAG_FINANCE_MIC = 20018 ;

/// �������ͣ�bytevector; ����������������
const int H5SDK_TAG_FINANCE_NAME = 20019 ;

/// �������ͣ�uint32; �������г�����
const int H5SDK_TAG_MARKET_DATE = 230 ;

/// �������ͣ�uint32; ��������������
const int H5SDK_TAG_INIT_DATE = 75 ;

/// �������ͣ�int32; ������ʱ��
const int H5SDK_TAG_TIMEZONE = 20020 ;

/// �������ͣ�uint8; ����������ʱ��־
const int H5SDK_TAG_DST_FLAG = 20021 ;

/// �������ͣ�sequence; �����������ظ���
const int H5SDK_TAG_TYPE_GRP = 20022 ;

/// �������ͣ�sequence; ���������������ظ���
const int H5SDK_TAG_SORT_TYPE_GRP = 20071 ;

/// �������ͣ�bytevector; ���������ʹ���
const int H5SDK_TAG_HQ_TYPE_CODE = 167 ;

/// �������ͣ�bytevector; ��������������
const int H5SDK_TAG_HQ_TYPE_NAME = 20023 ;

/// �������ͣ�uint32; �������۸�Ŵ���
const int H5SDK_TAG_PRICE_SCALE = 20024 ;

/// �������ͣ�sequence; ����������ʱ���
const int H5SDK_TAG_TRADE_SECTION_GRP = 20025 ;

/// �������ͣ�uint32; ����������ʱ��
const int H5SDK_TAG_OPEN_TIME = 20026 ;

/// �������ͣ�uint32; ����������ʱ��
const int H5SDK_TAG_CLOSE_TIME = 20027 ;

/// �������ͣ�int64; ���������ռ�
const int H5SDK_TAG_PRECLOSE_PX = 140 ;

/// �������ͣ�int64; ��������ͣ�۸�
const int H5SDK_TAG_UP_PRICE = 20028 ;

/// �������ͣ�int64; ��������ͣ�۸�
const int H5SDK_TAG_DOWN_PRICE = 20029 ;

/// �������ͣ�uint8(ö��); ����������ȼ�-��������Ч
const int H5SDK_TAG_HQ_LEVEL = 61 ;
    const uint8 H5SDK_ENUM_LEVEL_1 = 1 ; // ��������
    const uint8 H5SDK_ENUM_LEVEL_2 = 2 ; // 2������

/// �������ͣ�sequence; ��������Ʊ���ظ���
const int H5SDK_TAG_PROD_GRP = 20030 ;

/// �������ͣ�sequence; �����������Ʊ���ظ���
const int H5SDK_TAG_SORT_PROD_GRP = 20070 ;

/// �������ͣ�bytevector; ��������Ʊ����
const int H5SDK_TAG_PROD_CODE = 48 ;

/// �������ͣ�string; ��������ҵ����
const int H5SDK_TAG_INDUSTRY_CODE = 20031 ;

/// �������ͣ�string; ����������
const int H5SDK_TAG_MONEY_TYPE = 20032 ;

/// �������ͣ�uint32; ������ʱ���
const int H5SDK_TAG_DATA_TIMESTAMP = 10178 ;

/// �������ͣ�string; ������/*����״̬  START;   ///< �г�����(��ʼ��֮��,���Ͼ���ǰ)
   //  PRETR;   ///< ��ǰ
   //  OCALL;   ///< ��ʼ���Ͼ���
   //  TRADE;   ///< ����(�������)
   //  HALT;    ///< ��ͣ����
   //  SUSP;    ///< ͣ��
   //  BREAK;   ///< ����
   //  POSTR;   ///< �̺�
   //  ENDTR;   ///< ���׽���
   //  STOPT;   ///< ����ͣ�̣�ͣ��n��,n>=1 
   //  DELISTED;///< ���� */
const int H5SDK_TAG_TRADE_STATUS = 10135 ;

/// �������ͣ�int64; ���������̼�
const int H5SDK_TAG_OPEN_PX = 10018 ;

/// �������ͣ�int64; ���������¼�
const int H5SDK_TAG_LAST_PX = 31 ;

/// �������ͣ�int64; ��������߼�
const int H5SDK_TAG_HIGH_PX = 332 ;

/// �������ͣ�int64; ��������ͼ�
const int H5SDK_TAG_LOW_PX = 333 ;

/// �������ͣ�int64; ���������̼�
const int H5SDK_TAG_CLOSE_PX = 10204 ;

/// �������ͣ�int64; ������ƽ����
const int H5SDK_TAG_AVG_PX = 49 ;

/// �������ͣ�int64; ��������Ȩƽ����
const int H5SDK_TAG_WAVG_PX = 50 ;

/// �������ͣ�uint32; �������ɽ�����
const int H5SDK_TAG_BUSINESS_COUNT = 8503 ;

/// �������ͣ�uint64; �������ɽ���
const int H5SDK_TAG_BUSINESS_AMOUNT = 387 ;

/// �������ͣ�uint64; �������ɽ���
const int H5SDK_TAG_BUSINESS_BALANCE = 8504 ;

/// �������ͣ�uint64; ����������
const int H5SDK_TAG_CURRENT_AMOUNT = 30 ;

/// �������ͣ�uint64; ���������̳ɽ���
const int H5SDK_TAG_BUSINESS_AMOUNT_IN = 20033 ;

/// �������ͣ�uint64; ���������̳ɽ���
const int H5SDK_TAG_BUSINESS_AMOUNT_OUT = 20034 ;

/// �������ͣ�uint64; ��������ί����
const int H5SDK_TAG_TOTAL_BUY_AMOUNT = 10043 ;

/// �������ͣ�uint64; ��������ί����
const int H5SDK_TAG_TOTAL_SELL_AMOUNT = 10044 ;

/// �������ͣ�int64; ��������Ȩƽ��ί���
const int H5SDK_TAG_WAVG_BID_PX = 10039 ;

/// �������ͣ�int64; ��������Ȩƽ��ί����
const int H5SDK_TAG_WAVG_OFFER_PX = 10040 ;

/// �������ͣ�sequence; ������ί��λ
const int H5SDK_TAG_BID_GRP = 10068 ;

/// �������ͣ�sequence; ������ί����λ
const int H5SDK_TAG_OFFER_GRP = 10069 ;

/// �������ͣ�uint32; �������۸�
const int H5SDK_TAG_HQ_PRICE = 44 ;

/// �������ͣ�uint64; ������ί����
const int H5SDK_TAG_TOTAL_ENTRUST_AMOUNT = 39 ;

/// �������ͣ�sequence; ������ί�е��ظ���
const int H5SDK_TAG_ENTRUST_GRP = 73 ;

/// �������ͣ�int64; ������ί�м۸�
const int H5SDK_TAG_ENTRUST_PX = 20067 ;

/// �������ͣ�uint32; ������ί�е���
const int H5SDK_TAG_ENTRUST_AMOUNT = 38 ;

/// �������ͣ�int64; ������52����ͼ�
const int H5SDK_TAG_WEEK52_LOW_PX = 20035 ;

/// �������ͣ�int64; ������52����߼�
const int H5SDK_TAG_WEEK52_HIGH_PX = 20036 ;

/// �������ͣ�int64; �������۸��ǵ�
const int H5SDK_TAG_PX_CHANGE = 20037 ;

/// �������ͣ�int32; �������ǵ���
const int H5SDK_TAG_PX_CHANGE_RATE = 20038 ;

/// �������ͣ�int64; ��������ǰ/�̺�۸�
const int H5SDK_TAG_POPC_PX = 20039 ;

/// �������ͣ�uint64; ��������ǰ�׶εĳɽ���
const int H5SDK_TAG_SESSION_VOLUMUE = 20040 ;

/// �������ͣ�uint32; ����������: YYYYMMDD��0����ʾ��ǰ����
const int H5SDK_TAG_DATE = 20041 ;

/// �������ͣ�int32; ����������ƫ������
const int H5SDK_TAG_DATE_OFFSET = 20042 ;

/// �������ͣ�sequence; ��������ʱ�����ظ���
const int H5SDK_TAG_TREND_GRP = 20043 ;

/// �������ͣ�uint32(ö��); ������K������
const int H5SDK_TAG_CANDLE_PEROID = 20044 ;
    const uint32 H5SDK_ENUM_PERIOD_NONE = 0 ; // ������
    const uint32 H5SDK_ENUM_PEROID_1MIN = 1 ; // һ����
    const uint32 H5SDK_ENUM_PEROID_5MIN = 2 ; // 5����
    const uint32 H5SDK_ENUM_PEROID_15MIN = 3 ; // 15����
    const uint32 H5SDK_ENUM_PEROID_30MIN = 4 ; // 30����
    const uint32 H5SDK_ENUM_PEROID_60MIN = 5 ; // 60����
    const uint32 H5SDK_ENUM_PEROID_DAY = 6 ; // ����
    const uint32 H5SDK_ENUM_PEROID_WEEK = 7 ; // ����
    const uint32 H5SDK_ENUM_PEROID_MONTH = 8 ; // ����
    const uint32 H5SDK_ENUM_PEROID_YEAR = 9 ; // ����
    const uint32 H5SDK_ENUM_PEROID_10SEC = 10 ; // 10��
    const uint32 H5SDK_ENUM_PEROID_3MIN = 11 ; // 3����
    const uint32 H5SDK_ENUM_PEROID_10MIN = 12 ; // 10����
    const uint32 H5SDK_ENUM_PEROID_120MIN = 13 ; // 120����
    const uint32 H5SDK_ENUM_PEROID_240MIN = 14 ; // 240����
    const uint32 H5SDK_ENUM_PEROID_QUARTER = 15 ; // ����

/// �������ͣ�uint32(ö��); ����������K������
const int H5SDK_TAG_SETTLE_CANDLE_PEROID = 20045 ;
    const uint32 H5SDK_ENUM_PEROID_SETTLEMENT_DAY = 106 ; // �ս���

/// �������ͣ�uint8(ö��); ������K����������
const int H5SDK_TAG_DIRECTION = 20046 ;
    const uint8 H5SDK_ENUM_FORWARD = 1 ; // ��ǰ
    const uint8 H5SDK_ENUM_BACKWARD = 2 ; // ���

/// �������ͣ�uint32; ���������ݸ���
const int H5SDK_TAG_DATA_COUNT = 20047 ;

/// �������ͣ�uint32; ��������ʼ����,YYYYMMDD
const int H5SDK_TAG_START_DATE = 20048 ;

/// �������ͣ�uint32; ��������������,YYYYMMDD
const int H5SDK_TAG_END_DATE = 20049 ;

/// �������ͣ�sequence; ������K���ظ���
const int H5SDK_TAG_CANDLE_GRP = 20050 ;

/// �������ͣ�bytevector; ����������TOKEN
const int H5SDK_TAG_HQ_TOKEN = 20051 ;

/// �������ͣ�sequence; �������������ظ���
const int H5SDK_TAG_FINANCE_GRP = 20052 ;

/// �������ͣ�bytevector; �������˳�ԭ��
const int H5SDK_TAG_QUIT_REASON = 20053 ;

/// �������ͣ�sequence; ��������
const int H5SDK_TAG_BATCH_GRP = 20055 ;

/// �������ͣ�rawdata; �������Ӱ�
const int H5SDK_TAG_SUB_PACKET = 20056 ;

/// �������ͣ�sequence; �������ֶμ��ظ���
const int H5SDK_TAG_FIELD_GRP = 20057 ;

/// �������ͣ�bytevector; �������ֶ�����
const int H5SDK_TAG_FIELD_NAME = 20058 ;

/// �������ͣ�bytevector; ������֤ȯ����
const int H5SDK_TAG_PROD_NAME = 55 ;

/// �������ͣ�uint32; ������ί�е���
const int H5SDK_TAG_ENTRUST_COUNT = 10067 ;

/// �������ͣ�uint32; ���������׷�����
const int H5SDK_TAG_TRADE_MINS = 20059 ;

/// �������ͣ�int32; ���������׽׶�
const int H5SDK_TAG_TRADE_SECTION = 20060 ;

/// �������ͣ�uint8(ö��); ������K��ģʽ
const int H5SDK_TAG_CANDLE_MODE = 20061 ;
    const uint8 H5SDK_ENUM_CANDLE_ORIGINAL = 0 ; // ԭʼK��
    const uint8 H5SDK_ENUM_CANDLE_FORWARD = 1 ; // ǰ��ȨK��
    const uint8 H5SDK_ENUM_CANDLE_BACKWARD = 2 ; // ��ȨK��
    const uint8 H5SDK_ENUM_CANDLE_FORWAEX = 3 ; // ǰ��Ȩ��������K��
    const uint8 H5SDK_ENUM_CANDLE_BACKWAEX = 4 ; // ��Ȩ��������K��

/// �������ͣ�uint32; ���������ֵ
const int H5SDK_TAG_MAX_VALUE = 20062 ;

/// �������ͣ�uint64; �������ܹɱ�
const int H5SDK_TAG_TOTAL_SHARES = 20063 ;

/// �������ͣ�int32; ��������ӯ��
const int H5SDK_TAG_PE_RATE = 20064 ;

/// �������ͣ�sequence; �������г��ظ���
const int H5SDK_FINANCE_MIC_GRP = 30065 ;

/// �������ͣ�uint32(ö��); ���������Ļ����˶�, ������˶�,����SubscriberKeyΪ��,��ʾ�����ӵ������Ѷ�����Ϣ��ȡ��
const int H5SDK_TAG_SUB_TYPE = 13 ;
    const uint32 HSUB_ENUM_SUB_OVER = 0 ; // ���Ƕ���(��ǰ�ͻ��˵Ķ���ģʽ)
    const uint32 HSUB_ENUM_SUB = 1 ; // ׷�Ӷ���
    const uint32 HSUB_ENUM_UNSUB = 2 ; // �˶�

/// �������ͣ�uint32; ��������ʼλ��
const int H5SDK_TAG_START_POS = 50002 ;

/// �������ͣ�bytevector; �������ֶ�����
const int H5SDK_TAG_SORT_FIELD_NAME = 20066 ;

/// �������ͣ�int32; ����������
const int H5SDK_TAG_VOL_RATIO = 34 ;

/// �������ͣ�int64; ������������
const int H5SDK_TAG_DAY5_VOL = 35 ;

/// �������ͣ�int32; ���������
const int H5SDK_TAG_AMPLITUDE = 46 ;

/// �������ͣ�int64; �������ֲ���
const int H5SDK_TAG_AMOUNT = 95 ;

/// �������ͣ�int32; ������������
const int H5SDK_TAG_TURNOVER_RATIO = 97 ;

/// �������ͣ�int32; ������ί��
const int H5SDK_TAG_ENTRUST_RATE = 99 ;

/// �������ͣ�int64; ������ί��
const int H5SDK_TAG_ENTRUST_DIFF = 101 ;

/// �������ͣ�int8(ö��); ����������ʽ
const int H5SDK_TAG_SORT_TYPE = 102 ;
    const int8 HSUB_ENUM_SORT_ASC = 0 ; // ����
    const int8 HSUB_ENUM_SORT_DESC = 1 ; // ����

/// �������ͣ�bytevector; ������MIC_ABBR
const int H5SDK_TAG_MIC_ABBR = 103 ;

/// �������ͣ�uint32; ��������ʼ������
const int H5SDK_TAG_START_MIN = 104 ;

/// �������ͣ�uint32; ���������ܷ�����
const int H5SDK_TAG_END_MIN = 105 ;

/// �������ͣ�sequence; �������ֱ������ظ���
const int H5SDK_TAG_TICK_GRP = 106 ;

/// �������ͣ�uint32; �������ֱ����
const int H5SDK_TAG_BUSINESS_NO = 107 ;

/// �������ͣ�int32; �������ɽ�����
const int H5SDK_TAG_BUSINESS_DIRECTION = 109 ;

/// �������ͣ�int32; ������ÿ�ֹ���
const int H5SDK_TAG_SHARES_PER_HAND = 72 ;

/// �������ͣ�int32; �������۸񾫶�
const int H5SDK_TAG_PX_PRECISION = 71 ;

/// �������ͣ�int64; ��������ͨ�ɱ�
const int H5SDK_TAG_CIRCULATION_AMOUNT = 110 ;

/// �������ͣ�int64; ��������ֵ
const int H5SDK_TAG_MARKET_VALUE = 91 ;

/// �������ͣ�int64; ��������ͨ��ֵ
const int H5SDK_TAG_CIRCULATION_VALUE = 111 ;

/// �������ͣ�int32; ������ÿ�ɹ�����
const int HSSDK_TAG_EPS = 112 ;

/// �������ͣ�int32; ������ÿ�ɾ��ʲ�
const int HSSDK_TAG_BPS = 94 ;

/// �������ͣ�int32; �������о���
const int HSSDK_TAG_DYN_PB_RATE = 45 ;

/// �������ͣ�int32; ���������񼾶�
const int HSSDK_TAG_FIN_QUARTER = 113 ;

/// �������ͣ�int32; �����������������
const int HSSDK_TAG_FIN_END_DATE = 114 ;

/// �������ͣ�int8; �����������Ƿ��ȡ��ȫ
const int HSSDK_TAG_ALL_DATA_FLAG = 115 ;

/// �������ͣ�int32; ���������Ǽ���
const int HSSDK_TAG_RISE_COUNT = 124 ;

/// �������ͣ�int32; �������µ�����
const int HSSDK_TAG_FALL_COUNT = 125 ;

/// �������ͣ�int32; ��������Ա����
const int HSSDK_TAG_MEMBER_COUNT = 126 ;

/// �������ͣ�sequence; ���������ǹ�
const int H5SDK_TAG_RISE_FIRST_GRP = 1009 ;

/// �������ͣ�sequence; �����������
const int H5SDK_TAG_FALL_FIRST_GRP = 1010 ;

/// �������ͣ�string; ������ʱ����
const int H5SDK_TAG_TIMEZONE_CODE = 128 ;

/// �������ͣ�uint32; ����������ʱ��
const int H5SDK_TAG_MIN_TIME = 10014 ;

/// �������ͣ�uint32; �����������ֶ�ID
const int H5SDK_TAG_SORT_FIELD_ID = 20068 ;

/// �������ͣ�uint32; �������ֶ�id
const int H5SDK_TAG_FIELD_ID = 20069 ;

/// �������ͣ�int64; ��������ֲ֣��ڻ�����Ȩ��
const int HSSDK_TAG_PREV_AMOUNT = 122 ;

/// �������ͣ�int64; �����������֣��ڻ�����Ȩ��
const int HSSDK_TAG_AMOUNT_DELTA = 123 ;

/// �������ͣ�int64; ������IOPV
const int HSSDK_TAG_IOPV = 29 ;

/// �������ͣ�int64; ��������ծ����ֵ
const int HSSDK_TAG_DEBT_FUND_VALUE = 90 ;

/// �������ͣ�int64; �����������
const int HSSDK_TAG_PREV_SETTLEMENT = 28 ;

/// �������ͣ�int64; ������������
const int HSSDK_TAG_SETTLEMENT = 27 ;

/// �������ͣ�uint16; ��������������
const int H5SDK_TAG_SUB_KIND = 676 ;

/// �������ͣ�int32; ����������ֵ
const int H5SDK_TAG_MAINTAIN_RETURN_VALUE = 767 ;

/// �������ͣ�bytevector; ������Ӧ������
const int H5SDK_TAG_APP_NAME = 20072 ;

/// �������ͣ�bytevector; �������ֻ���
const int H5SDK_TAG_PHONE_NUMBER = 20073 ;

/// �������ͣ�bytevector; ������MAC��ַ����Ϊ�û�ʶ���־
const int H5SDK_TAG_MAC_ADDRESS = 20074 ;

/// �������ͣ�int8; �������Ƿ����Ӱ��
const int H5SDK_TAG_BLOCK_CHILDREN_FLAG = 20075 ;

/// �������ͣ�int64; ������������
/*Special Maker�궨��
#define SM_DELIST_WARNING             0x01  ///< ���о�ʾ���
#define SM_RISK_WARNING               0x02  ///< ���վ�ʾ���
#define SM_CRD_BUY                    0x04  ///< ���ʱ��
#define SM_CRD_SELL                   0x08  ///< ��ȯ���
#define SM_SH2HK                      0x10  ///< ����ͨ���(�������)
#define SM_HK2SH                      0x20  ///< �۹�ͨ���(�������)
#define SM_SH2HK_ONLY_SELL            0x40  ///< ����ͨ���(ֻ����)
#define SM_HK2SH_ONLY_SELL            0x80  ///< �۹�ͨ���(ֻ����)
#define SM_H_TARGET                  0x100  ///< H�ɱ��
#define SM_B_TARGET                  0x200  ///< B�ɱ��
#define SM_A_TARGET                  0x400  ///< A�ɱ��
#define SM_HK_DW_C                   0x800  ///< �۹�-�Ϲ�
#define SM_HK_DW_P                  0x1000  ///< �۹�-�Ϲ�
#define SM_HK_CBBC_C                0x2000  ///< �۹�-ţ֤
#define SM_HK_CBBC_P                0x4000  ///< �۹�-��֤
#define SM_NEEQ_BASE                0x10000  ///< ������-������
#define SM_NEEQ_CREATE              0x20000  ///< ������-���²�
#define SM_HK_VCM_FLAG              0x40000  ///< �۹�-�侲�ڱ��
#define SM_HK_CAS_FLAG              0x80000  ///< �۹�-���̾��۱��
#define SM_HK2SZ                   0x100000  ///< �۹�ͨ���(�������)
#define SM_HK2SZ_ONLY_SELL         0x200000  ///< �۹�ͨ���(ֻ����)
#define SM_SZ2HK_FRACTIONAL_SELL   0x400000  ///< �۹�ͨ��ɣ����������
#define SM_SZ2HK_FRACTIONAL_ONLY_SELL  0x800000  ///< �۹�ͨ��ɣ�ֻ������
#define SM_SZ2HK                       0x1000000  ///< ���ͨ���(�������)
#define SM_SZ2HK_ONLY_SELL             0x2000000  ///<���ͨ���(ֻ����)
#define SM_UNISSUED_STATE             0x4000000  ///< δ����
#define SM_PURCHASE_STATE             0x8000000  ///< �����깺
#define SM_ISSUED_STATE             0x10000000  ///< �ѷ���-δ����
#define SM_INVESTOR_ALL        0x20000000   ///<��������Ͷ���ߡ��ϸ�Ͷ�������ڵ�����Ͷ���߶������Ϲ��ͽ���
#define SM_QUALIFICATION_ONLY  0x40000000   ///<���ϸ�Ͷ���߿����Ϲ��ͽ���
#define SM_ORGANIZATION_QUALIFICATION_ONLY  0x80000000   ///<���ϸ�Ͷ�����еĻ���Ͷ���߿����Ϲ��ͽ���
#define SM_MAIN_CONTRACT_STATE  0x100000000       ///<�ڻ�������Լ���
#define SM_NIGHT_CONTRACT_STATE  0x200000000    ///<�ڻ�ҹ�̺�Լ���
#define SM_FATHER_BLOCK_STATE  0x400000000      ///<����г��������
#define SM_UP_LIMIT_STATE  0x800000000          ///<������ͣ���
#define SM_DOWN_LIMIT_STATE  0x1000000000       ///<������ͣ���
#define SM_TOUCH_UP_LIMIT_STATE  0x2000000000   ///<������ͣ���
#define SM_TOUCH_DOWN_LIMIT_STATE  0x4000000000 ///<�����ͣ���
*/
const int H5SDK_TAG_SPECIAL_MARKER = 20100 ;

/// �������ͣ�bytevector; ���������֤ȯ
const int H5SDK_TAG_UNDERLYING = 20101 ;

/// �������ͣ�uint32; ��������Ȩ����
const int H5SDK_TAG_EXERCISE_DATE = 20102 ;

/// �������ͣ�int64; ��������Ȩ�۸�
const int H5SDK_TAG_EXERCISE_PRICE = 20103 ;

/// �������ͣ�uint32; ��������Լ����
const int H5SDK_TAG_CONTRACT_UNIT = 20104 ;

/// �������ͣ�bytevector; ��������Լ����
const int H5SDK_TAG_CONTRACT_CODE = 20105 ;

/// �������ͣ�bytevector; ��������Ȩ��ʽ����Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A��
const int H5SDK_TAG_EXERCISE_TYPE = 20106 ;

/// �������ͣ�bytevector; �������Ϲ��Ϲ����Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P��
const int H5SDK_TAG_CALL_PUT = 20107 ;

/// �������ͣ�uint32; �������׸�������
const int H5SDK_TAG_START_TRADE_DATE = 20108 ;

/// �������ͣ�uint32; �������������
const int H5SDK_TAG_END_TRADE_DATE = 20109 ;

/// �������ͣ�uint32; ��������������
const int H5SDK_TAG_EXPIRE_DATE = 20110 ;

/// �������ͣ�uint32; ��������Ȩ��Լ״̬��Ϣ
const int H5SDK_TAG_SECURITY_STATUS_FLAG = 20111 ;

/// �������ͣ�int32; ��������С���۵�λ
const int H5SDK_TAG_TICK_SIZE = 20112 ;

/// �������ͣ�bytevector; ��������Ʒʵʩ��־�����ֶ�Ϊ4λ�ַ���������ÿλ��ʾ�ض��ĺ��壬�޶�������ո�
//��1λ����S����ʾ����������ǰ��ʱ�Σ���C����ʾ���Ͼ���ʱ�Σ���T����ʾ//��������ʱ�Σ���B����ʾ����ʱ�Σ���E����ʾ����ʱ�Σ���V����ʾ�������жϣ���P����ʾ��ʱͣ�ơ���U����ʾ���̼��Ͼ��ۡ�
//��2λ����0����ʾδ����ͣ�ƣ���1����ʾ����ͣ�ơ���Ԥ��������ո�
//��3λ����0����ʾ�����ƿ��֣���1����ʾ���Ʊ��ҿ��֣���2����ʾ�������֣���3����ʾ�����������֡����ҿ��֣���4����ʾ�������뿪�֣���5����ʾ�������뿪�֡����ҿ��֣���6����ʾ�������뿪�֡��������֣���7����ʾ�������뿪�֡��������֡����ҿ���

const int H5SDK_TAG_TRADING_PHASE_CODE = 20113 ;

/// �������ͣ�int32; ��������̬�ο���
const int H5SDK_TAG_AUCTION_PRICE = 20114 ;

/// �������ͣ�int64; ����������ƥ������
const int H5SDK_TAG_MATCHED_QTY = 20115 ;

/// �������ͣ�int32; ������������ǵ���
const int H5SDK_TAG_MIN5_CHGPCT = 47 ;

/// �������ͣ�int32; ���������з���������ԶԽ�����0��
const int H5SDK_TAG_OPEN_MIN = 74 ;

/// �������ͣ�int32; ���������з���������ԶԽ�����0��
const int H5SDK_TAG_CLOSE_MIN = 76 ;

/// �������ͣ�uint32(ö��); ��������������
const int H5SDK_TAG_UNDERLYING_TYPE = 20116 ;
    const uint32 H5SDK_ENUM_UNDERLYING_A = 0 ; // A��
    const uint32 H5SDK_ENUM_UNDERLYING_B = 1 ; // B��
    const uint32 H5SDK_ENUM_UNDERLYING_H = 2 ; // H��
    const uint32 H5SDK_ENUM_UNDERLYING_F = 3 ; // �ڻ�
    const uint32 H5SDK_ENUM_UNDERLYING_OPT = 4 ; // ��Ȩ
    const uint32 H5SDK_ENUM_UNDERLYING_DW_C = 5 ; // �۹�-�Ϲ�
    const uint32 H5SDK_ENUM_UNDERLYING_DW_P = 6 ; // �۹�-�Ϲ�
    const uint32 H5SDK_ENUM_UNDERLYING_CBBC_C = 7 ; // �۹�-ţ֤
    const uint32 H5SDK_ENUM_UNDERLYING_CBBC_P = 8 ; // �۹�-��֤

/// �������ͣ�sequence; ���������������ظ���
const int H5SDK_TAG_UNDERLYING_GRP = 20117 ;

/// �������ͣ�sequence; ��������Ȩ��Ϣ
const int H5SDK_TAG_EXER_GREP = 20118 ;

/// �������ͣ�int32; ������ÿ���͹�
const int H5SDK_TAG_ALLOTTED_PS = 51 ;

/// �������ͣ�int32; ������ÿ�������
const int H5SDK_TAG_RATIONED_PS = 52 ;

/// �������ͣ�int64; ��������ɼ�
const int H5SDK_TAG_RATIONED_PX = 53 ;

/// �������ͣ�int32; ������ÿ�ɷֺ�
const int H5SDK_TAG_BONUS_PS = 54 ;

/// �������ͣ�bytevector; ������ƴ�����
const int H5SDK_TAG_CHI_SPELLING = 20119 ;

/// �������ͣ�int32; ��������������
const int H5SDK_TAG_ISSUE_DATE = 20120 ;

/// �������ͣ�int64; ������IPO�۸�
const int H5SDK_TAG_IPO_PRICE = 20121 ;

/// �������ͣ�sequence; ������ƴ������ظ���
const int H5SDK_TAG_CHI_SPELLING_GRP = 20122 ;

/// �������ͣ�rawdata; �������û���Ϣ
const int H5SDK_TAG_USER_INFO = 20123 ;

/// �������ͣ�rawdata; ������Ӧ��ʶ���
const int H5SDK_TAG_APP_KEY = 20124 ;

/// �������ͣ�int64; ������gammaָ��
const int H5SDK_TAG_GAMMA_INDEX = 20130 ;

/// �������ͣ�int64; ������deltaָ��
const int H5SDK_TAG_DELTA_INDEX = 20131 ;

/// �������ͣ�int64; ��������ʵ�ܸ���
const int H5SDK_TAG_REAL_LEVERAGE = 20132 ;

/// �������ͣ�int64; ��������Ȩ����
const int H5SDK_TAG_OPTION_PRICE = 20133 ;

/// �������ͣ�sequence; ����������ظ���
const int H5SDK_TAG_TRANSCATION_GRP = 20134 ;

/// �������ͣ�int32; ������ί�����
const int H5SDK_TAG_TRANS_KIND = 20135 ;

/// �������ͣ�bytevector; ������Ȩ����Ϣ
const int H5SDK_TAG_AUTH_STRING = 1095 ;

/// �������ͣ�int32; �������г���Է�����
const int H5SDK_TAG_MARKET_MIN = 20136 ;

/// �������ͣ�sequence; ������F10�����ظ���
const int H5SDK_TAG_F10_INDEX_GRP = 20137 ;

/// �������ͣ�int8; ������//��Ϣ����
//Bit0-3��Ϣ����              0x00����������
//0x01�ƾ�����0x02 ������ʷ��Ѷ (��˾���¼�)
//0x03����ʵʱ��Ѷ
//0x04  F1����
//0x05-0x0����
//0x0f  ����

const int H5SDK_TAG_F10_GROUP = 20138 ;

/// �������ͣ�int8; �������г���Ӧbitλ
//0 �Ϻ�
//1 ����
//2 ��ҵ
//3 ���
//4 ̨��
//5 ����
//6 ����
//7 ����

const int H5SDK_TAG_F10_MARKET = 20139 ;

/// �������ͣ�int64; ������ί��һ��
const int H5SDK_TAG_BID_PRICE1 = 20140 ;

/// �������ͣ�int64; ������ί��һ��
const int H5SDK_TAG_OFFER_PRICE1 = 20141 ;

/// �������ͣ�int64; ������ί��һ��
const int H5SDK_TAG_BID_QTY1 = 20142 ;

/// �������ͣ�int64; ������ί��һ��
const int H5SDK_TAG_OFFER_QTY1 = 20143 ;

/// �������ͣ�bytevector; ���������⣬���64�ֽ�
const int H5SDK_TAG_F10_TILTLE = 20144 ;

/// �������ͣ�int64; ��������Ϣ��ţ�������ţ������������Ψһ������֤������(�׸��������)
const int H5SDK_TAG_F10_FILEPK = 20145 ;

/// �������ͣ�uint32; ������HHMMSS
const int H5SDK_TAG_TIME = 20146 ;

/// �������ͣ�sequence; ������F10�����ظ���
const int H5SDK_TAG_F10_FILEPK_GRP = 20147 ;

/// �������ͣ�sequence; ������F10���������ظ���
const int H5SDK_TAG_F10_TXT_GRP = 20148 ;

/// �������ͣ�uint32(ö��); ��������Ѷ��������
const int H5SDK_TAG_F10_TYPE = 20149 ;
    const uint32 H5SDK_ENUM_TYPE_F10 = 1 ; // F10����
    const uint32 H5SDK_ENUM_TYPE_RID = 2 ; // ��ʱ��Ѷ
    const uint32 H5SDK_ENUM_TYPE_HID = 3 ; // �۹ɷ�ʱ��Ѷ

/// �������ͣ�uint64; �������ɽ���(�Ŵ�1000��)
const int H5SDK_TAG_BUSINESS_BALANCE_SCALE = 20150 ;

/// �������ͣ�int32(ö��); ��������¼״̬
const int H5SDK_TAG_RECORD_STATUS = 20151 ;
    const int32 H5SDK_ENUM_RECORD_STATUS_INVALID = 0 ; // ��¼״̬��Ч
    const int32 H6SDK_ENUM_RECORD_STATUS_VALID = 1 ; // ��¼״̬��Ч

/// �������ͣ�uint32; ��������ת����������
const int H5SDK_TAG_NEEQ_MAKER_COUNT = 20152 ;

/// �������ͣ�int32; ��������λ���
const int H5SDK_TAG_SPREAD_LEVEL = 20153 ;

/// �������ͣ�bytevector; ��������Ʊ��λ����
const int H5SDK_TAG_FINANCE_UNITNAME = 20154 ;

/// �������ͣ�uint32; ����������ģʽ��0λ�����ض��ڻ���Լ��1Ϊ������������
const int H5SDK_CODE_PROPERTY_MODEL = 20155 ;

/// �������ͣ�bytevector; ��������������
const int H5SDK_TAG_RELATIVECODE = 20156 ;

/// �������ͣ�bytevector; ��������Ʒ����
const int H5SDK_TAG_SYMBOL_DETAIL = 20177 ;

/// �������ͣ�uint32; ��������Ч��ʶ
const int H5SDK_TAG_ENABLE = 20159 ;

/// �������ͣ�uint32; �������Ƿ���Խ���
const int H5SDK_TAG_CAN_TRADE = 20160 ;

/// �������ͣ�uint32; ��������С�䶯��λ
const int H5SDK_TAG_MIN_MOVE = 20174 ;

/// �������ͣ�uint32; ������ÿ���������ֵ
const int H5SDK_TAG_BIG_POINT_VALUE = 20175 ;

/// �������ͣ�uint32; �����������̸���
const int H5SDK_TAG_BID_ASK_DEPTH = 20176 ;

/// �������ͣ�uint32; �����������м۽����������
const int H5SDK_TAG_MAX_MARKET_ORDER_VOLUME = 20161 ;

/// �������ͣ�uint32; �����������޼۽����������
const int H5SDK_TAG_LIMIT_MARKET_ORDER_VOLUME = 20162 ;

/// �������ͣ�uint32; ��������󵥱�����
const int H5SDK_TAG_MAX_LIMIT_SHARES = 20163 ;

/// �������ͣ�bytevector; ��������֤�����
const int H5SDK_TAG_MARGIN_RATE = 20164 ;

/// �������ͣ�uint32; ��������֤����ʵļ��㷽ʽ
const int H5SDK_TAG_MARGIN_MODEL = 20165 ;

/// �������ͣ�uint32; �������ڻ���������
const int H5SDK_TAG_CODE_TYPE = 20166 ;

/// �������ͣ�uint32; ��������Լ�������
const int H5SDK_TAG_CONTRACT_YEAR = 20167 ;

/// �������ͣ�uint32; ��������Լ�����·�
const int H5SDK_TAG_CONTRACT_MONTH = 20168 ;

/// �������ͣ�uint32; �������Ƿ�������
const int H5SDK_TAG_IS_SERIES = 20169 ;

/// �������ͣ�uint32; ��������Ȩ����
const int H5SDK_TAG_OP_TYPE = 20170 ;

/// �������ͣ�uint32; ��������Ȩ��Ȩ��ʽ
const int H5SDK_TAG_OP_STYLE = 20171 ;

/// �������ͣ�bytevector; ��������Լ���״���
const int H5SDK_TAG_BROKER_CODE = 20172 ;

/// �������ͣ�bytevector; �������۸񾫶ȵ�λ
const int H5SDK_TAG_PRICE_SCALE_UNIT = 20173 ;

/// �������ͣ�int64; ������ί����
const int H5SDK_TAG_TOTAL_OFFERQTY = 20179 ;

/// �������ͣ�int64; ������ί����
const int H5SDK_TAG_TOTAL_BIDQTY = 20180 ;

/// �������ͣ�int64; ������ί�����
const int H5SDK_TAG_TOTAL_OFFER_TURNOVER = 20181 ;

/// �������ͣ�int64; ������ί����
const int H5SDK_TAG_TOTAL_BID_TURNOVER = 20182 ;

/// �������ͣ�uint64; ��������ʼʱ��YYYYMMDDHHMMSS
const int H5SDK_TAG_START_DATE_TIME = 20286 ;

/// �������ͣ�uint64; ����������ʱ��YYYYMMDDHHMMSS
const int H5SDK_TAG_END_DATE_TIME = 20287 ;

/// �������ͣ�bytevector; ��������С�۸�䶯��λ����
const int H5SDK_TAG_MIN_MOVE_SCALE = 20288 ;

/// �������ͣ�int32(ö��); �������۹�״̬
const int H5SDK_TAG_HK_STATUS = 20289 ;
    const int32 H5SDK_ENUM_HK_NORMAL_STATUS = 0 ; // �۹���������״̬
    const int32 H5SDK_ENUM_HK_VCM_STATUS = 1 ; // �۹��е�״̬
    const int32 H5SDK_ENUM_HK_CAS_STATUS = 2 ; // �۹����о���״̬

/// �������ͣ�string; ������CASδ����������̵ķ���
//N = �����������
//B = ���̱����̶�
//S = ���̱����̶�
//�ո� = ������(δ�вο�ƽ��۸�)

const int H5SDK_TAG_ORD_IMB_DIRECTION = 20290 ;

/// �������ͣ�int64; �������ο��۸�
const int H5SDK_TAG_REFERENCE_PX = 20291 ;

/// �������ͣ�uint32; ��������ʼʱ��,HHMMSS
const int H5SDK_TAG_START_TIME = 20292 ;

/// �������ͣ�uint32; ����������ʱ��,HHMMSS
const int H5SDK_TAG_END_TIME = 20293 ;

/// �������ͣ�uint64; �������ۻ��ɽ����(1000��)
const int H5SDK_TAG_ACCUMULATE_TURNOVER = 20190 ;

/// �������ͣ�bytevector; ������ǰ��Ȩ��Ȩ����A
const int H5SDK_TAG_EXER_FORWARD_A = 20294 ;

/// �������ͣ�int64; ������ǰ��Ȩ��Ȩ����B
const int H5SDK_TAG_EXER_FORWARD_B = 20295 ;

/// �������ͣ�bytevector; ��������Ȩ��Ȩ����A
const int H5SDK_TAG_EXER_BACKWARD_A = 20296 ;

/// �������ͣ�int64; ��������Ȩ��Ȩ����B
const int H5SDK_TAG_EXER_BACKWARD_B = 20297 ;

/// �������ͣ�int64; �������ɽ�������
const int H5SDK_TAG_BUSINESS_AMOUNT_DIFF = 20298 ;

/// �������ͣ�int64; �������ɽ�������
const int H5SDK_TAG_BUSINESS_BALANCE_DIFF = 20299 ;

/// �������ͣ�int32; �������ɽ���������
const int H5SDK_TAG_BUSINESS_COUNT_DIFF = 20300 ;

/// �������ͣ�int64; �������ʽ���ddx(�Ŵ�1000��)
const int H5SDK_TAG_FUNDFLOW_DDX = 55000 ;

/// �������ͣ�int64; �������ʽ���ddy(�Ŵ�1000��)
const int H5SDK_TAG_FUNDFLOW_DDY = 55001 ;

/// �������ͣ�int64; �������ʽ���ddz(�Ŵ�1000��)
const int H5SDK_TAG_FUNDFLOW_DDZ = 55002 ;

/// �������ͣ�int32; ���������10����DDXƮ������
const int H5SDK_TAG_RISEDAYS_PAST10_DDX = 55003 ;

/// �������ͣ�int32; ������DDX����Ʈ������
const int H5SDK_TAG_RISEDAYS_CONTINUES = 55004 ;

/// �������ͣ�sequence; ��������չ�ʽ���ָ��
const int H5SDK_TAG_FUNDFLOW_INDEX_EXT_GRP = 55005 ;

/// �������ͣ�uint32(ö��); �������ʽ���ָ������:0 = 5��;1 = 10��
const int H5SDK_TAG_FUNDFLOW_INDEX_TYPE = 55006 ;
    const uint32 H5SDK_ENUM_FUNDFLOW_FIVE_TYPE = 0 ; // 5��
    const uint32 H5SDK_ENUM_FUNDFLOW_TEN_TYPE = 1 ; // 10��

/// �������ͣ�sequence; ���������������ͳ��
const int H5SDK_TAG_CLASSIFY_ORDER_BID_GRP = 55007 ;

/// �������ͣ�sequence; ����������������ͳ��
const int H5SDK_TAG_CLASSIFY_ORDER_OFFER_GRP = 55008 ;

/// �������ͣ�sequence; ����������������ͳ��
const int H5SDK_TAG_CLASSIFY_TRANS_BID_GRP = 55009 ;

/// �������ͣ�sequence; �����������������ͳ��
const int H5SDK_TAG_CLASSIFY_TRANS_OFFER_GRP = 55010 ;

/// �������ͣ�int8(ö��); ������ѡ������
const int H5SDK_TAG_SELECTCODE_TYPE = 55011 ;
    const int8 H5SDK_ENUM_SELECTCODE_INDEX_TYPE = 0 ; // ָ��ѡ��
    const int8 H5SDK_ENUM_SELECTCODE_INDEX_RESONNACE_TYPE = 1 ; // ָ�깲��ѡ��
    const int8 H5SDK_ENUM_SELECTCODE_SHAPE_TYPE = 2 ; // K����̬ѡ��

/// �������ͣ�int8(ö��); ������ѡ�ɲ������ͣ�Ĭ��Ϊ��0��
const int H5SDK_TAG_SELECTCODE_PARAM_TYPE = 55012 ;
    const int8 H5SDK_ENUM_SELECTCODE_PARAM_DEF = 0 ; // def��Ĭ��ָ��
    const int8 H5SDK_ENUM_SELECTCODE_PARAM_OPT = 1 ; // opt������ָ��

/// �������ͣ�int32; ������ָ�����ش�����
const int H5SDK_TAG_RETURN_CODE_COUNT = 55013 ;

/// �������ͣ�int32; ���������ֶ�ID���򷵻�
const int H5SDK_TAG_ORDER_BY_FIELD = 55014 ;

/// �������ͣ�sequence; ������ָ���б�
const int H5SDK_TAG_INDEX_LIST_GRP = 55015 ;

/// �������ͣ�int8(ö��); ������ָ�����ͣ�����Ļ�Ĭ��Ϊȫ��ָ�꣩
const int H5SDK_TAG_INDEX_TYPE = 55016 ;
    const int8 H5SDK_ENUM_INDEX_MACD_TYPE = 0 ; // MACDָ��
    const int8 H5SDK_ENUM_INDEX_KDJ_TYPE = 1 ; // KDJָ��
    const int8 H5SDK_ENUM_INDEX_RSI_TYPE = 2 ; // RSIָ��
    const int8 H5SDK_ENUM_INDEX_MA_TYPE = 3 ; // MAָ��
    const int8 H5SDK_ENUM_INDEX_BOLL_TYPE = 4 ; // BOLLָ��

/// �������ͣ�sequence; ������ѡ�ɽ����
const int H5SDK_TAG_SELECTCODE_RESULT_GRP = 55017 ;

/// �������ͣ�int32; �������ز��н��״���
const int H5SDK_TAG_TRADE_COUNT = 55018 ;

/// �������ͣ�int32; �������ز���ӯ������
const int H5SDK_TAG_WIN_COUNT = 55019 ;

/// �������ͣ�int32; �������ز���ӯ���ĸ��ʣ�����100��
const int H5SDK_TAG_WIN_RATE = 55020 ;

/// �������ͣ�int32; ���������������ʣ�����100000��
const int H5SDK_TAG_EXP_REVENUE = 55021 ;

/// �������ͣ�int32(ö��); ���������ײ�������
const int H5SDK_TAG_TRADE_OPERATOR = 55022 ;
    const int32 H5SDK_ENUM_BUY_OPERATOR = 0 ; // ����
    const int32 H5SDK_ENUM_SELL_OPERATOR = 1 ; // ����
    const int32 H5SDK_ENUM_CASH_OPERATOR = 2 ; // �ֱ�
    const int32 H5SDK_ENUM_STOCK_OPERATOR = 3 ; // �ֹ�
    const int32 H5SDK_ENUM_NOBS_OPERATOR = 4 ; // �������

/// �������ͣ�int32; ������ָ�깲�����
const int H5SDK_TAG_INDEXRESONANCE_SCORE = 55023 ;

/// �������ͣ�int32(ö��); �������ز����ޣ�Ĭ��Ϊ3��
const int H5SDK_TAG_BACKTEST_YEARS = 55024 ;
    const int32 H5SDK_ENUM_BACKTEST_SHORT_YEARS = 0 ; // 1��
    const int32 H5SDK_ENUM_BACKTEST_MID_YEARS = 1 ; // 3��
    const int32 H5SDK_ENUM_BACKTEST_LONG_YEARS = 2 ; // 7��

/// �������ͣ�int32; �������ز�����
const int H5SDK_TAG_BACKTEST_DATE = 55025 ;

/// �������ͣ�int32; �������ز�ʱ��
const int H5SDK_TAG_BACKTEST_TIME = 55026 ;

/// �������ͣ�int32; ��������������
const int H5SDK_TAG_TOTAL_REVENUE = 55027 ;

/// �������ͣ�int32; �������ز��껯����
const int H5SDK_TAG_YEARLY_REVENUE = 55028 ;

/// �������ͣ�int32; ��������׼������
const int H5SDK_TAG_BENCHMARK_REVENUE = 55029 ;

/// �������ͣ�int32; �������ز�����������
const int H5SDK_TAG_SORTINO = 55030 ;

/// �������ͣ�int32; �������ز���Ϣ����
const int H5SDK_TAG_INFO_RATIO = 55031 ;

/// �������ͣ�int32; �������ز��㷨������
const int H5SDK_TAG_ALGO_VOLATILITY = 55032 ;

/// �������ͣ�int32; �������ز��׼������
const int H5SDK_TAG_BENCHMARK_VOLATILITY = 55033 ;

/// �������ͣ�int32; �������ز⻻����
const int H5SDK_TAG_TURNOVER_RATE = 55034 ;

/// �������ͣ�int32; �������ز����س�
const int H5SDK_TAG_MAX_DRAWDOWN = 55035 ;

/// �������ͣ�sequence; ��������̬�б�
const int H5SDK_TAG_SHAPE_LIST = 55036 ;

/// �������ͣ�int8(ö��); ��������̬����
const int H5SDK_TAG_SHAPE_TYPE = 55037 ;
    const int8 H5SDK_ENUM_SHAPE_SJZX = 0 ; // ���֮��
    const int8 H5SDK_ENUM_SHAPE_SDX = 1 ; // �ϵ���
    const int8 H5SDK_ENUM_SHAPE_HHZX = 2 ; // �ƻ�֮��
    const int8 H5SDK_ENUM_SHAPE_MBX = 3 ; // Ĺ����
    const int8 H5SDK_ENUM_SHAPE_WYGD = 4 ; // ���ƸǶ�
    const int8 H5SDK_ENUM_SHAPE_TMXT = 5 ; // ��û��̬
    const int8 H5SDK_ENUM_SHAPE_SZWY = 6 ; // ��ֻ��ѻ
    const int8 H5SDK_ENUM_SHAPE_CTX = 7 ; // ��ͷ��
    const int8 H5SDK_ENUM_SHAPE_ZCZX = 8 ; // �糿֮��
    const int8 H5SDK_ENUM_SHAPE_SGCX = 9 ; // ������
    const int8 H5SDK_ENUM_SHAPE_CTXT = 10 ; // ��͸��̬
    const int8 H5SDK_ENUM_SHAPE_HSB = 11 ; // ������

/// �������ͣ�int32; ������5��ӯ������
const int H5SDK_TAG_5DAY_WIN_COUNT = 55038 ;

/// �������ͣ�int32; ������10�����������ʣ�����100000��
const int H5SDK_TAG_5DAY_EXP_REVENUE = 55039 ;

/// �������ͣ�int32; ������10��ӯ������
const int H5SDK_TAG_10DAY_WIN_COUNT = 55040 ;

/// �������ͣ�int32; ������10�����������ʣ�����100000��
const int H5SDK_TAG_10DAY_EXP_REVENUE = 55041 ;

/// �������ͣ�sequence; �����������б�
const int H5SDK_TAG_DATE_GRP = 55042 ;

/// �������ͣ�sequence; ���������߹յ㼯
const int H5SDK_MSG_MA_INFLEXTION_GRP = 55043 ;

/// �������ͣ�int32; ������ѡ��ʱ��
const int H5SDK_TAG_SELECTCODE_TIME = 55044 ;

/// �������ͣ�bytevector; ������ָ�����
const int H5SDK_TAG_INDEX_VALUE = 55045 ;

/// �������ͣ�sequence; ������ÿ�������ʼ���ֻ��ָ�깲���У�
const int H5SDK_MSG_DAY_REVENUE_GRP = 55046 ;

/// �������ͣ�int64; ������ÿ��ӯ��
const int H5SDK_TAG_DAY_PROFIT_LOSS = 55047 ;

/// �������ͣ�sequence; ������ѡ�ɲ����б�
const int H5SDK_TAG_SELECTCODE_PARAM_TYPE_GRP = 55048 ;

/// �������ͣ�sequence; ������ѡ�������б�
const int H5SDK_TAG_SELECTCODE_TYPE_GRP = 55049 ;

/// �������ͣ�sequence; ���������������
const int H5SDK_TAG_BS_GRP = 55050 ;

/// �������ͣ�int8(ö��); ��������ȡ�������� 0:5�� 1:10�� Ĭ��Ϊ5��
const int H5SDK_TAG_SHAPE_REVENUE_TYPE = 55051 ;
    const int8 H5SDK_ENUM_SHAPE_FIVE_DAY_REVENUE = 0 ; // ��ȡ5��������
    const int8 H5SDK_ENUM_SHAPE_TEN_DAY_REVENUE = 1 ; // ��ȡ10��������

/// �������ͣ�bytevector; ��������̬����
const int H5SDK_TAG_SHAPE_NAME = 55052 ;

/// �������ͣ�int32; ��������������
const int H5SDK_TAG_CONTINUOUS_DAY = 55053 ;

/// �������ͣ�sequence; ���������ײ�������
const int H5SDK_TAG_TRADE_OPERATOR_GRP = 55054 ;

/// �������ͣ�int32(ö��); ������ѡ���Ƿ񷵻�ÿ�����漯��Ĭ��Ϊ0 �����أ�1:����
const int H5SDK_TAG_SELECT_RETURN_DAILY = 55055 ;
    const int32 H5SDK_ENUM_RETURN_DAILY_NO = 0 ; // ������
    const int32 H5SDK_ENUM_RETURN_DAILY_YES = 1 ; // ����

/// �������ͣ�int64; �������𵥴󵥳ɽ����
const int H5SDK_TAG_ORDER_LARGER_NET_TURNOVER = 55057 ;

/// �������ͣ�sequence; �������𵥷���ɽ���� ����0:����;����1:��;����2:�е�;����3:С��
const int H5SDK_TAG_CLASSIFY_ORDER_NET_TURNOVER = 55058 ;

/// �������ͣ�int64; �������ɽ����
const int H5SDK_TAG_NET_TURNOVER = 55059 ;

/// �������ͣ�int64; ��������ʴ󵥳ɽ����
const int H5SDK_TAG_TRANS_LARGER_NET_TURNOVER = 55060 ;

/// �������ͣ�sequence; ��������ʷ���ɽ���� ����0:����;����1:��;����2:�е�;����3:С��
const int H5SDK_TAG_CLASSIFY_TRANS_NET_TURNOVER = 55061 ;

/// �������ͣ�int32; �������ڻ�����Դʱ�䣨���ڻ�ʹ�ã�
const int H5SDK_TAG_RECORD_TIME = 20228 ;

/// �������ͣ�int64; ��������
const int H5SDK_TAG_OPEN_VOL = 20229 ;

/// �������ͣ�int64; ��������ƽ
const int H5SDK_TAG_CLOSE_VOL = 20230 ;

/// �������ͣ�int64; �����������л�
const int H5SDK_TAG_CHANGE_MAIN_FLAG = 20231 ;

/// �������ͣ�int32; ��������Լ��������
const int H5SDK_TAG_STOCK_CREATE_DATE = 20332 ;

/// �������ͣ�int32; ��������Լ��������
const int H5SDK_TAG_STOCK_LIST_DATE = 20334 ;

/// �������ͣ�bytevector; �������ͻ���ip��ַ
const int H5SDK_TAG_CLIENT_IP = 20335 ;

/// �������ͣ�sequence; ������5�����������ͳ�� ���α�ʾ����;��;�е�;С��
const int H5SDK_TAG_CLASSIFY_ORDER_BID_PAST5 = 55062 ;

/// �������ͣ�sequence; ������5������������ͳ�� ���α�ʾ����;��;�е�;С��
const int H5SDK_TAG_CLASSIFY_ORDER_OFFER_PAST5 = 55063 ;

/// �������ͣ�sequence; ������10�����������ͳ�� ���α�ʾ����;��;�е�;С��
const int H5SDK_TAG_CLASSIFY_ORDER_BID_PAST10 = 55064 ;

/// �������ͣ�sequence; ������10������������ͳ�� ���α�ʾ����;��;�е�;С��
const int H5SDK_TAG_CLASSIFY_ORDER_OFFER_PAST10 = 55065 ;

/// �������ͣ�sequence; ����������չ����  ���α�ʾ���� 5�� 10�ռ���
const int H5SDK_TAG_ORDER_EXT_DATA = 55066 ;

/// �������ͣ�int32; ������������������������Ϊ������������������Ϊ������������
const int H5SDK_TAG_CONTINUE_IN_DAYS = 55067 ;

/// �������ͣ�int32; �������ʽ��������
const int H5SDK_TAG_TURNOVER_IN_COUNT = 55068 ;

/// �������ͣ�int32; �������ʽ���������
const int H5SDK_TAG_TURNOVER_OUT_COUNT = 55069 ;

/// �������ͣ�int64; ����������������
const int H5SDK_TAG_MAIN_TOTAL_IN = 55070 ;

/// �������ͣ�int64; ����������������
const int H5SDK_TAG_MAIN_TOTAL_OUT = 55071 ;

/// �������ͣ�int64; ����������������
const int H5SDK_TAG_MAIN_NET_IN = 55072 ;

/// �������ͣ�int64; ������ɢ��������
const int H5SDK_TAG_RETAIL_TOTAL_IN = 55073 ;

/// �������ͣ�int64; ������ɢ��������
const int H5SDK_TAG_RETAIL_TOTAL_OUT = 55074 ;

/// �������ͣ�int64; ������ɢ��������
const int H5SDK_TAG_RETAIL_NET_IN = 55075 ;

/// �������ͣ�int32; ��������ͣ����
const int H5SDK_TAG_UPLIMIT_COUNT = 55077 ;

/// �������ͣ�int32; ��������ͣ����
const int H5SDK_TAG_DOWNLIMIT_COUNT = 55078 ;

/// �������ͣ�int32; �������ǵ����ĵ�λ��9��ʾ����9���Ƿ���8��ʾ����8С��9���Ƿ���-9��ʾС��-9���Ƿ���-8��ʾС��-8����-9���Ƿ�
const int H5SDK_TAG_CHG_LEVEL = 55079 ;

/// �������ͣ�bytevector; �������г����(L1��L2)
const int H5SDK_TAG_MARKET_LEVEL = 20336 ;

/// �������ͣ�int32; �������г���ʱʱ��(0,15)����
const int H5SDK_TAG_MARKET_DELAY_MINS = 20337 ;

/// �������ͣ�int32; ����������T-1����
const int H5SDK_TAG_FUND_T1_DATE = 20338 ;

/// �������ͣ�uint64; ����������T-1��ֵ
const int H5SDK_TAG_FUND_T1_VALUE = 20339 ;

/// �������ͣ�int32; ����������T-2����
const int H5SDK_TAG_FUND_T2_DATE = 20340 ;

/// �������ͣ�uint64; ����������T-2��ֵ
const int H5SDK_TAG_FUND_T2_VALUE = 20341 ;

/// �������ͣ�int32; ����������ʼ����
const int H5SDK_TAG_FUND_START_DATE = 20342 ;

/// �������ͣ�int32; ��������������
/*0-δ֪;1-��Ʊ��;2-�����;3-ծȯ��;4-������;*/
const int H5SDK_TAG_FUND_TYPE = 20343 ;

/// �������ͣ�int32; ������������״̬
/*0-δ֪;1-����;2-��ͣ;3-�ָ�;*/
const int H5SDK_TAG_FUND_BUY_STATUS = 20344 ;

/// �������ͣ�int32; ������������״̬
/*0-δ֪;1-����;2-��ͣ;3-�ָ�;*/
const int H5SDK_TAG_FUND_SELL_STATUS = 20345 ;

/// �������ͣ�int64; �����������ֵ�ǵ���(100��)
const int H5SDK_TAG_FUND_ASSESS_CHANGE = 20346 ;

/// �������ͣ�int64; ����������ʵʱ�ǵ���(100��)
const int H5SDK_TAG_FUND_REAL_CHANGE = 20347 ;

/// �������ͣ�int64; ��������ʳɽ����
const int H5SDK_TAG_TRANS_TOTAL_NET_TURNOVER = 55080 ;

/// �������ͣ�int32; ������ƽ�̼���
const int H5SDK_TAG_FLAT_COUNT = 55081 ;

/// �������ͣ�uint32; �������ɽ����
const int H5SDK_TAG_TRADE_INDEX = 20301 ;

/// �������ͣ�uint32; ���������򷽱��
const int H5SDK_TAG_BUY_NO = 20302 ;

/// �������ͣ�uint32; ���������������
const int H5SDK_TAG_SELL_NO = 20303 ;

/// �������ͣ�uint32; ������ί�б��
const int H5SDK_TAG_ORDER_NO = 20304 ;

/// �������ͣ�int64; ����������ֵ����
const int H5SDK_TAG_FUND_UNVT_BASE = 20349 ;

/// �������ͣ�uint64; �������ʽ�����
const int H5SDK_TAG_MON_IN = 20350 ;

/// �������ͣ�uint64; �������ʽ�����
const int H5SDK_TAG_MON_OUT = 20351 ;

/// �������ͣ�int64; �������ʽ�����
const int H5SDK_TAG_MON_PUREIN = 20352 ;

/// �������ͣ�int32; ��������ʼ��λ
const int H5SDK_TAG_LEVEL_START = 20353 ;

/// �������ͣ�int32; ������������λ
const int H5SDK_TAG_LEVEL_END = 20354 ;

/// �������ͣ�int8; �������Ƿ���/���ڣ���  1:��/���� 2������/������
const int H5SDK_TAG_LAGER_ORDER = 20355 ;

/// �������ͣ�int8; ������ί��/������ 0:buy 1:sell
const int H5SDK_TAG_ENTRUST_BS_SIDE = 20356 ;

/// �������ͣ�int64; ������ָ���������� (���ָ��)
const int H5SDK_TAG_INDEX_RISE_TREND = 20361 ;

/// �������ͣ�int64; ������ָ���µ����� (ǿ����)
const int H5SDK_TAG_INDEX_FALL_TREND = 20362 ;

/// �������ͣ�int32; �������������ͣ�0���ͻ���1:���ط�����2:���ķ�������
const int H5SDK_TAG_LOGIN_FLAG = 22001 ;

/// �������ͣ�int32; ��������½���ر�־(��һλ 0:�����ض����б�1�����ض����б�)
const int H5SDK_TAG_CONTENT_FLAG = 22002 ;

/// �������ͣ�rawdata; ��������½���ݣ��е�½��־����
const int H5SDK_TAG_LOGIN_CONTENT = 22003 ;

/// �������ͣ�rawdata; �����������б�{"subscribes": [{"serverId": "subscribe1","ip": "192.168.0.1","port": "9991","marketMic": ["XDCE", "CCFX"],"funcNo": ["4001","4002","4003"]},{"serverId": "subscribe2","ip": "192.168.0.2","port": "9991","marketMic": ["DEFAULT"],"funcNo": ["4001"]}]}
const int H5SDK_TAG_SUBCRIBE_LIST = 22004 ;

/// �������ͣ�rawdata; �������ͻ���session
const int H5SDK_TAG_CLIENT_SESSION = 22005 ;

/// �������ͣ�uint32; ������bestЭ��·�ɲ�crc������
const int GW_ROUTE_TEMPLET_CRC = 22006 ;

/// �������ͣ�string; ������bestЭ��·�ɲ������ID
const int GW_ROUTE_SERVER_ID = 22007 ;

/// �������ͣ�string; ������session�ڵ���zookeeper�е�·��
const int GW_ROUTE_SESSION_PATH = 22008 ;

/// �������ͣ�string; �������г����ʹ���
const int GW_ROUTE_HQ_TYPE_CODE = 22009 ;

/// �������ͣ�string; ��������Ʊ���ڻ�����
const int GW_ROUTE_PROD_CODE = 22010 ;

/// �������ͣ�string; ������session�ڵ���zookeeper�е�·��
const int H5SDK_TAG_SESSION_PATH = 22011 ;

/// �������ͣ�uint32; ���������ط���1 ���ķ���:2
const int GW_ROUTE_SERVER_TYPE = 22012 ;

/// �������ͣ�uint64; ������·�ɲ�ͻ���session
const int GW_ROUTE_CLIENT_SESSION = 22013 ;

/// �������ͣ�int64; ������4λ��ʾһ�����ܣ���һ����λ0:level1 1:level 2���ڶ�����λ0:ʵʱ1:��ʾ��ʱ �磺0x10 ����ʱlevel1���飩
const int GW_ROUTE_HQ_LEVEL = 22014 ;

/// �������ͣ�uint32; ������·�ɲ�����
const int GW_ROUTE_ERROR_NO = 22015 ;

/// �������ͣ�uint32; ������0:�Զ���ʼ�� 1:ǿ�Ƴ�ʼ��
const int H5SDK_TAG_INIT_FLAG = 22016 ;

/// �������ͣ�bytevector; ������������id
const int H5SDK_TAG_SERVER_ID = 22017 ;

/// �������ͣ�rawdata; ���������ط�������Ϣ 0:{"markets": ["XDCE","CCFX" ]}
const int H5SDK_TAG_GW_SERVER_INFO = 22018 ;

/// �������ͣ�uint32; ��������������Ϣ���� 0����ʾ�г�����
const int H5SDK_TAG_SERVER_INFO_TYPE = 22019 ;

/// �������ͣ�sequence; ��������������Ϣ�ظ���
const int H5SDK_TAG_SERVER_INFO_GRP = 22020 ;

/// �������ͣ�rawdata; ��������̨��������Ϣ0:{"markets": [{"market": "XDCE", "tradedate": "20170228"}, {"market": "CCFX", "tradedate": "20170228"}]}
const int H5SDK_TAG_BACK_SERVER_INFO = 22021 ;

/// �������ͣ�bytevector; ������enable 1:���� 0:������ {"markets":[{"market": "XDCE","enable": "1"},{"market": "CCFX","enable": "0"}]}
const int H5SDK_TAG_SERVER_SATAE = 22022 ;

/// �������ͣ�bytevector; �������û���־
const int GW_ROUTE_AUTH_ID = 22023 ;

/// �������ͣ�bytevector; �������û�Ȩ��
const int GW_ROUTE_AUTH_STR = 22024 ;

/// �������ͣ�rawdata; �������û���־
const int GW_ROUTE_USER_KEY = 22025 ;

/// �������ͣ�int16; �����������ֶζ��ļ���
const int H5SDK_TAG_FIELDS_LEVEL = 22026 ;

/// �������ͣ�int16; ������·�ɲ��ϵ������ֶζ��ļ���
const int GW_ROUTE_FIELDS_LEVEL = 22027 ;

/// �������ͣ�string; ������·�ɲ�appkey�ֶ�
const int GW_ROUTE_APP_KEY = 22028 ;

/// �������ͣ�int8(ö��); ������ȡ���뷶Χ��Ĭ��Ϊ0��
const int H5SDK_TAG_STOCK_RANGE = 55082 ;
    const int8 H5SDK_TAG_STOCKESA = 0 ; // ȫ�г�
    const int8 H5SDK_TAG_WITHOUT_SN = 1 ; // ��ST���¹�
    const int8 H5SDK_TAG_STOCKST = 2 ; // ST��
    const int8 H5SDK_TAG_STOCKNEW = 3 ; // �¹�

/// �������ͣ�int8(ö��); �������ֲ����ͣ�Ĭ��Ϊ0��
const int H5SDK_TAG_DIAGRAM_TYPE = 55083 ;
    const int8 H5SDK_TAG_COMMON_DIAGRAM = 0 ; // ͨ�÷ֲ�
    const int8 H5SDK_TAG_STOCKEXST = 1 ; // �ų�ST���¹ɵ��ǵ�ͣ�ֲ�

/// �������ͣ�int8(ö��); ������ָ������������ͽ��л�ȡ��ʷ����
const int H5SDK_TAG_CODE_RELATE_TYPE = 55084 ;
    const int8 H5SDK_TAG_CODE_RELATE_NOMORAL_TYPE = 0 ; // ��ȡ�ô����Ӧ����ʷ����
    const int8 H5SDK_TAG_CODE_RELATE_CONTNO_TYPE = 1 ; // ��ȡ�ô�����1����3����4��Լ��ʷ����
    const int8 H5SDK_TAG_CODE_RELATE_MONCONTN_TYPE = 2 ; // ��ȡ�ô��밴��������ʷ����

/// �������ͣ�int8(ö��); ���������ƻ�ȡ������Ƿ���ȫ��
const int H5SDK_TAG_CODE_FULL = 55085 ;
    const int8 H5SDK_TAG_CODE_NOMORAL = 0 ; // ��ͨSDK������������ȫ��
    const int8 H5SDK_TAG_CODE_ALL = 1 ; // ȫ����������

/// �������ͣ�uint32(ö��); �������춯�ź�����
const int H5SDK_TAG_ANOMALY_SIGNAL_TYPE = 55086 ;

/// �������ͣ�bytevector; �������춯�ź�����
const int H5SDK_TAG_ANOMALY_SIGNAL_NAME = 55087 ;

/// �������ͣ�sequence; �������춯�ź��б�
const int H5SDK_TAG_ANOMALY_SIGNAL_GRP = 55090 ;

/// �������ͣ�sequence; �������춯�źŽ���б�
const int H5SDK_TAG_ANOMALY_SIGNAL_RESULT_GRP = 55091 ;

/// �������ͣ�uint32; �������춯�źŽ������key
const int H5SDK_TAG_ANOMALY_SIGNAL_RESULT_KEY = 55092 ;

/// �������ͣ�int64; �������춯�źŽ������ֵ
const int H5SDK_TAG_ANOMALY_SIGNAL_RESULT_VALUE = 55093 ;

/// �������ͣ�uint8(ö��); �������춯�źŵķ���
const int H5SDK_TAG_ANOMALY_SIGNAL_DIRECTION = 55094 ;
    const uint8 H5SDK_ENUM_PLAT_DIRECT = 0 ; // ƽ
    const uint8 H5SDK_ENUM_UP_DIRECT = 1 ; // ��
    const uint8 H5SDK_ENUM_DOWN_DIRECT = 2 ; // ��

/// �������ͣ�uint32; ������ֵ�Ŵ���
const int H5SDK_TAG_VALUE_SCALE = 55095 ;

/// �������ͣ�int32; ������5.0�г�����
const int H5SDK_TAG_HQ50_MARKET_TYPE = 55096 ;

/// �������ͣ�sequence; �������춯�źŽ����ʽ�б�
const int H5SDK_TAG_ANOMALY_SIGNAL_FORMAT_GRP = 55097 ;

/// �������ͣ�bytevector; ������չʾǰ׺
const int H5SDK_TAG_FORMAT_PREFIX = 55098 ;

/// �������ͣ�bytevector; ������չʾ��׺
const int H5SDK_TAG_FORMAT_SUFFIX = 55099 ;

/// �������ͣ�uint8; ������չʾС����λ��
const int H5SDK_TAG_FORMAT_DECIMAL_DIGITS = 55100 ;

/// �������ͣ�sequence; �������������б�
const int H5SDK_TAG_BLOCK_PROD_CODE_GRP = 55101 ;

/// �������ͣ�uint32; ��������ʶspecial_marker�����ʱ������Ҫ�������е�λ����������һ��λ
/*0���������е������־λ
1��ֻ��Ҫ��������һ��λ*/
const int H5SDK_TAG_MARK_TYPE = 55102 ;

/// �������ͣ�uint32; �������ɽ���ǣ�0����ͨ�ɽ���1�������ɽ�
const int H5SDK_TAG_TRANS_FLAG = 55103 ;

/// �������ͣ�uint64; ����������������
const int H5SDK_TAG_SERVER_DATE = 55104 ;

/// �������ͣ�int32; ��������ǰ�̺�����
const int H5SDK_TAG_PREPOST_DATE = 20367 ;

/// �������ͣ�int32; ��������ǰ�̺�ʱ��
const int H5SDK_TAG_PREPOST_time = 98 ;

/// �������ͣ�int32; ������Ͷ��Ӯ�ҵ��г�����
const int H5SDK_TAG_HQ40_MARKET_TYPE = 55105 ;

/// �������ͣ�int32; ��������ͣ����
const int H5SDK_TAG_UP_LIMIT_COUNT = 20372 ;

/// �������ͣ�int32; ������������ͣ����
const int H5SDK_TAG_TOUCH_UP_LIMIT_COUNT = 20373 ;

/// �������ͣ�int32; ������ST����ͣ����
const int H5SDK_TAG_ST_UP_LIMIT_COUNT = 20374 ;

/// �������ͣ�int32; ������ST�ɴ�����ͣ����
const int H5SDK_TAG_ST_TOUCH_UP_LIMIT_COUNT = 20375 ;

/// �������ͣ�int32; ��������ͣ����
const int H5SDK_TAG_DOWN_LIMIT_COUNT = 20376 ;

/// �������ͣ�int32; �����������ͣ����
const int H5SDK_TAG_TOUCH_DOWN_LIMIT_COUNT = 20377 ;

/// �������ͣ�int32; ������ST�ɵ�ͣ����
const int H5SDK_TAG_ST_DOWN_LIMIT_COUNT = 20378 ;

/// �������ͣ�int32; ������ST�ɴ����ͣ����
const int H5SDK_TAG_ST_TOUCH_DOWN_LIMIT_COUNT = 20379 ;

/// �������ͣ�sequence; �������춯��������
const int H5SDK_TAG_ANOMALY_FACTOR_GRP = 55106 ;

/// �������ͣ�bytevector; �������춯��������
const int H5SDK_TAG_ANOMALY_FACTOR_NAME = 55107 ;

/// �������ͣ�uint8; ������������ǣ�Ĭ��Ϊ0����ʾ��ͨ���źţ�ֵΪ1ʱ��ʾ������ʷ�źţ��ڲ�ѯӦ���и�ֵ��ԶΪ0���������ź��п���Ϊ����ֵ
const int H5SDK_TAG_CANCEL_FLAG = 55108 ;

/// �������ͣ�int64; ������Ψһ���һ���춯�źŵ�У���
const int H5SDK_TAG_ANOMALY_SIGNAL_CRC = 55109 ;

/// �������ͣ�int8(ö��); ��������ʱ���Ĭ��Ϊ0��
const int H5SDK_TAG_TREND_TYPE = 55110 ;
    const int8 H5SDK_TAG_TREND_NORMAL = 0 ; // 240��������
    const int8 H5SDK_TAG_TREND_CUSTOM = 1 ; // 241��������

/// �������ͣ�sequence; ��������λ����
const int H5SDK_TAG_LEVEL_GRP = 55111 ;

/// �������ͣ�sequence; �������г������б�
const int H5SDK_TAG_HQ_MIC_TYPE_GRP = 55112 ;

/// �������ͣ�int32; �������г����� 0:ȫ�г� 1���Ϻ���ST 2���Ϻ�ST 3�����ڷ�ST 4����֤ST
const int H5SDK_TAG_HQ_MIC_TYPE = 55113 ;

/// �������ͣ�int32; ������ͳ������ 0:��ͣ������ԭ�� 1����ͣ���� 2��������ͣ��3��������ͣ
const int H5SDK_TAG_HQ_STATISTIC_TYPE = 55114 ;

/// �������ͣ�int32; �������ز����
const int H5SDK_TAG_RETURN_RANGE = 55115 ;

/// �������ͣ�int32; �������ǵ�ͣԭ��
const int H5SDK_TAG_UPDOWN_REASON = 55116 ;

/// �������ͣ�int64; ������ͳ�ƽ��
const int H5SDK_TAG_STATISTIC_RESULT = 55117 ;

/// �������ͣ�sequence; �������ǵ�ͣԭ���б�
const int H5SDK_TAG_UPDOWN_REASON_GRP = 55118 ;

/// �������ͣ�uint8(ö��); �������ǵ�ͣԭ������
const int H5SDK_TAG_STATISTIC_REASON_TYPE = 55119 ;
    const uint8 H5SDK_TAG_UP_REASON = 0 ; // ��ͣ����
    const uint8 H5SDK_TAG_DOWN_REASON = 1 ; // ��ͣ����

/// �������ͣ�int32; ������ƽ���Ƿ�
const int H5SDK_TAG_AVERAGE_RISE = 55122 ;

/// �������ͣ�int32; �������ӷ��� 0��all 1��ST�� 2����ST��
const int H5SDK_TAG_HQ_SUB_TYPE = 55123 ;

/// �������ͣ�int32; ������������ͣ�Ĵ����н�����ͣ�ĸ���
const int H5SDK_TAG_TODAY_UP_NUM = 55124 ;

/// �������ͣ�int32; ������������ͣ�Ĵ�����
const int H5SDK_TAG_YESTERDAY_UP_NUM = 55125 ;

/// �������ͣ�int32; ��������ͣ����
const int H5SDK_TAG_UP_COUNT = 55126 ;

/// �������ͣ�int32; ��������ͣ��������Ǵ���
const int H5SDK_TAG_UP_NEXT_DAY_RISE_COUNT = 55127 ;

/// �������ͣ�int32; ��������ͣ�����ƽ���ǵ���
const int H5SDK_TAG_UP_NEXT_DAY_AVE_PCHANGE_RATE = 55128 ;

/// �������ͣ�int32; ��������ͣ����
const int H5SDK_TAG_DOWN_COUNT = 55129 ;

/// �������ͣ�int32; ��������ͣ��������Ǵ���
const int H5SDK_TAG_DOWN_NEXT_DAY_RISE_COUNT = 55130 ;

/// �������ͣ�int32; ��������ͣ�����ƽ���ǵ���
const int H5SDK_TAG_DOWN_NEXT_DAY_AVE_PCHANGE_RATE = 55131 ;

/// �������ͣ�int32; �����������ͣ����
const int H5SDK_TAG_DBZT_COUNT = 55132 ;

/// �������ͣ�int32; �����������ͣ��������Ǵ���
const int H5SDK_TAG_DBZT_NEXT_DAY_RISE_COUNT = 55133 ;

/// �������ͣ�int32; �����������ͣ�����ƽ���ǵ���
const int H5SDK_TAG_DBZT_NEXT_DAY_AVE_PCHANGE_RATE = 55134 ;

/// �������ͣ�int32; ��������ͣ���״���
const int H5SDK_TAG_DTCD_COUNT = 55135 ;

/// �������ͣ�int32; ��������ͣ���׺�������Ǵ���
const int H5SDK_TAG_DTCD_NEXT_DAY_RISE_COUNT = 55136 ;

/// �������ͣ�int32; ��������ͣ���׺����ƽ���ǵ���
const int H5SDK_TAG_DTCD_NEXT_DAY_AVE_PCHANGE_RATE = 55137 ;

/// �������ͣ�int64; ���������³ɽ���
const int H5SDK_TAG_LAST_EXT_PX = 55138 ;

/// �������ͣ�int32; ��������ǰ����Ϊ�Ƿ������̼��ֶεı��
const int H5SDK_TAG_NOMINAL_PX = 55139 ;

/// �������ͣ�uint64; ��������������ɽ���
const int H5SDK_TAG_BUSINESS_BID_SUP_AMOUNT = 55140 ;

/// �������ͣ�uint64; ��������������ɽ���
const int H5SDK_TAG_BUSINESS_BID_SUP_BALANCE = 55141 ;

/// �������ͣ�uint32; ��������������ɽ�����
const int H5SDK_TAG_BUSINESS_BID_SUP_COUNT = 55142 ;

/// �������ͣ�uint32; ��������������ί�е���
const int H5SDK_TAG_BID_SUP_ENTRUST_COUNT = 55143 ;

/// �������ͣ�uint64; ������������ɽ���
const int H5SDK_TAG_BUSINESS_BID_BIG_AMOUNT = 55144 ;

/// �������ͣ�uint64; ������������ɽ���
const int H5SDK_TAG_BUSINESS_BID_BIG_BALANCE = 55145 ;

/// �������ͣ�uint32; ������������ɽ�����
const int H5SDK_TAG_BUSINESS_BID_BIG_COUNT = 55146 ;

/// �������ͣ�uint32; ������������ί�е���
const int H5SDK_TAG_BID_BIG_ENTRUST_COUNT = 55147 ;

/// �������ͣ�uint64; �������е�����ɽ���
const int H5SDK_TAG_BUSINESS_BID_MID_AMOUNT = 55148 ;

/// �������ͣ�uint64; �������е�����ɽ���
const int H5SDK_TAG_BUSINESS_BID_MID_BALANCE = 55149 ;

/// �������ͣ�uint32; �������е�����ɽ�����
const int H5SDK_TAG_BUSINESS_BID_MID_COUNT = 55150 ;

/// �������ͣ�uint32; �������е�����ί�е���
const int H5SDK_TAG_BID_MID_ENTRUST_COUNT = 55151 ;

/// �������ͣ�uint64; ������С������ɽ���
const int H5SDK_TAG_BUSINESS_BID_LITTLE_AMOUNT = 55152 ;

/// �������ͣ�uint64; ������С������ɽ���
const int H5SDK_TAG_BUSINESS_BID_LITTLE_BALANCE = 55153 ;

/// �������ͣ�uint32; ������С������ɽ�����
const int H5SDK_TAG_BUSINESS_BID_LITTLE_COUNT = 55154 ;

/// �������ͣ�uint32; ������С������ί�е���
const int H5SDK_TAG_BID_LITTLE_ENTRUST_COUNT = 55155 ;

/// �������ͣ�uint64; ���������������ɽ���
const int H5SDK_TAG_BUSINESS_OFFER_SUP_AMOUNT = 55156 ;

/// �������ͣ�uint64; ���������������ɽ���
const int H5SDK_TAG_BUSINESS_OFFER_SUP_BALANCE = 55157 ;

/// �������ͣ�uint32; ���������������ɽ�����
const int H5SDK_TAG_BUSINESS_OFFER_SUP_COUNT = 55158 ;

/// �������ͣ�uint32; ��������������ί�е���
const int H5SDK_TAG_OFFER_SUP_ENTRUST_COUNT = 55159 ;

/// �������ͣ�uint64; �������������ɽ���
const int H5SDK_TAG_BUSINESS_OFFER_BIG_AMOUNT = 55160 ;

/// �������ͣ�uint64; �������������ɽ���
const int H5SDK_TAG_BUSINESS_OFFER_BIG_BALANCE = 55161 ;

/// �������ͣ�uint32; �������������ɽ�����
const int H5SDK_TAG_BUSINESS_OFFER_BIG_COUNT = 55162 ;

/// �������ͣ�uint32; ������������ί�е���
const int H5SDK_TAG_OFFER_BIG_ENTRUST_COUNT = 55163 ;

/// �������ͣ�uint64; �������е������ɽ���
const int H5SDK_TAG_BUSINESS_OFFER_MID_AMOUNT = 55164 ;

/// �������ͣ�uint64; �������е������ɽ���
const int H5SDK_TAG_BUSINESS_OFFER_MID_BALANCE = 55165 ;

/// �������ͣ�uint32; �������е������ɽ�����
const int H5SDK_TAG_BUSINESS_OFFER_MID_COUNT = 55166 ;

/// �������ͣ�uint32; �������е�����ί�е���
const int H5SDK_TAG_OFFER_MID_ENTRUST_COUNT = 55167 ;

/// �������ͣ�uint64; ������С�������ɽ���
const int H5SDK_TAG_BUSINESS_OFFER_LITTLE_AMOUNT = 55168 ;

/// �������ͣ�uint64; ������С�������ɽ���
const int H5SDK_TAG_BUSINESS_OFFER_LITTLE_BALANCE = 55169 ;

/// �������ͣ�uint32; ������С�������ɽ�����
const int H5SDK_TAG_BUSINESS_OFFER_LITTLE_COUNT = 55170 ;

/// �������ͣ�uint32; ������С������ί�е���
const int H5SDK_TAG_OFFER_LITTLE_ENTRUST_COUNT = 55171 ;

/// �������ͣ�sequence; �������ļ�����
const int H5SDK_TAG_FILE_GRP = 55172 ;

/// �������ͣ�bytevector; �������ļ�·��
const int H5SDK_TAG_FILE_PATH = 55173 ;

/// �������ͣ�int16(ö��); �������ļ�����
const int H5SDK_TAG_HQ_FILE_EXT = 55174 ;
    const int16 H5SDK_TAG_HQ_FILE_EXT_NORMAL = 0 ; // ԭʼ�����ļ�
    const int16 H5SDK_TAG_HQ_FILE_EXT_ZIP = 1 ; // zipѹ���ļ�

/// �������ͣ�uint64; ��������С
const int H5SDK_TAG_SIZE = 55175 ;

/// �������ͣ�sequence; ������������˾�������Ϣ��
const int H5SDK_TAG_TERM_INFOSHEET_GRP = 55176 ;

/// �������ͣ�bytevector; ��������˾����
const int H5SDK_TAG_TERM_COMP_NAME = 55177 ;

/// �������ͣ�bytevector; ��������˾�������ƻ��������
const int H5SDK_TAG_TERM_CORR_NAME = 55178 ;

/// �������ͣ�bytevector; ����������title
const int H5SDK_TAG_TERM_CORR_TITLE = 55179 ;

/// �������ͣ�bytevector; ������EMAIL
const int H5SDK_TAG_TERM_CORR_EMAIL = 55180 ;

/// �������ͣ�bytevector; ��������ϵ�绰
const int H5SDK_TAG_TERM_CORR_PHONE = 55181 ;

/// �������ͣ�bytevector; ��������˾���߸�����ϸ��ϵ��ַ
const int H5SDK_TAG_TERM_CORR_ADDRESS = 55182 ;

/// �������ͣ�bytevector; �������û��ʺ�
const int H5SDK_TAG_TERM_USER_ACCOUNT = 55183 ;

/// �������ͣ�bytevector; ������ʹ�����飬���� XHKG-M,XHKG-G��
const int H5SDK_TAG_TERM_QUOTE_MARKET = 55184 ;

/// �������ͣ�bytevector; �������ն��������
const int H5SDK_TAG_TERM_APP_NAME = 55185 ;

/// �������ͣ�uint32; �����������ȶ�ֵ
const int H5SDK_TAG_HQ_HOT_SCORE = 55186 ;

/// �������ͣ�uint32; �����������ֶ�
const int H5SDK_TAG_STARE_FIELD = 55187 ;

/// �������ͣ�int16(ö��); ���������̷���
const int H5SDK_TAG_STARE_DIRECTION = 55188 ;
    const int16 H5SDK_TAG_STARE_DIRECTION_RISE = 0 ; // ���̷�������
    const int16 H5SDK_TAG_STARE_DIRECTION_FALL = 1 ; // ���̷�������

/// �������ͣ�int64; �����������ֶζ�Ӧ�ļ��ֵ
const int H5SDK_TAG_STARE_VALUE = 55189 ;

/// �������ͣ�bytevector; ���������̴���ʱ�Ļش�����
const int H5SDK_TAG_STARE_USER_DATA = 55190 ;

/// �������ͣ�int64; ���������̴���ʱ��Ӧ�Ķ����ֶ���Ŀ���ֵ
const int H5SDK_TAG_SNAPSHOT_VALUE = 55191 ;

/// �������ͣ�sequence; ������ί��λ
const int H5SDK_TAG_HK_BID_GRP = 55192 ;

/// �������ͣ�sequence; ������ί����λ
const int H5SDK_TAG_HK_OFFER_GRP = 55193 ;

/// �������ͣ�int32; ��������λ���
const int H5SDK_TAG_HK_SPREAD_LEVEL = 55194 ;

/// �������ͣ�sequence; ������ί�ж����б�
const int H5SDK_TAG_HK_ENTRUST_GRP = 55195 ;

/// �������ͣ�uint32; ������ί����
const int H5SDK_TAG_HK_ENTRUST_AMOUNT = 55196 ;

/// �������ͣ�sequence; �������۹ɵ������
const int H5SDK_TAG_HK_CLICK_PRICE_GRP = 55197 ;

/// �������ͣ�uint32; ������ʵʱһ�������ܴ���
const int H5SDK_TAG_ONE_LEVEL_COUNT = 55198 ;

/// �������ͣ�uint32; ������ʵʱʮ�������ܴ���
const int H5SDK_TAG_TEN_LEVEL_COUNT = 55199 ;

/// �������ͣ�uint32; ������ʵʱʮ���뾭�ö��б����ܴ���
const int H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_COUNT = 55200 ;

/// �������ͣ�uint32; ������ʵʱһ��ʣ�����
const int H5SDK_TAG_ONE_LEVEL_CURR_NUM = 55201 ;

/// �������ͣ�uint32; ������ʵʱʮ��ʣ�����
const int H5SDK_TAG_TEN_LEVEL_CURR_NUM = 55202 ;

/// �������ͣ�uint32; ������ʵʱʮ���뾭�ö���ʣ�����
const int H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_CURR_NUM = 55203 ;

/// �������ͣ�uint32(ö��); ������ʵʱһ���Ƿ����޴�ʹ��
const int H5SDK_TAG_ONE_LEVEL_LIMIT = 55204 ;
    const uint32 H5SDK_TAG_ONE_LEVEL_ENABLE = 0 ; // 
    const uint32 H5SDK_TAG_ONE_LEVEL_DISABLE = 1 ; // 

/// �������ͣ�uint32(ö��); ������ʵʱʮ���Ƿ����޴�ʹ��
const int H5SDK_TAG_TEN_LEVEL_LIMIT = 55207 ;
    const uint32 H5SDK_TAG_TEN_LEVEL_ENABLE = 0 ; // 
    const uint32 H5SDK_TAG_TEN_LEVEL_DISABLE = 1 ; // 

/// �������ͣ�uint32(ö��); ������ʵʱʮ���뾭�ö����Ƿ����޴�ʹ��
const int H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_LIMIT = 55210 ;
    const uint32 H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_ENABLE = 0 ; // 
    const uint32 H5SDK_TAG_TEN_LEVEL_BROKER_QUEUE_DISABLE = 1 ; // 

/// �������ͣ�sequence; ������ί�򾭼õ�λ
const int H5SDK_TAG_BID_BROKER_GRP = 55213 ;

/// �������ͣ�sequence; ������ί�����õ�λ
const int H5SDK_TAG_OFFER_BROKER_GRP = 55214 ;

/// �������ͣ�int32; ������ÿ��ת�����ɣ�
const int H5SDK_TAG_ZZSHARERAIO = 55215 ;

/// �������ͣ�int32; ������ÿ�ɶԼ۹�Ʊ���ɣ�
const int H5SDK_TAG_DJSHARERAIO = 55216 ;

/// �������ͣ�int32; ������ÿ�ɶԼ��ֽ�Ԫ��
const int H5SDK_TAG_DJCASHDIVI = 55217 ;

/// �������ͣ�int32; ������ÿ�����ɣ��ɣ�
const int H5SDK_TAG_SGSHARERAIO = 55218 ;

/// �������ͣ�int32; ������ÿ�ɲ�֣��ɣ�
const int H5SDK_TAG_CFSHARERAIO = 55219 ;

/// �������ͣ�bytevector; ����������
const int H5SDK_TAG_EXER_FACTOR = 55220 ;

/// �������ͣ�bytevector; ����������
const int H5SDK_TAG_CONST_VALUE = 55221 ;

/// �������ͣ�bytevector; �����������Ϣ
const int H5SDK_TAG_MARK = 55222 ;

/// �������ͣ�bytevector; ��������Ȩ��������
const int H5SDK_TAG_BACKWARD_FACTOR = 55223 ;

/// �������ͣ�bytevector; ������ǰ��Ȩ��������
const int H5SDK_TAG_FORWARD_FACTOR = 55224 ;

/// �������ͣ�uint32(ö��); ���������߾�ת�ź�
const int H5SDK_TAG_NINE_TURN_SIGNAL_DAY = 55225 ;
    const uint32 H5SDK_TAG_NINE_TURN_SIGNAL_DAY_BUY = 1 ; // ���߾�ת�����ź�
    const uint32 H5SDK_TAG_NINE_TURN_SIGNAL_DAY_SELL = 2 ; // ���߾�ת�����ź�

/// �������ͣ�uint32(ö��); ��������ʱ��ת�ź�
const int H5SDK_TAG_NINE_TURN_SIGNAL_TREND = 55226 ;
    const uint32 H5SDK_TAG_NINE_TURN_SIGNAL_TREND_BUY = 1 ; // ��ʱ��ת�����ź�
    const uint32 H5SDK_TAG_NINE_TURN_SIGNAL_TREND_SELL = 2 ; // ��ʱ��ת�����ź�

/// �������ͣ�int32; ������������򣬲����ʾ���š�1��ʾ��һ���������2��ʾ�Զ����������
const int H5SDK_TAG_SORT_LEVEL = 55227 ;

/// �������ͣ�bytevector; �������ַ�����ǰ��Ȩ����
const int H5SDK_TAG_EXER_FORWARD_B_STR = 55228 ;

/// �������ͣ�bytevector; �������ַ����ͺ�Ȩ����
const int H5SDK_TAG_EXER_BACKWARD_B_STR = 55229 ;


#endif /* __H5_SDK_TAG_H__ */

