#include "signin.h"


signin::signin(string id,string psword)
:m_id(id), m_psword(psword)
{
}


signin::~signin()
{
}

int signin::Enroll(string id, string psword)
{
	ofstream out("test.txt", ios::app);
	string Id = id;
	string Psword = psword;
	if (out.is_open()){
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