/** @file
* 行情Demo.MyThread
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/

#pragma once

#ifdef WIN32
	#include <wtypes.h>
	typedef HANDLE my_cond_t;
	typedef HANDLE my_mutex_t;
	typedef HANDLE my_thread_t;

	#define my_mutex_init	win_mutex_init
	#define my_mutex_lock	win_mutex_lock
	#define my_mutex_unlock	win_mutex_unlock
	#define my_mutex_destroy	win_mutex_destroy
	#define my_thread_create	win_thread_create
	#define my_thread_join	win_thread_join
	#define my_thread_exit   win_thread_exit
	#define my_cond_init		win_cond_init
	#define my_cond_signal	win_cond_signal
	#define my_cond_broadcast	win_cond_broadcast
	#define my_cond_wait		win_cond_wait
	#define my_cond_timewait	win_cond_timewait
	#define my_cond_destroy	win_cond_destroy

	#ifdef __cplusplus
	extern "C"
	{
	#endif

		int win_mutex_init(my_mutex_t *m, void *attr_unused);
		int win_mutex_lock(my_mutex_t *mutex);
		int win_mutex_unlock(my_mutex_t *mutex);
		int win_mutex_destroy(my_mutex_t *mutex);
		int win_thread_create(my_thread_t *t, void *attr_unused, void *(*func)(void*), void *arg);
		int win_thread_join(my_thread_t MyThread, void **unused);
		int win_thread_exit(my_thread_t MyThread);
		int win_cond_init(my_cond_t *cond, void *attr_unused);
		int win_cond_wait(my_cond_t * cond, my_mutex_t * mutex);
		int win_cond_timewait(my_cond_t * cond, my_mutex_t * mutex, unsigned long microsecond);
		int win_cond_signal(my_cond_t * cond);
		int win_cond_broadcast(my_cond_t * cond);
		int win_cond_destroy(my_cond_t * cond);

	#ifdef __cplusplus
	}
	#endif

#else

	#include <sys/socket.h>
	#include <pthread.h>
	#include <sys/time.h>

	#ifndef ETIMEDOUT
	#define ETIMEDOUT 110
	#endif

	typedef pthread_t my_thread_t;
	typedef pthread_mutex_t my_mutex_t;
	typedef pthread_cond_t my_cond_t;

	#ifdef __cplusplus
	extern "C"
	{
	#endif
		int __my_thread_join(my_thread_t MyThread, void **ptr);
		int __my_thread_create(pthread_t *MyThread, pthread_attr_t *attr, void * (*routine)(void*), void *arg);
		int __my_thread_cond_timewait(my_cond_t *cond, my_mutex_t *mutex, unsigned long microsecond);
	#ifdef __cplusplus
	}
	#endif

	#define my_thread_create	__ortp_thread_create
	#define my_thread_join	__ortp_thread_join
	#define my_thread_exit	pthread_exit
	#define my_mutex_init	pthread_mutex_init
	#define my_mutex_lock	pthread_mutex_lock
	#define my_mutex_unlock	pthread_mutex_unlock
	#define my_mutex_destroy	pthread_mutex_destroy
	#define my_cond_init		pthread_cond_init
	#define my_cond_signal	pthread_cond_signal
	#define my_cond_broadcast	pthread_cond_broadcast
	#define my_cond_wait		pthread_cond_wait
	#define my_cond_timewait	__my_thread_cond_timewait

	#define my_cond_destroy	pthread_cond_destroy
#endif

namespace HsHqSdkDemo
{
	class MyMutex{
	public:
		MyMutex();
		~MyMutex();

		void Lock();
		void Unlock();
	private:
		my_mutex_t m_mutex;
	};
	class MyThread
	{
	public:
		MyThread(const char* name = NULL);
		~MyThread();
		static void* Run(void *pv);
		int RunThread();
		virtual int MainFun() = 0 ;
		void SetThreadName(const char* name);
		bool IsActive(int timeout) ;
		void Active();
		bool Start() ;
		void Stop() ;
	public:
		bool m_bExit ;
	private:
		char m_name[64];
		bool m_set_thread_name;
		my_thread_t m_pid;
		my_cond_t m_cond;
		my_mutex_t m_mutex;
	};
}
