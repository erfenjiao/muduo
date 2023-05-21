
#include "muduo/base/Thread.h"
#include "muduo/base/CurrentThread.h"

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>


namespace muduo
{
    namespace detail
    {
        pid_t getpid(){
            return static_cast<pid_t>(::syscall(SYS_getpid));
        }


        
    } // namespace detail



    void CurrentThread::cacheTid() {
            if(t_cachedTid == 0) {
                t_cachedTid = detail::getpid();
                t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, " %5d", t_cachedTid);
            }
    }

    bool CurrentThread::isMainThread() {
        return tid() == ::getpid();
    }
    
} // namespace muduo
