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

// 会话选项
class SessionOptions: public IHSKnown {
public:
	virtual ~SessionOptions() {}

	// 设置心跳超时时间，默认由服务器下发心跳超时时间为60秒，心跳超时后连接将被断开
	//seconds心跳超时时间必须大于10秒，心跳发送间隔为一半的心跳超时时间
	virtual int H5SDKAPI SetHeartbeatTimeout(int seconds) = 0;
	// 获取心跳超时时间
	//// @return 0 表示 由服务器绝对的超时时间
	//@return 非0，表示由客户端设置的心跳超时时间
	virtual int H5SDKAPI GetHeartbeatTimeout() = 0;

	// 设置指定下标的服务端IP，默认为"127.0.0.1",按顺序来，不能跨越进行配置
	// 0 设置成功  -1 设置失败
	virtual int H5SDKAPI SetServerIp(const char *ip, size_t index = 0) = 0;

	// 设置指定下标的服务端端口，默认为8888,按顺序来，不能跨越进行配置
	// 0 设置成功  -1 设置失败
	virtual int H5SDKAPI SetServerPort(unsigned short port, size_t index = 0) = 0;

	// 获取指定下标的服务端IP
	virtual const char * H5SDKAPI GetServerIp(size_t index = 0) = 0;
	// 获取指定下标的服务端端口
	virtual unsigned short H5SDKAPI GetServerPort(size_t index = 0) = 0;

	// 获取设置的服务端个数
	virtual size_t H5SDKAPI GetServerCount() = 0;

	// 设置重连间隔，单位为秒，默认为3秒
	virtual int H5SDKAPI SetReconnintvl(int reconnintvl) = 0;
	// 设置重连次数，默认为5次
	virtual int H5SDKAPI SetReconnretries(int reconnretries) = 0;

	// 获取重连间隔
	virtual int H5SDKAPI GetReconnintvl() = 0;
	// 获取重连次数
	virtual int H5SDKAPI GetReconnretries() = 0;

	// 设置该Session解析处理行情服务器数据的单独线程个数，可提高异步应答包及无强制先后顺序的应答包的处理能力）
	// 一般不用设置，只有做服务端用途时该Session负载过高时设置
	// 线程信息可通过GetDecodeDataThreadNum()、GetDecodeDataThreadInfo()接口查看
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
//批处理
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

	//结果："suc"登陆成功，其他失败
	virtual const char * H5SDKAPI GetResult()=0;
	virtual const char * H5SDKAPI GetError()=0;

	//权限信息
	virtual const char * H5SDKAPI GetAuthString()=0;

	//引用计数
	virtual unsigned long H5SDKAPI AddRef() =0;
	virtual unsigned long H5SDKAPI Release()=0;

};
//注册
class RegisterAnsInfo : public IHSKnownSuper
{
public:
	//用户名密码
	virtual const char * H5SDKAPI GetUserName()=0;
	virtual const char * H5SDKAPI GetPassword()=0;

	//结果："suc"登陆成功，其他失败
	virtual const char * H5SDKAPI GetResult()=0;
	//错误信息
	virtual const char * H5SDKAPI GetError()=0;
	//引用计数器
	virtual unsigned long H5SDKAPI AddRef() =0;
	virtual unsigned long H5SDKAPI Release()=0;
};


class ChangeAnsInfo : public IHSKnownSuper
{
public:
	virtual const char * H5SDKAPI GetUserName()=0;
	virtual const char * H5SDKAPI GetPassword()=0;

	//结果："suc"登陆成功，其他失败
	virtual const char * H5SDKAPI GetResult()=0;
	virtual const char * H5SDKAPI GetError()=0;

	virtual unsigned long H5SDKAPI AddRef() =0;
	virtual unsigned long H5SDKAPI Release()=0;
};
// H5Sdk回调接口
class H5SdkCallback : public IHSKnownSuper
{
public:
	// 当会话连接成功时回调
	virtual void H5SDKAPI OnConnect(Session *session, const char *peerIp, int peerPort, const char *localIp, int localPort) = 0;

	// 当会话登录成功时回调
	virtual void H5SDKAPI OnSdkLogin(Session *session) = 0;

	// 当会话收到异步消息时回调
	// response需要业务层来释放
	virtual void H5SDKAPI OnReceived(Session *session, IHsCommMessage *response) = 0;

	// 当会话连接断开时回调
	virtual void H5SDKAPI OnClose(Session *session, int reason) = 0;

