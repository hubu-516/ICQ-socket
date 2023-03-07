#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
using namespace std;
int count;
void* server_thread(void* id)
{
    //将传入的无类型指针id转化为整数形
    int client_socket=*((int*)id);
    char str[2048]={0};
    int nbytes;
    while (1)
    {  //recv(client_socket,*str,2048,0);
       read(client_socket,str,sizeof(str)); 
       cout<<str<<endl;
       //if(nbytes<0) cout<<"read_error:"<<nbytes<<endl;
       send(client_socket,str,2048,0);
    }
    
    pthread_exit(NULL);
}
int main()
{

    //创建套接字
    int ser_socket=socket(AF_INET,SOCK_STREAM,0);
    //bind信息
    struct sockaddr_in ser_addr;
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(22516);
    if(bind(ser_socket,(struct sockaddr*)&ser_addr,sizeof(ser_addr))<-1)
    {
        //报错
        perror("bind:");
        return -1;
    }
    else cout<<"bind():done"<<endl;
    //开始监听
    if(listen(ser_socket,SOMAXCONN)<-1)
    {
        perror("listen:");
        return -1;
    }
    else cout<<"listen():done"<<endl;
    //不断接受客户端数据
    
    pthread_t count_id[99999];
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_size=sizeof(client_addr);
        int client_socket=accept(ser_socket,(struct sockaddr*)&client_addr,&client_addr_size);
        cout<<"aceept():done"<<endl;
        count_id[count]=count;
        //创建新的线程
        pthread_create(&count_id[count],NULL,server_thread,(void*)&(client_socket));
        count++;
    }
     
    //向客户端发送数据
    
    
    //关闭ser_socket
    close(ser_socket);
    pthread_exit(NULL);
    cout<<"已关闭服务器数据传输"<<endl;;
    return 0;

}
