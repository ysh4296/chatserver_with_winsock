#include "client.h"


client::client(std::string ip, int port)
:m_ip(ip), m_port(port)
{
}


client::~client()
{
	Cleanup();
}

bool client::Init()//winsock �ʱ�ȭ
{
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);
	return wsInit == 0;
}

void client::Cleanup()// ���� ����
{
	WSACleanup();
}

SOCKET client::Connect()
{

	SOCKET consock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);// ���ϻ��� / �ּ��йи�,��Ĺ����,��ſɼ�
	if (consock != INVALID_SOCKET)
	{
		sockaddr_in insock;//sockaddr_in �� ���Ͽ� ������ ������ ����
		insock.sin_family = AF_INET;
		insock.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ip.c_str(), &insock.sin_addr);// ip�ּҸ� ���������ͷ� ��ȯ�ؼ� ������
		int result = connect(consock, (sockaddr*)&insock, sizeof(insock));// connect �Լ��� ���� ������ ����
		if (result == SOCKET_ERROR)
		{
			cout << "connection failed open server first\r\n" << endl;
		}
		else
		{
			cout << "connection succeed\r\n" << endl;
		}

	}
	return consock;
}

void client::Run()
{
	char message[MAX_BUFFER_SIZE];
	std::string str;
	int byteReceive = 0;
	SOCKET server = Connect();//listen socket ����
	do
	{

		//ZeroMemory(message, MAX_BUFFER_SIZE);
		//recv(server, message, MAX_BUFFER_SIZE, 0);// 1: signin 2: login
		//cout << message << endl;
		
		Get(server, message);
		cin >> str;// �޴� ����
		Send(server, str);
		if (str == "1")
		{
			Get(server, message);// enrolling a user

			Get(server, message);// id �� �Է��ϼ���
			cin >> str;
			Send(server, str);// id send

			Get(server, message);// ps �� �Է��ϼ���
			cin >> str;
			Send(server, str);// psword send


			Get(server, message);//ȸ�����Կ� ����/�����Ͽ����ϴ�.
		}
		else if(str == "2")
		{
			Get(server, message);// login a user


			Get(server, message);// id �� �Է��ϼ���
			cin >> str;
			Send(server, str);//id send
			Get(server, message);// psword �� �Է��ϼ���
			cin >> str;
			Send(server, str);//psword send
			Get(server, message);// �α��ο� ����/���� �Ͽ����ϴ�.
		}
		else
		{
			Get(server, message);// wrong message
		}
	} while (true);
	closesocket(server);
	cout << "�������� ����" << endl << endl;
}
void client::Send(int serverSocket, std::string msg)
{
	send(serverSocket, msg.c_str(), msg.size() + 1, 0);
}
void client::Get(SOCKET server,char msg[])
{
	ZeroMemory(msg, MAX_BUFFER_SIZE);
	recv(server, msg, MAX_BUFFER_SIZE, 0);
	cout << msg << endl << endl;
}