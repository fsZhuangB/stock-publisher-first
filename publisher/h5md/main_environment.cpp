/** @file
* 行情Demo.模拟环境
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#include "my_vld.h"

#include "main_environment.h"
#include "sdk_data_parser.h"

HqSdkUtil *MyEnvironment::GetHqSdkUtil() //行情SDK工具类
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

HqSdkUtil *MyEnvironment::m_pHqSdkUtil; //行情SDK工具类
MyMessageQueue * MyEnvironment::m_pMainMessageQueue;		//消息队列
SdkBufferHandler * MyEnvironment::m_pSdkBufferHandler; //缓冲线程
KeyboardInputThread * MyEnvironment::m_pKeyboardInputThread;//键盘输入线程
list<MyProdCode> MyEnvironment::m_listCodes; //当前正在使用的代码。


/////////////////////////////////////////////////////////////////////////////////////////////////////
MyEnvironment::MyEnvironment()
{
	m_pHqSdkUtil = NULL; //行情SDK工具类
	m_pMainMessageQueue = NULL;		//消息队列
	m_pSdkBufferHandler = NULL; //缓冲线程
	m_pKeyboardInputThread = NULL;//键盘输入线程
}

/*
	环境清理
*/
MyEnvironment::~MyEnvironment()
{
	/*/////////////////////////////////////////////////////////////////////////////////////////
	//sdk关闭.
	//////////////////////////////////////////////////////////////////////////////////////////*/
	if(m_pHqSdkUtil)
	{
		m_pHqSdkUtil->sdk_close();
		delete m_pHqSdkUtil;
	}
	
	//键盘消息线程关闭
	if(m_pKeyboardInputThread)
	{
		delete m_pKeyboardInputThread;
	}
	
	//缓冲线程关闭
	if(m_pSdkBufferHandler)
	{
		delete m_pSdkBufferHandler;
	}
	
	//消息队列清空
	if(m_pMainMessageQueue)
	{
		delete m_pMainMessageQueue;
	}
	
	//清理内存
	Clear();
}

/*
	清理内存
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
	初始化环境
*/
bool MyEnvironment::Init(void)
{
	//消息队列
	m_pMainMessageQueue = new MyMessageQueue();

	//缓冲处理线程
	m_pSdkBufferHandler = new SdkBufferHandler();
	m_pSdkBufferHandler->Start();

	//键盘输入线程
	m_pKeyboardInputThread = new KeyboardInputThread();
	m_pKeyboardInputThread->Start();
	/*////////////////////////////////////////////////////////////////////////////////////
	//Sdk初始化
	////////////////////////////////////////////////////////////////////////////////////*/
	m_pHqSdkUtil = new HqSdkUtil();
	//从文件里获取配置
	if(! m_pHqSdkUtil->ReadConfigure())
	{
		my_log("read configure failed.\n");
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////*/
	//初始化SDK
	if(! GetHqSdkUtil()->sdk_init())
	{
		my_log("sdk init failed.\n");
		return false;
	}

	//启动所有会话
	my_log("\t启动SDK会话\n");

	WaitForMessage(Command_SdkCallback, SdkCallback_Login, OnLoginOver);
	WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);
	//Init后，启动session，开始处理行情事务。
	StartAllSessions();//等LoginByUser成功
	return true;
}

/*
	响应Login动作。登陆失败，退出程序。
*/
void MyEnvironment::WaitForMessage(MyCommandType commandType, int wParam, MyFuncCallback callback)
{//等待sdk做该动作。
	MyMessageWaitFor *pCommand = new MyMessageWaitFor(commandType, wParam, 0, callback);
	m_listCommand.push_back(pCommand);
}

/*
	等候的消息size.
*/
int	MyEnvironment::GetWaitforMessageSize()
{
	return m_listCommand.size();
}

