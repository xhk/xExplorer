
// xExplorerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "xExplorer.h"
#include "xExplorerDlg.h"
#include "afxdialogex.h"
#include "xQuery.h"
#include "Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CxExplorerDlg �Ի���



CxExplorerDlg::CxExplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_XEXPLORER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CxExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_myIE);
}

BEGIN_MESSAGE_MAP(CxExplorerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CxExplorerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CxExplorerDlg::OnBnClickedButtonGo)
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


// CxExplorerDlg ��Ϣ�������

BOOL CxExplorerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// m_myIE.Navigate(_T("https://www.baidu.com"), NULL, NULL, NULL, NULL);
	
	CConfig &cfg = CConfig::getInstance();
	cfg.Load();

	SetDlgItemText(IDC_EDIT_URL, cfg.GetUrl());

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CxExplorerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CxExplorerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CxExplorerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CxExplorerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString selector;
	GetDlgItemText(IDC_EDIT_SELECTOR, selector);
	xQuery x;
	CComPtr<IDispatch> dis = m_myIE.get_Document();
	x.Attach(m_myIE.get_Document());
	std::vector<xHtmlElement> ec;
	//x.query(selector, ec);
	x.query(_T("head"), ec);
	//ec[0].append(_T("<br><script defer>alert(1);</script>"));
	ec[0].appendChild();
	
	return ;

}
BEGIN_EVENTSINK_MAP(CxExplorerDlg, CDialogEx)
	ON_EVENT(CxExplorerDlg, IDC_EXPLORER1, 259, CxExplorerDlg::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CxExplorerDlg, IDC_EXPLORER1, 250, CxExplorerDlg::BeforeNavigate2Explorer1, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()


void CxExplorerDlg::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	/*CString url = URL->bstrVal;
	TRACE(_T("%s\n"), url);*/
	// TODO: �ڴ˴������Ϣ����������
	CComPtr<IHTMLDocument2> doc;
	CComPtr<IWebBrowser2> wb;
	if (S_OK != pDisp->QueryInterface<IWebBrowser2>(&wb)) {
		return;
	}

	CComPtr<IDispatch> dis;
	if (S_OK != wb->get_Document(&dis)) {
		return;
	}

	
	if (S_OK != dis->QueryInterface(&doc)) {
		return;
	}
	
	BSTR cookie;
	if (S_OK != doc->get_cookie(&cookie)) {
		return;
	}

	CString strCookie = cookie;
	SysFreeString(cookie);
	SetDlgItemText(IDC_EDIT_COOKIE, strCookie);

}

void CxExplorerDlg::OnBnClickedButtonGo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString url;
	GetDlgItemText(IDC_EDIT_URL, url);
	m_myIE.Navigate(url, NULL, NULL, NULL, NULL);

	CConfig::getInstance().UpdateUrl(url);
}


void CxExplorerDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: �ڴ˴������Ϣ����������
	if (!m_hWnd) {
		return;
	}

	CRect rcMain;
	GetClientRect(rcMain);

	CRect rc;
	m_myIE.GetClientRect(rc);
	rc.top = 50;
	rc.bottom = rcMain.Height() - 160;
	rc.left = 10;
	rc.right = rcMain.Width() - 10;
	m_myIE.MoveWindow(rc);
}


void CxExplorerDlg::BeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	// TODO: �ڴ˴������Ϣ����������
	CString url = URL->bstrVal;
	TRACE(_T("%s\n"), url);
	CString strHeaders = Headers->bstrVal;
	TRACE(_T("%s\n"), strHeaders);
}


void CxExplorerDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	OnBnClickedButtonGo();
	//CDialogEx::OnOK();
}
