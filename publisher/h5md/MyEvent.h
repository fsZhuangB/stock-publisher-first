/** @file
* ����Demo.MyEvent
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/
#pragma once

#include "MyThread.h"

namespace HsHqSdkDemo
{
	class MyEvent
	{
	public :
		MyEvent() ;
		~MyEvent() ;
		bool Wait(unsigned long timeout) ;
		void Set() ;	
	private:
		my_cond_t m_cond;
		my_mutex_t m_mutex ;
	};
}

