#include "Messanger.h"
Messanger::Messanger(SOCKET client, string Id) :tool(client)
{
}
Messanger::~Messanger()
{
}
int Messanger::in(SOCKET client, string Id) {
	char path[255];
	char msg[MAX_BUFFER_SIZE];
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	cout << "�޽��� ���� id:" + Id << endl;
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	socket_info.insert(pair<string, SOCKET>(Id, client));
	tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
	socket_info.clear();
	while (1) {
		ZeroMemory(msg, MAX_BUFFER_SIZE);
		int Bytein = Recv(client, msg);//�޼��� �Է¹��� ���⼭ �޽����� ���ᵵ �Է¹޴´�.
		string code = msg;
		code = code.substr(0, 3);
		if (strcmp(code.c_str(), "000") == 0) {// MessangerClose �Է¹���
			tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
			cout << "id:" + Id + " is now logout" << endl;
			iter = socket_info.find(Id);
			if (iter != socket_info.end()) {
				socket_info.erase(iter);
			}
			tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
			return 0;
		}
		else if (strcmp(code.c_str(), "001") == 0) {
			char* recv_id = strtok(msg, " ");
			recv_id = strtok(NULL, " ");
			AddFriends Add(client, Id, recv_id);
			Add.Delete_invite(client, Id, recv_id);
		}
		else if (strcmp(code.c_str(), "002") == 0) {//SendInvite �Է¹���
			cout << "Sending invite message" << endl;
			char* recv_id = strtok(msg, " ");
			recv_id = strtok(NULL, " ");
			vector<string> V_id;
			tool::TxtToVector("c:/server/id_index.txt", V_id);
			if (find(V_id.begin(), V_id.end(), recv_id) == V_id.end()) {
				Send(client, "001");
			}
			else {
				Send(client, "002");
				AddFriends Add(client, Id, recv_id);
				Add.Send_invite(client, Id, recv_id);
			}
		}
		else if (strcmp(code.c_str(), "003") == 0) {//AcceptInvite �Է¹���
			char* recv_id = strtok(msg, " ");
			recv_id = strtok(NULL, " ");
			AddFriends Add(client, Id, recv_id);
			Add.Accept_invite(client, Id, recv_id);
		}
		else if (strcmp(code.c_str(), "004") == 0) {
			cout << "Making Chating room" << endl;
			MakeChat Make(client, Id);
			Make.Make(client, Id, msg);
		}
		else if (strcmp(code.c_str(), "005") == 0) {//�޼����� �Է¹޾Ҵ� //filename msg ���·� ����
			char* ptr = strtok(msg, " ");
			ptr = strtok(NULL, " ");
			string file = (strcpy, ptr);//file = filename
			ptr = strtok(NULL, " ");
			char Str[MAX_BUFFER_SIZE];
			string tokmsg;
			strcpy(Str, "");
			while (ptr != NULL) {
				strcat(Str, ptr);
				tokmsg = strcat(Str, " ");
				ptr = strtok(NULL, " ");
			}
			string message = tokmsg;
			string pathstr = "c:/server/" + Id + "/" + file + ".txt";// message sender�� chatfile���� ä�ù� �������� ����� �޾ƿ�
			strcpy(path, pathstr.c_str());
			ofstream Write(path, ios::app);
			if (Write.is_open()) {
				cout << "writing file" << endl;
				Write << Id + ": " + message << endl;//�ڽ��� id folder�� message ����
			}
			Write.close();
			char filename[MAX_BUFFER_SIZE];
			strcpy(filename, file.c_str());
			ptr = strtok(filename, ",");//index ���� ���� ����
			SOCKET destsock;
			while (ptr != NULL) {//ptr�� ä�ù濡 �ִ� �ٸ� user_id�̴�.
				if (ptr != Id) {
					string str = ptr;// another_user_id
					//string index_path = "c:/server/Socket_Id_Map.txt";
					pathstr = "c:/server/" + str + "/chat" + str + "alarm/" + file + ".txt";//filename�� ���� user/alarm/filename�� ���
					strcpy(path, pathstr.c_str());
					ofstream DWrite(path, ios::app);
					if (DWrite.is_open()) {
						cout << "writing file" << endl;
						DWrite << Id + ": " + message << endl;//������ id/alarm/file�� message ����
					}//������ �������� ����.
					else if (DWrite.is_open() == false) {
						return -1;
					}
					DWrite.close();
					tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
					iter = socket_info.find(ptr);
					if (iter == socket_info.end()) {}
					else {
						destsock = iter->second;
						cout << "��ǥ ���� ������" << endl;// ��ǥ ������ ������ �̹Ƿ� �� ��뿡�� msg�� send�Ͽ� alarm�� ����Ŵ code:006
						string Clientmsg = "006 " + file + " " + Id + ": " + tokmsg;
						Send(destsock, Clientmsg);
					}
					socket_info.clear();
					//if (ptrfind = 1) {//���� �ش� user�� ������
					//   //send alarm message
					//}+
				}
				ptr = strtok(NULL, ",");
			}
		}
		else if (strcmp(code.c_str(), "006") == 0) {
			strtok(msg, " ");
			string filename = strtok(NULL, " ");
			string chatfilepath = "c:/server/" + Id + "/" + filename + ".txt";
			string alarmfilepath = "c:/server/" + Id + "/chat" + Id + "alarm/" + filename + ".txt";
			ofstream Write(chatfilepath, ios::app);
			ifstream Read(alarmfilepath);
			if (Write.is_open() && Read.is_open()) {
				string message;
				getline(Read, message);
				while (!Read.eof()) {
					Write << message << endl;
					getline(Read, message);
				}
				Write.close();
				Read.close();
			}
			remove(alarmfilepath.c_str());
		}
		else if (strcmp(code.c_str(), "007") == 0) {
		cout << "Send Schedule invite to Chat" << endl;
		MessangerSchedule MS(client, Id);
		MS.Schedule_invite(msg,client,Id);
		}
		else if (strcmp(code.c_str(), "008") == 0) {
		cout << " Accept invite" << endl;
		MessangerSchedule Ms(client, Id);
		Ms.Accept_schedule(msg,client,Id);
		}
		else if (strcmp(code.c_str(), "009") == 0) {
		cout << "Cancle Schedule" << endl;
		MessangerSchedule Ms(client, Id);
		Ms.Cancel_schedule(msg,client, Id);
		}
		else if (strcmp(code.c_str(), "010") == 0) {
		cout << "Cancle Schedule" << endl;
		MessangerSchedule Ms(client, Id);
		Ms.Group_Time(msg, client, Id);
		}
		else if (strcmp(code.c_str(), "011") == 0) {
		cout << "Cancle Schedule" << endl;
		MessangerSchedule Ms(client, Id);
		Ms.Accept_Index(msg, client, Id);
		}
		else if (Bytein <= 0) {
			tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
			iter = socket_info.find(Id);
			if (iter != socket_info.end()) {
				socket_info.erase(iter);
			}
			cout << "id:" + Id + " is now logout" << endl;
			tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
			return -1;
		}
	}
}