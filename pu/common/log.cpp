//#include "log.h"
//#include "time.h"
//#include <memory>
//#include <string>
//#include <string.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <unistd.h>
//#include <log4cplus/logger.h>
//#include <log4cplus/configurator.h>
//#include <log4cplus/consoleappender.h>
//#include <log4cplus/fileappender.h>
//#include <log4cplus/layout.h>
//#include <log4cplus/spi/filter.h>
//#include <log4cplus/helpers/property.h>
//#include <log4cplus/helpers/sleep.h>
//#include <log4cplus/loggingmacros.h>
//
//
//const char * log_level_names[]={"DEBUG","INFO","WARN","ERROR"};
//
//typedef uint64_t time_nanosec_t;
//inline time_nanosec_t get_nanosec()
//{
//    struct timespec time_point;
//    clock_gettime(CLOCK_REALTIME,&time_point);
//    return ((uint64_t)time_point.tv_sec)*1000000000 +time_point.tv_nsec;
//}
//
//
//void CSimpleLog::log(log_level_t level,const char * fn,unsigned int lineno,const char * format,...)
//{
//    if (level>=log_level_)
//    {
//        char log_content[4096];
//        va_list ap;
//        va_start(ap,format);
//        vsnprintf(log_content,sizeof(log_content),format,ap);
//        va_end(ap);
//
//	    //timespec tp;
//	    //clock_gettime(CLOCK_REALTIME,&tp);
//        //tm* lt = localtime(&tp.tv_sec);
//
//        pthread_mutex_lock(&mutex_);
//        fprintf(stdout,"%lu:%s[%s:%u]:%s",get_nanosec(),log_level_names[level],fn,lineno,log_content);
//        //fprintf(stdout, "%04d%02d%02d %02d:%02d:%02d.%03d %s",
//        //    lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
//        //    lt->tm_hour, lt->tm_min, lt->tm_sec,
//        //    (uint32_t)(tp.tv_nsec / 1000000),
//        //    log_content);
//
//        pending_count_++;
//        pthread_mutex_unlock(&mutex_);
//    }
//}
//
//int CSimpleLog::flush(bool bforce)
//{
//    //pthread_mutex_lock(&mutex_);
//    if (bforce || (pending_count_>0 && ((get_nanosec() - last_flush_time_)>10000000000)) || pending_count_>100)
//    {
//        fflush(stdout);
//        last_flush_time_ = get_nanosec();
//        pending_count_ = 0;
//        //pthread_mutex_unlock(&mutex_);
//        return 1;
//    }
//    //pthread_mutex_unlock(&mutex_);
//    return 0;
//}
//
//int SPrintf(char* pStr, size_t cStr, const char* fmt, va_list args) {
//	if (pStr == 0 || cStr == 0 || fmt == 0 || cStr > 40960)
//	{
//		return -2;
//	}
//
//	int len = vsnprintf(pStr, cStr, fmt, args);
//	if (len < 0) { // error
//		return -2;
//	}
//	else if (len >= (int)cStr) {
//		return -1;
//	}
//
//	// remove NULL char
//	while (len > 0 && pStr[len - 1] == '\0')
//		--len;
//
//	return len;
//}
//
//bool AppendString(std::string& buf, const char* fmt, ...)
//{
//	va_list args;
//
//	int base = (int)buf.size();
//	int ret = -1;
//
//	while (ret == -1)
//	{
//		try
//		{
//			buf.resize(buf.empty() ? 32 : buf.size() * 2);
//
//			va_start(args, fmt);
//			ret = SPrintf(&buf[base], buf.size() - base, fmt, args);
//			va_end(args);
//		}
//		catch (...)
//		{
//			ret = -2;
//		}
//	}
//
//	if (ret >= 0)
//	{
//		buf.resize(base + ret);
//		return true;
//	}
//
//	buf.resize(base);
//	return false;
//}
//
//std::string MakeString(const char* fmt, ...) {
//	va_list args;
//
//	std::string buf;
//	int ret = -1;
//
//	while (ret == -1)
//	{
//		try
//		{
//			buf.resize(buf.empty() ? 32 : buf.size() * 2);
//
//			va_start(args, fmt);
//			ret = SPrintf(&buf[0], buf.size(), fmt, args);
//			va_end(args);
//		}
//		catch (...)
//		{
//			ret = -2;
//		}
//	}
//
//	if (ret >= 0)
//	{
//		buf.resize(ret);
//	}
//	else
//	{
//		buf.clear();
//	}
//
//	return buf;
//}
//const char* GetLogLevelString(int ll) {
//    switch (ll) {
//    case 0: return "TRACE";
//    case 10000: return "DEBUG";
//    case 20000: return "INFO";
//    case 30000: return "WARN";
//    case 40000: return "ERROR";
//    default: break;
//    }
//    return "UNKNOWN";
//}
//void log_string2(bool main_log, const char* title, const char* fmt, ...) {
//	va_list args;
//
//    char timstr[128];
//    /*
//    timespec tp;
//	clock_gettime(CLOCK_REALTIME,&tp);
//    tm tmp;
//    tm* lt = localtime_r(&tp.tv_sec, &tmp);
//    sprintf(timstr, "%04d-%02d-%02d %02d:%02d:%02d.%03d: ",
//        lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
//            lt->tm_hour, lt->tm_min, lt->tm_sec,
//            (uint32_t)(tp.tv_nsec / 1000000));
//    */
//    sprintf(timstr, "%s:system_time=>%lu,", title, get_nanosec());
//
//
//    std::string buf(timstr);
//
//	int base = (int)buf.size();
//	int ret = -1;
//
//	while (ret == -1) {
//		try {
//			buf.resize(buf.empty() ? 32 : buf.size() * 2);
//			va_start(args, fmt);
//			ret = SPrintf(&buf[base], buf.size() - base, fmt, args);
//			va_end(args);
//		}
//		catch (...) {
//			ret = -2;
//		}
//	}
//
//	if (ret >= 0) {
//		buf.resize(base + ret);
//
//	}
//    else {
//        buf.assign(fmt);
//    }
//
//    log4cplus::Logger log = log4cplus::Logger::getRoot();
//    if (main_log) {
//        log.forcedLog((log4cplus::LogLevel)20000, buf, "", 0);
//    }
//    else {
//        log.forcedLog((log4cplus::LogLevel)10000, buf, "", 0);
//    }
//}
//void log_string(int ll, const char* fmt, ...) {
//	va_list args;
//
//    //char timstr[128];
//    /*
//    timespec tp;
//	clock_gettime(CLOCK_REALTIME,&tp);
//    tm tmp;
//    tm* lt = localtime_r(&tp.tv_sec, &tmp);
//    sprintf(timstr, "%04d-%02d-%02d %02d:%02d:%02d.%03d: ",
//        lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
//            lt->tm_hour, lt->tm_min, lt->tm_sec,
//            (uint32_t)(tp.tv_nsec / 1000000));
//    */
//    //sprintf(timstr, "%s:%lu:", GetLogLevelString(ll), get_nanosec());
//
//
//    std::string buf;//(timstr);
//
//	int base = (int)buf.size();
//	int ret = -1;
//
//	while (ret == -1) {
//		try {
//			buf.resize(buf.empty() ? 32 : buf.size() * 2);
//			va_start(args, fmt);
//			ret = SPrintf(&buf[base], buf.size() - base, fmt, args);
//			va_end(args);
//		}
//		catch (...) {
//			ret = -2;
//		}
//	}
//
//	if (ret >= 0) {
//		buf.resize(base + ret);
//
//	}
//    else {
//        buf.assign(fmt);
//    }
//
//    log4cplus::Logger log = log4cplus::Logger::getRoot();
//    log.forcedLog((log4cplus::LogLevel)ll, buf, "", 0);
//}
//
//void log_init(const char* fileName) {
//
//	char logFilePath[512];
//	memset(logFilePath, 0, sizeof(logFilePath));
//    getcwd(logFilePath, sizeof(logFilePath) - 1);
//
//    strcat(logFilePath, "/");
//    strcat(logFilePath, fileName);
//    mkdir(logFilePath, 0775);
//
//    strcat(logFilePath, "/logs/");
//    mkdir(logFilePath, 0775);
//
//    time_t now = time(0);
//    tm* lt = localtime(&now);
//
//    char logFileName[512];
//    sprintf(logFileName, "%s%s_%04d%02d%02d_%02d%02d%02d.log",
//            logFilePath, fileName,
//            lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
//            lt->tm_hour, lt->tm_min, lt->tm_sec);
//
//    char logDebugFileName[512];
//    sprintf(logDebugFileName, "%s%s_%04d%02d%02d_%02d%02d%02d_debug.log",
//            logFilePath, fileName,
//            lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
//            lt->tm_hour, lt->tm_min, lt->tm_sec);
//
//
//    //std::string logFormat = "%p %m";
//    std::string logFormat = "%m";
//
//	log4cplus::Logger logger = log4cplus::Logger::getRoot();
//	logger.setLogLevel(log4cplus::ALL_LOG_LEVEL);
//	logger.removeAllAppenders();
//
//	log4cplus::SharedAppenderPtr append;
//	log4cplus::helpers::Properties prop;
//	log4cplus::spi::FilterPtr filter;
//	log4cplus::spi::FilterPtr denyAllFilter(new log4cplus::spi::DenyAllFilter());
//
//    std::auto_ptr<log4cplus::Layout> layout(new log4cplus::PatternLayout(logFormat));
//    prop.setProperty("LogLevelMin", "TRACE");
//    prop.setProperty("AcceptOnMatch", "true");
//    filter = new log4cplus::spi::LogLevelRangeFilter(prop);
//    //filter->appendFilter(denyAllFilter);
//    append = new log4cplus::ConsoleAppender();
//    append->setName(log4cplus::tstring("ConsoleAppender"));
//    append->setFilter(filter);
//    append->setLayout(layout);
//    logger.addAppender(append);
//
//    int LogRollingFileMaxSize = 10 * 1024 * 1024;
//    int LogRollingFileMaxBackupIndex = 5;
//
//	layout.reset(new log4cplus::PatternLayout(logFormat));
//	prop.setProperty("LogLevelMin", "INFO");
//	prop.setProperty("LogLevelMax", "FATAL");
//	prop.setProperty("AcceptOnMatch", "true");
//	filter = new log4cplus::spi::LogLevelRangeFilter(prop);
//	//filter->appendFilter(denyAllFilter);
//	append = new log4cplus::RollingFileAppender(logFileName, LogRollingFileMaxSize, LogRollingFileMaxBackupIndex);
//	append->setName(log4cplus::tstring("RollingFileAppender"));
//	append->setLayout(layout);
//	append->setFilter(filter);
//	logger.addAppender(append);
//
//// ALL TRACE DEBUG INFO WARN ERROR FATAL OFF
//
//	layout.reset(new log4cplus::PatternLayout(logFormat));
//	prop.setProperty("LogLevelMin", "TRACE");
//	prop.setProperty("LogLevelMax", "DEBUG");
//	prop.setProperty("AcceptOnMatch", "true");
//	filter = new log4cplus::spi::LogLevelRangeFilter(prop);
//	//filter->appendFilter(denyAllFilter);
//	append = new log4cplus::RollingFileAppender(logDebugFileName, LogRollingFileMaxSize, LogRollingFileMaxBackupIndex);
//	append->setName(log4cplus::tstring("RollingFileDebugAppender"));
//	append->setLayout(layout);
//	append->setFilter(filter);
//	logger.addAppender(append);
//
//
//}