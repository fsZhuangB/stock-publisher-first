/** @file
* ����Demo.SDKʹ������
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
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
	���ܲ���ģ��
////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
	�յ�һ����ȷ����
*/
void MyCapabilityTest::PushOkItem(uint64 time, const char *code, const char *market, uint64 open_px, uint64 last_px)
{
	//���ܲ��ԣ�����ȡ��ֵ������С�
	MyCapabilityItem item(time, code, market, open_px, last_px);
	m_listGets.push_back(item);
}

/*
	�յ�һ����ȷ����
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
		printf(".");//1/10����ʾ��
	}

	m_iNumPackageOK ++;
	if(g_pMyCapabilityTest->GetAllPackage())
	{
		MyEnvironment::PostMainMessage(Command_SdkCallback, callback_type);
	}
}

/*
	�յ�һ����������
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
	���鷵�ص������ַ�����utf-8�ġ�ת��gbk,�������롣
	���ص�szGbk��Ҫdelete.
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
	//Linux,ֱ����utf8ȥ��ʾ����ʵ������Ҫת��������ʲô�ġ�
	//Ϊ�˸�windows����ݣ�����������
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
	����600570.SS
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
	sdk ��ʼ��
*/
bool HqSdkUtil::sdk_init(void)
{
	//////////////////////////////////////////////////////////////////////////
	// ���û�������
	//////////////////////////////////////////////////////////////////////////
	//����SDK��־·��
	SetH5DataPath("h5data");
	//����SDK��־·��
	SetH5LogPath("H5LOG");
	//������־��������·��
	SetSdkParamPath("SdkParamPath.json");

	//////////////////////////////////////////////////////////////////////////
	// �Ự����
	//////////////////////////////////////////////////////////////////////////
	m_pSessionOptions = CreateSessionOptions();
    if(m_pSessionOptions == NULL)
    {
        printf("Failed to create session option.");
        return false;
    }

	// ���ûỰѡ��1
	m_pSessionOptions->SetHeartbeatTimeout(3);

	//��������ip�Ͷ˿�
	m_pSessionOptions->SetServerIp(m_strIp1.c_str());
	m_pSessionOptions->SetServerPort(m_iPort1);

	m_pSessionOptions->SetServerIp(m_strIp2.c_str(),1);
	m_pSessionOptions->SetServerPort(m_iPort2,1);

	// �����Ự
	m_pSession = CreateSession(m_pSessionOptions);
    if(m_pSession == NULL)
    {
        printf("Failed to create session.");
        return false;
    }

	m_pSession->SetAppInfo(m_strAppKey.c_str(), m_strAppSecret.c_str());

	// ��ʼΪ���лỰ���ûص�
	StartSetCallback();
	//�����Ự��ʹ��ͬһ���ص��࣬Ҳ����ʹ�ò�ͬ�Ļص���
	m_pSession->SetCallback(&m_h5SdkCallbackImpl);

	//�״�����ʱ�������Զ����ӣ���Ҫ�����ֹ�����[�����ر���Ҫ������Ҫ���ô˺���]
	//SetInitAutoConnectFlag(false);

	//���ô���
	//SetProxyOptions(SDKHTTPPROXY, "10.26.210.42", 808, "test", "test");
	return true;
}
/*
	sdk �ر�
*/
void HqSdkUtil::sdk_close(void)
{
	my_log("\t�ر�sdk\n");
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
	������������ա�ĳֻ�������Ϣ��
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

	// ��ȡʱ��
	uint32 hsTimeStamp = record->GetItem(H5SDK_TAG_DATA_TIMESTAMP)->GetInt32();
	uint64 open_px = record->GetItem(H5SDK_TAG_OPEN_PX)->GetInt64();                   // ���տ��̼�
	uint64 close_px = record->GetItem(H5SDK_TAG_CLOSE_PX)->GetInt64();                   // �������̼�
	uint64 high_px = record->GetItem(H5SDK_TAG_HIGH_PX)->GetInt64();                   // �������̼�
	uint64 last_px = record->GetItem(H5SDK_TAG_LAST_PX)->GetInt64();                   // ���¼�

//	double px_change = (double)(int64)record->GetItem(H5SDK_TAG_PX_CHANGE)->GetInt64(); //�ǵ���
//	if(px_change <= 0)
//		my_log("  %f  ", px_change);
	int64 avg_px = record->GetItem(H5SDK_TAG_AVG_PX)->GetInt64(); //�ǵ���
//	my_log("  %d  ", avg_px);

	if(strcmp(hsCode, "600570") == 0)//ǿ�ƴ�ӡ.
	{//����my_log.ǿ�ƴ�ӡ
		printf("\n\t(code=%s.%s open_px=%llu close_px=%llu last_px=%llu)\n", hsCode, hq_type_code, open_px, close_px, last_px);
	}

	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Lock();
	if(g_pMyCapabilityTest)
	{//���ܲ��ԣ�����ȡ��ֵ������С�
		g_pMyCapabilityTest->PushOkItem(time, hsCode, hq_type_code, open_px, last_px);
	}
	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Unlock();

	// �̿�����
	IGroup * pBidGroup = record->GetGroup(H5SDK_TAG_BID_GRP);
	if (pBidGroup != NULL)
	{
		int layers = pBidGroup->GetRecordCount(); // ����

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

		/*	//level_2�Ĳ���
			IGroup * entrust_grp = record->GetGroup(H5SDK_TAG_ENTRUST_GRP);			
			if (entrust_grp != NULL)
			{
				my_log("\t\t\t\tentrust_grp��ֵ\n");
			}
			else
			{
				my_log("\t\t\t\tentrust_grp��\n");
			}
			*/
		}
	}
	else
	{}

	IGroup *pAskGroup = record->GetGroup(H5SDK_TAG_OFFER_GRP);
	if (pAskGroup != NULL)
	{
		int layers = pAskGroup->GetRecordCount(); // ����

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
			{//����my_log.ǿ�ƴ�ӡ
				printf("\t\t\toffer entrust_px=%llu entrust_amount=%llu\n", px, amount);
			}
		}
	}
	else
	{}
}

