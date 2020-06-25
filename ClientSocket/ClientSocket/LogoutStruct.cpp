#include "pch.h"
#include "LogoutStruct.h"

LogoutStruct::LogoutStruct(string userName) {
	this->userName = userName;
}

LogoutStruct::LogoutStruct() {
	this->userName = "Nick";
}

LogoutStruct::~LogoutStruct() {
	delete this;
}

// override
vector<char> LogoutStruct::pack() {

	vector<char> data;

	data.push_back((char)MessageType::logoutNotification);

	for (int i = 0; i < this->userName.length(); i++)
	{

		data.push_back(this->userName[i]);

	}

	return data;
}
// override
void LogoutStruct::unpack(vector<char> buff) {

	this->userName.clear();

	if (buff.size() > 0)
	{
		int i = 1;
		for (; i < buff.size() &&
			buff[i] != ' '
			; i++)
		{
			this->userName.push_back(buff[i]);
		}
	}
}
// override test
void LogoutStruct::hello() {


}