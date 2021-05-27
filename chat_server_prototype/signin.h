#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Send.h"
using namespace std;
class signin:Send
{
public:
	signin(string id, string psword);
	~signin();
	int Enroll(string id, string psword);
	void state() {
		cout << "Signin state" << endl;
	};
private:
	string m_id;
	string m_psword;
};

