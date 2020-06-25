#pragma once


// ClientRegister dialog

class ClientRegister : public CDialogEx
{
	DECLARE_DYNAMIC(ClientRegister)

public:
	ClientRegister(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ClientRegister();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENTSOCKET_Register };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	CString m_strPassword;
	CString m_strUsername;
	CString m_strConfirmPassword;
};
