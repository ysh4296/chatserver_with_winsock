#include <string>
#include "client.h"
using namespace std;
int main()
{
	client clt("127.0.0.1", 54010);//������ ip�� port 127.0.0.1�� �ڽ��� ��ǻ��
	if (clt.Init())
	{
		clt.Run();
	}


}