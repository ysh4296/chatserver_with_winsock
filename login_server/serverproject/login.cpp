#include "login.h"


login::login(string id,string psword)
:m_id(id), m_psword(psword)
{
}
login::~login()
{
}
int login::Login(string searchid,string searchpsword)
{
	string id;
	string psword;
	ifstream test;
	test.open("test.txt");
	cout << "id , psword �˻�\r\n" << endl;
	if (test.is_open())
	{

		cout << "searching file" << endl;
	while (!test.eof())
	{
	getline(test,id);
	getline(test, psword);
	//cout << id << endl;
	//cout << psword << endl;
	if (id == searchid && psword == searchpsword)
	{
	cout << "\r\n�α��� �Ǿ����ϴ�." << endl;

	return 1;
	break;
	}
	}
	if (test.eof())
	{
	cout << "\r\nid �Ǵ� ��й�ȣ�� �߸� �ԷµǾ����ϴ�." << endl;
	return 0;
	}
	}
}