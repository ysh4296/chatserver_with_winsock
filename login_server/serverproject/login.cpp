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
	cout << "id , psword 검색\r\n" << endl;
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
	cout << "\r\n로그인 되었습니다." << endl;

	return 1;
	break;
	}
	}
	if (test.eof())
	{
	cout << "\r\nid 또는 비밀번호가 잘못 입력되었습니다." << endl;
	return 0;
	}
	}
}