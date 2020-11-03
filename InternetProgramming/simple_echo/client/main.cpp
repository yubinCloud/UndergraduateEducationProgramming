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

using std::cout;
using std::endl;
using std::string;

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
int readOneChar(SOCKET socket, char* recvBuf, char* recvStrPtr, unsigned recvBufLen)
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

int readLineHelper(SOCKET socket, char* recvBuf, unsigned recvBufLen) {
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
int readLine(SOCKET socket, char* recvBuf, size_t recvBufLen)
{
    auto readLen = readLineHelper(socket, recvBuf, recvBufLen);
    if (readLen < 0) {
        std::cerr << "readLine error" << std::endl;
    }
    return readLen;
}


int main(int argc, char* argv[])
{
    WSAData wsaData;
    char sendBuf[DEFAULT_BUF_SIZE];  // 发送缓冲区
    char recvBuf[DEFAULT_BUF_SIZE];     // 接收缓冲区
    int recvBufLen = DEFAULT_BUF_SIZE;
    int errcode;  // 用来存放各种函数调用的返回错误码
    // 初始化套接字
    errcode = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (errcode != 0) {
        cout << "WSAStartup failed with error: " << errcode << endl;
    }
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;  // 地址族声明为 ipv4
    hints.ai_socktype = SOCK_STREAM;  // 套接字类型为流式套接字
    hints.ai_protocol = IPPROTO_TCP;  // 采用 TCP 协议

    // 解析服务器地址和端口号
    struct addrinfo* severAddrInfo = nullptr;
    errcode = getaddrinfo(NODE_IP, DEFAULT_PORT, &hints, &severAddrInfo);
    if (errcode != 0) {
        cout << "function <getaddrinfo> failed with error: " << errcode << endl;
        WSACleanup();
        return 1;
    }

    SOCKET connSocket = INVALID_SOCKET;
    // 尝试连接服务器地址，直到成功
    for (struct addrinfo* pServerAddrInfo = severAddrInfo; pServerAddrInfo != NULL; pServerAddrInfo = pServerAddrInfo->ai_next) {
        // 创建套接字
        connSocket = socket(pServerAddrInfo->ai_family, pServerAddrInfo->ai_socktype, pServerAddrInfo->ai_protocol);
        if (connSocket == INVALID_SOCKET) {
            cout << "socket failed with error: " << WSAGetLastError() << endl;
            WSACleanup();
            return 1;
        }
        // 向服务器请求连接
        errcode = connect(connSocket, pServerAddrInfo->ai_addr, pServerAddrInfo->ai_addrlen);
        if (errcode == SOCKET_ERROR) {
            closesocket(connSocket);
            connSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(severAddrInfo);
    if (connSocket == INVALID_SOCKET) {
        cout << "Unable to connect to server." << endl;
        WSACleanup();
        return 1;
    }

    ZeroMemory(sendBuf, DEFAULT_BUF_SIZE);
    ZeroMemory(recvBuf, DEFAULT_BUF_SIZE);

    while (true) {
        // 读取用户的输入
        cout << "Please enter your string: ";
        string sendStr;
        std::getline(std::cin, sendStr);
        if ("quit" == sendStr) {
            break;
        }
        // 发送数据
        strncpy(sendBuf, sendStr.c_str(), DEFAULT_BUF_SIZE);
        sendBuf[DEFAULT_BUF_SIZE - 1] = '\0';
        send(connSocket, sendBuf, strlen(sendBuf), 0);
        // 接收数据
        readLine(connSocket, recvBuf, DEFAULT_BUF_SIZE);
        cout << "接收到数据： " << recvBuf << std::endl;
    }

    // 数据发送结束，调用shutdown()函数声明不再发送数据
    errcode = shutdown(connSocket, SD_SEND);
    if (errcode == SOCKET_ERROR) {
        cout << "shutdown failed with error: " << WSAGetLastError() << endl;
        closesocket(connSocket);
        WSACleanup();
        return 1;
    }
    closesocket(connSocket);
    WSACleanup();
    return 0;
}