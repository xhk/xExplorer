// xQuery.h : xQuery DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CxQueryApp
// �йش���ʵ�ֵ���Ϣ������� xQuery.cpp
//

class CxQueryApp : public CWinApp
{
public:
	CxQueryApp();

	// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
