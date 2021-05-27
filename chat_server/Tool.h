#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <direct.h>
#include <mutex>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include "Schedule.h"
#define MAX_BUFFER_SIZE 4092
using namespace std;
class tool// recv와 send를 사용하기 쉽게 만들어줌
{
public:
	SOCKET client;
	char buf[MAX_BUFFER_SIZE];
	tool(SOCKET client);
	~tool();
	void splitString(vector<string> &v_str, const string &str, const char ch);
	int Recv(SOCKET client, char buf[]);
	void Send(SOCKET client, string msg);
	void VectorToTxt(const char* fileName, vector<string> &Vector);
	void TxtToVector(const char* fileName, vector<string> &Vector);
	void MapToTxt(const char* fileName, map<string, string> &Map);
	void TxtToMap(const char* fileName, map<string, string> &Map);
	void SocketToTxt(const char* fileName, map<string, SOCKET> &Map);
	void TxtToSocket(const char* fileName, map<string, SOCKET> &Id_Socket);
	void GScheToTxt(const char* fileName,map<string, string>&Map);
	void TxtToGSche(const char* fileName,map<string, string>&Map);
	/*int DailyScheduleToFile(Schedule &Ds, string Id, string date, string day);
	int WeeklyScheduleToFile(Schedule &Ds, string Id, string day);
	int FileToDailyScheduleClass(Schedule &Ds, string Id, string date,string day);
	int FileToWeeklyScheduleClass(Schedule &Ds, string Id, string day);*/
};
static mutex mtx;
static void mux(SOCKET client, string msg) {
	mtx.lock();
	Sleep(10);
	send(client, msg.c_str(), MAX_BUFFER_SIZE, 0);
	mtx.unlock();
}
