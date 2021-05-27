#pragma once
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#include "login.h"
#include "signin.h"
#define MAX_BUFFER_SIZE (49152)
class server;
class server
{
public:
	server(std::string ip, int port);
	~server();

	void Send(int clientSocket, std::string msg);

	bool Init();

	void Run();

	void Cleanup();

private:
	SOCKET CreateSocket();
	SOCKET WaitForConnection(SOCKET listening);

	std::string m_ip;
	int			m_port;
};

