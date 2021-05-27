#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class signin
{
public:
	signin(string id, string psword);
	~signin();
	int Login(string searchid, string searchpsword);
	int Enroll(string id, string psword);
private:
	string m_id;
	string m_psword;
};

