#include    <mds_api.h>
#include    <mds_api/parser/mds_protocol_parser.h>
#include    <mds_api/parser/json_parser/mds_json_parser.h>
#include    <sutil/logger/spk_log.h>
#include <string>
#include "datatype.h"
#include "queue.h"
#include "md_publisher.h"
#include "utility.h"

using namespace std;

#define SHARED_QUEUE_SIZE 8192
static int queue_shm_fd = 0;
static int data_shm_fd = 0;
static struct vrt_queue* _q ;
static PVO* _md_data;
static struct vrt_producer* _p;
void init_shm_queue(const Config& config) {
    string queue_data_str = config.mdQueuePrefix();
    string queue_str = queue_data_str + "_queue";
    string queue_producer = queue_data_str + "_producer";
    
    _q = vrt_queue_new (queue_str.c_str(), SHARED_QUEUE_SIZE, sizeof(PVO), &queue_shm_fd);
    _md_data = (PVO*)vrt_data_new(queue_data_str.c_str(), (_q->value_mask + 1)*sizeof(PVO), &data_shm_fd);
    _p = vrt_producer_new(queue_producer.c_str(), 1, _q, 0, true); 
}

/**
 * 通过证券代码列表, 重新订阅行情数据 (根据代码前缀区分所属市�?)
 *
 * @param   pTcpChannel         会话信息
 * @param   pCodeListString     证券代码列表字符�? (以空格或逗号/分号/竖线分割的字符串)
 * @return  TRUE 成功; FALSE 失败
 */
static BOOL
MdsApiSample_ResubscribeByCodePrefix(MdsApiSessionInfoT *pTcpChannel,
        const char *pCodeListString) {
    /* 上海证券代码前缀 */
    static const char       SSE_CODE_PREFIXES[] = \
            "009, 01, 02, "                 /* 国�? */    \
            "10, 11, 12, 13, 18, 19, "      /* 债券 (企业债、可转债等) */ \
            "20, "                          /* 债券 (回购) */   \
            "5, "                           /* 基金 */    \
            "6";                            /* A�? */

    /* 深圳证券代码前缀 */
    static const char       SZSE_CODE_PREFIXES[] = \
            "00, "                          /* 股票 */    \
            "10, 11, 12, 13, "              /* 债券 */    \
            "15, 16, 17, 18, "              /* 基金 */    \
            "30";                           /* 创业�? */

    return MdsApi_SubscribeByStringAndPrefixes(pTcpChannel,
            pCodeListString, (char *) NULL,
            SSE_CODE_PREFIXES, SZSE_CODE_PREFIXES,
            MDS_SECURITY_TYPE_STOCK, MDS_SUB_MODE_SET,
            MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS);
}


/**
 * 通过证券代码列表, 重新订阅行情数据 (根据代码后缀区分所属市�?, 如果没有指定后缀, 则默认为上证股票)
 *
 * @param   pTcpChannel         会话信息
 * @param   pCodeListString     证券代码列表字符�? (以空格或逗号/分号/竖线分割的字符串)
 * @return  TRUE 成功; FALSE 失败
 */
static BOOL
MdsApiSample_ResubscribeByCodePostfix(MdsApiSessionInfoT *pTcpChannel,
        const char *pCodeListString , eMdsExchangeIdT exch) {
    return MdsApi_SubscribeByString(pTcpChannel,
            pCodeListString, (char *) NULL,
            exch, MDS_SECURITY_TYPE_STOCK, MDS_SUB_MODE_APPEND,
            MDS_SUB_DATA_TYPE_L1_SNAPSHOT | MDS_SUB_DATA_TYPE_L2_SNAPSHOT | MDS_SUB_DATA_TYPE_L2_TRADE| MDS_SUB_DATA_TYPE_L2_ORDER );
}

void publish_trade(MdsL2TradeT& trade) {
    auto recv_nano = get_nanosec();
    
    if  (trade.BidApplSeqNum == 0) {//卖撤�?
        return;
    }
    int posi = 0;
    vrt_producer_claim(_p, &posi);
    PVO& data = _md_data[posi];
    data.recv_nano = recv_nano;
    data.instrId = trade.instrId;
    data.price = trade.TradePrice;
    data.vol = trade.TradeQty;
    data.update_time = trade.TransactTime;
    data.type = TYPE_TRADE;
    data.seq_num = trade.BidApplSeqNum;
    if (trade.OfferApplSeqNum == 0) {//买撤�?
        data.vol = INT_MAX;
    }

    vrt_producer_publish(_p);

    //fprintf(stdout, "trade,szCode=>%s,nTime=>%d,nPrice=>%d,nVolume=>%d,nBidOrder=>%ld,nAskOrder=>%ld,recv_nano=>%lu\n", 
    //        trade.SecurityID,trade.TransactTime,data.price,data.vol,data.seq_num, trade.OfferApplSeqNum, recv_nano);

}

