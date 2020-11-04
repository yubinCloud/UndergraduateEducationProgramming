#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <string>

#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")

using std::cout;
using std::endl;
using std::string;

constexpr auto REV_BUF_SIZE = 512;
constexpr auto SEND_BUF_SIZE = 512;


char* recvVarLen(const SOCKET& socket, char* recvBuf);
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

	char revBuf[REV_BUF_SIZE] = { 0 };
	char sendBuf[SEND_BUF_SIZE] = { 0 };  // 预备的发送缓冲区

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
		char* pRevData = nullptr;
		do {
			pRevData = recvVarLen(sevSock, revBuf);
			if (pRevData == nullptr) {
				break;
			}
			cout << "Receive data: " << pRevData << endl;
			// 构造发送数据
			char* tSendBuf = sendBuf;  // 真实的发送缓冲区
			auto const dataLen = strlen(pRevData);
			size_t const totalLen = sizeof(size_t) + dataLen;  // 需要发送的数据总长度
			if (totalLen > SEND_BUF_SIZE) {
				tSendBuf = new char[totalLen];
			}
			
			auto const pDataLen = reinterpret_cast<size_t*>(tSendBuf);
			*pDataLen = dataLen;
			strncpy(tSendBuf + sizeof(size_t), pRevData, dataLen);
			// send
			send(sevSock, tSendBuf, totalLen, 0);
			if (totalLen > SEND_BUF_SIZE) {
				delete[] tSendBuf;
			}
			if (pRevData != revBuf) {
				delete[] pRevData;
			}
		} while (true);

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


char* recvVarLen(const SOCKET& socket, char* recvBuf)
{
	size_t* pDataLen = nullptr;
	int revRet = recvn(socket, recvBuf, sizeof(size_t));
	if (revRet <= 0)
		return nullptr;
	pDataLen = reinterpret_cast<size_t*>(recvBuf);
	size_t const dataLen = *pDataLen;
	bool hasNewBuf = false;
	if (dataLen >= REV_BUF_SIZE) {
		recvBuf = new char[dataLen + 1];
		hasNewBuf = true;
	}

	revRet = recvn(socket, recvBuf, dataLen);
	if (revRet < dataLen) {
		if (hasNewBuf)
			delete[] recvBuf;
		return nullptr;
	}
	recvBuf[dataLen] = '\0';
	return recvBuf;
}


int recvn(const SOCKET& socket, char* recvBuf, const int fixedLen)
{
	int cnt = fixedLen;  // 记录还剩多少个字节尚未接收
	while (cnt > 0) {
		const auto revRet = recv(socket, recvBuf, fixedLen, 0);
		if (revRet < 0) {
			cout << "Error occur when receiving data: " << WSAGetLastError() << endl;
			return -1;
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