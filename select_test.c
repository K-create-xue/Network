 /*************************************************************************                                                                                                                                                                                                                                                                                                                                                                                                                 
      > File Name: select1.c
      > Author: Black_K
      > Mail: xzp01@foxmail.com 
      > Created Time: Thu 28 Oct 2021 07:18:54 PM CST
   ************************************************************************/
  
  //针对标准输入进行可读事件监控
  //当标准输入有数据可读，对其进行read操作
  #include<sys/select.h>
  #include<stdio.h>
  #include<unistd.h>
  #include<stdlib.h>
  #include<string.h>
  
W>int main(int argc,char* argv[]){
  //"start coding K:"
      fd_set rfds;
      FD_ZERO(&rfds);
      while(1){
          FD_SET(0,&rfds);
          struct timeval tv;
          tv.tv_sec=3;
          tv.tv_usec=0;
          int res=select(1,&rfds,NULL,NULL,&tv);
          if(res<0){
              perror("select error:");
              return -1;
          }else if(res==0){
              printf("监控超时：\n");
              continue;
          }
          if(FD_ISSET(0,&rfds)){
              printf("0-就绪\n");
          char buf[1024]={0};
          int ret=read(0,buf,1023);
          if(ret<=0){
              printf("read error;\n");
              return -1;
          }
          printf("buf:[%s]\n",buf);
      }
      }
      return 0;
  }
