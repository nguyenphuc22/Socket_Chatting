#include "LogoutStruct.h"
#include "User.h"
#include <list>
// Object login 
class UserOnlineStruct : public ChatStruct
{
private:

public:
	vector<string> userName;

	//Contractor
	UserOnlineStruct(list<User> userName);
	UserOnlineStruct();

	~UserOnlineStruct();
	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};
#pragma once
