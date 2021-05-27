#include "MessangerSchedule.h"
MessangerSchedule::MessangerSchedule(SOCKET client, string Id) :tool(client)
{
}
MessangerSchedule::~MessangerSchedule()
{
}
void MessangerSchedule::Schedule_invite(char* msg, SOCKET client, string Id) {//007 filename yy,mm,dd 00,00,00,00 요일 sche
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string Chat_file = (strcpy, ptr);//file = filename
	string date = strtok(NULL, " ");
	char* timeline = strtok(NULL, " ");
	string day = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	char Str[MAX_BUFFER_SIZE];
	string Sche;
	strcpy(Str, "");
	while (ptr != NULL) {
		strcat(Str, ptr);
		Sche = strcat(Str, " ");
		ptr = strtok(NULL, " ");
	}
	string message = Sche;
	string file = "c:/server/" + Id + "/schedule/daily/" + day + "/" + date + ".txt";
	tool::TxtToMap(file.c_str(), schedule);
	Schedule Daily; char* duptime;
	int D = 0, W = 0 ;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			Daily.Addmap(siter->first, siter->second);
			Daily.AddTimeLine(siter->first);
		}
		duptime = _strdup(timeline);
		//파일이 열렸으면, 있으면
		D = Daily.CheckOverlap(duptime);
		//중복검사
		schedule.clear();
	}
	file = "c:/server/" + Id + "/schedule/weekly/" + day + ".txt";
	tool::TxtToMap(file.c_str(), schedule);
	Schedule Weekly;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			Weekly.Addmap(siter->first, siter->second);
			Weekly.AddTimeLine(siter->first);
		}
		duptime = _strdup(timeline);
		//파일이 열렸으면, 있으면
		W = Weekly.CheckOverlap(duptime);
		schedule.clear();
	}
	//group 검색
	file = "c:/server/" + Id + "/schedule/group/" + date + ".txt";
	tool::TxtToGSche(file.c_str(), schedule);
	Schedule Group; int G = 0;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			char* dupbuf = _strdup(siter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " "); 
			char* gid = strtok(dupbuf, ",");
			while (gid !=NULL) {
				if (gid == Id) {
					Group.Addmap(siter->first, siter->second);
					Group.AddTimeLine(siter->first);
				}
				gid = strtok(NULL, ",");
			}
		}
		duptime = _strdup(timeline);
		G = Group.CheckOverlap(duptime);
		schedule.clear();
	}

	//중복검사
//중복검사
//가능하면 004 + 일정추가 불가능하면 005
	if (D + W + G == 0)//성공
	{
			// ***님이 ***에 여러분을 초대했습니다.
			char filename[MAX_BUFFER_SIZE];
			strcpy( filename,Chat_file.c_str());
			set<char*> sid;
			set<char*>::iterator iditer;
			duptime = _strdup(timeline);
			string invite_msg = "____" + Id + " 님이 " + message + "에 여러분을 초대했습니다.____\n" + "( " +date+ " | " + duptime + " )";
			ptr = strtok(filename,",");
			while (ptr != NULL) {
				sid.insert(ptr);
				ptr = strtok(NULL, ",");
			}
			for(iditer = sid.begin();iditer!=sid.end();iditer++){
				string str = (*iditer);
				string pathstr = "c:/server/" + str + "/chat" + str + "alarm/" + Chat_file + ".txt";
				ofstream DWrite(pathstr, ios::app);
				if (DWrite.is_open()) {
					cout << "writing file" << endl;
					DWrite << invite_msg << endl;
				}DWrite.close();

				string File_Path = "c:/server/" + str + "/schedule/group/" + date + ".txt";
				tool::TxtToGSche(file.c_str(), schedule);
				Schedule AddGroup;
				if (schedule.size() != 0) {
					for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
						AddGroup.Addmap(siter->first, siter->second);
					}
				}
				duptime = _strdup(timeline);
				AddGroup.Addmap(timeline, Chat_file + "|" + Sche + "|" + Id);//timeline|File|Sche|Id_list
				tool::GScheToTxt(File_Path.c_str(), AddGroup.Map_Schedule);
				schedule.clear();
				tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
				iter = socket_info.find(str);
				if (iter == socket_info.end()) {}
				else {
					SOCKET destsock = iter->second;
					cout << "목표 소켓 접속중" << endl;
					string cmsg = "006 " + Chat_file + " " + invite_msg;
					Sleep(30);
					Send(destsock,cmsg);
				}
				socket_info.clear();
			}
			Sleep(30);
			Send(client, "003");//일정 안겹침 성공
	}
	else
	{
		Sleep(30);
		Send(client, "004");//일정 겹칩 실패
	}
}
void MessangerSchedule::Accept_schedule(char* msg, SOCKET client, string Id) {//008 filename yy,mm,dd 00,00,00,00 요일 sche
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string Chat_file = (strcpy, ptr);//file = filename
	string date = strtok(NULL, " ");
	char* timeline = strtok(NULL, " ");
	string day = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	char Str[MAX_BUFFER_SIZE];
	string Sche;
	strcpy(Str, "");
	while (ptr != NULL) {
		strcat(Str, ptr);
		Sche = strcat(Str, " ");
		ptr = strtok(NULL, " ");
	}
	string message = Sche;
	string file = "c:/server/" + Id + "/schedule/daily/" + day + "/" + date + ".txt";
	tool::TxtToMap(file.c_str(), schedule);
	Schedule Daily; char* duptime;
	int D = 0, W = 0;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			Daily.Addmap(siter->first, siter->second);
			Daily.AddTimeLine(siter->first);
		}
		duptime = _strdup(timeline);
		//파일이 열렸으면, 있으면
		D = Daily.CheckOverlap(duptime);
		//중복검사
		schedule.clear();
	}
	file = "c:/server/" + Id + "/schedule/weekly/" + day + ".txt";
	tool::TxtToMap(file.c_str(), schedule);
	Schedule Weekly;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			Weekly.Addmap(siter->first, siter->second);
			Weekly.AddTimeLine(siter->first);
		}
		duptime = _strdup(timeline);
		//파일이 열렸으면, 있으면
		W = Weekly.CheckOverlap(duptime);
		schedule.clear();
	}
	//group 검색
	file = "c:/server/" + Id + "/schedule/group/" + date + ".txt";
	tool::TxtToGSche(file.c_str(), schedule);
	Schedule Group; int G = 0;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			char* dupbuf = _strdup(siter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " ");
			char* gid = strtok(dupbuf, ",");
			while (gid != NULL) {
				if (gid == Id) {
					Group.Addmap(siter->first, siter->second);
					Group.AddTimeLine(siter->first);
				}
				gid = strtok(NULL, ",");
			}
		}
		duptime = _strdup(timeline);
		G = Group.CheckOverlap(duptime);
		schedule.clear();
	}
