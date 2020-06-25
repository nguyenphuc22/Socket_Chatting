
// ClientSocketDlg.h : header file
//

#pragma once
#include <Windows.h>
#include <string>
#include "ClientManager.h"
#include "resource.h"

using namespace std;

// CClientSocketDlg dialog
class CClientSocketDlg : public CDialogEx
{
// Construction
public:
	CClientSocketDlg(CWnd* pParent = nullptr);	// standard constructor
	void ShowServerInfo(string sValue);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENTSOCKET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit edt_val_username;
	CEdit edt_val_password;
	CButton btn_val_login;
	CButton btn_val_signup;
	afx_msg void OnBnClickedButtonSignup();

	ClientManager * m_pClient;

	static UINT StaticThreadFunc(LPVOID pParam);
	UINT ThreadFunc();
	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);
	CEdit m_Portbox;
	void AppString(string msg);
	void AppStringOnline(string msg);
	void DeleteStringListBox(string userName);
	void AppStringComboBox(string msg);
private:
	HANDLE m_Thread_handle;
	CWinThread* cTh;
public:
	CEdit edt_val_port;
	afx_msg void OnBnClickedButtonLogin();
	CListBox chatbox_val;
	CListBox listonline_val;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSend();
	CEdit edt_val_message;
	CComboBox combo_val_chat;
	afx_msg void OnCbnSelchangeCombo1();
};
