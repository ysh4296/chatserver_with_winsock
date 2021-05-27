#pragma once
#include <string>
#include <sstream>
#include <fstream>
//#include <thread>
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Valid.h"
#include "chatLog.h"
#pragma comment(lib,"ws2_32.lib")
#define MAX_BUFFER_SIZE (49152)
using namespace std;

void in(SOCKET client)
{
	Valid va(client);
	va.in(client);
}
int main()
{
	while (1)
	{
		// 윈속 초기화
		string ip = "127.0.0.1";
		int port = 4296;
		WSADATA data;
		WORD ver = MAKEWORD(2, 2);
		int wsInit = WSAStartup(ver, &data);
		if (wsInit != 0) {
			cout << "윈속 초기화 실패" << endl;
		}
		cout << "윈속 초기화 성공" << endl;
		//listen 소켓 생성
		SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in insock;
		insock.sin_family = AF_INET;
		insock.sin_port = htons(port);
		inet_pton(AF_INET, ip.c_str(), &insock.sin_addr);
		bind(listensock, (sockaddr*)&insock, sizeof(insock));
		listen(listensock, SOMAXCONN);
		cout << "소켓 연결 대기중" << endl;
		fd_set master;

		FD_ZERO(&master);

		FD_SET(listensock, &master);
		cout << "listensock을 master에 추가" << endl;
		while (true)
		{
			fd_set copy = master;

			int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
			cout << "select 실행" << socketCount << "에 이벤트 발생" << endl;
			for (int i = 0; i < socketCount; i++)
			{
				SOCKET sock = copy.fd_array[i];
				if (sock == listensock)
				{
					//Accept a new connection
					SOCKET client = accept(listensock, nullptr, nullptr);
					cout << "소켓 accept" << endl;
					// Add the new connection to the list of connected client
					FD_SET(client, &master);
					// send a welcome message to the connected client
					// 로그인하기 thread속으로 넣음
					//thread In(&in, sock);
					//In.join();
					// 헤더파일 thread는 listensocket 생성을 방해하는거같음 thread 생성이 안됨
					Valid va(client);
					va.in(client);
					string welcomeMsg = "Welcome to the Awesome Chat Server!";
					send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
					// TODO: Broadcast we have a new connection

					chatLog cL(client);
					cL.Read(client);
				}
				else
				{
					char buf[4096];
					ZeroMemory(buf, 4096);
					cout << "socket:" << sock << "recv 실행" << endl;
					int bytesIn = recv(sock, buf, 4096, 0);
					if (bytesIn <= 0) // client의 접속종료
					{
						// Drop the client

						cout << "socket:" << sock << " 을 제거하고 file descripter에서 제거합니다." << endl;
						closesocket(sock);
						FD_CLR(sock, &master);
					}
					else
					{
						ofstream out("chatlog.txt", ios::app);
						if (out.is_open()) {
							cout << "writing file" << endl;
							out << "SOCKET #" << sock << ":" << buf <<endl;
						}
						cout << "메세지 송신 완료" << endl;
						// Send message to other clients
						for (int i = 0; i < master.fd_count; i++)
						{
							SOCKET outSock = master.fd_array[i];
							if (outSock != listensock && outSock != sock)
							{
								cout << sock << " 에 메세지 송신" << endl;
								ostringstream ss;
								ss << "SOCKET #" << sock << ":" << buf << "\r\n";
								string strOut = ss.str();
								send(outSock, strOut.c_str(), strOut.size() + 1, 0);

							}
						}
					}
					// Accept a new message
					// Send message to other clients, and definitely not the listening socket
				}
			}
			cout << "작은 loop 종료" << endl;
		}
	}
	WSACleanup();
}