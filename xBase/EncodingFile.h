#pragma once
#ifdef __xBase_lib__
#define xBase_INTFACE _declspec( dllexport )
#else
#define xBase_INTFACE _declspec( dllimport )
#endif
class xBase_INTFACE CEncodingFile
{
public:
	CEncodingFile();
	~CEncodingFile();

	bool Open(const TCHAR *file, const TCHAR *mode, const TCHAR *encoding = NULL);

	void Close();

	bool Read(CString &str);

	bool Write(const CString &str);



private:
	FILE *m_fp;
	CString m_strFile;
	CString m_strMode;
	CString m_strEncoding;
};