/*
	������������ա�
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
		// ��ȡH5SDK_FINANCE_MIC_GRP�ļ�¼����
		int count = group->GetRecordCount();
		// ����ÿһ����¼
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

		//���������ģ�ֻ��ʾһ���㡣
		if(count > 1)
		{
			my_log("\n\t\t%d(֧)\n", count);
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
	{//���ܲ��ԣ�����ȡ��ֵ������С�
		g_pMyCapabilityTest->PushOkPackage(time, SdkCallback_Snapshot_Capability);
	}
	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Unlock();
}

/*
	��������ʱ��
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
		// ����ÿһ����¼
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
			my_log("\t\tdate=%d.%d �۸�=%d ����=%lld ��Ȩ����=%lld �ɽ���=%llu �ɽ���=%llu\n", date, time,price, avg_px, wavg_px, amount, balance);
		}
	}
	else
		my_log("\t\tgroup == null\n");
}

/*
	���������ί��(��ʳɽ�)
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
		// ��ȡH5SDK_FINANCE_MIC_GRP�ļ�¼����
		int count = group->GetRecordCount();
		// ����ÿһ����¼
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
	
			// �̿�����
			IGroup * groupTranscation = record->GetGroup(H5SDK_TAG_TRANSCATION_GRP);

			if (groupTranscation != NULL)
			{
				int countTranscation = groupTranscation->GetRecordCount(); // ����

				bool b0 = true;//�ɽ�����0,��ӡһ��
				bool b1 = true;//�ɽ������0,��ӡһ��
				my_log("\t\t�ɽ�����0,��0,ֻ���ӡһ��\n");
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
	�������г�������Ϣ��
	�г�������֪ͨ�����ԣ����Ҫ֪ͨ�����̣߳������¶��ĵĶ�����
*/
void HqSdkUtil::parse_market_types(IHsCommMessage* response)
{
	if(response == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	// ��Ϊ�ֶ�H5SDK_FINANCE_MIC_GRPΪsequence, �Ȼ�ȡIGroup���
	IGroup *finance_mic_grp = response->GetGroup(H5SDK_FINANCE_MIC_GRP);
	if(finance_mic_grp != NULL)
	{
		// ��ȡH5SDK_FINANCE_MIC_GRP�ļ�¼����
		int finance_mic_grp_cnt = finance_mic_grp->GetRecordCount();
		// ����ÿһ����¼
		for (int i = 0; i < finance_mic_grp_cnt; i++)
		{
			// ��ȡ��¼�ľ��
			IRecord *finance_mic_record = finance_mic_grp->GetRecord(i);
			// ���ݸ����ֶε���������, ���ò�ͬ������ȡ�ֶ�ֵ
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
			// ��ΪH5SDK_TAG_TYPE_GRP����Ϊsequence, �����ȱ����ȡIGroup���
			IGroup *type_grp = finance_mic_record->GetGroup(H5SDK_TAG_TYPE_GRP);
			if(type_grp)
			{
				// ��ȡH5SDK_TAG_TYPE_GRP�ļ�¼����
				int type_grp_cnt = type_grp->GetRecordCount();
				// ����ÿһ����¼
				for (int j = 0; j < type_grp_cnt; j++)
				{
					// ��ȡ��¼�ľ��
					IRecord *type_record = type_grp->GetRecord(j);
					// ���ݸ����ֶε���������, ���ò�ͬ������ȡ�ֶ�ֵ
					const char *hq_type_code = type_record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
					const char *hq_type_name = type_record->GetItem(H5SDK_TAG_HQ_TYPE_NAME)->GetString();
					uint32 px_scale = type_record->GetItem(H5SDK_TAG_PRICE_SCALE)->GetInt32();
					int32 px_precision = type_record->GetItem(H5SDK_TAG_PX_PRECISION)->GetInt32();

					UTF82GBK(hq_type_name, gbkName);
					my_log("\t\t\tcode=%s name=%s\n", hq_type_code, gbkName.c_str());
					// ͬ��ɽ��������ֶ�, ע���ֶ�������sequence�Ľ���
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
	��������������Ϣ.
	�г���ʼ����֪ͨ�����ԣ����Ҫ֪ͨ�����̣߳������¶��ĵĶ�����
*/
void HqSdkUtil::parse_server_info(IHsCommMessage* response)
{
	if(response == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	const char *server_name = response->GetItem(H5SDK_TAG_SERVER_NAME)->GetString();//����������
	my_log("\t����������: ����=%s\n", server_name);
	IGroup *group = response->GetGroup(H5SDK_TAG_FINANCE_GRP);
	if(group)
	{
		int count = group->GetRecordCount();
		// ����ÿһ����¼
		for (int i = 0; i < count; i++)
		{
			IRecord *record = group->GetRecord(i);
			const char *mic = record->GetItem(H5SDK_TAG_FINANCE_MIC)->GetString();//�г�����
			const char *name = record->GetItem(H5SDK_TAG_FINANCE_MIC)->GetString();//�г�����
			my_log("\t\t�г�%s %s\n", mic, name);
		}
	}
	else
	{}
}
/*
	����.���Ļ�Ӧ.
	����������SDK���Զ�����.
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
		sub_type_str = "���Ƕ���";
	}
	else if(sub_type == HSUB_ENUM_SUB)
	{
		sub_type_str = "׷�Ӷ���";
	}
	else if(sub_type == HSUB_ENUM_UNSUB)
	{
		sub_type_str = "�˶�";
		my_log("\t%s\n", sub_type_str);
	}

	IGroup *finance_mic_grp = response->GetGroup(H5SDK_TAG_PROD_GRP);
	int finance_mic_grp_cnt = 0;
	if(finance_mic_grp)
	{
		// ��ȡH5SDK_FINANCE_MIC_GRP�ļ�¼����
		finance_mic_grp_cnt = finance_mic_grp->GetRecordCount();
		// ����ÿһ����¼
		for (int i = 0; i < finance_mic_grp_cnt; i++)
		{
			IRecord *record = finance_mic_grp->GetRecord(i);

			const char *prod_code = record->GetItem(H5SDK_TAG_PROD_CODE)->GetString();
			const char *type_code = record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->GetString();
			uint32 error_no = record->GetItem(H5SDK_TAG_ERROR_NO)->GetInt32();
			if(strcmp(prod_code, "600570") == 0)//ǿ�ƴ�ӡ
			{//����my_log.ǿ�ƴ�ӡ
				printf("\t\tcode=%s.%s error_no=%d\n", prod_code, type_code, error_no);
			}
		}
	}
	else
	{}
	my_log("\tcount=%d\n", finance_mic_grp_cnt);
}

/*
	���ί��.���Ļ�Ӧ.
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
		sub_type_str = "���Ƕ���";
	}
	else if(sub_type == HSUB_ENUM_SUB)
	{
		sub_type_str = "׷�Ӷ���";
	}
	else if(sub_type == HSUB_ENUM_UNSUB)
	{
		sub_type_str = "�˶�";
		my_log("\t%s\n", sub_type_str);
	}

	IGroup *group = response->GetGroup(H5SDK_TAG_PROD_GRP);
	if(group)
	{
		// ��ȡH5SDK_FINANCE_MIC_GRP�ļ�¼����
		int count = group->GetRecordCount();
		// ����ÿһ����¼
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
	���ί��.���Ļ�Ӧ.
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
		sub_type_str = "���Ƕ���";
	}
	else if(sub_type == HSUB_ENUM_SUB)
	{
		sub_type_str = "׷�Ӷ���";
	}
	else if(sub_type == HSUB_ENUM_UNSUB)
	{
		sub_type_str = "�˶�";
		my_log("\t%s\n", sub_type_str);
	}

	IGroup *group = response->GetGroup(H5SDK_TAG_PROD_GRP);
	if(group)
	{
		// ��ȡH5SDK_FINANCE_MIC_GRP�ļ�¼����
		int count = group->GetRecordCount();
		// ����ÿһ����¼
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
	��2003���г��������ȡȫ����֤ȯ���롣
*/
void HqSdkUtil::GetCodesInMarket(const char *market, list<MyProdCode>* pList, int size)
{
	if(market == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	//�ο���H5�������Э��(�޶���).xls��������̬��Ϣ�� tab�У���Ϣ�����ǡ��г���������ܺ����ǡ�2003���Ľӿ��ĵ�
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_MARKET_REFERENCE, REQUEST);
	request->GetBody()->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString(market);//�г�����
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);//ͬ������
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
					break;//���ȡ��ô�������.
				}

				IRecord *record = group->GetRecord(i);
				const char* code = record->GetItem(H5SDK_TAG_PROD_CODE)->GetString();//��Ʒ����

				if(strcmp(code, "600570") != 0)
				{//��ֹ������ֱ����ӵ��ظ�
					MyProdCode myProdCode(code, market);
					pList->push_back(myProdCode);
				}
			}
		}
		else
		{
			my_log("\t�г������: group == null.\n");
		}
	}
	//!!!�ͷ�.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!�ͷ�.
	request->Release();
}

//review by liushengxing ȫ�г����Ŀ���ʹ���µ�ģʽ
/*
	����.���ġ�
*/
void HqSdkUtil::SubscriberAll(list<MyProdCode> *pListCodes, bool bSync/*ͬ��*/, uint32 sub_type/*���ģ��˶�*/)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	bool bLog = (pListCodes->size() == 1);//ֻ����һ�����룬��Ҫ��������ӡLog.

	//�ο���H5�������Э��(�޶���).xls���������������ࡿ tab�У���Ϣ�����ǡ�������ն��ġ����ܺ����ǡ�4001���Ľӿ��ĵ�
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_SUBSCRIBE, REQUEST);

	request->GetItem(H5SDK_TAG_HQ_LEVEL)->SetInt8(H5SDK_ENUM_LEVEL_1);//level two�Ļ�����Ҫ�������ֵ��
	request->GetItem(H5SDK_TAG_SUB_TYPE)->SetInt8(sub_type); //���Ƕ���

	IGroup *group = request->SetGroup(H5SDK_TAG_PROD_GRP);
	// ΪH5SDK_FINANCE_MIC_GRP��ӵ�һ����¼
	
	int count = 0;
	list<MyProdCode>::iterator it = pListCodes->begin();
	while(it != pListCodes->end())
	{
		IRecord *record = group->AddRecord();
		record->GetItem(H5SDK_TAG_PROD_CODE)->SetString((*it).prod_code.c_str());
		record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString((*it).market.c_str());

		if(pListCodes->size() == 1)
		{//������붩�ģ��Ͳ���ӡ�ˡ�
			if(sub_type == HSUB_ENUM_UNSUB)
			{
				my_log("\t�˶�: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
			else
			{
				my_log("\t����: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
		}

		it ++;
	}

	if(! bSync)
	{//�첽
		m_pSession->AsyncSend(request);//�첽����, OnReceived��Ӧ�ص�
		//!!!�ͷ�.
		request->Release();
		return;
	}
	//ͬ��
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000); //ͬ������
	if (ret ==0 && ansMsg)
	{
		my_log("\t����.ͬ������:\n");
		parse_subscribe(ansMsg);
	}
	//!!!�ͷ�.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!�ͷ�.
	request->Release();
}

/*
	��ʳɽ�.���ġ�
*/
void HqSdkUtil::SubL2Transcation(list<MyProdCode> *pListCodes, bool bSync/*ͬ��*/, uint32 sub_type/*���ģ��˶�*/)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	bool bLog = (pListCodes->size() == 1);//ֻ����һ�����룬��Ҫ��������ӡLog.

	//�ο���H5�������Э��(�޶���).xls���������������ࡿ tab�У���Ϣ�����ǡ�l2��ʳɽ����ġ����ܺ����ǡ�4002���Ľӿ��ĵ�
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_SUBSCRIBE_L2_TRANSCATION, REQUEST);

	request->GetItem(H5SDK_TAG_SUB_TYPE)->SetInt8(sub_type); //���Ƕ���

	IGroup *group = request->SetGroup(H5SDK_TAG_PROD_GRP);
	// ΪH5SDK_FINANCE_MIC_GRP��ӵ�һ����¼
	
	int count = 0;
	list<MyProdCode>::iterator it = pListCodes->begin();
	while(it != pListCodes->end())
	{
		IRecord *record = group->AddRecord();
		record->GetItem(H5SDK_TAG_PROD_CODE)->SetString((*it).prod_code.c_str());
		record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString((*it).market.c_str());

		if(pListCodes->size() == 1)
		{//������붩�ģ��Ͳ���ӡ�ˡ�
			if(sub_type == HSUB_ENUM_UNSUB)
			{
				my_log("\t�˶�: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
			else
			{
				my_log("\t����: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
		}

		it ++;
	}

	if(! bSync)
	{//�첽
		m_pSession->AsyncSend(request);//�첽����, OnReceived��Ӧ�ص�
		//!!!�ͷ�.
		request->Release();
		return;
	}
	//ͬ��
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000); //ͬ������
	if (ret ==0 && ansMsg)
	{
		my_log("\t���ί��.����.ͬ������:\n");
		parse_subscribe_l2_transcation(ansMsg);
	}
	//!!!�ͷ�.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!�ͷ�.
	request->Release();
}

/*
	���ί��.���ġ�
*/
void HqSdkUtil::SubL2Order(list<MyProdCode> *pListCodes, bool bSync/*ͬ��*/, uint32 sub_type/*���ģ��˶�*/)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	bool bLog = (pListCodes->size() == 1);//ֻ����һ�����룬��Ҫ��������ӡLog.

	//�ο���H5�������Э��(�޶���).xls���������������ࡿ tab�У���Ϣ�����ǡ�l2���ί�ж��ġ����ܺ����ǡ�4003���Ľӿ��ĵ�
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_SUBSCRIBE_L2_ORDER, REQUEST);

	request->GetItem(H5SDK_TAG_SUB_TYPE)->SetInt8(sub_type); //���Ƕ���

	IGroup *group = request->SetGroup(H5SDK_TAG_PROD_GRP);
	// ΪH5SDK_FINANCE_MIC_GRP��ӵ�һ����¼
	
	int count = 0;
	list<MyProdCode>::iterator it = pListCodes->begin();
	while(it != pListCodes->end())
	{
		IRecord *record = group->AddRecord();
		record->GetItem(H5SDK_TAG_PROD_CODE)->SetString((*it).prod_code.c_str());
		record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString((*it).market.c_str());

		if(pListCodes->size() == 1)
		{//������붩�ģ��Ͳ���ӡ�ˡ�
			if(sub_type == HSUB_ENUM_UNSUB)
			{
				my_log("\t�˶�: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
			else
			{
				my_log("\t����: %s.%s \n", (*it).prod_code.c_str(), (*it).market.c_str());
			}
		}

		it ++;
	}

	if(! bSync)
	{//�첽
		m_pSession->AsyncSend(request);//�첽����, OnReceived��Ӧ�ص�
		//!!!�ͷ�.
		request->Release();
		return;
	}
	//ͬ��
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000); //ͬ������
	if (ret ==0 && ansMsg)
	{
		my_log("\t���ί��.����.ͬ������:\n");
		parse_subscribe_l2_order(ansMsg);
	}
	//!!!�ͷ�.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!�ͷ�.
	request->Release();
}

/*
	�����ٶ�
*/
void HqSdkUtil::speed_test(void)
{
	my_log("\n\t�����ٶȿ�ʼ\n");

	int num = 1;
	Endpoint endpoint[1];

	//�������Է�����
	strcpy(endpoint[0].ip, m_strIp1.c_str());
	endpoint[0].port = m_iPort1;
	strcpy(endpoint[0].userData, "���Է�����");

/*	//�������ķ�����
	strcpy(endpoint[1].ip, "127.0.0.1");
	endpoint[1].port = 9999;
	strcpy(endpoint[1].userData, "�˿�δ��");

	//�������ķ�����
	strcpy(endpoint[2].ip, "192.168.94.200");
	endpoint[2].port = 9999;
	strcpy(endpoint[2].userData, "���ɴ������");
*/
	m_velocimetry = CreateVelocimetry();

	m_velocimetry->Start(endpoint, num, &m_myVelocimetryCallback, 3000);//��������
}

/*
	�������.����
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
		my_log("\n\t�������ͬ��\n");
	}
	else
	{
		my_log("\n\t��������첽\n");
	}

	//�ο���H5�������Э��(�޶���).xls����������ʵʱ�����顿 tab�У���Ϣ�����ǡ�������ա����ܺ����ǡ�3001���Ľӿ��ĵ�
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_SNAPSHOT, REQUEST);
	if (NULL == request)
	{
		my_log("\t��Ϣ����ʧ��\n");
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
		// ΪH5SDK_FINANCE_MIC_GRP��ӵ�һ����¼
		IRecord *record = group->AddRecord(); //����ظ��ӹ�Ʊ����
		record->GetItem(H5SDK_TAG_PROD_CODE)->SetString(item.prod_code.c_str());
		record->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString(item.market.c_str());
		my_log("\tȡ�������: %s.%s\n", item.prod_code.c_str(), item.market.c_str());
	}
	//�����ֶΣ�û�����õ��ֶΣ�ȥȡֵ�����ؿա�
	//�����õĻ�������ȫ���ֶΡ�
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
		record->GetItem(H5SDK_TAG_FIELD_ID)->SetInt32(H5SDK_TAG_BID_GRP);//group�Ļ�������������������ֶ��ˡ�
		record->GetItem(H5SDK_TAG_FIELD_NAME)->SetString("bid_grp");
		record = groupF->AddRecord();
		record->GetItem(H5SDK_TAG_FIELD_ID)->SetInt32(H5SDK_TAG_OFFER_GRP);//group�Ļ�������������������ֶ��ˡ�
		record->GetItem(H5SDK_TAG_FIELD_NAME)->SetString("offer_grp");
	}
	*/

	if(! bSync)
	{//�첽
		m_pSession->AsyncSend(request);//�첽����, OnReceived��Ӧ�ص�
		//!!!�ͷ�.
		request->Release();
		return;
	}
	//ͬ��
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		my_log("\t����.ͬ������:\n");
		parse_snapshot(ansMsg, 0);
	}
	else
	{
		my_log("\tͬ��������� ret=%d������ǳ�ʱ���������\r\n",ret);
	}
	//!!!�ͷ�.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!�ͷ�.
	request->Release();
}

/*
	���Է�ʱ
*/
void HqSdkUtil::test_trend(const char *prod_code, const char *market, bool bSync)
{
	if(bSync)
	{
		my_log("\n\t��ʱ.ͬ��\n");
	}
	else
	{
		my_log("\n\t��ʱ.�첽\n");
	}

	//�ο���H5�������Э��(�޶���).xls�������ۻ������顿 tab�У���Ϣ�����ǡ���ָ�������ڻ�ƫ��ȡ��ʱ���ݡ����ܺ����ǡ�6001���Ľӿ��ĵ�
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_TREND, REQUEST);
	if (NULL == request)
	{
		my_log("\t��Ϣ����ʧ��\n");
		return;
	}

	request->GetItem(H5SDK_TAG_PROD_CODE)->SetString(prod_code); //֤ȯ����
	request->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString(market); //���ʹ���
//	request->GetItem(H5SDK_TAG_DATE)->SetInt32(0); //����:YYYYMMDD,0:��ʾ����
//	request->GetItem(H5SDK_TAG_DATE_OFFSET)->SetInt32(0); //���뵱ǰ���ڵ�ƫ������,
	request->GetItem(H5SDK_TAG_CRC)->SetInt32(m_crc); //���ɷ�ʱ����crc�������ɷ�ʱ�������Ժ�crc�仯�������������ʼ�����ߵȲ�������ע�ⲻͬ����crc��ͬ��
//	request->GetItem(H5SDK_TAG_MIN_TIME)->SetInt32(0); //���������ʱ�Ŀ�ʼʱ��HHMM��Ĭ��Ϊ���յĵ�һ���ӣ�����Ϊ��Ч��ʱ�䣨����ʱ�䷶Χ�ڣ�
	
	if(! bSync)
	{//�첽
		m_pSession->AsyncSend(request);//�첽����, OnReceived��Ӧ�ص�
		//!!!�ͷ�.
		request->Release();
		return;
	}
	//ͬ��
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		my_log("\t����.ͬ������:\n");
		parse_trend(ansMsg);
	}
	else
	{
		my_log("\tͬ��������� ret=%d������ǳ�ʱ���������\r\n",ret);
	}
	//!!!�ͷ�.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!�ͷ�.
	request->Release();
}