//중복검사
//중복검사
//가능하면 004 + 일정추가 불가능하면 005
	if (D + W + G == 0)//성공
	{
		// ***님이 ***에 여러분을 초대했습니다.
		char* filename = _strdup(Chat_file.c_str());
		set<char*> sid;
		set<char*>::iterator iditer;
		ptr = strtok(filename, ",");
		while (ptr != NULL) {
			sid.insert(ptr);
			ptr = strtok(NULL, ",");
		}
		for (iditer = sid.begin(); iditer != sid.end(); iditer++) {
			string str = (*iditer);
			string File_Path = "c:/server/" + str + "/schedule/group/" + date + ".txt";
			tool::TxtToGSche(File_Path.c_str(), schedule);
			Schedule AddGroup; 
			if (schedule.size() != 0) {
				for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
					duptime = _strdup(timeline);
					char* dupbuf = _strdup(siter->second.c_str());
					char* cfile = strtok(dupbuf, "|"); 
					dupbuf = strtok(NULL, "|");
					char* alid = strtok(NULL, "|");
					if ((strcmp(siter->first.c_str(), timeline)==0)&&(strcmp(cfile,Chat_file.c_str())==0)&&(strcmp(dupbuf,Str) == 0)){
						char* Party = NULL;
						Party = _strdup(siter->second.c_str());
						if (alid == NULL) {
							strcat(Party, "");
							strcat(Party, Id.c_str());
						}
						else {
							string list = "," + Id;
							strcat(Party, list.c_str());
						}
						AddGroup.Addmap(siter->first, Party);
					}
					else {
						AddGroup.Addmap(siter->first, siter->second);
					}
				}
				schedule.clear();
			}
			tool::GScheToTxt(File_Path.c_str(), AddGroup.Map_Schedule);
		}
		Send(client, "003");//일정 안겹침 성공
	}
	else
	{
		Send(client, "004");//일정 겹침 실패
	}
}
void MessangerSchedule::Cancel_schedule(char* msg, SOCKET client, string Id) { //009 file yy,mm,dd 00,00,00,00 wod sche
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	char* duptime;
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string Chat_file = (strcpy, ptr);//file = filename
	string date = strtok(NULL, " ");
	char* timeline = strtok(NULL, " ");
	string day = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	char Str[MAX_BUFFER_SIZE];
	string Sche;
	strcpy(Str, "");
	while (ptr != NULL) {
		strcat(Str, ptr);
		Sche = strcat(Str, " ");
		ptr = strtok(NULL, " ");
	}
	string message = Sche; 
	char filename[MAX_BUFFER_SIZE];
	strcpy(filename, Chat_file.c_str());
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	set<char*> sid;
	set<char*>::iterator iditer;
	ptr = strtok(filename, ",");
	while (ptr != NULL) {
		sid.insert(ptr);
		ptr = strtok(NULL, ",");
	}
	for (iditer = sid.begin(); iditer != sid.end(); iditer++) {
		string str = (*iditer);
		string File_Path = "c:/server/" + str + "/schedule/group/" + date + ".txt";
		tool::TxtToGSche(File_Path.c_str(), schedule);
		Schedule AddGroup;
		if (schedule.size() != 0) {
			for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
				duptime = _strdup(timeline);
				char* dupbuf = _strdup(siter->second.c_str());
				char* cfile = strtok(dupbuf, "|");
				dupbuf = strtok(NULL, "|");
				char* alid = strtok(NULL, "|");
				if ((strcmp(siter->first.c_str(), timeline) == 0) && (strcmp(cfile, Chat_file.c_str()) == 0) && (strcmp(dupbuf, Str) == 0)) {
					char* on = strtok(alid, ",");
					char* id_list =_strdup("");
					while (on != NULL) {
						if (on != Id) {
							strcat(id_list, on);
							strcat(id_list, ",");
						}
						on = strtok(NULL, ",");
					}
					string l = id_list;
					int length = l.size();
					l = l.substr(0,length-1);
					string second = Chat_file + "|" + Str + "|" + l;
					AddGroup.Addmap(siter->first, second);
				}
				else {
					AddGroup.Addmap(siter->first, siter->second);
				}
			}
			schedule.clear();
		}
		tool::GScheToTxt(File_Path.c_str(), AddGroup.Map_Schedule);
	}
}
void MessangerSchedule::Group_Time(char* msg, SOCKET client, string Id) {//010 filename yy,mm,dd wod
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string Chat_file = (strcpy, ptr);//file = filename
	string date = strtok(NULL, " ");
	char* timeline = strtok(NULL, " ");
	string day = strtok(NULL, " ");
	Schedule Daily; char* duptime;
	set<char*> sid;
	set<char*>::iterator iditer;
	char filename[MAX_BUFFER_SIZE];
	strcpy(filename, Chat_file.c_str());
	ptr = strtok(filename, ",");
	while (ptr != NULL) {
		sid.insert(ptr);
		ptr = strtok(NULL, ",");
	}
	for (iditer = sid.begin(); iditer != sid.end(); iditer++) {
		string file = "c:/server/" + Id + "/schedule/daily/" + day + "/" + date + ".txt";
		tool::TxtToMap(file.c_str(), schedule);
		if (schedule.size() != 0) {
			for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
				Daily.Addmap(siter->first, siter->second);
				Daily.AddTimeLine(siter->first);
			}
		}
		file = "c:/server/" + Id + "/schedule/weekly/" + day + ".txt";
		tool::TxtToMap(file.c_str(), schedule);
		if (schedule.size() != 0) {
			for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
				Daily.Addmap(siter->first, siter->second);
				Daily.AddTimeLine(siter->first);
			}
		}
		//group 검색
		file = "c:/server/" + Id + "/schedule/group/" + date + ".txt";
		tool::TxtToGSche(file.c_str(), schedule);
		if (schedule.size() != 0) {
			for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
				char* dupbuf = _strdup(siter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " ");
				char* gid = strtok(dupbuf, ",");
				while (gid != NULL) {
					if (gid == Id) {
						Daily.Addmap(siter->first, siter->second);
						Daily.AddTimeLine(siter->first);
					}
					gid = strtok(NULL, ",");
				}
			}
		}
	}

}
void MessangerSchedule::Accept_Index(char* msg, SOCKET client, string Id) {//011 filename yy,mm,dd 00,00,00,00 wod sche
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	char* duptime;
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string Chat_file = (strcpy, ptr);//file = filename
	string date = strtok(NULL, " ");
	char* timeline = strtok(NULL, " ");
	string day = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	char Str[MAX_BUFFER_SIZE];
	string Sche;
	strcpy(Str, "");
	while (ptr != NULL) {
		strcat(Str, ptr);
		Sche = strcat(Str, " ");
		ptr = strtok(NULL, " ");
	}
	string File_Path = "c:/server/" + Id + "/schedule/group/" + date + ".txt";
	tool::TxtToGSche(File_Path.c_str(), schedule);
		if (schedule.size() != 0) {
				for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
					duptime = _strdup(timeline);
					char* dupbuf = _strdup(siter->second.c_str());
					char* cfile = strtok(dupbuf, "|");
					dupbuf = strtok(NULL, "|");
					char* alid = strtok(NULL, "|");
			if ((strcmp(siter->first.c_str(), timeline) == 0) && (strcmp(cfile, Chat_file.c_str()) == 0) && (strcmp(dupbuf, Str) == 0)) {
				Send(client, alid);
			}
		}
	}
}