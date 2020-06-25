
// ServerSocketDlg.h : header file
//

#pragma once
#include "ServerManager.h"
#include <Windows.h>
#include <string>
#include <string.h>

using namespace std;

// CServerSocketDlg dialog
class CServerSocketDlg : public CDialogEx
{
// Construction
public:
	CServerSocketDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERSOCKET_DIALOG };
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
	CEdit edt_val_port;
	CButton btn_val_listen;
	static UINT StaticThreadFunc(LPVOID pParam);
	UINT ThreadFunc();
	ServerManager * server;
private:
	HANDLE m_Thread_handle;
	CWinThread* cTh;
public:
	afx_msg void OnBnClickedButtonListen();
	CEdit edt_val_username;
	CEdit edt_val_password;
	CEdit edt_val_chat;
	void ShowServerInfo(string sValue);
	//void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);
	afx_msg void OnEnChangeEditChat();
	afx_msg void OnLbnSelchangeListNotifications();
	CListBox list_val_notifi;
	afx_msg void OnEnChangeEditPort();
	afx_msg void OnBnClickedOk();
};
