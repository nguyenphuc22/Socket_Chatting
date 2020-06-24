
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
    char* message, server_reply[2000];
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
        return;
    }

    puts("Connected");

    //Send some data
    //message = "GET / HTTP/1.1\r\n\r\n";
   /*

    puts("Data Send\n");
     */
     //Receive a reply from the server
    while ((recv_size = recv(s, server_reply, 2000, 0)) != SOCKET_ERROR)
    {
        puts("Reply received\n");

        //Add a NULL terminating character to make it a proper string before printing
        server_reply[recv_size] = '\0';
        puts(server_reply);

        string sTempMsg = "\n" + string(server_reply) + "\n";
        m_pdialog->ShowServerInfo(sTempMsg);
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