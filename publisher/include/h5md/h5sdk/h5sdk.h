#ifndef __H5SDK_H__
#define __H5SDK_H__

#include "h5sdk_export.h"
#include "velocimetry.h"

#include <Include/hscomm_message_factory_interface.h>
#include <Include/hscomm_message_interface.h>
#include <Include/sdk_tag.h>
#include "vector"
#include <string>
using namespace std;

enum SDKProxyType
{
	SDKINVALIDPROXY = 0,
	SDKHTTPPROXY = 1,
	SDKSOCKET4PROXY = 2,
	SDKSOCKET5PROXY = 3
};

typedef struct SDKProxyOptions
{
	SDKProxyOptions()
	{
		type = SDKINVALIDPROXY;
		ip = "";
		port = -1;
		username = "";
		password = "";
	}

	SDKProxyType type;
	std::string ip;
	unsigned short port;
	std::string username;
	std::string password;
}SDKProxyOptions;

// �Ựѡ��
class SessionOptions: public IHSKnown {
public:
	virtual ~SessionOptions() {}

	// ����������ʱʱ�䣬Ĭ���ɷ������·�������ʱʱ��Ϊ60�룬������ʱ�����ӽ����Ͽ�
	//seconds������ʱʱ��������10�룬�������ͼ��Ϊһ���������ʱʱ��
	virtual int H5SDKAPI SetHeartbeatTimeout(int seconds) = 0;
	// ��ȡ������ʱʱ��
	//// @return 0 ��ʾ �ɷ��������Եĳ�ʱʱ��
	//@return ��0����ʾ�ɿͻ������õ�������ʱʱ��
	virtual int H5SDKAPI GetHeartbeatTimeout() = 0;

	// ����ָ���±�ķ����IP��Ĭ��Ϊ"127.0.0.1",��˳���������ܿ�Խ��������
	// 0 ���óɹ�  -1 ����ʧ��
	virtual int H5SDKAPI SetServerIp(const char *ip, size_t index = 0) = 0;

	// ����ָ���±�ķ���˶˿ڣ�Ĭ��Ϊ8888,��˳���������ܿ�Խ��������
	// 0 ���óɹ�  -1 ����ʧ��
	virtual int H5SDKAPI SetServerPort(unsigned short port, size_t index = 0) = 0;

	// ��ȡָ���±�ķ����IP
	virtual const char * H5SDKAPI GetServerIp(size_t index = 0) = 0;
	// ��ȡָ���±�ķ���˶˿�
	virtual unsigned short H5SDKAPI GetServerPort(size_t index = 0) = 0;

	// ��ȡ���õķ���˸���
	virtual size_t H5SDKAPI GetServerCount() = 0;

	// ���������������λΪ�룬Ĭ��Ϊ3��
	virtual int H5SDKAPI SetReconnintvl(int reconnintvl) = 0;
	// ��������������Ĭ��Ϊ5��
	virtual int H5SDKAPI SetReconnretries(int reconnretries) = 0;

	// ��ȡ�������
	virtual int H5SDKAPI GetReconnintvl() = 0;
	// ��ȡ��������
	virtual int H5SDKAPI GetReconnretries() = 0;

	// ���ø�Session��������������������ݵĵ����̸߳�����������첽Ӧ�������ǿ���Ⱥ�˳���Ӧ����Ĵ���������
	// һ�㲻�����ã�ֻ�����������;ʱ��Session���ع���ʱ����
	// �߳���Ϣ��ͨ��GetDecodeDataThreadNum()��GetDecodeDataThreadInfo()�ӿڲ鿴
	virtual int H5SDKAPI SetDecodeDataThreadNum(int threadNum) = 0;
};

const int H5SDK_SUBSCRIBE_NOT_CONNECT = -4;
const int H5SDK_DISCONNECT			  = -1;
const int H5SDK_TIMEOUT               = -3;
const int H5SDK_SDK_LOGIN_ERROR       = 1010;
const int H5SDK_SERIALIZATION_ERROR   = 1002;
const int H5SDK_SET_DECODER_ERROR     = 1004;
const int H5SDK_SDK_LOGIN_TIMEOUT     = 1005;

#define		LEVEL_1		(0x0)
#define		LEVEL_2		(0x1)
#define		_REAL		(0x00)
#define		_DELAY		(0x10)

class Session;
//������
class AnsBatch : public IHSKnownSuper
{
public:
	virtual int H5SDKAPI GetMessageCount()=0;
	virtual IHsCommMessage* H5SDKAPI GetMessage(int index)=0;
	virtual unsigned long H5SDKAPI AddRef() =0;
	virtual unsigned long H5SDKAPI Release()=0;
};

