#include <iostream>
#include <ctime>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <WinSock2.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

using std::cout;
using std::endl;
using std::string;


constexpr auto REV_BUF_SIZE = 512;
constexpr auto SEND_BUF_SIZE = 512;

int read_cnt = 0;//表示每一次读读取后，还有多少个字符未被判断
char* read_ptr = NULL;

int my_read(SOCKET fd, char* ptr, char* vptr)
{

	if (read_cnt <= 0) {
	again:
		if ((read_cnt = recv(fd, vptr, REV_BUF_SIZE, 0)) < 0) {
			if (errno == EINTR)
				goto again;
			return(-1);
		}
		else if (read_cnt == 0)
			return(0);
		read_ptr = vptr;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return(1);
}




int revLine(const SOCKET& fd, char* vptr)
{
	int rc = 0, i = 1;
	char* ptr = vptr;
	char c;

	for (i = 1; 1 < REV_BUF_SIZE; i++)
	{
		if ((rc = my_read(fd, &c, vptr)) == 1)
		{
			*ptr++ = c;
			if (c == '\n')
				break;//newline is stored
		}
		else if (rc == 0)
		{
			//表示读到最后一个字符也不是换行符
			*ptr = 0;
			return i - 1;
		}
		else return -1;
	}
	*ptr = 0;
	return i;

}


int main(int argc, char** argv)
{
	char revBuf[REV_BUF_SIZE] = {0};
	WSAData wsaData{};
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
	char sendBuf[SEND_BUF_SIZE] = { 0 };
	while (strcmp(sendBuf, "quit\n")) {
		cout << "Please enter your data: " << endl;
		fgets(sendBuf, SEND_BUF_SIZE, stdin);
		send(connSocket, sendBuf, strlen(sendBuf), 0);
		memset(revBuf, 0, REV_BUF_SIZE);
		revLine(connSocket, revBuf);
		cout << "Receive data: " << revBuf << endl;
	}

	shutdown(connSocket, 2);
	closesocket(connSocket);
	cout << "socket close." << endl;

	WSACleanup();
	return 0;
}
