#include "pch.h"
#include "ServerManager.h"
#include "ServerSocket.h"
#include "ServerSOcketDlg.h"
#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <fstream>
#include <list>
static SOCKET sArray[100];

static int iCount;
//static list<User> sArray;


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

     
       
        User new_user;
        new_user.socket = new_socket;
        SocketManager::addNewuser(new_user);

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
    
    int recv_size;
    vector<char> buf(4096);

        while ((recv_size = recv(pYourSocket, &buf[0], buf.size(), 0)) != SOCKET_ERROR)
    {
        //server_reply[recv_size] = '\0';
        
        SocketManager socketManager;

        socketManager.listenMessageFromClient(pYourSocket,buf);
     
        for (int i = 0; i < recv_size; i++)
        {
            buf[i] = ' ';
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

/*
void ServerManager::SetStaticVariable(int iC, SOCKET cS)
{
    iCount = iC;
    sArray[iCount] = cS;
}
*/
