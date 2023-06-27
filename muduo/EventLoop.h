#pragma once

#include <functional>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>

#include "noncopyable.h"
#include "Timestamp.h"
// #include "CurrentThread.h"

class Channel;
class Poller;

/*
    EventLoop    对应 Reactor
    epoll poller 对应 Demultiplex
*/

// 事件循环类 主要包含了两个大模块 Channel Poller(epoll的抽象)
class EventLoop : noncopyable
{
public:


private:

};