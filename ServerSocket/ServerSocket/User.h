#pragma once
#include <WinSock2.h>
#include <string>
#include <string.h>

using namespace std;

class User
{
public:
	SOCKET socket;
	string userName;
};

