#include <string>
#include "server.h"
using namespace std;


int main()
{
	server serv("127.0.0.1", 54010);//������ ip�� port 127.0.0.1�� �ڽ��� ��ǻ��
	if (serv.Init())
	{
		serv.Run();
	}
}