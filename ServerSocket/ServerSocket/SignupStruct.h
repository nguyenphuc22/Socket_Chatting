#include "LoginStruct.h"
// Object signup 
class SignupStruct : public ChatStruct
{
private:

public:
	string userName;
	string passWord;
	//Contractor
	SignupStruct(string userName, string passWord);

	SignupStruct();

	~SignupStruct();
	// override
	vector<char> pack();
	// override
	void unpack(vector<char> buff);
	// override test
	void hello();
};
#pragma once
