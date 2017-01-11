// CustomBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomBrowser.h"
#include "CustomBrowserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomBrowserDlg dialog

CCustomBrowserDlg::CCustomBrowserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomBrowserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomBrowserDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nWindowCount = 0;
	strModalDialogInfo.nWidth=0;
	strModalDialogInfo.nHeight = 0;
	strModalDialogInfo.nLeft = 0;
	strModalDialogInfo.nTop = 0;
}

void CCustomBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomBrowserDlg)
	DDX_Control(pDX, IDC_EXPLORER1, m_Browser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCustomBrowserDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomBrowserDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomBrowserDlg message handlers

BOOL CCustomBrowserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(1,1,1,1);
	m_Browser.SetWindowPos(NULL,rect.left, rect.top, rect.Width(), rect.Height(),NULL);
	

	//Get Current Path of exe
	CString cszFullFileName;
	GetModuleFileName ( AfxGetInstanceHandle ( ), cszFullFileName.GetBuffer( MAX_PATH ), MAX_PATH ) ;
	cszFullFileName.ReleaseBuffer();
	cszFullFileName = cszFullFileName.Left ( cszFullFileName.ReverseFind ( '\\' ) ) ;


	COleVariant varEmpty;
	COleVariant varURL(cszFullFileName + "\\CustomTest.html");
	m_Browser.Navigate2(varURL, varEmpty,varEmpty,varEmpty,varEmpty);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomBrowserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCustomBrowserDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCustomBrowserDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCustomBrowserDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(1,1,1,1);
	if(m_Browser)
		m_Browser.SetWindowPos(NULL,rect.left, rect.top, rect.Width(), rect.Height(),NULL);
}

BOOL CCustomBrowserDlg::CB_IsOurCustomBrowser()
{
	//return true because this is obviously our
	//custom browser
	return TRUE;
}

void CCustomBrowserDlg::CB_Close()
{
	//AfxMessageBox("Close the browser here or the current window");

	//This is one way you can determine whether or not
	//to close a dialog or the main application depending
	//on if you call the CB_Close method from an html page
	//in a dialog/window or from an html page in the main app
	
	
	CWnd* pWnd = GetActiveWindow();

	if(pWnd == this)
	{
		
		EndDialog(0);
	}
	else
	{
		CDialog* pWin = (CDialog*)pWnd;
		pWin->EndDialog(1);
	}
	
}

void CCustomBrowserDlg::CB_CustomFunction()
{

	AfxMessageBox("Do whatever you like here!");
}

void CCustomBrowserDlg::CB_CustomFunctionWithParams(CString cszString, int nNumber)
{
	CString cszParameters;
	cszParameters.Format("parameter 1: %s\nparameter 2:  %d", cszString, nNumber);
	AfxMessageBox(cszParameters);
}

void CCustomBrowserDlg::CB_OpenWindow(CString cszURL, int nLeft, int nTop, int nWidth, int nHeight, int nResizable)
{
	/*CString cszParameters;
	cszParameters.Format("URL=%s LEFT=%d TOP=%d WIDTH=%d HEIGHT=%d RESIZABLE=%d", cszURL, nLeft, nTop, nWidth, nHeight, nResizable);
	AfxMessageBox(cszParameters);*/

	dlg[nWindowCount].Create(IDD_WINDOW);
	dlg[nWindowCount].SetWindowPos(NULL,nLeft, nTop, nWidth, nHeight,NULL);
	dlg[nWindowCount].cszURL = cszURL;
	dlg[nWindowCount].ShowWindow(SW_SHOW);
	nWindowCount++;
}

void CCustomBrowserDlg::CB_ShowModalDialog(CString cszURL, int nLeft, int nTop, int nWidth, int nHeight)
{
	/*CString cszParameters;
	cszParameters.Format("URL=%s LEFT=%d TOP=%d WIDTH=%d HEIGHT=%d RESIZABLE=%d", cszURL, nLeft, nTop, nWidth, nHeight);
	AfxMessageBox(cszParameters);*/

	CCustomModalDialog modaldlg;
	strModalDialogInfo.cszURL = cszURL;
	strModalDialogInfo.nWidth = nWidth;
	strModalDialogInfo.nHeight = nHeight;
	strModalDialogInfo.nLeft = nLeft;
	strModalDialogInfo.nTop = nTop;
	modaldlg.DoModal();
}

void CCustomBrowserDlg::CB_ShowModelessDialog(CString cszURL, int nLeft, int nTop, int nWidth, int nHeight)
{
	/*CString cszParameters;
	cszParameters.Format("URL=%s LEFT=%d TOP=%d WIDTH=%d HEIGHT=%d RESIZABLE=%d", cszURL, nLeft, nTop, nWidth, nHeight);
	AfxMessageBox(cszParameters);*/

	dlgmodeless[nWindowCount].Create(IDD_MODELESS_DIALOG);
	dlgmodeless[nWindowCount].SetWindowPos(NULL,nLeft, nTop, nWidth, nHeight,NULL);
	dlgmodeless[nWindowCount].cszURL = cszURL;
	dlgmodeless[nWindowCount].ShowWindow(SW_SHOW);
	nWindowCount++;
}
