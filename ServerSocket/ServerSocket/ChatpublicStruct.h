#include "UserOnlineStruct.h"
// Object login 
class ChatpublicStruct : public ChatStruct
{

public:
	string userName;
	string passWord;
	//Contractor
	ChatpublicStruct(string userName);
	ChatpublicStruct();

	~ChatpublicStruct();
	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};
#pragma once
