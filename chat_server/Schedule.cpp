#include "Schedule.h"
Schedule::Schedule()
{
}
Schedule::~Schedule()
{
}
int Schedule::AddSchedule(string sh,string sm, string fh, string fm,string Schedule) {
	int Starthour = atoi(sh.c_str());
	int Startminute = atoi(sm.c_str());
	int Finalhour = atoi(fh.c_str());
	int Finalminute = atoi(fm.c_str());
	string Dest_Sche = Schedule;
	int hour;
	int minute;
	for (hour = Starthour, minute = Startminute; (hour != Finalhour) || (minute != Finalminute);) {
		if (minute != 59) {
			TimeLine[hour][minute] = 1;
				
			minute++;
		}
		else {
			hour++;
			minute = 0;
		}
	}
	string time = sh + sm + fh + fm;
	Map_Schedule[time] = Dest_Sche;
	//추가 timeline에 추가
	return 0;
}
int Schedule::DeleteSchedule(string Time) {
	char* time = _strdup(Time.c_str());
	char* sh = strtok(time, ",");
	char* sm = strtok(NULL, ",");
	char* fh = strtok(NULL, ",");
	char* fm = strtok(NULL, ",");
	int Starthour = atoi(sh);
	int Startminute = atoi(sm);
	int Finalhour = atoi(fh);
	int Finalminute = atoi(fm);
	if (Map_Schedule.find(Time) == Map_Schedule.end()) {
		cout << "there is no such Schedule";
		return -1;
	}
	else {
		int hour;
		int minute;
		Map_Schedule.erase(Time);
	}
	return 0;
}
map<string, string> Schedule::ReturnSchedule() {
	return Map_Schedule;
}
int* Schedule::AddTimeLine(string Time) {
	char* time = _strdup(Time.c_str());
	char* sh = strtok(time, ",");
	char* sm = strtok(NULL, ",");
	char* fh = strtok(NULL, ",");
	char* fm = strtok(NULL, ",");
	int hour; int minute;
	int Starthour = atoi(sh);
	int Startminute = atoi(sm);
	int Finalhour = atoi(fh);
	int Finalminute = atoi(fm);
	for (hour = Starthour, minute = Startminute; (hour != Finalhour) || (minute != Finalminute);) {
		if (minute != 59) {
			TimeLine[hour][minute] = 1;
			minute++;
		}
		else {
			TimeLine[hour][minute] = 1;
			hour++;
			minute = 0;
		}
	}
	return &TimeLine[0][0];
}
void Schedule::Addmap(string time, string sche)
{
	Map_Schedule[time] = sche;
}
int Schedule::CheckOverlap(char* time) {
	char* sh = strtok(time, ",");
	char* sm = strtok(NULL, ",");
	char* fh = strtok(NULL, ",");
	char* fm = strtok(NULL, ",");
	int hour; int minute;
	int Starthour = atoi(sh);
	int Startminute = atoi(sm);
	int Finalhour = atoi(fh);
	int Finalminute = atoi(fm);
	for (hour = Starthour, minute = Startminute; (hour != Finalhour) || (minute != Finalminute);) {
		if (minute != 59) {
			if (TimeLine[hour][minute] == 1) {
				return -1; //overlap exist
			}
			minute++;
		}
		else {
			hour++;
			minute = 0;
		}
	}
	return 0; //no overlap
}
int Schedule::CheckCurOverlap(char* time, int CStarthour, int CStartminute) {
	char* sh = strtok(time, ",");
	char* sm = strtok(NULL, ",");
	char* fh = strtok(NULL, ",");
	char* fm = strtok(NULL, ",");
	int Starthour = atoi(sh);
	int Startminute = atoi(sm);
	int Finalhour = atoi(fh);
	int Finalminute = atoi(fm);
	int hour; int minute;
	if (CStarthour >= Finalhour&&CStartminute >= Finalminute)
		return 0;
	if ((CStarthour >= Starthour) && (CStartminute >= Startminute))
	{
		Starthour = CStarthour; Startminute = CStartminute;
	}
	for (hour = Starthour, minute = Startminute; (hour != Finalhour) || (minute != Finalminute);) {
		if (minute != 59) {
			if (TimeLine[hour][minute] == 1) {
				return -1; //overlap exist
			}
			minute++;
		}
		else {
			hour++;
			minute = 0;
		}
	}
	return 0; //no overlap
}
int Schedule::Make_Sche(char* time) {
	char* sh = strtok(time, ",");
	char* sm = strtok(NULL, ",");
	char* fh = strtok(NULL, ",");
	char* fm = strtok(NULL, ",");
	int hour; int minute;
	int Starthour = atoi(sh);
	int Startminute = atoi(sm);
	int Finalhour = atoi(fh);
	int Finalminute = atoi(fm);
	for (hour = Starthour, minute = Startminute; (hour != Finalhour) || (minute != Finalminute);) {
		if (minute != 59) {
			if (TimeLine[hour][minute] == 1) {
				return -1; //overlap exist
			}
			minute++;
		}
		else {
			hour++;
			minute = 0;
		}
	}
	return 0; //no overlap
}