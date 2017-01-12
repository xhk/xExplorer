#include "stdafx.h"
#include "EncodingFile.h"
#include <io.h>
#include "HwBuffer.h"
#include "Widgets.h"

CEncodingFile::CEncodingFile()
{
	m_fp = NULL;
}


CEncodingFile::~CEncodingFile()
{
	Close();
}

bool CEncodingFile::Open(const TCHAR *file, const TCHAR *mode, const TCHAR *encoding /*= NULL*/)
{
	m_strEncoding = encoding;
	return !_tfopen_s(&m_fp, file, mode);
}

void CEncodingFile::Close()
{
	if (m_fp) {
		fclose(m_fp);
		m_fp = NULL;
	}
}

bool CEncodingFile::Read(CString &str)
{
	if (!m_fp) { return false; }

	int file_len = _filelength(_fileno(m_fp));
	if (file_len <= 0) {
		return false;
	}

	CHwBuffer buf;
	void *data = buf.Get(file_len);
	fread(data, 1, file_len, m_fp);

	if (m_strEncoding.IsEmpty()) {
		str = (TCHAR*)data;
	}
	else if (!m_strEncoding.CompareNoCase(_T("utf8")) || !m_strEncoding.CompareNoCase(_T("utf-8")) ){
		CWidgets::Utf82Unicdoe((const char *)data, str);
	}
	else if (!m_strEncoding.CompareNoCase(_T("gbk")) || !m_strEncoding.CompareNoCase(_T("gb2312")))
	{
		str = (TCHAR*)data;
	}

	return true;
}

bool CEncodingFile::Write(const CString &str)
{
	if (!m_fp) { return false; }

	std::string s;
	if (m_strEncoding.IsEmpty()) {
		CWidgets::WideByte2Acsii(s, str.GetString());
	}
	else if (!m_strEncoding.CompareNoCase(_T("utf8")) || !m_strEncoding.CompareNoCase(_T("utf-8"))) {
		CWidgets::Unicode2Utf8(s, str.GetString());
	}
	else if (!m_strEncoding.CompareNoCase(_T("gbk")) || !m_strEncoding.CompareNoCase(_T("gb2312")))
	{
		CWidgets::WideByte2Acsii(s, str.GetString());
	}

	fwrite(s.c_str(), 1, s.length(), m_fp);

	return true;
}

