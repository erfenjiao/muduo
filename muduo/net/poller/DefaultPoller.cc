#include "../Poller.h"
#include "../poller/PollPoller.h"
// #include "../poller/EPollPoller.h"

#include <stdlib.h>
#include <iostream>

using namespace muduo::net;

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
//   if (::getenv("MUDUO_USE_POLL"))
//   {
    return new PollPoller(loop);

//   else
//   {
//     //return new EPollPoller(loop);
//   }
}