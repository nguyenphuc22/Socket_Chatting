#include "pch.h"
#include "ChatprivateStruct.h"

ChatprivateStruct::ChatprivateStruct(string userName, string msg) {
	this->userName = userName;
	this->msg = msg;
}


ChatprivateStruct::ChatprivateStruct() {
	this->userName = "Nick";
}

ChatprivateStruct::~ChatprivateStruct() {
	delete this;
}

// override
vector<char> ChatprivateStruct::pack() {

	vector<char> data;

	data.push_back((char)MessageType::privateMessage);

	for (int i = 0; i < this->userName.length(); i++)
	{
		data.push_back(userName[i]);
	}

	data.push_back('|');

	for (int i = 0; i < this->msg.length(); i++)
	{
		data.push_back(msg[i]);
	}

	return data;
}
// override
void ChatprivateStruct::unpack(vector<char> buff) {

	this->userName.clear();

	if (buff.size() > 0)
	{
		int i = 1;
		for (; i < buff.size(); i++)
		{
			if (buff[i] == '|')
			{
				break;
			}
			this->userName.push_back(buff[i]);
		}

		for (; i < buff.size(); i++)
		{
			this->msg.push_back(buff[i]);
		}
	}
}
// override test
void ChatprivateStruct::hello() {


}