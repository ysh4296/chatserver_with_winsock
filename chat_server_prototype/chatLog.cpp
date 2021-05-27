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
		cout << "파일을읽는중입니다" << endl;
		while (!Chat.eof())
		{
			Sleep(100);// 속도가 너무 빨라서 client가 정보를 다 못받는 경우가 생김 허걱
			getline(Chat, chat);
			Run(client, chat);
		}
	}

	getline(Chat, chat);
	Run(client, chat);
}