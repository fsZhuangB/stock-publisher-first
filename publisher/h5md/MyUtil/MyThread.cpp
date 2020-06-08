/** @file
* 行情Demo.MyThread
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/

#include "MyThread.h"
#include "string.h"


#if	!defined(_WIN32) && !defined(_WIN32_WCE)
int __ortp_thread_join(my_thread_t MyThread, void **ptr){
	int err=pthread_join(MyThread,ptr);
	if (err!=0) {
	}
	return err;
}

int __ortp_thread_create(pthread_t *MyThread, pthread_attr_t *attr, void * (*routine)(void*), void *arg){
	pthread_attr_t my_attr;
	pthread_attr_init(&my_attr);
	if (attr)
		my_attr = *attr;
#ifdef ORTP_DEFAULT_THREAD_STACK_SIZE
	if (ORTP_DEFAULT_THREAD_STACK_SIZE!=0)
		pthread_attr_setstacksize(&my_attr, ORTP_DEFAULT_THREAD_STACK_SIZE);
#endif
	return pthread_create(MyThread, &my_attr, routine, arg);
}
// 1 for time out, 0 for cond
int __my_thread_cond_timewait(my_cond_t *cond, my_mutex_t *mutex, unsigned long microsecond)
{
	timeval now;
	timespec to;
	gettimeofday(&now,NULL);  
	to.tv_sec   = now.tv_sec + microsecond / 1000;
	to.tv_nsec  = now.tv_usec * 1000 + (microsecond - ((microsecond / 1000) * 1000)) * 1000000;
	if (to.tv_nsec >= 1000000000)
	{
		to.tv_sec += to.tv_nsec / 1000000000;
		to.tv_nsec %= 1000000000;
	}
	return (pthread_cond_timedwait(cond, mutex, &to) == ETIMEDOUT);
}
#endif

#if	defined(_WIN32) || defined(_WIN32_WCE)

int win_mutex_init(my_mutex_t *mutex, void *attr)
{
	*mutex=CreateMutex(NULL, FALSE, NULL);
	return 0;
}

int win_mutex_lock(my_mutex_t * hMutex)
{
	WaitForSingleObject(*hMutex, INFINITE); /* == WAIT_TIMEOUT; */
	return 0;
}

int win_mutex_unlock(my_mutex_t * hMutex)
{
	ReleaseMutex(*hMutex);
	return 0;
}

int win_mutex_destroy(my_mutex_t * hMutex)
{
	CloseHandle(*hMutex);
	return 0;
}

typedef struct thread_param{
	void * (*func)(void *);
	void * arg;
}thread_param_t;

static unsigned WINAPI thread_starter(void *data){
	thread_param_t *params=(thread_param_t*)data;
	void *ret=params->func(params->arg);
	free(data);
	return (DWORD)ret;
}

#if defined WIN32
#    define _beginthreadex	CreateThread
#    define	_endthreadex	ExitThread
#endif

int win_thread_create(my_thread_t *th, void *attr, void * (*func)(void *), void *data)
{
	thread_param_t *params=(thread_param_t*)malloc(sizeof(thread_param_t));
	params->func=func;
	params->arg=data;
	*th=(HANDLE)_beginthreadex( NULL, 0, (LPTHREAD_START_ROUTINE)thread_starter, params, 0, NULL);
	return 0;
}

int win_thread_join(my_thread_t thread_h, void **unused)
{
	if (thread_h!=NULL)
	{
		WaitForSingleObject(thread_h, INFINITE);
		CloseHandle(thread_h);
	}
	return 0;
}

int win_thread_exit(my_thread_t MyThread)
{
	CloseHandle(MyThread);
	return 0;
}

int win_cond_init(my_cond_t *cond, void *attr)
{
	*cond=CreateEvent(NULL, FALSE, FALSE, NULL);
	return 0;
}

