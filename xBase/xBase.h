// xBase.h : xBase DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CxBaseApp
// �йش���ʵ�ֵ���Ϣ������� xBase.cpp
//

class CxBaseApp : public CWinApp
{
public:
	CxBaseApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
