#include "Valid.h"


Valid::Valid(SOCKET client): Send(client)
{
}


Valid::~Valid()
{
}

void Valid::in(SOCKET client)
{

	int suc = 0;
	while (suc ==0)
	{
		char String[MAX_BUFFER_SIZE];
		char String2[MAX_BUFFER_SIZE];
		int byteReceive;
		int byteReceive2;
		do
		{
			state();
			string start = "1: sign up 2: log in";
			Run(client, start);
			ZeroMemory(String, MAX_BUFFER_SIZE);
			byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);//menu�޼����� �Է¹���
			string Menu = std::string(String, 0, byteReceive);
			if (byteReceive > 0)
			{
			}
			if (Menu != "1"&& Menu != "2")
			{
				string end = "wrong message.";

				Run(client, end);
			}
			else if (Menu == "1")
			{
				cout << "client�� ȸ������ ��û\r\n" << endl;
				int YN;
				Run(client, "Enrolling a user");
				Run(client, "id�� �Է��ϼ���");
				ZeroMemory(String, MAX_BUFFER_SIZE);
				byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);// client�� ���� id �Է¹���
				cout << "id�Է°�\r\n" + std::string(String, 0, byteReceive) << endl << endl;
				Run(client, "\r\npsword�� �Է��ϼ���");
				ZeroMemory(String2, MAX_BUFFER_SIZE);
				byteReceive2 = recv(client, String2, MAX_BUFFER_SIZE, 0);// client�� ���� psword �Է¹���
				cout << "psword�Է°�\r\n" + std::string(String2, 0, byteReceive2) << endl << endl;
				signin Sign(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				YN = Sign.Enroll(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				if (YN == 1)
				{
					Run(client, "\r\nsignin succeed!");
				}
				else
				{
					if (YN == 2)
					{
						Run(client, "\r\nid overlaped");
					}
					Run(client, "\r\nsignin failed!");
				}
			}
			else if (Menu == "2")
			{
				cout << "client�� �α��� ��û\r\n" << endl;
				int YN;
				Run(client, "login a user");
				Run(client, "id�� �Է��ϼ���");
				ZeroMemory(String, MAX_BUFFER_SIZE);
				byteReceive = recv(client, String, MAX_BUFFER_SIZE, 0);// client�� ���� id �Է¹���
				cout << "id�Է°�\r\n" + std::string(String, 0, byteReceive) << endl << endl;
				Run(client, "\r\npsword�� �Է��ϼ���");
				ZeroMemory(String2, MAX_BUFFER_SIZE);
				byteReceive2 = recv(client, String2, MAX_BUFFER_SIZE, 0);// client�� ���� psword �Է¹���
				cout << "psword�Է°�\r\n" + std::string(String2, 0, byteReceive2) << endl << endl;
				login Log(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				YN = Log.Login(std::string(String, 0, byteReceive), std::string(String2, 0, byteReceive2));
				if (YN == 1)
				{
					Run(client, "\r\nlogin succeed!");
					suc = 1;
				}
				else
				{
					Run(client, "\r\nlogin failed!");
				}
			}
		} while (suc == 0);



	}
}
//void Valid::Send(int clientSocket, std::string msg)
//{
//	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
//}