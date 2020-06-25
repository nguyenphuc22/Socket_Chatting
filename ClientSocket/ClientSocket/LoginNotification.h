#include "ResponseLoginStruct.h"


// Object signup 
class LoginNotification : public ChatStruct
{
private:

public:
	string userName;

	LoginNotification(string userName);

	LoginNotification();

	~LoginNotification();

	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};

