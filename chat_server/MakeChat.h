#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <algorithm>
#include "Tool.h"
#include <stdlib.h>
class MakeChat :public tool
{
private:
	string Id;
	SOCKET client;
public:
	MakeChat(SOCKET client, string Id);
	~MakeChat();
	int Make(SOCKET client, string Id, char* msg);
};