	// 当会话出错时回调
	// errorNo目前可能为H5SDK_SDK_LOGIN_TIMEOUT，表示sdk登录超时
	virtual void H5SDKAPI OnError(Session *session, int errorNo) = 0;

	// 当重连指定次数后仍然无法连上则回调
	virtual void H5SDKAPI OnCore(Session *session) = 0;
};


class ThreadInfo;
// 会话
class Session: public IHSKnown {
public:
	virtual ~Session() {}

	// 创建指定业务号、功能号、包类型的消息
	// 该方法必须在回调接口H5SdkCallback的方法OnSdkLogin回调后才可以调用
	virtual IHsCommMessage * H5SDKAPI CreateMessage(int businessId, int functionId, int packetType) = 0;

	// 同步调用
	// 同步调用不会收到异步应答
	// 超时应答会被自动丢弃，不会被其他SyncCall收到
	// @return 0 表示 成功
	// @return H5SDK_DISCONNECT 表示 连接未建立或已断开
	// @return H5SDK_SERIALIZATION_ERROR 表示 request序列化失败，具体原因可调用request的GetLastErrInfo方法来查看
	// @return H5SDK_TIMEOUT 表示 调用超时
	virtual int H5SDKAPI SyncCall(IHsCommMessage *request, IHsCommMessage **response, int milliseconds) = 0;

	// 异步发送
	// @return 0 表示 成功
	// @return H5SDK_DISCONNECT 表示 连接未建立或已断开
	// @return H5SDK_SERIALIZATION_ERROR 表示 request序列化失败，具体原因可调用request的GetLastErrInfo方法来查看
	virtual int H5SDKAPI AsyncSend(IHsCommMessage *request) = 0;

	// 获取本会话所关联的消息工厂
	virtual IHsComMessageFactory * H5SDKAPI GetMessageFactory() = 0;

	// 设置回调接口
	// 该接口必须在StartSetCallback之后，StartAllSessions之前调用
	// @return 0 表示 设置成功
	// @return H5SDK_SET_DECODER_ERROR 表示 设置SetDecoder失败
	virtual int H5SDKAPI SetCallback(H5SdkCallback *h5SdkCallback) = 0;

	// 发起异步连接
	// 如果要实现断线重连，可在回调接口H5SdkCallback的OnCore方法里进行调用
	// StartAllSessions调用后，会自动发起所有会话的AsyncConnect
	// 当连接成功时会通过回调接口H5SdkCallback的方法OnConnect进行通知
	// 当连接一直无法连上则会通过回调接口H5SdkCallback的方法OnCore进行通知
	// @return 0 表示 发起成功
	virtual int H5SDKAPI AsyncConnect() = 0;

	// 发起异步Sdk登录
	// millseconds表示超时时间，单位毫秒
	// 该方法在回调接口H5SdkCallback的OnConnect方法里进行调用
	// 当Sdk登录成功时会通过回调接口H5SdkCallback的方法OnSdkLogin进行通知
	// 当Sdk登录超时时会通过回调接口H5SdkCallback的方法OnError进行通知，其中errorNo为H5SDK_SDK_LOGIN_TIMEOUT
	// 当OnSdkLogin回调之后才可以发起业务层操作
	// @return 0 表示 发起成功
	virtual int H5SDKAPI AsyncSdkLogin(int millseconds) = 0;

	// 发起异步连接
	// 本接口和AsyncConnect的主要区别是本接口可以运行时指定IP和端口
	// @return 0 表示 发起成功
	virtual int H5SDKAPI AsyncConnectEx(const char *ip, unsigned short port) = 0;

	// 获取指定业务号、功能号、包类型的消息模板特征值（该接口可以用来比较不同会话的指定模板是否完全匹配）
	// 该方法必须在回调接口H5SdkCallback的方法OnSdkLogin回调后才可以调用
	virtual int64 H5SDKAPI GetTemplateFeature(int businessId, int functionId, int packetType) = 0;

	//获取批处理消息
	virtual IHsCommMessage * H5SDKAPI CreateBatchMessage() = 0;

	//将消息添加到批处理消息中
	//request必须是组织好以后的消息
	//BatchMsg消息组织完成后，使用发送（同步或者异步）接口发送
	// 返回：0表示成功
	//		  其他表示失败。
	virtual int H5SDKAPI AddMessagetoBatch(IHsCommMessage *request, IHsCommMessage *batchMsg) = 0;

