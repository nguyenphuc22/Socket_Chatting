#include "pch.h"
#include "ManagerStruct.h"

ChatStruct* ManagerStruct::createChatStruct(MessageType messageType) {
	switch (messageType)
	{
	case MessageType::publicMessage:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::privateMessage:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::privateFile:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::userStatus:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::requestSendFile:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::responseSendFile:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::login:
	{
		new LoginStruct();
		break;
	}
	case MessageType::responseLogin:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::signup:
	{
		// implement create 
		return new SignupStruct();
		break;
	}
	case MessageType::responseSignup:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::loginNotification:
	{
		// implement create 
		return NULL;
		break;
	}
	case MessageType::logoutNotification:
	{
		// implement create 
		return NULL;
		break;
	}
	default:
	{
		return NULL;
		break;
	}
	}
}

ChatStruct* ManagerStruct::unpack(vector<char> buff) {

	if (buff.empty())
	{
		return NULL;
	}
	ChatStruct* result = NULL;
	// convert char to int
	int convertTemp = (int)buff[0];
	// convert int to MessageType 
	MessageType messageType = (MessageType)convertTemp;

	switch (messageType)
	{
	case publicMessage:
		break;
	case privateMessage:
		break;
	case privateFile:
		break;
	case userStatus:
		break;
	case requestSendFile:
		break;
	case responseSendFile:
		break;
	case login:
		break;
	case responseLogin:
		break;
	case signup:
	{
		result = new SignupStruct();
		result->mesageType = MessageType::signup;

		result->unpack(buff);

		break;
	}
	case responseSignup:
		break;
	case loginNotification:
		break;
	case logoutNotification:
		break;
	default:
		break;
	}

	return result;
}