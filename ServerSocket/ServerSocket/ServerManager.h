#pragma once

#include<winsock2.h>
#include "ManagerStruct.h"
class CServerSocketDlg;

#pragma comment(lib,"ws2_32.lib")

class ServerManager {
public:	
	CServerSocketDlg* m_pDialog;
	UINT SendReceiveData(SOCKET cSocket);
	void ClearServer();
	static void SetStaticVariable(int iC, SOCKET cS);
	static UINT DataThreadFunc(LPVOID pParam);
	WSADATA wsa;
	SOCKET s, new_socket;
	//static SOCKET sArray[100];
	struct sockaddr_in server, client;
	int c;
	//static int iCount;
	int iTempCount;
	HANDLE m_Thread_handle[100];
	CWinThread* cpTh[100];

	ServerManager(CServerSocketDlg* dialog);
	~ServerManager(void);
	void StartListening(int iPort);

public:
	string accountPath = "../database.txt";
	// helper
	bool checkLogin(string userName, string passWord, string& errorMsg);
	bool checkAccount(string username, string password, string& errorMsg);
	bool checkSignup(string username, string password, string& errorMsg);
	bool checkAccountExists(string username);
	bool addAnAccountToDatabase(string username, string password);


	bool signup(string userName, string passWord, SOCKET & socket);
	void signupResponse(bool isSucc, string errorMsg, SOCKET & socket);

};