#include "signin.h"


signin::signin(string id, string psword)
	:Send(client),m_id(id), m_psword(psword)
{
}


signin::~signin()
{
}


int signin::Enroll(string inputid, string inputpsword)
{
	state();
	ofstream out("test.txt", ios::app);
	ifstream test;
	string Id;
	string Psword;
	test.open("test.txt");
	if (test.is_open())
	{
		cout << "id �ߺ� �˻�" << endl;
		while (!test.eof())
		{
			getline(test, Id);
			getline(test, Psword);
			if (Id == inputid)
			{
				cout << "�Է¹��� id�� �ߺ��Դϴ�" << endl;
				return 2;
				break;
			}
		}
	}
	Id = inputid;
	Psword = inputpsword;
	if (out.is_open()) {
		cout << "writing file" << endl;
		out << Id << endl;
		out << Psword << endl;
		cout << "\r\nȸ������ �Ϸ�" << endl;
		return 1;
	}
	else {
		cout << "������ ã�� �� �����ϴ�." << endl;
		return 0;
	}
}