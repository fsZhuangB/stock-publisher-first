#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iconv.h>

#include    <mds_api.h>
#include    <mds_api/parser/mds_protocol_parser.h>
#include    <mds_api/parser/json_parser/mds_json_parser.h>
#include    <sutil/logger/spk_log.h>

using namespace std;
#define CACHE_SIZE 1500000
const string FILE_DIR = "/home/data/stockdata/";
struct StockData
{
	string market;
	string tradingDay;
	string code;
	string type;
	string dataStr;
};

template <class T, int N>
class BoundedBuffer {
private:
    T buffer[N];
    unsigned int fill, use;
    int itemCount;
    pthread_mutex_t monitor;
    //pthread_cond_t empty;
    pthread_cond_t full;
public:

    BoundedBuffer() : use(0), fill(0), itemCount(0) {

    }

    void produce(T& item) {
        pthread_mutex_lock(&monitor);
        while (itemCount == N) {
            pthread_cond_wait(&full, &monitor);
        }
        buffer[fill] = item;
        fill = (fill + 1) % N;
        itemCount++;
        /*
        if (itemCount == 1) {
            pthread_cond_signal(&empty);
        }*/
        pthread_mutex_unlock(&monitor);
    }

    bool consume(T* item) {
        bool is_consumed = false;
        pthread_mutex_lock(&monitor);
        /*
        while (itemCount == 0)
            pthread_cond_wait(&empty, &monitor);
         */
        if (itemCount != 0) {
            is_consumed = true;
            (*item) = buffer[use];
            use = (use + 1) % N;
            itemCount--;
            if (itemCount == N - 1) {
                pthread_cond_signal(&full);
            }
        }
        pthread_mutex_unlock(&monitor);
        return is_consumed;
    }
};

BoundedBuffer<StockData, CACHE_SIZE> buffer;

StockData tmp;
/**
 * 通过证券代码列表, 重新订阅行情数据 (根据代码前缀区分所属市场)
 *
 * @param   pTcpChannel         会话信息
 * @param   pCodeListString     证券代码列表字符串 (以空格或逗号/分号/竖线分割的字符串)
 * @return  TRUE 成功; FALSE 失败
 */
static BOOL
MdsApiSample_ResubscribeByCodePrefix(MdsApiSessionInfoT *pTcpChannel,
        const char *pCodeListString) {
    /* 上海证券代码前缀 */
    static const char       SSE_CODE_PREFIXES[] = \
            "20, "                          /* 债券 (回购) */   \
            "5, "                           /* 基金 */    \
            "6, "                            /* A股 */    \
            "000";                          /* 指数 */ 

    /* 深圳证券代码前缀 */
    static const char       SZSE_CODE_PREFIXES[] = \
            "00, "                          /* 股票 */    \
            "15, 16, 17, 18, "              /* 基金 */    \
            "30 "                           /* 创业板 */    \
            "39";                          /* 指数 */ 

    return MdsApi_SubscribeByStringAndPrefixes(pTcpChannel,
            pCodeListString, (char *) NULL,
            SSE_CODE_PREFIXES, SZSE_CODE_PREFIXES,
            MDS_SECURITY_TYPE_STOCK, MDS_SUB_MODE_SET,
            MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
                    | MDS_SUB_DATA_TYPE_L2_TRADE
                    | MDS_SUB_DATA_TYPE_L2_ORDER);
}


void publish_trade(MdsL2TradeT& trade) {
    timespec marketTime;
    clock_gettime(CLOCK_REALTIME, &marketTime);

    tmp.code = trade.SecurityID;
    tmp.type = "TRANSACTION";
    stringstream s;
    s << trade.tradeDate;
    tmp.tradingDay = s.str();
    tmp.market = trade.exchId == MDS_EXCH_SSE ? "SH" : "SZ";
    tmp.code = tmp.code + "." + tmp.market;
    char trade_type = '0';
    if  (trade.BidApplSeqNum == 0 || trade.OfferApplSeqNum == 0) {
        trade_type = 'C';
    }
    stringstream ss;
    ss << (1000000000 * marketTime.tv_sec + marketTime.tv_nsec) << "," << tmp.code << "," << trade.SecurityID << "," << tmp.tradingDay << "," << trade.TransactTime << ",";
    ss << trade.ApplSeqNum << "," << trade.TradePrice << "," << trade.TradeQty << "," << trade.TradeMoney << "," << trade.TradeBSFlag << "," << 0 << "," << trade_type << "," << trade.OfferApplSeqNum << "," << trade.BidApplSeqNum;
    tmp.dataStr = ss.str();
    buffer.produce(tmp);
}

