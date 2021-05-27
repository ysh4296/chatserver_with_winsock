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
		cout << "id 중복 검사" << endl;
		while (!test.eof())
		{
			getline(test, Id);
			getline(test, Psword);
			if (Id == inputid)
			{
				cout << "입력받은 id가 중복입니다" << endl;
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
		cout << "\r\n회원가입 완료" << endl;
		return 1;
	}
	else {
		cout << "파일을 찾을 수 없습니다." << endl;
		return 0;
	}
}