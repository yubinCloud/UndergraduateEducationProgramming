#include <iostream>
#include <ctime>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")


using std::cout;
using std::endl;

constexpr auto SERVER_BUF_SIZE = 512;

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
	sockaddr_in serverAddress{};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(7999);
	serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
		cout << "Bind error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
	}

	// listen
	if (listen(listenSocket, SOMAXCONN) < 0) {
		cout << "Listen error." << endl;
		cout << "Error code: " << WSAGetLastError() << endl;
	}

	// accept
	while (true) {
		const auto serverSocket = accept(listenSocket, nullptr, nullptr);
		if (serverSocket == INVALID_SOCKET) {
			cout << "accept error" << endl;
			cout << "Error code: " << WSAGetLastError() << endl;
			return 1;
		}
		cout << "accept a connection." << endl;

		// receive data
		char* serverBuf = new char[SERVER_BUF_SIZE];
		memset(serverBuf, 0, SERVER_BUF_SIZE);

			int revResult = 0;
			do {
				revResult = recv(serverSocket, serverBuf, SERVER_BUF_SIZE, 0);
				if (revResult > 0) {
					// echo
					const auto sendResult = send(serverSocket, serverBuf, strlen(serverBuf), 0);
					if (sendResult == SOCKET_ERROR) {
						cout << "send error" << endl;
						cout << "Error code: " << WSAGetLastError() << endl;
					} else {
						cout << "Receive data: " << serverBuf << endl;
					}
					memset(serverBuf, 0, SERVER_BUF_SIZE);
				}
			} while (revResult > 0);

			cout << "close a server socket." << endl;
		shutdown(serverSocket, SD_SEND);
		delete[] serverBuf;
		closesocket(serverSocket);
	}
	shutdown(listenSocket, 2);
	closesocket(listenSocket);
	cout << "close connect." << endl;

	WSACleanup();
	return 0;
}