void publish_order(MdsL2OrderT& order)
{
    timespec marketTime;
    clock_gettime(CLOCK_REALTIME, &marketTime);
    tmp.code = order.SecurityID;
    tmp.type = "ORDER";
    stringstream s;
    s << order.tradeDate;
    tmp.tradingDay = s.str();
    tmp.market = order.exchId == MDS_EXCH_SSE ? "SH" : "SZ";
    tmp.code = tmp.code + "." + tmp.market;
    char order_type = order.OrderType == '2' ? '0' : order.OrderType;
    char order_direction = 'N';
    if(order.Side == '1') {
        order_direction = 'B';
    } else if(order.Side == '2') {
        order_direction = 'S';
    }
    stringstream ss;
    ss << (1000000000 * marketTime.tv_sec + marketTime.tv_nsec) << "," << tmp.code << "," << order.SecurityID<< "," << tmp.tradingDay << "," << order.TransactTime << ",";
    ss << order.ApplSeqNum << "," << order.Price << "," << order.OrderQty << "," << order_type << "," << order_direction;
    tmp.dataStr = ss.str();
    buffer.produce(tmp);
}

void publish_snapshot_l1(MdsMktDataSnapshotT& snapshot) {  
    timespec marketTime;
    clock_gettime(CLOCK_REALTIME, &marketTime);

    const MdsStockSnapshotBodyT& l1Data = snapshot.stock;
    tmp.code = l1Data.SecurityID;
    tmp.type = "SNAPSHOT_L1";
    stringstream s;
    s << snapshot.head.tradeDate;
    tmp.tradingDay = s.str();
    tmp.market = snapshot.head.exchId == MDS_EXCH_SSE ? "SH" : "SZ";
    tmp.code = tmp.code + "." + tmp.market;
    stringstream ss;
    ss << (1000000000 * marketTime.tv_sec + marketTime.tv_nsec) << "," << tmp.code << "," << l1Data.SecurityID << "," << tmp.tradingDay << "," << tmp.tradingDay << "," << snapshot.head.updateTime << "," << '0' << ",";
    ss << l1Data.PrevClosePx << "," << l1Data.OpenPx << "," << l1Data.HighPx << "," << l1Data.LowPx << ",";

    const int level_count = 10;
    for(int i = level_count - 1; i >= 0; i--) {
        if (i > 4) {
            ss << 0 << "," << 0 << ",";
        } else {
            ss << l1Data.OfferLevels[i].Price << "," << l1Data.OfferLevels[i].OrderQty << ",";
        }
        
    }
    ss << l1Data.TradePx << ",";
    for (int i = 0; i < level_count; i++) {
        if (i > 4) {
            ss << 0 << "," << 0 << ",";
        } else {
            ss << l1Data.BidLevels[i].Price << "," << l1Data.BidLevels[i].OrderQty << ",";
        }
    }
            
    ss << l1Data.NumTrades << "," << l1Data.TotalVolumeTraded << "," << l1Data.TotalValueTraded << "," << 0 << "," << 0 << ",";
    ss  << 0 << "," << 0 << "," << l1Data.IOPV << ",";
    ss << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0;
    tmp.dataStr = ss.str();
    buffer.produce(tmp);
}

void publish_snapshot_l2(MdsMktDataSnapshotT& snapshot) {  
    timespec marketTime;
    clock_gettime(CLOCK_REALTIME, &marketTime);

    const MdsL2StockSnapshotBodyT& l2Data = snapshot.l2Stock;

    tmp.code = l2Data.SecurityID;
    tmp.type = "SNAPSHOT";
    stringstream s;
    s << snapshot.head.tradeDate;
    tmp.tradingDay = s.str();
    tmp.market = snapshot.head.exchId == MDS_EXCH_SSE ? "SH" : "SZ";
    tmp.code = tmp.code + "." + tmp.market;
    stringstream ss;
    ss << (1000000000 * marketTime.tv_sec + marketTime.tv_nsec) << "," << tmp.code << "," << l2Data.SecurityID<< "," << tmp.tradingDay << "," << tmp.tradingDay << "," << snapshot.head.updateTime << "," << '0' << ",";
    ss << l2Data.PrevClosePx << "," << l2Data.OpenPx << "," << l2Data.HighPx << "," << l2Data.LowPx << ",";

    const int level_count = 10;
    for(int i = level_count - 1; i >= 0; i--) {
        ss << l2Data.OfferLevels[i].Price << "," << l2Data.OfferLevels[i].OrderQty << ",";
    }
    ss << l2Data.TradePx << ",";
    for (int i = 0; i < level_count; i++) {
        ss << l2Data.BidLevels[i].Price << "," << l2Data.BidLevels[i].OrderQty << ",";
    }
            
    ss << l2Data.NumTrades << "," << l2Data.TotalVolumeTraded << "," << l2Data.TotalValueTraded << "," << l2Data.TotalBidQty << "," << l2Data.TotalOfferQty << ",";
    ss  << l2Data.WeightedAvgBidPx << "," << l2Data.WeightedAvgOfferPx << "," << l2Data.IOPV << ",";
    ss << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0;
    tmp.dataStr = ss.str();
    buffer.produce(tmp);
}

