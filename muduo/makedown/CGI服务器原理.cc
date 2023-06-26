#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
    CGI（通用网关接口，Common Gateway Interface）服务器是一种在Web服务器和其他应用程序之间传递数据的标准协议。
    它允许Web服务器调用可执行文件或脚本来处理Web请求，并返回结果给浏览器。

    CGI服务器的工作原理如下：当一个客户端通过浏览器发送一个HTTP请求时，Web服务器会将该请求转发到CGI服务器。
    CGI服务器使用相应的脚本或可执行文件来处理请求，从而生成HTML页面或其他响应内容。
    CGI服务器然后将响应返回到Web服务器，最终发送回客户端的浏览器。

    需要注意的是，CGI服务器是单独的进程，与Web服务器分开运行，因此可以独立管理和扩展。
    同时，由于CGI服务器使用标准协议，它可以与任何Web服务器进行通信，无论它们使用哪种编程语言或操作系统。这使得CGI服务器成为处理动态Web内容的强大工具。
*/

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    /*
        struct sockaddr_in
        {
            __SOCKADDR_COMMON (sin_);
            in_port_t sin_port;			 // Port number.  
            struct in_addr sin_addr;     // Internet address.  

            // Pad to size of `struct sockaddr'.  
            unsigned char sin_zero[sizeof (struct sockaddr)
                    - __SOCKADDR_COMMON_SIZE
                    - sizeof (in_port_t)
                    - sizeof (struct in_addr)];
        };
    */
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    /*
         协议簇     地址簇    描述
        PF_INET   AF_INET   TCP/Ipv4协议簇
    */
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    // short , host -> network
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(socket >= 0);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    if(connfd < 0) {
        printf("errno is : %d\n", errno);
    }
    else{
        /*
            CGI 服务器原理
        */
        close(STDOUT_FILENO);
        dup(connfd);
        printf("abcd\n");
        close(connfd);
    }

    close(sock);
    return 0;                                                                                                                                                                               

}