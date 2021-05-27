#include <string>
#include "client.h"
using namespace std;
int main()
{
	client clt("127.0.0.1", 54010);//서버의 ip와 port 127.0.0.1은 자신의 컴퓨터
	if (clt.Init())
	{
		clt.Run();
	}


}