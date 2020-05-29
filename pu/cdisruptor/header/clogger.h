#ifndef _CLOGGER_H
#define _CLOGGER_H
#include <stdarg.h>  
#include <stdio.h>
#include <time.h>
#define _NO_LOGGING
/*
enum log_level {
    LEVEL_DEBUG = 0,
    LEVEL_INFO,
    LEVEL_ERROR
};

#define CLOG_TMP_SIZE 200
char *log_level_str[]={"debug","info","error"};
void _log(enum log_level level,const char * file,const char * func, int line_num,const char *format, ...){
    char str_tmp[CLOG_TMP_SIZE];
    va_list vArgList;
    va_start (vArgList, format); 
    vsnprintf(str_tmp, CLOG_TMP_SIZE, format, vArgList);
    va_end(vArgList);
    time_t t = time(0); 
    char tmp[64]; 
    strftime( tmp, sizeof(tmp), "%F %T",localtime(&t) );
    fprintf(stderr,"%s %s:%s[%s %d]  %s\n",tmp,log_level_str[level],file,func,line_num,str_tmp);
}
*/

#ifdef _NO_LOGGING 
#define clog_debug(format, ...) do {} while(0)
#define clog_trace(format, ...) do {} while(0)
#define clog_error(format, ...) do {} while(0)
#else
#define clog_debug(format, ...) _log(LEVEL_DEBUG,__FILE__,__FUNCTION__,__LINE__,format, __VA_ARGS__)
#define clog_trace(format, ...) _log(LEVEL_INFO,__FILE__,__FUNCTION__,__LINE__,format,__VA_ARGS__)
#define clog_error(format, ...) _log(LEVEL_ERROR,__FILE__,__FUNCTION__,__LINE__,format,__VA_ARGS__)
#endif













#endif