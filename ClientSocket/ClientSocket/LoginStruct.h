#include "ChatStruct.h"
// Object login 
class LoginStruct : public ChatStruct
{

public:
	string userName;
	string passWord;
	//Contractor
	LoginStruct(string userName, string passWord);
	LoginStruct();

	~LoginStruct();
	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};
#pragma once
