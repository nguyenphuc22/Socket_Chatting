#include "pch.h"
#include "UserOnlineStruct.h"

//Contractor
UserOnlineStruct::UserOnlineStruct(list<User> userName) {
	for (list<User>::iterator it = userName.begin(); it != userName.end(); ++it)
	{
		this->userName.push_back(it->userName);
	}
}
UserOnlineStruct::UserOnlineStruct() {

}

UserOnlineStruct::~UserOnlineStruct() {
	delete this;
}
// override
vector<char> UserOnlineStruct::pack() {
	vector<char> buf;

	buf.push_back((char)MessageType::userStatus);

	for (int i = 0; i < this->userName.size(); i++)
	{
		for (int j = 0; j < this->userName[i].length(); j++) {
			buf.push_back((char)userName[i][j]);
		}
		buf.push_back('|');
	}
	return buf;
}
// override
void UserOnlineStruct::unpack(vector<char> buff) {

	string temp;
	for (int i = 1; i < buff.size(); i++)
	{
		if (buff[i] != '|')
		{
			temp.push_back(buff[i]);
		}
		else {
			this->userName.push_back(temp);
			temp.clear();
		}
	}

}
// override test
void UserOnlineStruct::hello() {

}