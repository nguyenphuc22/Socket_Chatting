// ClientRegister.cpp : implementation file
//

#include "pch.h"
#include "ClientSocket.h"
#include "ClientRegister.h"
#include "afxdialogex.h"


// ClientRegister dialog

IMPLEMENT_DYNAMIC(ClientRegister, CDialogEx)

ClientRegister::ClientRegister(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENTSOCKET_Register, pParent)
	, m_strPassword(_T(""))
	, m_strUsername(_T(""))
	, m_strConfirmPassword(_T(""))
{

}

ClientRegister::~ClientRegister()
{
}

void ClientRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Password, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_Username, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_ConfirmPassword, m_strConfirmPassword);
}


BEGIN_MESSAGE_MAP(ClientRegister, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &ClientRegister::OnEnChangeEdit2)
END_MESSAGE_MAP()


// ClientRegister message handlers


void ClientRegister::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
