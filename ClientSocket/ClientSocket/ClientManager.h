#pragma once

#include "string.h"
#include "string"
#include<winsock2.h>
#include "Ws2tcpip.h"
#include <WS2tcpip.h>

using namespace std;

class CClientSocketDlg;

class ClientManager {

public:
	ClientManager(CClientSocketDlg * dlg);
	~ClientManager(void);
	void StartConnect(string sAddress, int iPort, string sUsername,string sPassword);
	void SendData(string sMessage);


	WSADATA wsa;
	SOCKET s;
	CClientSocketDlg * m_pdialog;
	string m_pUser;

};