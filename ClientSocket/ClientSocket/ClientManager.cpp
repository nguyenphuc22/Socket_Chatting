
#include "pch.h"
#include "ClientManager.h"
#include <stdio.h>
#include <string.h>
#include "ClientSocketDlg.h"


#pragma comment(lib,"Ws2_32.lib") //Winsock Library

ClientManager::ClientManager(CClientSocketDlg* pdialog) {

    this->m_pdialog = pdialog;

}


ClientManager::~ClientManager(void)
{
    closesocket(s);
    WSACleanup();
}

void ClientManager::StartConnect(string sAddress, int iPort, string sUsername , string sPassword)
{
    struct sockaddr_in server;
    vector<char> data(4096);
    int recv_size;
    m_pUser = sUsername;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return;
    }

    printf("Initialised.\n");

    //Create a socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");
    CString address(sAddress.c_str(), sAddress.length());
    InetPton(AF_INET, address, &server.sin_addr.s_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(iPort);

    //Connect to remote server
    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        puts("connect error");
        this->m_pdialog->MessageBox(_T("Please wait server run and restart app!"));
        return;
    }

    puts("Connected");

    //Send some data
    //message = "GET / HTTP/1.1\r\n\r\n";
   /*

    puts("Data Send\n");
     */
    
    

     //Receive a reply from the server
    while ((recv_size = recv(s, &data[0], data.size(), 0)) != SOCKET_ERROR)
    {

        listenMessageFromServer(s,data);
        
        for (int i = 0; i < recv_size;i++) {
            data[i] = ' ';
        }
        
    }

}

void ClientManager::SendData(string sMessage)
{
    string sTemp = m_pUser + ">>" + sMessage + "\n";

    if (send(s, sTemp.c_str(), sTemp.size(), 0) < 0)
    {
        puts("Send failed");
        return;
    }
}


void ClientManager::listenMessageFromServer(SOCKET& socket, vector<char> buf) {

    //vector<char> buf(4096);

    //int recved = recv(socket, &buf[0], buf.size(), 0);

    ChatStruct* msgReceived = ManagerStruct::unpack(buf);



    switch (msgReceived->mesageType)
    {
    case publicMessage:
    {
        ChatpublicStruct* chatpublic = (ChatpublicStruct*)msgReceived;

        this->listenpublicmessage(chatpublic->userName);

        break;
    }
    case privateMessage:
    {
        ChatprivateStruct* chatpublic = (ChatprivateStruct*)msgReceived;

        this->listenprivatemessage(chatpublic->msg);

        break;
    }
    case privateFile:
        break;
    case userStatus:
    {
        UserOnlineStruct* userStruct = (UserOnlineStruct*)msgReceived;

        this->addListboxOnline(userStruct->userName);

        break;
    }
    case requestSendFile:
        break;
    case responseSendFile:
        break;
    case login:
    {
        LoginStruct* loginStruct = (LoginStruct*)msgReceived;

        this->loginfunc(loginStruct->userName, loginStruct->passWord, socket);

        break;
    }
    case responseLogin:
    {
        ResponseLoginStruct* responseLoginStruct = (ResponseLoginStruct *)msgReceived;

        this->ResponseLoginfunc(responseLoginStruct->isSecc, responseLoginStruct->error);

        break;
    }
    case signup:
    {
        SignupStruct* signupStruct = (SignupStruct*)msgReceived;

        this->signupfunc(signupStruct->userName, signupStruct->passWord, socket);

        break;
    }
    case responseSignup:
    {
        ResponseSignupStruct* reponseStruct = (ResponseSignupStruct*)msgReceived;

        this->Responsesignupfunc(reponseStruct->isSecc, reponseStruct->error);
        
        break;
    }
    case loginNotification:
    {
        LoginNotification* loginNotification = (LoginNotification*)msgReceived;

        this->loginNoti(loginNotification->userName);

        break;
    }
    case logoutNotification: {

        LogoutStruct* logout = (LogoutStruct*)msgReceived;

        this->logout(logout->userName);

        break;
    }
        
    default:
        break;
    }
}

bool ClientManager::signupfunc(string userName, string passWord, SOCKET& socket) {

    if (userName.empty() || passWord.empty()) {
        
        return false;
    
    }
    else {

        //this->m_pdialog->MessageBox(_T("Show top view"), _T("Infomation"), MB_YESNOCANCEL | MB_ICONWARNING);

        SignupStruct* signupStruct = new SignupStruct(userName,passWord);

        vector<char> data = signupStruct->pack();
        
        send(socket, &data[0], data.size(), 0);

        
    }
    return true;
}

bool ClientManager::Responsesignupfunc(bool isSucc, string msgError) {

    CString msg(msgError.c_str(), msgError.length());

    this->m_pdialog->MessageBox(msg, _T("Infomation"));

    if (isSucc)
    {
        return true;
        this->m_pdialog;
    }
    else {
        return false;
    }

}

bool ClientManager::loginfunc(string userName, string passWord, SOCKET& socket) {
    
    if (userName.empty() || passWord.empty()) {

        return false;

    }
    else {

        LoginStruct* login;

        login = new LoginStruct(userName, passWord);

        vector<char> buf = login->pack();

        send(socket, &buf[0], buf.size(), 0);
        
        return true;
    }
}

bool ClientManager::ResponseLoginfunc(bool isSucc, string msgError) {

    CString msg(msgError.c_str(), msgError.length());

    this->m_pdialog->MessageBox(msg, _T("Infomation"));

    if (isSucc)
    {
        this->m_pdialog->AppString("welcome to chat room");
        return true;
    }
    else {
        return false;
    }

}

void ClientManager::loginNoti(string userName) {

    if (!userName.empty())
    {
        userName.append(" Has login.");
        this->m_pdialog->AppString(userName);
    }
}

void ClientManager::addListboxOnline(vector<string> sArray) {

    int count = this->m_pdialog->listonline_val.GetCount();

    this->m_pdialog->listonline_val.ResetContent();
    
    this->m_pdialog->combo_val_chat.ResetContent();

    this->m_pdialog->AppStringComboBox("Public");

    this->m_pdialog->combo_val_chat.SetCurSel(0);

    for (int i = 0; i < sArray.size(); i++)
    {
        this->m_pdialog->AppStringOnline(sArray[i]);
        this->m_pdialog->AppStringComboBox(sArray[i]);
    }
    
}

void ClientManager::logoutNoti(string userName,SOCKET & socket) {
    
    LogoutStruct* logout = new LogoutStruct(userName);

    vector<char> buf = logout->pack();

    send(socket, &buf[0], buf.size(), 0);

}

void ClientManager::logout(string userName) {
   
    this->m_pdialog->DeleteStringListBox(userName);

    this->m_pdialog->AppString(userName + " Has logout!");

}

void ClientManager::publicmessage(string userName, SOCKET& socket) {

    ChatpublicStruct * logout = new ChatpublicStruct(userName);

    vector<char> buf = logout->pack();

    send(socket, &buf[0], buf.size(), 0);

}

void ClientManager::listenpublicmessage(string msg) {

    this->m_pdialog->AppString(msg);

}

void ClientManager::privatemessage(string userName,string msg, SOCKET& socket) {

    ChatprivateStruct * logout = new ChatprivateStruct(userName,msg);

    vector<char> buf = logout->pack();

    send(socket, &buf[0], buf.size(), 0);

}

void ClientManager::listenprivatemessage(string msg) {

    this->m_pdialog->AppString(msg);

}
