#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <fstream>
using namespace std;
int count=1;
int client_socket[999];
//char *log[1000];
//int count_log=0;
fstream file;
//创建一个线程用于接受和执行服务端指令
void* common(void*id)
{
    string input;
    int ser_socket=*((int*)id);
    while (1)
    {
        cin>>input;
        //接到指令“exit”后关闭服务socket并退出程序，避免服务端socket在程序直接关闭(ctrl+c)后持续占用
        if (input=="exit")
        {
            close(ser_socket);
            cout<<"已关闭服务端socket"<<endl;
            for (int i = 0; i < count; i++)
            {
                close(client_socket[i]);
                cout<<"已关闭客户端"<<client_socket[i]<<"socket"<<endl;
            }
            
            exit(0);
        }
    } 
}
void* server_thread(void* id)
{
    //将传入的无类型指针id转化为整数形
    //int client_socket[999];
    int client_socket_=*((int*)id);
    char str[2048]={0};
    int nbytes;
    char line[2048];//用于读入历史消息文件一行

    //开始发送历史消息
    file.open("./log.txt",ios::in);
    while(file.getline(line,2048))
    {
        
        send(client_socket_,line,sizeof(line),MSG_NOSIGNAL);
        usleep(20000);
    }
    send(client_socket_,"/log done",9,MSG_NOSIGNAL);
    file.close(); 
    //开始循环阻塞收发并记录消息
    while (1)
    {   memset(str,0,sizeof(str));
        //recv(client_socket,*str,2048,0);
        
        nbytes=read(client_socket_,str,sizeof(str)); 
        if(nbytes<0) 
        {
            close(client_socket_);
            cout<<"客户端"<<client_socket_<<"断开了连接"<<endl;

            pthread_exit(NULL);

        }
        
        cout<<"来自客户端："<<str<<endl;
        //if(nbytes<0) cout<<"read_error:"<<nbytes<<endl;
        //send(client_socket[count],str,2048,0);
        file.open("./log.txt",ios::app);
        cout<<"是否打开文件:"<<file.is_open()<<endl;
        file<<str<<endl; //向文件写入新消息
        file.close();
        /*
        if (count_log<999) 
        {
            
        }
        else
       {
            for (int i = 0; i < 500; i++)
            {
                log[i]=log[i+500];
                log[i+500]={};
            }
            count_log=500;
            log[count_log]=str;
       }
       count_log++;
       */
       for (int i = 0; i < count; i++)
       {
            send(client_socket[i],str,nbytes,MSG_NOSIGNAL);
       }
       
       
    }
    
}
int main()
{
    
    //设置连接最多可能数，避免之前连接未销毁以优化
    int max=1;
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
    //system("node socket.server.js");
    //执行js转发脚本
    pthread_t count_id[99999];
    pthread_create(&count_id[99999],NULL,common,(void*)&(ser_socket));
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_size=sizeof(client_addr);
        int a=accept(ser_socket,(struct sockaddr*)&client_addr,&client_addr_size);
        client_socket[a-4]=a;
        cout<<"aceept():done"<<endl;
        count_id[count]=count;
        //创建新的线程
        pthread_create(&count_id[count],NULL,server_thread,(void*)&(client_socket[a-4]));
        if(a-3>max)
        {
            count++;
            max=a-3;
        }
        
    }
     

    
    
    //关闭ser_socket
    close(ser_socket);
    pthread_exit(NULL);
    cout<<"已关闭服务器数据传输"<<endl;;
    return 0;

}
