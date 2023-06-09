

// virtual TimeStamp poll(int timeoutMs, ChannelList* activeChannels) = 0;
// Poller 的核心功能，调用 poll(2)获得当前活动的 IO 事件，然后填充调用方传入的 activeChannels，并返回 poll(2)return 的时刻
TimeStamp Poller::poll(int timeoutMs, ChannelList* activeChannels) {  
      int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);

      TimeStamp now(TimeStamp::now());

      if( numEvents > 0) {
          LOG_TRACE << numEvents << " events happened";
          fillActiveChannels(numEvents, activeChannels);
      } else if( numEvents == 0) {
          LOG_TRACE << "nothing happended";
      } else {
        LOG_SYSERR << "Poller::poll()";
      }
      return now;
}