/*
	�г�������Ϣ.����
*/
void HqSdkUtil::test_market_type(bool bSync)
{
	if(bSync)
	{
		my_log("\n\t�г�������Ϣ.ͬ��\n");
	}
	else
	{
		my_log("\n\t�г�������Ϣ.�첽\n");
	}

	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_MARKET_TYPES, REQUEST);
	if (NULL == request)
	{
		my_log("\t��Ϣ����ʧ��\n");
		return;
	}
	// ����H5SDK_FINANCE_MIC_GRP�ֶ�����Ϊsequence, ����IGroup���
	IGroup *group = request->SetGroup(H5SDK_FINANCE_MIC_GRP);
	// ΪH5SDK_FINANCE_MIC_GRP��ӵ�һ����¼
	IRecord *record = group->AddRecord();
	// Ϊ��һ����¼���ֶ�H5SDK_TAG_FINANCE_MIC����ֵ"SS", H5SDK_TAG_FINANCE_MIC�ֶ�����Ϊbytevector, �ʵ���SetString, �����ַ���ֵ
	record->GetItem(H5SDK_TAG_FINANCE_MIC)->SetString("SS");
	// ΪH5SDK_FINANCE_MIC_GRP��ӵڶ�����¼
	record = group->AddRecord();
	// Ϊ�ڶ�����¼���ֶ�H5SDK_TAG_FINANCE_MIC����ֵ"SZ"
	record->GetItem(H5SDK_TAG_FINANCE_MIC)->SetString("SZ");
	my_log("\t�����г�: SS SZ\n");

	if(! bSync)
	{//�첽
		m_pSession->AsyncSend(request);//�첽����, OnReceived��Ӧ�ص�
		//!!!�ͷ�.
		request->Release();
		return;
	}
	//ͬ��
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		my_log("\t�г�����.ͬ������:\n");
		parse_market_types(ansMsg);
	}
	else
	{
		my_log("\tͬ��������� ret=%d������ǳ�ʱ���������\r\n",ret);
	}
	//!!!�ͷ�.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!�ͷ�.
	request->Release();
}