void publish_index(MdsMktDataSnapshotT& snapshot) {
    timespec marketTime;
    clock_gettime(CLOCK_REALTIME, &marketTime);
    const MdsIndexSnapshotBodyT& indexData = snapshot.index;

    tmp.code = indexData.SecurityID;
    tmp.type = "INDEX";
    stringstream s;
    s << snapshot.head.tradeDate;
    tmp.tradingDay = s.str();
    tmp.market = snapshot.head.exchId == MDS_EXCH_SSE ? "SH" : "SZ";
    tmp.code = tmp.code + "." + tmp.market;
    stringstream ss;
    ss << (1000000000 * marketTime.tv_sec + marketTime.tv_nsec) << "," << tmp.code << "," << indexData.SecurityID << "," << tmp.tradingDay << "," << tmp.tradingDay << "," << snapshot.head.updateTime << ",";
    ss << indexData.OpenIdx << "," << indexData.HighIdx << "," << indexData.LowIdx << "," << indexData.LastIdx << "," << indexData.TotalVolumeTraded << "," << indexData.TotalValueTraded << "," << indexData.PrevCloseIdx;
    tmp.dataStr = ss.str();
    buffer.produce(tmp);
}


void publish_orderqueue(MdsMktDataSnapshotT& snapshot) {
    timespec marketTime;
    clock_gettime(CLOCK_REALTIME, &marketTime);

    const MdsL2BestOrdersSnapshotBodyT orderQueue = snapshot.l2BestOrders;
    tmp.code = orderQueue.SecurityID;
    tmp.type = "ORDERQUEUE";
    stringstream s;
    s << snapshot.head.tradeDate;
    tmp.tradingDay = s.str();
    tmp.market = snapshot.head.exchId == MDS_EXCH_SSE ? "SH" : "SZ";
    tmp.code = tmp.code + "." + tmp.market;
    stringstream ss;
    //Best sell price order queue 
    ss << (1000000000 * marketTime.tv_sec + marketTime.tv_nsec) << "," << tmp.code << "," << orderQueue.SecurityID << "," << tmp.tradingDay << "," << snapshot.head.updateTime << ",";
    ss << 65 << "," << orderQueue.BestOfferPrice << "," << (int)orderQueue.NoOfferOrders << "," << (int)orderQueue.NoOfferOrders << ",";
    for (int i = 0; i < orderQueue.NoOfferOrders -1; i++ ) {
        ss << orderQueue.OfferOrderQty[i] << " ";
    }
    ss << orderQueue.OfferOrderQty[orderQueue.NoOfferOrders -1];
    tmp.dataStr = ss.str();
    buffer.produce(tmp);
    
    ss.str("");
    //Best buy price order queue
    ss << (1000000000 * marketTime.tv_sec + marketTime.tv_nsec) << "," << tmp.code << "," << orderQueue.SecurityID << "," << tmp.tradingDay << "," << snapshot.head.updateTime << ",";
    ss << 66 << "," << orderQueue.BestBidPrice << "," << (int)orderQueue.NoBidOrders << "," << (int)orderQueue.NoBidOrders << ",";
    for (int i = 0; i < orderQueue.NoBidOrders -1; i++ ) {
        ss << orderQueue.BidOrderQty[i] << " ";
    }
    ss << orderQueue.BidOrderQty[orderQueue.NoBidOrders -1];
    tmp.dataStr = ss.str();
    buffer.produce(tmp);

}
/**
 * 进行消息处理的回调函数
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
MdsApiSample_HandleMsg(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    
    MdsMktRspMsgBodyT   *pRspMsg = (MdsMktRspMsgBodyT *) pMsgBody;
    /*
     * 根据消息类型对行情消息进行处理
     */
    switch (pMsgHead->msgId) {
    case MDS_MSGTYPE_L2_TRADE:
        /* 处理Level2逐笔成交消息 */
        publish_trade(pRspMsg->trade);
        break;

    case MDS_MSGTYPE_L2_ORDER:
        /* 处理Level2逐笔委托消息 */
        publish_order(pRspMsg->order);
        break;
    //case MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE:
    case MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT:
        /* 处理Level2快照行情消息 */
        publish_snapshot_l2(pRspMsg->mktDataSnapshot);
        break;

    case MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH:
        /* 处理Level1 index快照行情消息 */
        publish_index(pRspMsg->mktDataSnapshot);
        break;
    case MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH:
    case MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH:
        /* Level1 stock data */
        if (pRspMsg->mktDataSnapshot.head.exchId == MDS_EXCH_SSE) {
            publish_snapshot_l1(pRspMsg->mktDataSnapshot);
        }
        break;
    case MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT:
        publish_orderqueue(pRspMsg->mktDataSnapshot);
        break;
    case MDS_MSGTYPE_MARKET_DATA_REQUEST:
        /* 处理行情订阅请求的应答消息 */
        if (pMsgHead->status == 0) {
            printf("... 行情订阅请求应答, 行情订阅成功!\n");
        } else {
            printf("... 行情订阅请求应答, 行情订阅失败! errCode[%02hhu%02hhu]\n",
                    pMsgHead->status, pMsgHead->detailStatus);
        }
        break;
    }
    return 0;
}

