#include "AddFriends.h"
AddFriends::AddFriends(SOCKET client, string Id, string recv_id) :tool(client)
{
}
AddFriends::~AddFriends()
{
}
int AddFriends::Send_invite(SOCKET client, string Id, string recv_id) {//id �� �ʴ��� recv id �� �ʴ� ������
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info; 
	SOCKET destsock;
	string filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "invite/" + Id + ".txt";//�ʴ����� friendsrecv_idinvite�� ����
	ofstream Write(filepath, ios::app);
	if (Write.is_open()) {
		cout << "writing file" << endl;
		Write << Id << endl;
	}
	Write.close();
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	iter = socket_info.find(recv_id);
	if (iter == socket_info.end()) {}//��밡 �������϶� �˶��� ����
	else {
		destsock = iter->second;
		cout << "��ǥ ���� ������" << endl;
		string Smsg = "007 " + Id;
		Send(destsock, Smsg);
	}
	return 0;
}
int AddFriends::Accept_invite(SOCKET client, string Id, string recv_id) {//id�� �ʴ� ������recv id �� �ʴ���
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	SOCKET destsock;
	string filepath = "c:/server/" + Id + "/friends" + Id + "invite/" + recv_id + ".txt";
	remove(filepath.c_str());//�޾����� �ʴ� �޼��� ����
	filepath = "c:/server/" + recv_id + "/friends" + recv_id + "/" + Id + ".txt";//�ʴ븦 ������ �ٷ� ģ�� ������� ����
	ofstream DWrite(filepath, ios::app);
	if (DWrite.is_open()) {
		cout << "friends write on : " + recv_id << endl;
		DWrite << Id << endl;
	}
	DWrite.close();
	filepath = "c:/server/" + Id + "/" + "friends" + Id + "/" + recv_id + ".txt";//�ʴ븦 ������ �ٷ� ģ��������� ����
	ofstream IWrite(filepath, ios::app);
	if (IWrite.is_open()) {
		cout << "friends write on : " + Id << endl;
		IWrite << recv_id << endl;
	}
	IWrite.close();
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	iter = socket_info.find(recv_id);
	if (iter == socket_info.end()) {
		filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "alarm/" + Id + ".txt";//�ʴ븦 ������ �޾Ҵٴ� �˸��� server�� ������^^
		ofstream AWrite(filepath, ios::app);
		if (AWrite.is_open()) {
			cout << "friends write on :" + recv_id + "alarm" << endl;
			AWrite << Id << endl;
		}
		AWrite.close();
	}
	else {
		destsock = iter->second;
		cout << "��ǥ ���� ������" << endl;
		string Smsg = "008 " + Id;
		Send(destsock, Smsg);//���� ��밡 �������̶�� �ٷ� ģ���� �߰�����//ģ�� ���Ϸ� �ٷ� ����
	}
	socket_info.clear();
	string Cmsg = "008 " + recv_id;
	Send(client, Cmsg);//client�� ģ���� �߰���
	return 1;
}
int AddFriends::Delete_invite(SOCKET client, string Id, string recv_id)
{
	string filepath = "c:/server/" + Id + "/friends" + Id + "invite/" + recv_id + ".txt";
	remove(filepath.c_str());
	return 0;

}
