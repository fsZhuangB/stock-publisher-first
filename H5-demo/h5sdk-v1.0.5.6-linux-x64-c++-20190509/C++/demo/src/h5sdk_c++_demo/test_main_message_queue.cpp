#include "main_message_queue.h"

MyMessage *MyMessageQueue::Peek_Message(void)
{
    while(1)
    {
        m_mutexData.Lock();
        if (m_listMessage.size() > 0)
        {
            MyMessage *pMessage = *m_listMessage.begin();
            m_listMessage.pop_front();
            m_mutexData.Unlock();
            // return the message
            return pMessage;
        }
        m_mutexData.Unlock();
        m_eventWait.Wait(-1);
    }
    return NULL;
}

// post message into m_message_list
void MyMessageQueue::Post_Message(MyCommandType status, WPARAM wParam, LPARAM lParam)
{
    MyMessage *pMessage = new MyMessage(status, wParam, lParam);
    m_mutexData.Lock();
    m_listMessage.push_back(pMessage);
    m_mutexData.Unlock();

	m_eventWait.Set();//通知消息等候
}