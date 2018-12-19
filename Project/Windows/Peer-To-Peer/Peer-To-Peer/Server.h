#pragma once
#include <WS2tcpip.h>
#include <vector>
#include "Node.h"

#pragma comment (lib, "ws2_32.lib")

class Server {
private:
	int errorFlag = 0;

	const static int PORT = 54000;
	const static int MESSAGE_BUFFER_SIZE = 1024;
	char messageBuffer[MESSAGE_BUFFER_SIZE];

	std::vector<Node> nodeList;
	
	SOCKET serverSocket;

	bool serverRunning;

	void clearMessageBuffer();
	//void clearClientBuffer();
	void startupLoop();
	int sendMessage(SOCKADDR_IN receiver, std::string msg);

public:
	Server();
	~Server();

	void startListen();
	
	const int getErrorCode() const;
};