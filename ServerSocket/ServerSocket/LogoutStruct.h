#include "LoginNotification.h"
// Object login 
class LogoutStruct : public ChatStruct
{
private:

public:
	string userName;

	//Contractor
	LogoutStruct(string userName);
	LogoutStruct();

	~LogoutStruct();
	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};
#pragma once
