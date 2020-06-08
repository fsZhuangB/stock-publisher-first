#include <list>
#include <string>
using namespace std;

#include "../MyUtil/MyThread.h"
#include "../MyUtil/MyEvent.h"
#include "../MyUtil/MyAutoLock.h"
using namespace HsHqSdkDemo;

#include "h5sdk/h5sdk.h"

// sdk data bag
class CSdkPackage
{
    public:
    IHsCommMessage* m_hsMsgPackage;
    uint64          m_timeReceived;

    public:
    CSdkPackage(IHsCommMessage* response);
    ~CSdkPackage();

    void Handle(void);
};

// SDK callback data buffer
class CSdkPackageQueue
{
    public:
    list<CSdkPackage*> m_listSdkPackage;
    MyMutex            m_mutex;

    public:
    CSdkPackageQueue();
    virtual ~CSdkPackageQueue();
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