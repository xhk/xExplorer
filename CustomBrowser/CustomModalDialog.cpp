// CustomModalDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CustomBrowser.h"
#include "CustomBrowserDlg.h"
#include "CustomModalDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomModalDialog dialog


CCustomModalDialog::CCustomModalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomModalDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomModalDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CCustomModalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomModalDialog)
	DDX_Control(pDX, IDC_EXPLORER1, m_browser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomModalDialog, CDialog)
	//{{AFX_MSG_MAP(CCustomModalDialog)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomModalDialog message handlers

BOOL CCustomModalDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CCustomBrowserDlg* pParent = (CCustomBrowserDlg*)GetParent();

	cszURL = pParent->strModalDialogInfo.cszURL;
	SetWindowPos(NULL, pParent->strModalDialogInfo.nLeft, pParent->strModalDialogInfo.nTop, pParent->strModalDialogInfo.nWidth, pParent->strModalDialogInfo.nHeight, NULL);
	COleVariant vEmpty;
	COleVariant vURL;
	vURL = cszURL;

	if(m_browser)
		m_browser.Navigate2(vURL, vEmpty, vEmpty, vEmpty, vEmpty);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomModalDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(&rect);
	if(m_browser)
		m_browser.SetWindowPos(NULL,rect.left, rect.top, rect.Width(), rect.Height(), NULL);	
}
