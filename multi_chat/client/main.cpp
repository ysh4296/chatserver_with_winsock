#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mutex>
#pragma comment(lib,"ws2_32.lib")
#define MAX_BUFFER_SIZE (49152)
using namespace std;
mutex mtx;
void Get(SOCKET server, char msg[])
{
	while (1)
	{
		mtx.lock();
		ZeroMemory(msg, 4096);
		recv(server, msg, 4096, 0);
		cout << msg << endl;
		mtx.unlock();
	}
}
void Send(SOCKET server)
{
	char buffer[4096];
	cin.getline(buffer,sizeof(buffer));
	send(server, buffer, 4096, 0);
}
int main()
{
	// ���� �ʱ�ȭ
	string ip = "127.0.0.1";
	int port = 4296;
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);
	if (wsInit != 0) {
		cout << "���� �ʱ�ȭ ����" << endl;
	}
	else
	{
		cout << "���� �ʱ�ȭ ����" << endl;
	}
	SOCKET consock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in insock;
	insock.sin_family = AF_INET;
	insock.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &insock.sin_addr);
	int result = connect(consock, (sockaddr*)&insock, sizeof(insock));
	char buf[4096];

	if (result == SOCKET_ERROR)
	{
		cout << "connect ����" << endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "connect ����" << endl;
	}

	thread Getm(&Get, consock, buf);
	
	while (1)
	{
		Send(consock);
	}

	Getm.join();

	WSACleanup();
	return 0;

}