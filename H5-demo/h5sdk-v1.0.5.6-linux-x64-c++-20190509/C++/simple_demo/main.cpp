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
        // 已经建立了Tcp连接
        puts(__FUNCTION__);

        PRINT(peerIp);
        PRINT(peerPort);
        PRINT(localIp);
        PRINT(localPort);

        // 发起异步Sdk登录
        // 1000为超时时间
        PRINT(session->AsyncSdkLogin(1000));
    }

    void H5SDKAPI OnSdkLogin(Session *session) {
        // 当Sdk登录成功后回调
        puts(__FUNCTION__);

		//需要填入对应的用户名和密码
		LoginAnsInfo *lp=session->LoginByUser("anyone","anyone");
		if (lp && !strcmp(lp->GetResult(),"suc"))
		{
			//登录成功
			printf("session[%p]登录成功\n", session);
		}
		else
		{
			printf("session[%p]异步发起业务登录失败\n", session);
		}
		
    }

    void H5SDKAPI OnReceived(Session *session, IHsCommMessage *response) {
        // 当会话收到异步应答时会触发该回调
        puts(__FUNCTION__);

        // 判断是否执行成功
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
					//主推处理
				}
				else
				{
					//请求实时行情处理
				}
				break;
			}
		case H5SDK_MSG_MARKET_TYPES: // 市场分类信息
			{
				// 开始解析市场分类信息
				// 因为字段H5SDK_FINANCE_MIC_GRP为sequence, 先获取IGroup句柄
				IGroup *finance_mic_grp = response->GetGroup(H5SDK_FINANCE_MIC_GRP);
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

					// 因为H5SDK_TAG_TYPE_GRP类型为sequence, 所以先必须获取IGroup句柄
					IGroup *type_grp = finance_mic_record->GetGroup(H5SDK_TAG_TYPE_GRP);
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
						// 同理可解析余下字段, 注意字段类型是sequence的解析
					}
				}
			}
			break;

		default:
			{
				//其他业务处理;
			}
		}
		

        response->Release();

        // 可以在这里发起其他业务请求
    }

    void H5SDKAPI OnClose(Session *session, int reason) {
        // 当会话连接断开时回调
        puts(__FUNCTION__);

		printf("OnClose reason%d", reason);

        // 为了实现断开重连，可以在OnClose里发起AsyncConnect调用
        session->AsyncConnect();
    }

    void H5SDKAPI OnError(Session *session, int errorNo) {
        // 当会话出错时回调
        puts(__FUNCTION__);
        // 打印错误号
        PRINT(errorNo);
    }

    void H5SDKAPI OnCore(Session *session) {
        // 当会话一直无法连上服务端时回调
        puts(__FUNCTION__);
        // 为了实现继续重连，可以在OnCore里发起AsyncConnect调用
        session->AsyncConnect();
    }
};

