#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

#include "Server.h"
void main() {
	bool gameActive = true;
	char pressed;
	
	Server* s = new Server();
	s->start();
	


	/*
	
	
	while (gameActive) {
		std::cout << "Hello World" << std::endl;




		if (GetAsyncKeyState(VK_ESCAPE)) {
			gameActive = false;
		}
	}
	*/
}