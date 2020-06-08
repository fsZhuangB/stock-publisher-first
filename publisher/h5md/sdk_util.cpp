/** @file
* 行情Demo.SDK使用例子
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/

#include "sdk_util.h"
#include "sdk_callback.h"
#include "main_message_queue.h"
#include "main_environment.h"
#include <string.h>
#ifndef WIN32
#include <inttypes.h>
#endif

/*////////////////////////////////////////////////////////////////////////////////////////////////
	性能测试模块
////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
	收到一个正确代码
*/
void MyCapabilityTest::PushOkItem(uint64 time, const char *code, const char *market, uint64 open_px, uint64 last_px)
{
	//性能测试，将获取的值存入队列。
	MyCapabilityItem item(time, code, market, open_px, last_px);
	m_listGets.push_back(item);
}

/*
	收到一个正确命令
*/
void MyCapabilityTest::PushOkPackage(uint64 time, int callback_type)
{
    if(g_pMyCapabilityTest == NULL)
    {
        printf("Error: Bad code logic, please check your codes.");
        return;
    }

	int ten_percent = (m_iNumPackage / 10) > 0 ? (m_iNumPackage / 10) : 1;
	if(m_iNumPackageOK % ten_percent == 0)
	{
		printf(".");//1/10才显示。
	}

	m_iNumPackageOK ++;
	if(g_pMyCapabilityTest->GetAllPackage())
	{
		MyEnvironment::PostMainMessage(Command_SdkCallback, callback_type);
	}
}

/*
	收到一个错误命令
*/
void MyCapabilityTest::PushErrPackage(uint64 time, int callback_type)
{

}

/*
	getTickCount
*/
uint64 getTickCount64(void)
{
	uint64 currentTime;
#ifdef WIN32
	currentTime = GetTickCount64();
#else
	struct timeval current;
	gettimeofday(&current, NULL);
	currentTime = current.tv_sec * 1000 + current.tv_usec/1000;
#endif
	return currentTime;
}

/*
	行情返回的中文字符，是utf-8的。转成gbk,否则乱码。
	返回的szGbk需要delete.
*/
#ifdef WIN32
int UTF82GBK(const char *szUtf8, string& szGbk)  
{  
    if(szUtf8 == NULL)
    {
        printf("Error : Shouldn't run in, please check your codes.");
        return -1;
    }

	int n = MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, NULL, 0);  
	WCHAR * wszGBK = new WCHAR[sizeof(WCHAR) * n];  
	memset(wszGBK, 0, sizeof(WCHAR) * n);  
	MultiByteToWideChar(CP_UTF8, 0,szUtf8,-1, wszGBK, n);  

	n = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
	char *pTmp = new char[n + 1];
	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, pTmp, n, NULL, NULL);  

	szGbk = pTmp;

	delete[]wszGBK;
	delete []pTmp;
	return 0;  
}
#else
int UTF82GBK(const char *szUtf8, string &szGbk)
{
	//Linux,直接用utf8去显示。其实，不需要转换，拷贝什么的。
	//为了跟windows版兼容，才这里拷贝。
	szGbk = szUtf8;
	return 0;
}
#endif
/*
	MyCapabilityItem constructor
*/
MyCapabilityItem::MyCapabilityItem(uint64 t, const char *code, const char *m, uint64 open, uint64 last)
	: m_time(t), m_strProdCode(code), m_strMarket(m), m_u64OpenPx(open), m_u64LastPx(last)
{
}
/*
	返回600570.SS
*/
string MyCapabilityItem::GetFullName(string& ret)
{
	ret = m_strProdCode;
	ret += m_strMarket;
	return ret;
}

/*
	HqSdkUtil constructor
*/
HqSdkUtil::HqSdkUtil()
{
	m_bLogin = false;
	m_pSession = NULL;
	m_pSessionOptions = NULL;
}

