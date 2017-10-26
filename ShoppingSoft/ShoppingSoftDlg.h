
// ShoppingSoftDlg.h : header file
//

#pragma once

#include "LoginService.h"
#include "afxwin.h"

// CShoppingSoftDlg dialog
class CShoppingSoftDlg : public CDialogEx
{
// Construction
public:
	CShoppingSoftDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SHOPPINGSOFT_DIALOG };

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
	afx_msg void OnBnClickedBtnLogin();

public:
	LoginService *loginService;
	CEdit edtUsername;
	CEdit edtPassword;
	CButton edtLogout;
	afx_msg void OnBnClickedBtnLogout();
	CComboBox cmbTransferType;
};
