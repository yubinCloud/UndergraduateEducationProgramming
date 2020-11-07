#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Ws2tcpip.h>
#include <windows.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using std::cout;
using std::cin;
using std::endl;
using std::string;

constexpr auto REV_BUF_SIZE = 512;


int main(int argc, char* argv[])
{
	int iRet = 0;
	// 初始化套接字
	WSADATA wsaData{};
	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet != 0) {
		cout << "WSAStartup failed with error: " << iRet << endl;
		return 1;
	}
	addrinfo hints{};
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	// 解析服务器地址和端口号
	addrinfo* pAddrInfo = nullptr;
	iRet = getaddrinfo("127.0.0.1", "7999", &hints, &pAddrInfo);
	if (iRet != 0) {
		cout << "getaddrinfo failed with error: " << iRet << endl;
		WSACleanup();
		return 1;
	}
	// 创建数据报套接字
	const auto connSocket = socket(pAddrInfo->ai_family, pAddrInfo->ai_socktype, pAddrInfo->ai_protocol);
	if (connSocket == INVALID_SOCKET) {
		cout << "connSocket create failed with error: " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	// 读取用户输入并发送
	string sendStr;
	char* revBuf = new char[REV_BUF_SIZE];
	while (true) {
		// send
		cout << "Please enter your data: ";
		std::getline(cin, sendStr);
		iRet = sendto(connSocket, sendStr.c_str(), sendStr.size() + 1, 0, pAddrInfo->ai_addr, pAddrInfo->ai_addrlen);
		if (iRet == SOCKET_ERROR) {
			cout << "sendto failed with error: " << WSAGetLastError() << endl;
			closesocket(connSocket);
			WSACleanup();
			return 1;
		}
		cout << "Bytes sent: " << iRet << endl;
		// recv
		iRet = recvfrom(connSocket, revBuf, REV_BUF_SIZE, 0, nullptr, nullptr);
		if (iRet > 0) {
			cout << "Bytes received: " << iRet << endl;
		}
		else if (iRet == 0) {
			cout << "Connection closed." << endl;
		}
		else {
			cout << "recv failed with error: " << WSAGetLastError();
		}
		if (sendStr == "quit")
			break;
	}
	freeaddrinfo(pAddrInfo);
	delete[] revBuf;
	closesocket(connSocket);
	WSACleanup();
	return 0;
}