#define STRLEN 32
class LoginAnsInfo : public IHSKnownSuper
{
public:
	virtual const char * H5SDKAPI GetUserName()=0;	

	//tocken
	virtual const char * H5SDKAPI GetToken()=0;
	virtual const char * H5SDKAPI GetAuthId()=0;

	//�����"suc"��½�ɹ�������ʧ��
	virtual const char * H5SDKAPI GetResult()=0;
	virtual const char * H5SDKAPI GetError()=0;

	//Ȩ����Ϣ
	virtual const char * H5SDKAPI GetAuthString()=0;

	//���ü���
	virtual unsigned long H5SDKAPI AddRef() =0;
	virtual unsigned long H5SDKAPI Release()=0;

};
//ע��
class RegisterAnsInfo : public IHSKnownSuper
{
public:
	//�û�������
	virtual const char * H5SDKAPI GetUserName()=0;
	virtual const char * H5SDKAPI GetPassword()=0;

	//�����"suc"��½�ɹ�������ʧ��
	virtual const char * H5SDKAPI GetResult()=0;
	//������Ϣ
	virtual const char * H5SDKAPI GetError()=0;
	//���ü�����
	virtual unsigned long H5SDKAPI AddRef() =0;
	virtual unsigned long H5SDKAPI Release()=0;
};


class ChangeAnsInfo : public IHSKnownSuper
{
public:
	virtual const char * H5SDKAPI GetUserName()=0;
	virtual const char * H5SDKAPI GetPassword()=0;

	//�����"suc"��½�ɹ�������ʧ��
	virtual const char * H5SDKAPI GetResult()=0;
	virtual const char * H5SDKAPI GetError()=0;

	virtual unsigned long H5SDKAPI AddRef() =0;
	virtual unsigned long H5SDKAPI Release()=0;
};
// H5Sdk�ص��ӿ�
class H5SdkCallback : public IHSKnownSuper
{
public:
	// ���Ự���ӳɹ�ʱ�ص�
	virtual void H5SDKAPI OnConnect(Session *session, const char *peerIp, int peerPort, const char *localIp, int localPort) = 0;

	// ���Ự��¼�ɹ�ʱ�ص�
	virtual void H5SDKAPI OnSdkLogin(Session *session) = 0;

	// ���Ự�յ��첽��Ϣʱ�ص�
	// response��Ҫҵ������ͷ�
	virtual void H5SDKAPI OnReceived(Session *session, IHsCommMessage *response) = 0;

	// ���Ự���ӶϿ�ʱ�ص�
	virtual void H5SDKAPI OnClose(Session *session, int reason) = 0;

	// ���Ự����ʱ�ص�
	// errorNoĿǰ����ΪH5SDK_SDK_LOGIN_TIMEOUT����ʾsdk��¼��ʱ
	virtual void H5SDKAPI OnError(Session *session, int errorNo) = 0;

	// ������ָ����������Ȼ�޷�������ص�
	virtual void H5SDKAPI OnCore(Session *session) = 0;
};


class ThreadInfo;
// �Ự
class Session: public IHSKnown {
public:
	virtual ~Session() {}

	// ����ָ��ҵ��š����ܺš������͵���Ϣ
	// �÷��������ڻص��ӿ�H5SdkCallback�ķ���OnSdkLogin�ص���ſ��Ե���
	virtual IHsCommMessage * H5SDKAPI CreateMessage(int businessId, int functionId, int packetType) = 0;

	// ͬ������
	// ͬ�����ò����յ��첽Ӧ��
	// ��ʱӦ��ᱻ�Զ����������ᱻ����SyncCall�յ�
	// @return 0 ��ʾ �ɹ�
	// @return H5SDK_DISCONNECT ��ʾ ����δ�������ѶϿ�
	// @return H5SDK_SERIALIZATION_ERROR ��ʾ request���л�ʧ�ܣ�����ԭ��ɵ���request��GetLastErrInfo�������鿴
	// @return H5SDK_TIMEOUT ��ʾ ���ó�ʱ
	virtual int H5SDKAPI SyncCall(IHsCommMessage *request, IHsCommMessage **response, int milliseconds) = 0;

	// �첽����
	// @return 0 ��ʾ �ɹ�
	// @return H5SDK_DISCONNECT ��ʾ ����δ�������ѶϿ�
	// @return H5SDK_SERIALIZATION_ERROR ��ʾ request���л�ʧ�ܣ�����ԭ��ɵ���request��GetLastErrInfo�������鿴
	virtual int H5SDKAPI AsyncSend(IHsCommMessage *request) = 0;

	// ��ȡ���Ự����������Ϣ����
	virtual IHsComMessageFactory * H5SDKAPI GetMessageFactory() = 0;

