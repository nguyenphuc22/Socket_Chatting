#include "pch.h"
#include "ResponseSignupStruct.h"

ResponseSignupStruct::ResponseSignupStruct(bool isSecc, string error) {
	this->isSecc = isSecc;
	this->error = error;
}

ResponseSignupStruct::ResponseSignupStruct() {
	this->isSecc = false;
	this->error = "Can't Signup";
}

ResponseSignupStruct::~ResponseSignupStruct() {
	delete this;
}

// override
// first place for save status mode pack
// second place for save is seccuss
// parse string error.
vector<char> ResponseSignupStruct::pack() {
	vector<char> data;

	data.push_back((char)MessageType::responseSignup);

	data.push_back((char)this->isSecc);
	for (int i = 0; i < this->error.length(); i++)
	{
		data.push_back((char)this->error[i]);
	}

	return data;
}
// override
// skip first place
void ResponseSignupStruct::unpack(vector<char> buff) {

	this->isSecc = (bool)buff[1];
	this->error.clear();
	for (int i = 2; i < buff.size(); i++)
	{
		this->error.push_back(buff[i]);
	}
}
// override test
void ResponseSignupStruct::hello() {

}