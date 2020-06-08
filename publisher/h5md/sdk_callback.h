/** @file
* ����demo.�ص����
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/

#pragma once

#include <string>
using namespace std;
#include "h5sdk/h5sdk.h"
/*
	�����ٶȣ��ص���
*/
class MyVelocimetryCallback: public VelocimetryCallback
{
public:
	/*
		���ٳɹ�
	*/
	int H5SDKAPI OnVelocimetrySucceed(Endpoint *endpoint, int delay, int load);

	/*
		����ʧ��
	*/
	int H5SDKAPI OnVelocimetryFail(Endpoint *endpoint, VelocimetryErrorNo errorNo);
	/*
		���ٽ���
	*/
	int H5SDKAPI OnVelocimetryComplete();
};

/*
	����SDK�ص�
*/
class H5SdkCallbackImpl: public H5SdkCallback 
{
public:
	/*
		����������ӳɹ�.(��û��½.)
	*/
	void H5SDKAPI OnConnect(Session *session, const char *peerIp, int peerPort, const char *localIp, int localPort);
	/*
		SDK��½���
	*/
	void H5SDKAPI OnSdkLogin(Session *session);
	/*
		������Ϣ���.
		�����첽��Ϣ�ص����������ƣ�������֪ͨ�����������
		��Ӧ���뾡�졣����sdk���ܻ���Ϊ�����ۼ�̫��������⡣
	*/
	void H5SDKAPI OnReceived(Session *session, IHsCommMessage *response);
	/*
		SDK����������ӶϿ�.
	*/
	void H5SDKAPI OnClose(Session *session, int reason);
	/*
		session����
	*/
	void H5SDKAPI OnError(Session *session, int errorNo);
	/*
		���ӷ�������ʱ���ص�
	*/
	void H5SDKAPI OnCore(Session *session);

};