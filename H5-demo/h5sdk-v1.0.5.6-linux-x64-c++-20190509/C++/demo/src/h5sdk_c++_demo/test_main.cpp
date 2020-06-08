#include <stdio.h>
#include "main_environment.h"

int main()
{
    MyEnvironment env;
    if (!env.Init())
    {
        my_log("bad init");
        getchar();
        return 0;
    }

    MyMessage *pMessage = NULL;
    // use peek message to get the message
    while (pMessage = MyEnvironment::PeekMainMessage())
    {
        // then we get the command type from pMessage
        // and make a comparison with the callback type
        if (pMessage->m_commandType == Command_SdkCallback)
        {
            if (pMessage->m_wParam == SdkCallback_Login)
            {
                MyEnvironment::GetHqSdkUtil()->SetLoginStatus((bool)pMessage->m_lParam);
            }
            else if (pMessage->m_wParam == SdkCallback_Server_Info)
            {

            }
        }

        if (env.GetWaitforMessageSize() > 0)
        {
            if (!env.WaitforMessageAndHandleIt(pMessage))
            {
                delete pMessage;
                break;
            }

        }
        else
        {
            /* if there's no waiting message, that'll be keyboard selection */
            if (pMessage->m_commandType == Command_KeyInput)
            {
                if(! env.SelectMenu(pMessage->m_wParam))
				{
					delete pMessage;
					break;//'q',return false,ÍË³ö³ÌĞò
				}
            }  
        }
        delete pMessage;
    }
    return 0;
}