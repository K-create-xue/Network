 1 #include"tcpsocket.hpp"
  2 
  3 int main(int argc,char *argv[]){
  4 //通过程序运行参数指定服务端要绑定的地址信息
  5 // ./tcp_srv 192.168.106.133 9050
  6     if(argc!=3){
  7     std::cout<<"usage: ./tcp_srv 192.168.106.133 9050"<<std::endl;
  8     return -1;
  9     }
 10     std::string srvip=argv[1];
 11     uint16_t srvport=std::stoi(argv[2]);
 12     TcpSocket lst_sock;//监听套接字
 13     //1.创建套接字
 14     CHECK_RET(lst_sock.Socket());
 15     //2.绑定地址信息
 16     CHECK_RET(lst_sock.Bind(srvip,srvport));
 17     //3.开始监听
 18     CHECK_RET(lst_sock.Listen());
 19     while(1){
 20     //4.获取新建连接
 21         TcpSocket clisock;
 22         std::string cliip;
 23         uint16_t cliport;
 24         bool ret=lst_sock.Accept(&clisock,&cliip,&cliport);
 25         if(ret==false){
 26             //clisock.Close();
 27             continue;
 28         }
 29         std::cout<<"get newconnect:"<<cliip<<"--"<<cliport<<std::endl;
 30     //5.收发数据——使用获取的新建套接字进行通行
 31     std::string buf;
 32     ret=clisock.Recv(&buf);
 33     if(ret==false){
 34         clisock.Close();
 35         continue;
 36         }
 37         std::cout<<"client say: "<<buf<<std::endl;
 38         buf.clear();
 39 
 40         std::cout<<"server say: ";
 41         std::cin>>buf;
 42         ret=clisock.Send(buf);
 43         if(ret==false){
 44             clisock.Close();
 45         }
 46     }
 47     //6.关闭套接字
 48     lst_sock.Close();
 49     return 0;
 50 }
