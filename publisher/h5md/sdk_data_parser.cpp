/** @file
* ����Demo.SDKʹ������
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/


#include "sdk_data_parser.h"
#include "sdk_util.h"
#include "main_message_queue.h"
#include "main_environment.h"

/*///////////////////////////////////////////////////////////////////////////////////////////////////
	sdk���ݰ�
///////////////////////////////////////////////////////////////////////////////////////////////////*/
CSdkPackage::CSdkPackage(IHsCommMessage* package)
{
	m_hsMsgPackage = package;
	m_timeReceived = getTickCount64();
}
CSdkPackage::~CSdkPackage()
{
	if(m_hsMsgPackage)
	{
		//�ͷ�!!!
		m_hsMsgPackage->Release();
	}
}
void CSdkPackage::Handle(void)
{
	bool bPackageOK = true;
	//�ж��Ƿ�ִ�гɹ�
	int headErrorNo = m_hsMsgPackage->GetHead()->GetItem(H5PROTO_TAG_ERROR_NO)->GetInt32();
	if(headErrorNo != 0)
	{//������
		int len = m_hsMsgPackage->GetHead()->GetItem(H5PROTO_TAG_USER_KEY)->GetRawDataLen(0); //ֻȡ��һ���û��Զ���Key.
		char *user_key = (char *)m_hsMsgPackage->GetHead()->GetItem(H5PROTO_TAG_USER_KEY)->GetRawData(&len);//�û������key.�������첽����һһ��Ӧ��
		my_log("\n\t%s: errNo=%d user_key=%s\n",__FUNCTION__,headErrorNo, user_key);

		bPackageOK = false;
	}

	int funcid = m_hsMsgPackage->GetFunction();
	if(funcid != 3001 && funcid != 3003 && funcid != 3004)//��ӡ�ص����ܺš�3001��ӡ�Ļ���̫��,���ԡ�
	{
		my_log("\t%s funcid=%d\n",__FUNCTION__, funcid);
	}

	switch (funcid)
	{
	case H5SDK_MSG_SNAPSHOT://�������3001
		if(bPackageOK)
		{
			if (m_hsMsgPackage->GetPacketType() == PUSH)
			{
			//	my_log("\t�����������:\n");//���ƴ���
			}
			else
			{
				my_log("\t�������.�첽����:\n");//��������
			}
			MyEnvironment::GetHqSdkUtil()->parse_snapshot(m_hsMsgPackage, this->m_timeReceived);
		}
		else
		{

		}

		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Snapshot);
		break;
	case H5SDK_MSG_L2_TRANSCATION://��ʳɽ�3003
		if(bPackageOK)
		{
			if (m_hsMsgPackage->GetPacketType() == PUSH)
			{
				my_log("\t��ʳɽ�����:\n");//���ƴ���
			}
			else
			{
				my_log("\t��ʳɽ�.�첽����:\n");//��������
			}
			MyEnvironment::GetHqSdkUtil()->parse_l2_order(m_hsMsgPackage, true);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_L2_Transcation);
		break;
	case H5SDK_MSG_L2_ORDER://���ί��3004
		if(bPackageOK)
		{
			if (m_hsMsgPackage->GetPacketType() == PUSH)
			{
				my_log("\t���ί������:\n");//���ƴ���
			}
			else
			{
				my_log("\t���ί��.�첽����:\n");//��������
			}
			MyEnvironment::GetHqSdkUtil()->parse_l2_order(m_hsMsgPackage, true);//����ʳɽ��Ĵ���һ����!!!
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_L2_Order);
		break;
	case H5SDK_MSG_MARKET_TYPES: // �г�������Ϣ
		if(bPackageOK)
		{
			my_log("\t�г�������Ϣ.�첽����:\n");
			MyEnvironment::GetHqSdkUtil()->parse_market_types(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Market_Types);
		break;
	case H5SDK_MSG_TREND://��ʱ
		{
			my_log("\t��ʱ.�첽����:\n");
			MyEnvironment::GetHqSdkUtil()->parse_trend(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Trend);
		break;
	case H5SDK_SERVER_INFO://��������Ϣ.�г���ʼ����֪ͨ�����ԣ����Ҫ֪ͨ�����̣߳������¶��ĵĶ�����
		if(bPackageOK)
		{
			my_log("\t��������Ϣ.�첽����:\n");
			MyEnvironment::GetHqSdkUtil()->parse_server_info(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Server_Info);
		break;
	case H5SDK_MSG_SUBSCRIBE://����.���Ļ�Ӧ.����������SDK���Զ�����.
		if(bPackageOK)
		{
			my_log("\t����.�첽����:\n");
			MyEnvironment::GetHqSdkUtil()->parse_subscribe(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Subscribe);
		break;
	case H5SDK_MSG_SUBSCRIBE_L2_TRANSCATION://���ί��.���Ļ�Ӧ.����������SDK���Զ�����.
		if(bPackageOK)
		{
			my_log("\t����.�첽����:\n");
			MyEnvironment::GetHqSdkUtil()->parse_subscribe_l2_transcation(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Subscribe_L2_Transcation);
		break;
	case H5SDK_MSG_SUBSCRIBE_L2_ORDER://���ί��.���Ļ�Ӧ.����������SDK���Զ�����.
		if(bPackageOK)
		{
			my_log("\t����.�첽����:\n");
			MyEnvironment::GetHqSdkUtil()->parse_subscribe_l2_order(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Subscribe_L2_Order);
		break;
	case H5SDK_MSG_CANDLE_BY_OFFSET://K�߻�Ӧ.
		if(bPackageOK)
		{
			my_log("\tK��.�첽����:\n");
			MyEnvironment::GetHqSdkUtil()->parse_k_line(m_hsMsgPackage, this->m_timeReceived);
		}
		else
		{

		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Candle_By_Offset);
		break;
	default:
		{
			//����ҵ����;
			my_log("\t���ݰ�.δ����. id=%d\n", funcid);
		}
	}
}
/*///////////////////////////////////////////////////////////////////////////////
	SDK�ص������ݻ���
///////////////////////////////////////////////////////////////////////////////*/
CSdkPackageQueue::CSdkPackageQueue()
{

}
CSdkPackageQueue::~CSdkPackageQueue()
{
	MyAutoLock lock(m_mutex);

	list<CSdkPackage *>::iterator it;
	for(it = m_listSdkPackage.begin(); it != m_listSdkPackage.end(); it ++)
	{
		delete *it;
	}
	m_listSdkPackage.clear();
}

/*
	���뻺��
*/
void CSdkPackageQueue::Push(IHsCommMessage* hsMsgPackage)
{
	if(hsMsgPackage == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	MyAutoLock lock(m_mutex);
	CSdkPackage *item = new CSdkPackage(hsMsgPackage);
	m_listSdkPackage.push_back(item);
}

/*
	�ӻ���ȡ��.
	ȡ����ָ�룬��Ҫ�ֶ�ɾ��
*/
CSdkPackage *CSdkPackageQueue::Pop(void)
{
	MyAutoLock lock(m_mutex);
	if(m_listSdkPackage.size() > 0)
	{
		CSdkPackage *pPackage = *m_listSdkPackage.begin();
		m_listSdkPackage.pop_front();
		return pPackage;
	}
	return NULL;
}

/*///////////////////////////////////////////////////////////////////////////////////////////////////
	SDK�������ݴ����߳�
///////////////////////////////////////////////////////////////////////////////////////////////////*/

/*
	sdk���ݰ����浽������
*/
void SdkBufferHandler::Store2Buffer(IHsCommMessage* hsMsgPackage)
{
	if(hsMsgPackage == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	m_sdkPackageQueue.Push(hsMsgPackage);
	Active();
}

CSdkPackage* SdkBufferHandler::GetFromBuffer()
{
	return m_sdkPackageQueue.Pop();
}
/*
	�߳����
*/
int SdkBufferHandler::MainFun()
{
	while(1)
	{
		if(m_bExit)
			break;

		CSdkPackage *item = GetFromBuffer();
		if(item)
		{
			item->Handle();
			delete item;
		}
		else
		{
			if(! IsActive(-1))//�ȴ������з����°���
				break;//m_bExit==true;
		}
	}
	return 0;
}