	// ���ûص��ӿ�
	// �ýӿڱ�����StartSetCallback֮��StartAllSessions֮ǰ����
	// @return 0 ��ʾ ���óɹ�
	// @return H5SDK_SET_DECODER_ERROR ��ʾ ����SetDecoderʧ��
	virtual int H5SDKAPI SetCallback(H5SdkCallback *h5SdkCallback) = 0;

	// �����첽����
	// ���Ҫʵ�ֶ������������ڻص��ӿ�H5SdkCallback��OnCore��������е���
	// StartAllSessions���ú󣬻��Զ��������лỰ��AsyncConnect
	// �����ӳɹ�ʱ��ͨ���ص��ӿ�H5SdkCallback�ķ���OnConnect����֪ͨ
	// ������һֱ�޷��������ͨ���ص��ӿ�H5SdkCallback�ķ���OnCore����֪ͨ
	// @return 0 ��ʾ ����ɹ�
	virtual int H5SDKAPI AsyncConnect() = 0;

	// �����첽Sdk��¼
	// millseconds��ʾ��ʱʱ�䣬��λ����
	// �÷����ڻص��ӿ�H5SdkCallback��OnConnect��������е���
	// ��Sdk��¼�ɹ�ʱ��ͨ���ص��ӿ�H5SdkCallback�ķ���OnSdkLogin����֪ͨ
	// ��Sdk��¼��ʱʱ��ͨ���ص��ӿ�H5SdkCallback�ķ���OnError����֪ͨ������errorNoΪH5SDK_SDK_LOGIN_TIMEOUT
	// ��OnSdkLogin�ص�֮��ſ��Է���ҵ������
	// @return 0 ��ʾ ����ɹ�
	virtual int H5SDKAPI AsyncSdkLogin(int millseconds) = 0;

	// �����첽����
	// ���ӿں�AsyncConnect����Ҫ�����Ǳ��ӿڿ�������ʱָ��IP�Ͷ˿�
	// @return 0 ��ʾ ����ɹ�
	virtual int H5SDKAPI AsyncConnectEx(const char *ip, unsigned short port) = 0;

	// ��ȡָ��ҵ��š����ܺš������͵���Ϣģ������ֵ���ýӿڿ��������Ƚϲ�ͬ�Ự��ָ��ģ���Ƿ���ȫƥ�䣩
	// �÷��������ڻص��ӿ�H5SdkCallback�ķ���OnSdkLogin�ص���ſ��Ե���
	virtual int64 H5SDKAPI GetTemplateFeature(int businessId, int functionId, int packetType) = 0;

	//��ȡ��������Ϣ
	virtual IHsCommMessage * H5SDKAPI CreateBatchMessage() = 0;

	//����Ϣ��ӵ���������Ϣ��
	//request��������֯���Ժ����Ϣ
	//BatchMsg��Ϣ��֯��ɺ�ʹ�÷��ͣ�ͬ�������첽���ӿڷ���
	// ���أ�0��ʾ�ɹ�
	//		  ������ʾʧ�ܡ�
	virtual int H5SDKAPI AddMessagetoBatch(IHsCommMessage *request, IHsCommMessage *batchMsg) = 0;

	//����ȡ��������ϢH5SDK_MSG_BATCH��1006������Ϊ�������Ϣ( vector<IHsCommMessage *>ansMsgs)

	virtual AnsBatch *H5SDKAPI GetBatchInfo(IHsCommMessage *batchMsg) = 0;

	/// <summary>
	///  ���ü�����Կ��Ӧ�ñ�ʶ��Ϣ
	/// ��½����ע��֮ǰ���ã��͵�½/ע��/�޸��û���Ϣ�ӿڷ��̰߳�ȫ
	/// ��������˵����ʹ��Ĭ����Կ����
	/// </summary>
	/// <param name="app_key">�ڽ����ƿ���ƽ̨(http://open.hs.net)����һ��Ӧ�ú��ȡ��App Key</param>
	/// <param name="app_secret">�ڽ����ƿ���ƽ̨(http://open.hs.net)����һ��Ӧ�ú��ȡ��App Secret</param>
	/// <returns></returns>
	virtual int H5SDKAPI SetAppInfo(const char *app_key,const char *app_secret = NULL) = 0;

	//��½��ע�ᣬ�޸��û���Ϣ�Ƚӿ���ҪSDK��½����ã������ٻص�������ֱ�ӵ���
	//ͬ��ע����ýӿ�
	virtual RegisterAnsInfo *H5SDKAPI RegisterUser(	const char* userName, //�û���
		const char* password,//����
		const char* phone,	//�ֻ���
		const char* email) = 0;	//����)	  

