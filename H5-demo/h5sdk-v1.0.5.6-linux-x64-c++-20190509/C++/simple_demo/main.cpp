#include <iostream>
#include <string.h>
using namespace std;

#include "h5sdk.h"

#define PRINT(a)\
    cout << #a << " = " << (a) << endl

class MyVelocimetryCallback: public VelocimetryCallback
{
public:
    int H5SDKAPI OnVelocimetrySucceed(Endpoint *endpoint, int delay, int load)
    {
        cout << __FUNCTION__ << endl;

        PRINT(endpoint->userData);
        PRINT(delay);
        PRINT(load);

        return 0;
    }

    int H5SDKAPI OnVelocimetryFail(Endpoint *endpoint, VelocimetryErrorNo errorNo)
    {
        cout << __FUNCTION__ << endl;

        PRINT(endpoint->userData);
        PRINT(errorNo);

        return 0;
    }

    int H5SDKAPI OnVelocimetryComplete()
    {
        cout << __FUNCTION__ << endl;
        return 0;
    }
};

class H5SdkCallbackImpl: public H5SdkCallback {
public:
    void H5SDKAPI OnConnect(Session *session, const char *peerIp, int peerPort, const char *localIp, int localPort) {
        // �Ѿ�������Tcp����
        puts(__FUNCTION__);

        PRINT(peerIp);
        PRINT(peerPort);
        PRINT(localIp);
        PRINT(localPort);

        // �����첽Sdk��¼
        // 1000Ϊ��ʱʱ��
        PRINT(session->AsyncSdkLogin(1000));
    }

    void H5SDKAPI OnSdkLogin(Session *session) {
        // ��Sdk��¼�ɹ���ص�
        puts(__FUNCTION__);

		//��Ҫ�����Ӧ���û���������
		LoginAnsInfo *lp=session->LoginByUser("anyone","anyone");
		if (lp && !strcmp(lp->GetResult(),"suc"))
		{
			//��¼�ɹ�
			printf("session[%p]��¼�ɹ�\n", session);
		}
		else
		{
			printf("session[%p]�첽����ҵ���¼ʧ��\n", session);
		}
		
    }

    void H5SDKAPI OnReceived(Session *session, IHsCommMessage *response) {
        // ���Ự�յ��첽Ӧ��ʱ�ᴥ���ûص�
        puts(__FUNCTION__);

        // �ж��Ƿ�ִ�гɹ�
        int headErrorNo = response->GetHead()->GetItem(H5PROTO_TAG_ERROR_NO)->GetInt32();
        if (headErrorNo != 0)
        {
            cout << "headErrorNo = " << headErrorNo << endl;
        }

        const char *userKey = response->GetHead()->GetItem(H5PROTO_TAG_USER_KEY)->GetString();

        PRINT(userKey);
		int fucid = response->GetFunction();
		switch (fucid)
		{
		case H5SDK_MSG_SNAPSHOT:
			//
			{
				if (response->GetPacketType() == PUSH)
				{
					//���ƴ���
				}
				else
				{
					//����ʵʱ���鴦��
				}
				break;
			}
		case H5SDK_MSG_MARKET_TYPES: // �г�������Ϣ
			{
				// ��ʼ�����г�������Ϣ
				// ��Ϊ�ֶ�H5SDK_FINANCE_MIC_GRPΪsequence, �Ȼ�ȡIGroup���
				IGroup *finance_mic_grp = response->GetGroup(H5SDK_FINANCE_MIC_GRP);
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

					// ��ΪH5SDK_TAG_TYPE_GRP����Ϊsequence, �����ȱ����ȡIGroup���
					IGroup *type_grp = finance_mic_record->GetGroup(H5SDK_TAG_TYPE_GRP);
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
						// ͬ��ɽ��������ֶ�, ע���ֶ�������sequence�Ľ���
					}
				}
			}
			break;

		default:
			{
				//����ҵ����;
			}
		}
		

        response->Release();

        // ���������﷢������ҵ������
    }

    void H5SDKAPI OnClose(Session *session, int reason) {
        // ���Ự���ӶϿ�ʱ�ص�
        puts(__FUNCTION__);

		printf("OnClose reason%d", reason);

        // Ϊ��ʵ�ֶϿ�������������OnClose�﷢��AsyncConnect����
        session->AsyncConnect();
    }

    void H5SDKAPI OnError(Session *session, int errorNo) {
        // ���Ự����ʱ�ص�
        puts(__FUNCTION__);
        // ��ӡ�����
        PRINT(errorNo);
    }

    void H5SDKAPI OnCore(Session *session) {
        // ���Ựһֱ�޷����Ϸ����ʱ�ص�
        puts(__FUNCTION__);
        // Ϊ��ʵ�ּ���������������OnCore�﷢��AsyncConnect����
        session->AsyncConnect();
    }
};

