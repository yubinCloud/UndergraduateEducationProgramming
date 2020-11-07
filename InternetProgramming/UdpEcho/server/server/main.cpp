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
	// 声明IPv4地址族、数据包套接字、UDP协议
	addrinfo hints{};
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_PASSIVE;
	// 解析服务器地址和端口号
	addrinfo* pAddrInfo = nullptr;
	iRet = getaddrinfo(nullptr, "7999", &hints, &pAddrInfo);
	if (iRet != 0) {
		cout << "getaddrinfo failed with error: " << iRet << endl;
		WSACleanup();
		return 1;
	}
	// 为无连接的服务器创建套接字
	auto sevSocket = socket(pAddrInfo->ai_family, pAddrInfo->ai_socktype, pAddrInfo->ai_protocol);
	if (sevSocket == INVALID_SOCKET) {
		cout << "socket failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(pAddrInfo);
		WSACleanup();
		return 1;
	}
	// 为套接字绑定端口号
	iRet = ::bind(sevSocket, pAddrInfo->ai_addr, pAddrInfo->ai_addrlen);
	if (iRet == SOCKET_ERROR) {
		cout << "bind failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(pAddrInfo);
		closesocket(sevSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(pAddrInfo);

	cout << "UDP server starting..." << endl;
	char* revBuf = new char[REV_BUF_SIZE];
	while (true) {
		sockaddr_in clientSocket{};
		int clientSocketLen = sizeof(clientSocket);
		ZeroMemory(&clientSocket, sizeof(sockaddr_in));
		iRet = recvfrom(sevSocket, revBuf, REV_BUF_SIZE - 1, 0, reinterpret_cast<sockaddr*>(&clientSocket), &clientSocketLen);
		if (iRet > 0) {
			revBuf[iRet] = '\0';
			cout << "Bytes received: " << iRet << endl;
			cout << "Data received: " << revBuf << endl;
			auto const sendRet = sendto(sevSocket, revBuf, iRet, 0, reinterpret_cast<sockaddr*>(&clientSocket), clientSocketLen);
			if (sendRet == SOCKET_ERROR) {
				cout << "send failed with error: " << WSAGetLastError() << endl;
				closesocket(sevSocket);
				WSACleanup();
				return 1;
			}
			cout << "Bytes sent: " << sendRet << endl;
		}
		else if (iRet == 0) {
			cout << "connection closing..." << endl;
		}
		else {
			cout << "rev data failed with error: " << WSAGetLastError() << endl;
			closesocket(sevSocket);
			WSACleanup();
			return 1;
		}
	}
	closesocket(sevSocket);
	WSACleanup();
	return 0;
}