#include "Login.h"



Login::Login(SOCKET client) :tool(client)
{
}


Login::~Login()
{
}
int Login::logging(SOCKET client) {
	char Id[MAX_BUFFER_SIZE];
	string id = Id;
	char Password[MAX_BUFFER_SIZE];
	int Id_Bytein;
	int Password_Bytein;
	map<string, string> user_Info;
	map<string, string>::iterator iter;
	map<string, SOCKET> IdSocketInfo;
	int CheckId = 0;
	int CheckPassword = 0;
	string str;
	tool::TxtToMap("c:/server/Id_Ps_map.txt", user_Info);

	str = "enter your Id and Password";

	send(client, str.c_str(), MAX_BUFFER_SIZE, 0);
	//do {
		Id_Bytein = tool::Recv(client, Id); //아이디 받기

		str = "enter your Id and Password";

		send(client, str.c_str(), MAX_BUFFER_SIZE, 0);

		Password_Bytein = tool::Recv(client, Password);//비번 받기

		CheckId = 0;
		CheckPassword = 0;
		
		for (iter = user_Info.begin(); iter != user_Info.end(); (++iter)) {
			if (iter->first == Id) {
				CheckId = 1;//Id가 등록되어 있음
				if (iter->second == Password) {
					CheckPassword = 1;
				}
			}
		}
		
		if (CheckId == 1 && CheckPassword == 1) {
			str = "Successfully Login";
			send(client, str.c_str(), MAX_BUFFER_SIZE, 0);

			tool::TxtToSocket("C:/server/Id_Socket_map.txt", IdSocketInfo);
			IdSocketInfo.insert(pair<string, SOCKET>(Id, client));
			tool::SocketToTxt("C:/server/Id_Socket_map.txt", IdSocketInfo);
		}
		//Id가 등록되어 있지 않음
		else if (CheckId != 1 || CheckPassword != 1) {
			str = "Ether your id or password is wrong";
			send(client, str.c_str(), MAX_BUFFER_SIZE, 0);
		}



	//} while (CheckId == 1 && CheckPassword == 1);



	return 0;
}
