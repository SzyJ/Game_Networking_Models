#pragma once
#include "Client.h"
#include <vector>

class P2P_Controller {
private:
	std::vector<Client> clientList;
	const float TICKRATE = 0.1f;

public:
	P2P_Controller();
	~P2P_Controller();

	void addClient(Client newClient);

	void onMessageReceive();

	std::vector<Client> getClientList();
};