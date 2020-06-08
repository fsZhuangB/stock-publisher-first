/** @file
* 行情Demo.MyAutoLock
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#pragma once

#include "MyThread.h"

namespace HsHqSdkDemo
{
	class MyAutoLock
	{
	public:
		MyAutoLock(MyMutex& mutex);
		~MyAutoLock() ;
	private:
		MyMutex& m_mutex ;
	};

	template<class T>
	class MyAutoPointer
	{
	public:
		T * m_pT;

	public:
		MyAutoPointer(T * p) : m_pT(p){}
		~MyAutoPointer(void){ delete m_pT; }
	};
}
