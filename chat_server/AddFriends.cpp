#include "AddFriends.h"
AddFriends::AddFriends(SOCKET client, string Id, string recv_id) :tool(client)
{
}
AddFriends::~AddFriends()
{
}
int AddFriends::Send_invite(SOCKET client, string Id, string recv_id) {//id 는 초대자 recv id 는 초대 수신인
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info; 
	SOCKET destsock;
	string filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "invite/" + Id + ".txt";//초대장은 friendsrecv_idinvite에 저장
	ofstream Write(filepath, ios::app);
	if (Write.is_open()) {
		cout << "writing file" << endl;
		Write << Id << endl;
	}
	Write.close();
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	iter = socket_info.find(recv_id);
	if (iter == socket_info.end()) {}//상대가 접속중일때 알람을 보냄
	else {
		destsock = iter->second;
		cout << "목표 소켓 접속중" << endl;
		string Smsg = "007 " + Id;
		Send(destsock, Smsg);
	}
	return 0;
}
int AddFriends::Accept_invite(SOCKET client, string Id, string recv_id) {//id는 초대 수신인recv id 는 초대자
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	SOCKET destsock;
	string filepath = "c:/server/" + Id + "/friends" + Id + "invite/" + recv_id + ".txt";
	remove(filepath.c_str());//받았으니 초대 메세지 삭제
	filepath = "c:/server/" + recv_id + "/friends" + recv_id + "/" + Id + ".txt";//초대를 받으면 바로 친구 목록으로 보냄
	ofstream DWrite(filepath, ios::app);
	if (DWrite.is_open()) {
		cout << "friends write on : " + recv_id << endl;
		DWrite << Id << endl;
	}
	DWrite.close();
	filepath = "c:/server/" + Id + "/" + "friends" + Id + "/" + recv_id + ".txt";//초대를 받으면 바로 친구목록으로 보냄
	ofstream IWrite(filepath, ios::app);
	if (IWrite.is_open()) {
		cout << "friends write on : " + Id << endl;
		IWrite << recv_id << endl;
	}
	IWrite.close();
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	iter = socket_info.find(recv_id);
	if (iter == socket_info.end()) {
		filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "alarm/" + Id + ".txt";//초대를 받으면 받았다는 알림을 server에 저장함^^
		ofstream AWrite(filepath, ios::app);
		if (AWrite.is_open()) {
			cout << "friends write on :" + recv_id + "alarm" << endl;
			AWrite << Id << endl;
		}
		AWrite.close();
	}
	else {
		destsock = iter->second;
		cout << "목표 소켓 접속중" << endl;
		string Smsg = "008 " + Id;
		Send(destsock, Smsg);//만약 상대가 접속중이라면 바로 친구를 추가해줌//친구 파일로 바로 전송
	}
	socket_info.clear();
	string Cmsg = "008 " + recv_id;
	Send(client, Cmsg);//client도 친구를 추가함
	return 1;
}
int AddFriends::Delete_invite(SOCKET client, string Id, string recv_id)
{
	string filepath = "c:/server/" + Id + "/friends" + Id + "invite/" + recv_id + ".txt";
	remove(filepath.c_str());
	return 0;

}
