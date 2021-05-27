#include "DailySchedule.h"
int DailySchedule::AddSchedule(char* Schedule) {
	string Date = Schedule;
	date = Date.substr(4, 10);
	char* ptr = strtok(Schedule, " ");
	ptr = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	string time = ptr;
	int Starthour = atoi(time.substr(0, 2).c_str());
	int Startminute = atoi(time.substr(3, 5).c_str());
	int Finalhour = atoi(time.substr(6, 8).c_str());
	int Finalminute = atoi(time.substr(9, 11).c_str());
	ptr = strtok(NULL, " ");
	string schedule = ptr;
	int Check = 0;

	for (int i = Starthour; i < Finalhour; i++) {
		for (int j = Startminute; j < Finalminute; j++) {
			Check += TimeLine[i][j];
		}
	}
	if (Check != 0) {
		cout << "overlap schedule";;
		return -1;
	}
	else {
		for (int i = Starthour; i < Finalhour; i++) {
			for (int j = Startminute; j < Finalminute; j++) {
				TimeLine[i][j] = 1;
			}
		}
		Map_Schedule[time] = schedule;
		cout << "added schedule";
	}
	return 0;
}
int DailySchedule::DeleteSchedule(char* Schedule) {

	string Date = Schedule;
	date = Date.substr(4, 10);
	char* ptr = strtok(Schedule, " ");
	ptr = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	string time = ptr;
	int Starthour = atoi(time.substr(0, 2).c_str());
	int Startminute = atoi(time.substr(3, 5).c_str());
	int Finalhour = atoi(time.substr(6, 8).c_str());
	int Finalminute = atoi(time.substr(9, 11).c_str());
	ptr = strtok(NULL, " ");
	string schedule = ptr;

	if (Map_Schedule.find(time) == Map_Schedule.end()) {
		cout << "there is no such Schedule";
		return -1;
	}
	else {

		Map_Schedule.erase(time);

		for (int i = Starthour; i < Finalhour; i++) {
			for (int j = Startminute; j < Finalminute; j++) {
				TimeLine[i][j] = 0;
			}
		}
	}
	return 0;
}
map<string, string> DailySchedule::ReturnSchedule() {
		return Map_Schedule;
}
int* DailySchedule::ReturnTimeLine() {
	return &TimeLine[0][0];
}