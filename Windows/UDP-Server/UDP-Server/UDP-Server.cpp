// UDP-Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

int main() {
	// Startup WinSock
	std::cout << "Starting WinSock..." << std::endl;
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int serverStartResponse = WSAStartup(version, &data);
	if (serverStartResponse != 0) {
		std::cout << "Failed to start WinSock. Error Code: " << serverStartResponse << std::endl;
		return -1;
	}

    // Bind Socket to IP Address and Port
	std::cout << "Binding Socket to IP Address and Port..." << std::endl;
	const int port = 54000;
	SOCKET inSocket = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(port); // Host to Network: Convert from little to big endian 

	int socketBindResponse = bind(inSocket, (sockaddr*)&serverHint, sizeof(serverHint));
	if (socketBindResponse == SOCKET_ERROR) {
		std::cout << "Failed to bind socket. Error Code: " << WSAGetLastError() << std::endl;
		return -1;
	}
	std::cout << "Bound socket " << inSocket << " to port " << port << "..." << std::endl;

	//Client Info & Message buffer
	sockaddr_in client;
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);
	// Message Buffer
	const int bufferLength = 1024;
	char messageBuffer[bufferLength];

	bool serverRunning = true;

	// Enter a Loop
	std::cout << "Starting Server..." << std::endl;
	while (serverRunning) {
		ZeroMemory(messageBuffer, bufferLength);

		// Wait for message
		int bytesIn = recvfrom(inSocket, messageBuffer, bufferLength, 0, (sockaddr*) &client, &clientLength);
		if (bytesIn == SOCKET_ERROR) {
			std::cout << "Error Receiving Message from Client " << WSAGetLastError() << std::endl;
			continue;
		}

		// Display Message and Client Info
		const int clientIPBufferLength = 256;
		char clientIP[clientIPBufferLength];

		ZeroMemory(clientIP, clientIPBufferLength);

		inet_ntop(AF_INET, &client.sin_addr, clientIP, clientIPBufferLength);

		std::cout << "Msg frm " << clientIP << ": " << messageBuffer << std::endl;

		if (GetAsyncKeyState(VK_ESCAPE)) {
			serverRunning = false;
		}
	}

	// Close socket
	closesocket(inSocket);

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
