
// xJsAttacherDlg.h : 头文件
//

#pragma once
#include "explorer1.h"
#include <vector>

// CxJsAttacherDlg 对话框
class CxJsAttacherDlg : public CDialogEx
{
// 构造
public:
	CxJsAttacherDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XJSATTACHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_myIe;
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);

	std::vector<CString> m_jsList;
	CString m_dstUrl;
	afx_msg void OnBnClickedButton1();
};
