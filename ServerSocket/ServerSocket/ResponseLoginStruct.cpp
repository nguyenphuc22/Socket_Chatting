#include "pch.h"
#include "ResponseLoginStruct.h"

ResponseLoginStruct::ResponseLoginStruct(bool isSecc, string error) {
	this->isSecc = isSecc;
	this->error = error;
}

ResponseLoginStruct::ResponseLoginStruct() {
	this->isSecc = false;
	this->error = "NULL";
}

ResponseLoginStruct::~ResponseLoginStruct() {
	delete this;
}

// override
vector<char> ResponseLoginStruct::pack() {
	vector<char> buf;

	buf.push_back((char)MessageType::responseLogin);

	buf.push_back((char)this->isSecc);
	for (int i = 0; i < this->error.length(); i++)
	{
		buf.push_back((char)this->error[i]);
	}
	return buf;
}
// override
void ResponseLoginStruct::unpack(vector<char> buff) {

	this->isSecc = (bool)buff[1];
	this->error.clear();
	for (int i = 2; i < buff.size(); i++)
	{
		this->error.push_back(buff[i]);
	}
}
// override test
void ResponseLoginStruct::hello() {

}