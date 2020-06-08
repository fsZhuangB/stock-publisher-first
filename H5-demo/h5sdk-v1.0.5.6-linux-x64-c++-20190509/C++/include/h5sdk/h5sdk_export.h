/** @file
* h5sdk动态库引出函数
* @author  应鸿浩
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20140428
*/

#ifndef __H5SDK_EXPORT_H__
#define __H5SDK_EXPORT_H__

#include <stdio.h>

#if ( defined(_WIN32) || defined(_WIN64) )
#  define H5SDKAPI __stdcall
#else
#  define H5SDKAPI
#endif

class SessionOptions;
class Session;
class Velocimetry;
struct IF2UnPacker;
struct IF2Packer;
class ThreadInfo;

#ifndef HS_SID
#define HS_SID	const char *
#endif

#ifndef IHS_KNOWN
#define IHS_KNOWN
struct IHSKnown
{
	///接口查询
	/**查询与当前接口相关的其他接口，例如可以查到 IIoC, IManager 等
	*@param HS_SID  iid  接口全局唯一标识
	*@param IKnown **ppv 返回iid对应的接口指针
	*@return I_OK 成功，I_NONE 未查到iid 相应接口
	*/
	virtual unsigned long  H5SDKAPI QueryInterface( HS_SID iid, IHSKnown **ppv ) = 0;
	///引用接口，引用计数加一(多线程引用时，方法实现代码里要对计数值加锁后修改)
	virtual unsigned long  H5SDKAPI AddRef() = 0;
	///释放接口，引用计数减一，计数为0时释放接口的实现对象(多线程引用时，方法实现代码里要对计数值加锁后修改)
	virtual unsigned long  H5SDKAPI Release() =  0;
};
#endif
class IHSKnownSuper : public IHSKnown
{
	virtual unsigned long  H5SDKAPI QueryInterface( HS_SID iid, IHSKnown **ppv )
	{
		return 0;
	}
	virtual unsigned long  H5SDKAPI AddRef()
	{
		return 0;
	}
	virtual unsigned long  H5SDKAPI Release()
	{
		return 0;
	}
};



extern "C" {
    // 获取SDK版本
    const char * H5SDKAPI GetSdkVersion();

    // 创建会话选项SessionOptions
    SessionOptions * H5SDKAPI CreateSessionOptions();

    // 用会话选项SessionOptions来创建会话Session
    Session * H5SDKAPI CreateSession(SessionOptions *sessionOptions);

    // 创建测速对象Velocimetry
    Velocimetry * H5SDKAPI CreateVelocimetry();

    // 获取错误号对应的错误信息
    const char * H5SDKAPI GetErrorStringByErrorNo(int errorNo);

    // 开始设置所有会话的回调接口
    // 该接口必须在所有会话创建完后进行调用
    int H5SDKAPI StartSetCallback();

    // 启动所有会话
    int H5SDKAPI StartAllSessions();

	// 关闭所有会话
	int H5SDKAPI StopAllSessions();
	
	//h5模板存储路认径，默路径为当前路径下的h5data路径
	//会话创建之前使用
	void H5SDKAPI SetH5DataPath( const char *path);
	//h5日志存储路认径，默路径为当前路径下的h5data路径
	//会话创建之前使用
	void H5SDKAPI SetH5LogPath( const char *path);

	//日志级别等其他参数配置文件
	void H5SDKAPI SetSdkParamPath( const char *path);

	//设置是否启动时自动连接行情服务
	void H5SDKAPI SetInitAutoConnectFlag(bool autoconnect);

	//设置连接行情服务的代理
	int H5SDKAPI SetProxyOptions(int type, const char *ip, unsigned short port, const char *username = NULL , const char *password = NULL);

	//内部管理功能（可不关心该接口）
	int H5SDKAPI ProcSDKMngRequest(Session * session, HS_SID iid, IF2UnPacker * input, IF2Packer * output);

	//获取Session内部处理行情服务器数据的线程数（业务处理可不关心此接口）
	// session传入NULL，代表获取全局共用处理行情服务器数据的线程数
	int H5SDKAPI GetSDKDecodeDataThreadNum(Session * session);

	//获取Session内部处理行情服务器数据的指定线程的线程信息（业务处理可不关心此接口）
	// session传入NULL，代表获取全局共用处理行情服务器数据的指定线程的线程信息
	//thrreadIndex: 0 ~ (GetSDKDecodeDataThreadNum() - 1)
	//返回非NULL为成功
	ThreadInfo * H5SDKAPI GetSDKDecodeDataThreadInfo(Session * session, int threadIndex);

}

#endif