	/// <summary>
	/// ʹ���û���\�ֻ�����\���估�������¼
	/// </summary>
	/// <param name="userName">�û���\�ֻ�����\����</param>
	/// <param name="password">����</param>
	/// <param name="imei">��¼�豸��ʶ</param>
	/// <returns>��¼�ɹ����Ӧ����Ϣ����Ҫ����Release �ӿ��ͷ���Դ</returns>
	virtual LoginAnsInfo *H5SDKAPI LoginByUser(const char *userName,  // �û������ֻ������EMail
		const char *password, 
		const char *imei = NULL) = 0;

	//ʹ��token��½,���ص�LoginAnsInfo�����û���Ҫ����Release �ӿ��ͷ���Դ
	virtual LoginAnsInfo *H5SDKAPI LoginByToken(const char *token,
		const char *auth_id, 
		const char *imei = NULL)=0;

	//ͬ���޸��û���Ϣ���ýӿ�
	//virtual ChangeAnsInfo *H5SDKAPI ChangeUserInfo(const char* userName, //�û���
	//	const char* password,//����
	//	const char* imei,	//�ƶ��豸���������
	//	const char* phone,	//�ֻ���
	//	const char* email, // ����
	//	const char* newPassword) = 0;

	//�û�����ָ�����ӷ���IP����ʼ���,��������0��ʼ
	virtual int H5SDKAPI SwitchConnectIndex(const size_t index) = 0;

	//�û����Խ����ֶ����IP�Ͷ˿�
	virtual int H5SDKAPI AddIpAndPort(const char * ipaddr, unsigned short port) = 0;

	//�û������޸�ָ��������IP�Ͷ˿�,��������0��ʼ
	virtual int H5SDKAPI ChangeIpAndPort(const size_t index, const char * ipaddr, unsigned short port) = 0;

	//�û����Ի�ȡָ��������IP�Ͷ˿�,��������0��ʼ
	virtual int H5SDKAPI GetIpAndPort(const size_t index, char * ipaddr, unsigned short* port) = 0;

	//�û����Ի�ȡ�˻Ự���õ����е�ַ����
	virtual int H5SDKAPI GetAddressCount() = 0;

	//���øûỰʹ��bestЭ��
	virtual void H5SDKAPI SetBestProtocol(bool trueORfalse) = 0;

	//��ȡ�ûỰ�Ƿ�ΪbestЭ��
	virtual bool H5SDKAPI GetBestProtocolFlag() = 0;

	//�û����������ȡʲô�ȼ���������Ϣ��level1 or level2����ʱ����ʵʱ��  Ĭ��level1ʵʱ
	//�����ȡLevel1��ʱ���飬�ɵ��� SetHqLevel(LEVEL_1 | _DELAY);
	//�������������ʱ��Ч
	virtual void H5SDKAPI SetHqLevel(long long hqlevel) = 0;

	//�û��ǳ�
	virtual int H5SDKAPI Logout() = 0;
	
	//�û��Ͽ�����
	virtual int H5SDKAPI Disconnect() = 0;

#ifdef SdkTest
	virtual void H5SDKAPI ShowResult() = 0;
	virtual void H5SDKAPI ClearTestMap() = 0;
#endif

	//��ȡSession�ڲ�����������������ݵ��߳�����ҵ����ɲ����Ĵ˽ӿڣ�
	virtual int H5SDKAPI GetDecodeDataThreadNum() = 0;

	//��ȡSession�ڲ�����������������ݵ�ָ���̵߳��߳���Ϣ��ҵ����ɲ����Ĵ˽ӿڣ�
	//thrreadIndex: 0 ~ (GetDecodeDataThreadNum() - 1)
	//���ط�NULLΪ�ɹ�
	virtual ThreadInfo * H5SDKAPI GetDecodeDataThreadInfo(int threadIndex) = 0;
};

class ThreadInfo : public IHSKnownSuper {
public:
	virtual ~ThreadInfo() {}

	// 0 ~ GetSessionDecodeDataThreadNum() -1
	virtual int H5SDKAPI GetThreadIndex() = 0;

	// operating system thread id
	virtual int H5SDKAPI GetThreadId() = 0;

	// defered successfully message count
	virtual uint64 H5SDKAPI GetDeferedMsgs() = 0;

	// defered failed message count
	virtual uint64 H5SDKAPI GetErrorDeferedMsgs() = 0;

	// dealed message count
	virtual uint64 H5SDKAPI GetDealedMsgs() = 0;

	// history max backlog message count
	virtual uint64 H5SDKAPI GetHisMaxBackLog() = 0;

	// current backlog msssage count
	virtual uint64 H5SDKAPI GetBacklog() = 0;
};

#endif
