#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

void read_thread(int sock) {
    char buffer[2048] = { 0 };
    while (1) {
        int len = recv(sock, buffer, 2048, 0);
        if (len > 0) {
            buffer[len] = '\0'; // 在读取到的数据后面添加字符串结束符
            cout << buffer << endl;
        }
        memset(buffer, 0, sizeof(buffer)); // 清空缓冲区
    }
}

int main() {
    // 初始化WinSock
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(wVersionRequested, &wsaData) != 0) {
        cout << "WSAStartup failed." << endl;
        return 1;
    }

    // 创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        cout << "socket failed." << endl;
        WSACleanup();
        return 1;
    }

    // 连接服务器
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  // 使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("81.68.123.231");  // 具体的IP地址
    serv_addr.sin_port = htons(22516);  // 端口
    int ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret != 0) {
        cout << "connect() failed: " << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // 读取服务器传回的数据
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)read_thread, (void*)&sock, 0, NULL);

    // 发送数据
    string str;
    while (1) {
        cin >> str;
        const char* mes = str.c_str();
        send(sock, mes, strlen(mes), 0);
    }

    // 关闭套接字和WinSock
    //t.join();
    closesocket(sock);
    WSACleanup();

    return 0;
}
