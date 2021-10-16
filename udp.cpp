/*************************************************************************
    > File Name: udp_client.cpp
    > Author: Black_K
    > Mail: xzp01@foxmail.com 
    > Created Time: 2021年10月16日 星期六 13时08分11秒
 ************************************************************************/

#include<iostream>
#include"Udp_Socket.hpp"
#define CHECK_RET(q) if((q)==false){return -1;}
using namespace std;


int main(int argc,char* argv[]){
    Udp_Socket sock;
    //1.创建套接字
    CHECK_RET(sock.Socket());
    //2.绑定地址信息(不推荐)
    while(1){
        //3.发送数据
        std::cout<<"clinet said: ";
        std::string buf;
        std::cin>>buf;
        CHECK_RET(sock.Send(buf,"172.22.226.182",9000))
        //4.接受数据
        buf.clear();
        CHECK_RET(sock.Recv(&buf));
        std::cout<<"server said: "<<buf<<std::endl;
    }   
    //5.关闭套接字
   sock.Close();
    return 0;
}                    
