#include "chatLog.h"


chatLog::chatLog(SOCKET client):Send(client)
{
}


chatLog::~chatLog()
{
}

void chatLog::Read(SOCKET client)
{
	state();
	string chat;
	ifstream Chat;
	Chat.open("chatlog.txt");
	if(Chat.is_open())
	{
		cout << "�������д����Դϴ�" << endl;
		while (!Chat.eof())
		{
			Sleep(100);// �ӵ��� �ʹ� ���� client�� ������ �� ���޴� ��찡 ���� ���
			getline(Chat, chat);
			Run(client, chat);
		}
	}

	getline(Chat, chat);
	Run(client, chat);
}