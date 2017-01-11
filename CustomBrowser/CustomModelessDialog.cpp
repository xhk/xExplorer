// CustomModelessDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CustomBrowser.h"
#include "CustomModelessDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomModelessDialog dialog


CCustomModelessDialog::CCustomModelessDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomModelessDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomModelessDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CCustomModelessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomModelessDialog)
	DDX_Control(pDX, IDC_EXPLORER1, m_browser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomModelessDialog, CDialog)
	//{{AFX_MSG_MAP(CCustomModelessDialog)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomModelessDialog message handlers

BOOL CCustomModelessDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomModelessDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(&rect);
	if(m_browser)
		m_browser.SetWindowPos(NULL,rect.left, rect.top, rect.Width(), rect.Height(), NULL);
	
}

void CCustomModelessDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	COleVariant vEmpty;
	COleVariant vURL;
	vURL = cszURL;
	if(m_browser)
		m_browser.Navigate2(vURL, vEmpty, vEmpty, vEmpty, vEmpty);	
	
}
