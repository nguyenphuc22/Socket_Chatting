#pragma once

#include "string.h"
#include "string"
#include<winsock2.h>
#include "Ws2tcpip.h"
#include <WS2tcpip.h>
#include <vector>
#include "ManagerStruct.h"

using namespace std;

class CClientSocketDlg;

class ClientManager {

public:
	ClientManager(CClientSocketDlg * dlg);
	~ClientManager(void);
	void StartConnect(string sAddress, int iPort, string sUsername,string sPassword);
	void SendData(string sMessage);

	void listenMessageFromServer(SOCKET& socket, vector<char> buf);

	bool signupfunc(string userName, string passWord, SOCKET& socket);

	bool Responsesignupfunc(bool isSucc, string msgError);

	bool loginfunc(string userName, string passWord, SOCKET& socket);

	bool ResponseLoginfunc(bool isSucc, string msgError);

	void loginNoti(string userName);

	void logoutNoti(string userName,SOCKET & socket);
	void logout(string userName);

	void publicmessage(string userName, SOCKET & socket);

	void addListboxOnline(vector<string> sArray);

	void listenpublicmessage(string msg);

	void privatemessage(string userName,string msg, SOCKET& socket);

	void listenprivatemessage(string msg);
	WSADATA wsa;
	SOCKET s;
	CClientSocketDlg * m_pdialog;
	
	string m_pUser;

};