/*
	sdk 初始化
*/
bool HqSdkUtil::sdk_init(void)
{
	//////////////////////////////////////////////////////////////////////////
	// 设置环境变量
	//////////////////////////////////////////////////////////////////////////
	//设置SDK日志路径
	SetH5DataPath("h5data");
	//设置SDK日志路径
	SetH5LogPath("H5LOG");
	//设置日志级别配置路径
	SetSdkParamPath("SdkParamPath.json");

	//////////////////////////////////////////////////////////////////////////
	// 会话创建
	//////////////////////////////////////////////////////////////////////////
	m_pSessionOptions = CreateSessionOptions();
    if(m_pSessionOptions == NULL)
    {
        printf("Failed to create session option.");
        return false;
    }

	// 设置会话选项1
	m_pSessionOptions->SetHeartbeatTimeout(3);

	//设置两组ip和端口
	m_pSessionOptions->SetServerIp(m_strIp1.c_str());
	m_pSessionOptions->SetServerPort(m_iPort1);

	m_pSessionOptions->SetServerIp(m_strIp2.c_str(),1);
	m_pSessionOptions->SetServerPort(m_iPort2,1);

	// 创建会话
	m_pSession = CreateSession(m_pSessionOptions);
    if(m_pSession == NULL)
    {
        printf("Failed to create session.");
        return false;
    }

	m_pSession->SetAppInfo(m_strAppKey.c_str(), m_strAppSecret.c_str());

	// 开始为所有会话设置回调
	StartSetCallback();
	//两个会话可使用同一个回调类，也可以使用不同的回调类
	m_pSession->SetCallback(&m_h5SdkCallbackImpl);

	//首次启动时，不会自动连接，需要后面手工连接[除非特别需要，不需要调用此函数]
	//SetInitAutoConnectFlag(false);

	//设置代理
	//SetProxyOptions(SDKHTTPPROXY, "10.26.210.42", 808, "test", "test");
	return true;
}
/*
	sdk 关闭
*/
void HqSdkUtil::sdk_close(void)
{
	my_log("\t关闭sdk\n");
	StopAllSessions();

	if(m_pSessionOptions)
	{
		m_pSessionOptions->Release();
		m_pSessionOptions = NULL;
	}
	
    if(m_pSession)
	{
		m_pSession->Release();
		m_pSession = NULL;
	}
}
/*
	解析。行情快照。某只代码的信息。
*/
void HqSdkUtil::parse_snapshot_record(IRecord * record, uint64 time)
{
    if(record == NULL)
    {
        printf("Error : Shouldn't run in, please check your codes.");
        return ;
    }

	const char *hq_type_name = record->GetItem(H5SDK_TAG_PROD_NAME)->GetString();
	
	string gbkName; 
	UTF82GBK(hq_type_name, gbkName); 

	const char *hq_type_code = record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();

	const char *hsCode = record->GetItem(H5SDK_TAG_PROD_CODE)->GetString();

	// 获取时间
	uint32 hsTimeStamp = record->GetItem(H5SDK_TAG_DATA_TIMESTAMP)->GetInt32();
	uint64 open_px = record->GetItem(H5SDK_TAG_OPEN_PX)->GetInt64();                   // 今日开盘价
	uint64 close_px = record->GetItem(H5SDK_TAG_CLOSE_PX)->GetInt64();                   // 今日收盘价
	uint64 high_px = record->GetItem(H5SDK_TAG_HIGH_PX)->GetInt64();                   // 今日收盘价
	uint64 last_px = record->GetItem(H5SDK_TAG_LAST_PX)->GetInt64();                   // 最新价

//	double px_change = (double)(int64)record->GetItem(H5SDK_TAG_PX_CHANGE)->GetInt64(); //涨跌额
//	if(px_change <= 0)
//		my_log("  %f  ", px_change);
	int64 avg_px = record->GetItem(H5SDK_TAG_AVG_PX)->GetInt64(); //涨跌额
//	my_log("  %d  ", avg_px);

	if(strcmp(hsCode, "600570") == 0)//强制打印.
	{//不用my_log.强制打印
		printf("\n\t(code=%s.%s open_px=%llu close_px=%llu last_px=%llu)\n", hsCode, hq_type_code, open_px, close_px, last_px);
	}

	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Lock();
	if(g_pMyCapabilityTest)
	{//性能测试，将获取的值存入队列。
		g_pMyCapabilityTest->PushOkItem(time, hsCode, hq_type_code, open_px, last_px);
	}
	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Unlock();

	// 盘口数据
	IGroup * pBidGroup = record->GetGroup(H5SDK_TAG_BID_GRP);
	if (pBidGroup != NULL)
	{
		int layers = pBidGroup->GetRecordCount(); // 档数

		for (int i = 0; i < layers; i++)
		{
			IRecord * pBid = pBidGroup->GetRecord(i);
			if (NULL == pBid)
			{
				my_log("bid-null ");
				continue;
			}

			uint64 px = pBid->GetItem(H5SDK_TAG_ENTRUST_PX)->GetInt64();
			uint64 amount = pBid->GetItem(H5SDK_TAG_TOTAL_ENTRUST_AMOUNT)->GetInt64();
			if(strcmp(hsCode, "600570") == 0)
			{
				printf("\t\t\tbid entrust_px=%llu entrust_amount=%llu\n", px, amount);
			}

		/*	//level_2的参数
			IGroup * entrust_grp = record->GetGroup(H5SDK_TAG_ENTRUST_GRP);			
			if (entrust_grp != NULL)
			{
				my_log("\t\t\t\tentrust_grp有值\n");
			}
			else
			{
				my_log("\t\t\t\tentrust_grp空\n");
			}
			*/
		}
	}
	else
	{}

	IGroup *pAskGroup = record->GetGroup(H5SDK_TAG_OFFER_GRP);
	if (pAskGroup != NULL)
	{
		int layers = pAskGroup->GetRecordCount(); // 档数

		for (int i = 0; i < layers; i++)
		{
			IRecord * pAsk = pAskGroup->GetRecord(i);
			if (NULL == pAsk)
			{
				my_log("offer-null ");
				continue;
			}

			uint64 px = pAsk->GetItem(H5SDK_TAG_ENTRUST_PX)->GetInt64();
			uint64 amount = pAsk->GetItem(H5SDK_TAG_TOTAL_ENTRUST_AMOUNT)->GetInt64();

			if(strcmp(hsCode, "600570") == 0)
			{//不用my_log.强制打印
				printf("\t\t\toffer entrust_px=%llu entrust_amount=%llu\n", px, amount);
			}
		}
	}
	else
	{}
}

