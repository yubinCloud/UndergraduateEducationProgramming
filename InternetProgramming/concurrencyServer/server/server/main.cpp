#include <iostream>
#include <string>
#include <thread>

#include "WinTcp.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;


void serverRun(const WinTcp& tcpServer);


int main(int argv, char* argc[])
{
	constexpr auto PORT_NUM = 7999;
	WinTcp listenTcp;
	listenTcp.createSocket();
	listenTcp.bindPort(PORT_NUM);
	listenTcp.listen();

	
	while (true) {
		WinTcp client = listenTcp.accept();
		auto td = thread(serverRun, client);
		td.detach();
	}
	listenTcp.close();
	return 0;
}

void serverRun(const WinTcp& tcpServer)
{
	while (true) {
		string revStr = tcpServer.rev();
		tcpServer.send(revStr);
		if (revStr == "quit" || revStr.empty())
			break;
	}
	tcpServer.close();
	
}