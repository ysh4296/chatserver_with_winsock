#include "Tool.h"


tool::tool(SOCKET client) {

}


tool::~tool() {

}
void tool::splitString(vector<string> &v_str, const string &str, const char ch) {
	string sub;
	string::size_type pos = 0;
	string::size_type old_pos = 0;
	bool flag = true;

	while (flag) {
		pos = str.find_first_of(ch, pos);
		if (pos == string::npos) {

			flag = false;
			pos = str.size();
		}
		sub = str.substr(old_pos, pos - old_pos);
		v_str.push_back(sub);
		old_pos = ++pos;
	}
}
void tool::Send(SOCKET client, string msg) {
	Sleep(30);
	send(client, msg.c_str(), MAX_BUFFER_SIZE, 0);
}

int tool::Recv(SOCKET client, char buf[]) {

	ZeroMemory(buf, MAX_BUFFER_SIZE);
	int Bytein = recv(client, buf, MAX_BUFFER_SIZE, 0);//error handle
	if (Bytein <= 0) {
		return -1;
	}
	else {
		return 1;
	}
}
void tool::VectorToTxt(const char* fileName, vector<string> &Vector) {
	mutex mtx;
	mtx.lock();
	ofstream wFile(fileName);
	ostream_iterator<string> wFile_iterator(wFile, "\n");
	copy(Vector.begin(), Vector.end(), wFile_iterator);
	wFile.close();
	mtx.unlock();
}
void tool::TxtToVector(const char* fileName, vector<string> &Vector) {
	mutex mtx;
	mtx.lock();
	string file_string;
	ifstream rFile(fileName);
	while (getline(rFile, file_string)) {
		if (file_string.size() > 0)
			Vector.push_back(file_string);
	}
	rFile.close();
	mtx.unlock();
}
void tool::MapToTxt(const char* fileName, map<string, string> &Map) {
	mutex mtx;
	mtx.lock();
	ofstream wFile(fileName);
	for (map<string, string>::const_iterator iterator = Map.begin(); iterator != Map.end(); ++iterator) {
		wFile << iterator->first << "|" << iterator->second;  
		wFile << "\n";
	}
	wFile.close();
	mtx.unlock();
}
void tool::TxtToMap(const char* fileName, map<string, string> &Map) {
	mutex mtx;
	mtx.lock();
	ifstream rFile(fileName);
	string file_string;
	string key;
	vector<string> v_str;
	while (getline(rFile, file_string)) {
		splitString(v_str, file_string, '|');
		for (vector<string>::iterator iterator = v_str.begin(); iterator != v_str.end(); (++iterator)) {

			Map[*(--iterator)] = *(++iterator);
			++iterator;
		}
	}
	rFile.close();
	mtx.unlock();
}
void tool::SocketToTxt(const char* fileName, map<string, SOCKET> &Map) {
	mutex mtx;
	mtx.lock();
	ofstream wFile(fileName);
	for (map<string, SOCKET>::const_iterator iterator = Map.begin(); iterator != Map.end(); ++iterator) {
		wFile << iterator->first << "|" << iterator->second;
		wFile << "\n";
	}
	wFile.close();
	mtx.unlock();
}
void tool::TxtToSocket(const char* fileName, map<string, SOCKET> &Id_Socket) {
	mutex mtx;
	mtx.lock(); 
	ifstream rFile(fileName);
	string file_string;
	string key;
	vector<string> v_str;
	while (getline(rFile, file_string)) {
		splitString(v_str, file_string, '|');
		for (vector<string>::iterator iterator = v_str.begin(); iterator != v_str.end(); ++iterator) {
			Id_Socket[*(--iterator)] = stoi(*(++iterator));
			++iterator;
		}
	}
	rFile.close();
	mtx.unlock();
}
void tool::GScheToTxt(const char* fileName,map<string, string>&Map) {
	mutex mtx;
	mtx.lock();
	ofstream wFile(fileName);
	for (map<string, string>::const_iterator iterator = Map.begin(); iterator != Map.end(); ++iterator) {
		wFile << iterator->first << "|" << iterator->second;
		wFile << "\n";
	}
	wFile.close();
	mtx.unlock();
}
void tool::TxtToGSche(const char* fileName,map<string, string>&Map) {
	mutex mtx;
	mtx.lock();
	ifstream rFile(fileName);
	string file_string;
	string key;
	vector<string> v_str;
	while (getline(rFile, file_string)) {
		char* buf = _strdup(file_string.c_str());
		char* time = strtok(buf, "|");
		char* Str = strtok(NULL,"\n");
		Map[time] = Str;
	}
	rFile.close();
	mtx.unlock();
}
/*
int tool::DailyScheduleToFile(Schedule &Ds, string Id ,string date ,string day) {//day == 해당요일
	string filepath = "c:/server/" + Id + "/schedule/daily/"+ day  + "/" + date + ".bin";
	ofstream fout(filepath, ios::out | ios::binary);
	if (fout.is_open() ) {
		fout.write((char*)&Ds, sizeof(Ds));
		fout.close();
		return 0;
	}
	else { return -1; }
}
int tool::WeeklyScheduleToFile(Schedule &Ds, string Id, string day) {//day == 해당일자 yymmdd
	string filepath = "c:/server/" + Id + "/schedule/weekly/" + day + ".bin";
	ofstream fout(filepath, ios_base::out | ios_base::binary);
	if (fout.is_open()) {
		fout.write((char*)&Ds, sizeof(Ds));
		fout.close();
		return 0;
	}
	else { return 1; }
}
int tool::FileToDailyScheduleClass(Schedule &Ds, string Id, string date, string day) {
	string filepath = "c:/server/" + Id + "/schedule/daily/" + day + "/" + date + ".bin";
	ifstream fin(filepath, ios_base::in | ios_base::binary);
	if (fin.is_open()) {
		fin.read((char*)&Ds, sizeof(Ds));
		fin.close();
		return 0;
	}
	else { return -1; }
}
int tool::FileToWeeklyScheduleClass(Schedule &Ds, string Id, string day) {
	string filepath = "c:/server/" + Id + "/schedule/weekly/" + day + ".bin";
	ifstream fin(filepath, ios_base::in | ios_base::binary);
	if (fin.is_open()) {
		fin.read((char*)&Ds, sizeof(Ds));
		fin.close();
		return 0;
	}
	else { return -1; }
}
*/
