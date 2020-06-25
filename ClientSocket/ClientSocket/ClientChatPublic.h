#pragma once


// ClientChatPublic dialog

class ClientChatPublic : public CDialogEx
{
	DECLARE_DYNAMIC(ClientChatPublic)

public:
	ClientChatPublic(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ClientChatPublic();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ClientChat };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnLbnSelchangeListChatconference();
	afx_msg void OnLbnSelchangeListFriends();
	CString m_strMessage;
	CString m_strUsername;
	CListBox ListChatconference;
	CListBox Listfriends;
};
