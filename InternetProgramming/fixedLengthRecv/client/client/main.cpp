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

	// �����û����뷢������
	string sendStr;
	while (sendStr != "quit") {
		cout << "Please enter your data: " << endl;
		std::getline(std::cin, sendStr);

		if (sendStr.size() < FIXED_READ_LENGTH) {  // ���sendStr���Ȳ�������Ҫ�ں�����ӿո�
			sendStr += string(FIXED_READ_LENGTH - sendStr.size(), ' ');
		}
		else if (sendStr.size() > FIXED_READ_LENGTH) {  // ������������ȡǰ�沿��
			sendStr = sendStr.substr(0, FIXED_READ_LENGTH);
		}
		// ���Ͷ�������
		send(connSocket, sendStr.c_str(), FIXED_READ_LENGTH, 0);
		// ���ն�������
		
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
	int cnt = fixedLen;  // ��¼��ʣ���ٸ��ֽ���δ����
	while (cnt > 0) {
		const auto revRet = recv(socket, recvBuf, FIXED_READ_LENGTH, 0);
		if (revRet < 0) {
			cout << "Error occur when receiving data: " << WSAGetLastError() << endl;
			return 1;
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
