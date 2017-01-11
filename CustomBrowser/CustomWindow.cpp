// CustomWindow.cpp : implementation file
//

#include "stdafx.h"
#include "CustomBrowser.h"
#include "CustomWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomWindow dialog


CCustomWindow::CCustomWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomWindow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CCustomWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomWindow)
	DDX_Control(pDX, IDC_EXPLORER1, m_browser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomWindow, CDialog)
	//{{AFX_MSG_MAP(CCustomWindow)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomWindow message handlers

void CCustomWindow::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(&rect);
	if(m_browser)
		m_browser.SetWindowPos(NULL,rect.left, rect.top, rect.Width(), rect.Height(), NULL);
	
}

void CCustomWindow::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	COleVariant vEmpty;
	COleVariant vURL;
	vURL = cszURL;
	if(m_browser)
		m_browser.Navigate2(vURL, vEmpty, vEmpty, vEmpty, vEmpty);		
}

BOOL CCustomWindow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
