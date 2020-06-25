#pragma once


// ClientChatPrivate dialog

class ClientChatPrivate : public CDialogEx
{
	DECLARE_DYNAMIC(ClientChatPrivate)

public:
	ClientChatPrivate(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ClientChatPrivate();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ClientChatPrivate };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMessage;
	CListBox ListChat;
};
