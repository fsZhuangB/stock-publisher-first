#ifndef __STRATEGY_LOG_H__
#define __STRATEGY_LOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <pthread.h>
#include <string>

//class CLog
//{
    //public:
        //static clog & Inst() { static clog inst;return inst; };
        //void log(conat char * format,...);
    //protected:
        //void log_impl(conat char * format,...);
//};

#ifndef __NO_PERF_LOG__
#define PERF_BEGIN() {struct timespec __perf_time_start_;clock_gettime(CLOCK_THREAD_CPU_TIME_ID,&__perf_time_start_);}
#define PERF_END(desc) {struct timespec __perf_time_end_;clock_gettime(CLOCK_REALTIME,&__perf_time_end_);\
    long nanosecs = (__perf_time_end_.tv_sec*1000000000 +__perf_time_end_.tv_nsec)-(__perf_time_start_.tv_sec*1000000000+__perf_time_start_.tv_nsec);\
fprintf(stderr,"%s time cost=>%lu\n",(desc),nanosecs);}

//#define LOG_DEBUG()

#else
#define PERF_BEGIN() do {} while(0)
#define PERF_END(desc) do {} while(0)
#endif

enum log_level_t { LL_DEBUG,LL_INFO,LL_WARN,LL_ERROR };

class CSimpleLog
{
    public:
        static CSimpleLog & Inst() { static CSimpleLog inst;return inst; };
        void enable(log_level_t);
        void log(log_level_t,const char * fn,unsigned int lineno,const char * format,...);
        int flush(bool bforce=false);
    protected:
        CSimpleLog();
        CSimpleLog(const CSimpleLog &);
        CSimpleLog & operator =(const CSimpleLog &);
        int check_flush();
        log_level_t log_level_;
        uint64_t last_flush_time_;
        uint64_t pending_count_;
        pthread_mutex_t mutex_;
};

inline CSimpleLog::CSimpleLog():log_level_(LL_DEBUG),last_flush_time_(0),pending_count_(0)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex_,&attr);
}

inline void CSimpleLog::enable(log_level_t level)
{
    log_level_ = level;
}
void log_init(const char* fileName);
void log_string(int ll, const char* fmt, ...);
std::string MakeString(const char* fmt, ...);
bool AppendString(std::string& buf, const char* fmt, ...);
#ifndef __NO_LOGGING__

void log_string(int ll, const char* fmt, ...);
void log_string2(bool main_log, const char* title, const char* fmt, ...);

#if 0
#define LOG_TRACE(...)  printf(__VA_ARGS__)
#define LOG_DEBUG(...)  printf(__VA_ARGS__)
#define LOG_INFO(...)  printf(__VA_ARGS__)
#define LOG_WARN(...)  printf(__VA_ARGS__)
#define LOG_ERROR(...)  printf(__VA_ARGS__)
#define LOG_MAIN(title, ...)  printf(__VA_ARGS__)
#else

#define LOG_DEBUG_SL(...)  CSimpleLog::Inst().log(LL_DEBUG,__FILE__,__LINE__,__VA_ARGS__)
#define LOG_INFO_SL(...)  CSimpleLog::Inst().log(LL_INFO,__FILE__,__LINE__,__VA_ARGS__)
#define LOG_WARN_SL(...)  CSimpleLog::Inst().log(LL_WARN,__FILE__,__LINE__,__VA_ARGS__)
#define LOG_ERROR_SL(...)  CSimpleLog::Inst().log(LL_ERROR,__FILE__,__LINE__,__VA_ARGS__)

#define LOG_TRACE(...)  log_string2(false, "TRACE", __VA_ARGS__)
#define LOG_DEBUG(...)  log_string2(false, "DEBUG", __VA_ARGS__)
#define LOG_INFO(...)  log_string2(false, "INFO", __VA_ARGS__)
#define LOG_WARN(...)  log_string2(false, "WARN", __VA_ARGS__)
#define LOG_ERROR(...)  log_string2(false, "ERROR", __VA_ARGS__)
#define LOG_MAIN(title, ...)  log_string2(true, title, __VA_ARGS__)
#endif

/*

*/
#else
#define LOG_DEBUG(...) do {} while(0)
#define LOG_INFO(...) do {} while(0)
#define LOG_WARN(...) do {} while(0)
#define LOG_ERROR(...) do {} while(0)
#endif

#endif

