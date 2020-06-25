#include "ChatprivateStruct.h"


// Object signup 
class LogoutNotification : public ChatStruct
{
private:

public:
	string userName;

	LogoutNotification(string userName);

	LogoutNotification();

	~LogoutNotification();

	// override
	virtual vector<char> pack();
	// override
	virtual void unpack(vector<char> buff);
	// override test
	virtual void hello();
};

