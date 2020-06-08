/** @file
* 行情Demo.MyAutoLock
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#include "MyAutoLock.h"
namespace HsHqSdkDemo
{
	MyAutoLock::MyAutoLock(MyMutex& mutex):m_mutex(mutex)
	{
		m_mutex.Lock();
	}

	MyAutoLock::~MyAutoLock()
	{
		m_mutex.Unlock();
	}
};
