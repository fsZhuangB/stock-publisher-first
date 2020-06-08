/** @file
* ����Demo.ģ�⻷��
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/
#include "my_vld.h"

#include "main_environment.h"
#include "sdk_data_parser.h"

HqSdkUtil *MyEnvironment::GetHqSdkUtil() //����SDK������
{
	return m_pHqSdkUtil;
}

void MyEnvironment::PostMainMessage(MyCommandType status, WPARAM wParam, LPARAM lParam)
{
	if(m_pMainMessageQueue)
		m_pMainMessageQueue->Post_Message(status, wParam, lParam);
}
MyMessage *MyEnvironment::PeekMainMessage(void)
{
	if(m_pMainMessageQueue)
		return m_pMainMessageQueue->Peek_Message();
	return NULL;
}

SdkBufferHandler * MyEnvironment::GetSdkBufferHandler(void)
{
	return m_pSdkBufferHandler;
}

KeyboardInputThread * MyEnvironment::GetKeyboardInputThread(void)
{
	return m_pKeyboardInputThread;
}

HqSdkUtil *MyEnvironment::m_pHqSdkUtil; //����SDK������
MyMessageQueue * MyEnvironment::m_pMainMessageQueue;		//��Ϣ����
SdkBufferHandler * MyEnvironment::m_pSdkBufferHandler; //�����߳�
KeyboardInputThread * MyEnvironment::m_pKeyboardInputThread;//���������߳�
list<MyProdCode> MyEnvironment::m_listCodes; //��ǰ����ʹ�õĴ��롣


/////////////////////////////////////////////////////////////////////////////////////////////////////
MyEnvironment::MyEnvironment()
{
	m_pHqSdkUtil = NULL; //����SDK������
	m_pMainMessageQueue = NULL;		//��Ϣ����
	m_pSdkBufferHandler = NULL; //�����߳�
	m_pKeyboardInputThread = NULL;//���������߳�
}

/*
	��������
*/
MyEnvironment::~MyEnvironment()
{
	/*/////////////////////////////////////////////////////////////////////////////////////////
	//sdk�ر�.
	//////////////////////////////////////////////////////////////////////////////////////////*/
	if(m_pHqSdkUtil)
	{
		m_pHqSdkUtil->sdk_close();
		delete m_pHqSdkUtil;
	}
	
	//������Ϣ�̹߳ر�
	if(m_pKeyboardInputThread)
	{
		delete m_pKeyboardInputThread;
	}
	
	//�����̹߳ر�
	if(m_pSdkBufferHandler)
	{
		delete m_pSdkBufferHandler;
	}
	
	//��Ϣ�������
	if(m_pMainMessageQueue)
	{
		delete m_pMainMessageQueue;
	}
	
	//�����ڴ�
	Clear();
}

/*
	�����ڴ�
*/
void MyEnvironment::Clear()
{
	list<MyMessageWaitFor *>::iterator it;
	for(it = m_listCommand.begin(); it != m_listCommand.end(); it ++)
	{
		if(*it)
		{
			delete *it;
		}
	}
	m_listCommand.clear();
}

/*
	��ʼ������
*/
bool MyEnvironment::Init(void)
{
	//��Ϣ����
	m_pMainMessageQueue = new MyMessageQueue();

	//���崦���߳�
	m_pSdkBufferHandler = new SdkBufferHandler();
	m_pSdkBufferHandler->Start();

	//���������߳�
	m_pKeyboardInputThread = new KeyboardInputThread();
	m_pKeyboardInputThread->Start();
	/*////////////////////////////////////////////////////////////////////////////////////
	//Sdk��ʼ��
	////////////////////////////////////////////////////////////////////////////////////*/
	m_pHqSdkUtil = new HqSdkUtil();
	//���ļ����ȡ����
	if(! m_pHqSdkUtil->ReadConfigure())
	{
		my_log("read configure failed.\n");
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////*/
	//��ʼ��SDK
	if(! GetHqSdkUtil()->sdk_init())
	{
		my_log("sdk init failed.\n");
		return false;
	}

	//�������лỰ
	my_log("\t����SDK�Ự\n");

	WaitForMessage(Command_SdkCallback, SdkCallback_Login, OnLoginOver);
	WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);
	//Init������session����ʼ������������
	StartAllSessions();//��LoginByUser�ɹ�
	return true;
}

/*
	��ӦLogin��������½ʧ�ܣ��˳�����
*/
void MyEnvironment::WaitForMessage(MyCommandType commandType, int wParam, MyFuncCallback callback)
{//�ȴ�sdk���ö�����
	MyMessageWaitFor *pCommand = new MyMessageWaitFor(commandType, wParam, 0, callback);
	m_listCommand.push_back(pCommand);
}

