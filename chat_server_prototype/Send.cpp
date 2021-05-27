#include "Send.h"



Send::Send(SOCKET client)
{
}


Send::~Send()
{
}
void Send::Run(SOCKET client , string msg)
{
	send(client, msg.c_str(), msg.size() + 1, 0);
}
void Send::state()
{
	cout << "Send state" << endl;
}