// ClientChatPublic.cpp : implementation file
//

#include "pch.h"
#include "ClientSocket.h"
#include "ClientChatPublic.h"
#include "afxdialogex.h"
#include "ClientChatPrivate.h"

// ClientChatPublic dialog

IMPLEMENT_DYNAMIC(ClientChatPublic, CDialogEx)

ClientChatPublic::ClientChatPublic(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ClientChat, pParent)
	, m_strMessage(_T(""))
	, m_strUsername(_T(""))
{

}

ClientChatPublic::~ClientChatPublic()
{
}

void ClientChatPublic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Message, m_strMessage);
	DDX_Text(pDX, IDC_EDIT_Username, m_strUsername);
	DDX_Control(pDX, IDC_LIST_Chatconference, ListChatconference);
	DDX_Control(pDX, IDC_LIST_Friends, Listfriends);
}


BEGIN_MESSAGE_MAP(ClientChatPublic, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Send, &ClientChatPublic::OnBnClickedButtonSend)
	ON_LBN_SELCHANGE(IDC_LIST_Chatconference, &ClientChatPublic::OnLbnSelchangeListChatconference)
	ON_LBN_SELCHANGE(IDC_LIST_Friends, &ClientChatPublic::OnLbnSelchangeListFriends)
END_MESSAGE_MAP()


// ClientChatPublic message handlers


void ClientChatPublic::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	ListChatconference.AddString(m_strMessage);
	Listfriends.AddString(m_strMessage);
	UpdateData(false);
}


void ClientChatPublic::OnLbnSelchangeListChatconference()
{
	// TODO: Add your control notification handler code here
	int index;
	index = ListChatconference.GetCurSel();
	if (index != LB_ERR) {

	}
}


void ClientChatPublic::OnLbnSelchangeListFriends()
{
	// TODO: Add your control notification handler code here
	int index;
	index = Listfriends.GetCurSel();
	if (index != LB_ERR) {
		ClientChatPrivate clientchatprivate;
		clientchatprivate.DoModal();
	}
}
