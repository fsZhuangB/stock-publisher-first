#ifndef __ADAPTER_UTILITY_H__
#define __ADAPTER_UTILITY_H__
#include <sys/time.h>
#include <time.h>
#include <inttypes.h>
#include <string>
#include <algorithm>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "log.h"
using std::transform;


class function_log {
public:
    function_log(const char* fn) : m_functionName(fn) {
        LOG_DEBUG("%s enter\n", m_functionName);
    }
    ~function_log() {
        LOG_DEBUG("%s leave\n", m_functionName);
    }
    const char* m_functionName;
};

typedef uint64_t time_nanosec_t;

inline int get_time() {
    struct timespec cur_time;
    clock_gettime(CLOCK_REALTIME_COARSE,&cur_time);
    return cur_time.tv_sec;
}
  
 
inline time_nanosec_t get_nanosec()
{
    struct timespec time_point;
    clock_gettime(CLOCK_REALTIME,&time_point);
    return ((uint64_t)time_point.tv_sec)*1000000000 +time_point.tv_nsec;
}
inline int get_date_YYYYMMDD()
{
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    return (now->tm_year + 1900)* 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
}

inline uint64_t rdtscl()
{
    uint32_t lo,hi;
    __asm__ __volatile__("rdtsc":"=a"(lo),"=d"(hi));
    return ((uint64_t)lo|(((uint64_t)hi)<<32));
}

inline int get_cur_msec(uint64_t day_begin_msec) {
    struct timespec time_point;
    clock_gettime(CLOCK_REALTIME,&time_point);
    return ((uint64_t)time_point.tv_sec) * 1000 + time_point.tv_nsec / 1000000 - day_begin_msec;

}
inline int get_time_msec(int time) {
    return  time / 10000000 * 3600000 + (time % 10000000)/100000 * 60000 + (time % 100000)/1000 * 1000 + (time % 1000);
}


inline int get_time_msec() {
    struct timeval tv;
    struct tm *tm;
    gettimeofday(&tv, NULL);
    struct tm ret;
    tm = localtime_r(&tv.tv_sec, &ret);
    int cur_time  = tm->tm_hour * 10000000;
    cur_time += tm->tm_min * 100000;
    cur_time += tm->tm_sec * 1000;
    cur_time += (int) (tv.tv_usec / 1000);
    return cur_time;
}

const unsigned int PAGE_SIZE = 4096;
const uint64_t PAGE_MASK = 0xfff;

inline int vm_preload(void * pdata,size_t len)
{
    //LOG_DEBUG("vm_preload:pdata=>%x,len=>%d\n",reinterpret_cast<uint64_t>(pdata),len);
    int accumulate=0;
    uint64_t start_addr = reinterpret_cast<uint64_t>(reinterpret_cast<unsigned char*>(pdata));
    uint64_t end_addr = reinterpret_cast<uint64_t>(reinterpret_cast<unsigned char*>(pdata)+len);
    start_addr &= ~PAGE_MASK;
    end_addr &= ~PAGE_MASK;

    for (unsigned char * ppage=reinterpret_cast<unsigned char *>(start_addr);ppage<=reinterpret_cast<unsigned char *>(end_addr);ppage+=PAGE_SIZE)
    {
        //LOG_DEBUG("vm_preload:preloaded page addr:%x\n",reinterpret_cast<uint64_t>(ppage));
        accumulate += *ppage;
    }
    return accumulate;
}

inline std::vector<std::string> split(const std::string text,const char * psep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find_first_of(psep, start)) != std::string::npos) {
        if (end-start>0)
            tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    if(0 != text.length()) {
        tokens.push_back(text.substr(start));
    }
    return tokens;
}

inline void strlower(std::string & str)
{
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
}

inline int bind_core(unsigned int core_id)
{
    pthread_t self;
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(core_id,&cpu_set);
    self = pthread_self();
    return pthread_setaffinity_np(self,sizeof(cpu_set_t),&cpu_set);
}

inline pid_t get_self_tid()
{
    return syscall(__NR_gettid);
}

#endif

