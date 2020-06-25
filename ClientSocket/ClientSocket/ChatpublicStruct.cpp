#include "pch.h"
#include "ChatpublicStruct.h"

ChatpublicStruct::ChatpublicStruct(string userName) {
	this->userName = userName;
}

ChatpublicStruct::ChatpublicStruct() {
	this->userName = "Nick";
}

ChatpublicStruct::~ChatpublicStruct() {
	delete this;
}

// override
vector<char> ChatpublicStruct::pack() {

	vector<char> data;

	data.push_back((char)MessageType::publicMessage);

	for (int i = 0; i < this->userName.length(); i++)
	{
		data.push_back(userName[i]);
	}

	return data;
}
// override
void ChatpublicStruct::unpack(vector<char> buff) {

	this->userName.clear();

	if (buff.size() > 0)
	{
		int i = 1;
		for (; i < buff.size(); i++)
		{
			this->userName.push_back(buff[i]);
		}
	}
}
// override test
void ChatpublicStruct::hello() {


}