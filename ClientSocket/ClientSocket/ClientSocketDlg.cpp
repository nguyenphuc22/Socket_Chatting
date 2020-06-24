
// ClientSocketDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ClientSocket.h"
#include "ClientSocketDlg.h"
#include "afxdialogex.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientSocketDlg dialog



CClientSocketDlg::CClientSocketDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENTSOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Username, edt_val_username);
	DDX_Control(pDX, IDC_EDIT_Password, edt_val_password);
	DDX_Control(pDX, IDC_BUTTON_Login, btn_val_login);
	DDX_Control(pDX, IDC_BUTTON_Signup, btn_val_signup);
	DDX_Control(pDX, IDC_EDIT_Port, edt_val_port);
}

BEGIN_MESSAGE_MAP(CClientSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Signup, &CClientSocketDlg::OnBnClickedButtonSignup)
END_MESSAGE_MAP()


// CClientSocketDlg message handlers

BOOL CClientSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientSocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientSocketDlg::ShowServerInfo(string sValue) {
	CString strLine(sValue.c_str());
	// add CR/LF to text
	//MessageBox(sValue.c_str());
	//AppendTextToEditCtrl(, strLine);
	//DoModal();
	//UpdateData(TRUE);
}

void CClientSocketDlg::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.ReplaceSel(pszText);
}

void CClientSocketDlg::OnBnClickedButtonSignup()
{
	cTh = AfxBeginThread(
		StaticThreadFunc,
		this);

	//cTh->m_bAutoDelete = FALSE;
	m_Thread_handle = cTh->m_hThread;
}

UINT CClientSocketDlg::ThreadFunc() {

	// Do your thing, this thread now has access to all the classes member variables


	CString txtname;

	edt_val_username.GetWindowTextW(txtname);


	CString txtpassword;

	edt_val_password.GetWindowTextW(txtpassword);

	CString portname;
	edt_val_port.GetWindowTextW(portname);

	int iPort = _ttoi(portname);

	m_pClient = new ClientManager(this);

	CT2CA CStringToAscii(txtname);

	// construct a std::string using the LPCSTR input
	std::string sResultedString(CStringToAscii);

	CT2CA CStringToAscii2(txtpassword);

	std::string sResultedString2(CStringToAscii2);

	m_pClient->StartConnect("127.0.0.1", iPort, sResultedString,sResultedString2);
	return 0;

}

UINT CClientSocketDlg::StaticThreadFunc(LPVOID pParam)
{
	CClientSocketDlg* pYourClass = reinterpret_cast<CClientSocketDlg*>(pParam);
	UINT retCode = pYourClass->ThreadFunc();

	return retCode;
}
