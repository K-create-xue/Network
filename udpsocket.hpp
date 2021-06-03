/* 
  2  * 封装一个实现socket类
  3  * 通过实例化的对象调用对应的接口，
  4  * 可以实现udp客户端和服务端的搭建
  5  */
  6 #include<cstdio>
  7 #include<iostream>
  8 #include<string>
  9 #include<unistd.h>
 10 #include<arpa/inet.h>//字节序转接接口头文件
 11 #include<netinet/in.h>//地址结构头，协议类型文件
 12 #include<sys/socket.h>//套接字接口头文件
 13 
 14 class UdpSocket{
 15 private:
 16     int _sockfd;
 17 public:
 18     UdpSocket()
 19     :_sockfd(-1)
 20     {};
 21 
 22     bool Socket(){
 23     _sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
 24         if(_sockfd<0){
 25             perror("socket error");
 26             return false;
 27         }
 28     return true;
 29     }
 30 
 31     bool Bind(std::string &ip,uint16_t port){
 32         struct sockaddr_in addr;
 33         addr.sin_family=AF_INET;
 34         addr.sin_port=htons(port);
 35         addr.sin_addr.s_addr=inet_addr(ip.c_str());
 36         socklen_t len=sizeof(struct sockaddr_in);
 37         int ret;
 38         ret=bind(_sockfd,(struct sockaddr*)&addr,len);
 39         if(ret<0){
 40             perror("bind error");
 41             return false;
 42         }
 43     return true;
 44     }
 45 
 46     bool Send(std::string &data,const std::string &ip,const int port){
 47         struct sockaddr_in addr;
 48         addr.sin_family=AF_INET;
 49         addr.sin_port=htons(port);
 50         addr.sin_addr.s_addr=inet_addr(ip.c_str());
 51         socklen_t len=sizeof(struct sockaddr_in);
 52         int ret=sendto(_sockfd,data.c_str(),data.size(),0,(sockaddr*)&addr,len);
 53         if(ret<0){
 54             perror("sendto error");
 55             return false;
 56         }
 57     return true;
 58     }
 59 
 60     bool Recv(std::string *buf,std::string *ip=NULL,int* port=NULL){
 61         struct sockaddr_in addr;
 62         socklen_t len=sizeof(struct sockaddr_in);
 63         char tmp[4096]={0};
 64         int ret=recvfrom(_sockfd,tmp,4096,0,(sockaddr*)&addr,&len);
 65         if(ret<0){
 66             perror("recvfrom error");
 67             return false;;
 68         }
 69         buf->assign(tmp,ret);//自带申请空间拷贝数据
 70         if(ip!=NULL){
 71             *ip=inet_ntoa(addr.sin_addr);
 72         }
 73         if(port!=NULL){
 74             *port=ntohs(addr.sin_port);
 75         }
 76         return true;
 77     }
 78 
 79     bool Close(){
 80         if(_sockfd!=-1){
 81             close(_sockfd);
 82         }
 83     return true;
 84     }
 85 };

