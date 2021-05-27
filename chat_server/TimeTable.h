#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <algorithm>
#include "Tool.h"
#include "Alarm.h"
#include <stdlib.h>
#include "Messanger.h"
#define MAX_BUFFER_SIZE 4092
using namespace std;
class TimeTable : public tool {
private:
	SOCKET client;
	string id;
public:
	TimeTable(SOCKET client, string id);
	~TimeTable();
	int table(SOCKET client, string id);

};