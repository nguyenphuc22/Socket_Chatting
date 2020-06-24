#include "SignupStruct.h"
#ifndef AAA_HEADER
#define AAA_HEADER

// Object signup 
class ResponseSignupStruct : public ChatStruct
{
private:

public:
	bool isSecc;

	string error;

	ResponseSignupStruct(bool isSecc, string error);

	ResponseSignupStruct();

	~ResponseSignupStruct();

	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};

#endif