#include "MakeChat.h"

MakeChat::MakeChat(SOCKET client, string Id) : tool(client)
{
}
MakeChat::~MakeChat()
{
}
int MakeChat::Make(SOCKET client, string Id, char* msg) {
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info; 
	string fpath;
	char path[MAX_BUFFER_SIZE];
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string file = (strcpy, ptr);//file = filename
	string pathstr = "c:/server/" + Id + "/" + file + ".txt";// message sender�� chatfile���� ä�ù� �������� ����� �޾ƿ�
	fpath = "c:/server/" + Id + "/schedule/group/" + file;
	_mkdir(fpath.c_str());
	strcpy(path, pathstr.c_str());
	ofstream Write(path, ios::app);
	if (Write.is_open()) {
		cout << "writing file" << endl;
		Write << Id + "����" + file + "�� �ʴ��Ͽ����ϴ�." << endl;//�ڽ��� id folder�� message ����
	}
	Write.close();
	char filename[MAX_BUFFER_SIZE];
	strcpy(filename, file.c_str());
	ptr = strtok(filename, ",");
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
				DWrite << Id + "����" + file + "�� �ʴ��Ͽ����ϴ�." << endl;//������ id/alarm/file�� message ����
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
				cout << "��ǥ ���� ������" << endl;
				string Smsg = "006 " + file + " " + Id + "����" + file + "�� �ʴ��Ͽ����ϴ�.";
				Send(destsock, Smsg);
			}
			socket_info.clear();
			//if (ptrfind = 1) {//���� �ش� user�� ������
			//	//send alarm message
			//}
		}
		ptr = strtok(NULL, ",");
	}
	string Cmsg = "006 " + file + " " + Id + "����" + file + "�� �ʴ��Ͽ����ϴ�.";
	Send(client, Cmsg);
	return 1;
}