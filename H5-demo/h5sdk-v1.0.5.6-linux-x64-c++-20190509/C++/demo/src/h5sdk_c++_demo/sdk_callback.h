/** @file
* 行情demo.回调相关
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/

#pragma once

#include <string>
using namespace std;
#include "h5sdk/h5sdk.h"
/*
	测试速度，回调。
*/
class MyVelocimetryCallback: public VelocimetryCallback
{
public:
	/*
		测速成功
	*/
	int H5SDKAPI OnVelocimetrySucceed(Endpoint *endpoint, int delay, int load);

	/*
		测速失败
	*/
	int H5SDKAPI OnVelocimetryFail(Endpoint *endpoint, VelocimetryErrorNo errorNo);
	/*
		测速结束
	*/
	int H5SDKAPI OnVelocimetryComplete();
};

/*
	行情SDK回调
*/
class H5SdkCallbackImpl: public H5SdkCallback 
{
public:
	/*
		与服务器连接成功.(还没登陆.)
	*/
	void H5SDKAPI OnConnect(Session *session, const char *peerIp, int peerPort, const char *localIp, int localPort);
	/*
		SDK登陆入口
	*/
	void H5SDKAPI OnSdkLogin(Session *session);
	/*
		推送消息入口.
		所有异步消息回调，行情主推，服务器通知，都进入这里。
		响应必须尽快。否则，sdk可能会因为数据累计太大而出问题。
	*/
	void H5SDKAPI OnReceived(Session *session, IHsCommMessage *response);
	/*
		SDK与服务器连接断开.
	*/
	void H5SDKAPI OnClose(Session *session, int reason);
	/*
		session出错
	*/
	void H5SDKAPI OnError(Session *session, int errorNo);
	/*
		连接服务器超时，回调
	*/
	void H5SDKAPI OnCore(Session *session);

};