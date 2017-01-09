#pragma once
class CConfig
{
public:
	CConfig();
	~CConfig();

	void Load();

	void UpdateUrl(CString url);

	CString GetUrl() { return m_strUrl;  }

	static CConfig & getInstance() { static CConfig cfg; return cfg; }

private :
	CString m_strIniFile;
	CString m_strUrl;

};