int main()
{

	//////////////////////////////////////////////////////////////////////////
	// 1. 演示测速
	//////////////////////////////////////////////////////////////////////////
#if 0
    // 演示测速
    Endpoint endpoint[3];

    strcpy(endpoint[0].ip, "121.43.71.217");
    endpoint[0].port = 9999;
    strcpy(endpoint[0].userData, "测试服务器");

    strcpy(endpoint[1].ip, "127.0.0.1");
    endpoint[1].port = 9999;
    strcpy(endpoint[1].userData, "端口未打开");

    strcpy(endpoint[2].ip, "192.168.94.200");
    endpoint[2].port = 9999;
    strcpy(endpoint[2].userData, "不可达服务器");

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
	// 2. 设置环境变量
	//////////////////////////////////////////////////////////////////////////
#if 1
	
	//设置SDK日志路径
	SetH5DataPath("h5data");
	//设置SDK日志路径
	SetH5LogPath("H5LOG");
	//设置日志级别配置路径
	SetSdkParamPath("SdkParamPath.json");
#endif




	//////////////////////////////////////////////////////////////////////////
	// 3. 会话创建
	//示例代码为创建两个会话，其中会话0为普通协议，会话1使用best协议
	//////////////////////////////////////////////////////////////////////////
    // 创建会话选项1
	 SessionOptions *sessionOptions[2];
	 Session *session[2];
#if 1
	 //创建会话1
    sessionOptions[0] = CreateSessionOptions();
     sessionOptions[0]->AddRef();

    // 设置会话选项1
     sessionOptions[0]->SetHeartbeatTimeout(3);

	//设置两组ip和端口
     sessionOptions[0]->SetServerIp("10.20.135.126");
     sessionOptions[0]->SetServerPort(9999);

	 sessionOptions[0]->SetServerIp("121.43.71.218",1);
	 sessionOptions[0]->SetServerPort(9999,1);

    // 创建会话
	session[0] = CreateSession( sessionOptions[0]);
    session[0]->AddRef();
	//
	session[0]->SetAppInfo("app_key","app_secret");
#endif

#if 1
	//创建会话2
	sessionOptions[1] = CreateSessionOptions();
	sessionOptions[1]->AddRef();

	// 设置会话选项2
	sessionOptions[1]->SetHeartbeatTimeout(3);

	//设置ip和端口
	sessionOptions[1]->SetServerIp("10.20.27.193",0);
	sessionOptions[1]->SetServerPort(9601,0);

	// 创建会话
	session[1] = CreateSession( sessionOptions[1]);
	session[1]->AddRef();
	session[1]->SetAppInfo("app_key","app_secret");

	//设置使用best协议
	session[1]->SetBestProtocol(true);
#endif

    // 开始为所有会话设置回调
    StartSetCallback();

    // 设置回调
    H5SdkCallbackImpl h5SdkCallbackImpl;
	//两个会话可使用同一个回调类，也可以使用不同的回调类
	for (int i=0;i<2;i++)
	{
		session[i]->SetCallback(&h5SdkCallbackImpl);
	}

	//首次启动时，不会自动连接，需要后面手工连接[除非特别需要，不需要调用此函数]
	//SetInitAutoConnectFlag(false);

	//设置代理
	//SetProxyOptions(SDKHTTPPROXY, "10.26.210.42", 808, "test", "test");

    // 启动所有会话
    StartAllSessions();
	//////////////////////////////////////////////////////////////////////////
	// 4. 创建请求报文
	//////////////////////////////////////////////////////////////////////////
#if 1
	getchar();
	// 创建请求报文, 请求"市场分类信息"
	IHsCommMessage *request = session[0]->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_MARKET_TYPES, REQUEST);
	if (NULL == request)
	{
		printf("create message fail\n");
		return -1;
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



	//////////////////////////////////////////////////////////////////////////
	// 5. 同步请求和异步请求
	//////////////////////////////////////////////////////////////////////////
#if 0
	//异步发送在回调函数中处理，同步发送在此函数中处理
	session[0]->AsyncSend(request);
#else
	IHsCommMessage *ansMsg =NULL;
	int ret = session[0]->SyncCall(request,&ansMsg,3000);
	if (ret ==0 && ansMsg)
	{
		// 开始解析市场分类信息
		// 因为字段H5SDK_FINANCE_MIC_GRP为sequence, 先获取IGroup句柄
		IGroup *finance_mic_grp = ansMsg->GetGroup(H5SDK_FINANCE_MIC_GRP);
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

			// 因为H5SDK_TAG_TYPE_GRP类型为sequence, 所以先必须获取IGroup句柄
			IGroup *type_grp = finance_mic_record->GetGroup(H5SDK_TAG_TYPE_GRP);
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
				// 同理可解析余下字段, 注意字段类型是sequence的解析
			}
		}
		ansMsg->Release();
	}
	else
	{
		printf("同步请求错误 ret %d",ret);
	}
#endif
	// 释放消息
	request->Release();

	

#endif

	//////////////////////////////////////////////////////////////////////////
	// 6. IP地址和切换测试
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
	// 7. 登出测试
	//////////////////////////////////////////////////////////////////////////
#if 1
	getchar();
	int logoutcallret = session[0]->Logout();
	printf("\n ---- Logout test %d\n", logoutcallret);

	// 创建请求报文, 请求"市场分类信息"
	IHsCommMessage *logoutrequest = session[0]->CreateMessage(BIZ_H5PROTO, H5SDK_MSG_MARKET_TYPES, REQUEST);
	// 根据H5SDK_FINANCE_MIC_GRP字段类型为sequence, 创建IGroup句柄
	IGroup *logoutgroup = logoutrequest->SetGroup(H5SDK_FINANCE_MIC_GRP);
	// 为H5SDK_FINANCE_MIC_GRP添加第一条记录
	IRecord *logoutrecord = logoutgroup->AddRecord();
	// 为第一条记录的字段H5SDK_TAG_FINANCE_MIC设置值"SS", H5SDK_TAG_FINANCE_MIC字段类型为bytevector, 故调用SetString, 传入字符串值
	logoutrecord->GetItem(H5SDK_TAG_FINANCE_MIC)->SetString("SS");
	// 为H5SDK_FINANCE_MIC_GRP添加第二条记录
	logoutrecord = logoutgroup->AddRecord();
	// 为第二条记录的字段H5SDK_TAG_FINANCE_MIC设置值"SZ"
	logoutrecord->GetItem(H5SDK_TAG_FINANCE_MIC)->SetString("SZ");
	
	IHsCommMessage *ansLogoutMsg =NULL;
	int logutret = session[0]->SyncCall(logoutrequest,&ansLogoutMsg,3000);
	if (logutret ==0 && ansLogoutMsg)
	{		
		int logouterrno= ansLogoutMsg->GetHead()->GetItem(H5PROTO_TAG_ERROR_NO)->GetInt32();

		const char * logouterrstr = ansLogoutMsg->GetHead()->GetItem(H5PROTO_TAG_ERROR_INFO)->GetString();

		printf("登出请求失败 错误码:%d 错误描述:%s\n" ,logouterrno, logouterrstr);

		ansLogoutMsg->Release();
	}
	else
	{
		printf("同步请求错误 ret %d", logutret);
	}

#endif

	////////////////////////////////////////////////////////////////////////////////
	// 8. 断开连接测试 ， 查看close回调方法，及回调方法返回的reason值,是否为手动断开
	////////////////////////////////////////////////////////////////////////////////
#if 1
	getchar();
	session[0]->Disconnect();
	printf("\n ---- Disconnect test\n");

#endif

    // 等待回调触发
    getchar();
	StopAllSessions();
    return 0;

}
