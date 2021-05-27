#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Send.h"
using namespace std;
class login:public Send
{
public:
	login(string id,string psword);
	~login();
	int Login(string searchid,string searchpsword);
	void state() {
		cout << "Login state" << endl;
	};
private:
	string m_id;
	string m_psword;
};

