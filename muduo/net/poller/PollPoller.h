
#ifndef MUDUO_NET_POLLPOLLER_H
#define MUDUO_NET_POLLPOLLER_H

#include "../Poller.h"

#include <vector>

// 自己前向声明了 struct pollfd，不妨碍我们定义 vector<struct pollfd> 成员
struct pollfd;

namespace muduo{
    namespace net
    {
        // a PollPoller class which is derived from the Poller base class.
        class PollPoller : public Poller {
            public:
                PollPoller(EventLoop* loop);
                ~PollPoller() override;

                TimeStamp poll(int timeoutMs, ChannelList* activeChannels) override;

                void updateChannel(Channel* channel) override;

                void removeChannel(Channel* Channel) override;

            private:
                void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

                typedef std::vector<struct pollfd> PollFdList;
                
                PollFdList pollfds_;


            /**Poller.h:
             * private:
                void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

                typedef std::vector<struct pollfd> PollFdList;
                // 从 fd 到 Channel* 的映射
                typedef std::map<int, Channel*> ChannelMap;

                EventLoop* ownerLoop_;
                //Poller::poll() 不会在每次调用poll(2)之前临时构造pollfd数组，而是将他们缓存起来(pollfds_)
                // typedef std::vector<pollfd> muduo::net::Poller::PollFdList
                PollFdList pollfds_;
                ChannelMap channels_;
            */
        };
        
    } // namespace net
    
} // namespace muduo


#endif  // #define MUDUO_NET_POLLPOLLER_H