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

    // 设置回调函数对象 
    void setReadCallback(ReadEventCallback cb) { readCallback_  = cb; }
    void setWriteCallback(EventCallback cb)    { writeCallback_ = cb; }
    void setCloseCallback(EventCallback cb)    { closeCallback_ = cb; }
    void setErrorCallback(EventCallback cb)    { errorCallback_ = cb; }

    // 防止手动 remove Channel 后仍在执行回调操作。
    // std::weak_ptr<void> tie_;        // 防止手动 remove Channel后仍在执行回调操作。
    // bool tied_;
    void tie(const std::shared_ptr<void>&);

    int fd()            const  { return fd_;}
    int events()         const {return events_;}
    // 为什么要设置这样一个方法？
    // channel 不能监听自己发生了什么事件，poller在监听
    int set_revents(int revt)  {revents_ = revt;}

    // 设置fd相应的事件状态 相当于 epoll_ctl add delete
    /*
        const int Channel::kNoneEvent = 0;
        const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
        const int Channel::kWriteEvent = EPOLLOUT;
    */
    void enableReading()  { events_ |= kReadEvent;   update(); }     // 让 fd 对读事件感兴趣
    void disableReading() { events_ &= ~kReadEvent;  update(); }     // ～：使得read的那一位是0,，再&=上其他位，把相应的位置成0,去掉，
    void enableWriting()  { events_ |= kWriteEvent;  update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll()     { events_  = kNoneEvent;   update(); }

    // 返回fd当前的事件状态
    bool isNoneEvent() const { return events_ == kNoneEvent; }
    bool isWriting()   const { return events_ & kWriteEvent; }
    bool isReading()   const { return events_ & kReadEvent;  }

    // 与业务相关，表示 channel 在 poll 中的状态
    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    // one loop per thread
    EventLoop *ownerLoop() { return loop_; }
    void remove();   // 删除 channel

private:
    void update(); 
    // WithGuard 受保护的
    void handleEventWithGuard(Timestamp receiveTime);

    static const int kNoneEvent;      // 对任何事件都不感兴趣
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;                 // 事件循环

    const int fd_;                   // fd，Poller监听的对象
    int events_;                     // 注册fd感兴趣的事件
    int revents_;                    // Poller 返回的具体发生的事件,channel
    int index_;

    std::weak_ptr<void> tie_;        // 防止手动 remove Channel后仍在执行回调操作。
    bool tied_;

    // 因为channel通道里可获知fd最终发生的具体的事件events，所以它负责调用具体事件的回调操作
    ReadEventCallback readCallback_;
    EventCallback     writeCallback_;
    EventCallback     closeCallback_;
    EventCallback     errorCallback_;

};
