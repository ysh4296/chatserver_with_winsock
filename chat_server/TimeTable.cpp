#include "TimeTable.h"
TimeTable::TimeTable(SOCKET client, string id) :tool(client) {

}
TimeTable::~TimeTable() {

}

int TimeTable::table(SOCKET client, string id) {
	while (1) {
		char buf[MAX_BUFFER_SIZE];
		ZeroMemory(buf, MAX_BUFFER_SIZE);
		int byteIn = recv(client, buf, MAX_BUFFER_SIZE, 0);
		string code = buf;
		code = code.substr(0, 3);
		//send class �� recv Ŭ���� �����
		if (byteIn <= 0) {
			break;
		}
		else {
			if (strcmp(code.c_str(), "000") == 0) {//000 yymmdd ���� //string recv client�� ���� �ð�ǥ Ȯ�� ��û �ش� �ð�ǥ�� ������
				map<string, string> Sche;
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* date = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				string file = "c:/server/" + id + "/schedule/daily/" + day + "/" + date + ".txt";
				tool::TxtToMap(file.c_str(), Sche);
				Schedule Daily;
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter) {
						Daily.Addmap((*iter).first, (*iter).second);
					}
					for (iter = Daily.Map_Schedule.begin(); iter != Daily.Map_Schedule.end(); ++iter) {
						string msg;
						msg = "001 " + iter->first + " " + iter->second;
						Send(client, msg);
					}
				}Send(client, "000");
				Sche.clear();
				file = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				tool::TxtToMap(file.c_str(), Sche);
				Schedule Weekly;
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter)
						Weekly.Addmap((*iter).first, (*iter).second);
					for (iter = Weekly.Map_Schedule.begin(); iter != Weekly.Map_Schedule.end(); ++iter) {
						string msg;
						msg = "003 " + iter->first + " " + iter->second;
						Send(client, msg);
					}
				}Send(client, "002");
				file = "c:/server/" + id + "/schedule/group/" + date + ".txt";
				tool::TxtToGSche(file.c_str(), Sche);
				Schedule Group; int G = 0;
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter) {
						char* dupbuf = _strdup(iter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " ");
						char* gid = strtok(dupbuf, ",");
						while (gid != NULL) {
							if (gid == id) {
								Group.Addmap(iter->first, iter->second);
								Group.AddTimeLine(iter->first);
							}
							gid = strtok(NULL, ",");
						}
					}
					for (iter = Group.Map_Schedule.begin(); iter != Group.Map_Schedule.end(); iter++) {
						string msg;
						msg = "011 " + iter->first + " " + iter->second;
						Send(client, msg);
					}
				}
			}
			else if (strcmp(code.c_str(), "001") == 0) {//MessangerIn
				Alarm alarm(client, id);
				alarm.Messanger(client, id);
				Messanger messanger(client, id);
				messanger.in(client, id);
			}
			else if (strcmp(code.c_str(), "002") == 0) {//002 yymmdd 00,00,00,00 ���� ���� recv /client�� daily ���� �߰� ��û �ڽ��� ������ Ȯ���ϰ� �߰� ���� �Ұ� ���θ� ������.
				map<string, string> schedule;
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* date = strtok(NULL, " ");
				char* timeline = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				char* Dest_Sche = strtok(NULL, " ");
				char Str[MAX_BUFFER_SIZE];
				strcpy(Str, "");
				while (Dest_Sche != NULL) {
					strcat(Str, Dest_Sche);
					Dest_Sche = strcat(Str, " ");
					Dest_Sche = strtok(NULL, " ");
				}
				char* duptime;
				duptime = _strdup(timeline);
				string file = "c:/server/" + id + "/schedule/daily/" + day + "/" + date + ".txt";
				tool::TxtToMap(file.c_str(), schedule);
				Schedule Daily;
				int D = 0, W = 0;
				if (schedule.size() != 0) {
					for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
						Daily.Addmap(iter->first, iter->second);
						Daily.AddTimeLine(iter->first);
					}
					//������ ��������, ������
					D = Daily.CheckOverlap(duptime);
					duptime = _strdup(timeline);
					//�ߺ��˻�
					schedule.clear();
				}
				file = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				tool::TxtToMap(file.c_str(), schedule);
				Schedule Weekly;
				if (schedule.size() != 0) {
					for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
						Weekly.Addmap(iter->first, iter->second);
						Weekly.AddTimeLine(iter->first);
					}
					//������ ��������, ������
					W = Weekly.CheckOverlap(duptime);
					duptime = _strdup(timeline);
					schedule.clear();
				}
				file = "c:/server/" + id + "/schedule/group/" + date + ".txt";
				tool::TxtToGSche(file.c_str(), schedule);
				Schedule Group; int G = 0;
				if (schedule.size() != 0) {
					for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
						char* dupbuf = _strdup(iter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " ");
						char* gid = strtok(dupbuf, ",");
						while (gid != NULL) {
							if (gid == id) {
								Group.Addmap(iter->first, iter->second);
								Group.AddTimeLine(iter->first);
							}
							gid = strtok(NULL, ",");
						}
					}
					G = Group.CheckOverlap(duptime);
					schedule.clear();
					duptime = _strdup(timeline);
				}
				//�ߺ��˻�
			//�ߺ��˻�
			//�����ϸ� 004 + �����߰� �Ұ����ϸ� 005
				if ((D + W + G) == 0)//����
				{
					file = "c:/server/" + id + "/schedule/daily/" + day + "/" + date + ".txt";
					string AddT = duptime;
					string AddS = Str;
					Daily.Addmap(AddT, Str);
					tool::MapToTxt(file.c_str(), Daily.Map_Schedule);
					Send(client, "004");
				}
				else
				{
					Send(client, "005");
				}
			}
			else if (strcmp(code.c_str(), "003") == 0) {//003 yymmdd 00000000 ���� // �ش� ��¥�� ���� ����
				map<string, string> Sche;
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* date = strtok(NULL, " ");
				char* time = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				string file = "c:/server/" + id + "/schedule/daily/" + day + "/" + date + ".txt";
				Schedule Daily;
				tool::TxtToMap(file.c_str(), Sche);
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter) {
						Daily.Addmap((*iter).first, (*iter).second);
					}
					Daily.DeleteSchedule(time);
				}
				tool::MapToTxt(file.c_str(), Daily.Map_Schedule);
				//��ū��Ȱ
				//�ش� ���� ����
			}
			else if (strcmp(code.c_str(), "004") == 0) {//004 00000000 ���� // �ش� ������ ���� ����
				map<string, string> Sche;
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* time = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				string file = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				Schedule Weekly;
				tool::TxtToMap(file.c_str(), Sche);
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter) {
						Weekly.Addmap((*iter).first, (*iter).second);
					}
					Weekly.DeleteSchedule(time);
				}
				tool::MapToTxt(file.c_str(), Weekly.Map_Schedule);
				// �ش� ���� ����
			}
			else if (strcmp(code.c_str(), "005") == 0) {//005 yymmdd 00,00,00,00 ���� ���� �ð�ǥ �߰� 
				map<string, string> schedule;
				map<string, string>::iterator iter;
				int error = 0;
				int result = 0;
				string msg;
				strtok(buf, " ");
				char* Cur_Date = strtok(NULL, " ");
				char* Time = strtok(NULL, " ");
				char* Dup_Time = _strdup(Time);
				char* day = strtok(NULL, " ");
				char* Dest_Sche = strtok(NULL, " ");
				char Str[MAX_BUFFER_SIZE];
				strcpy(Str, "");
				while (Dest_Sche != NULL) {
					strcat(Str, Dest_Sche);
					Dest_Sche = strcat(Str, " ");
					Dest_Sche = strtok(NULL, " ");
				}
				Schedule Weekly;
				string Filepath = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				tool::TxtToMap(Filepath.c_str(), schedule);
				if (schedule.size() != 0) {
					for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
						Weekly.Addmap((*iter).first, (*iter).second);
						Weekly.AddTimeLine((*iter).first);
					}
					result = Weekly.CheckOverlap(Dup_Time);
				}
				if (result == -1) {
					string msg = "009";
					cout << "send msg" + msg << endl;
					Send(client, msg);
					error++;
				}
				else {
					char path[255];
					string pathstr = "c:/server/" + id + "/schedule/daily/" + day + "/*.txt";
					strcpy(path, pathstr.c_str());
					WIN32_FIND_DATA FindData;
					HANDLE hFind;
					hFind = FindFirstFile((LPCSTR)path, &FindData);
					if (hFind == INVALID_HANDLE_VALUE)//file�� �ƹ��͵� ������
					{
						cout << "No file in directory!" << endl;//
					}
					else {
						do {
							cout << FindData.cFileName << endl;
							char* File_Date = FindData.cFileName;
							if (strcmp(Cur_Date, File_Date) > 0) {}
							else if (strcmp(Cur_Date, File_Date) < 0) {
								//���� ��¥ ���� ���ϵ�
								Schedule Find_File;
								string File_Date = FindData.cFileName;
								File_Date = File_Date.substr(0, 8);
								string Filepath = "c:/server/" + id + "/schedule/daily/" + day + "/" + FindData.cFileName;
								tool::TxtToMap(Filepath.c_str(), schedule);
								if (schedule.size() != 0) {
									for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
										Find_File.Addmap((*iter).first, (*iter).second);
										Find_File.AddTimeLine((*iter).first);
									}

									Dup_Time = _strdup(Time);
									result = Find_File.CheckOverlap(Dup_Time);
								}
								if (result == -1) {
									msg = "008 " + File_Date;
									Send(client, msg);
									error++;
								}
							}
							else {
								//���糯¥�� ���� �˻��� �����м�
								time_t curr_time;
								struct tm *curr_tm;
								curr_time = time(NULL);
								curr_tm = localtime(&curr_time);
								Schedule Find_File;
								string File_Date = FindData.cFileName;
								File_Date = File_Date.substr(0, 8);
								string Filepath = "c:/server/" + id + "/schedule/daily/" + day + "/" + FindData.cFileName;
								tool::TxtToMap(Filepath.c_str(), schedule);
								if (schedule.size() != 0) {
									for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
										Find_File.Addmap((*iter).first, (*iter).second);
										Find_File.AddTimeLine((*iter).first);
									}
									Dup_Time = _strdup(Time);
									result = Find_File.CheckCurOverlap(Dup_Time, curr_tm->tm_hour, curr_tm->tm_min);
								}
								if (result == -1) {
									msg = "008 " + File_Date;
									Send(client, msg);
									error++;
								}
							}
							schedule.clear();
						} while (FindNextFile(hFind, &FindData));
					}
					pathstr = "c:/server/" + id + "/schedule/group/*.txt";

					strcpy(path, pathstr.c_str());
					hFind = FindFirstFile((LPCSTR)path, &FindData);
					if (hFind == INVALID_HANDLE_VALUE)//file�� �ƹ��͵� ������
					{
						cout << "No file in directory!" << endl;//
					}
					else {
						do {
							cout << FindData.cFileName << endl;
							char* File_Date = FindData.cFileName;
							if (strcmp(Cur_Date, File_Date) > 0) {}
							else if (strcmp(Cur_Date, File_Date) < 0) {
								//���� ��¥ ���� ���ϵ�
								Schedule Find_File;
								string File_Date = FindData.cFileName;
								File_Date = File_Date.substr(0, 8);
								string Filepath = "c:/server/" + id + "/schedule/group/" + FindData.cFileName;
								tool::TxtToGSche(Filepath.c_str(), schedule);
								if (schedule.size() != 0) {
									for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
										char* dupbuf = _strdup(iter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " ");
										char* gid = strtok(dupbuf, ",");
										while (gid != NULL) {
											if (gid == id) {
												Find_File.Addmap(iter->first, iter->second);
												Find_File.AddTimeLine(iter->first);
											}
											gid = strtok(NULL, ",");
										}
									}
									Dup_Time = _strdup(Time);
									result = Find_File.CheckOverlap(Dup_Time);
								}
								if (result == -1) {
									msg = "010 " + File_Date;
									Send(client, msg);
									error++;
								}
							}
							else {
								//���糯¥�� ���� �˻��� �����м�
								time_t curr_time;
								struct tm *curr_tm;
								curr_time = time(NULL);
								curr_tm = localtime(&curr_time);
								Schedule Find_File;
								string File_Date = FindData.cFileName;
								File_Date = File_Date.substr(0, 8);
								string Filepath = "c:/server/" + id + "/schedule/group/" + FindData.cFileName;
								tool::TxtToGSche(Filepath.c_str(), schedule);
								if (schedule.size() != 0) {
									for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
										char* dupbuf = _strdup(iter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " ");
										char* gid = strtok(dupbuf, ",");
										while (gid != NULL) {
											if (gid == id) {
												Find_File.Addmap(iter->first, iter->second);
												Find_File.AddTimeLine(iter->first);
											}
											gid = strtok(NULL, ",");
										}
									}
									Dup_Time = _strdup(Time);
									result = Find_File.CheckCurOverlap(Dup_Time, curr_tm->tm_hour, curr_tm->tm_min);
								}
								if (result == -1) {
									msg = "010 " + File_Date;
									Send(client, msg);
									error++;
								}
							}
							schedule.clear();
						} while (FindNextFile(hFind, &FindData));
					}
					if (error == 0) {
						Send(client, "006");
						Filepath = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
						tool::TxtToMap(Filepath.c_str(), Weekly.Map_Schedule);
						Dup_Time = _strdup(Time);
						Weekly.Addmap(Dup_Time, Str);
						tool::MapToTxt(Filepath.c_str(), Weekly.Map_Schedule);
						schedule.clear();
					}
					else {
						msg = "007";
						Send(client, msg);
					}
					//while �ش� ���� ������ ���� ������ ���� �˻� �� ������{
					//�ߺ��˻��� �ߺ��̸� �Ұ� ��¥;
					//}
					//�����ϸ� 000 + �����߰� �Ұ����ϸ� 001 +  �Ұ� ��¥
				}
			}
		}
	}
	return 0;
}