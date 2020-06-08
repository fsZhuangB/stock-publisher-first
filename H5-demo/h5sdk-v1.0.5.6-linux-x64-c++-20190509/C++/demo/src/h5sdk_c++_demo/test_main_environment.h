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
    static SdkBufferHandler * m_pSdkBufferHandler; //�����߳�
	static KeyboardInputThread * m_pKeyboardInputThread;//���������߳�

public:
	MyEnvironment();

	/*
		��������
	*/
	~MyEnvironment();

	/*
		�����ڴ�
	*/
	void Clear();

	/*
		��ʼ������
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
		�˳�����ģʽ.�ص�
	*/
	static bool OnSubscribeL2TranscationOver();

	/*
		�˳�����ģʽ.�ص�
	*/
	static bool OnSubscribeL2OrderOver();

	/*
		�˳����ܲ���.�ص�
	*/
	static bool OnCapabilityOver();

	/*
		��ӡ�˵�
	*/
	static bool PrintMenu(void);

	/*
		���˵���
		����true��������
		����false,�˳�����
	*/
	bool SelectMenu(char ch);

    // this file will call the message queue file
	static HqSdkUtil *GetHqSdkUtil(); //����SDK������
	static void PostMainMessage(MyCommandType status, WPARAM wParam, LPARAM lParam=0);
	static MyMessage *PeekMainMessage(void);
	static SdkBufferHandler * GetSdkBufferHandler(void);
	static KeyboardInputThread * GetKeyboardInputThread(void);
};