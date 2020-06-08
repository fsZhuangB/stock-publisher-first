/** @file
* ����Demo.MyAutoLock
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
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
