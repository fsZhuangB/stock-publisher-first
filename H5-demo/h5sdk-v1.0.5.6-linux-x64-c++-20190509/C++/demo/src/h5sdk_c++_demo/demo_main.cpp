// /** @file
// * 行情Demo.main
// * @author  张春雷
// * @author  恒生电子股份有限公司
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
// 		my_log("初始化失败,回车退出\n");
// 		getchar();
// 		return 0;
// 	}

// 	MyMessage *pMessage = NULL;
// 	while(pMessage = MyEnvironment::PeekMainMessage())
// 	{
// 		/*
// 			响应消息
// 		*/
// 		if(pMessage->m_commandType == Command_SdkCallback)
// 		{
// 			if(pMessage->m_wParam == SdkCallback_Login)
// 			{//登陆结束，记录状态
// 				MyEnvironment::GetHqSdkUtil()->SetLoginStatus((bool)pMessage->m_lParam);
// 			}
// 			else if(pMessage->m_wParam == SdkCallback_Server_Info)
// 			{//市场初始化，需要重新取市场信息，重新订阅!!!

// 			}
// 		}
		
// 		if(myEnvironment.GetWaitforMessageSize() > 0)
// 		{
// 			/*
// 				处理正在守候的消息。
// 			*/
// 			if(! myEnvironment.WaitforMessageAndHandleIt(pMessage))
// 			{
// 				delete pMessage;
// 				break;//退出程序
// 			}
// 		}
// 		else
// 		{
// 			//没等待的消息，如果是键盘输入，就是菜单选项。
// 			if(pMessage->m_commandType == Command_KeyInput)
// 			{
// 				if(! myEnvironment.SelectMenu(pMessage->m_wParam))
// 				{
// 					delete pMessage;
// 					break;//'q',return false,退出程序
// 				}
// 			}
// 		}

// 		delete pMessage;
// 	}//继续消息队列
// 	return 0;
// }
