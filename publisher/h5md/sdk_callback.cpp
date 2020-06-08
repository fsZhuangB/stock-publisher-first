/** @file
* 行情demo.回调相关
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#include "my_vld.h"

#include "sdk_util.h"
#include "sdk_callback.h"
#include "sdk_util.h"
#include <string.h>
#include "sdk_data_parser.h"
#include "main_message_queue.h"
#include "main_environment.h"

#ifdef WIN32
#undef H5SDKAPI
#define H5SDKAPI
#endif
/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	测试速度，回调。
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
/*
	测速成功
*/
int H5SDKAPI MyVelocimetryCallback::OnVelocimetrySucceed(Endpoint *endpoint, int delay, int load)
{
	if(! endpoint)
	{
		my_log("\tMyVelocimetryCallback::OnVelocimetrySucceed endpoint=null\n");
		return 0;
	}
	my_log("\t%s:\n\t\t测速成功 endpoint=%s delay=%d(命令响应速度.毫秒) load=%d%%(服务器端已使用的资源)\n",__FUNCTION__, endpoint->userData, delay, load);
	return 0;
}

/*
	测速失败
*/
int H5SDKAPI MyVelocimetryCallback::OnVelocimetryFail(Endpoint *endpoint, VelocimetryErrorNo errorNo)
{
	if(! endpoint)
	{
		printf("\tMyVelocimetryCallback::OnVelocimetryFail endpoint=null\n");
		return 0;
	}
	my_log("\t%s:\n\t\t测速失败 endpoint=%s errNo=%d\n",__FUNCTION__, endpoint->userData, errorNo);
	return 0;
}

/*
	测速结束
*/
int H5SDKAPI MyVelocimetryCallback::OnVelocimetryComplete()
{
	my_log("\t%s:\n\t\t测速结束.\n",__FUNCTION__);
	MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_SpeedTest);
	return 0;
}
/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	行情SDK回调
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

/*
	与服务器连接成功.(还没登陆.)
*/
void H5SDKAPI H5SdkCallbackImpl::OnConnect(Session *session, const char *peerIp, int peerPort, const char *localIp, int localPort) 
{
	if(! session)
	{
		printf("\tH5SdkCallbackImpl::OnConnect session=null\n");
		return;
	}
	if(! peerIp)
	{
		printf("\tH5SdkCallbackImpl::OnConnect peerIp=null\n");
		return;
	}
	if(! localIp)
	{
		printf("\tH5SdkCallbackImpl::localIp session=null\n");
		return;
	}
	// 已经建立了Tcp连接
	my_log("\t%s:\n\t\t建立连接 服务器%s:%d 本地%s:%d\n", __FUNCTION__, peerIp, peerPort, localIp, localPort);

	//异步Sdk登录
	session->AsyncSdkLogin(2000/*超时时间, 1秒*/);
}

/*
	SDK登陆入口
*/
void H5SDKAPI H5SdkCallbackImpl::OnSdkLogin(Session *session) 
{
	if(! session)
	{
		my_log("\tH5SdkCallbackImpl::OnSdkLogin session=null\n");
		return;
	}
	// 当Sdk登录成功后回调
	my_log("\t%s:\n\t\tsdk登陆入口\n",__FUNCTION__);

	//用户登陆.同步.
	my_log("\t用户登录开始.\n");
	LoginAnsInfo *lp=session->LoginByUser(MyEnvironment::GetHqSdkUtil()->m_strUser.c_str(), MyEnvironment::GetHqSdkUtil()->m_strPass.c_str());
	if (lp && lp->GetResult() && strcmp(lp->GetResult(),"suc") == 0)
	{
		my_log("\t登录成功.\n");
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Login, (WPARAM)true);
	}
	else
	{
		my_log("\t登录失败.\n");
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Login, (WPARAM)false);
	}
	if(lp)//注意释放
		lp->Release();
}
/*
	推送消息入口.
	所有异步消息回调，行情主推，服务器通知，都进入这里。
	响应必须尽快。否则，sdk可能会因为数据累计太大而出问题。
*/
void H5SDKAPI H5SdkCallbackImpl::OnReceived(Session *session, IHsCommMessage *response) 
{
	if(!session)
	{
		my_log("\tH5SdkCallbackImpl::OnReceived session=null\n");
		return;
	}
	if(!response)
	{
		my_log("\tH5SdkCallbackImpl::OnReceived response=null\n");
		return;
	}

	MyEnvironment::GetSdkBufferHandler()->Store2Buffer(response);
}
/*
	SDK与服务器连接断开.
*/
void H5SDKAPI H5SdkCallbackImpl::OnClose(Session *session, int reason) 
{
	if(!session)
	{
		my_log("\tH5SdkCallbackImpl::OnClose session=null\n");
		return;
	}
	// 当会话连接断开时回调
	my_log("\t%s: close reason=%d\n",__FUNCTION__, reason);

	// 为了实现断开重连，可以在OnClose里发起AsyncConnect调用
	my_log("\tsession断开，重新试着连接\r\n");

	session->AsyncConnect();

}
/*
	session出错
*/
void H5SDKAPI H5SdkCallbackImpl::OnError(Session *session, int errorNo) 
{
	if(!session)
	{
		my_log("\tH5SdkCallbackImpl::OnError session=null\n");
		return;
	}

	// 当会话出错时回调
	my_log("\t%s: onError errNo=%d\n",__FUNCTION__, errorNo);

	my_log("\t重新试着连接\r\n");
	session->AsyncConnect();
}

/*
	连接服务器超时，回调
*/
void H5SDKAPI H5SdkCallbackImpl::OnCore(Session *session) 
{
	if(!session)
	{
		my_log("\tH5SdkCallbackImpl::OnCore session=null\n");
		return;
	}
	// 当会话一直无法连上服务端时回调
	my_log("%s (无法连接服务器.ip错误，或者app_key,app_secret错误，或者网络错误)\r\n",__FUNCTION__);

	// 为了实现继续重连，可以在OnCore里发起AsyncConnect调用
	session->AsyncConnect();
}