void publish_order(MdsL2OrderT& order)
{
    auto recv_nano = get_nanosec();
    int posi = 0;
    vrt_producer_claim(_p, &posi);
    PVO& data = _md_data[posi];
    data.recv_nano = recv_nano;
    data.instrId = order.instrId;
    strncpy(data.code, order.SecurityID, sizeof(order.SecurityID));
    data.price = order.Price;
    data.vol = order.OrderQty;
    data.update_time = order.TransactTime;
    data.type = TYPE_ORDER;
    data.seq_num = order.ApplSeqNum;
    if (order.OrderType == '1' || order.OrderType == 'U') {//市价或本方最优价
        data.price = INT_MAX;
    }
    if(order.Side == '1') {
        data.direction = DIRECTION_BUY;
    } else if(order.Side == '2') {
        data.direction = DIRECTION_SELL;
    }

    vrt_producer_publish(_p);

    fprintf(stdout, "order,szCode=>%s,nTime=>%d,nPrice=>%d,nVolume=>%d,nOrder=>%ld,direction=>%d,recv_nano=>%lu\n",
            order.SecurityID,order.TransactTime,data.price,data.vol,data.seq_num,data.direction,recv_nano);

    }

void publish_snapshot(MdsMktDataSnapshotT& snapshot) {
    int posi = 0;
    vrt_producer_claim(_p, &posi);
    PVO& data = _md_data[posi];
    data.recv_nano =  get_nanosec();
    data.instrId = snapshot.head.instrId;
    strncpy(data.code, snapshot.l2Stock.SecurityID, sizeof(snapshot.l2Stock.SecurityID));
    data.price = snapshot.l2Stock.OpenPx;
    data.pre_close = snapshot.l2Stock.PrevClosePx;
    data.update_time = snapshot.head.updateTime;
    data.last_price = snapshot.l2Stock.TradePx;
    data.vol = snapshot.l2Stock.TotalVolumeTraded;
    
    for (int i = 0; i < 10; i++) {
        data.bid_prices[i] = snapshot.l2Stock.BidLevels[i].Price;
        data.bid_vols[i] = snapshot.l2Stock.BidLevels[i].OrderQty;
        data.ask_prices[i] = snapshot.l2Stock.OfferLevels[i].Price;
        data.ask_vols[i] = snapshot.l2Stock.OfferLevels[i].OrderQty;
    }
    

    data.type = TYPE_SNAPSHOT;
   
    vrt_producer_publish(_p);
    fprintf(stdout, "snapshot,szCode=>%s,nTime=>%d,bp1=>%d,bv1=>%d,recv_nano=>%lu\n",data.code,data.update_time,data.bid_prices[0],data.bid_vols[0], data.recv_nano);
}

void publish_snapshot_l1(MdsMktDataSnapshotT& snapshot) {  
    int posi = 0;
    vrt_producer_claim(_p, &posi);
    PVO& data = _md_data[posi];
    data.recv_nano =  get_nanosec();
    data.instrId = snapshot.head.instrId;
    strncpy(data.code, snapshot.stock.SecurityID, sizeof(snapshot.stock.SecurityID));
    data.price = snapshot.stock.OpenPx;
    data.pre_close = snapshot.stock.PrevClosePx;
    data.update_time = snapshot.head.updateTime;
    data.last_price = snapshot.stock.TradePx;
    data.vol = snapshot.stock.TotalVolumeTraded;
    
    for (int i = 0; i < 5; i++) {
        data.bid_prices[i] = snapshot.stock.BidLevels[i].Price;
        data.bid_vols[i] = snapshot.stock.BidLevels[i].OrderQty;
        data.ask_prices[i] = snapshot.stock.OfferLevels[i].Price;
        data.ask_vols[i] = snapshot.stock.OfferLevels[i].OrderQty;
    }
    
    
    data.type = TYPE_SNAPSHOT_L1;
   
    vrt_producer_publish(_p);
    fprintf(stdout, "snapshot_L1,szCode=>%s,nTime=>%d,bp1=>%d,bv1=>%d,recv_nano=>%lu\n",data.code,data.update_time,data.bid_prices[0],data.bid_vols[0], data.recv_nano);
}