	//将获取到的批消息H5SDK_MSG_BATCH（1006）解析为多个子消息( vector<IHsCommMessage *>ansMsgs)

	virtual AnsBatch *H5SDKAPI GetBatchInfo(IHsCommMessage *batchMsg) = 0;

	/// <summary>
	///  设置加密秘钥和应用标识信息
	/// 登陆或者注册之前调用，和登陆/注册/修改用户信息接口非线程安全
	/// 如无特殊说明，使用默认秘钥即可
	/// </summary>
	/// <param name="app_key">在金融云开放平台(http://open.hs.net)创建一个应用后获取的App Key</param>
	/// <param name="app_secret">在金融云开放平台(http://open.hs.net)创建一个应用后获取的App Secret</param>
	/// <returns></returns>
	virtual int H5SDKAPI SetAppInfo(const char *app_key,const char *app_secret = NULL) = 0;

	//登陆，注册，修改用户信息等接口需要SDK登陆后调用，不能再回调函数中直接调用
	//同步注册调用接口
	virtual RegisterAnsInfo *H5SDKAPI RegisterUser(	const char* userName, //用户名
		const char* password,//密码
		const char* phone,	//手机号
		const char* email) = 0;	//邮箱)	  

	/// <summary>
	/// 使用用户名\手机号码\邮箱及其密码登录
	/// </summary>
	/// <param name="userName">用户名\手机号码\邮箱</param>
	/// <param name="password">密码</param>
	/// <param name="imei">登录设备标识</param>
	/// <returns>登录成功后的应答信息，需要调用Release 接口释放资源</returns>
	virtual LoginAnsInfo *H5SDKAPI LoginByUser(const char *userName,  // 用户名、手机号码或EMail
		const char *password, 
		const char *imei = NULL) = 0;

	//使用token登陆,返回的LoginAnsInfo对象用户需要调用Release 接口释放资源
	virtual LoginAnsInfo *H5SDKAPI LoginByToken(const char *token,
		const char *auth_id, 
		const char *imei = NULL)=0;

	//同步修改用户信息调用接口
	//virtual ChangeAnsInfo *H5SDKAPI ChangeUserInfo(const char* userName, //用户名
	//	const char* password,//密码
	//	const char* imei,	//移动设备国际身份码
	//	const char* phone,	//手机号
	//	const char* email, // 邮箱
	//	const char* newPassword) = 0;

	//用户可以指定连接服务IP的起始编号,从索引从0开始
	virtual int H5SDKAPI SwitchConnectIndex(const size_t index) = 0;

	//用户可以进行手动添加IP和端口
	virtual int H5SDKAPI AddIpAndPort(const char * ipaddr, unsigned short port) = 0;

	//用户可以修改指定索引的IP和端口,从索引从0开始
	virtual int H5SDKAPI ChangeIpAndPort(const size_t index, const char * ipaddr, unsigned short port) = 0;

	//用户可以获取指定索引的IP和端口,从索引从0开始
	virtual int H5SDKAPI GetIpAndPort(const size_t index, char * ipaddr, unsigned short* port) = 0;

	//用户可以获取此会话设置的所有地址个数
	virtual int H5SDKAPI GetAddressCount() = 0;

	//设置该会话使用best协议
	virtual void H5SDKAPI SetBestProtocol(bool trueORfalse) = 0;

	//获取该会话是否为best协议
	virtual bool H5SDKAPI GetBestProtocolFlag() = 0;

	//用户可设置想获取什么等级的行情信息（level1 or level2，延时还是实时）  默认level1实时
	//如想获取Level1延时行情，可调用 SetHqLevel(LEVEL_1 | _DELAY);
	//仅针对连接网关时有效
	virtual void H5SDKAPI SetHqLevel(long long hqlevel) = 0;

	//用户登出
	virtual int H5SDKAPI Logout() = 0;
	
	//用户断开连接
	virtual int H5SDKAPI Disconnect() = 0;

#ifdef SdkTest
	virtual void H5SDKAPI ShowResult() = 0;
	virtual void H5SDKAPI ClearTestMap() = 0;
#endif

	//获取Session内部处理行情服务器数据的线程数（业务处理可不关心此接口）
	virtual int H5SDKAPI GetDecodeDataThreadNum() = 0;

	//获取Session内部处理行情服务器数据的指定线程的线程信息（业务处理可不关心此接口）
	//thrreadIndex: 0 ~ (GetDecodeDataThreadNum() - 1)
	//返回非NULL为成功
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