/*
	����.K�ߡ�
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
	{//����my_log.ǿ�ƴ�ӡ
		printf("\t\tprod_code=%s type_code=%s\n", prod_code, type_code);
	}
	else
		my_log("\t\tprod_code=%s type_code=%s\n", prod_code, type_code);
	
	// ��Ϊ�ֶ�H5SDK_FINANCE_MIC_GRPΪsequence, �Ȼ�ȡIGroup���
	IGroup *group = response->GetGroup(H5SDK_TAG_CANDLE_GRP);
	// ��ȡH5SDK_FINANCE_MIC_GRP�ļ�¼����
	uint64 tmp_open=0, tmp_close=0, tmp_last=0;
	if(group != NULL)
	{
		int grpCount = group->GetRecordCount();
		// ����ÿһ����¼
		for (int i = 0; i < grpCount; i++)
		{
			// ��ȡ��¼�ľ��
			IRecord *record = group->GetRecord(i);
			// ���ݸ����ֶε���������, ���ò�ͬ������ȡ�ֶ�ֵ
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
	{//���ܲ��ԣ�����ȡ��ֵ������С�
		g_pMyCapabilityTest->PushOkItem(time, prod_code, type_code, tmp_open, tmp_last);
		g_pMyCapabilityTest->PushOkPackage(time, SdkCallback_Candle_By_Offset_Cabability);
	}
	MyEnvironment::GetHqSdkUtil()->m_mutexCapabilityTest.Unlock();
}

/*
	K��.����
*/
void HqSdkUtil::test_k_line(const char* code, const char *market, int k_num/*��������*/, bool bSync)
{
	if(bSync)
	{
		my_log("\n\tK��.ͬ��\n");
	}
	else
	{
		my_log("\n\tK��.�첽\n");
	}

	//�ο���H5�������Э��(�޶���).xls�������ۻ������顿 tab�У���Ϣ�����ǡ���ƫ��ȡK�ߡ����ܺ����ǡ�6002���Ľӿ��ĵ�
	IHsCommMessage *request = m_pSession->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_CANDLE_BY_OFFSET, REQUEST);
	if (NULL == request)
	{
		my_log("\t��Ϣ����ʧ��\n");
		return;
	}
	char *tmp = (char *)malloc(strlen(code) + strlen(market) + 2);
	sprintf(tmp, "%s.%s", code, market);
	request->GetHead()->GetItem(H5PROTO_TAG_USER_KEY)->SetRawData(tmp, strlen(tmp)); //�û���Ϣ������첽������OnReceived��������ֵ����Ӧ�����
	free(tmp);

	request->GetItem(H5SDK_TAG_PROD_CODE)->SetString(code); //����
	request->GetItem(H5SDK_TAG_HQ_TYPE_CODE)->SetString(market); //�г�
	request->GetItem(H5SDK_TAG_CANDLE_PEROID)->SetInt32(H5SDK_ENUM_PEROID_1MIN); //1����K��
	request->GetItem(H5SDK_TAG_CANDLE_MODE)->SetInt8(H5SDK_ENUM_CANDLE_ORIGINAL); //ԭʼK��
	request->GetItem(H5SDK_TAG_DIRECTION)->SetInt8(H5SDK_ENUM_FORWARD); //����
	request->GetItem(H5SDK_TAG_DATA_COUNT)->SetInt32(k_num); //ȡ5����״ֵ

	my_log("\t�������: %s.%s ��������=%d K������=%d\n", code, market, k_num, H5SDK_ENUM_PEROID_1MIN);
	if(! bSync)
	{//�첽
		m_pSession->AsyncSend(request);//�첽����, OnReceived��Ӧ�ص�
		//!!!�ͷ�.
		request->Release();
		return;
	}
	//ͬ��
	IHsCommMessage *ansMsg =NULL;
	int ret = m_pSession->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		my_log("\tK��.ͬ������:\n");
		parse_k_line(ansMsg, 0);
	}
	else
	{
		my_log("\tͬ��������� ret=%d������ǳ�ʱ���������\r\n",ret);
	}
	//!!!�ͷ�.
	if(ansMsg)
	{
		ansMsg->Release();
	}
	//!!!�ͷ�.
	request->Release();
}