int win_cond_wait(my_cond_t* hCond, my_mutex_t * hMutex)
{
	//gulp: this is not very atomic ! bug here ?
	win_mutex_unlock(hMutex);
	WaitForSingleObject(*hCond, INFINITE);
	win_mutex_lock(hMutex);
	return 0;
}

int win_cond_signal(my_cond_t * hCond)
{
	SetEvent(*hCond);
	return 0;
}

int win_cond_broadcast(my_cond_t * hCond)
{
	win_cond_signal(hCond);
	return 0;
}

int win_cond_destroy(my_cond_t * hCond)
{
	CloseHandle(*hCond);
	return 0;
}
// 1 for time out, 0 for hcond
int win_cond_timewait(my_cond_t * hCond, my_mutex_t * hMutex, unsigned long microsecond)
{
	//gulp: this is not very atomic ! bug here ?
	DWORD dwRet;
	win_mutex_unlock(hMutex);
	dwRet = WaitForSingleObject(*hCond, microsecond);
	win_mutex_lock(hMutex);
	return (dwRet ==  WAIT_TIMEOUT);
}
#endif

namespace HsHqSdkDemo{
MyThread::MyThread(const char* name)
{
	m_bExit = true ;
	my_cond_init(&m_cond,NULL);
	my_mutex_init(&m_mutex,NULL) ;
	m_set_thread_name = false;
	if (name != NULL)
	{
		m_set_thread_name = true;
		strncpy(m_name, name, 64);
		m_name[63] = 0;
	}
}
MyThread::~MyThread()
{
	Stop();
	my_mutex_destroy(&m_mutex);
	my_cond_destroy(&m_cond);
}
void* MyThread::Run(void *pv)
{
	MyThread *pthread= static_cast<MyThread*>(pv);
	return (void*)(pthread->RunThread());
}

int MyThread::RunThread()
{
	if (m_set_thread_name)
		SetThreadName(m_name);

	MainFun() ;

	return 0 ;
}

void MyThread::SetThreadName(const char* name)
{
#ifdef WIN32
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // must be 0x1000
		LPCSTR szName; // pointer to name (in user addr space)
		DWORD dwThreadID; // MyThread ID (-1=caller MyThread)
		DWORD dwFlags; // reserved for future use, must be zero
	} THREADNAME_INFO;


	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.dwThreadID = GetCurrentThreadId();
	info.dwFlags = 0;
	info.szName = name;

	__try
	{
#ifdef _WIN64
		RaiseException(0x406D1388, 0, sizeof(info)/sizeof(DWORD), (ULONG_PTR*)&info);
#else
		RaiseException(0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info);
#endif
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{

	}
#else
//	prctl(PR_SET_NAME, name) ;
#endif
}

bool MyThread::Start()
{
	m_bExit = false ;
	int iRet = my_thread_create(&m_pid,NULL,&MyThread::Run,this);
	return (iRet == 0 );
}

void MyThread::Active()
{
	if(m_bExit)
		return;

	my_cond_signal(&m_cond);
}

bool MyThread::IsActive(int timeout)
{
	my_mutex_lock(&m_mutex);
	my_cond_timewait(&m_cond, &m_mutex,timeout);
	my_mutex_unlock(&m_mutex);	
	return (!m_bExit);
}


void MyThread::Stop()
{
	if (m_bExit)
		return;
	m_bExit = true ;
	my_cond_signal(&m_cond);
	
//#if !defined(ANDROID) && !defined(IOS)
//	void *retVal = NULL ;
//	my_thread_join(m_pid,&retVal);
//#endif
	my_thread_join(m_pid, NULL);
}


MyMutex::MyMutex()
{
	my_mutex_init(&m_mutex, NULL);
}
MyMutex::~MyMutex()
{
	my_mutex_destroy(&m_mutex);
}

void MyMutex::Lock()
{
	my_mutex_lock(&m_mutex);
}
void MyMutex::Unlock()
{
	my_mutex_unlock(&m_mutex);
}
};
