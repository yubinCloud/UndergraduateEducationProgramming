#include <windows.h>
#include <winsock2.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define BUFFSIZE 1024
#define LISTENQ 80

using namespace std;


int main(int argc, char** argv)
{
    WSADATA wsadata;
    WORD wVersionRequested = MAKEWORD(2, 1);
    WSAStartup(wVersionRequested, &wsadata);

    int  serverAddrlen;
    SOCKET ListenSocket, ClientSocket;

    //establish socket
    ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ListenSocket < 0)
    {
        cout << "Socket establishes error!" << endl;
        cout << "Error numble is " << WSAGetLastError() << endl;
    }


    //bind
    sockaddr sockaddrlength;
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(25);
    servaddr.sin_addr.S_un.S_addr = htonl(inet_addr("127.0.0.1"));// inet_addr("127.0.0.1");//INADDR_ANY会报错
    serverAddrlen = sizeof(sockaddrlength);
    if (bind(ListenSocket, (sockaddr*)&servaddr, serverAddrlen) < 0)
    {
        cout << "Bind occurs error" << endl;
        cout << "Error numble is " << WSAGetLastError() << endl;
    }

    //listen
    if (listen(ListenSocket, LISTENQ) < 0)
    {
        cout << "Listen error" << endl;
        cout << "Error numble is " << WSAGetLastError() << endl;
    }

    //accept
    //注意服务器要循环，表示可以接收多个连接
    for (; ; )
    {
        //accept后两个参数可以为NULL
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket < 0)
        {
            cout << "accept error" << endl;
            cout << "Error numble is " << WSAGetLastError() << endl;
        }

        //recv
        //服务器接收后原样send给客户端
        char buf[BUFFSIZE];
        memset(buf, 0, BUFFSIZE);
        int iResult = 1;
        //	cout << "发送的字符串是：" << endl;
        while (strcmp(buf, "quit\n"))
        {
            cout << "发送的字符串是：" << endl;
            do
            {

                iResult = recv(ClientSocket, buf, BUFFSIZE, 0);
                if (iResult > 0)
                {
                    //接收成功就回送
                    if (send(ClientSocket, buf, strlen(buf), 0) < 0)
                    {
                        cout << "send error" << endl;
                        cout << "Error numble is " << WSAGetLastError() << endl;
                    }
                    else cout << buf << endl;

                }
                else
                {
                    if (iResult == 0)
                        cout << "连接已断开" << endl;
                    else
                        cout << "recv出错" << endl;
                }
                //memset(buf, 0, BUFFSIZE);

            } while (iResult > 0);
        }



        //shutdown ClientSocket
        if (shutdown(ClientSocket, SD_SEND) < 0)
        {
            cout << "shutdown 函数调用错误，错误号： " << WSAGetLastError() << endl;

        }
        closesocket(ClientSocket);

    }



    shutdown(ListenSocket, 2);
    closesocket(ListenSocket);
    cout << "主动关闭连接";

    WSACleanup();
    return 1;
}