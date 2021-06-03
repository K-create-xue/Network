 1 #include"udpsocket.hpp"
  2 
  3 #define CHECK_RET(q) if((q)==false){return -1;}
  4 
  5 int main(){
  6 UdpSocket sock;
  7 //1.创建套接字
  8 CHECK_RET(sock.Socket());
  9 //2.绑定地址信息(客户端，不推荐）；
 10 while(1){
 11     //3.发送数据
 12     std::cout<<"client say:";
 13     std::string buf;
 14     std::cin>>buf;
 15     CHECK_RET(sock.Send(buf,"192.168.106.133",9050));
 16     //4.接受数据
 17     buf.clear();
 18     CHECK_RET(sock.Recv(&buf));
 19     std::cout<<"server say:"<<buf<<"\n";
 20 }
 21 //5.关闭套接字
 22 //sock.Close();
 23 return 0;
 24 }
