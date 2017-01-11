//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_CUSTOMMODALDIALOG_H__C93107E0_EDD1_4E10_B6BC_E3C6B4B99D2F__INCLUDED_)
#define AFX_CUSTOMMODALDIALOG_H__C93107E0_EDD1_4E10_B6BC_E3C6B4B99D2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomModalDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomModalDialog dialog

class CCustomModalDialog : public CDialog
{
// Construction
public:
	CString cszURL;
	HICON m_hIcon;
	CCustomModalDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomModalDialog)
	enum { IDD = IDD_MODAL_DIALOG };
	CWebBrowser2	m_browser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomModalDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomModalDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMODALDIALOG_H__C93107E0_EDD1_4E10_B6BC_E3C6B4B99D2F__INCLUDED_)
