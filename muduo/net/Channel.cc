
#include <iostream>
#include <sstream>
#include <poll.h>

#include "../base/noncopyable.h"
#include "../base/Logging.h"

// #include "muduo/net/Channel.h"
// #include "muduo/net/EventLoop.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Poller.h"


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
    // 调用 Poller::updateChannel() 由于Channel没有包含EventLoop.h，因此必须定义在Channel.cc 中
    // 是 EventLoop.h 中的
    loop_->updateChannel(this);
}

// poller.h 中 fillActiveChannels() 遍历pollfds_,找出有活动事件的fd，把它对应的Channel填入activeChannels。
// 当前活动事件 revents 会保存在Channel中，供 Channel::handleEvent() 使用
// 注意：不能一边遍历 pollfds_ ， 一边调用 Channel::handleEvent()。
void Channel::handleEvent() {
    LOG_TRACE << "Channel::handleEvent():\n" ;
    
    if(revent_ & POLLNVAL) {
        LOG_WARN << "Channel::handle_event() POLLNVAL";
    }

    if(revent_ & (POLLERR | POLLNVAL)) {
        if(errorCallback_) errorCallback_();
    }
    // if(revent_ &  (POLLIN | POLLPRI | POLLRDHUP)) {
    //     if(readCallback_) readCallback_(receiveTime);
    // }
    if(revent_ &  POLLOUT) {
        if(writeCallback_) writeCallback_();
    }
}