int main()
{

	//////////////////////////////////////////////////////////////////////////
	// 1. ��ʾ����
	//////////////////////////////////////////////////////////////////////////
#if 0
    // ��ʾ����
    Endpoint endpoint[3];

    strcpy(endpoint[0].ip, "121.43.71.217");
    endpoint[0].port = 9999;
    strcpy(endpoint[0].userData, "���Է�����");

    strcpy(endpoint[1].ip, "127.0.0.1");
    endpoint[1].port = 9999;
    strcpy(endpoint[1].userData, "�˿�δ��");

    strcpy(endpoint[2].ip, "192.168.94.200");
    endpoint[2].port = 9999;
    strcpy(endpoint[2].userData, "���ɴ������");

    MyVelocimetryCallback myVelocimetryCallback;

    Velocimetry *velocimetry = CreateVelocimetry();

    velocimetry->AddRef();
    velocimetry->Start(endpoint, 3, &myVelocimetryCallback, 3000);

    getchar();

    velocimetry->Stop();
    velocimetry->Release();

    return 0;
#endif


	//////////////////////////////////////////////////////////////////////////
	// 2. ���û�������
	//////////////////////////////////////////////////////////////////////////
#if 1
	
	//����SDK��־·��
	SetH5DataPath("h5data");
	//����SDK��־·��
	SetH5LogPath("H5LOG");
	//������־��������·��
	SetSdkParamPath("SdkParamPath.json");
#endif




	//////////////////////////////////////////////////////////////////////////
	// 3. �Ự����
	//ʾ������Ϊ���������Ự�����лỰ0Ϊ��ͨЭ�飬�Ự1ʹ��bestЭ��
	//////////////////////////////////////////////////////////////////////////
    // �����Ựѡ��1
	 SessionOptions *sessionOptions[2];
	 Session *session[2];
#if 1
	 //�����Ự1
    sessionOptions[0] = CreateSessionOptions();
     sessionOptions[0]->AddRef();

    // ���ûỰѡ��1
     sessionOptions[0]->SetHeartbeatTimeout(3);

	//��������ip�Ͷ˿�
     sessionOptions[0]->SetServerIp("10.20.135.126");
     sessionOptions[0]->SetServerPort(9999);

	 sessionOptions[0]->SetServerIp("121.43.71.218",1);
	 sessionOptions[0]->SetServerPort(9999,1);

    // �����Ự
	session[0] = CreateSession( sessionOptions[0]);
    session[0]->AddRef();
	//
	session[0]->SetAppInfo("app_key","app_secret");
#endif

#if 1
	//�����Ự2
	sessionOptions[1] = CreateSessionOptions();
	sessionOptions[1]->AddRef();

	// ���ûỰѡ��2
	sessionOptions[1]->SetHeartbeatTimeout(3);

	//����ip�Ͷ˿�
	sessionOptions[1]->SetServerIp("10.20.27.193",0);
	sessionOptions[1]->SetServerPort(9601,0);

	// �����Ự
	session[1] = CreateSession( sessionOptions[1]);
	session[1]->AddRef();
	session[1]->SetAppInfo("app_key","app_secret");

	//����ʹ��bestЭ��
	session[1]->SetBestProtocol(true);
#endif

    // ��ʼΪ���лỰ���ûص�
    StartSetCallback();

    // ���ûص�
    H5SdkCallbackImpl h5SdkCallbackImpl;
	//�����Ự��ʹ��ͬһ���ص��࣬Ҳ����ʹ�ò�ͬ�Ļص���
	for (int i=0;i<2;i++)
	{
		session[i]->SetCallback(&h5SdkCallbackImpl);
	}

	//�״�����ʱ�������Զ����ӣ���Ҫ�����ֹ�����[�����ر���Ҫ������Ҫ���ô˺���]
	//SetInitAutoConnectFlag(false);

	//���ô���
	//SetProxyOptions(SDKHTTPPROXY, "10.26.210.42", 808, "test", "test");

    // �������лỰ
    StartAllSessions();
	//////////////////////////////////////////////////////////////////////////
	// 4. ����������
	//////////////////////////////////////////////////////////////////////////
#if 1
	getchar();
	// ����������, ����"�г�������Ϣ"
	IHsCommMessage *request = session[0]->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_MARKET_TYPES, REQUEST);
	if (NULL == request)
	{
		printf("create message fail\n");
		return -1;
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



	//////////////////////////////////////////////////////////////////////////
	// 5. ͬ��������첽����
	//////////////////////////////////////////////////////////////////////////
#if 0
	//�첽�����ڻص������д���ͬ�������ڴ˺����д���
	session[0]->AsyncSend(request);
#else
	IHsCommMessage *ansMsg =NULL;
	int ret = session[0]->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		// ��ʼ�����г�������Ϣ
		// ��Ϊ�ֶ�H5SDK_FINANCE_MIC_GRPΪsequence, �Ȼ�ȡIGroup���
		IGroup *finance_mic_grp = ansMsg->GetGroup(H5SDK_FINANCE_MIC_GRP);
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

			// ��ΪH5SDK_TAG_TYPE_GRP����Ϊsequence, �����ȱ����ȡIGroup���
			IGroup *type_grp = finance_mic_record->GetGroup(H5SDK_TAG_TYPE_GRP);
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
				// ͬ��ɽ��������ֶ�, ע���ֶ�������sequence�Ľ���
			}
		}
		ansMsg->Release();
	}
	else
	{
		printf("ͬ��������� ret %d",ret);
	}
