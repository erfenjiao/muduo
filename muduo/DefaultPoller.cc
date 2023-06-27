#include <stdlib.h>

#include "Poller.h"
#include "EPollPoller.h"

Poller *Poller::newDefaultPoller(EventLoop *loop)
{
    // getenv 环境变量
    if (::getenv("MUDUO_USE_POLL"))
    {
        return nullptr; // 生成poll的实例
    }
    else
    {
        return new EPollPoller(loop); // 生成epoll的实例
    }
}