 #include<iostream>                                                                                                                                                                                                                                                            
  #include<sys/select.h>    
  #include"Tcp_Socket.hpp"    
  #include<vector>    
  #include<time.h>    
  
  class Select{    
      public:    
          Select():_max_fd(-1){    
              FD_ZERO(&_rfds);    
          }    
          bool Add(const Tcp_Socket &sock){//添加监控    
            int fd=sock.GetFD();    
              FD_SET(fd,&_rfds);    
              _max_fd=_max_fd>fd?_max_fd:fd;    
              return true;    
          }    
          bool Del(const Tcp_Socket &sock){    
           int fd=sock.GetFD();    
            FD_CLR(fd,&rfds);//移除    
              //重新判断最大描述符    
              for(int i=_max_fd;i>=0;--i){    
                  if(FD_ISSET(i,&_rfds)){    
                      _max_fd=i;    
                      break;    
                  }    
              }    
              return true;    
          }    
      
          //通过参数返回就绪的套接字数组    
          bool Wait(std::vector<Tcp_Socket>* arry){    
              struct timeval tv;    
              tv.tv_sec=3;    
              tv.tv_usec=0;    
              //select(max+1,r,w,e,超时);    
              fd_set tmp=_rfds;    
              int ret=select(_max_fd+1,&tmp,NULL,NULL,&tv);    
              if(ret<0){    
                  perror("select error:");    
                  return -1;    
              }else if(ret==0){    
                  arry->clear();    
                  return true;    
              }    
              for(int i=0;i<_max_fd;++i){    
                  if(FD_ISSET(i,&tmp)){    
                      Tcp_Socket sock;    
                      sock.SetFD(i);    
                      arry->push_back(sock);    
                  }    
              }    
              return true;    
          }    
      private:    
          fd_set _rfds;//需要监控描述符集合    
          int _max_fd;//保存当前集合中最大描述符    
}    
