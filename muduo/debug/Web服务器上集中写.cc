/*
    readv
    writev
    相当于简化版的 recvmsg sendmsg
    Web 服务器应答，传输客户端请求的文档，这个HTTP应答包含：
*/
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 1024
/*
    定义两种 HTTP 状态码和状态信息
*/
static const char* status_line[2] = {"200 OK", "500 Internet server error"};

int main(int argc, char* argv[]) {
    if(argc < 3){
        printf("usage: %s ip_address port_number filename\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    
}