/*
	等候指定消息，并做特定处理
	return false, 退出程序。
	return true. 继续
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
		return bContinue;//没有守候的消息;

	//有正在守候的消息.
	MyMessageWaitFor *pMsgWaitFor = *m_listCommand.begin();

	if(! pMsgWaitFor)
		return bContinue;

	if(pMsgWaitFor->m_commandType == pMessage->m_commandType && pMsgWaitFor->m_wParam == pMessage->m_wParam)
	{//当前消息，正是等候的消息。不要判断 m_lParam.
		if(pMsgWaitFor->m_funcCallback)
		{
			bContinue = pMsgWaitFor->m_funcCallback();//做回调动作.返回false,退出程序
		}
		//已守候到该消息，去掉。
		delete pMsgWaitFor;
		m_listCommand.pop_front();
	}
	
	return bContinue;
}

/*
	登陆结束.回调
*/
bool MyEnvironment::OnLoginOver(void)
{//登陆结束
	if(! GetHqSdkUtil()->m_bLogin)
	{//登陆,并且失败,退出程序
		my_log("登陆失败 退出\n");
		return false;
	}

	PrintWaitForEnter();
	return true;
}

/*
	速度测试结束.回调
*/
bool MyEnvironment::OnSpeedTestOver(void)
{//速度测试结束，清理.
	if(GetHqSdkUtil()->m_velocimetry)
	{
		GetHqSdkUtil()->m_velocimetry->Stop();
		//!!!释放.
		GetHqSdkUtil()->m_velocimetry->Release();
	
		GetHqSdkUtil()->m_velocimetry = NULL;
	}
	
	PrintWaitForEnter();
	return true;
}

/*
	打印信息.回调
*/
bool MyEnvironment::PrintWaitForEnter()
{
	my_log("回车 继续\n\n");
	return true;
}
	
/*
	退出订阅模式.回调
*/
bool MyEnvironment::OnSubscribeOver()
{
	//行情订阅.退订
	GetHqSdkUtil()->SubscriberAll(&m_listCodes, false/*同步*/, HSUB_ENUM_UNSUB/*退定*/);

	return true;
}

/*
	退出订阅模式.回调
*/
bool MyEnvironment::OnSubscribeL2TranscationOver()
{
	//逐笔成交.退订
	GetHqSdkUtil()->SubL2Transcation(&m_listCodes, false/*同步*/, HSUB_ENUM_UNSUB/*退定*/);//退定

	return true;
}

/*
	退出订阅模式.回调
*/
bool MyEnvironment::OnSubscribeL2OrderOver()
{
	//逐笔委托.退订
	GetHqSdkUtil()->SubL2Order(&m_listCodes, false/*同步*/, HSUB_ENUM_UNSUB/*退定*/);//退定

	return true;
}

/*
	退出性能测试.回调
*/
bool MyEnvironment::OnCapabilityOver()
{
	GetHqSdkUtil()->m_mutexCapabilityTest.Lock();
	//性能测试，输出结果。
	MyCapabilityTest *pTemp = g_pMyCapabilityTest;

	//停止性能测试。
	g_pMyCapabilityTest = NULL;
	pTemp->Log();
	delete pTemp;
	GetHqSdkUtil()->m_mutexCapabilityTest.Unlock();

	PrintWaitForEnter();
	return true;
}

