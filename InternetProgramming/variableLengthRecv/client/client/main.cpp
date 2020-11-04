#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <string>

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
	WSADATA wsaData{ };
	WSAStartup(MAKEWORD(2, 1), &wsaData);

	// establish socket
	const auto connSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (connSocket == INVALID_SOCKET) {
		cout << "Socket establishes error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
		return 1;
	}

	// connect
	sockaddr_in clientAddress{};
	clientAddress.sin_family = AF_INET;
	clientAddress.sin_port = htons(7999);
	clientAddress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(connSocket, reinterpret_cast<sockaddr*>(&clientAddress), sizeof(clientAddress)) < 0) {
		cout << "connect error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
		return 1;
	}

	string sendStr;  // ��Ҫ���͵��ַ���
	char revBuf[REV_BUF_SIZE] = { 0 };  // ���ջ�����
	char sendBuf[SEND_BUF_SIZE] = { 0 };  // Ԥ���ķ��ͻ�����
	while (sendStr != "quit") {
		cout << "Please enter your data: ";
		std::getline(std::cin, sendStr);
		char* tSendBuf = sendBuf;  // ��ʵ�ķ��ͻ�����
		size_t const totalLen = sizeof(size_t) + sendStr.size();  // ��Ҫ���͵������ܳ���
		if (totalLen > SEND_BUF_SIZE) {
			tSendBuf = new char[totalLen];
		}
		// ���췢������
		auto const pDataLen = reinterpret_cast<size_t*>(tSendBuf);
		*pDataLen = sendStr.size();
		strncpy_s(tSendBuf + sizeof(size_t), sendStr.size(), sendStr.c_str(), sendStr.size());
		// send
		send(connSocket, tSendBuf, totalLen, 0);
		if (totalLen > SEND_BUF_SIZE) {
			delete[] tSendBuf;
		}
		// recv
		char* pRevData = recvVarLen(connSocket, revBuf);
		if (pRevData == nullptr) {
			return 1;
		}
		cout << "Receive data: " << pRevData << endl;
		if (pRevData != revBuf) {
			delete[] pRevData;
		}
	}

	shutdown(connSocket, 2);
	closesocket(connSocket);
	cout << "socket close." << endl;

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
	int cnt = fixedLen;  // ��¼��ʣ���ٸ��ֽ���δ����
	while (cnt > 0) {
		const auto revRet = recv(socket, recvBuf, fixedLen, 0);
		if (revRet < 0) {
			cout << "Error occur when receiving data: " << WSAGetLastError() << endl;
			return -1;
		}
		if (revRet == 0) {
			// �Է��ر�������
			cout << "connection close." << endl;
			return fixedLen - cnt;  // ���ؽ��յ��ֽ���
		}
		recvBuf += revRet;
		// ����cntֵ
		cnt -= revRet;
	}
	return fixedLen;
}