void *threadfn(void *arg) {
    int trading_day = *(int *)arg;
    map<string, vector<string> > filemap;
    int consume_count = 0;
    StockData data;
    timespec marketTime;
    clock_gettime(CLOCK_REALTIME, &marketTime);
    long lastSaveTime = marketTime.tv_sec;
    while (true) {
        if (buffer.consume(&data)) {
            string filepath = FILE_DIR + data.market + "/" + data.code + "/" + data.code + "_" + data.tradingDay + "_" + data.type + ".csv";
            filemap[filepath].push_back(data.dataStr);
            consume_count++;
            //先创建对应的文件夹，但是不立刻保存数据
            string dirfile = FILE_DIR + data.market + "/" + data.code;
            fstream _file;
            _file.open(dirfile.c_str(), ios::in);
            if (!_file) {
                cout << "create dir base on=> " << data.dataStr << endl;
                if (mkdir(dirfile.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IXOTH | S_IROTH) != 0) {
                    std::cout << "Failed to make dir..." << dirfile << endl;
                    exit(-1);
                }
            }
            _file.close();
        }
        
        timespec curTime;
        clock_gettime(CLOCK_REALTIME, &curTime);
        //存入文件
        if ((consume_count >= 0.6*CACHE_SIZE) || (curTime.tv_sec - lastSaveTime > 60)) {
            cout << "start save file,time=>" << curTime.tv_sec <<  ",consume_count=>" << consume_count << endl;
            for (map<string, vector<string> >::iterator it = filemap.begin(); it != filemap.end(); it++) {
                ofstream ofs;
                ofstream* file = &ofs;
                ifstream infile(it->first.c_str());
                if (!infile) {
                    file->open(it->first.c_str(), ios::app);
                    if (it->first.find("SNAPSHOT_L1") != string::npos) {
                        (*file) << "systime,szWindCode,szCode,nActionDay,nTradingDay,nTime,nStatus,nPreClose,nOpen,nHigh,nLow,ap10,av10,ap9,av9,ap8,av8,ap7,av7,ap6,av6,ap5,av5,ap4,av4,ap3,av3,ap2,av2,ap1,av1,nMatch,bp1,bv1,bp2,bv2,bp3,bv3,bp4,bv4,bp5,bv5,bp6,bv6,bp7,bv7,bp8,bv8,bp9,bv9,bp10,bv10,nNumTrades,iVolume,iTurnover,nTotalBidVol,nTotalAskVol,nWeightedAvgBidPrice,nWeightedAvgAskPrice,nIOPV,nYieldToMaturity,nHighLimited,nLowLimited,chPrefix,nSyl1,nSyl2,nSD2" << endl;
                    } else 
                    if (it->first.find("SNAPSHOT") != string::npos) {
                        (*file) << "systime,szWindCode,szCode,nActionDay,nTradingDay,nTime,nStatus,nPreClose,nOpen,nHigh,nLow,ap10,av10,ap9,av9,ap8,av8,ap7,av7,ap6,av6,ap5,av5,ap4,av4,ap3,av3,ap2,av2,ap1,av1,nMatch,bp1,bv1,bp2,bv2,bp3,bv3,bp4,bv4,bp5,bv5,bp6,bv6,bp7,bv7,bp8,bv8,bp9,bv9,bp10,bv10,nNumTrades,iVolume,iTurnover,nTotalBidVol,nTotalAskVol,nWeightedAvgBidPrice,nWeightedAvgAskPrice,nIOPV,nYieldToMaturity,nHighLimited,nLowLimited,chPrefix,nSyl1,nSyl2,nSD2" << endl;
                    } else
                        if (it->first.find("INDEX") != string::npos) {
                        (*file) << "systime,szWindCode,szCode,nActionDay,nTradingDay,nTime,nOpenIndex,nHighIndex,nLowIndex,nLastIndex,iTotalVolume,iTurnover,nPreCloseIndex" << endl;
                    } else
                        if (it->first.find("TRANSACTION") != string::npos) {
                        (*file) << "systime,szWindCode,szCode,nActionDay,nTime,nIndex,nPrice,nVolume,nTurnover,nBSFlag,chOrderKind,chFunctionCode,nAskOrder,nBidOrder" << endl;
                    } else
                        if (it->first.find("ORDERQUEUE") != string::npos) {
                        (*file) << "systime,szWindCode,szCode,nActionDay,nTime,nSide,nPrice,nOrders,nABItems,nVolume" << endl;
                    } else
                        if (it->first.find("ORDER") != string::npos) {
                        (*file) << "systime,szWindCode,szCode,nActionDay,nTime,nOrder,nPrice,nVolume,chOrderKind,chFunctionCode" << endl;
                    }
                    file->close();
                }
                for (vector<string>::iterator iter = it->second.begin(); iter != it->second.end(); iter++) {
                    if (!file->is_open()) {
                        file->open(it->first.c_str(), ios::app);
                    }
                    (*file) << (*iter) << endl;
                }
                file->close();
            }
            clock_gettime(CLOCK_REALTIME, &curTime);
            cout << "end save file,time=>" << curTime.tv_sec <<  ",consume_count=>" << consume_count << endl;
            if (trading_day !=0 && consume_count ==0) {
                //cout << "exit application..." << endl;
                //exit(0);
            }
            filemap.clear();
            consume_count = 0;
            lastSaveTime = curTime.tv_sec;
        }
    }

    return ((void *) 0);
}


