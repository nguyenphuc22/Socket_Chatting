#include "pch.h"
#include "LogoutNotification.h"

LogoutNotification::LogoutNotification(string userName) {
	this->userName = userName;
}

LogoutNotification::LogoutNotification() {
	this->userName = "Nick";
}

LogoutNotification::~LogoutNotification() {
	delete this;
}

// override
vector<char> LogoutNotification::pack() {

	vector<char> data;

	data.push_back((char)MessageType::loginNotification);

	for (int i = 0; i < this->userName.length(); i++)
	{

		data.push_back(this->userName[i]);

	}

	return data;
}
// override
void LogoutNotification::unpack(vector<char> buff) {

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
void LogoutNotification::hello() {


}