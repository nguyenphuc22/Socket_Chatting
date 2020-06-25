#include "ResponseSignupStruct.h"

// Object signup 
class ResponseLoginStruct : public ChatStruct
{
private:

public:
	bool isSecc;

	string error;

	ResponseLoginStruct(bool isSecc, string error);

	ResponseLoginStruct();

	~ResponseLoginStruct();

	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};
