#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <WinSock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using std::cout;
using std::endl;
using std::string;

constexpr auto FIXED_READ_LENGTH = 10;


int recvn(const SOCKET& socket, char* recvBuf, int fixedLen);


int main(int argc, char* argv[])
{
	char revBuf[FIXED_READ_LENGTH + 1] = { 0 };
	WSADATA wsaData{};
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

	// 请求用户输入发送数据
	string sendStr;
	while (sendStr != "quit") {
		cout << "Please enter your data: " << endl;
		std::getline(std::cin, sendStr);

		if (sendStr.size() < FIXED_READ_LENGTH) {  // 如果sendStr长度不够，需要在后面添加空格
			sendStr += string(FIXED_READ_LENGTH - sendStr.size(), ' ');
		}
		else if (sendStr.size() > FIXED_READ_LENGTH) {  // 如果过长，则截取前面部分
			sendStr = sendStr.substr(0, FIXED_READ_LENGTH);
		}
		// 发送定长数据
		send(connSocket, sendStr.c_str(), FIXED_READ_LENGTH, 0);
		// 接收定长数据
		
		cout << "Receive data: " << revBuf << endl;
	}

	shutdown(connSocket, 2);
	closesocket(connSocket);
	cout << "socket close." << endl;

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
