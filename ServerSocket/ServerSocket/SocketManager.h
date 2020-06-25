#include <WinSock2.h>
#include <string.h>
#include <string>
#include "ManagerStruct.h"
#include <fstream>
#include "User.h"
#include <list>
using namespace std;

static class SocketManager {
public:
	
	string accountPath = "../database.txt";
	// helper
	bool checkLogin(string userName, string passWord, string& errorMsg);
	bool checkAccount(string username, string password, string& errorMsg);
	bool checkSignup(string username, string password, string& errorMsg);
	bool checkAccountExists(string username);
	bool addAnAccountToDatabase(string username, string password);
	bool loginfunc(string userName, string passWord, SOCKET& socket);
	void loginResponse(bool isSucc, string errorMsg, SOCKET& socket);

	void loginNoti(string userName, SOCKET& socket);
	void logoutNoti(string userName, SOCKET& socket);
	
	bool signupfunc(string userName, string passWord, SOCKET& socket);
	void signupResponse(bool isSucc, string errorMsg, SOCKET& socket);

	void UserOnline(list<User> sArray);

	void listenMessageFromClient(SOCKET& socket, vector<char> buf);

	static void addNewuser(User user);

	bool isUserOnline(string userName);

	void sendMessagepublic(string msg,SOCKET & socket);

	void sendMessageprivate(string userName, string msg ,SOCKET& socket);
};