#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#define RECVBUFFERLENGTH 1028
#define MaxCount 1024

using namespace std;
int read_cnt = 0;//表示每一次读读取后，还有多少个字符未被判断
char* read_ptr = NULL;

int my_read(SOCKET fd,char* ptr,char * vptr)
{

    if (read_cnt <= 0) {
        again:
        if ((read_cnt = recv(fd, vptr, RECVBUFFERLENGTH,0)) < 0) {
            if (errno == EINTR)
                goto again;
            return(-1);
        }
        else if (read_cnt == 0)
            return(0);
        read_ptr = vptr;
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return(1);
}




int recvline(SOCKET fd,int RECVBUFFLENGTH,char * vptr)
{
    int rc = 0, i = 1;
    char* ptr = vptr;
    char c;

    for ( i = 1; 1 < RECVBUFFERLENGTH; i++)
    {
        if ((rc = my_read(fd, &c, vptr)) == 1)
        {
            *ptr++ = c;
            if (c == '\n')
                break;//newline is stored
        }
        else if (rc == 0)
        {
            //表示读到最后一个字符也不是换行符
            *ptr = 0;
            return i - 1;
        }
        else return -1;
    }
    *ptr = 0;
    return i;

}


int main(int argc, char** argv)
{

    WSADATA wsadata;
    WORD wVersionRequested = MAKEWORD(2, 1);
    WSAStartup(wVersionRequested, &wsadata);
    SOCKET ConnectSocket = INVALID_SOCKET;


    //establish socket
    ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ConnectSocket < 0)
    {
        cout << "Socket establishes error!" << endl;
        cout << "Error numble is " << WSAGetLastError() << endl;
    }

    //connect
    int clientAddrlen;
    sockaddr sockaddrlen;
    sockaddr_in clientaddr;
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(25);
    clientaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    clientAddrlen = sizeof(sockaddrlen);
    if (connect(ConnectSocket, (sockaddr*)&clientaddr, clientAddrlen) < 0)
    {
        cout << "Connect occurs error" << endl;
        cout << "Error numble is " << WSAGetLastError() << endl;
    }

    //先从键盘fgets数据，然后发送给server
    char SendData[BUFSIZ];
    memset(SendData, 0, BUFSIZ);//初始化


    while (SendData != "quit")
    {
        memset(SendData, 0, BUFSIZ);
        cout << "请输入你要发送的数据，输入quit结束" << endl;
        fgets(SendData, MaxCount, stdin);
        send(ConnectSocket, SendData, strlen(SendData), 0);
        cout << "键盘输入的数据是：" << SendData << endl;




        //recvline
        //先尽可能多地读取数据到RecvData,再判断换行符的位置（高效版本）
        //存在问题：输入quit结束不了，其他任务完成
        char RecvData[RECVBUFFERLENGTH];
        memset(RecvData, 0, RECVBUFFERLENGTH);
        recvline(ConnectSocket, RECVBUFFERLENGTH, RecvData);
        cout << "收到的数据为：" << RecvData << endl;
        //memset(SendData, 0, BUFSIZ);
    }

    //先关闭读写通道，再释放套接字占用资源
    shutdown(ConnectSocket, 2);
    closesocket(ConnectSocket);
    cout << "socket已关闭";

    WSACleanup();
    return 1;
}