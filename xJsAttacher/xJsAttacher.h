
// xJsAttacher.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CxJsAttacherApp: 
// �йش����ʵ�֣������ xJsAttacher.cpp
//

class CxJsAttacherApp : public CWinApp
{
public:
	CxJsAttacherApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CxJsAttacherApp theApp;