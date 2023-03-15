#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
using namespace std;
void* read_thread(void* id)
{
    char buf[2048];
    int n;  
    int sock=*((int*)id);
    while (1)
    {
        if(read(sock,buf,sizeof(buf))>0) cout<<"from server:"<<buf<<endl; 
    }
    
    
    //结束进程和套接字
    close(sock);
    pthread_exit(NULL);
}
int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(22516);  //端口
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))!=0) cout<<"connect():error";
    //读取服务器传回的数据
    else
    {
        char buffer[40]={"\0"};
        char str[2048];
        struct mes
        {
            string nick;
            string text;

        }client_mes;
        client_mes.nick="c++-linux";
        pthread_t a=1;
        //pthread_create(&a,NULL,read_thread,(void*)&(sock));
        while (1)
        {
            cin>>client_mes.text;
            if (str[0]=='/'&&str[1]=='e'&&str[2]=='x'&&str[3]=='i'&&str[4]=='t')
            {
                //send(sock,"/exit",2048,0);
                break;
            }
            int a=send(sock,"123",3,0);
            cout<<a<<endl;
        }       
        
        
    }
    //关闭套接字
    close(sock);

    return 0;
}