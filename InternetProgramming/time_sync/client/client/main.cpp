#include <cstdio>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") //引入动态链接库
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1


constexpr auto MAX_LINE = 4096l;             //接收缓冲区长度
constexpr auto SEVER_PORT = 13131;          //时间同步服务器端口号
constexpr auto SERVER_IP = "127.0.0.1";     // 服务器ip地址


int main()
{
    char recvData[MAX_LINE + 1];

    // 初始化Windows Sockets DLL,协议版本号
    WORD wVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    int res = WSAStartup(wVersion, &wsaData);
    if (res != 0)
    {
        printf("%d  WSAStartup Error!\n", WSAGetLastError());
        return -1;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        printf("Version Error!\n");
        WSACleanup();
        return -1;
    }

    // 设置地址
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;                        // 设置ip协议
    server_addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP); //设置ip
    server_addr.sin_port = htons(SEVER_PORT);                //设置端口

    //创建流式套接字
    SOCKET sock_conn = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_conn == INVALID_SOCKET)
    {
        printf("%d  Socket Error!\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    // 请求连接服务器
    res = connect(sock_conn, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
    if (res == SOCKET_ERROR)
    {
        printf("%d Connect Error!\n", WSAGetLastError());
        closesocket(sock_conn);
        WSACleanup();
        return -1;
    }

    // 清空接收缓冲区 准备接收数据
    memset(recvData, 0, sizeof(recvData));
    printf("Recv Data Is:");

    do
    {
        // 接收数据
        res = recv(sock_conn, recvData, MAX_LINE, 0);
        if (res > 0)
        {
            printf("%s\n", recvData);
        }
        else
        {
            if (res == 0)
            {
                printf("Server is closed!\n");
            }
            else
            {
                printf("%d Recv Error!\n", WSAGetLastError());
            }
        }
    } while (res > 0);

    // 清理环境 断开连接 释放DLL
    closesocket(sock_conn);
    WSACleanup();
    return 0;
}