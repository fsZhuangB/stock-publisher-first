/** @file
* 行情Demo.MyEvent
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#include "MyEvent.h"

namespace HsHqSdkDemo
{
	MyEvent::MyEvent()
	{
		my_cond_init(&m_cond,NULL);
		my_mutex_init(&m_mutex,NULL) ;
	}
	MyEvent::~MyEvent()
	{
		my_cond_destroy(&m_cond);
		my_mutex_destroy(&m_mutex);
	}

	bool MyEvent::Wait(unsigned long timeout)
	{//防止多个线程被点亮。
		my_mutex_lock(&m_mutex);
		bool ret = (my_cond_timewait(&m_cond, &m_mutex, timeout) != 1);
		my_mutex_unlock(&m_mutex);
		return ret;
	}

	void MyEvent::Set()
	{
		my_cond_signal(&m_cond);
	}
}

