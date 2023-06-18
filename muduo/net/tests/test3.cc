#include <sys/timerfd.h>

#include "../EventLoop.h"
#include "../Channel.h"
#include "../../base/Logging.h"

muduo::net::EventLoop* g_loop;

// void timeout() {
//     printf("Timeout!\n");
//     g_loop->quit();
// }

void timeout(muduo::TimeStamp timestamp) {
    printf("Timeout at %s\n", timestamp.toFormattedString().c_str());
    g_loop->quit();
}

int main() {
    LOG_INFO << "muduo::net::EventLoop loop";
    muduo::net::EventLoop loop;
    // 将其地址存储在指针变量g_loop中
    g_loop = &loop;

    /*
        使用Linux系统调用timerfd_create创建了一个计时器文件描述符，并将其赋值给整型变量time_fd
        timerfd_create是一个Linux系统调用，它可以创建一个计时器文件描述符，并返回该文件描述符的整数值。
        它的第一个参数指定了计时器的类型，CLOCK_MONOTONIC表示使用单调时钟来计算时间；
        第二个参数是一个标志位，其中TFD_NONBLOCK表示将文件描述符设置为非阻塞模式，TFD_CLOEXEC表示在执行execve时关闭文件描述符。

        Return file descriptor for new interval timer source. 
        extern int timerfd_create (__clockid_t __clock_id, int __flags) __THROW;
    */
    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

    muduo::net::Channel channel(&loop, timerfd);
    channel.setReadCallback(timeout);
    channel.enableReading();

    struct itimerspec howlong;
    bzero(&howlong, sizeof howlong);
    howlong.it_value.tv_sec = 5;
    ::timer_settime(reinterpret_cast<timer_t>(timerfd), 0, &howlong, NULL);
    // 错误的：
    //::timer_settime(*reinterpret_cast<timer_t*>(timerfd), 0, &howlong, NULL);

    char buf[1024];
    ssize_t n = ::read(timerfd, buf, sizeof(buf));
    if(n < 0) {
        LOG_INFO << "test3:line47 n < 0";
    }

    loop.loop();

    ::close(timerfd);
}

/*
    poll(2) 是 level trigger,在timeout中应该read() timefd，否则下回会立刻触发

    在使用 `poll()` 函数等待事件的过程中，如果设置了超时时间，那么当超时时间到达时，`poll()` 函数会返回一个特殊的值，用于表示超时事件已经发生。

    这个特殊的返回值是指 `poll()` 函数返回值为 0。因此，在处理超时事件时，我们需要检查 `poll()` 函数的返回值是否为 0，以判断是否发生了超时事件。

    在处理超时事件时，通常需要从定时器文件描述符（例如，通过 `timerfd_create()` 函数创建）中读取数据，以清除定时器并使其不再触发下一个超时事件。
    如果不进行读取操作，定时器将保持激活状态，并且下一次调用 `poll()` 函数时将立即返回，并报告可读事件，这可能会导致意外的行为和性能问题。

    根据 `timerfd_settime()` 函数的文档，该函数支持基于绝对时间或相对时间的定时器。如果使用的是相对时间定时器，则可以将定时器的超时时间设置为 0，
    以便在下一次读取操作之前触发超时事件。这样就可以避免上述问题。

    因此，在 `poll()` 函数超时后，应该先读取定时器文件描述符中的数据来清除定时器，然后再处理其他事件，以避免意外触发下一次超时事件。

    这里的知识点是，使用定时器（例如 `timerfd`）时，需要及时清除定时器并读取其数据，以避免下一次调用 `poll()` 函数时触发意外的超时事件。
    同时，还要注意定时器的类型，以确定超时时间的单位和计算方式。
*/