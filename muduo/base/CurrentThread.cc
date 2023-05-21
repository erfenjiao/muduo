
#include "CurrentThread.h"


namespace muduo
{
    namespace CurrentThread
    {
        __thread int t_cachedTid = 0;
        __thread char t_tidString[32];
        __thread int t_tidStringLength = 0;
        __thread const char* t_threadName = "unknown";

    } // namespace CurrentThread
} // namespace muduo
