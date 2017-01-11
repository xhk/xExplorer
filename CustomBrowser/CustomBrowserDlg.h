// CustomBrowserDlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_CUSTOMBROWSERDLG_H__7BA59E70_8752_490B_BDA1_6F64843BE441__INCLUDED_)
#define AFX_CUSTOMBROWSERDLG_H__7BA59E70_8752_490B_BDA1_6F64843BE441__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CustomModalDialog.h"
#include "CustomModelessDialog.h"
#include "CustomWindow.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomBrowserDlg dialog

#define MAX_WINDOWS 100

class CCustomBrowserDlg : public CDialog
{
// Construction
public:
	struct ModalDialogInfo
	{
		CString cszURL;
		int nWidth;
		int nHeight;
		int nTop;
		int nLeft;
	};
	int nWindowCount;

	ModalDialogInfo strModalDialogInfo;

	CCustomWindow dlg[MAX_WINDOWS];
	CCustomModelessDialog dlgmodeless[MAX_WINDOWS];

	void CB_ShowModelessDialog(CString cszURL, int nLeft, int nTop, int nWidth, int nHeight);
	void CB_ShowModalDialog(CString cszURL, int nLeft, int nTop, int nWidth, int nHeight);
	void CB_OpenWindow(CString cszURL, int nLeft, int nTop, int nWidth, int nHeight, int nResizable);
	void CB_CustomFunctionWithParams(CString cszString, int nNumber);
	void CB_CustomFunction();
	void CB_Close();
	BOOL CB_IsOurCustomBrowser();
	CCustomBrowserDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomBrowserDlg)
	enum { IDD = IDD_CUSTOMBROWSER_DIALOG };
	CWebBrowser2	m_Browser;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomBrowserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCustomBrowserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMBROWSERDLG_H__7BA59E70_8752_490B_BDA1_6F64843BE441__INCLUDED_)
