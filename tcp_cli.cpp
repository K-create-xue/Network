 1 #include"tcpsocket.hpp"
  2 
  3 int main(int argc,char *argv[]){
  4 //通过参数传入要连接的服务端地址信息
  5     if(argc!=3){
  6         std::cout<<"usage: ./tcp_cli srcip srvport"<<std::endl;
  7         return -1;
  8     }
  9     std::string srvip=argv[1];
 10     uint16_t srvport=std::stoi(argv[2]);
 11     std::cout<<srvip<<"__"<<srvport<<std::endl;
 12     TcpSocket cli_sock;
 13     //1.创建套接字
 14     CHECK_RET(cli_sock.Socket());
 15     //2.绑定地址信息（不推荐）
 16     //3.向服务端发起连接
 17     CHECK_RET(cli_sock.Connect(srvip,srvport));
 18     while(1){
 19     //4.收发数据
 20         std::string buf;
 21         std::cout<<"client say: ";
 22         std::cin>>buf;
 23         CHECK_RET(cli_sock.Send(buf));
 24 
 25         buf.clear();
 26         CHECK_RET(cli_sock.Recv(&buf));
 27         std::cout<<"server say: "<<buf<<std::endl;
 28     }
 29     //5.关闭套接字
 30     CHECK_RET(cli_sock.Close());
 31     return 0;
 32 }