/*
	解析。行情快照。
*/
void HqSdkUtil::parse_snapshot(IHsCommMessage* ansMsg, uint64 time)
{
	if(ansMsg == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	IGroup *group = ansMsg->GetGroup(H5SDK_TAG_PROD_GRP);
	if(group)
	{
		// 获取H5SDK_FINANCE_MIC_GRP的记录条数
		int count = group->GetRecordCount();
		// 解析每一条记录
		for (int i = 0; i < count; i++)
		{
			IRecord *type_record = group->GetRecord(i);

			if(type_record == NULL)
			{
				my_log("prod-null ");
				continue;
			}

			parse_snapshot_record(type_record, time);
		}

		//大批量订阅，只显示一个点。
		if(count > 1)
		{
			my_log("\n\t\t%d(支)\n", count);
		}
		else
		{
			my_log(".");
		}
	}
	else
		my_log("group == null ");

	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Lock();
	if(g_pMyCapabilityTest)
	{//性能测试，将获取的值存入队列。
		g_pMyCapabilityTest->PushOkPackage(time, SdkCallback_Snapshot_Capability);
	}
	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Unlock();
}

/*
	解析。分时。
*/
void HqSdkUtil::parse_trend(IHsCommMessage* ansMsg)
{
	if(ansMsg == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}
	const char *prod_code = ansMsg->GetItem(H5SDK_TAG_PROD_CODE)->GetString();
	const char *type_code = ansMsg->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
	uint32 date = ansMsg->GetItem(H5SDK_TAG_DATE)->GetInt32();
	m_crc = ansMsg->GetItem(H5SDK_TAG_CRC)->GetInt32();
	uint32 time = ansMsg->GetItem(H5SDK_TAG_MIN_TIME)->GetInt32();

	my_log("\tprod=%s.%s date=%d.%d crc=%d\n", prod_code, type_code, date, time, m_crc);

	IGroup *group = ansMsg->GetGroup(H5SDK_TAG_TREND_GRP);
	if(group)
	{
		int count = group->GetRecordCount();
		// 解析每一条记录
		for (int i = 0; i < count; i++)
		{
			IRecord *record = group->GetRecord(i);

			if(record == NULL)
			{
				my_log("\t\tprod-null\n");
				continue;
			}

			uint32 date = record->GetItem(H5SDK_TAG_MARKET_DATE)->GetInt32();
			uint32 time = record->GetItem(H5SDK_TAG_MIN_TIME)->GetInt32();
			uint32 price = record->GetItem(H5SDK_TAG_HQ_PRICE)->GetInt32();
			int64 avg_px = record->GetItem(H5SDK_TAG_AVG_PX)->GetInt64();
			int64 wavg_px = record->GetItem(H5SDK_TAG_WAVG_PX)->GetInt64();
			uint64 amount = record->GetItem(H5SDK_TAG_BUSINESS_AMOUNT)->GetInt64();
			uint64 balance = record->GetItem(H5SDK_TAG_BUSINESS_BALANCE)->GetInt64();
			my_log("\t\tdate=%d.%d 价格=%d 均价=%lld 加权均价=%lld 成交量=%llu 成交额=%llu\n", date, time,price, avg_px, wavg_px, amount, balance);
		}
	}
	else
		my_log("\t\tgroup == null\n");
}

/*
	解析。逐笔委托(逐笔成交)
*/
void HqSdkUtil::parse_l2_order(IHsCommMessage* ansMsg, bool bLogMore)
{
	if(ansMsg == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	IGroup *group = ansMsg->GetGroup(H5SDK_TAG_PROD_GRP);
	if(group)
	{
		// 获取H5SDK_FINANCE_MIC_GRP的记录条数
		int count = group->GetRecordCount();
		// 解析每一条记录
		for (int j = 0; j < count; j++)
		{
			IRecord *record = group->GetRecord(j);

			if(record == NULL)
			{
				my_log("\tprod-null\n");
				continue;
			}

			const char *hq_type_code = record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
			const char *hsCode = record->GetItem(H5SDK_TAG_PROD_CODE)->GetString();

			my_log("\n\tcode=%s.%s\n", hsCode, hq_type_code);
	
			// 盘口数据
			IGroup * groupTranscation = record->GetGroup(H5SDK_TAG_TRANSCATION_GRP);

			if (groupTranscation != NULL)
			{
				int countTranscation = groupTranscation->GetRecordCount(); // 档数

				bool b0 = true;//成交方向0,打印一次
				bool b1 = true;//成交方向非0,打印一次
				my_log("\t\t成交方向0,非0,只会打印一次\n");
				for (int k = 0; k < countTranscation; k++)
				{
					IRecord * recordTranscation = groupTranscation->GetRecord(k);

					if (NULL == recordTranscation)
					{
						my_log("record-null ");
						continue;
					}
					uint32 business_time = recordTranscation->GetItem(H5SDK_TAG_BUSINESS_TIME)->GetInt32();
					uint32 hq_price = recordTranscation->GetItem(H5SDK_TAG_HQ_PRICE)->GetInt32();
					uint64 business_amount = recordTranscation->GetItem(H5SDK_TAG_BUSINESS_AMOUNT)->GetInt64();
					uint32 business_count = recordTranscation->GetItem(H5SDK_TAG_BUSINESS_COUNT)->GetInt32();
					int32 business_direction = (int32) recordTranscation->GetItem(H5SDK_TAG_BUSINESS_DIRECTION)->GetInt32();
					int32 trans_kind = (int32) recordTranscation->GetItem(H5SDK_TAG_TRANS_KIND)->GetInt32();

					bool bLog = false;
					if(0 == business_direction && b0)
					{
						b0 = false;
						bLog = true;
					}
					if(0 != business_direction && b1)
					{
						b1 = false;
						bLog = true;
					}
					if(bLog)
						my_log("\t\tbusiness_time=%d hq_price=%d business_amount=%llu business_count=%d business_direction=%d trans_kind=%d\n",
							business_time, hq_price, business_amount, business_count, business_direction, trans_kind);
				}
			}
			else
			{
				my_log("groupTranscation == null ");
			}
		}
	}
	else
	{
		my_log("\tgroup == null \n");
	}
}
/*
	解析。市场分类信息。
	市场重启，通知。所以，这里，要通知其他线程，做重新订阅的动作。
*/
void HqSdkUtil::parse_market_types(IHsCommMessage* response)
{
	if(response == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	// 因为字段H5SDK_FINANCE_MIC_GRP为sequence, 先获取IGroup句柄
	IGroup *finance_mic_grp = response->GetGroup(H5SDK_FINANCE_MIC_GRP);
	if(finance_mic_grp != NULL)
	{
		// 获取H5SDK_FINANCE_MIC_GRP的记录条数
		int finance_mic_grp_cnt = finance_mic_grp->GetRecordCount();
		// 解析每一条记录
		for (int i = 0; i < finance_mic_grp_cnt; i++)
		{
			// 获取记录的句柄
			IRecord *finance_mic_record = finance_mic_grp->GetRecord(i);
			// 根据各个字段的数据类型, 调用不同函数获取字段值
			const char *finance_mic = finance_mic_record->GetItem(H5SDK_TAG_FINANCE_MIC)->GetString();
			const char *finance_name = finance_mic_record->GetItem(H5SDK_TAG_FINANCE_NAME)->GetString();
			uint32 market_date = finance_mic_record->GetItem(H5SDK_TAG_MARKET_DATE)->GetInt32();
			uint32 init_date = finance_mic_record->GetItem(H5SDK_TAG_INIT_DATE)->GetInt32();
			int32 timezone = finance_mic_record->GetItem(H5SDK_TAG_TIMEZONE)->GetInt32();
			const char *timezone_code = finance_mic_record->GetItem(H5SDK_TAG_TIMEZONE_CODE)->GetString();
			uint8 dst = finance_mic_record->GetItem(H5SDK_TAG_DST_FLAG)->GetInt8();

			string gbkName; 
			UTF82GBK(finance_name, gbkName);
			my_log("\t\tmic=%s name=%s\n", finance_mic, gbkName.c_str());
			// 因为H5SDK_TAG_TYPE_GRP类型为sequence, 所以先必须获取IGroup句柄
			IGroup *type_grp = finance_mic_record->GetGroup(H5SDK_TAG_TYPE_GRP);
			if(type_grp)
			{
				// 获取H5SDK_TAG_TYPE_GRP的记录条数
				int type_grp_cnt = type_grp->GetRecordCount();
				// 解析每一条记录
				for (int j = 0; j < type_grp_cnt; j++)
				{
					// 获取记录的句柄
					IRecord *type_record = type_grp->GetRecord(j);
					// 根据各个字段的数据类型, 调用不同函数获取字段值
					const char *hq_type_code = type_record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
					const char *hq_type_name = type_record->GetItem(H5SDK_TAG_HQ_TYPE_NAME)->GetString();
					uint32 px_scale = type_record->GetItem(H5SDK_TAG_PRICE_SCALE)->GetInt32();
					int32 px_precision = type_record->GetItem(H5SDK_TAG_PX_PRECISION)->GetInt32();

					UTF82GBK(hq_type_name, gbkName);
					my_log("\t\t\tcode=%s name=%s\n", hq_type_code, gbkName.c_str());
					// 同理可解析余下字段, 注意字段类型是sequence的解析
				}
			}
			else
			{}
		}
	}
	else
		my_log("\tH5SDK_FINANCE_MIC_GRP grou=NULL\n");
}
/*
	解析。服务器信息.
	市场初始化，通知。所以，这里，要通知其他线程，做重新订阅的动作。
*/
void HqSdkUtil::parse_server_info(IHsCommMessage* response)
{
	if(response == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	const char *server_name = response->GetItem(H5SDK_TAG_SERVER_NAME)->GetString();//服务器名称
	my_log("\t服务器重启: 名称=%s\n", server_name);
	IGroup *group = response->GetGroup(H5SDK_TAG_FINANCE_GRP);
	if(group)
	{
		int count = group->GetRecordCount();
		// 解析每一条记录
		for (int i = 0; i < count; i++)
		{
			IRecord *record = group->GetRecord(i);
			const char *mic = record->GetItem(H5SDK_TAG_FINANCE_MIC)->GetString();//市场类型
			const char *name = record->GetItem(H5SDK_TAG_FINANCE_MIC)->GetString();//市场名称
			my_log("\t\t市场%s %s\n", mic, name);
		}
	}
	else
	{}
}
/*
	快照.订阅回应.
	断线重连，SDK会自动订阅.
*/
void HqSdkUtil::parse_subscribe(IHsCommMessage* response)
{
	if(response == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	uint32 sub_type = response->GetItem(H5SDK_TAG_SUB_TYPE)->GetInt32();
	char *sub_type_str = "?";
	if(sub_type == HSUB_ENUM_SUB_OVER)
	{
		sub_type_str = "覆盖订阅";
	}
	else if(sub_type == HSUB_ENUM_SUB)
	{
		sub_type_str = "追加订阅";
	}
	else if(sub_type == HSUB_ENUM_UNSUB)
	{
		sub_type_str = "退订";
		my_log("\t%s\n", sub_type_str);
	}

	IGroup *finance_mic_grp = response->GetGroup(H5SDK_TAG_PROD_GRP);
	int finance_mic_grp_cnt = 0;
	if(finance_mic_grp)
	{
		// 获取H5SDK_FINANCE_MIC_GRP的记录条数
		finance_mic_grp_cnt = finance_mic_grp->GetRecordCount();
		// 解析每一条记录
		for (int i = 0; i < finance_mic_grp_cnt; i++)
		{
			IRecord *record = finance_mic_grp->GetRecord(i);

			const char *prod_code = record->GetItem(H5SDK_TAG_PROD_CODE)->GetString();
			const char *type_code = record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
			uint32 error_no = record->GetItem(H5SDK_TAG_ERROR_NO)->GetInt32();
			if(strcmp(prod_code, "600570") == 0)//强制打印
			{//不用my_log.强制打印
				printf("\t\tcode=%s.%s error_no=%d\n", prod_code, type_code, error_no);
			}
		}
	}
	else
	{}
	my_log("\tcount=%d\n", finance_mic_grp_cnt);
}

/*
	逐笔委托.订阅回应.
*/
void HqSdkUtil::parse_subscribe_l2_transcation(IHsCommMessage* response)
{
	if(response == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	uint32 sub_type = response->GetItem(H5SDK_TAG_SUB_TYPE)->GetInt32();
	char *sub_type_str = "?";
	if(sub_type == HSUB_ENUM_SUB_OVER)
	{
		sub_type_str = "覆盖订阅";
	}
	else if(sub_type == HSUB_ENUM_SUB)
	{
		sub_type_str = "追加订阅";
	}
	else if(sub_type == HSUB_ENUM_UNSUB)
	{
		sub_type_str = "退订";
		my_log("\t%s\n", sub_type_str);
	}

	IGroup *group = response->GetGroup(H5SDK_TAG_PROD_GRP);
	if(group)
	{
		// 获取H5SDK_FINANCE_MIC_GRP的记录条数
		int count = group->GetRecordCount();
		// 解析每一条记录
		for (int i = 0; i < count; i++)
		{
			IRecord *record = group->GetRecord(i);

			const char *prod_code = record->GetItem(H5SDK_TAG_PROD_CODE)->GetString();
			const char *type_code = record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
			uint32 error_no = record->GetItem(H5SDK_TAG_ERROR_NO)->GetInt32();

			my_log("\t\tcode=%s.%s error_no=%d\n", prod_code, type_code, error_no);
		}
	}
	else
	{}
}

/*
	逐笔委托.订阅回应.
*/
void HqSdkUtil::parse_subscribe_l2_order(IHsCommMessage* response)
{
	if(response == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	uint32 sub_type = response->GetItem(H5SDK_TAG_SUB_TYPE)->GetInt32();
	char *sub_type_str = "?";
	if(sub_type == HSUB_ENUM_SUB_OVER)
	{
		sub_type_str = "覆盖订阅";
	}
	else if(sub_type == HSUB_ENUM_SUB)
	{
		sub_type_str = "追加订阅";
	}
	else if(sub_type == HSUB_ENUM_UNSUB)
	{
		sub_type_str = "退订";
		my_log("\t%s\n", sub_type_str);
	}

	IGroup *group = response->GetGroup(H5SDK_TAG_PROD_GRP);
	if(group)
	{
		// 获取H5SDK_FINANCE_MIC_GRP的记录条数
		int count = group->GetRecordCount();
		// 解析每一条记录
		for (int i = 0; i < count; i++)
		{
			IRecord *record = group->GetRecord(i);

			const char *prod_code = record->GetItem(H5SDK_TAG_PROD_CODE)->GetString();
			const char *type_code = record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
			uint32 error_no = record->GetItem(H5SDK_TAG_ERROR_NO)->GetInt32();

			my_log("\t\tcode=%s.%s error_no=%d\n", prod_code, type_code, error_no);
		}
	}
	else
	{}
}

/*
	从2003，市场代码表，获取全部的证券代码。
*/
void HqSdkUtil::GetCodesInMarket(const char *market, list<MyProdCode>* pList, int size)
{
	if(market == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	//参考【H5行情服务协议(修订版).xls】，【静态信息】 tab中，消息名称是【市场代码表】功能号域是【2003】的接口文档
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_MARKET_REFERENCE, REQUEST);
	request->GetBody()->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString(market);//市场代码
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);//同步命令
	if (ret ==0 && ansMsg)
	{
		IGroup *group = ansMsg->GetGroup(H5SDK_TAG_PROD_GRP);
		if(group != NULL)
		{
			int count = group->GetRecordCount();
			for (int i = 0; i < count; i++)
			{
				if(pList->size() >= size)
				{
					break;//最多取这么多个代码.
				}

				IRecord *record = group->GetRecord(i);
				const char* code = record->GetItem(H5SDK_TAG_PROD_CODE)->GetString();//产品代码

				if(strcmp(code, "600570") != 0)
				{//防止与外面直接添加的重复
					MyProdCode myProdCode(code, market);
					pList->push_back(myProdCode);
				}
			}
		}
		else
		{
			my_log("\t市场代码表: group == null.\n");
		}
	}
	//!!!释放.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!释放.
	request->Release();
}

//review by liushengxing 全市场订阅可以使用新的模式
/*
	快照.订阅。
*/
void HqSdkUtil::SubscriberAll(list<MyProdCode> *pListCodes, bool bSync/*同步*/, uint32 sub_type/*订阅，退订*/)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	bool bLog = (pListCodes->size() == 1);//只订阅一个代码，需要解析，打印Log.

	//参考【H5行情服务协议(修订版).xls】，【订阅主推类】 tab中，消息名称是【行情快照订阅】功能号域是【4001】的接口文档
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_SUBSCRIBE, REQUEST);

	request->GetItem(H5SDK_TAG_HQ_LEVEL)->SetInt8(H5SDK_ENUM_LEVEL_1);//level two的话，不要设置这个值。
	request->GetItem(H5SDK_TAG_SUB_TYPE)->SetInt8(sub_type); //覆盖订阅

	IGroup *group = request->SetGroup(H5SDK_TAG_PROD_GRP);
	// 为H5SDK_FINANCE_MIC_GRP添加第一条记录
	
	int count = 0;
	list<MyProdCode>::iterator it = pListCodes->begin();
	while(it != pListCodes->end())
	{
		IRecord *record = group->AddRecord();
		record->GetItem(H5SDK_TAG_PROD_CODE)->SetString((*it).prod_code.c_str());
		record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString((*it).market.c_str());

		if(pListCodes->size() == 1)
		{//多个代码订阅，就不打印了。
			if(sub_type == HSUB_ENUM_UNSUB)
			{
				my_log("\t退订: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
			else
			{
				my_log("\t订阅: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
		}

		it ++;
	}

	if(! bSync)
	{//异步
		m_pSession->AsyncSend(request);//异步调用, OnReceived响应回调
		//!!!释放.
		request->Release();
		return;
	}
	//同步
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000); //同步命令
	if (ret ==0 && ansMsg)
	{
		my_log("\t订阅.同步返回:\n");
		parse_subscribe(ansMsg);
	}
	//!!!释放.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!释放.
	request->Release();
}

/*
	逐笔成交.订阅。
*/
void HqSdkUtil::SubL2Transcation(list<MyProdCode> *pListCodes, bool bSync/*同步*/, uint32 sub_type/*订阅，退订*/)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	bool bLog = (pListCodes->size() == 1);//只订阅一个代码，需要解析，打印Log.

	//参考【H5行情服务协议(修订版).xls】，【订阅主推类】 tab中，消息名称是【l2逐笔成交订阅】功能号域是【4002】的接口文档
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_SUBSCRIBE_L2_TRANSCATION, REQUEST);

	request->GetItem(H5SDK_TAG_SUB_TYPE)->SetInt8(sub_type); //覆盖订阅

	IGroup *group = request->SetGroup(H5SDK_TAG_PROD_GRP);
	// 为H5SDK_FINANCE_MIC_GRP添加第一条记录
	
	int count = 0;
	list<MyProdCode>::iterator it = pListCodes->begin();
	while(it != pListCodes->end())
	{
		IRecord *record = group->AddRecord();
		record->GetItem(H5SDK_TAG_PROD_CODE)->SetString((*it).prod_code.c_str());
		record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString((*it).market.c_str());

		if(pListCodes->size() == 1)
		{//多个代码订阅，就不打印了。
			if(sub_type == HSUB_ENUM_UNSUB)
			{
				my_log("\t退订: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
			else
			{
				my_log("\t订阅: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
		}

		it ++;
	}

	if(! bSync)
	{//异步
		m_pSession->AsyncSend(request);//异步调用, OnReceived响应回调
		//!!!释放.
		request->Release();
		return;
	}
	//同步
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000); //同步命令
	if (ret ==0 && ansMsg)
	{
		my_log("\t逐笔委托.订阅.同步返回:\n");
		parse_subscribe_l2_transcation(ansMsg);
	}
	//!!!释放.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!释放.
	request->Release();
}

/*
	逐笔委托.订阅。
*/
void HqSdkUtil::SubL2Order(list<MyProdCode> *pListCodes, bool bSync/*同步*/, uint32 sub_type/*订阅，退订*/)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	bool bLog = (pListCodes->size() == 1);//只订阅一个代码，需要解析，打印Log.

	//参考【H5行情服务协议(修订版).xls】，【订阅主推类】 tab中，消息名称是【l2逐笔委托订阅】功能号域是【4003】的接口文档
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_SUBSCRIBE_L2_ORDER, REQUEST);

	request->GetItem(H5SDK_TAG_SUB_TYPE)->SetInt8(sub_type); //覆盖订阅

	IGroup *group = request->SetGroup(H5SDK_TAG_PROD_GRP);
	// 为H5SDK_FINANCE_MIC_GRP添加第一条记录
	
	int count = 0;
	list<MyProdCode>::iterator it = pListCodes->begin();
	while(it != pListCodes->end())
	{
		IRecord *record = group->AddRecord();
		record->GetItem(H5SDK_TAG_PROD_CODE)->SetString((*it).prod_code.c_str());
		record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString((*it).market.c_str());

		if(pListCodes->size() == 1)
		{//多个代码订阅，就不打印了。
			if(sub_type == HSUB_ENUM_UNSUB)
			{
				my_log("\t退订: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
			else
			{
				my_log("\t订阅: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
		}

		it ++;
	}

	if(! bSync)
	{//异步
		m_pSession->AsyncSend(request);//异步调用, OnReceived响应回调
		//!!!释放.
		request->Release();
		return;
	}
	//同步
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000); //同步命令
	if (ret ==0 && ansMsg)
	{
		my_log("\t逐笔委托.订阅.同步返回:\n");
		parse_subscribe_l2_order(ansMsg);
	}
	//!!!释放.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!释放.
	request->Release();
}

/*
	测试速度
*/
void HqSdkUtil::speed_test(void)
{
	my_log("\n\t测试速度开始\n");

	int num = 1;
	Endpoint endpoint[1];

	//正常测试服务器
	strcpy(endpoint[0].ip, m_strIp1.c_str());
	endpoint[0].port = m_iPort1;
	strcpy(endpoint[0].userData, "测试服务器");

/*	//非正常的服务器
	strcpy(endpoint[1].ip, "127.0.0.1");
	endpoint[1].port = 9999;
	strcpy(endpoint[1].userData, "端口未打开");

	//非正常的服务器
	strcpy(endpoint[2].ip, "192.168.94.200");
	endpoint[2].port = 9999;
	strcpy(endpoint[2].userData, "不可达服务器");
*/
	m_velocimetry = CreateVelocimetry();

	m_velocimetry->Start(endpoint, num, &m_myVelocimetryCallback, 3000);//启动测试
}

/*
	行情快照.测试
*/
void HqSdkUtil::test_snapshot(list<MyProdCode> *pListCodes, int iBegin, int iEnd, bool bSync)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	if(bSync)
	{
		my_log("\n\t行情快照同步\n");
	}
	else
	{
		my_log("\n\t行情快照异步\n");
	}

	//参考【H5行情服务协议(修订版).xls】，【快照实时类行情】 tab中，消息名称是【行情快照】功能号域是【3001】的接口文档
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_SNAPSHOT, REQUEST);
	if (NULL == request)
	{
		my_log("\t消息创建失败\n");
		return;
	}

	request->GetItem(H5SDK_TAG_HQ_LEVEL)->SetInt8(H5SDK_ENUM_LEVEL_1); //level_1
	
	IGroup *group = request->SetGroup(H5SDK_TAG_PROD_GRP);

	int id=0;
	list<MyProdCode>::iterator it;
	for(it = pListCodes->begin(); it != pListCodes->end(); it ++, id ++)
	{
		if(id < iBegin)
		{
			continue;
		}
		if(id > iEnd)
		{
			break;
		}
		const MyProdCode& item = *it;
		// 为H5SDK_FINANCE_MIC_GRP添加第一条记录
		IRecord *record = group->AddRecord(); //这里，重复加股票代码
		record->GetItem(H5SDK_TAG_PROD_CODE)->SetString(item.prod_code.c_str());
		record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString(item.market.c_str());
		my_log("\t取行情快照: %s.%s\n", item.prod_code.c_str(), item.market.c_str());
	}
	//设置字段，没有设置的字段，去取值，返回空。
	//不设置的话，返回全部字段。
/*	{
		IGroup *groupF = request->SetGroup(H5SDK_TAG_FIELD_GRP);
		IRecord *record = groupF->AddRecord();
		record->GetItem(H5SDK_TAG_FIELD_ID)->SetInt32(H5SDK_TAG_PROD_CODE);
		record->GetItem(H5SDK_TAG_FIELD_NAME)->SetString("prod_code");
		record = groupF->AddRecord();
		record->GetItem(H5SDK_TAG_FIELD_ID)->SetInt32(H5SDK_TAG_PROD_NAME);
		record->GetItem(H5SDK_TAG_FIELD_NAME)->SetString("prod_name");
		record = groupF->AddRecord();
		record->GetItem(H5SDK_TAG_FIELD_ID)->SetInt32(H5SDK_TAG_OPEN_PX);
		record->GetItem(H5SDK_TAG_FIELD_NAME)->SetString("open_px");
		record = groupF->AddRecord();
		record->GetItem(H5SDK_TAG_FIELD_ID)->SetInt32(H5SDK_TAG_LAST_PX);
		record->GetItem(H5SDK_TAG_FIELD_NAME)->SetString("last_px");
		record = groupF->AddRecord();
		record->GetItem(H5SDK_TAG_FIELD_ID)->SetInt32(H5SDK_TAG_BID_GRP);//group的话，不必再设置里面的字段了。
		record->GetItem(H5SDK_TAG_FIELD_NAME)->SetString("bid_grp");
		record = groupF->AddRecord();
		record->GetItem(H5SDK_TAG_FIELD_ID)->SetInt32(H5SDK_TAG_OFFER_GRP);//group的话，不必再设置里面的字段了。
		record->GetItem(H5SDK_TAG_FIELD_NAME)->SetString("offer_grp");
	}
	*/

	if(! bSync)
	{//异步
		m_pSession->AsyncSend(request);//异步调用, OnReceived响应回调
		//!!!释放.
		request->Release();
		return;
	}
	//同步
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		my_log("\t快照.同步返回:\n");
		parse_snapshot(ansMsg, 0);
	}
	else
	{
		my_log("\t同步请求错误 ret=%d。如果是超时，最好重试\r\n",ret);
	}
	//!!!释放.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!释放.
	request->Release();
}

/*
	测试分时
*/
void HqSdkUtil::test_trend(const char *prod_code, const char *market, bool bSync)
{
	if(bSync)
	{
		my_log("\n\t分时.同步\n");
	}
	else
	{
		my_log("\n\t分时.异步\n");
	}

	//参考【H5行情服务协议(修订版).xls】，【累积类行情】 tab中，消息名称是【按指定的日期或偏移取分时数据】功能号域是【6001】的接口文档
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_TREND, REQUEST);
	if (NULL == request)
	{
		my_log("\t消息创建失败\n");
		return;
	}

	request->GetItem(H5SDK_TAG_PROD_CODE)->SetString(prod_code); //证券代码
	request->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString(market); //类型代码
//	request->GetItem(H5SDK_TAG_DATE)->SetInt32(0); //日期:YYYYMMDD,0:表示今天
//	request->GetItem(H5SDK_TAG_DATE_OFFSET)->SetInt32(0); //距离当前日期的偏移天数,
	request->GetItem(H5SDK_TAG_CRC)->SetInt32(m_crc); //个股分时修正crc，当个股分时修正过以后，crc变化（行情服务器初始化或补线等操作），注意不同代码crc不同，
//	request->GetItem(H5SDK_TAG_MIN_TIME)->SetInt32(0); //增量请求分时的开始时间HHMM，默认为当日的第一分钟，必须为有效的时间（交易时间范围内）
	
	if(! bSync)
	{//异步
		m_pSession->AsyncSend(request);//异步调用, OnReceived响应回调
		//!!!释放.
		request->Release();
		return;
	}
	//同步
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		my_log("\t快照.同步返回:\n");
		parse_trend(ansMsg);
	}
	else
	{
		my_log("\t同步请求错误 ret=%d。如果是超时，最好重试\r\n",ret);
	}
	//!!!释放.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!释放.
	request->Release();
}

/*
	市场分类信息.测试
*/
void HqSdkUtil::test_market_type(bool bSync)
{
	if(bSync)
	{
		my_log("\n\t市场分类信息.同步\n");
	}
	else
	{
		my_log("\n\t市场分类信息.异步\n");
	}

	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_MARKET_TYPES, REQUEST);
	if (NULL == request)
	{
		my_log("\t消息创建失败\n");
		return;
	}
	// 根据H5SDK_FINANCE_MIC_GRP字段类型为sequence, 创建IGroup句柄
	IGroup *group = request->SetGroup(H5SDK_FINANCE_MIC_GRP);
	// 为H5SDK_FINANCE_MIC_GRP添加第一条记录
	IRecord *record = group->AddRecord();
	// 为第一条记录的字段H5SDK_TAG_FINANCE_MIC设置值"SS", H5SDK_TAG_FINANCE_MIC字段类型为bytevector, 故调用SetString, 传入字符串值
	record->GetItem(H5SDK_TAG_FINANCE_MIC)->SetString("SS");
	// 为H5SDK_FINANCE_MIC_GRP添加第二条记录
	record = group->AddRecord();
	// 为第二条记录的字段H5SDK_TAG_FINANCE_MIC设置值"SZ"
	record->GetItem(H5SDK_TAG_FINANCE_MIC)->SetString("SZ");
	my_log("\t输入市场: SS SZ\n");

	if(! bSync)
	{//异步
		m_pSession->AsyncSend(request);//异步调用, OnReceived响应回调
		//!!!释放.
		request->Release();
		return;
	}
	//同步
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		my_log("\t市场分类.同步返回:\n");
		parse_market_types(ansMsg);
	}
	else
	{
		my_log("\t同步请求错误 ret=%d。如果是超时，最好重试\r\n",ret);
	}
	//!!!释放.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!释放.
	request->Release();
}

/*
	解析.K线。
*/
void HqSdkUtil::parse_k_line(IHsCommMessage* response, uint64 time)
{
	if(response == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	const char *prod_code = response->GetItem(H5SDK_TAG_PROD_CODE)->GetString();
	const char *type_code = response->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
	if(strcmp(prod_code, "600570") == 0)
	{//不用my_log.强制打印
		printf("\t\tprod_code=%s type_code=%s\n", prod_code, type_code);
	}
	else
		my_log("\t\tprod_code=%s type_code=%s\n", prod_code, type_code);
	
	// 因为字段H5SDK_FINANCE_MIC_GRP为sequence, 先获取IGroup句柄
	IGroup *group = response->GetGroup(H5SDK_TAG_CANDLE_GRP);
	// 获取H5SDK_FINANCE_MIC_GRP的记录条数
	uint64 tmp_open=0, tmp_close=0, tmp_last=0;
	if(group != NULL)
	{
		int grpCount = group->GetRecordCount();
		// 解析每一条记录
		for (int i = 0; i < grpCount; i++)
		{
			// 获取记录的句柄
			IRecord *record = group->GetRecord(i);
			// 根据各个字段的数据类型, 调用不同函数获取字段值
			uint32 date = record->GetItem(H5SDK_TAG_DATE)->GetInt32();
			uint32 time = record->GetItem(H5SDK_TAG_MIN_TIME)->GetInt32();
			uint64 open_px = record->GetItem(H5SDK_TAG_OPEN_PX)->GetInt64();
			uint64 close_px = record->GetItem(H5SDK_TAG_CLOSE_PX)->GetInt64();
			int64 low_px = (int64)record->GetItem(H5SDK_TAG_LOW_PX)->GetInt64();

			tmp_open = open_px;
			tmp_close = close_px;

			if(strcmp(prod_code, "600570") == 0)
			{
				printf("\t\t\tdate=%u time=%u open_px=%llu close_px=%llu\n", date, time, open_px, close_px);
			}
			else
				my_log("\t\t\tdate=%u time=%u open_px=%llu close_px=%llu\n", date, time, open_px, close_px);
		}
	}
	else
	{}

	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Lock();
	if(g_pMyCapabilityTest)
	{//性能测试，将获取的值存入队列。
		g_pMyCapabilityTest->PushOkItem(time, prod_code, type_code, tmp_open, tmp_last);
		g_pMyCapabilityTest->PushOkPackage(time, SdkCallback_Candle_By_Offset_Cabability);
	}
	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Unlock();
}

/*
	K线.测试
*/
void HqSdkUtil::test_k_line(const char* code, const char *market, int k_num/*几个柱子*/, bool bSync)
{
	if(bSync)
	{
		my_log("\n\tK线.同步\n");
	}
	else
	{
		my_log("\n\tK线.异步\n");
	}

	//参考【H5行情服务协议(修订版).xls】，【累积类行情】 tab中，消息名称是【按偏移取K线】功能号域是【6002】的接口文档
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_CANDLE_BY_OFFSET, REQUEST);
	if (NULL == request)
	{
		my_log("\t消息创建失败\n");
		return;
	}
	char *tmp = (char *)malloc(strlen(code) + strlen(market) + 2);
	sprintf(tmp, "%s.%s", code, market);
	request->GetHead()->GetItem(H5PROTO_TAG_USER_KEY)->SetRawData(tmp, strlen(tmp)); //用户信息，如果异步错误，在OnReceived里，能用这个值，对应到命令。
	free(tmp);

	request->GetItem(H5SDK_TAG_PROD_CODE)->SetString(code); //代码
	request->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString(market); //市场
	request->GetItem(H5SDK_TAG_CANDLE_PEROID)->SetInt32(H5SDK_ENUM_PEROID_1MIN); //1分钟K线
	request->GetItem(H5SDK_TAG_CANDLE_MODE)->SetInt8(H5SDK_ENUM_CANDLE_ORIGINAL); //原始K线
	request->GetItem(H5SDK_TAG_DIRECTION)->SetInt8(H5SDK_ENUM_FORWARD); //方向
	request->GetItem(H5SDK_TAG_DATA_COUNT)->SetInt32(k_num); //取5组柱状值

	my_log("\t输入代码: %s.%s 柱子数量=%d K线类型=%d\n", code, market, k_num, H5SDK_ENUM_PEROID_1MIN);
	if(! bSync)
	{//异步
		m_pSession->AsyncSend(request);//异步调用, OnReceived响应回调
		//!!!释放.
		request->Release();
		return;
	}
	//同步
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		my_log("\tK线.同步返回:\n");
		parse_k_line(ansMsg, 0);
	}
	else
	{
		my_log("\t同步请求错误 ret=%d。如果是超时，最好重试\r\n",ret);
	}
	//!!!释放.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!释放.
	request->Release();
}

/*
	快照订阅.测试
*/
void HqSdkUtil::test_subscribe(list<MyProdCode> *pListCodes, bool bSync)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	if(bSync)
	{
		my_log("\t订阅.同步.\n");
	}
	else
	{
		my_log("\t订阅.异步.\n");
	}

	SubscriberAll(pListCodes, bSync, HSUB_ENUM_SUB_OVER/*覆盖*/);
}

