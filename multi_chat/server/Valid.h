#pragma once
#include <WinSock2.h>
#include <string>
#include "login.h"
#include "signin.h"
#include "Send.h"
#define MAX_BUFFER_SIZE 40910
using namespace std;
class Valid :public Send
{
public:
	SOCKET client;
	Valid(SOCKET client);
	~Valid();

	//void Send(int clientSocket, std::string msg);

	void in(SOCKET client);
	void state() {
		cout << "Valid state" << endl;
	};
};