/*
	�Ⱥ����Ϣsize.
*/
int	MyEnvironment::GetWaitforMessageSize()
{
	return m_listCommand.size();
}

/*
	�Ⱥ�ָ����Ϣ�������ض�����
	return false, �˳�����
	return true. ����
*/
bool MyEnvironment::WaitforMessageAndHandleIt(MyMessage *pMessage)
{
	if(pMessage == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return false;
	}

	bool bContinue = true;
	if(m_listCommand.size() == 0)
		return bContinue;//û���غ����Ϣ;

	//�������غ����Ϣ.
	MyMessageWaitFor *pMsgWaitFor = *m_listCommand.begin();

	if(! pMsgWaitFor)
		return bContinue;

	if(pMsgWaitFor->m_commandType == pMessage->m_commandType && pMsgWaitFor->m_wParam == pMessage->m_wParam)
	{//��ǰ��Ϣ�����ǵȺ����Ϣ����Ҫ�ж� m_lParam.
		if(pMsgWaitFor->m_funcCallback)
		{
			bContinue = pMsgWaitFor->m_funcCallback();//���ص�����.����false,�˳�����
		}
		//���غ򵽸���Ϣ��ȥ����
		delete pMsgWaitFor;
		m_listCommand.pop_front();
	}
	
	return bContinue;
}

/*
	��½����.�ص�
*/
bool MyEnvironment::OnLoginOver(void)
{//��½����
	if(! GetHqSdkUtil()->m_bLogin)
	{//��½,����ʧ��,�˳�����
		my_log("��½ʧ�� �˳�\n");
		return false;
	}

	PrintWaitForEnter();
	return true;
}

/*
	�ٶȲ��Խ���.�ص�
*/
bool MyEnvironment::OnSpeedTestOver(void)
{//�ٶȲ��Խ���������.
	if(GetHqSdkUtil()->m_velocimetry)
	{
		GetHqSdkUtil()->m_velocimetry->Stop();
		//!!!�ͷ�.
		GetHqSdkUtil()->m_velocimetry->Release();
	
		GetHqSdkUtil()->m_velocimetry = NULL;
	}
	
	PrintWaitForEnter();
	return true;
}

/*
	��ӡ��Ϣ.�ص�
*/
bool MyEnvironment::PrintWaitForEnter()
{
	my_log("�س� ����\n\n");
	return true;
}
	
/*
	�˳�����ģʽ.�ص�
*/
bool MyEnvironment::OnSubscribeOver()
{
	//���鶩��.�˶�
	GetHqSdkUtil()->SubscriberAll(&m_listCodes, false/*ͬ��*/, HSUB_ENUM_UNSUB/*�˶�*/);

	return true;
}

/*
	�˳�����ģʽ.�ص�
*/
bool MyEnvironment::OnSubscribeL2TranscationOver()
{
	//��ʳɽ�.�˶�
	GetHqSdkUtil()->SubL2Transcation(&m_listCodes, false/*ͬ��*/, HSUB_ENUM_UNSUB/*�˶�*/);//�˶�

	return true;
}

/*
	�˳�����ģʽ.�ص�
*/
bool MyEnvironment::OnSubscribeL2OrderOver()
{
	//���ί��.�˶�
	GetHqSdkUtil()->SubL2Order(&m_listCodes, false/*ͬ��*/, HSUB_ENUM_UNSUB/*�˶�*/);//�˶�

	return true;
}

/*
	�˳����ܲ���.�ص�
*/
bool MyEnvironment::OnCapabilityOver()
{
	GetHqSdkUtil()->m_mutexCapabilityTest.Lock();
	//���ܲ��ԣ���������
	MyCapabilityTest *pTemp = g_pMyCapabilityTest;

	//ֹͣ���ܲ��ԡ�
	g_pMyCapabilityTest = NULL;
	pTemp->Log();
	delete pTemp;
	GetHqSdkUtil()->m_mutexCapabilityTest.Unlock();

	PrintWaitForEnter();
	return true;
}

