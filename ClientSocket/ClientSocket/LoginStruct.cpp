#include "pch.h"
#include "LoginStruct.h"

void LoginStruct::hello() {

	cout << "Hello World" << endl;

}
// implement contructor login
LoginStruct::LoginStruct(string userName, string passWord) {

	this->userName = userName;

	this->passWord = passWord;

}
// implement contructor login : hard set , userName = "Nick" , passWord = "Nick"
LoginStruct::LoginStruct() {

	this->userName = "Nick";

	this->passWord = "Nick";

}
// implement decontructor login delete memory
LoginStruct::~LoginStruct() {

	delete this;

}
// First place in array save mode pack . 
// Parse parse string userName and string passWord to vector char
vector<char> LoginStruct::pack() {

	vector<char> data;

	//Save First place is mode pack
	data.push_back((char)MessageType::login);

	// Parse string userName to vector char
	for (int i = 0; i < this->userName.length(); i++)
	{

		data.push_back(this->userName[i]);

	}

	// End string userName
	data.push_back(' ');

	// Parse string passWord to vector char
	for (int i = 0; i < this->passWord.length(); i++)
	{

		data.push_back(passWord[i]);

	}

	// End string passWord
	data.push_back(' ');
	return data;
}
// skip 1 first place . Because it's for ManagerStruct
// Parse string userName
// Parse string passWord
void LoginStruct::unpack(vector<char> buff) {
	this->userName.clear();
	this->passWord.clear();
	if (buff.size() > 0)
	{
		int i = 1;
		for (; i < buff.size() &&
			buff[i] != ' '
			; i++)
		{
			this->userName.push_back(buff[i]);
		}

		//skip 1 step 
		i++;
		for (; i < buff.size() &&
			buff[i] != ' '
			; i++)
		{
			this->passWord.push_back(buff[i]);
		}
	}
}