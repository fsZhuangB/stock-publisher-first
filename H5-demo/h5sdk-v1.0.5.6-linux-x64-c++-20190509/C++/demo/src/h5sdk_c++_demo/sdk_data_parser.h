/** @file
* ����Demo.SDKʹ������
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/
#pragma once

#include <list>
#include <string>
using namespace std;

#include "../MyUtil/MyThread.h"
#include "../MyUtil/MyEvent.h"
#include "../MyUtil/MyAutoLock.h"
using namespace HsHqSdkDemo;

#include "h5sdk/h5sdk.h"

/*
	sdk���ݰ�
*/
class CSdkPackage
{
public:
	IHsCommMessage *	m_hsMsgPackage;		//�ص������ݰ�
	uint64				m_timeReceived;		//�յ����ݰ���ʱ��
public:
	CSdkPackage(IHsCommMessage* response);
	~CSdkPackage();

	void Handle(void);
};

/*
	SDK�ص������ݻ���
*/
class CSdkPackageQueue
{
public:
	list<CSdkPackage *>	m_listSdkPackage;//���ݰ�������
	MyMutex				m_mutex;		 //��д����
public:
	CSdkPackageQueue();
	virtual ~CSdkPackageQueue();

	/*
		���뻺��
	*/
	void Push(IHsCommMessage* response);
	/*
		�ӻ���ȡ��.
		ȡ����ָ�룬��Ҫ�ֶ�ɾ��
	*/
	CSdkPackage *Pop(void);
};

/*
	SDK�������ݴ����߳�
*/
class SdkBufferHandler : public MyThread
{
public:
	CSdkPackageQueue m_sdkPackageQueue;//����
public:
	/*
		�߳����
	*/
	virtual int MainFun();

public:
	/*
		sdk���ݰ����浽������
	*/
	void Store2Buffer(IHsCommMessage* response);

	/*
		�ӻ�����ȡ����
	*/
	CSdkPackage* GetFromBuffer();
};

