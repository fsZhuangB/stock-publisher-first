/** @file
* ����demo.�ص����
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/

#include "sdk_util.h"
#include "sdk_callback.h"
#include "sdk_util.h"
#include <string.h>
#include "sdk_data_parser.h"
#include "main_message_queue.h"
#include "main_environment.h"

#ifdef WIN32
#undef H5SDKAPI
#define H5SDKAPI
#endif
/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	�����ٶȣ��ص���
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
/*
	���ٳɹ�
*/
int H5SDKAPI MyVelocimetryCallback::OnVelocimetrySucceed(Endpoint *endpoint, int delay, int load)
{
	if(! endpoint)
	{
		my_log("\tMyVelocimetryCallback::OnVelocimetrySucceed endpoint=null\n");
		return 0;
	}
	my_log("\t%s:\n\t\t���ٳɹ� endpoint=%s delay=%d(������Ӧ�ٶ�.����) load=%d%%(����������ʹ�õ���Դ)\n",__FUNCTION__, endpoint->userData, delay, load);
	return 0;
}

/*
	����ʧ��
*/
int H5SDKAPI MyVelocimetryCallback::OnVelocimetryFail(Endpoint *endpoint, VelocimetryErrorNo errorNo)
{
	if(! endpoint)
	{
		printf("\tMyVelocimetryCallback::OnVelocimetryFail endpoint=null\n");
		return 0;
	}
	my_log("\t%s:\n\t\t����ʧ�� endpoint=%s errNo=%d\n",__FUNCTION__, endpoint->userData, errorNo);
	return 0;
}

/*
	���ٽ���
*/
int H5SDKAPI MyVelocimetryCallback::OnVelocimetryComplete()
{
	my_log("\t%s:\n\t\t���ٽ���.\n",__FUNCTION__);
	MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_SpeedTest);
	return 0;
}
/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	����SDK�ص�
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

/*
	����������ӳɹ�.(��û��½.)
*/
void H5SDKAPI H5SdkCallbackImpl::OnConnect(Session *session, const char *peerIp, int peerPort, const char *localIp, int localPort) 
{
	if(! session)
	{
		printf("\tH5SdkCallbackImpl::OnConnect session=null\n");
		return;
	}
	if(! peerIp)
	{
		printf("\tH5SdkCallbackImpl::OnConnect peerIp=null\n");
		return;
	}
	if(! localIp)
	{
		printf("\tH5SdkCallbackImpl::localIp session=null\n");
		return;
	}
	// �Ѿ�������Tcp����
	my_log("\t%s:\n\t\t�������� ������%s:%d ����%s:%d\n", __FUNCTION__, peerIp, peerPort, localIp, localPort);

	//�첽Sdk��¼
	session->AsyncSdkLogin(2000/*��ʱʱ��, 1��*/);
}

/*
	SDK��½���
*/
void H5SDKAPI H5SdkCallbackImpl::OnSdkLogin(Session *session) 
{
	if(! session)
	{
		my_log("\tH5SdkCallbackImpl::OnSdkLogin session=null\n");
		return;
	}
	// ��Sdk��¼�ɹ���ص�
	my_log("\t%s:\n\t\tsdk��½���\n",__FUNCTION__);

	//�û���½.ͬ��.
	my_log("\t�û���¼��ʼ.\n");
	LoginAnsInfo *lp=session->LoginByUser(MyEnvironment::GetHqSdkUtil()->m_strUser.c_str(), MyEnvironment::GetHqSdkUtil()->m_strPass.c_str());
	if (lp && lp->GetResult() && strcmp(lp->GetResult(),"suc") == 0)
	{
		my_log("\t��¼�ɹ�.\n");
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Login, (WPARAM)true);
	}
	else
	{
		my_log("\t��¼ʧ��.\n");
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Login, (WPARAM)false);
	}
	if(lp)//ע���ͷ�
		lp->Release();
}
/*
	������Ϣ���.
	�����첽��Ϣ�ص����������ƣ�������֪ͨ�����������
	��Ӧ���뾡�졣����sdk���ܻ���Ϊ�����ۼ�̫��������⡣
*/
void H5SDKAPI H5SdkCallbackImpl::OnReceived(Session *session, IHsCommMessage *response) 
{
	if(!session)
	{
		my_log("\tH5SdkCallbackImpl::OnReceived session=null\n");
		return;
	}
	if(!response)
	{
		my_log("\tH5SdkCallbackImpl::OnReceived response=null\n");
		return;
	}

	MyEnvironment::GetSdkBufferHandler()->Store2Buffer(response);
}
/*
	SDK����������ӶϿ�.
*/
void H5SDKAPI H5SdkCallbackImpl::OnClose(Session *session, int reason) 
{
	if(!session)
	{
		my_log("\tH5SdkCallbackImpl::OnClose session=null\n");
		return;
	}
	// ���Ự���ӶϿ�ʱ�ص�
	my_log("\t%s: close reason=%d\n",__FUNCTION__, reason);

	// Ϊ��ʵ�ֶϿ�������������OnClose�﷢��AsyncConnect����
	my_log("\tsession�Ͽ���������������\r\n");

	session->AsyncConnect();

}
/*
	session����
*/
void H5SDKAPI H5SdkCallbackImpl::OnError(Session *session, int errorNo) 
{
	if(!session)
	{
		my_log("\tH5SdkCallbackImpl::OnError session=null\n");
		return;
	}

	// ���Ự����ʱ�ص�
	my_log("\t%s: onError errNo=%d\n",__FUNCTION__, errorNo);

	my_log("\t������������\r\n");
	session->AsyncConnect();
}

/*
	���ӷ�������ʱ���ص�
*/
void H5SDKAPI H5SdkCallbackImpl::OnCore(Session *session) 
{
	if(!session)
	{
		my_log("\tH5SdkCallbackImpl::OnCore session=null\n");
		return;
	}
	// ���Ựһֱ�޷����Ϸ����ʱ�ص�
	my_log("%s (�޷����ӷ�����.ip���󣬻���app_key,app_secret���󣬻����������)\r\n",__FUNCTION__);

	// Ϊ��ʵ�ּ���������������OnCore�﷢��AsyncConnect����
	session->AsyncConnect();
}

