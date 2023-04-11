#include "muduo/net/EventLoop.h"

#include <unistd.h>
#include <stdio.h>



int main() {
    printf("main(): pid = %d, tid = %d\n",
    getpid(), muduo::CurrentThread::tid());


}