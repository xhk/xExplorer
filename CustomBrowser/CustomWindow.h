//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_CUSTOMWINDOW_H__11EDF572_9AE1_4BB6_9C0C_33D608081866__INCLUDED_)
#define AFX_CUSTOMWINDOW_H__11EDF572_9AE1_4BB6_9C0C_33D608081866__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomWindow dialog

class CCustomWindow : public CDialog
{
// Construction
public:
	CCustomWindow(CWnd* pParent = NULL);   // standard constructor
	CString cszURL;
	HICON m_hIcon;

// Dialog Data
	//{{AFX_DATA(CCustomWindow)
	enum { IDD = IDD_WINDOW };
	CWebBrowser2	m_browser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomWindow)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMWINDOW_H__11EDF572_9AE1_4BB6_9C0C_33D608081866__INCLUDED_)