/*
	逐笔成交.订阅.测试
*/
void HqSdkUtil::test_l2_transcation(list<MyProdCode> *pListCodes, bool bSync)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	if(bSync)
	{
		my_log("\n\t逐笔成交.订阅.同步.\n");
	}
	else
	{
		my_log("\n\t逐笔成交.订阅.异步.\n");
	}

	SubL2Transcation(pListCodes, bSync, HSUB_ENUM_SUB_OVER/*覆盖*/);
}

/*
	逐笔委托.订阅.测试
*/
void HqSdkUtil::test_l2_order(list<MyProdCode> *pListCodes, bool bSync)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	if(bSync)
	{
		my_log("\n\t逐笔委托.订阅.同步.\n");
	}
	else
	{
		my_log("\n\t逐笔委托.订阅.异步.\n");
	}

	SubL2Order(pListCodes, bSync, HSUB_ENUM_SUB_OVER/*覆盖*/);
}


/*
	IP地址和切换测试
*/
void HqSdkUtil::test_ip_switch(void)
{
	my_log("\n\tIP地址和切换测试\n");

	char addr[100] = {0};
	uint16 myport = 0;
	m_pSession->GetIpAndPort(0, addr, &myport);
	my_log("\t\tGetIpAndPort addr=%s port=%d\n", addr, myport);

	m_pSession->AddIpAndPort("sit.hq.hscloud.cn", 9999);
	m_pSession->GetIpAndPort(2, addr, &myport);
	my_log("\t\tAddIpAndPort addr=%s port=%d\n", addr, myport);

	m_pSession->ChangeIpAndPort(2, m_strIp1.c_str(), 9999);
	m_pSession->GetIpAndPort(2, addr, &myport);
	my_log("\t\tChangeIpAndPort addr=%s port=%d\n", addr, myport);

	int addCount = m_pSession->GetAddressCount();
	my_log("\t\tGetAddressCount count=%d\n", addCount);
	for (int i = 0; i< addCount; i++)
	{
		m_pSession->GetIpAndPort(i, addr, &myport);
		my_log("\t\t\tindex=%d addr=%s port=%d\n", i, addr, myport);
	}

	my_log("\t切换seesion中的ip,port. 请等待...\r\n");
	m_pSession->SwitchConnectIndex(2);
}
/*
	断开连接测试
*/
void HqSdkUtil::test_disconnect(void)
{
	my_log("\n\t断开连接测试(如有多个ip,会连接其他的ip)\n");
	m_pSession->Disconnect();
}
/*
	登出测试
*/
void HqSdkUtil::test_logout(void)
{
	my_log("\t登出测试(logout时，m_pSession调用命令，还是能成功。但是内部数据为空。)\n");

	int ret = m_pSession->Logout();
	my_log("\tLogout 返回=%d\n", ret);

	//m_pSession已经logout. 再发送消息，会收到空数据包。之后，就是验证这个情况。
	test_market_type(true);
}

