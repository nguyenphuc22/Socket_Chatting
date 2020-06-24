#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include "eManager.h"
using namespace std;
// ChatStruct is abstract class
class ChatStruct {

public:
	MessageType mesageType;

	virtual vector<char> pack() = 0;

	virtual void unpack(vector<char> buff) = 0;

	virtual void hello() = 0;
};