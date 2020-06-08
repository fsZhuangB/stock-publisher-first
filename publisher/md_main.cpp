#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <execinfo.h>
#include "md_publisher.h"
#include "utility.h"

static void print_stack()
{
    int i;
    void *buffer[1024];
    int n = backtrace(buffer, 1024);
    fprintf(stdout, "backtrace() returned %d addresses\n", n);
    char **symbols = backtrace_symbols(buffer, n);
    if (symbols == nullptr)
    {
        return;
    }
    for (i = 0; i < n; i++) {
        fprintf(stdout, "[%02d] %s\n", i, symbols[i]);
    }
    free(symbols);
}

static void sig_handler(int signum)
{
    fprintf(stdout, "Got a signal, signum=>%d\n",signum);
    print_stack();
    if (SIGINT!=signum && SIGQUIT!=signum && SIGTERM!=signum)
    {
        fprintf(stdout, "crash signal triggered\n");
        signal(signum,SIG_DFL);
        kill(getpid(),signum);
    }
}

int main(int argc, char** argv) {

    signal(SIGINT,sig_handler);
    signal(SIGQUIT,sig_handler);
    signal(SIGTERM,sig_handler);
    signal(SIGSEGV,sig_handler);
    signal(SIGABRT,sig_handler);
    signal(SIGPIPE,sig_handler);

    int md_core_id = 2;
    char c;
    while (-1 != (c = getopt(argc, argv, "c:"))) {
        switch (c) {
            case 'c':
                md_core_id = atoi(optarg);
                break;
        }
    }
    
    int ret = bind_core(md_core_id);
    if (0!=ret)
        fprintf(stdout, "bind md spi thread(%d) core:%d fail\n", get_self_tid(), md_core_id);
    else
        fprintf(stdout, "bind md spi thread(%d) on core:%d\n",get_self_tid(),md_core_id);
    
    fprintf(stdout, "begin to read the config file!");
    
    Config& config = Config::getInstance("config.cfg");
    start_md(config);
    fprintf(stderr,"md_main :thread(%d)\n",get_self_tid());
    sleep(UINT_MAX);
    return 0;
}