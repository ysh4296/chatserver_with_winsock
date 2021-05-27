#include "server.h"


server::server(std::string ip,int port)// ������ /�ɹ� �ʱ�ȭ
:m_ip(ip), m_port(port)
{
}
server::~server()// destructor
{
	Cleanup();//winsock ����
}
bool server::Init()// winsock �ʱ�ȭ ���� ��Ʈ��ũ�� �ϱ����� ���� ó������ ���ľߵǴ� ����
{
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);//winsock �ʱ�ȭ
	return wsInit == 0;
}
void server::Cleanup()
{
	WSACleanup();//winsock ����
}
SOCKET server::CreateSocket()
{
	SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);// ���ϻ��� / �ּ��йи�,��Ĺ����,��ſɼ�
	if (listensock != INVALID_SOCKET)
	{
		sockaddr_in insock;//sockaddr_in �� ���Ͽ� ������ ������ ����
		insock.sin_family = AF_INET;
		insock.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ip.c_str(), &insock.sin_addr);// ip�ּҸ� ���������ͷ� ��ȯ�ؼ� ������
		bind(listensock, (sockaddr*)&insock, sizeof(insock));// bind �Լ��� ���� ���Ͽ� ip�ּ�/��Ʈ��/ip�ּ� ���������Ͱ��� ����

		listen(listensock, SOMAXCONN);//listensock�� listen���·� ����
	}
	return listensock;
}
void server::Run()//���� ���������� �Լ�
{
	char String[MAX_BUFFER_SIZE];
	char String2[MAX_BUFFER_SIZE];
	while (true)//������ �� ������ �׻� ��������
	{
		cout << "waiting for a client\r\n" << endl;
		int byteReceive = 0;
		int byteReceive2 = 0;
		SOCKET listensock = CreateSocket();//listen socket ����

		if (listensock == INVALID_SOCKET)
		{
			break;
		}
		string start = "1: sign up 2: log in";
		cout << "\n\n\n  �����Ǿ����ϴ� \n\n\n" << endl;
		SOCKET client = WaitForConnection(listensock);//listensocket�� client�� ���� == ����socket�� ����

		cout << "accepting client\r\n" << endl;
		closesocket(listensock);// ��� ������ ���� ������
		do
		{
			Send(client, start);
			ZeroMemory(String, MAX_BUFFER_SIZE);
			byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);//menu�޼����� �Է¹���
			string Menu = std::string(String, 0, byteReceive);
			if (byteReceive > 0)
			{
			}
			if (Menu != "1"&& Menu != "2")
			{
					string end = "wrong message.";

					Send(client, end);
			}
			else if (Menu == "1")
			{
				cout << "client�� ȸ������ ��û\r\n" << endl;
				int YN;
				Send(client, "Enrolling a user");
				Send(client, "id�� �Է��ϼ���");
				ZeroMemory(String, MAX_BUFFER_SIZE);
				byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);// client�� ���� id �Է¹���
				cout << "id�Է°�\r\n" + std::string(String, 0, byteReceive) << endl << endl;
				Send(client, "\r\npsword�� �Է��ϼ���");
				ZeroMemory(String2, MAX_BUFFER_SIZE);
				byteReceive2 = recv(client, String2, MAX_BUFFER_SIZE, 0);// client�� ���� psword �Է¹���
				cout << "psword�Է°�\r\n" + std::string(String2, 0, byteReceive2) << endl << endl;
				signin Sign(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				YN = Sign.Enroll(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				if (YN == 1)
				{
					Send(client, "\r\nsignin succeed!");
				}
				else
				{
					Send(client, "\r\nsignin failed!");
				}
			}
			else if (Menu == "2")
			{
				cout << "client�� �α��� ��û\r\n" << endl;
				int YN;
				Send(client, "login a user");
				Send(client, "id�� �Է��ϼ���");
				ZeroMemory(String, MAX_BUFFER_SIZE);
				byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);// client�� ���� id �Է¹���
				cout << "id�Է°�\r\n" + std::string(String, 0, byteReceive) << endl << endl;
				Send(client, "\r\npsword�� �Է��ϼ���");
				ZeroMemory(String2, MAX_BUFFER_SIZE);
				byteReceive2 = recv(client, String2, MAX_BUFFER_SIZE, 0);// client�� ���� psword �Է¹���
				cout << "psword�Է°�\r\n" + std::string(String2, 0, byteReceive2) << endl << endl;
				login Log(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				YN = Log.Login(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				if (YN == 1)
				{
					Send(client, "\r\nlogin succeed!");
				}
				else
				{
					Send(client, "\r\nlogin failed!");
				}
			}
		} while (byteReceive > 0);
		closesocket(client);
		cout << "closing client\r\n" << endl;
	}

}
SOCKET server::WaitForConnection(SOCKET listensock)
{
	SOCKET client = accept(listensock, NULL, NULL);
	return client;
}
void server::Send(int clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}