
// ServerSocketDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ServerSocket.h"
#include "ServerSocketDlg.h"
#include "afxdialogex.h"

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


// CServerSocketDlg dialog



CServerSocketDlg::CServerSocketDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVERSOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, btn_val_listen);
	DDX_Control(pDX, IDC_LIST_Notifications, list_val_notifi);
}

BEGIN_MESSAGE_MAP(CServerSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CServerSocketDlg::OnBnClickedButtonListen)
	ON_EN_CHANGE(IDC_EDIT_Chat, &CServerSocketDlg::OnEnChangeEditChat)
	ON_LBN_SELCHANGE(IDC_LIST_Notifications, &CServerSocketDlg::OnLbnSelchangeListNotifications)
	ON_EN_CHANGE(IDC_EDIT_PORT, &CServerSocketDlg::OnEnChangeEditPort)
	ON_BN_CLICKED(IDOK, &CServerSocketDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CServerSocketDlg message handlers

BOOL CServerSocketDlg::OnInitDialog()
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

void CServerSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerSocketDlg::OnPaint()
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
HCURSOR CServerSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CServerSocketDlg::ThreadFunc() {
	// Do your thing, this thread now has access to all the classes member variables

	int iPort = 6666;

	if (iPort == 0)
	{
		return -1;
	}
	server = new ServerManager(this);

	server->StartListening(iPort);
	return 0;
}

UINT CServerSocketDlg::StaticThreadFunc(LPVOID pParam) {
	
	CServerSocketDlg * pCServerSocketDlg = reinterpret_cast<CServerSocketDlg*>(pParam);
	
	UINT retCode = pCServerSocketDlg->ThreadFunc();

	return retCode;

}


void CServerSocketDlg::OnBnClickedButtonListen()
{
	cTh = AfxBeginThread(
		StaticThreadFunc,
		this);

	//cTh->m_bAutoDelete = FALSE;
	m_Thread_handle = cTh->m_hThread;
}

void CServerSocketDlg::ShowServerInfo(string sValue) {
	sValue.append("\n");
	CString strLine(sValue.c_str(), sValue.length());
	list_val_notifi.AddString(strLine);
	// add CR/LF to text
	//MessageBox(sValue.c_str());
	//DoModal();
	//UpdateData(TRUE);

}



void CServerSocketDlg::OnEnChangeEditChat()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CServerSocketDlg::OnLbnSelchangeListNotifications()
{
	// TODO: Add your control notification handler code here
	int index;
	index = list_val_notifi.GetCurSel();
	if (index != LB_ERR) {
		//AfxMessageBox("111");
	}
}


void CServerSocketDlg::OnEnChangeEditPort()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CServerSocketDlg::OnBnClickedOk()
{
	this->server->socketManager.logoutNoti("Server Out", this->server->s);

	CloseHandle(m_Thread_handle);

	delete server;
}
