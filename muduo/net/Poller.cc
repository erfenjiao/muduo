#include "Poller.h"
#include "Channel.h"

#include "../base/Logging.h"

using namespace muduo;
using namespace muduo::net;

Poller::Poller(EventLoop* loop)
     : ownerLoop_(loop)
{
}

Poller::~Poller() = default;


// void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
// 
// void Poller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const {
    
//     for(PollFdList::const_iterator pfd = pollfds_.begin(); 
//         pfd != pollfds_.end() && numEvents >0 ; ++pfd) {
//           if(pfd->revents > 0) {
//             --numEvents;

//             ChannelMap::const_iterator ch = channels_.find(pfd->fd);
//           }
//         }  

// }
//epoll4

bool Poller::hasChannel(Channel* channel) const
{
  assertInLoopThread();
  ChannelMap::const_iterator it = channels_.find(channel->fd());
  return it != channels_.end() && it->second == channel;
}