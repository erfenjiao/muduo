
#include <iostream>
#include <sstream>
#include <poll.h>

#include "../base/noncopyable.h"
#include "../base/Logging.h"

// #include "muduo/net/Channel.h"
// #include "muduo/net/EventLoop.h"
#include "Channel.h"
#include "EventLoop.h"


using namespace muduo;
using namespace muduo::net;


Channel::Channel(EventLoop* loop, int fd__)
: loop_(loop),
  fd_(fd__),
  events_(0),
  revent_(0),
  index_(-1)
{}

Channel::~Channel() {

}

void Channel::update() {

}

void Channel::handleEvent() {
    LOG_TRACE << "Channel::handleEvent():\n" ;

}
