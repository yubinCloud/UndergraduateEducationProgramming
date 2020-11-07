#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Ws2tcpip.h>
#include <windows.h>
#include <string>
#include <thread>


#pragma comment (lib, "ws2_32.lib")

using std::cout;
using std::endl;
using std::string;

constexpr auto REV_BUF_SIZE = 512;

void subServerRun(sockaddr_in clientSocket, const string& firstStr);

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
	const auto sevSocket = socket(pAddrInfo->ai_family, pAddrInfo->ai_socktype, pAddrInfo->ai_protocol);
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
	char* mainRevBuf = new char[REV_BUF_SIZE];

	while (true) {
		sockaddr_in clientSocket{};
		int clientSocketLen = sizeof(clientSocket);
		ZeroMemory(&clientSocket, sizeof(sockaddr_in));
		iRet = recvfrom(sevSocket, mainRevBuf, REV_BUF_SIZE - 1, 0, reinterpret_cast<sockaddr*>(&clientSocket), &clientSocketLen);
		if (iRet <= 0)
			continue;
		mainRevBuf[iRet] = '\0';
		string revStr(mainRevBuf);
		std::thread subServerThread(subServerRun, clientSocket, revStr);
		subServerThread.detach();
	}
	delete[] mainRevBuf;
}


void subServerRun(sockaddr_in clientSocketAddr, const string& firstStr)
{
	// create socket
	const auto sevSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (sevSocket == INVALID_SOCKET) {
		cout << "Socket establishes error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
		return;
	}
	// connect
	if (connect(sevSocket, reinterpret_cast<sockaddr*>(&clientSocketAddr), sizeof(clientSocketAddr)) < 0) {
		cout << "connect error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
		return;
	}
	// send the firstStr
	cout << "Receive data: " << firstStr << endl;
	send(sevSocket, firstStr.c_str(), firstStr.size() + 1, 0);
	// rev and send
	char* revBuf = new char[REV_BUF_SIZE];
	while (true) {
		const auto revRet = recv(sevSocket, revBuf, REV_BUF_SIZE - 1, 0);
		if (revRet < 0) {
			cout << "recv data failed with error: " << revRet << endl;
		}
		revBuf[revRet] = '\0';
		cout << "Receive data: " << revBuf << endl;
		if (!strcmp(revBuf, "q")) {
			break;
		}
		send(sevSocket, revBuf, revRet, 0);
	}
	delete[] revBuf;
	shutdown(sevSocket, SD_SEND);
	closesocket(sevSocket);
}