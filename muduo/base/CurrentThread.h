#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

namespace muduo {
    namespace CurrentThread {
        extern __thread int t_cachedTid;

        void cacheTid();

        inline int tid() {
            if(__builtin_except(t_cachedTid == 0, 0)) {
                cacheTid();
            }
            return t_cachedTid;
        }

        bool isMainThread();

        void sleepUsec(bool demangle);
    }
}

#endif