/*
	���ն���.����
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
		my_log("\t����.ͬ��.\n");
	}
	else
	{
		my_log("\t����.�첽.\n");
	}

	SubscriberAll(pListCodes, bSync, HSUB_ENUM_SUB_OVER/*����*/);
}

/*
	��ʳɽ�.����.����
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
		my_log("\n\t��ʳɽ�.����.ͬ��.\n");
	}
	else
	{
		my_log("\n\t��ʳɽ�.����.�첽.\n");
	}

	SubL2Transcation(pListCodes, bSync, HSUB_ENUM_SUB_OVER/*����*/);
}

/*
	���ί��.����.����
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
		my_log("\n\t���ί��.����.ͬ��.\n");
	}
	else
	{
		my_log("\n\t���ί��.����.�첽.\n");
	}

	SubL2Order(pListCodes, bSync, HSUB_ENUM_SUB_OVER/*����*/);
}


/*
	IP��ַ���л�����
*/
void HqSdkUtil::test_ip_switch(void)
{
	my_log("\n\tIP��ַ���л�����\n");

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

	my_log("\t�л�seesion�е�ip,port. ��ȴ�...\r\n");
	m_pSession->SwitchConnectIndex(2);
}
/*
	�Ͽ����Ӳ���
*/
void HqSdkUtil::test_disconnect(void)
{
	my_log("\n\t�Ͽ����Ӳ���(���ж��ip,������������ip)\n");
	m_pSession->Disconnect();
}
/*
	�ǳ�����
*/
void HqSdkUtil::test_logout(void)
{
	my_log("\t�ǳ�����(logoutʱ��m_pSession������������ܳɹ��������ڲ�����Ϊ�ա�)\n");

	int ret = m_pSession->Logout();
	my_log("\tLogout ����=%d\n", ret);

	//m_pSession�Ѿ�logout. �ٷ�����Ϣ�����յ������ݰ���֮�󣬾�����֤��������
	test_market_type(true);
}

