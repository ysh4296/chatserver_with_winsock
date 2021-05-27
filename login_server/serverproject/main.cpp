#include <string>
#include "server.h"
using namespace std;


int main()
{
	server serv("127.0.0.1", 54010);//서버의 ip와 port 127.0.0.1은 자신의 컴퓨터
	if (serv.Init())
	{
		serv.Run();
	}
}