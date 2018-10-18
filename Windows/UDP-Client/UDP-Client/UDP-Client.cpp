// UDP-Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	// Startup WinSock
	std::cout << "Starting WinSock..." << std::endl;
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int serverStartResponse = WSAStartup(version, &data);
	if (serverStartResponse != 0) {
		std::cout << "Failed to start WinSock. Error Code: " << serverStartResponse << std::endl;
		return -1;
	}
	
	const int port = 54000;
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	//Socket
	SOCKET outSocket = socket(AF_INET, SOCK_DGRAM, 0);

	// Send Message
	std::string message(argv[1]);
	int sendMessageResponse = sendto(outSocket, message.c_str(), message.size() + 1, 0, (sockaddr*) &server, sizeof(server));
	if (sendMessageResponse == SOCKET_ERROR) {
		std::cout << "Failed to send message. Error Code: " << WSAGetLastError() << std::endl;

	}


	closesocket(outSocket);


	// Shutdown WinSock
	WSACleanup();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
