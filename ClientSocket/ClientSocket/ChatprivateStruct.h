#include "ChatpublicStruct.h"
// Object login 
class ChatprivateStruct : public ChatStruct
{

public:
	string userName;
	string msg;
	//Contractor
	ChatprivateStruct(string userName, string msg);
	ChatprivateStruct();

	~ChatprivateStruct();
	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};
#pragma once
