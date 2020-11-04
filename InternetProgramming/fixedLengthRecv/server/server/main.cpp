#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using std::cout;
using std::endl;
using std::string;

constexpr auto FIXED_READ_LENGTH = 5;


int recvn(const SOCKET& socket, char* recvBuf, int fixedLen);


int main(int argc, char* argv[])
{
	WSADATA wsaData{};
	WSAStartup(MAKEWORD(2, 1), &wsaData);

	// establish socket
	const auto listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET) {
		cout << "Socket establishes error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
	}

	// bind port
	sockaddr_in sevAddr{};
	sevAddr.sin_family = AF_INET;
	sevAddr.sin_port = htons(7999);
	sevAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&sevAddr), sizeof(sevAddr)) < 0) {
		cout << "Bind error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
	}

	// listen
	if (listen(listenSocket, SOMAXCONN) < 0) {
		cout << "Listen error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
	}

	char revBuf[FIXED_READ_LENGTH + 1] = { 0 };
	
	while (true) {
		// accept
		const auto sevSock = accept(listenSocket, nullptr, nullptr);
		if (sevSock == INVALID_SOCKET) {
			cout << "accept error" << endl;
			cout << "Error code: " << WSAGetLastError() << endl;
			return 1;
		}
		cout << "accept a connection." << endl;
		// recv data
		int revRet = 0;
		do {
			revRet = recvn(sevSock, revBuf, FIXED_READ_LENGTH);
			revBuf[revRet] = '\0';
			cout << "Receive data: " << revBuf << endl;
			send(sevSock, revBuf, revRet, 0);
		} while (revRet == FIXED_READ_LENGTH);
		shutdown(sevSock, SD_SEND);
		closesocket(sevSock);
		cout << "close a server socket." << endl;
	}
	shutdown(listenSocket, 2);
	closesocket(listenSocket);
	cout << "close listen socket." << endl;

	WSACleanup();
	return 0;
}


int recvn(const SOCKET& socket, char* recvBuf, const int fixedLen)
{
	int cnt = fixedLen;  // 记录还剩多少个字节尚未接收
	while (cnt > 0) {
		const auto revRet = recv(socket, recvBuf, FIXED_READ_LENGTH, 0);
		if (revRet < 0) {
			cout << "Error occur when receiving data: " << WSAGetLastError() << endl;
			return 1;
		}
		if (revRet == 0) {
			// 对方关闭了连接
			cout << "connection close." << endl;
			return fixedLen - cnt;  // 返回接收的字节数
		}
		recvBuf += revRet;
		// 更新cnt值
		cnt -= revRet;
	}
	return fixedLen;
}