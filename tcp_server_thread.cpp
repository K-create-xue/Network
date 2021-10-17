/*************************************************************************
    > File Name: tcp_server_thread.cpp
    > Author: Black_K
    > Mail: xzp01@foxmail.com 
    > Created Time: 2021年10月17日 星期日 09时41分00秒
 ************************************************************************/


#include "Tcp_Socket.hpp"
#include <pthread.h>

void *thr_entry(void *arg)
{
    bool ret;
    Tcp_Socket *clisock = (Tcp_Socket*)arg;
    while(1) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
        //5. 收发数据--使用获取的新建套接字进行通信
        std::string buf;
        ret = clisock->Recv(&buf);
        if (ret == false) {
            clisock->Close();
            delete clisock;
            return NULL;
        }   
        std::cout << "client say: " << buf << std::endl;

        buf.clear();
        std::cout << "server say: ";
        std::cin >> buf;
        ret = clisock->Send(buf);
        if (ret == false) {
            clisock->Close();
            delete clisock;
            return NULL;
        }   
    }   
    clisock->Close();
    delete clisock;
    return NULL;
}
int main(int argc, char *argv[])
{
    //通过程序运行参数指定服务端要绑定的地址
    // ./tcp_srv 192.168.2.2 9000
    if (argc != 3) {
        printf("usage: ./tcp_src 192.168.2.2 9000\n");
        return -1; 
    }   
    std::string srvip = argv[1];
    uint16_t srvport = std::stoi(argv[2]);
    Tcp_Socket lst_sock;//监听套接字
    //1. 创建套接字
    CHECK_RET(lst_sock.Socket());
    //2. 绑定地址信息
    CHECK_RET(lst_sock.Bind(srvip, srvport));
    //3. 开始监听
    CHECK_RET(lst_sock.Listen());
    while(1) {
        //4. 获取新建连接
        Tcp_Socket *clisock = new Tcp_Socket();
        std::string cliip;
        uint16_t cliport;
        bool ret = lst_sock.Accept(clisock, &cliip,&cliport);
        if (ret == false) {
            continue;
        }   
        std::cout<<"get newconn:"<< cliip<<"-"<<cliport<<"\n";
        //创建线程专门负责与指定客户端的通信
        pthread_t tid;
        pthread_create(&tid, NULL, thr_entry, (void*)clisock);
        pthread_detach(tid);
    }   
    //6. 关闭套接字
    lst_sock.Close();
}
