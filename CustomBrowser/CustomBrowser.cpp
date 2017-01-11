// CustomBrowser.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CustomBrowser.h"
#include "CustomBrowserDlg.h"

#include "afxpriv.h"
//#include <..\src\occimpl.h>
#include "CustSite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomBrowserApp

BEGIN_MESSAGE_MAP(CCustomBrowserApp, CWinApp)
	//{{AFX_MSG_MAP(CCustomBrowserApp)
	ON_COMMAND(ID_POPUP_ITEM1, OnPopupItem1)
	ON_COMMAND(ID_POPUP_ITEM2, OnPopupItem2)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomBrowserApp construction

CCustomBrowserApp::CCustomBrowserApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCustomBrowserApp object

CCustomBrowserApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCustomBrowserApp initialization

BOOL CCustomBrowserApp::InitInstance()
{
	
	CCustomOccManager *pMgr = new CCustomOccManager;

	// Create an IDispatch class for extending the Dynamic HTML Object Model 
	m_pDispOM = new CImpIDispatch;

	// Set our control containment up but using our control container 
	// management class instead of MFC's default
	AfxEnableControlContainer(pMgr);


	//AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCustomBrowserDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CCustomBrowserApp::OnPopupItem1() 
{
		// TODO: Add your command handler code here
		AfxMessageBox("Item 1");
}

void CCustomBrowserApp::OnPopupItem2() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("Item 2");
}
