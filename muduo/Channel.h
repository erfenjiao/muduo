// 通道
/*
    EventLoop 事件循环
    两个重要的组件 ： epoll Channel
*/
#pragma once

#include <functional>
#include <memory>

#include "noncopyable.h"
#include "Timestamp.h"

class EventLoop;

/**
 * 理清楚 EventLoop、Channel、Poller之间的关系  Reactor模型上对应多路事件分发器
 * Channel理解为通道 封装了sockfd和其感兴趣的event 如EPOLLIN、EPOLLOUT事件 还绑定了poller返回的具体事件
 **/
class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>; // muduo仍使用typedef
    // 只读事件的回调
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    // fd得到Poller通知以后 处理事件 handleEvent ,在 EventLoop::loop()中调用
    void handleEvent(Timestamp receiveTime);
private:

    static const int kNoneEvent;      // 对任何事件都不感兴趣
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;                 // 事件循环

    const int fd_;                   // fd，Poller监听的对象
    int events_;                     // 注册fd感兴趣的事件
    int revents_;                    // Poller返回的具体发生的事件
    int index_;

    std::weak_ptr<void> tie_;        // 防止手动 remove Channel后仍在空转。
    bool tied_;

    // 因为channel通道里可获知fd最终发生的具体的事件events，所以它负责调用具体事件的回调操作
    ReadEventCallback readCallback_;
    EventCallback     writeCallback_;
    EventCallback     closeCallback_;
    EventCallback     errorCallback_;

};
