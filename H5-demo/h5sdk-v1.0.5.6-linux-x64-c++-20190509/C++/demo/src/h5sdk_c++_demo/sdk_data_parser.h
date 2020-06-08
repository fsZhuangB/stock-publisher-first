/** @file
* 行情Demo.SDK使用例子
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
#include "../MyUtil/MyAutoLock.h"
using namespace HsHqSdkDemo;

#include "h5sdk/h5sdk.h"

/*
	sdk数据包
*/
class CSdkPackage
{
public:
	IHsCommMessage *	m_hsMsgPackage;		//回调的数据包
	uint64				m_timeReceived;		//收到数据包的时间
public:
	CSdkPackage(IHsCommMessage* response);
	~CSdkPackage();

	void Handle(void);
};

/*
	SDK回调的数据缓冲
*/
class CSdkPackageQueue
{
public:
	list<CSdkPackage *>	m_listSdkPackage;//数据包。集合
	MyMutex				m_mutex;		 //读写锁。
public:
	CSdkPackageQueue();
	virtual ~CSdkPackageQueue();

	/*
		存入缓冲
	*/
	void Push(IHsCommMessage* response);
	/*
		从缓冲取出.
		取出的指针，需要手动删除
	*/
	CSdkPackage *Pop(void);
};

/*
	SDK缓冲数据处理线程
*/
class SdkBufferHandler : public MyThread
{
public:
	CSdkPackageQueue m_sdkPackageQueue;//缓冲
public:
	/*
		线程入口
	*/
	virtual int MainFun();

public:
	/*
		sdk数据包，存到缓冲中
	*/
	void Store2Buffer(IHsCommMessage* response);

	/*
		从缓冲中取数据
	*/
	CSdkPackage* GetFromBuffer();
};

