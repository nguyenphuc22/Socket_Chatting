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
	{
		result = new ChatpublicStruct();

		result->mesageType = MessageType::publicMessage;


		result->unpack(buff);

		break;
	}
	case privateMessage:
	{
		result = new ChatprivateStruct();

		result->mesageType = MessageType::privateMessage;


		result->unpack(buff);

		break;
	}
	case privateFile:
		break;
	case userStatus:
	{
		result = new UserOnlineStruct();
		result->mesageType = MessageType::userStatus;

		result->unpack(buff);

		break;
	}
	case requestSendFile:
		break;
	case responseSendFile:
		break;
	case login:
	{
		result = new LoginStruct();
		result->mesageType = MessageType::login;

		result->unpack(buff);

		break;
	}
	case responseLogin:
	{
		result = new ResponseLoginStruct();

		result->mesageType = MessageType::responseLogin;

		result->unpack(buff);

		break;
	}
	case signup:
	{
		result = new SignupStruct();
		result->mesageType = MessageType::signup;

		result->unpack(buff);

		break;
	}
	case responseSignup:
	{
		result = new ResponseSignupStruct();

		result->mesageType = MessageType::responseSignup;

		result->unpack(buff);

		break;
	}
	case loginNotification:
	{
		result = new LoginNotification();

		result->mesageType = MessageType::loginNotification;

		result->unpack(buff);

		break;
	}
	case logoutNotification:
	{
		result = new LogoutStruct();

		result->mesageType = MessageType::logoutNotification;

		result->unpack(buff);

		break;
	}
	default:
		break;
	}

	return result;
}