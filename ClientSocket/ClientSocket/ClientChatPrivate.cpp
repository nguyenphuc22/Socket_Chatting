// ClientChatPrivate.cpp : implementation file
//

#include "pch.h"
#include "ClientSocket.h"
#include "ClientChatPrivate.h"
#include "afxdialogex.h"


// ClientChatPrivate dialog

IMPLEMENT_DYNAMIC(ClientChatPrivate, CDialogEx)

ClientChatPrivate::ClientChatPrivate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ClientChatPrivate, pParent)
	, m_strMessage(_T(""))
{

}

ClientChatPrivate::~ClientChatPrivate()
{
}

void ClientChatPrivate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Message, m_strMessage);
	DDX_Control(pDX, IDC_LIST_Chatconference, ListChat);
}


BEGIN_MESSAGE_MAP(ClientChatPrivate, CDialogEx)
END_MESSAGE_MAP()


// ClientChatPrivate message handlers
