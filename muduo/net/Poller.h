#ifndef MUDUO_NET_POLLER_H
#define MUDUO_NET_POLLER_H

/**
 * 
*/
#include <vector>
#include <map>

#include "../base/noncopyable.h"
#include "../base/TimeStamp.h"
#include "EventLoop.h"

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

            virtual TimeStamp poll(int timeoutMs, ChannelList* activeChannels) = 0;

            virtual void updateChannel(Channel* channel) = 0;
            


            private:
            EventLoop* ownerLoop_;
        };
    } // namespace net
    
} // namespace muduo


#endif