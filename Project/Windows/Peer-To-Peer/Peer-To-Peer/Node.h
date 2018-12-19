#pragma once
#include <Ws2tcpip.h>
#include <string>

class Node {
private:
	static int previousNodeID;
	const int nodeID;

	SOCKADDR_IN sockAddr;

public:
	Node(std::string address, int port);
	Node(SOCKADDR_IN sockAddr);

	int sendMsg(SOCKET& socket, std::string& msg);
};