/*
	��ӡ�˵�
*/
bool MyEnvironment::PrintMenu(void)
{
	const char *strMenuText =
		"---------------------------------------\n"\
		"\t 1: �����ٶ�\n"\
		"\t 2: IP��ַ���л�����\n"\
		"\t 3: �Ͽ����Ӳ���\n"\
		"---------------------------------------\n"\
		"\t 4: �г�������Ϣ.ͬ��\n"\
		"\t 5: K Line.�첽\n"\
		"\t 6: ����.�첽\n"\
		"\t 7: ��ʱ.�첽\n"\
		"\t 8: ������ն���.���ơ�('q'�� �˳�)\n"\
		"---------------------------------------\n"\
		"\t 9: ��ʳɽ�.����.ͬ��('q'�� �˳�)(level2,û�˺ž�û��Ӧ)\n"\
		"\t a: ���ί��.����.ͬ��('q'�� �˳�)(level2,û�˺ž�û��Ӧ)\n"\
		"---------------------------------------\n"\
		"\t b: ���ܲ���.K��.\n"\
		"\t c: ���ܲ���.����.\n"\
		"---------------------------------------\n"\
		"\t Q: logout, �˳�\n"\
		"\t����ѡ��,�س�ȷ��\n"\
		"---------------------------------------\n\n";

	my_log(strMenuText);
	fflush(stdin);
	return true;
}
/*
	ѡ�����������
	����true��������
	����false,�˳�����
*/
bool MyEnvironment::SelectMenu(char ch)
{
	switch(ch)
	{
	case '1':
	{	/*/////////////////////////////////////////////////////////////////////////////////////////
		//�����ٶ�
		//////////////////////////////////////////////////////////////////////////////////////////*/
		WaitForMessage(Command_SdkCallback, SdkCallback_SpeedTest, OnSpeedTestOver);//�ȴ��ٶȲ��Խ���
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		GetHqSdkUtil()->speed_test();
		break;
	}
	case '2':
	{	//////////////////////////////////////////////////////////////////////////
		//IP��ַ���л�����
		//////////////////////////////////////////////////////////////////////////
		WaitForMessage(Command_SdkCallback, SdkCallback_Login, OnLoginOver);//�ȴ�:�л������µ�½�ɹ���
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		GetHqSdkUtil()->test_ip_switch();
		break;
	}
	case '3':
	{	////////////////////////////////////////////////////////////////////////////////
		//�Ͽ����Ӳ��� �� �鿴close�ص����������ص��������ص�reasonֵ,�Ƿ�Ϊ�ֶ��Ͽ�
		////////////////////////////////////////////////////////////////////////////////
		WaitForMessage(Command_SdkCallback, SdkCallback_Login, OnLoginOver);//�ȴ�:disconnect�����µ�½�ɹ���
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�
			
		GetHqSdkUtil()->test_disconnect();
		break;
	}
	case '4':
	{	/*/////////////////////////////////////////////////////////////////////////////////////////
		//�г�������Ϣ.ͬ��.
		//////////////////////////////////////////////////////////////////////////////////////////*/
		WaitForMessage(Command_SdkCallback, SdkCallback_Market_Types, PrintWaitForEnter);//�ȴ�callback����������
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		GetHqSdkUtil()->test_market_type(true);
		PostMainMessage(Command_SdkCallback, SdkCallback_Market_Types);//ͬ��������������Ϣ����ʾ��ǰ����������
		break;
	}
	case '5':
	{	/*/////////////////////////////////////////////////////////////////////////////////////////
		//K Line.�첽.
		//////////////////////////////////////////////////////////////////////////////////////////*/
		WaitForMessage(Command_SdkCallback, SdkCallback_Candle_By_Offset, PrintWaitForEnter);//�ȴ�callback����������
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		GetHqSdkUtil()->test_k_line("600570", "SS", 6, false);
		//test_k_line("090107", "XSHG.M", 6, false); //�������е�֤ȯ���룬����ȡK�ߡ��������
		break;
	}
	case '6':
	{
		/*/////////////////////////////////////////////////////////////////////////////////////////
		//�������.�첽.
		//////////////////////////////////////////////////////////////////////////////////////////*/
		m_listCodes.clear();
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		WaitForMessage(Command_SdkCallback, SdkCallback_Snapshot, PrintWaitForEnter);//�ȴ�callback����������
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�
			
		GetHqSdkUtil()->test_snapshot(&m_listCodes, 0, 0, false);
		break;
	}
	case '7':
	{
		/*/////////////////////////////////////////////////////////////////////////////////////////
		//��ʱ.�첽.
		//////////////////////////////////////////////////////////////////////////////////////////*/
		WaitForMessage(Command_SdkCallback, SdkCallback_Trend, PrintWaitForEnter);//�ȴ�callback����������
		WaitForMessage(Command_KeyInput, Key_Return, &PrintMenu);//�ȴ��س�.��ӡ�˵�
			
		GetHqSdkUtil()->test_trend("600570", "SS", false);
		break;
	}
	case '8':
	{
		//////////////////////////////////////////////////////////////////////////
		// ������ն���.���ơ�
		//////////////////////////////////////////////////////////////////////////
		//ȡ��֧����
		m_listCodes.clear();
		GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);
		GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);
		GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.SMSE", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);
	//	GetHqSdkUtil()->GetCodesInMarket("XSHG", &m_listCodes, 20000);
	//	GetHqSdkUtil()->GetCodesInMarket("XSHE", &m_listCodes, 20000);

		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);
	

		WaitForMessage(Command_KeyInput, Key_Quit, OnSubscribeOver);//�ȴ�'Q'.�˳�����ģʽ
		WaitForMessage(Command_SdkCallback, SdkCallback_Subscribe, PrintWaitForEnter);//�ȴ��˶�����������
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		//����
		my_log("\n\t��ʼ����\n");
		my_log("\n\t�����У�'q'�� �˳� !!!\r\n");
		GetHqSdkUtil()->SubscriberAll(&m_listCodes, true/*ͬ��*/, HSUB_ENUM_SUB_OVER/*����*/);
		break;
	}
	case '9':
	{
		/*/////////////////////////////////////////////////////////////////////////////////////////
		//��ʳɽ�.����.ͬ��
		//////////////////////////////////////////////////////////////////////////////////////////*/
		m_listCodes.clear();
		GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, 2/*ֻȡ��ô��*/);//ȡ�Ϻ��Ĵ��롣
		GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, 4/*ֻȡ��ô��*/);//ȡ���ڵĴ��롣
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		WaitForMessage(Command_KeyInput, Key_Quit, OnSubscribeL2TranscationOver);//�ȴ�'Q'.�˳�����ģʽ
		WaitForMessage(Command_SdkCallback, SdkCallback_Subscribe_L2_Transcation, PrintWaitForEnter);//�ȴ��˶�����������
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		my_log("\n\t��ʼ������ʳɽ�\n");
		my_log("\n\t�����У�'q'�� �˳� !!!\r\n");
		GetHqSdkUtil()->test_l2_transcation(&m_listCodes, true);
		break;
	}
	case 'A':
	{
		/*/////////////////////////////////////////////////////////////////////////////////////////
		//���ί��.����.ͬ��
		//////////////////////////////////////////////////////////////////////////////////////////*/
		m_listCodes.clear();
		GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, 2/*ֻȡ��ô��*/);//ȡ��ҵ���һ֧������ԡ�
		GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, 4/*ֻȡ��ô��*/);//ȡ��ҵ���һ֧������ԡ�
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		WaitForMessage(Command_KeyInput, Key_Quit, OnSubscribeL2OrderOver);//�ȴ�'Q'.�˳�����ģʽ
		WaitForMessage(Command_SdkCallback, SdkCallback_Subscribe_L2_Order, PrintWaitForEnter);//�ȴ��˶�����������
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		my_log("\n\t��ʼ�������ί��\n");
		my_log("\n\t�����У�'q'�� �˳� !!!\r\n");

		GetHqSdkUtil()->test_l2_order(&m_listCodes, true);
		break;
	}
	case 'B':
	{
		//////////////////////////////////////////////////////////////////////////
		// ���ܲ���.K��.
		//////////////////////////////////////////////////////////////////////////
		//ȡ��֧����
		m_listCodes.clear();
		#if 0 //ȫ�г���
		{
			GetHqSdkUtil()->GetCodesInMarket("SS", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/); 
			GetHqSdkUtil()->GetCodesInMarket("SZ", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/); 
		}
		#else
		{
			GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.SMSE", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/); 
		}
		#endif
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		my_log("\t���Դ���%d֧\n", m_listCodes.size());

		WaitForMessage(Command_SdkCallback, SdkCallback_Candle_By_Offset_Cabability, OnCapabilityOver);//�ȴ����ܲ��Խ�����
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		//ȡk��
		if(m_listCodes.size() > 0)
		{
			GetHqSdkUtil()->capability_k_line(&m_listCodes);
		}
		break;
	}
	case 'C':
	{
		//////////////////////////////////////////////////////////////////////////
		// ���ܲ���.����.
		//////////////////////////////////////////////////////////////////////////
		//ȡ��֧����
		m_listCodes.clear();
		#if 0 //ȫ�г���
		{
			GetHqSdkUtil()->GetCodesInMarket("SS", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/); 
			GetHqSdkUtil()->GetCodesInMarket("SZ", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/); 
		}
		#else
		{
			GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.SMSE", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/); 
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.NEEQ", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/); 
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.GEM", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/); 
		}
		#endif
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		my_log("\t���Դ���%d֧\n", m_listCodes.size());

		WaitForMessage(Command_SdkCallback, SdkCallback_Snapshot_Capability, OnCapabilityOver);//�ȴ����ܲ��Խ�����
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//�ȴ��س�.��ӡ�˵�

		//ȡk��
		if(m_listCodes.size() > 0)
		{
			GetHqSdkUtil()->capability_snapshot(&m_listCodes);
		}
		break;
	}
	case 'Q':
		//////////////////////////////////////////////////////////////////////////
		//�ǳ�����.
		//////////////////////////////////////////////////////////////////////////
		GetHqSdkUtil()->test_logout();
		return false;//�˳����򣬲�������
	default:
		break;
	}
	return true;
}

