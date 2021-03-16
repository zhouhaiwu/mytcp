#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>   //connect,send,recv,setsockopt等
#include <sys/types.h>      
#include <netinet/in.h>     // sockaddr_in, "man 7 ip" ,htons
#include <poll.h>             //poll,pollfd
#include <arpa/inet.h>   //inet_addr,inet_aton
#include <unistd.h>        //read,write
#include <netdb.h>         //gethostbyname
#include <error.h>         //perror
#include <errno.h>         //errno
#include <string.h>          // memset
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define PORT 6666
#define BUFLEN 200


//int getaddrinfo(const char *host, const char *service, const struct addrinfo *hints, struct addrinfo **result);

int main(int argc, char **argv) {
    //步1：定义sockaddr_in型结构变量
    struct sockaddr_in s_addr;
    char msg[200];
    int rc;
    socklen_t len;
    int flag;
    /*通过sockfd（网络套接字描述符）
    找到os分配的一小块内存把客户端的网络信息写入该内存地址并且和服务端的网络相关信息（IP地址、端口）建立因特网连接*/
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(errno);
    }else
        printf("socket create success!\n");
    /*设置服务器的IP和端口,组成一个套接字*/
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    //SA.sin_addr = argv[1];
    if (inet_aton(argv[1], (struct in_addr *)&s_addr.sin_addr.s_addr) == 0) {//功能是将一个字符串IP地址转换为一个32位的网络序列IP地址
        perror(argv[1]);
        exit(errno);
    }
    //rc = inet_pton(AF_INET, argv[1], (struct in_addr *)&s_addr.sin_addr.s_addr);
    //if (rc == 0)
    //    printf("inet_pton error: invalid dotted-decimal address");
        //app_error("inet_pton error: invalid dotted-decimal address");
    //else if (rc < 0)
        //unix_error("inet_pton error");
    //    printf("inet_pton error\n");

    /*通过sockfd（网络套接字描述符）把客户端的网络相关信息（IP地址、端口）
    写入指定的内存地址同时和服务端的网络相关信息（IP地址、端口）建立因特网连接*/
    int connfd = connect(sockfd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr));
    if (connfd == -1) {
        perror("connect");
        exit(errno);
    }else
        printf("conncet success!\n");
    printf("connfd:%d\n", connfd);
    int len1;
    int len2;
    while(1) {
        //printf("请输入内容：\n");
        //scanf();
        //recvfrom(sockfd, msg, strlen(msg), 0, &s_addr, &addr_len);
        //int len1 = sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&s_addr, len);
        //scanf("%s", msg);
        /*int len1 = write(sockfd,msg,strlen(msg));
        if (len1 > 0)
            printf("msg:%s\n", msg);
        else
            printf("发送失败\n");*/
        //printf("client: ");
        len2 = read(sockfd, msg, BUFLEN);
        //scanf("%s", msg);
        //len2 = write(sockfd, msg, strlen(msg));
        //sendto(sockfd, msg, strlen(msg), &SA, 0);
        if (len2 > 0) {
            printf("msg:%s\n", msg);
        }
        else {
            printf("接收失败\n");
        }
    }
    close(sockfd);
    return 0;
}