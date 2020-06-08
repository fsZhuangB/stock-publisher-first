/** @file
* 行情Demo.消息队列
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#include "my_vld.h"

#include "main_message_queue.h"

MyMessageQueue::~MyMessageQueue()
{
	list<MyMessage *>::iterator it;
	for(it = m_listMessage.begin(); it != m_listMessage.end(); it ++)
	{
		if(*it)
		{
			delete *it;
		}
	}
	m_listMessage.clear();
}
/*
	消息队列，获取消息。
*/
MyMessage *MyMessageQueue::Peek_Message(void)
{
	while(1)
	{
		m_mutexData.Lock();
		if(m_listMessage.size() > 0)
		{
			MyMessage *pMessage = *m_listMessage.begin();
			m_listMessage.pop_front();

			m_mutexData.Unlock();

			return pMessage;
		}
		m_mutexData.Unlock();

		//队列处理完后，等待下一个消息到达。
		m_eventWait.Wait(-1);
	}
	return NULL;
}

/*
	消息队列，发送消息。
*/
void MyMessageQueue::Post_Message(MyCommandType status, WPARAM wParam, LPARAM lParam)
{
	MyMessage *pMessage = new MyMessage(status, wParam, lParam);

	m_mutexData.Lock();
	m_listMessage.push_back(pMessage);
	m_mutexData.Unlock();

	m_eventWait.Set();//通知消息等候
}
