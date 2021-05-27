#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <map>
#include <algorithm>
#include "Tool.h"
#include "AddFriends.h"
#include "MakeChat.h"
#include "MessangerSchedule.h"
#include <stdlib.h>
#pragma comment(lib,"ws2_32")
using namespace std;
class Messanger :public tool
{
private:
	SOCKET client;
	string Id;
public:
	Messanger(SOCKET client, string Id);
	~Messanger();
	int in(SOCKET client, string id);
};