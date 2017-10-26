
// ShoppingSoftDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShoppingSoft.h"
#include "ShoppingSoftDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShoppingSoftDlg dialog




CShoppingSoftDlg::CShoppingSoftDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShoppingSoftDlg::IDD, pParent),
	  loginService(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShoppingSoftDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USERNAME, edtUsername);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, edtPassword);
	DDX_Control(pDX, IDC_BTN_LOGOUT, edtLogout);
	DDX_Control(pDX, IDC_CMB_TRANSFER_TYPE, cmbTransferType);
}

BEGIN_MESSAGE_MAP(CShoppingSoftDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CShoppingSoftDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, &CShoppingSoftDlg::OnBnClickedBtnLogout)
END_MESSAGE_MAP()


// CShoppingSoftDlg message handlers

BOOL CShoppingSoftDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	//!添加其它初始化代码
	//!1>初始化下拉框，可选传输类型为：http、https、socket三种类型
	if (cmbTransferType.GetCount() > 0)
	{
		cmbTransferType.ResetContent();
	}
	else
	{
		cmbTransferType.AddString("HTTP");
		cmbTransferType.AddString("HTTPS");
		cmbTransferType.AddString("SOCKET");
		cmbTransferType.SetCurSel(0);
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShoppingSoftDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShoppingSoftDlg::OnPaint()
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
HCURSOR CShoppingSoftDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShoppingSoftDlg::OnBnClickedBtnLogin()
{
	// TODO: Add your control notification handler code here
	
	//!获取用户名和密码
	CString strUsername;
	CString strPassword;
	GetDlgItemText(IDC_EDIT_USERNAME, strUsername);
	GetDlgItemText(IDC_EDIT_PASSWORD, strPassword);

	do 
	{
		if(strUsername.IsEmpty() || strPassword.IsEmpty())
		{
			MessageBox(_T("用户名或密码不能为空!"), _T("友情提示"), MB_OK);
			break;
		}

		//!生成登录类，实现登录
		loginService = new LoginService(strUsername.GetBuffer(0), strPassword.GetBuffer(0));

		if(!loginService->Login())
		{
			MessageBox(_T("登录失败，请重新登陆!"), _T("友情提示"), MB_OK);
			break;
		}
		else
		{
			MessageBox(_T("登录成功!"), _T("友情提示"), MB_OK);
		}
	} while (FALSE);

}


void CShoppingSoftDlg::OnBnClickedBtnLogout()
{
	// TODO: Add your control notification handler code here
	if (!loginService->Logout())
	{
		MessageBox(_T("无法正常退出，请重新尝试!"), _T("友情提示"), MB_OK);
	}
	else
	{
		MessageBox(_T("已安全退出!"), _T("友情提示"), MB_OK);
	}
}
