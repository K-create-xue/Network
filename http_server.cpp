#include"Tcp_Socket.hpp"
#include<sstream>

int main(int argc,char* argv[]){
    //./tcp_server 192.1.1.1 9000
    if(argc!=3){
        printf("usage: ./tcp_server 172.22.226.182 9000\n");
        return -1;
    }
    std::string srvip=argv[1];
    uint16_t srvport=std::stoi(argv[2]);
    Tcp_Socket lst_sock;//监听套接字
    //1.创建套接字
    CHECK_RET(lst_sock.Socket());
    //2.绑定地址信息
    CHECK_RET(lst_sock.Bind(srvip,srvport));
    //3.开始监听
    CHECK_RET(lst_sock.Listen());
    while(1){
        //4.获取新建套接字
        Tcp_Socket clisock;
        std::string cliip;
        uint16_t cliport;
        bool ret=lst_sock.Accept(&clisock,&cliip,&cliport);
        if(ret==false)
            continue;
        std::string buf;
        clisock.Recv(&buf);
        std::cout<<"request:["<<buf<<"]\n";

        std::string body="<html><body><h1>Hello Black_K</h1></body></html>";
        std::stringstream ss;
        ss<<"HTTP/1.1 200 OK\r\n";
        ss<<"Connection: close\r\n";
        ss<<"Content-Length: "<<body.size()<<"\r\n";
        ss<<"Content-type: text/html\r\n";
        //ss<<"Content-type: application/octet-stream\r\n";
        ss<<"\r\n";
        ss<<body;
        clisock.Send(ss.str());
        clisock.Close();
    }
    //6.关闭套接字
    lst_sock.Close();
    return 0;
}
