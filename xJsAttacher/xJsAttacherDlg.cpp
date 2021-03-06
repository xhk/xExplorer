
// xJsAttacherDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "xJsAttacher.h"
#include "xJsAttacherDlg.h"
#include "afxdialogex.h"
#include <xQuery\xQuery.h>
#include <xBase\Widgets.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CxJsAttacherDlg 对话框



CxJsAttacherDlg::CxJsAttacherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_XJSATTACHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CxJsAttacherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_myIe);
}

BEGIN_MESSAGE_MAP(CxJsAttacherDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CxJsAttacherDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CxJsAttacherDlg 消息处理程序

BOOL CxJsAttacherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	
	m_myIe.put_Silent(TRUE);
	
	if (__argc == 1) {
		m_myIe.Navigate(L"http://www.baidu.com", NULL, NULL, NULL, NULL);
	}
	else {
		if (__argc == 3) {
			CString url = __wargv[1];
			CString jsFiles = __wargv[2];
			CWidgets::SplitStr(m_jsList, jsFiles, _T(","));

			m_dstUrl = url;
			m_myIe.Navigate(url, NULL, NULL, NULL, NULL);
		}
		
	}
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CxJsAttacherDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CxJsAttacherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CxJsAttacherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CxJsAttacherDlg, CDialogEx)
	ON_EVENT(CxJsAttacherDlg, IDC_EXPLORER1, 259, CxJsAttacherDlg::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()

std::wstring Acsii2WideByte(std::string& strascii)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);


	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return std::wstring(&resultstring[0]);
}



void CxJsAttacherDlg::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码
	_bstr_t bs = URL;
	CString strUrl = bs;

	//if( strUrl != m_dstUrl ){
	//	return;
	//}

	xQuery x;
	CComPtr<IDispatch> dis = m_myIe.get_Document();
	x.Attach(m_myIe.get_Document());
	std::vector<xHtmlElement> ec;
	//x.query(selector, ec);
	x.query(_T("head"), ec);;
	CString js;
	for (auto i = m_jsList.begin(); i != m_jsList.end(); ++i) {
		CWidgets::ReadFile(js, *i, _T("utf-8"));
		ec[0].appendJS(js);
	}
}


void CxJsAttacherDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
