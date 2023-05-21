//#include "../../muduo/muduo/net/EventLoop.h"

#include "../EventLoop.h"
//#include "../../muduo/muduo/base/Mutex.h"

#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
    cout << "test1: " << endl;
    // printf("main(): pid = %d, tid = %d\n",
    // getpid(), muduo::CurrentThread::tid());
    cout << "main() : pid = " << getpid() << "tid = " << muduo::CurrentThread::tid() << endl;
}