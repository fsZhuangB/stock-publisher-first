/** @file
* ����Demo.ģ�⻷��
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/
#pragma once

#include "sdk_util.h"
#include "main_message_queue.h"
class SdkBufferHandler;
class KeyboardInputThread;


/*
	�Զ���Ϣ��ص�����.
	����false,���ټ�����
*/
typedef bool (*MyFuncCallback)(void);

/*
	��Ҫ�ȴ�����Ϣ
*/
class MyMessageWaitFor : public MyMessage
{
public:
	MyFuncCallback		m_funcCallback;		//�ȵ�������������Ҫ�������顣
public:
	MyMessageWaitFor(MyCommandType type, WPARAM w, LPARAM l, MyFuncCallback callback)
		: MyMessage(type, w, l), m_funcCallback(callback)
	{
	}
};

/*
	ģ�����̻߳���
*/
class MyEnvironment
{
public:
	list<MyMessageWaitFor *> m_listCommand;  //�ȴ�����.��ǰ�����ڴ��Ķ��������̴߳������ؼ�����

	static list<MyProdCode>	m_listCodes; //��ǰ����ʹ�õĴ��롣���̴߳������ؼ�����

	static HqSdkUtil *m_pHqSdkUtil; //����SDK������
	static MyMessageQueue * m_pMainMessageQueue;		//��Ϣ����
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

	/*
		����:�ȴ�����Ϣ��
		�ȴ�������Ϣ����SDK�ص���Ϣ��
	*/
	void WaitForMessage(MyCommandType commandType, int wParam, MyFuncCallback callback);

	/*
		�Ⱥ�ָ����Ϣ�������ض�����
	*/
	bool WaitforMessageAndHandleIt(MyMessage *pMessage);

	/*
		�Ⱥ����Ϣsize.
	*/
	int	GetWaitforMessageSize();

	/*
		��½����.�ص�
	*/
	static bool OnLoginOver(void);

	/*
		�ٶȲ��Խ���.�ص�
	*/
	static bool OnSpeedTestOver(void);

	/*
		��ӡ��Ϣ.�ص�
	*/
	static bool PrintWaitForEnter();
	
	/*
		�˳�����ģʽ.�ص�
	*/
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

	//
	static HqSdkUtil *GetHqSdkUtil(); //����SDK������
	static void PostMainMessage(MyCommandType status, WPARAM wParam, LPARAM lParam=0);
	static MyMessage *PeekMainMessage(void);
	static SdkBufferHandler * GetSdkBufferHandler(void);
	static KeyboardInputThread * GetKeyboardInputThread(void);
};
