/** @file
* 行情Demo.消息队列
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#pragma once

#include <list>
#include <string>
using namespace std;

#include "../MyUtil/MyThread.h"
#include "../MyUtil/MyEvent.h"
using namespace HsHqSdkDemo;
#include <h5sdk/h5sdk.h>

#ifndef WIN32
#define WPARAM uint32
#define LPARAM uint32
#endif

/*
	消息类型
*/
typedef enum {
	Command_KeyInput, //等待键盘输入
	Command_SdkCallback,//等待SDK回调
} MyCommandType;

/*
	键盘输入类型
*/
#ifdef WIN32
#define Key_Return '\r'
#else
#define Key_Return '\n'
#endif
#define Key_Quit 'Q'


/*
	sdk回调类型
*/
typedef enum {
	SdkCallback_none = 100,

	SdkCallback_Login,	//login
	SdkCallback_SpeedTest,	//速度测试
	SdkCallback_Market_Types,//市场分类信息
	SdkCallback_Candle_By_Offset,//K线
	SdkCallback_Snapshot,	//行情快照
	SdkCallback_Trend,	//分时
	SdkCallback_L2_Transcation,	//逐笔成交
	SdkCallback_L2_Order,	//逐笔委托
	SdkCallback_Server_Info,//服务器信息.市场初始化.
	SdkCallback_Subscribe, //订阅.
	SdkCallback_Subscribe_L2_Transcation, //订阅.逐笔成交
	SdkCallback_Subscribe_L2_Order, //订阅.逐笔委托

	SdkCallback_Snapshot_Capability,	//行情快照.性能
	SdkCallback_Candle_By_Offset_Cabability,//K线.性能
} SdkCallbackType;

class MyMessage
{
public:
	MyCommandType	m_commandType;
	WPARAM			m_wParam;
	LPARAM			m_lParam;
public:
	MyMessage(MyCommandType status, WPARAM wParam, LPARAM lParam) : m_commandType(status), m_wParam(wParam), m_lParam(lParam) {}
	virtual ~MyMessage(){} //子类注意释放内存
};

class MyMessageQueue
{
public:
	list<MyMessage *>	m_listMessage;
	MyEvent				m_eventWait;	//等候信号
	MyMutex				m_mutexData;	//数据锁
public:
	~MyMessageQueue();

	MyMessage *Peek_Message(void);
	void Post_Message(MyCommandType status, WPARAM wParam, LPARAM lParam=0);
};

/*
	键盘输入.线程
*/
class KeyboardInputThread : public MyThread
{
public:
	/*
		线程入口
	*/
	virtual int MainFun();
};
