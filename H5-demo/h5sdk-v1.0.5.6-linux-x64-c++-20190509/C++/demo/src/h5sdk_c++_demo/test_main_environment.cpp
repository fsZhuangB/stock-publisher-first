#include "main_environment.h"
#include "sdk_data_parser.h"

// the utility tools, include server, callback function and so on
HqSdkUtil* MyEnvironment::GetHqSdkUtil()
{
    return m_pHqSdkUtil;
}

void MyEnvironment::PostMainMessage(MyCommandType status, WPARAM wParam, LPARAM lParam)
{
    if (m_pMainMessageQueue)
        m_pMainMessageQueue->Post_Message(status, wParam, lParam);
}

MyMessage* MyEnvironment::PeekMainMessage(void)
{
    if (m_pMainMessageQueue)
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

bool MyEnvironment::Init(void)
{
    m_pMainMessageQueue = new MyMessageQueue();

    m_pSdkBufferHandler = new SdkBufferHandler();
    m_pSdkBufferHandler->Start();

    m_pKeyboardInputThread = new KeyboardInputThread();
    m_pKeyboardInputThread->Start();

    m_pHqSdkUtil = new HqSdkUtil();

    	//从文件里获取配置
	if(! m_pHqSdkUtil->ReadConfigure())
	{
		my_log("read configure failed.\n");
		return false;
	}

    // SDK init
    if (!GetHqSdkUtil()->sdk_init())
    {
        my_log("sdk init failed.\n");
        return false;
    }

    WaitForMessage(Command_SdkCallback, SdkCallback_Login, OnLoginOver);
    WaitForMessage(Command_KeyInput, Key_Return, PrintMenu);

    StartAllSessions();
    return true;
}

void MyEnvironment::WaitForMessage(MyCommandType commandType, int wParam, MyFuncCallback callback)
{//等待sdk做该动作。
	MyMessageWaitFor *pCommand = new MyMessageWaitFor(commandType, wParam, 0, callback);
	m_listCommand.push_back(pCommand);
}

int	MyEnvironment::GetWaitforMessageSize()
{
	return m_listCommand.size();
}

bool MyEnvironment::WaitforMessageAndHandleIt(MyMessage* pMessage)
{
    if (pMessage == NULL)
    {
        printf("error");
        return false;
    }

    bool bContinue = true;

    // no command
    if (m_listCommand.size() == 0)
        return bContinue;

        MyMessageWaitFor* pMsgWaitFor = *m_listCommand.begin();

        if(!pMsgWaitFor)
            return bContinue;

        if (pMsgWaitFor->m_commandType == pMessage->m_commandType && pMsgWaitFor->m_wParam == pMessage->m_wParam)
        {
            if (pMsgWaitFor->m_funcCallback)
            {
                bContinue = pMsgWaitFor->m_funcCallback();
            }
            delete pMsgWaitFor;
            m_listCommand.pop_front();
        }
        return bContinue;
}

bool MyEnvironment::OnLoginOver(void)
{
    if (!GetHqSdkUtil()->m_bLogin)
    {
        // fail
    }

    PrintWaitForEnter();
    return true;
}

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

bool MyEnvironment::SelectMenu(char ch)
{
    switch (ch)
    {
    case '8':
        m_listCodes.clear();
        
        break;
    
    default:
        break;
    }
}