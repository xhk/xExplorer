
// xExplorerDlg.h : ͷ�ļ�
//

#pragma once
#include "explorer1.h"


// CxExplorerDlg �Ի���
class CxExplorerDlg : public CDialogEx
{
// ����
public:
	CxExplorerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XEXPLORER_DIALOG };
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
	CExplorer1 m_myIE;
	afx_msg void OnBnClickedButton1();
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);
	afx_msg void OnBnClickedButtonGo();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	void BeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
	virtual void OnOK();
};
