// udp  服务端的
  2 #include<stdio.h>
  3 #include<unistd.h>
  4 #include<string.h>
  5 #include<arpa/inet.h>//字节序转换接口头文件
  6 #include<netinet/in.h>//地址结构头文件，协议类型头文件
  7 #include<sys/socket.h>//套接字头文件
  8 
  9 //服务端serve
 10 int main(){
 11 //1.创建套接字
 12 //int socket（地址域类型，套接字类型，协议类型）；
 13 //int sockfd=socket(int domain, int type, int protocol);
 14  int sockfd=socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);
 15  if(sockfd<0){
 16 perror("socket error\n");
 17     return -1;
 18  }
 19 //2.为套接字绑定地址信息  绑定xshell绑定的地址
 20 //int bind(套接字描述符，地址信息，地址长度）
 21 //int bind(int sockfd,struct sockaddr* addr,socklen_t addrlen);
 22 struct sockaddr_in addr;//定义IPV4地址结构
 23 addr.sin_family=AF_INET;
 24 addr.sin_port=htons(9050);//设置地址端口
 25 addr.sin_addr.s_addr=inet_addr("192.168.106.133");
 26 int len=sizeof(addr);
 27 int ret=bind(sockfd,(struct sockaddr*)&addr,len);
 28 if(ret<0){
 29     perror("bind error\n");
 30     return -1;
 31 }
 32 
 33 //需要一直接受数据、发送数据
 34 while(1){
 35 //3.接受数据
 36 //recvfrom(句柄，空间，长度，标志，对端地址，地址长度）；
 37 //ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
 38 //                        struct sockaddr *src_addr, socklen_t *addrlen);
 39 char buf[1024]={0};
 40 struct sockaddr_in paddr;
 41 int len=sizeof(struct sockaddr_in);
 42 ret=recvfrom(sockfd,buf,1023,0,(struct sockaddr*)&paddr,&len);
 43 if(ret<0){
 44     perror("recvfrom error\n");
 45     return -1;
 46 }
 47 uint16_t cport=ntohs(paddr.sin_port);
 48 char* cip=inet_ntoa(paddr.sin_addr);
 49 printf("client-[%s,%d]- said:%s\n",cip,cport,buf);
 50 
 51 //char *data="终于看完了~~";
 52 //4.发送/回复数据
 53 //ssize_t sendto(int sockfd,void* buf,size_t len,int flags,struct sockaddr* addr,socklen_t addrlen);
 54 memset(buf,0x00,1024);
 55 printf("server  said:");
 56 fflush(stdout);
 57 fgets(buf,1023,stdin);
 58 ret=sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&paddr,len);
 59 if(ret<0){
 60     perror("sendto error\n");
 61     return -1;
 62 }
 63 }
 64 
 65 //5.关闭套接字
 66 close(sockfd);
 67 return 0;
 68 }
 69 

   
   
   
   
