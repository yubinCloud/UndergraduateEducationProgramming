#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <winsock2.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib") //引入动态链接库

constexpr auto MAX_LINE = 4096;     //接收缓冲区长度
constexpr auto LIST_ENQ = 1024;     //监听队列长度
constexpr auto SEVER_PORT = 13131;  //时间同步服务器端口号

int main()
{
	char buff[MAX_LINE]; //缓冲区

    //初始化Windows Sockets DLL,协议版本号
    constexpr auto WIN_SOCKETS_DLL_VERSION = MAKEWORD(2, 2);
    WSADATA wsaData;

    int res = WSAStartup(WIN_SOCKETS_DLL_VERSION, &wsaData);
    if (res != 0)
    {
        cout << WSAGetLastError() << "WSAStartup Error!" << endl;
        return -1;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        cout << WSAGetLastError() << "Version Error!" << endl;
        WSACleanup();
        return -1;
    }

    // 设置地址
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;                // 设置ip协议
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY -- 0.0.0.0
    serverAddr.sin_port = htons(SEVER_PORT);        //设置端口

    //创建流式套接字
    const SOCKET socketListen = socket(AF_INET, SOCK_STREAM, 0);
    if (socketListen == INVALID_SOCKET)
    {
        cout << WSAGetLastError() << "Socket Error!" << endl;
        WSACleanup();
        return -1;
    }

    //绑定地址
    res = bind(socketListen, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (res == SOCKET_ERROR)
    {
        cout << WSAGetLastError() << "Bind address error!" << endl;
        closesocket(socketListen);
        WSACleanup();
        return -1;
    }

    //设置监听 最长队列长度LIST_ENQ
    res = listen(socketListen, LIST_ENQ);
    if (res == SOCKET_ERROR)
    {
        cout << WSAGetLastError() << "Listen Error!" << endl;
        closesocket(socketListen);
        WSACleanup();
        return -1;
    }

    // 循环服务器 -- 循环处理用户的连接请求
    while (true)
    {
        //接受客户端连接请求，返回连接套接字sock_conn
        const SOCKET socketConn = accept(socketListen, nullptr, nullptr);
        if (socketConn == INVALID_SOCKET)
        {
            cout << WSAGetLastError() << "Accept Error!" << endl;
            closesocket(socketListen);
            WSACleanup();
            return -1;
        }

        //获取当前时间
        auto timestamp = time(nullptr);
        time(&timestamp);
        memset(buff, 0, sizeof(buff)); //清空缓冲区
        char timeStrBuf[30];
        ctime_s(timeStrBuf, 30, &timestamp);
        strcpy_s(buff, timeStrBuf);   // 将数据转换成字符串准备发送
        cout << "Now time is: " << buff << endl;

        //发送数据
        res = send(socketConn, buff, strlen(buff), 0);
        if (res == SOCKET_ERROR)
        {
            cout << WSAGetLastError() << "Send Error!" << endl;
            closesocket(socketConn);
            WSACleanup();
            return -1;
        }

        cout << "Sent Time Data Successfully." << endl;

        //停止连接，不再发送数据
        res = shutdown(socketConn, SD_SEND);
        if (res == SOCKET_ERROR)
        {
            cout << WSAGetLastError() << "Shutdown Error!" << endl;
            closesocket(socketConn);
            WSACleanup();
            return -1;
        }

        //关闭套接字
        closesocket(socketConn);
        cout << "Server Disconnect" << endl;
    }
}