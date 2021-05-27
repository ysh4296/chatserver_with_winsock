#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <string>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
class Schedule {
private:
	int TimeLine[24][60];
	string date;
public:
	map<string, string> Map_Schedule;
	Schedule();
	~Schedule();
	int AddSchedule(string sh,string sm, string fh, string fm, string Schedule);
	int DeleteSchedule(string time);
	map<string, string> ReturnSchedule();
	int* AddTimeLine(string Time); 
	void Addmap(string time, string sche);
	int CheckOverlap(char* time); 
	int CheckCurOverlap(char* time, int Starthour, int Startminute); 
	int Make_Sche(char* time);

};