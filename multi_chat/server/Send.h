#pragma once
#include <WinSock2.h>
#include <string>
#include <iostream>
using namespace std;
class Send
{
public:
	SOCKET client;
	Send(SOCKET client);
	~Send();
	void Run(SOCKET client, string msg);
	virtual void state();
};

