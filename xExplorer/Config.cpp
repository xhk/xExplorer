#include "stdafx.h"
#include "Config.h"


CConfig::CConfig()
{
}


CConfig::~CConfig()
{
}

void CConfig::Load() 
{
	TCHAR szDir[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szDir, MAX_PATH);
	CString strDir = szDir;
	strDir.MakeLower();
	strDir.Replace(_T(".exe"), _T(".ini"));
	m_strIniFile = strDir;
	GetPrivateProfileString(_T("config"), _T("url"), _T(""), m_strUrl.GetBuffer(MAX_PATH), MAX_PATH, m_strIniFile); m_strUrl.ReleaseBuffer();
}

void CConfig::UpdateUrl(CString url)
{
	m_strUrl = url;
	WritePrivateProfileString(_T("config"), _T("url"), url, m_strIniFile);
}