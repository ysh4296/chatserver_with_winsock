#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include "Tool.h"
#include "AddFriends.h"
#include "MakeChat.h"
#include "Schedule.h"
#include <stdlib.h>
#pragma comment(lib,"ws2_32")
using namespace std;
class MessangerSchedule :public tool
{
private:
	SOCKET client;
	string Id;
public:
	MessangerSchedule(SOCKET client, string Id);
	~MessangerSchedule();
	void Schedule_invite(char* msg,SOCKET client,string Id);
	void Accept_schedule(char* msg, SOCKET client, string Id);
	void Cancel_schedule(char* msg, SOCKET client, string Id);
	void Group_Time(char* msg, SOCKET client, string Id);
	void Accept_Index(char* msg, SOCKET client, string Id);
};