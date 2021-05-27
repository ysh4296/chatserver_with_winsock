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
	string pathstr = "c:/server/" + Id + "/" + file + ".txt";// message sender의 chatfile에서 채팅방 참가자의 목록을 받아옴
	fpath = "c:/server/" + Id + "/schedule/group/" + file;
	_mkdir(fpath.c_str());
	strcpy(path, pathstr.c_str());
	ofstream Write(path, ios::app);
	if (Write.is_open()) {
		cout << "writing file" << endl;
		Write << Id + "님이" + file + "을 초대하였습니다." << endl;//자신의 id folder에 message 저장
	}
	Write.close();
	char filename[MAX_BUFFER_SIZE];
	strcpy(filename, file.c_str());
	ptr = strtok(filename, ",");
	SOCKET destsock;
	while (ptr != NULL) {//ptr은 채팅방에 있는 다른 user_id이다.
		if (ptr != Id) {
			string str = ptr;// another_user_id
							 //string index_path = "c:/server/Socket_Id_Map.txt";
			pathstr = "c:/server/" + str + "/chat" + str + "alarm/" + file + ".txt";//filename은 같다 user/alarm/filename의 경로
			strcpy(path, pathstr.c_str());
			ofstream DWrite(path, ios::app);
			if (DWrite.is_open()) {
				cout << "writing file" << endl;
				DWrite << Id + "님이" + file + "을 초대하였습니다." << endl;//참여자 id/alarm/file에 message 저장
			}//파일이 없을수는 없다.
			else if (DWrite.is_open() == false) {
				return -1;
			}
			DWrite.close();
			tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
			iter = socket_info.find(ptr);
			if (iter == socket_info.end()) {}
			else {
				destsock = iter->second;
				cout << "목표 소켓 접속중" << endl;
				string Smsg = "006 " + file + " " + Id + "님이" + file + "을 초대하였습니다.";
				Send(destsock, Smsg);
			}
			socket_info.clear();
			//if (ptrfind = 1) {//현재 해당 user가 접속중
			//	//send alarm message
			//}
		}
		ptr = strtok(NULL, ",");
	}
	string Cmsg = "006 " + file + " " + Id + "님이" + file + "을 초대하였습니다.";
	Send(client, Cmsg);
	return 1;
}