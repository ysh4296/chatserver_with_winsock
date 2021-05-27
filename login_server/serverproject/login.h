#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class login
{
public:
	login(string id,string psword);
	~login();
	int Login(string searchid,string searchpsword);
private:
	string m_id;
	string m_psword;
};

