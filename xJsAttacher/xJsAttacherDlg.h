
// xJsAttacherDlg.h : ͷ�ļ�
//

#pragma once
#include "explorer1.h"
#include <vector>

// CxJsAttacherDlg �Ի���
class CxJsAttacherDlg : public CDialogEx
{
// ����
public:
	CxJsAttacherDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XJSATTACHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
