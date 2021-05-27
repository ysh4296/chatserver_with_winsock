#include <Winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <sstream>
#include <thread>  
#include <direct.h>
#include <WS2tcpip.h>
#include "Signin.h"
//#include "Alarm.h"
#include "Login.h"
#include "Messanger.h"
#include "TimeTable.h"
#include "Tool.h"
//#include "TimeTable.h"
using namespace std;
fd_set Fd;
#pragma comment(lib,"ws2_32.lib")
void Sign(SOCKET client) {
	Signin sign(client);
	sign.in(client);
}
void Log(SOCKET client) {
	Login login(client);
	login.logging(client);
}
//void Message(SOCKET client, string id) {
//	Alarm alarm(client, id);
//	alarm.Messanger(client, id);
//	Messanger messanger(client, id);
//	messanger.in(client, id);
//}
void Table(SOCKET client, string id) {
	TimeTable table(client, id);
	table.table(client, id);
}
int main() {
	while (1) {
		WSADATA data;
		WORD ver = MAKEWORD(2, 2);
		map<string, SOCKET>socket_info;
		ofstream wFile("c:/server/Id_Socket_map.txt");
		for (map<string, SOCKET>::const_iterator iterator = socket_info.begin(); iterator != socket_info.end(); ++iterator) {
			wFile << iterator->first << "|" << iterator->second;
			wFile << "\n";
		}
		wFile.close();
		int wsInit = WSAStartup(ver, &data);
		if (wsInit != 0) {
			cout << "윈속 초기화 실패" << endl;
		}
		cout << "윈속 초기화 성공" << endl;
		_mkdir("c:/server");
		_mkdir("c:/server/schedule/daily");
		_mkdir("c:/server/schedule/weekly");
		SOCKET listensocket = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in insocket;
		insocket.sin_family = AF_INET;
		int port = 4296;
		insocket.sin_port = htons(port);
		string ip = "127.0.0.1";
		inet_pton(AF_INET, ip.c_str(), &insocket.sin_addr);
		::bind(listensocket, (sockaddr*)&insocket, sizeof(insocket));
		listen(listensocket, SOMAXCONN);
		FD_ZERO(&Fd);
		FD_SET(listensocket, &Fd);
		cout << "listensock을 master에 추가" << endl;
		while (1) {
			fd_set copy = Fd;
			int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
			cout << "select 실행" << socketCount << "에 이벤트 발생" << endl;
			for (int i = 0; i < socketCount; i++) {
				SOCKET sock = copy.fd_array[i];
				if (sock == listensocket)
				{
					SOCKET client = accept(listensocket, nullptr, nullptr);
					cout << "소켓 accept" << endl;
					FD_SET(client, &Fd);
				}
				else {
					char buf[MAX_BUFFER_SIZE];
					ZeroMemory(buf, MAX_BUFFER_SIZE);
					int byteIn = recv(sock, buf, MAX_BUFFER_SIZE, 0);
					if (byteIn <= 0) {
						closesocket(sock);
						FD_CLR(sock, &Fd);
					}
					else {
						if (strcmp(buf, "Signin") == 0) {//client의 login 요청
						   //thread Signin
							thread SIGN(&Sign, sock);
							SIGN.detach();
						}
						else if (strcmp(buf, "Login") == 0) {
							thread LOGIN(&Log, sock);
							LOGIN.detach();
						}
						//else if (strcmp(buf, "Messanger") == 0) {
						//	cout << "Messanger in" << endl;
						//	buf[MAX_BUFFER_SIZE];
						//	ZeroMemory(buf, MAX_BUFFER_SIZE);
						//	int byteIn = recv(sock, buf, MAX_BUFFER_SIZE, 0);
						//	if (byteIn <= 0) {
						//		closesocket(sock);
						//		FD_CLR(sock, &Fd);
						//	}
						//	else {
						//		thread Messange(&Message, sock, buf);
						//		Messange.detach();
						//	}
						//}
						else if (strcmp(buf, "TimeTable") == 0) {
							cout << "TimeTable in" << endl;
							buf[MAX_BUFFER_SIZE];
							ZeroMemory(buf, MAX_BUFFER_SIZE);
							int byteIn = recv(sock, buf, MAX_BUFFER_SIZE, 0);
							if (byteIn <= 0) {
								closesocket(sock);
								FD_CLR(sock, &Fd);
							}
							else {
								thread TimeTable(&Table, sock, buf);
								cout << "접속:" << buf << endl;
								TimeTable.detach();
							}
						}
						//메세지 수신
						//event 수신
						//recv 현재 client의 상태를 입력받고
						//switch(msg)

						//thread 구분 detach
						{
							//case 구분
							{
								//login();

								//sendmsg();

								//plusfri();

								//makemultichat();

								//msgread(currid,file);
							}
						}

					}
				}
			}
		}
	}
}