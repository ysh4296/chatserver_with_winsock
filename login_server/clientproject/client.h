#pragma once
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define MAX_BUFFER_SIZE (49152)
class client
{
public:
	client(std::string ip, int port);
	~client();

	void Send(int serverSocket, std::string msg);

	bool Init();

	void Run();

	void Cleanup();

	void Get(SOCKET server, char msg[]);
private:
	SOCKET Connect();
	SOCKET WaitForConnection(SOCKET listening);

	std::string m_ip;
	int			m_port;
};