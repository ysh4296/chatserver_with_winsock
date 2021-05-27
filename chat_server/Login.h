#pragma once
#include <WinSock2.h>
#include <string>
#include "tool.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <iterator>

using namespace std;

class Login :public tool
{
public:
	Login(SOCKET client);
	~Login();
	int logging(SOCKET client);
	
};

