#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include <wininet.h>
#include <winsock2.h>
#include <winsock.h>
#include <pthread.h>
#include <windows.h>
#include <cstring>
#pragma comment(lib, “wsock32.lib”)
using namespace std;
void* read_thread(void* id)
{
    char buf[2048]={0};
    int sock=*((int*)id);
    while (1)
    { 
        if(recv(sock,buf,2048,0)>0) cout<<"server:"<<buf<<endl; 
        memset(buf,0,sizeof(buf));
    }
    //memset(buf,0,sizeof(buf));
    
    //结束进程和套接字
    closesocket(sock);
    pthread_exit(NULL);
}
int main(){
    //WSADATA WSAData;
    //WSAStartup(MAKEWORD(2,2),&WSAData);
    //创建套接字
    WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if(WSAStartup(sockVersion, &data)!=0)
	{
		return 0;
    }
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("81.68.123.231");  //具体的IP地址
    serv_addr.sin_port = htons(22516);  //端口
    int a=connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(a!=0) cout<<"connect():error"<<a;
    //读取服务器传回的数据
    else
    {
        pthread_t a=1;
        HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)read_thread, (void*)&sock, 0, NULL);
        while (1)
        {
            char str[2048]={0};
            cin>>str;
            //const char * mes;
		    //mes = str.c_str();
            
            send(sock,str,strlen(str),0);
            memset(str,0,sizeof(str));
        }       
        
        
    }
    //关闭套接字
    system("pause");
    closesocket(sock);

    return 0;
}