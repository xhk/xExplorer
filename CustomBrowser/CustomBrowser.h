// CustomBrowser.h : main header file for the CUSTOMBROWSER application
//

#if !defined(AFX_CUSTOMBROWSER_H__2FF7439C_5CF1_4AC0_9F42_FA1E3C5CAF52__INCLUDED_)
#define AFX_CUSTOMBROWSER_H__2FF7439C_5CF1_4AC0_9F42_FA1E3C5CAF52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCustomBrowserApp:
// See CustomBrowser.cpp for the implementation of this class
//

class CCustomBrowserApp : public CWinApp
{
public:
	CCustomBrowserApp();
	class CImpIDispatch* m_pDispOM;
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomBrowserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCustomBrowserApp)
	afx_msg void OnPopupItem1();
	afx_msg void OnPopupItem2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMBROWSER_H__2FF7439C_5CF1_4AC0_9F42_FA1E3C5CAF52__INCLUDED_)
extern CCustomBrowserApp theApp;