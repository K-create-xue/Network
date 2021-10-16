/*************************************************************************                                                                                                                                                                                                                                                                                                                    
    > File Name: udp_server.c
    > Author: Black_K
    > Mail: xzp01@foxmail.com 
    > Created Time: 2021年10月14日 星期四 15时39分21秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>//字节序转换接口
#include<netinet/in.h>//地址结构头文件，协议类型文件
#include<sys/socket.h>//socket 


int main(int argc,char* argv[]){
//"start coding K:"
    //1.创建套接字
    int sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd<0){
        perror("socket error:\n");
        return -1;
    }
    //2.绑定套接字
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9000);
    addr.sin_addr.s_addr=inet_addr("172.22.226.182");
    int len=sizeof(addr);
    int ret=bind(sockfd,(struct sockaddr*)&addr,len);
    if(ret<0){
        perror("bind error:\n");
        return -1;
    }
    struct sockaddr_in addr_recv;
    while(1){
    //3.接受收据
    char buf[1024]={0};
    len=sizeof(struct sockaddr_in);
    ret=recvfrom(sockfd,buf,1023,0,(struct sockaddr*)&addr_recv,&len);
    if(ret<0){
        perror("recvfrom error:\n");
        return -1;
    }
    uint16_t cport=ntohs(addr_recv.sin_port);
    char* cip=inet_ntoa(addr_recv.sin_addr);
    printf("client - [%s : %d]-said: %s\n",cip,cport,buf);



    //4.回复数据
    memset(buf,0,1024);
    printf("server said: ");
    fflush(stdout);
    fgets(buf,1023,stdin);
    printf("\n");
    //char *data="冲啊，，，学啊，，，";
    ret=sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&addr_recv,len);
    if(ret<0){
        perror("sendto error:\n");
        return -1;
    }
    }
    //printf("server said: %s\n",buf);

    //5.关闭套接字
    close(sockfd);
    return 0;

}
