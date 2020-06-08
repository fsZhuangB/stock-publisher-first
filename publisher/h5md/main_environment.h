/** @file
* 行情Demo.模拟环境
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#pragma once

#include "sdk_util.h"
#include "main_message_queue.h"
class SdkBufferHandler;
class KeyboardInputThread;


/*
	自定消息里，回调函数.
	返回false,不再继续。
*/
typedef bool (*MyFuncCallback)(void);

/*
	需要等待的消息
*/
class MyMessageWaitFor : public MyMessage
{
public:
	MyFuncCallback		m_funcCallback;		//等到动作到来后，需要做的事情。
public:
	MyMessageWaitFor(MyCommandType type, WPARAM w, LPARAM l, MyFuncCallback callback)
		: MyMessage(type, w, l), m_funcCallback(callback)
	{
	}
};

/*
	模拟主线程环境
*/
class MyEnvironment
{
public:
	list<MyMessageWaitFor *> m_listCommand;  //等待队列.当前正在期待的动作。主线程处理，不必加锁。

	static list<MyProdCode>	m_listCodes; //当前正在使用的代码。主线程处理，不必加锁。

	static HqSdkUtil *m_pHqSdkUtil; //行情SDK工具类
	static MyMessageQueue * m_pMainMessageQueue;		//消息队列
	static SdkBufferHandler * m_pSdkBufferHandler; //缓冲线程
	static KeyboardInputThread * m_pKeyboardInputThread;//键盘输入线程

public:
	MyEnvironment();

	/*
		环境清理
	*/
	~MyEnvironment();

	/*
		清理内存
	*/
	void Clear();

	/*
		初始化环境
	*/
	bool Init(void);

	/*
		设置:等待的消息。
		等待键盘消息，或SDK回调消息。
	*/
	void WaitForMessage(MyCommandType commandType, int wParam, MyFuncCallback callback);

	/*
		等候指定消息，并做特定处理
	*/
	bool WaitforMessageAndHandleIt(MyMessage *pMessage);

	/*
		等候的消息size.
	*/
	int	GetWaitforMessageSize();

	/*
		登陆结束.回调
	*/
	static bool OnLoginOver(void);

	/*
		速度测试结束.回调
	*/
	static bool OnSpeedTestOver(void);

	/*
		打印信息.回调
	*/
	static bool PrintWaitForEnter();
	
	/*
		退出订阅模式.回调
	*/
	static bool OnSubscribeOver();

	/*
		退出订阅模式.回调
	*/
	static bool OnSubscribeL2TranscationOver();

	/*
		退出订阅模式.回调
	*/
	static bool OnSubscribeL2OrderOver();

	/*
		退出性能测试.回调
	*/
	static bool OnCapabilityOver();

	/*
		打印菜单
	*/
	static bool PrintMenu(void);

	/*
		主菜单。
		返回true，继续。
		返回false,退出程序
	*/
	bool SelectMenu(char ch);

	//
	static HqSdkUtil *GetHqSdkUtil(); //行情SDK工具类
	static void PostMainMessage(MyCommandType status, WPARAM wParam, LPARAM lParam=0);
	static MyMessage *PeekMainMessage(void);
	static SdkBufferHandler * GetSdkBufferHandler(void);
	static KeyboardInputThread * GetKeyboardInputThread(void);
};
