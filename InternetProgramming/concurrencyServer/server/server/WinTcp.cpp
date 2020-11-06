#include <iostream>
#include <string>

#include "WinTcp.h"

using std::cout;
using std::endl;
using std::string;

constexpr auto REV_BUF_SIZE = 512;
constexpr auto SEND_BUF_SIZE = 512;

char* recvVarLen(const SOCKET& socket, char* recvBuf);
int recvn(const SOCKET& socket, char* recvBuf, int fixedLen);


WinTcp::WinTcp() :
	sock(INVALID_SOCKET),
	port(0),
	ip(),
	revBuf(nullptr),
	sendBuf(nullptr)
{
	this->revBuf = new char[REV_BUF_SIZE] { 0 };
	this->sendBuf = new char[SEND_BUF_SIZE] { 0 };
#ifdef WIN32
	static bool firstTcp = true;
	if (firstTcp)
	{
		firstTcp = false;
		WSADATA ws;
		WSAStartup(MAKEWORD(2, 2), &ws);
	}
#endif
}

WinTcp::~WinTcp() = default;


SOCKET WinTcp::createSocket()
{
	sock = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		cout << "create socket failed!" << endl;
	return sock;
}

bool WinTcp::bindPort(const int port)
{
	if (sock <= 0)
		createSocket();
	sockaddr_in socketAddr{};
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(port);
	socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (::bind(sock, reinterpret_cast<sockaddr*>(&socketAddr), sizeof(socketAddr)) != 0) {
		cout << "bind port " << port << " failed." << endl;
		return false;
	}
	printf("bind port %d success.\n", port);
	return true;
}

WinTcp WinTcp::accept() const
{
	WinTcp tcp;
	sockaddr_in clientAddr{};
	int addrLen = sizeof(clientAddr);
	const auto client = ::accept(sock, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
	if (client == INVALID_SOCKET) {
		cout << "accept error" << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
		return tcp;
	}
	cout << "accept client: " << client << endl;
	tcp.ip = inet_ntoa(clientAddr.sin_addr);
	tcp.port = ntohs(clientAddr.sin_port);
	tcp.sock = client;
	cout << "client ip is: " << tcp.ip << ", port is: " << tcp.port << endl;
	return tcp;
}

bool WinTcp::listen() const
{
	auto const listenRet = ::listen(sock, SOMAXCONN);
	if (listenRet < 0) {
		cout << "Listen error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

void WinTcp::close() const
{
	if (sock == INVALID_SOCKET)
		return;
	shutdown(sock, SD_SEND);
	closesocket(sock);
	cout << "close socket: " << sock << endl;
	delete[] revBuf;
	delete[] sendBuf;
}

std::string WinTcp::rev() const
{
	char* pRevData = recvVarLen(sock, revBuf);
	if (pRevData == nullptr) {
		return "";
	}
	
	const string revStr(pRevData);
	if (pRevData != revBuf) {
		delete[] pRevData;
	}
	
	cout << "Receive data: " << revStr << endl;
	return revStr;
}

int WinTcp::send(char* sendBuf, const size_t sendLen) const
{
	// 构造发送数据
	size_t const totalLen = sizeof(size_t) + sendLen;  // 需要发送的数据总长度
	char* tSendBuf = new char[totalLen];

	auto const pDataLen = reinterpret_cast<size_t*>(tSendBuf);
	*pDataLen = sendLen;
	memcpy(tSendBuf + sizeof(size_t), sendBuf, sendLen);
	// send
	::send(sock, tSendBuf, totalLen, 0);
	delete[] tSendBuf;
	return sendLen;
}

int WinTcp::send(std::string& sendStr) const
{
	char* sendBuf = new char[sendStr.size()];
	memcpy(sendBuf, sendStr.c_str(), sendStr.size());
	const auto sendRet =  send(sendBuf, sendStr.size());
	delete[] sendBuf;
	return sendRet;
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