int main(int argc, char*argv[]) {

    /* 配置文件 */
    static const char   THE_CONFIG_FILE_NAME[] = "./mds_client.conf";
    /* 尝试等待行情消息到达的超时时间 (毫秒) */
    static const int32  THE_TIMEOUT_MS = 1000;

    MdsApiClientEnvT    cliEnv = {NULLOBJ_MDSAPI_CLIENT_ENV};
    int32               ret = 0;

    /* 初始化客户端环境 (配置文件参见: mds_client_sample.conf) */
    if (! MdsApi_InitAllByConvention(&cliEnv, THE_CONFIG_FILE_NAME)) {
        return -1;
    }
    //need stock code to subscibe marketdata
    /*
    if (! MdsApiSample_ResubscribeByCodePrefix(&cliEnv.tcpChannel,
            config.routeKey().c_str())) {
        goto ON_ERROR;
    }
    */
    
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%d%m%Y",timeinfo);
    int date = atoi(buffer);
    //write data to hard disk
    pthread_t t;
    pthread_create(&t, NULL, threadfn, (void *)&date);
    while (1) {
        /* 等待行情消息到达, 并通过回调函数对消息进行处理 */
        ret = MdsApi_WaitOnMsg(&cliEnv.tcpChannel, THE_TIMEOUT_MS,
                MdsApiSample_HandleMsg, NULL);
        
        
        if (unlikely(ret < 0)) {
            if (likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 执行超时检查 (检查会话是否已超时) */
                continue;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                /* 连接已断开 */
            }
            goto ON_ERROR;
        }
    }

    MdsApi_LogoutAll(&cliEnv, TRUE);
    return 1;

ON_ERROR:
    fprintf(stderr, "ERROR MD conection disconnected...\n");
    MdsApi_DestoryAll(&cliEnv);
    return -1;
}
