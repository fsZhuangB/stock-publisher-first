// /** @file
// * ����Demo.main
// * @author  �Ŵ���
// * @author  �������ӹɷ����޹�˾
// * @version 1.0
// * @date    20160815
// */
// #include "my_vld.h"

// #include <stdio.h>
// #include "main_environment.h"

// int main(int argc, char* argv[])
// {
// 	MyEnvironment myEnvironment;
// 	if(! myEnvironment.Init())
// 	{
// 		my_log("��ʼ��ʧ��,�س��˳�\n");
// 		getchar();
// 		return 0;
// 	}

// 	MyMessage *pMessage = NULL;
// 	while(pMessage = MyEnvironment::PeekMainMessage())
// 	{
// 		/*
// 			��Ӧ��Ϣ
// 		*/
// 		if(pMessage->m_commandType == Command_SdkCallback)
// 		{
// 			if(pMessage->m_wParam == SdkCallback_Login)
// 			{//��½��������¼״̬
// 				MyEnvironment::GetHqSdkUtil()->SetLoginStatus((bool)pMessage->m_lParam);
// 			}
// 			else if(pMessage->m_wParam == SdkCallback_Server_Info)
// 			{//�г���ʼ������Ҫ����ȡ�г���Ϣ�����¶���!!!

// 			}
// 		}
		
// 		if(myEnvironment.GetWaitforMessageSize() > 0)
// 		{
// 			/*
// 				���������غ����Ϣ��
// 			*/
// 			if(! myEnvironment.WaitforMessageAndHandleIt(pMessage))
// 			{
// 				delete pMessage;
// 				break;//�˳�����
// 			}
// 		}
// 		else
// 		{
// 			//û�ȴ�����Ϣ������Ǽ������룬���ǲ˵�ѡ�
// 			if(pMessage->m_commandType == Command_KeyInput)
// 			{
// 				if(! myEnvironment.SelectMenu(pMessage->m_wParam))
// 				{
// 					delete pMessage;
// 					break;//'q',return false,�˳�����
// 				}
// 			}
// 		}

// 		delete pMessage;
// 	}//������Ϣ����
// 	return 0;
// }
