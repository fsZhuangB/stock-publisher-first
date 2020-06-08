#include "sdk_util.h"
#include "main_message_queue.h"

class SdkBufferHandler;
class KeyboardInputThread;

/**
 * callback function
*/
typedef bool (*MyFuncCallBack)(void);

// the message to wait
class MyMessageWaitFor : public MyMessage {
    public:
    // public member
    MyFuncCallBack m_funcCallBack;
    public:
    MyMessageWaitFor(MyCommandType type, WPARAM w, LPARAM l, MyFuncCallBack callback)
        : MyMessage(type, w, l), m_funcCallBack(callback)
        {}
};

class MyEnvironment
{
    public:
    // wait queue
    list<MyMessageWaitFor*> m_listCommand;
    static list<MyProdCode> m_listCodes;
    static HqSdkUtil* m_pHqSdkUtil;
    static MyMessageQueue* m_pMainMessageQueue;
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

    // wait for message: 1. keyboard message
    //                   2. SDK callback message
    void WaitForMessage(MyCommandType common_type, int wParam, MyFuncCallBack callback);

    // wait for message and handle
    bool WaitForMessageAndHandleIt(MyMessage* pMessage);

    int GetWaitForMessageSize();

    static bool OnLoginOver(void);
    static bool PrintWaitForEnter();
    static bool OnSpeedTestOver(void);
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

    // this file will call the message queue file
	static HqSdkUtil *GetHqSdkUtil(); //行情SDK工具类
	static void PostMainMessage(MyCommandType status, WPARAM wParam, LPARAM lParam=0);
	static MyMessage *PeekMainMessage(void);
	static SdkBufferHandler * GetSdkBufferHandler(void);
	static KeyboardInputThread * GetKeyboardInputThread(void);
};