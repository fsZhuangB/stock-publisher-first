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