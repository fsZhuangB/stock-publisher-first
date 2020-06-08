/** @file
* h5sdk��̬����������
* @author  Ӧ���
* @author  �������ӹɷ����޹�˾
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
	///�ӿڲ�ѯ
	/**��ѯ�뵱ǰ�ӿ���ص������ӿڣ�������Բ鵽 IIoC, IManager ��
	*@param HS_SID  iid  �ӿ�ȫ��Ψһ��ʶ
	*@param IKnown **ppv ����iid��Ӧ�Ľӿ�ָ��
	*@return I_OK �ɹ���I_NONE δ�鵽iid ��Ӧ�ӿ�
	*/
	virtual unsigned long  H5SDKAPI QueryInterface( HS_SID iid, IHSKnown **ppv ) = 0;
	///���ýӿڣ����ü�����һ(���߳�����ʱ������ʵ�ִ�����Ҫ�Լ���ֵ�������޸�)
	virtual unsigned long  H5SDKAPI AddRef() = 0;
	///�ͷŽӿڣ����ü�����һ������Ϊ0ʱ�ͷŽӿڵ�ʵ�ֶ���(���߳�����ʱ������ʵ�ִ�����Ҫ�Լ���ֵ�������޸�)
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
    // ��ȡSDK�汾
    const char * H5SDKAPI GetSdkVersion();

    // �����Ựѡ��SessionOptions
    SessionOptions * H5SDKAPI CreateSessionOptions();

    // �ûỰѡ��SessionOptions�������ỰSession
    Session * H5SDKAPI CreateSession(SessionOptions *sessionOptions);

    // �������ٶ���Velocimetry
    Velocimetry * H5SDKAPI CreateVelocimetry();

    // ��ȡ����Ŷ�Ӧ�Ĵ�����Ϣ
    const char * H5SDKAPI GetErrorStringByErrorNo(int errorNo);

    // ��ʼ�������лỰ�Ļص��ӿ�
    // �ýӿڱ��������лỰ���������е���
    int H5SDKAPI StartSetCallback();

    // �������лỰ
    int H5SDKAPI StartAllSessions();

	// �ر����лỰ
	int H5SDKAPI StopAllSessions();
	
	//h5ģ��洢·�Ͼ���Ĭ·��Ϊ��ǰ·���µ�h5data·��
	//�Ự����֮ǰʹ��
	void H5SDKAPI SetH5DataPath( const char *path);
	//h5��־�洢·�Ͼ���Ĭ·��Ϊ��ǰ·���µ�h5data·��
	//�Ự����֮ǰʹ��
	void H5SDKAPI SetH5LogPath( const char *path);

	//��־������������������ļ�
	void H5SDKAPI SetSdkParamPath( const char *path);

	//�����Ƿ�����ʱ�Զ������������
	void H5SDKAPI SetInitAutoConnectFlag(bool autoconnect);

	//���������������Ĵ���
	int H5SDKAPI SetProxyOptions(int type, const char *ip, unsigned short port, const char *username = NULL , const char *password = NULL);

	//�ڲ������ܣ��ɲ����ĸýӿڣ�
	int H5SDKAPI ProcSDKMngRequest(Session * session, HS_SID iid, IF2UnPacker * input, IF2Packer * output);

	//��ȡSession�ڲ�����������������ݵ��߳�����ҵ����ɲ����Ĵ˽ӿڣ�
	// session����NULL�������ȡȫ�ֹ��ô���������������ݵ��߳���
	int H5SDKAPI GetSDKDecodeDataThreadNum(Session * session);

	//��ȡSession�ڲ�����������������ݵ�ָ���̵߳��߳���Ϣ��ҵ����ɲ����Ĵ˽ӿڣ�
	// session����NULL�������ȡȫ�ֹ��ô���������������ݵ�ָ���̵߳��߳���Ϣ
	//thrreadIndex: 0 ~ (GetSDKDecodeDataThreadNum() - 1)
	//���ط�NULLΪ�ɹ�
	ThreadInfo * H5SDKAPI GetSDKDecodeDataThreadInfo(Session * session, int threadIndex);

}

#endif
