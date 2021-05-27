#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <windows.h>
#include "Send.h"
using namespace std;
class chatLog :public Send
{
public:
	SOCKET client;
	chatLog(SOCKET client);
	~chatLog();
	void Read(SOCKET client);
	void state() {
		cout << "ChatLog state" << endl;
	};
};