#endif
	// �ͷ���Ϣ
	request->Release();

	

#endif

	//////////////////////////////////////////////////////////////////////////
	// 6. IP��ַ���л�����
	//////////////////////////////////////////////////////////////////////////
#if 0
	
	getchar();
	char addr[100] = {0};
	uint16 myport = 0;
	session[0]->GetIpAndPort(0, addr, &myport);
	printf("\n ---- GetIpAndPort test addr = %s myport = %d\n", addr, myport);

	session[0]->AddIpAndPort("3.1.2.3", 33);
	session[0]->GetIpAndPort(2, addr, &myport);
	printf("---- AddIpAndPort test addr = %s myport = %d\n", addr, myport);

	session[0]->ChangeIpAndPort(2, "112.124.211.5", 9999);
	session[0]->GetIpAndPort(2, addr, &myport);
	printf("---- ChangeIpAndPort test addr = %s myport = %d\n", addr, myport);

	int addCount = session[0]->GetAddressCount();
	printf("---- GetAddressCount test count = %d\n", addCount);
	for (int i = 0; i< addCount; i++)
	{
		session[0]->GetIpAndPort(i, addr, &myport);
		printf("---- index = %d addr = %s myport = %d\n", i, addr, myport);
	}

	session[0]->SwitchConnectIndex(2);

#endif

	//////////////////////////////////////////////////////////////////////////
	// 7. �ǳ�����
	//////////////////////////////////////////////////////////////////////////
#if 1
	getchar();
	int logoutcallret = session[0]->Logout();
	printf("\n ---- Logout test %d\n", logoutcallret);

	// ����������, ����"�г�������Ϣ"
	IHsCommMessage *logoutrequest = session[0]->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_MARKET_TYPES, REQUEST);
	// ����H5SDK_FINANCE_MIC_GRP�ֶ�����Ϊsequence, ����IGroup���
	IGroup *logoutgroup = logoutrequest->SetGroup(H5SDK_FINANCE_MIC_GRP);
	// ΪH5SDK_FINANCE_MIC_GRP��ӵ�һ����¼
	IRecord *logoutrecord = logoutgroup->AddRecord();
	// Ϊ��һ����¼���ֶ�H5SDK_TAG_FINANCE_MIC����ֵ"SS", H5SDK_TAG_FINANCE_MIC�ֶ�����Ϊbytevector, �ʵ���SetString, �����ַ���ֵ
	logoutrecord->GetItem(H5SDK_TAG_FINANCE_MIC)->SetString("SS");
	// ΪH5SDK_FINANCE_MIC_GRP��ӵڶ�����¼
	logoutrecord = logoutgroup->AddRecord();
	// Ϊ�ڶ�����¼���ֶ�H5SDK_TAG_FINANCE_MIC����ֵ"SZ"
	logoutrecord->GetItem(H5SDK_TAG_FINANCE_MIC)->SetString("SZ");
	
	IHsCommMessage *ansLogoutMsg =NULL;
	int logutret = session[0]->SyncCall(logoutrequest,&ansLogoutMsg,3000);
	if (logutret ==0 && ansLogoutMsg)
	{		
		int logouterrno= ansLogoutMsg->GetHead()->GetItem(H5PROTO_TAG_ERROR_NO)->GetInt32();

		const char * logouterrstr = ansLogoutMsg->GetHead()->GetItem(H5PROTO_TAG_ERROR_INFO)->GetString();

		printf("�ǳ�����ʧ�� ������:%d ��������:%s\n" ,logouterrno, logouterrstr);

		ansLogoutMsg->Release();
	}
	else
	{
		printf("ͬ��������� ret %d", logutret);
	}

#endif

	////////////////////////////////////////////////////////////////////////////////
	// 8. �Ͽ����Ӳ��� �� �鿴close�ص����������ص��������ص�reasonֵ,�Ƿ�Ϊ�ֶ��Ͽ�
	////////////////////////////////////////////////////////////////////////////////
#if 1
	getchar();
	session[0]->Disconnect();
	printf("\n ---- Disconnect test\n");

#endif

    // �ȴ��ص�����
    getchar();
	StopAllSessions();
    return 0;

}
