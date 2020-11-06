#pragma once

#include <string>
#include <WinSock2.h>

#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")


class WinTcp
{
public:
	explicit WinTcp();
	virtual ~WinTcp();
	
	SOCKET createSocket();
	bool bindPort(int port);
	WinTcp accept() const;
	bool listen() const;
	void close() const;
	std::string rev() const;
	int send(char* sendBuf, size_t sendLen) const;
	int send(std::string& sendStr) const;
private:
	SOCKET sock;
	int port;
	std::string ip;
	char* revBuf;
	char* sendBuf;
};

