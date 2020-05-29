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
#include <limits.h>
#include "wd/TDFAPI.h"
#include "wd/TDFAPIStruct.h"
#include "datatype.h"
#include "queue.h"
#include "md_publisher.h"
#include "utility.h"
#define MIN(x, y) ((x)>(y)?(y):(x))

using namespace std;

#define SHARED_QUEUE_SIZE 65536*128
static int queue_shm_fd = 0;
static int data_shm_fd = 0;
static struct vrt_queue* _q ;
static PVO* _md_data;
static struct vrt_producer* _p;
void init_shm_queue(const Config& config) {
    //ST_MD_QUEUE
    string queue_data_str = config.mdQueuePrefix();
    string queue_str = queue_data_str + "_QUEUE";
    string queue_producer = queue_data_str + "_PRODUCER";
    
    _q = vrt_queue_new (queue_str.c_str(), SHARED_QUEUE_SIZE, sizeof(PVO), &queue_shm_fd);
    _md_data = (PVO*)vrt_data_new(queue_data_str.c_str(), (_q->value_mask + 1)*sizeof(PVO), &data_shm_fd);
    _p = vrt_producer_new(queue_producer.c_str(), 1, _q, 0, true); 
}


void RecvData(THANDLE hTdf, TDF_MSG* pMsgHead);
void RecvSys(THANDLE hTdf, TDF_MSG* pSysMsg);
void DumpScreenTransaction(TDF_TRANSACTION* pTransaction, int nItems);
void DumpScreenOrder(TDF_ORDER* pOrder, int nItems);
void DumpSnapshot(TDF_MARKET_DATA* pMarket, int nItems);

#define ELEM_COUNT(arr) (sizeof(arr)/sizeof(arr[0]))
#define SAFE_STR(str) ((str)?(str):"")
#define SAFE_CHAR(ch) ((ch) ? (ch) : ' ')

int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t* inlen,char *outbuf,size_t* outlen)
{
        iconv_t cd;
        char **pin = &inbuf;
        char **pout = &outbuf;

        cd = iconv_open(to_charset,from_charset);
        if (cd==0)
                return -1;
        memset(outbuf,0,*outlen);
        if (iconv(cd,pin,(size_t*)inlen,pout,(size_t*)outlen) == -1)
                return -1;
        iconv_close(cd);
        return 0;
}

static void recover() {
    /*
    vector<PVO> orders = read_stock_order("./recover");
    vector<PVO> trades = read_stock_trade("./recover");
    orders.insert(orders.end(),trades.begin(),trades.end());
    std::sort(orders.begin(),orders.end(),less_sort);
    fprintf(stderr,"recover size=>%d\n", orders.size());
    for (vector <PVO> :: iterator iter = orders.begin(); iter != orders.end(); ++iter) {
        int posi = 0;
        vrt_producer_claim(_p, &posi);
        PVO& data = _md_data[posi];
        memcpy( &data, &(*iter), sizeof(PVO));
        vrt_producer_publish(_p);
        fprintf(stdout, "posi=>%d,time=>%lu,instrId=>%d,type=>%d,direction=>%d,seq=>%d\n", posi, data.recv_nano, data.instrId, data.type, data.direction, data.seq_num);
        //grep ,1950318, recover/*
    }
*/
}


void start_md(Config& config)
{
    init_shm_queue(config);
    recover();
    //TDF_SetEnv(TDF_ENVIRON_HEART_BEAT_INTERVAL, 10);
    //TDF_SetEnv(TDF_ENVIRON_MISSED_BEART_COUNT, 2);
    TDF_SetEnv(TDF_ENVIRON_OUT_LOG, 1);


    TDF_OPEN_SETTING settings = {0};
    strcpy(settings.szIp,   config.mdUrl().c_str());
    strcpy(settings.szPort, std::to_string(config.mdPort()).c_str());
    strcpy(settings.szUser, config.mdUserName().c_str());
    strcpy(settings.szPwd,  config.mdPassword().c_str());
    settings.nReconnectCount = 99999999;
    settings.nReconnectGap = 5;
    settings.pfnMsgHandler = RecvData; //设置数据消息回调函数
    settings.pfnSysMsgNotify = RecvSys;//设置系统消息回调函数
    settings.nProtocol = 0;
    settings.szMarkets = config.mdType().c_str();      //需要订阅的市场列表
    settings.szSubScriptions = config.routeKey().c_str();    //需要订阅的股票,为空则订阅全市场
    settings.nDate = atoi(config.authCode().c_str());//请求的日期，格式YYYYMMDD，为0则请求今天
    settings.nTime = 0;//请求的时间，格式HHMMSS，为0则请求实时行情，䶿xffffffff从头请求
    settings.nTypeFlags = DATA_TYPE_TRANSACTION | DATA_TYPE_ORDER; //请求的品种。DATA_TYPE_ALL请求所有品祍
    TDF_ERR nErr = TDF_ERR_SUCCESS;
    THANDLE hTDF = NULL;
    hTDF = TDF_Open(&settings, &nErr);
    while (hTDF == NULL){
        printf("TDF_Open return error: %d,retry...\n", nErr);
	sleep(10);
	hTDF = TDF_Open(&settings, &nErr);
    }

    

    //TDF_Close(hTDF);

}


