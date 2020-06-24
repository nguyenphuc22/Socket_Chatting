#include "pch.h"
#include "ServerManager.h"
#include "ServerSocket.h"
#include "ServerSOcketDlg.h"
#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <fstream>

static SOCKET sArray[100];
static int iCount;


ServerManager::ServerManager(CServerSocketDlg* dialog)
{
	m_pDialog = dialog;
}

void ServerManager::StartListening(int iPort) {
    iCount = 0;
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
        m_pDialog->ShowServerInfo("Could not create socket");
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(iPort);

    //Bind
    if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        m_pDialog->ShowServerInfo("Bind failed with error code");
        exit(EXIT_FAILURE);
    }
    // test
    m_pDialog->ShowServerInfo("Test Line 1");
    m_pDialog->ShowServerInfo("Test Line 2");
    m_pDialog->ShowServerInfo("Test Line 3");


    puts("Bind done");

    //Listen to incoming connections
    listen(s, 100);
    char* message;
    puts("Waiting for incoming connections...");
    m_pDialog->ShowServerInfo("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);

    while ((new_socket = accept(s, (struct sockaddr*)&client, &c)) != INVALID_SOCKET)
    {
        puts("Connection accepted");
        // m_pDialog->ShowServerInfo("Connection accepted\n");
         //Reply to the client
        socklen_t len;
        struct sockaddr_storage addr;
        char ipstr[INET6_ADDRSTRLEN];
        int port;

        len = sizeof addr;
        getpeername(new_socket, (struct sockaddr*)&addr, &len);

        // deal with IPv4:
        if (addr.ss_family == AF_INET) {
            struct sockaddr_in* s = (struct sockaddr_in*)&addr;
            port = ntohs(s->sin_port);
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
        }

        printf("Peer IP address: %s\n", ipstr);
        m_pDialog->ShowServerInfo("Connected Peer IP address: " + string(ipstr) + "\n");
        CWinThread* cTh = AfxBeginThread(
            DataThreadFunc,
            (LPVOID)new_socket);
        ++iCount;
        //m_Thread_handle[++iCount] = cTh->m_hThread;
        //cpTh[iCount] = cTh;
        sArray[iCount] = new_socket;
        //message = "Hello Client , I have received your connection.\n";
        //send(new_socket , message , strlen(message) , 0);

        //SetStaticVariable(iTempCount, new_socket);
    }

    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d", WSAGetLastError());
        return;
    }
}

ServerManager::~ServerManager()
{

	closesocket(s);
	WSACleanup();
}

UINT ServerManager::DataThreadFunc(LPVOID pParam) {
    SOCKET pYourSocket = reinterpret_cast<SOCKET>(pParam);
    //UINT retCode = pYourClass->ThreadFunc();
    //SendReceiveData(pYourClass);


    char* message;
    message = "Welcome to Matrix chat room.\n";
    send(pYourSocket, message, strlen(message), 0);
    char server_reply[2000];
    int recv_size;

    while ((recv_size = recv(pYourSocket, server_reply, 2000, 0)) != SOCKET_ERROR)
    {
        server_reply[recv_size] = '\0';
        //m_pDialog->ShowServerInfo("Message Received: "+ string(server_reply));
        for (int i = 1; i <= iCount; i++)
        {
            if (send(sArray[i], server_reply, recv_size, 0) < 0)
            {
                puts("Send failed");
                //return -1;
            }
        }

    }
    return 0;
}

void ServerManager::ClearServer() {

    closesocket(s);
    WSACleanup();

    /*
    for(int i=1;i<=iCount;++i)
    {
        DWORD dwCode;
        GetExitCodeThread(cpTh[i]->m_hThread, &dwCode);
        delete cpTh[i];
        //CloseHandle(m_Thread_handle[i]);
    }*/

}

UINT ServerManager::SendReceiveData(SOCKET cSocket)
{

    return 0;
}

void ServerManager::SetStaticVariable(int iC, SOCKET cS)
{
    iCount = iC;
    sArray[iCount] = cS;
}

bool ServerManager::signup(string userName, string passWord, SOCKET & socket) {

    string error = "";
    if (checkSignup(userName, passWord, error))
    {
        signupResponse(true, error, socket);

        //update client list

        return true;
    }
    // Signup Fail

    signupResponse(false, error, socket);


    return false;
}

void ServerManager::signupResponse(bool isSucc, string errorMsg, SOCKET & socket) {

    ResponseSignupStruct* responseSignupStruct = new ResponseSignupStruct(isSucc, errorMsg);

    vector<char> data = responseSignupStruct->pack();

    send(socket, &data[0], data.size(), 0);
}

bool ServerManager::checkLogin(string userName, string passWord, string& errorMsg) {
    // check empty
    if (userName.empty() || passWord.empty())
    {
        errorMsg = "Username or Password can't be blank!";
        return false;
    }

    if (!checkAccount(userName, passWord, errorMsg))
    {
        return false;
    }
    // not finish
    return true;
}
bool ServerManager::checkAccount(string username, string password, string& errorMsg) {

    ifstream fileInput(this->accountPath);

    if (fileInput.fail())
    {
        errorMsg = "Can't not open file database";
        return false;
    }
    string tmp, tmp1, tmp2;
    while (!fileInput.eof())
    {

        getline(fileInput, tmp);
        getline(fileInput, tmp1);
        tmp2 = username + password;

        if (tmp2 == (tmp1 + tmp))
        {
            return true;
        }
    }
    errorMsg = "Username or Password is not correct!";
    return false;
}
bool ServerManager::checkSignup(string username, string password, string& errorMsg) {

    // check empty
    if (username.empty() || password.empty())
    {
        errorMsg = "Username or Password can't be blank!";
        return false;
    }

    //Check exists username in database
    if (checkAccountExists(username))
    {
        errorMsg = "This username has been registered!";
        return false;
    }

    if (!addAnAccountToDatabase(username, password))
    {
        errorMsg = "Can't register!";
        return false;
    }


    return true;
}
bool ServerManager::checkAccountExists(string username) {

    ifstream fileInput(this->accountPath);

    if (fileInput.fail())
    {
        return false;
    }
    string tmp;
    while (!fileInput.eof())
    {
        getline(fileInput, tmp);

        if (tmp == username)
        {
            return true;
        }
        // skip line password
        getline(fileInput, tmp);
    }

    return false;
}
bool ServerManager::addAnAccountToDatabase(string username, string password) {
    // Mode write file the end postion
    ofstream fileOutput(this->accountPath, std::ios::app);

    if (fileOutput.fail())
    {
        return false;
    }

    fileOutput << username << endl;
    fileOutput << password << endl;

    fileOutput.close();

    return true;
}