void publish_index(MdsMktDataSnapshotT& snapshot) {
    int posi = 0;
    vrt_producer_claim(_p, &posi);
    PVO& data = _md_data[posi];
    data.recv_nano =  get_nanosec();
    data.instrId = snapshot.head.instrId;
    strncpy(data.code, snapshot.index.SecurityID, sizeof(snapshot.index.SecurityID));
    data.price = snapshot.index.OpenIdx;
    data.pre_close = snapshot.index.PrevCloseIdx;
    data.update_time = snapshot.head.updateTime;
    data.vol = snapshot.index.TotalVolumeTraded;
    data.last_price = snapshot.index.LastIdx;      
    data.type = TYPE_INDEX;
   
    vrt_producer_publish(_p);

    fprintf(stdout, "index,szCode=>%s,nTime=>%d,openidx=%d,idx=%d\n",data.code,data.update_time, data.price, data.last_price);
}


/**
 * 进行消息处理的回调函�?
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息�?
 * @param   pMsgBody        消息体数�?
 * @param   pCallbackParams 外部传入的参�?
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
MdsApiSample_HandleMsg(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    
    MdsMktRspMsgBodyT   *pRspMsg = (MdsMktRspMsgBodyT *) pMsgBody;
    /*
     * 根据消息类型对行情消息进行处�?
     */
    switch (pMsgHead->msgId) {
    case MDS_MSGTYPE_L2_TRADE:
        /* 处理Level2逐笔成交消息 */
        if (pRspMsg->mktDataSnapshot.head.exchId == MDS_EXCH_SZSE) {
            publish_trade(pRspMsg->trade);
        }
        break;

    case MDS_MSGTYPE_L2_ORDER:
        /* 处理Level2逐笔委托消息 */
        publish_order(pRspMsg->order);
        break;

    case MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT:
        /* 处理Level2快照行情消息 */
        publish_snapshot(pRspMsg->mktDataSnapshot);
        break;
    case MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH:
        /* Level1 stock data */
        if (pRspMsg->mktDataSnapshot.head.exchId == MDS_EXCH_SSE) {
            publish_snapshot_l1(pRspMsg->mktDataSnapshot);
        }
        break;
    case MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH:
        /* 处理Level1快照行情消息 */
        publish_index(pRspMsg->mktDataSnapshot);
        break;

    case MDS_MSGTYPE_MARKET_DATA_REQUEST:
        /* 处理行情订阅请求的应答消�? */
        if (pMsgHead->status == 0) {
            printf("... 行情订阅请求应答, 行情订阅成功!\n");
        } else {
            printf("... ERROR 行情订阅请求应答, 行情订阅失败! errCode[%02hhu%02hhu]\n",
                    pMsgHead->status, pMsgHead->detailStatus);
        }
        break;
    }
    return 0;
}



void start_md(Config& config){
    init_shm_queue(config);
    /* 配置文件 */
    static const char   THE_CONFIG_FILE_NAME[] = "./mds_client.conf";
    /* 尝试等待行情消息到达的超时时�? (毫秒) */
    static const int32  THE_TIMEOUT_MS = 1000;

    MdsApiClientEnvT    cliEnv = {NULLOBJ_MDSAPI_CLIENT_ENV};


    /* 初始化客户端环境 (配置文件参见: mds_client_sample.conf) */
    if (! MdsApi_InitAllByConvention(&cliEnv, THE_CONFIG_FILE_NAME)) {
        return ;
    }
    
    sleep(2);
    
    const string& routeKey = config.routeKey();
    if (routeKey.length() > 0) {
        if (! MdsApiSample_ResubscribeByCodePostfix(&cliEnv.tcpChannel,
                routeKey.c_str(), MDS_EXCH_SZSE)) {
            fprintf(stderr, "ERROR MdsApiSample_ResubscribeByCodePostfix...\n");
            //goto ON_ERROR;
        }
    }
    
    sleep(2);
    
    string routeKeySH = config.routeKeySH();
    if (routeKeySH.length() > 0) {
        if (! MdsApiSample_ResubscribeByCodePostfix(&cliEnv.tcpChannel,
                routeKeySH.c_str(), MDS_EXCH_SSE)) {
            fprintf(stderr, "ERROR MdsApiSample_ResubscribeByCodePostfix...\n");
            goto ON_ERROR;
        }
    }
    

    
    while (1) {
        /* 等待行情消息到达, 并通过回调函数对消息进行处�? */
        int ret = MdsApi_WaitOnMsg(&cliEnv.tcpChannel, THE_TIMEOUT_MS,
                MdsApiSample_HandleMsg, NULL);
        
        
        if (unlikely(ret < 0)) {
            if (likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 执行超时检�? (检查会话是否已超时) */
                continue;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                /* 连接已断开 */
            }
            goto ON_ERROR;
        }
    }

    MdsApi_LogoutAll(&cliEnv, TRUE);
    return ;

ON_ERROR:
    fprintf(stderr, "ERROR MD publisher disconnected...\n");
    MdsApi_DestoryAll(&cliEnv);
    return ;
}
