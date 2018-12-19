#include "Node.h"

int Node::previousNodeID = 0;

Node::Node(std::string address, int port)
	: nodeID(++previousNodeID) {

	sockAddr.sin_port = htons(port);
	sockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, address.c_str(), &sockAddr.sin_addr);
}

Node::Node(SOCKADDR_IN sockAddr)
	: sockAddr(sockAddr), nodeID(++previousNodeID) {}

int Node::sendMsg(SOCKET& socket, std::string& msg) {
	return sendto(socket, msg.c_str(), msg.length(), 0, (sockaddr*)&sockAddr, sizeof(sockAddr));
}