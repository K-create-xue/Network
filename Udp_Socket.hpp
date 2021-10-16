/*************************************************************************                                                                                                                                                                                                                                                                                                                    
    > File Name: udp_socket.cpp
    > Author: Black_K
    > Mail: xzp01@foxmail.com 
    > Created Time: 2021年10月15日 星期五 21时13分50秒
 ************************************************************************/
#include<cstdio>
#include<string>
#include<unistd.h>
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
using namespace std;

class Udp_Socket{
    private:
        int _sockfd;
    public:
        Udp_Socket()
            :_sockfd(-1){}
        bool Socket(){
            _sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
            if(_sockfd<0){
                perror("socket error:\n");
                return false;
            }   
            return true;
        }   
        bool Bind(std::string &ip,uint16_t port){
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(port);
            addr.sin_addr.s_addr=inet_addr("ip.c_str()");
            socklen_t len=sizeof(addr);
            int ret=bind(_sockfd,(struct sockaddr*)&addr,len);
            if(ret<0){
                perror("bind error\n");
                return false;
            }   
            return true;
        }   
        bool Send(std::string &data,const std::string &ip,const uint16_t port){
            struct sockaddr_in addr;
            addr.sin_family=AF_INET;
            addr.sin_port=htons(port);
            addr.sin_addr.s_addr=inet_addr(ip.c_str());
            socklen_t len=sizeof(addr);
            int ret=sendto(_sockfd,data.c_str(),data.size(),0,(sockaddr*)&addr,len);
            if(ret<0){
                perror("send_to error\n");
                return false;
            }   
            return true;
        }   
        bool Recv(std::string *buf,std::string *ip=NULL,int *port=NULL){
            struct sockaddr_in addr;
            char temp[4096]={0};
            socklen_t len=sizeof(addr);
            int ret=recvfrom(_sockfd,temp,4096,0,(struct sockaddr*)&addr,&len);
            if(ret<0){
                perror("recvfrom error:\n");
                return false;
            }   
            buf->assign(temp,ret);
            if(ip!=NULL)
                *ip=inet_ntoa(addr.sin_addr);
            if(port!=NULL)
                *port=ntohs(addr.sin_port);
            return true;
        }   
        bool Close(){
            if(_sockfd!=-1)
                close(_sockfd);
            return true;
        }   
};