#define GETRECORD(pBase, TYPE, nIndex) ((TYPE*)((char*)(pBase) + sizeof(TYPE)*(nIndex)))
int md_core_id = -1;
void RecvData(THANDLE hTdf, TDF_MSG* pMsgHead)
{
    if (md_core_id == -1) {
        md_core_id = 4;
        int ret = bind_core(md_core_id);
        if (0!=ret)
            LOG_ERROR("bind md spi thread(%d) core id fail:%s\n",get_self_tid(),strerror(errno));
        else
            LOG_INFO("bind md spi thread(%d) on core:%d\n",get_self_tid(),md_core_id);
    }
   if (!pMsgHead->pData)
   {
       assert(0);
       return ;
   }

   unsigned int nItemCount = pMsgHead->pAppHead->nItemCount;
   if (!nItemCount)
   {
       assert(0);
       return ;
   }

   switch(pMsgHead->nDataType)
   {

   case MSG_DATA_TRANSACTION:
       {
           DumpScreenTransaction((TDF_TRANSACTION*)pMsgHead->pData, nItemCount);
       }
       break;

   case MSG_DATA_ORDER:
       {
           DumpScreenOrder((TDF_ORDER*)pMsgHead->pData, nItemCount);
       }
       break;
    case MSG_DATA_MARKET:
    {
        DumpSnapshot((TDF_MARKET_DATA*) pMsgHead->pData, nItemCount);
    }
    break;
   default:
       break;
   }
}

void RecvSys(THANDLE hTdf, TDF_MSG* pSysMsg)
{
    if (!pSysMsg ||! hTdf)
    {
        return;
    }

    switch (pSysMsg->nDataType)
    {
    case MSG_SYS_DISCONNECT_NETWORK:
        {
            printf("网络断开\n");
        }
        break;
    case MSG_SYS_CONNECT_RESULT:
        {
            TDF_CONNECT_RESULT* pConnResult = (TDF_CONNECT_RESULT*)pSysMsg->pData;
            if (pConnResult && pConnResult->nConnResult)
            {
                printf("连接 %s:%s user:%s, password:%s 成功!\n", pConnResult->szIp, pConnResult->szPort, pConnResult->szUser, pConnResult->szPwd);
            }
            else
            {
                printf("连接 %s:%s user:%s, password:%s 失败!\n", pConnResult->szIp, pConnResult->szPort, pConnResult->szUser, pConnResult->szPwd);
            }
        }
        break;
    case MSG_SYS_LOGIN_RESULT:
        {
            TDF_LOGIN_RESULT* pLoginResult = (TDF_LOGIN_RESULT*)pSysMsg->pData;
            
                //convert gb2312 to utf-8
                char utf_info[128];
                size_t len2 =128;
                size_t len1 = strlen(pLoginResult->szInfo);
                code_convert("gb2312","utf-8",pLoginResult->szInfo,&len1,utf_info,&len2);
            
            if (pLoginResult && pLoginResult->nLoginResult)
            {
                printf("登陆成功！info:%s, nMarkets:%d\n", utf_info , pLoginResult->nMarkets);
                for (int i=0; i<pLoginResult->nMarkets; i++)
                {
                    printf("market:%s, dyn_date:%d\n", pLoginResult->szMarket[i], pLoginResult->nDynDate[i]);
                }
            }
            else
            {
                printf("登陆失败，原因：%s\n", utf_info);
            }
        }
        break;
    case MSG_SYS_CODETABLE_RESULT:
        {
            TDF_CODE_RESULT* pCodeResult = (TDF_CODE_RESULT*)pSysMsg->pData;
            if (pCodeResult )
            {
                printf("接收到代码表：info:%s, 市场个数:%d\n", pCodeResult->szInfo, pCodeResult->nMarkets);
                for (int i=0; i<pCodeResult->nMarkets; i++)
                {
                    printf("市场:%s, 代码表项数:%d, 代码表日期:%d\n", pCodeResult->szMarket[i], pCodeResult->nCodeCount[i], pCodeResult->nCodeDate[i]);
                    //获取代码表
                    TDF_CODE* pCodeTable;
                    unsigned int nItems;
                    TDF_GetCodeTable(hTdf, pCodeResult->szMarket[i], &pCodeTable, &nItems);
                    for (int i=0; i<nItems; i++)
                    {
                        TDF_CODE& code = pCodeTable[i];
                        //convert gbk to utf-8
                        char utf_name[128];
                        size_t len2 =128;
                        size_t len1 = strlen(code.szCNName);
                        code_convert("gbk","utf-8",code.szCNName,&len1,utf_name,&len2);
                       // printf("windcode:%s, code:%s, market:%s, name:%s, nType:0x%x\n",code.szWindCode, code.szCode, code.szMarket, utf_name, code.nType);

                    }
                    TDF_FreeArr(pCodeTable);                   
                }
            }
        }
        break;
    case MSG_SYS_QUOTATIONDATE_CHANGE:
        {
            TDF_QUOTATIONDATE_CHANGE* pChange = (TDF_QUOTATIONDATE_CHANGE*)pSysMsg->pData;
            if (pChange)
            {
                printf("收到行情日期变更通知，即将自动重连！交易所：%s, 原日期:%d, 新日期：%d\n", pChange->szMarket, pChange->nOldDate, pChange->nNewDate);
            }
        }
        break;
    case MSG_SYS_MARKET_CLOSE:
        {
            TDF_MARKET_CLOSE* pCloseInfo = (TDF_MARKET_CLOSE*)pSysMsg->pData;
            if (pCloseInfo)
            {
                printf("闭市消息:market:%s, time:%d, info:%s\n", pCloseInfo->szMarket, pCloseInfo->nTime, pCloseInfo->chInfo);
            }
        }
        break;
    case MSG_SYS_HEART_BEAT:
        {
            printf("收到心跳消息\n");
        }
        break;
    default:
        assert(0);
        break;
    }
}


