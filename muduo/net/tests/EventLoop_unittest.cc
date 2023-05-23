//#include "../../muduo/muduo/net/EventLoop.h"
//#include "../../muduo/muduo/base/Mutex.h"
#include "../EventLoop.h"
#include "../../base/Thread.h"


#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace muduo;
using namespace muduo::net;

void threadFunc() {
    cout << "threadfunc(): pid = " << getpid() << " tid = " << muduo::CurrentThread::tid() << endl;
    muduo::net::EventLoop loop;
    loop.loop();
}

int main() {
    cout << "test1: " << endl;
    // printf("main(): pid = %d, tid = %d\n",
    // getpid(), muduo::CurrentThread::tid());
    cout << "main() : pid = " << getpid() << "tid = " << muduo::CurrentThread::tid() << endl;

    EventLoop loop;
    Thread thread(threadFunc);
    thread.start();

    loop.loop();
    pthread_exit(NULL);
}

// 编译：make eventloopthread_unittest