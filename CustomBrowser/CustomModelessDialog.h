//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_CUSTOMMODELESSDIALOG_H__5F0E91E0_61B4_4457_8E4B_0F7FD9BCD067__INCLUDED_)
#define AFX_CUSTOMMODELESSDIALOG_H__5F0E91E0_61B4_4457_8E4B_0F7FD9BCD067__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomModelessDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomModelessDialog dialog

class CCustomModelessDialog : public CDialog
{
// Construction
public:
	CString cszURL;
	HICON m_hIcon;
	CCustomModelessDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomModelessDialog)
	enum { IDD = IDD_MODELESS_DIALOG };
	CWebBrowser2	m_browser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomModelessDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomModelessDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMODELESSDIALOG_H__5F0E91E0_61B4_4457_8E4B_0F7FD9BCD067__INCLUDED_)