/*
	打印菜单
*/
bool MyEnvironment::PrintMenu(void)
{
	const char *strMenuText =
		"---------------------------------------\n"\
		"\t 1: 测试速度\n"\
		"\t 2: IP地址和切换测试\n"\
		"\t 3: 断开连接测试\n"\
		"---------------------------------------\n"\
		"\t 4: 市场分类信息.同步\n"\
		"\t 5: K Line.异步\n"\
		"\t 6: 快照.异步\n"\
		"\t 7: 分时.异步\n"\
		"\t 8: 行情快照订阅.主推。('q'键 退出)\n"\
		"---------------------------------------\n"\
		"\t 9: 逐笔成交.订阅.同步('q'键 退出)(level2,没账号就没响应)\n"\
		"\t a: 逐笔委托.订阅.同步('q'键 退出)(level2,没账号就没响应)\n"\
		"---------------------------------------\n"\
		"\t b: 性能测试.K线.\n"\
		"\t c: 性能测试.快照.\n"\
		"---------------------------------------\n"\
		"\t Q: logout, 退出\n"\
		"\t输入选项,回车确定\n"\
		"---------------------------------------\n\n";

	my_log(strMenuText);
	fflush(stdin);
	return true;
}
/*
	选择测试用例。
	返回true，继续。
	返回false,退出程序
*/
bool MyEnvironment::SelectMenu(char ch)
{
	switch(ch)
	{
	case '1':
	{	/*/////////////////////////////////////////////////////////////////////////////////////////
		//测试速度
		//////////////////////////////////////////////////////////////////////////////////////////*/
		WaitForMessage(Command_SdkCallback, SdkCallback_SpeedTest, OnSpeedTestOver);//等待速度测试结束
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		GetHqSdkUtil()->speed_test();
		break;
	}
	case '2':
	{	//////////////////////////////////////////////////////////////////////////
		//IP地址和切换测试
		//////////////////////////////////////////////////////////////////////////
		WaitForMessage(Command_SdkCallback, SdkCallback_Login, OnLoginOver);//等待:切换后，重新登陆成功。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		GetHqSdkUtil()->test_ip_switch();
		break;
	}
	case '3':
	{	////////////////////////////////////////////////////////////////////////////////
		//断开连接测试 ， 查看close回调方法，及回调方法返回的reason值,是否为手动断开
		////////////////////////////////////////////////////////////////////////////////
		WaitForMessage(Command_SdkCallback, SdkCallback_Login, OnLoginOver);//等待:disconnect后，重新登陆成功。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单
			
		GetHqSdkUtil()->test_disconnect();
		break;
	}
	case '4':
	{	/*/////////////////////////////////////////////////////////////////////////////////////////
		//市场分类信息.同步.
		//////////////////////////////////////////////////////////////////////////////////////////*/
		WaitForMessage(Command_SdkCallback, SdkCallback_Market_Types, PrintWaitForEnter);//等待callback动作结束。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		GetHqSdkUtil()->test_market_type(true);
		PostMainMessage(Command_SdkCallback, SdkCallback_Market_Types);//同步，主动发个消息。表示当前动作结束。
		break;
	}
	case '5':
	{	/*/////////////////////////////////////////////////////////////////////////////////////////
		//K Line.异步.
		//////////////////////////////////////////////////////////////////////////////////////////*/
		WaitForMessage(Command_SdkCallback, SdkCallback_Candle_By_Offset, PrintWaitForEnter);//等待callback动作结束。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		GetHqSdkUtil()->test_k_line("600570", "SS", 6, false);
		//test_k_line("090107", "XSHG.M", 6, false); //不是所有的证券代码，都能取K线。比如这个
		break;
	}
	case '6':
	{
		/*/////////////////////////////////////////////////////////////////////////////////////////
		//行情快照.异步.
		//////////////////////////////////////////////////////////////////////////////////////////*/
		m_listCodes.clear();
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		WaitForMessage(Command_SdkCallback, SdkCallback_Snapshot, PrintWaitForEnter);//等待callback动作结束。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单
			
		GetHqSdkUtil()->test_snapshot(&m_listCodes, 0, 0, false);
		break;
	}
	case '7':
	{
		/*/////////////////////////////////////////////////////////////////////////////////////////
		//分时.异步.
		//////////////////////////////////////////////////////////////////////////////////////////*/
		WaitForMessage(Command_SdkCallback, SdkCallback_Trend, PrintWaitForEnter);//等待callback动作结束。
		WaitForMessage(Command_KeyInput, Key_Return, &PrintMenu);//等待回车.打印菜单
			
		GetHqSdkUtil()->test_trend("600570", "SS", false);
		break;
	}
	case '8':
	{
		//////////////////////////////////////////////////////////////////////////
		// 行情快照订阅.主推。
		//////////////////////////////////////////////////////////////////////////
		//取多支代码
		m_listCodes.clear();
		GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/);
		GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/);
		GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.SMSE", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/);
	//	GetHqSdkUtil()->GetCodesInMarket("XSHG", &m_listCodes, 20000);
	//	GetHqSdkUtil()->GetCodesInMarket("XSHE", &m_listCodes, 20000);

		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);
	

		WaitForMessage(Command_KeyInput, Key_Quit, OnSubscribeOver);//等待'Q'.退出订阅模式
		WaitForMessage(Command_SdkCallback, SdkCallback_Subscribe, PrintWaitForEnter);//等待退订动作结束。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		//订阅
		my_log("\n\t开始订阅\n");
		my_log("\n\t推送中，'q'键 退出 !!!\r\n");
		GetHqSdkUtil()->SubscriberAll(&m_listCodes, true/*同步*/, HSUB_ENUM_SUB_OVER/*覆盖*/);
		break;
	}
	case '9':
	{
		/*/////////////////////////////////////////////////////////////////////////////////////////
		//逐笔成交.订阅.同步
		//////////////////////////////////////////////////////////////////////////////////////////*/
		m_listCodes.clear();
		GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, 2/*只取这么多*/);//取上海的代码。
		GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, 4/*只取这么多*/);//取深圳的代码。
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		WaitForMessage(Command_KeyInput, Key_Quit, OnSubscribeL2TranscationOver);//等待'Q'.退出订阅模式
		WaitForMessage(Command_SdkCallback, SdkCallback_Subscribe_L2_Transcation, PrintWaitForEnter);//等待退订动作结束。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		my_log("\n\t开始订阅逐笔成交\n");
		my_log("\n\t推送中，'q'键 退出 !!!\r\n");
		GetHqSdkUtil()->test_l2_transcation(&m_listCodes, true);
		break;
	}
	case 'A':
	{
		/*/////////////////////////////////////////////////////////////////////////////////////////
		//逐笔委托.订阅.同步
		//////////////////////////////////////////////////////////////////////////////////////////*/
		m_listCodes.clear();
		GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, 2/*只取这么多*/);//取创业版的一支代码测试。
		GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, 4/*只取这么多*/);//取创业版的一支代码测试。
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		WaitForMessage(Command_KeyInput, Key_Quit, OnSubscribeL2OrderOver);//等待'Q'.退出订阅模式
		WaitForMessage(Command_SdkCallback, SdkCallback_Subscribe_L2_Order, PrintWaitForEnter);//等待退订动作结束。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		my_log("\n\t开始订阅逐笔委托\n");
		my_log("\n\t推送中，'q'键 退出 !!!\r\n");

		GetHqSdkUtil()->test_l2_order(&m_listCodes, true);
		break;
	}
	case 'B':
	{
		//////////////////////////////////////////////////////////////////////////
		// 性能测试.K线.
		//////////////////////////////////////////////////////////////////////////
		//取多支代码
		m_listCodes.clear();
		#if 0 //全市场。
		{
			GetHqSdkUtil()->GetCodesInMarket("SS", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/); 
			GetHqSdkUtil()->GetCodesInMarket("SZ", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/); 
		}
		#else
		{
			GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/);
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/);
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.SMSE", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/); 
		}
		#endif
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		my_log("\t测试代码%d支\n", m_listCodes.size());

		WaitForMessage(Command_SdkCallback, SdkCallback_Candle_By_Offset_Cabability, OnCapabilityOver);//等待性能测试结束。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		//取k线
		if(m_listCodes.size() > 0)
		{
			GetHqSdkUtil()->capability_k_line(&m_listCodes);
		}
		break;
	}
	case 'C':
	{
		//////////////////////////////////////////////////////////////////////////
		// 性能测试.快照.
		//////////////////////////////////////////////////////////////////////////
		//取多支代码
		m_listCodes.clear();
		#if 0 //全市场。
		{
			GetHqSdkUtil()->GetCodesInMarket("SS", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/); 
			GetHqSdkUtil()->GetCodesInMarket("SZ", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/); 
		}
		#else
		{
			GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/);
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/);
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.SMSE", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/); 
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.NEEQ", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/); 
			GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.GEM", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*只取这么多*/); 
		}
		#endif
		MyProdCode code("600570", "SS");
		m_listCodes.push_back(code);

		my_log("\t测试代码%d支\n", m_listCodes.size());

		WaitForMessage(Command_SdkCallback, SdkCallback_Snapshot_Capability, OnCapabilityOver);//等待性能测试结束。
		WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);//等待回车.打印菜单

		//取k线
		if(m_listCodes.size() > 0)
		{
			GetHqSdkUtil()->capability_snapshot(&m_listCodes);
		}
		break;
	}
	case 'Q':
		//////////////////////////////////////////////////////////////////////////
		//登出测试.
		//////////////////////////////////////////////////////////////////////////
		GetHqSdkUtil()->test_logout();
		return false;//退出程序，不继续。
	default:
		break;
	}
	return true;
}

