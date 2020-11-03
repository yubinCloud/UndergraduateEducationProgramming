#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <winsock2.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib") //���붯̬���ӿ�

constexpr auto MAX_LINE = 4096;     //���ջ���������
constexpr auto LIST_ENQ = 1024;     //�������г���
constexpr auto SEVER_PORT = 13131;  //ʱ��ͬ���������˿ں�

int main()
{
	char buff[MAX_LINE]; //������

    //��ʼ��Windows Sockets DLL,Э��汾��
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

    // ���õ�ַ
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;                // ����ipЭ��
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY -- 0.0.0.0
    serverAddr.sin_port = htons(SEVER_PORT);        //���ö˿�

    //������ʽ�׽���
    const SOCKET socketListen = socket(AF_INET, SOCK_STREAM, 0);
    if (socketListen == INVALID_SOCKET)
    {
        cout << WSAGetLastError() << "Socket Error!" << endl;
        WSACleanup();
        return -1;
    }

    //�󶨵�ַ
    res = bind(socketListen, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (res == SOCKET_ERROR)
    {
        cout << WSAGetLastError() << "Bind address error!" << endl;
        closesocket(socketListen);
        WSACleanup();
        return -1;
    }

    //���ü��� ����г���LIST_ENQ
    res = listen(socketListen, LIST_ENQ);
    if (res == SOCKET_ERROR)
    {
        cout << WSAGetLastError() << "Listen Error!" << endl;
        closesocket(socketListen);
        WSACleanup();
        return -1;
    }

    // ѭ�������� -- ѭ�������û�����������
    while (true)
    {
        //���ܿͻ����������󣬷��������׽���sock_conn
        const SOCKET socketConn = accept(socketListen, nullptr, nullptr);
        if (socketConn == INVALID_SOCKET)
        {
            cout << WSAGetLastError() << "Accept Error!" << endl;
            closesocket(socketListen);
            WSACleanup();
            return -1;
        }

        //��ȡ��ǰʱ��
        auto timestamp = time(nullptr);
        time(&timestamp);
        memset(buff, 0, sizeof(buff)); //��ջ�����
        char timeStrBuf[30];
        ctime_s(timeStrBuf, 30, &timestamp);
        strcpy_s(buff, timeStrBuf);   // ������ת�����ַ���׼������
        cout << "Now time is: " << buff << endl;

        //��������
        res = send(socketConn, buff, strlen(buff), 0);
        if (res == SOCKET_ERROR)
        {
            cout << WSAGetLastError() << "Send Error!" << endl;
            closesocket(socketConn);
            WSACleanup();
            return -1;
        }

        cout << "Sent Time Data Successfully." << endl;

        //ֹͣ���ӣ����ٷ�������
        res = shutdown(socketConn, SD_SEND);
        if (res == SOCKET_ERROR)
        {
            cout << WSAGetLastError() << "Shutdown Error!" << endl;
            closesocket(socketConn);
            WSACleanup();
            return -1;
        }

        //�ر��׽���
        closesocket(socketConn);
        cout << "Server Disconnect" << endl;
    }
}