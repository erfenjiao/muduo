#ifndef MUDUO_NET_POLLER_H
#define MUDUO_NET_POLLER_H

/**
 * Poller class
 * 是 IO multiplexing 的封装，在 muudo 中是抽象基类，因为 muduo 支持 poll 和 epoll 两种IO多路复用机制
 * Poller 是 EventLoop 的间接成员，只供 own EventLoop 在 IO 线程调用
 * 
*/
#include <vector>
#include <map>

#include "../base/noncopyable.h"
#include "../base/TimeStamp.h"
#include "EventLoop.h"

// 自己前向声明了 struct pollfd，不妨碍我们定义 vector<struct pollfd> 成员
// struct pollfd;

namespace muduo
{
    namespace net
    {
        class Channel;


        /// @brief  
        /// Base class for IO Multiplexing
        class Poller : noncopyable {
            public:
            typedef std::vector<Channel*> ChannelList;

            Poller(EventLoop* loop);
            virtual ~Poller();

            // Polls the I/O events
            // Must be called in the loop thread.
            // Poller 的核心功能，调用 poll(2)获得当前活动的 IO 事件，然后填充调用方传入的 activeChannels，并返回 poll(2)return 的时刻
            virtual TimeStamp poll(int timeoutMs, ChannelList* activeChannels);

            /*
                Changes the interested I/O events.
                Must be called in the loop thread.
                Poller::updateChannel() 主要功能：负责维护和更新pollfds_数组
                添加新的Channel的复杂度是O(logN)
                更新已有的 Channel 的复杂度是 O(1)
            */
            virtual void updateChannel(Channel* channel) = 0;

            virtual void removeChannel(Channel* channel) = 0;

            void assertInLoopThread() {
                ownerLoop_->assertInLoopThread();
            }
            


            protected:
            void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

            typedef std::vector<struct pollfd> PollFdList;
            // 从 fd 到 Channel* 的映射
            typedef std::map<int, Channel*> ChannelMap;

            
            //Poller::poll() 不会在每次调用poll(2)之前临时构造pollfd数组，而是将他们缓存起来(pollfds_)
            // typedef std::vector<pollfd> muduo::net::Poller::PollFdList
            PollFdList pollfds_;
            ChannelMap channels_;

            private:
            EventLoop* ownerLoop_;
        };
    } // namespace net
    
} // namespace muduo


#endif