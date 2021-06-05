 1 #include<cstdio>
  2 #include<iostream>
  3 #include<unistd.h>
  4 #include<string>
  5 #include<sys/socket.h>
  6 #include<arpa/inet.h>
  7 #include<netinet/in.h>
  8 #define CHECK_RET(q) if((q)==false){return -1;}
  9 #define LISTEN_BACKLOG 5
 10 class TcpSocket{
 11 private:
 12     int _sockfd;
 13 public:
 14     TcpSocket()
 15     :_sockfd(-1)
 16     {}
 17 
 18     bool Socket(){
 19         _sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
 20         if(_sockfd<0){
 21             perror("socket error");
 22             return false;
 23         }
 24         //std::cout<<_sockfd<<std::endl;
 25         return true;
 26     }
 27 
 28     bool Bind(const std::string& ip,const uint16_t port){
 29         sockaddr_in addr;
 30         addr.sin_family=AF_INET;
 31         addr.sin_port=htons(port);
 32         addr.sin_addr.s_addr=inet_addr(&ip[0]);
 33         socklen_t len=sizeof(sockaddr_in);
 34         int ret=bind(_sockfd,(sockaddr*)&addr,len);
 35         if(ret<0){
 36             perror("bind error");
 37             return -1;
 38         }
 39     return true;
 40     }
 41 
 42     bool Send(const std::string &data){
 43         int total=0;
 44         while(total<data.size()){
 45             int ret=send(_sockfd,&data[0]+total,data.size()-total,0);
 46             if(ret<0){
 47                 perror("send error");
 48                 return false;
 49             }
 50             total+=ret;
 51         }
  52     return true;
 53     }
 54 
 55     bool Recv(std::string* buf){
 56 //int recv(描述符，空间地址，数据长度，标志位);
 57 //返回值：实际获取大小，0——连接断开，-1——出错;
 58         char tmp[4096]={0};
 59         int ret=recv(_sockfd,tmp,4096,0);
 60         if(ret<0){
 61             perror("recv error");
 62             return false;
 63         }
 64         else if(ret==0){
 65         std::cout<<"peer shutdown";
 66             return false;
 67         }
 68     buf->assign(tmp,ret);
 69     return true;
 70     }
 71 
 72     bool Listen(int backlog=LISTEN_BACKLOG){
 73 //listen(描述符，同一时间连接数);
 74         int ret=listen(_sockfd,backlog);
 75         if(ret<0){
 76             perror("listen error");
 77             return false;
 78         }
 79     return true;
 80     }
 81 
 82     bool Accept(TcpSocket* sock,std::string* ip=NULL,uint16_t* port=NULL){
 83 //int accept(监听套接字，回去客户端地址，长度);
 84     sockaddr_in addr;
 85     socklen_t len=sizeof(sockaddr_in);
 86     int newfd=accept(_sockfd,(sockaddr*)&addr,&len);
 87     if(newfd<0){
 88         perror("accept error");
 89         return false;
 90     }
 91     sock->_sockfd=newfd;
 92     if(ip!=NULL){
 93         *ip=inet_ntoa(addr.sin_addr);
 94     }
 95     if(port!=NULL){
 96         *port=ntohs(addr.sin_port);
 97     }
 98     return true;
 99     }
100 
101     bool Connect(const std::string &ip,const int port){
102         sockaddr_in addr;
103         addr.sin_family=AF_INET;
104         addr.sin_port=htons(port);
105         addr.sin_addr.s_addr=inet_addr(&ip[0]);
106         socklen_t len=sizeof(sockaddr_in);
107     std::cout<<_sockfd<<"--"<<addr.sin_port<<"--"<<ip[0]<<"--"<<ip[1]<<"--"<<len<<std::endl;
108     //connect(描述符，服务端地址，地址长度);
109     int ret=connect(_sockfd,(sockaddr*)&addr,len);
110     if(ret<0){
111         perror("connect error");
112         return false;
113     }
114     return true;
115     }
116 
117     bool Close(){
118         if(_sockfd!=-1){
119             close(_sockfd);
120         }
121         return true;
122     }
123 };
