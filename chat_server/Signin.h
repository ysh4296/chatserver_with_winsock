#pragma once
#include <direct.h>
#include <WinSock2.h>
#include <string>
#include "Tool.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#define MAX_BUFFER_SIZE 4092
using namespace std;
class Signin: public tool
{
public:
	Signin(SOCKET client);
	~Signin();
	int in(SOCKET client);
};

