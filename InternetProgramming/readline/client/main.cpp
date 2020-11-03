#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

using namespace std;

constexpr auto DEFAULT_BUF_SIZE = 512;      // 默认缓冲区大小
constexpr auto DEFAULT_PORT = "27015";      // 默认端口号
constexpr auto NODE_IP = "127.0.0.1";       // 本机节点的ip

static int readCnt = 0;  // 指示当前需要读取的字符串的数量
static char* readPtr = 0;  // 指向当前应该读取的字符串中的字符


/**
 * 在应用程序缓冲区中读取一个字符到存储本行的字符串中，当应用程序缓冲区不足时从内核缓冲区中读取一次
 * @param socket 接收套接字
 * @param recvBuf 应用程序的缓冲区
 * @param recvStrPtr 指向存储本行数据的字符串中下一个要存储字符的指针
 * @return
 */
int readOneChar(SOCKET socket, char* recvBuf, char* recvStrPtr, int recvBufLen)
{
    if (readCnt <= 0) {
        readAgain:
        if ((readCnt = recv(socket, recvBuf, recvBufLen, 0)) < 0) {
            if (errno == EINTR)
                goto readAgain;
            return -1;
        }
        else if (readCnt == 0) {
            return 0;
        }
        readPtr = recvBuf;
    }
    --readCnt;
    *recvStrPtr = *readPtr;
    ++readPtr;
    return 1;
}

int readLineHelper(SOCKET socket, char* recvBuf, int recvBufLen) {
    char* pRecvBuf = recvBuf;  // 指向缓冲区中下一个接收字符的空间
    int readLen = 0;  // 当前所读取的字符的长度
    for (readLen = 0; readLen < recvBufLen; ++readLen) {
        auto readOneCharResult = readOneChar(socket, recvBuf, pRecvBuf, recvBufLen);
        if (readOneCharResult == 1) {  // 读取一个字符成功
            ++pRecvBuf;
            if (*pRecvBuf == '\n')
                break;  // 读取结束，已经完成一行的读取
        }
        else if (readOneCharResult == 0) {
            *pRecvBuf = '\0';
            return readLen - 1;  // EOF, n - 1 bytes were read.
        }
        else
            return -1;
    }

    *pRecvBuf = '\0';
    return readLen;
}

/**
 * 读取一行数据到缓冲接收区中
 * @param socket 接收套接字
 * @param recvBuf 接收缓冲区
 * @param maxLen 接收缓冲区的最大长度
 * @return 读取的字符数
 */
int readLine(SOCKET socket, char* recvBuf, int recvBufLen)
{
    auto readLen = readLineHelper(socket, recvBuf, recvBufLen);
    if (readLen < 0) {
        std::cerr << "readLine error" << std::endl;
    }
    return readLen;
}


int main(){
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);


    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);


    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    char line[50];
    char recv_line[50];
    while(true){
        //scanf("%s", line);
        memset(line, 0, 49);
        gets(line);
        line[strlen(line)] = '\n';
        if (line[0] == 'q')
            break;

        send(sock, line, strlen(line), 0);  // 发送一行数据
        readLine(sock, recv_line, 50);
        printf("%s", recv_line);
    }

    /*
    //接收服务器传回的数据
    char szBuffer[MAXBYTE] = {0};
    recv(sock, szBuffer, MAXBYTE, NULL);


    //输出接收到的数据
    printf("Message form server: %s\n", szBuffer);
    */

    //关闭套接字
    closesocket(sock);


    //终止使用 DLL
    WSACleanup();
    system("pause");
    return 0;
}