/** @file
* ����Demo.��Ϣ����
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/


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
	��Ϣ���У���ȡ��Ϣ��
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

		//���д�����󣬵ȴ���һ����Ϣ���
		m_eventWait.Wait(-1);
	}
	return NULL;
}

/*
	��Ϣ���У�������Ϣ��
*/
void MyMessageQueue::Post_Message(MyCommandType status, WPARAM wParam, LPARAM lParam)
{
	MyMessage *pMessage = new MyMessage(status, wParam, lParam);

	m_mutexData.Lock();
	m_listMessage.push_back(pMessage);
	m_mutexData.Unlock();

	m_eventWait.Set();//֪ͨ��Ϣ�Ⱥ�
}
