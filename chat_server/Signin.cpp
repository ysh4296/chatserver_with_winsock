#include "Signin.h"

Signin::Signin(SOCKET client) :tool(client)
{
}


Signin::~Signin()
{
}

int Signin::in(SOCKET client)
{
	char id[MAX_BUFFER_SIZE];
	char password[MAX_BUFFER_SIZE];
	char str[MAX_BUFFER_SIZE];
	int Id_Bytein;
	int Password_Bytein;
	//id 중복검사
	int overlap = 0;
	vector<string> V_id;
	string file_string;
	map<string, string> user_Info;
	do {
		Id_Bytein = tool::Recv(client, id);
		if (strcmp(id, "SigninClose") == 0) {
			return -1;
		}
		else if (Id_Bytein <= 0) {
			return -1;
		}

		//in_index 파일 불러오기(txt)

		mutex mtx;
		mtx.lock();
		tool::TxtToVector("c:/server/id_index.txt", V_id);
		mtx.unlock();
		if (find(V_id.begin(), V_id.end(), id) == V_id.end()) {
			//id가 없을때
			overlap = 1;
			/*Id_Bytein = tool::Recv(client, id);
			if (Id_Bytein <= 0) {
			return -1;
			}
			*/
			//vector에 정보 추가
			V_id.clear();
			Password_Bytein = tool::Recv(client, password);
			mtx.lock();
			tool::TxtToVector("c:/server/id_index.txt", V_id);
			if (find(V_id.begin(), V_id.end(), id) == V_id.end()) {
				V_id.push_back(id);
				tool::VectorToTxt("c:/server/id_index.txt", V_id);
				strcpy_s(str, sizeof(str), "Successfully finished signin");
				send(client, str, MAX_BUFFER_SIZE, 0);
			}
			else{
				strcpy_s(str, sizeof(str), "overlap\nRe-enter your id\n");
				send(client, str, MAX_BUFFER_SIZE, 0);
			}
			mtx.unlock();
			//txt파일 저장
		}
		else {
			strcpy_s(str, sizeof(str), "overlap\nRe-enter your id\n");
			send(client, str, MAX_BUFFER_SIZE, 0);
		}
		//id 중복 메세지 send
	} while (overlap == 0);

	string file = id;
	string path = "c:/server/" + file;
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/chat" + file + "alarm";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/friends" + file + "alarm";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/friends" + file + "invite";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/friends" + file;
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/daily";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/daily/mon";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/daily/tue";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/daily/wed";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/daily/thr";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/daily/fri";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/daily/sat";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/daily/sun";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/weekly";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/schedule/group";
	_mkdir(path.c_str());
	//txt에서 map으로
	tool::TxtToMap("c:/server/Id_Ps_map.txt", user_Info);
	user_Info.insert(pair<string, string>(id, password));

	tool::MapToTxt("c:/server/Id_Ps_map.txt", user_Info);
	return 0;

}