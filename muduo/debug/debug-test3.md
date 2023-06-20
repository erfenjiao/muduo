```
(gdb) run
Starting program: /home/erfenjiao/project/muduo/muduo/build/bin/test3 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x0000555555560559 in muduo::TimeStamp::now () at /usr/include/string.h:268
268       return __builtin_strrchr (__s, __c);
```

查看调用栈
```
(gdb) backtrace
#0  0x0000555555560559 in muduo::TimeStamp::now () at /usr/include/string.h:268
#1  0x000055555555dbca in muduo::Logger::Impl::Impl (this=0x7fffff7ff740, level=muduo::Logger::INFO, savedErrno=0, file=..., line=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:87
#2  0x000055555555df43 in muduo::Logger::Logger (this=this@entry=0x7fffff7ff740, file=..., line=line@entry=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:147
#3  0x000055555556055e in muduo::TimeStamp::now () at /usr/include/string.h:268
#4  0x000055555555dbca in muduo::Logger::Impl::Impl (this=0x7fffff8007a0, level=muduo::Logger::INFO, savedErrno=0, file=..., line=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:87
#5  0x000055555555df43 in muduo::Logger::Logger (this=this@entry=0x7fffff8007a0, file=..., line=line@entry=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:147
#6  0x000055555556055e in muduo::TimeStamp::now () at /usr/include/string.h:268
#7  0x000055555555dbca in muduo::Logger::Impl::Impl (this=0x7fffff801800, level=muduo::Logger::INFO, savedErrno=0, file=..., line=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:87
#8  0x000055555555df43 in muduo::Logger::Logger (this=this@entry=0x7fffff801800, file=..., line=line@entry=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:147
#9  0x000055555556055e in muduo::TimeStamp::now () at /usr/include/string.h:268
#10 0x000055555555dbca in muduo::Logger::Impl::Impl (this=0x7fffff802860, level=muduo::Logger::INFO, savedErrno=0, file=..., line=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:87
#11 0x000055555555df43 in muduo::Logger::Logger (this=this@entry=0x7fffff802860, file=..., line=line@entry=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:147
#12 0x000055555556055e in muduo::TimeStamp::now () at /usr/include/string.h:268
#13 0x000055555555dbca in muduo::Logger::Impl::Impl (this=0x7fffff8038c0, level=muduo::Logger::INFO, savedErrno=0, file=..., line=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:87
#14 0x000055555555df43 in muduo::Logger::Logger (this=this@entry=0x7fffff8038c0, file=..., line=line@entry=88) at /home/erfenjiao/project/muduo/muduo/base/Logging.cc:147
```
可能是日志使用问题？修改如下：
```
//LOG_INFO << "now" ;
std::cout << "now()" << std::endl;
```

```
(gdb) run
Program received signal SIGSEGV, Segmentation fault.
0x000055555555d4d3 in muduo::net::EventLoop::updateChannel (this=0x7fffffffc490, channel=0x7fffffffc4f0) at /home/erfenjiao/project/muduo/muduo/net/EventLoop.cc:130
130         poller_->updateChannel(channel);

(gdb) backtrace
#0  0x000055555555d4d3 in muduo::net::EventLoop::updateChannel (this=0x7fffffffc490, channel=0x7fffffffc4f0) at /home/erfenjiao/project/muduo/muduo/net/EventLoop.cc:130
#1  0x000055555555cb9f in muduo::net::Channel::update (this=<optimized out>) at /home/erfenjiao/project/muduo/muduo/net/Channel.cc:39
#2  0x000055555555c533 in muduo::net::Channel::enableReading (this=0x7fffffffc4f0) at /home/erfenjiao/project/muduo/muduo/net/tests/../Channel.h:61
#3  main () at /home/erfenjiao/project/muduo/muduo/net/tests/test3.cc:38
```

看一下updateChannel函数
```
void EventLoop::updateChannel(Channel* channel) {
    LOG_INFO << "EventLoop::updateChannel - channel:" << channel;
    assert(channel->ownerLoop() == this);
    assertInLoopThread();

    //poller_->updateChannel(channel);
    if (poller_) {
        poller_->updateChannel(channel);
    }else {
        LOG_INFO << "poller_ 是空指针";
    }
}
```
检查一下poller_是否为空指针，输出结果：是的。然后去看了构造函数，没有初始化
输出结果：
```
20230617 14:02:26.974839Z  9633 INFO  poller_ 是空指针 - EventLoop.cc:134
```

一个小错误：之前函数未等于0
```
virtual TimeStamp poll(int timeoutMs, ChannelList* activeChannels) = 0;
```
解释
```
这是一个纯虚函数，其末尾加上= 0是为了将该函数声明为抽象函数。在C++中，当一个类包含至少一个纯虚函数时，它就成为了抽象基类（Abstract Base Class），不能被实例化。派生类必须实现所有的纯虚函数才能被实例化。

因此，在定义一个纯虚函数时，我们需要在函数声明后面加上= 0来告诉编译器这个函数是一个纯虚函数，是不能被实现的。这样做可以确保这个类只能被用作其他类的基类，而不能被直接实例化。

至于virtual TimeStamp poll(int timeoutMs, ChannelList* activeChannels)和virtual TimeStamp poll(int timeoutMs, ChannelList* activeChannels) = 0之间的区别，则在前者中有一个默认实现，允许派生类继承该函数并使用默认实现。而后者是纯虚函数，要求派生类必须实现该函数。如果派生类不实现该函数，则会被编译器视为抽象类，无法被实例化。
```

最后一处错误：
```
::timer_settime(reinterpret_cast<timer_t>(timerfd), 0, &howlong, NULL);
// 错误的：
//::timer_settime(*reinterpret_cast<timer_t*>(timerfd), 0, &howlong, NULL);
```
因为书上的报错，只能使用报错提示的类型转换，成功了。