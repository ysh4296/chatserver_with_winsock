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
class AddFriends :public tool
{
private:
	string Id;
	SOCKET client;
	string recv_id;
public:
	AddFriends(SOCKET client, string Id, string recv_id);
	~AddFriends();
	int Send_invite(SOCKET client, string Id, string recv_id);
	int Accept_invite(SOCKET client, string Id, string recv_id);
	int Delete_invite(SOCKET client, string Id, string recv_id);
};