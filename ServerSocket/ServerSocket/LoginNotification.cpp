#include "pch.h"
#include "LoginNotification.h"

LoginNotification::LoginNotification(string userName) {
	this->userName = userName;
}

LoginNotification::LoginNotification() {
	this->userName = "Nick";
}

LoginNotification::~LoginNotification() {
	delete this;
}

// override
vector<char> LoginNotification::pack() {

	vector<char> data;

	data.push_back((char)MessageType::loginNotification);

	for (int i = 0; i < this->userName.length(); i++)
	{

		data.push_back(this->userName[i]);

	}

	return data;
}
// override
void LoginNotification::unpack(vector<char> buff) {
	
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
void LoginNotification::hello() {


}