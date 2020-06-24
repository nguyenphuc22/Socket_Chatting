#include "ResponseSignupStruct.h"


class ManagerStruct {

public:
	static ChatStruct* createChatStruct(MessageType messageType);
	static ChatStruct* unpack(vector<char> buff);
};

#pragma once