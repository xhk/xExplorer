
// xExplorer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CxExplorerApp: 
// �йش����ʵ�֣������ xExplorer.cpp
//

class CxExplorerApp : public CWinApp
{
public:
	CxExplorerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CxExplorerApp theApp;