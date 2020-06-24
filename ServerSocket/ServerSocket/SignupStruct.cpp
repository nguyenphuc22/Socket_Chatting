#include "pch.h"
#include "SignupStruct.h"
// implement Contructor Signup
SignupStruct::SignupStruct(string userName, string passWord) {
	this->userName = userName;

	this->passWord = passWord;
}
// implement Contructor Signup hard set userName and passWord
SignupStruct::SignupStruct() {
	this->userName = "Nick";
	this->passWord = "Nick";
}

SignupStruct::~SignupStruct() {

	delete this;

}
// first place in array save status mode 
// parse string userName to char in vector
// parse string passWord to char in vector
vector<char> SignupStruct::pack() {
	vector<char> data;

	data.push_back((char)MessageType::signup);

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

void SignupStruct::unpack(vector<char> buff) {

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

void SignupStruct::hello() {

	cout << this->userName << endl;

	cout << this->passWord << endl;

}