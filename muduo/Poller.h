#pragma once

#include <vector>
#include <unordered_map>

#include "noncopyable.h"
#include "Timestamp.h"

class Channel;
class EventLoop;

// muduo库中多路事件分发器的核心IO复用模块
class Poller
{
public:
    // 所有的 channel 都在在里面管理，注册的，未注册的都有，最后注册过的也会写进 ChannelMap 中
    using ChannelList = std::vector<Channel *>;

    Poller(EventLoop *loop);
    virtual ~Poller() = default;

    // 给所有IO复用保留统一的接口
    virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;
    virtual void updateChannel(Channel* channel) = 0;
    virtual void removeChannel(Channel* channel) = 0;

    // 判断参数channel是否在当前的Poller当中
    bool hasChannel(Channel *channel) const;

    // EventLoop可以通过该接口获取默认的IO复用的具体实现
    // 不写在 poller.cc 中,因为需要具体实现的对象
    static Poller *newDefaultPoller(EventLoop *loop);

protected:
    // map 的 key:sockfd value:sockfd 所属的 channel 通道类型
    using ChannelMap = std::unordered_map<int, Channel *>;
    ChannelMap channels_;
     
private:
    EventLoop *ownerLoop_; // 定义Poller所属的事件循环EventLoop
};