void DumpScreenTransaction(TDF_TRANSACTION* pTransaction, int nItems)
{
    auto recv_nano = get_nanosec();
    for (int i=0; i<nItems; i++)
    {
        const TDF_TRANSACTION& transaction = pTransaction[i];
        if  (transaction.nBidOrder == 0) {//卖撤单
            continue;
        }
        
        int posi = 0;
        vrt_producer_claim(_p, &posi);
        PVO& data = _md_data[posi];
        data.recv_nano = recv_nano;
        data.instrId = atoi(transaction.szCode);
        data.price = transaction.nPrice;
        data.vol = transaction.nVolume;
        data.type = TYPE_TRADE;
        data.seq_num = transaction.nBidOrder;
        if (transaction.nAskOrder == 0) {//买撤单
            data.vol = INT_MAX;
        }
        
        vrt_producer_publish(_p);
        
        auto publish_nano = get_nanosec();
        fprintf(stdout, "trade,szCode=>%s,nTime=>%d,nPrice=>%d,nVolume=>%d,nBidOrder=>%d,nAskOrder=>%d,recv_nano=>%lu,publish_nano=>%lu,elapsed_time=>%lu\n", 
                transaction.szCode,transaction.nTime,data.price,data.vol,data.seq_num,transaction.nAskOrder, recv_nano, publish_nano, publish_nano - recv_nano);
    }
}

void DumpScreenOrder(TDF_ORDER* pOrder, int nItems)
{
    auto recv_nano = get_nanosec();
    for (int i=0; i<nItems; i++)
    {
        const TDF_ORDER& order = pOrder[i];
    
        int posi = 0;
        vrt_producer_claim(_p, &posi);
        PVO& data = _md_data[posi];
        data.recv_nano = recv_nano;
        data.instrId = atoi(order.szCode);
        strncpy(data.code, order.szCode, sizeof(order.szCode));
        data.price = order.nPrice;
        data.vol = order.nVolume;
        data.type = TYPE_ORDER;
        data.seq_num = order.nOrder;
        if (order.chOrderKind == '1' || order.chOrderKind == 'U') {//市价或本方最优价
            data.price = INT_MAX;
        }
        if(order.chFunctionCode == 'B') {
            data.direction = DIRECTION_BUY;
        } else if(order.chFunctionCode == 'S') {
            data.direction = DIRECTION_SELL;
        }

        vrt_producer_publish(_p);
        
        auto publish_nano = get_nanosec();
        fprintf(stdout, "order,szCode=>%s,nTime=>%d,nPrice=>%d,nVolume=>%d,nOrder=>%d,recv_nano=>%lu,publish_nano=>%lu,elapsed_time=>%lu\n",
                order.szCode,order.nTime,data.price,data.vol,data.seq_num, recv_nano, publish_nano, publish_nano - recv_nano);
    }
}

void DumpSnapshot(TDF_MARKET_DATA* pMarket, int nItems) {
    for (int i = 0; i < nItems; i++) {
        const TDF_MARKET_DATA& snapshot = pMarket[i];
        int posi = 0;
        vrt_producer_claim(_p, &posi);
        PVO& data = _md_data[posi];
        
        data.instrId = atoi(snapshot.szCode);
        strncpy(data.code, snapshot.szCode, sizeof(snapshot.szCode));
        data.price = snapshot.nOpen;
        data.vol = snapshot.nPreClose;
        data.type = TYPE_SNAPSHOT;
        vrt_producer_publish(_p);
    }
}







