#include"Tcp_Socket.hpp"                                                                                                                                                                                                                                                        


int main(int argc,char* argv[]){
    //./tcp_server 192.1.1.1 9000
    if(argc!=3){
        printf("usage: ./tcp_server 192.1.1.1 9000\n");
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
    std::cout<<"get newconn: "<<cliip<<"-"<<cliport<<endl;
    //5.收发信息
    std::string buf;
    ret=clisock.Recv(&buf);
    if(ret==false){
        clisock.Close();
        continue;
    }
    std::cout<<"client said: "<<buf<<endl;

    buf.clear();
    cout<<"server said: ";
    cin>>buf;
    ret=clisock.Send(buf);
    if(ret==false)
        clisock.Close();
    }
    //6.关闭套接字
    lst_sock.Close();
    return 0;
}
