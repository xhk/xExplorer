#include "stdafx.h"
#include "Widgets.h"
#include <io.h>
#include <string>

CWidgets::CWidgets()
{
}


CWidgets::~CWidgets()
{
}

CString CWidgets::GetBytesStr(__int64 iBytes){
	CString str;
	if ( iBytes <1024 ){
		str.Format(_T("%lldB"), iBytes);
		return str;
	}

	if ( iBytes<1024*1024 ){
		str.Format(_T("%lldKB"), iBytes/1024);
		return str;
	}

	if ( iBytes<1024*1024*1024 ){
		str.Format(_T("%lld.%02dM"), iBytes/(1024*1024), (int)(iBytes%(1024*1024)/1024.0/1024*100));
		return str;
	}

	if ( iBytes<(__int64)1024*1024*1024*1024 ){
		str.Format(_T("%lld.%02dG"), iBytes/(1024*1024*1024), (int)(iBytes%(1024*1024*1024)/1024.0/1024/1024*100));
	}

	return str;
}

int CWidgets::GetMarketId(const char *market)
{
	//SZ; SH; CF; SHF; DCE;
	static std::string markets[] = {
		"SZ",
		"SH",
		"CF",
		"SHF",
		"DCE",
		"CZC",
		"HK"
	};

	for (int i = 0; i < sizeof(markets) / sizeof(markets[0]); i++){
		if (markets[i] == market){
			return i;
		}
	}

	return -1;
}

int CWidgets::GetMarketId(const wchar_t *market)
{
	//SZ; SH; CF; SHF; DCE;
	static std::wstring markets[] = {
		L"SZ",
		L"SH",
		L"CF",
		L"SHF",
		L"DCE",
		L"CZC",
		L"HK"
	};

	for (int i = 0; i < sizeof(markets) / sizeof(markets[0]); i++){
		if (markets[i] == market){
			return i;
		}
	}

	return -1;
}

//循环创建目录.
bool CWidgets::MakeDir(const TCHAR* chDir)
{
	TCHAR buff[MAX_PATH] = { 0 };
	_tcscpy_s(buff, chDir);
	TCHAR* pos = _tcschr(buff, '\\');
	while (pos)
	{
		buff[pos - buff] = '\0';
		_tmkdir(buff);
		buff[pos - buff] = '\\';
		pos = _tcschr(pos + 1, '\\');
	}
	return !_tmkdir(buff);
}

bool CWidgets::TruncateFile(FILE *f)
{
	fseek(f,0,SEEK_SET);
	int fd = _fileno(f);
	HANDLE hfile = (HANDLE)_get_osfhandle(fd);
	return SetEndOfFile(hfile) == TRUE;
}

void CWidgets::GetDirList(const TCHAR * dir, std::vector<CString> & dir_list)
{
	CString strFind;
	strFind.Format(_T("%s\\*"),dir);
	WIN32_FIND_DATA wfd = {0};
	HANDLE hFile = FindFirstFile(strFind,&wfd);
	if (hFile == INVALID_HANDLE_VALUE){
		return ;
	}

	while (FindNextFile(hFile,&wfd)){
		if (wfd.cFileName[0] == '.'){
			continue;
		}

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			dir_list.push_back(wfd.cFileName);
		}
	}

	FindClose(hFile);
}

void CWidgets::GetFileList(std::vector<CString> & file_list, const TCHAR * dir, const TCHAR *ext)
{
	CString strFind;
	if (ext){
		strFind.Format(_T("%s\\*.%s"), dir, ext);
	}
	else
	{
		strFind.Format(_T("%s\\*"), dir);
	}
	WIN32_FIND_DATA wfd = { 0 };
	HANDLE hFile = FindFirstFile(strFind, &wfd);
	if (hFile == INVALID_HANDLE_VALUE){
		return;
	}

	if (wfd.cFileName[0] != '.' && !(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
		file_list.push_back(wfd.cFileName);
	}

	while (FindNextFile(hFile, &wfd)){
		if (wfd.cFileName[0] == '.'){
			continue;
		}

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			continue;
		}

		file_list.push_back(wfd.cFileName);
	}

	FindClose(hFile);
}

bool CWidgets::IsFileExist(const TCHAR *file)
{
	return !_taccess( file, 0 );
}

CString CWidgets::GetParentDir()
{
	TCHAR szModuleFile[MAX_PATH] = {0};
	GetModuleFileName(NULL, szModuleFile, MAX_PATH);
	*_tcsrchr(szModuleFile, '\\') = 0;
	*_tcsrchr(szModuleFile, '\\') = 0;
	return szModuleFile;
}

CString CWidgets::GetLocalDir()
{
    TCHAR szModuleFile[MAX_PATH] = {0};
    GetModuleFileName(NULL, szModuleFile, MAX_PATH);
    *_tcsrchr(szModuleFile, '\\') = 0;
    return szModuleFile;
}

bool CWidgets::CopyDir(const TCHAR *dst, const TCHAR *src)
{
/*
pFrom
Type: PCZZTSTR
Note  This string must be double-null terminated.

A pointer to one or more source file names. These names should be fully qualified paths to prevent unexpected results.
Standard MS-DOS wildcard characters, such as "*", are permitted only in the file-name position. Using a wildcard character elsewhere in the string will lead to unpredictable results.
Although this member is declared as a single null-terminated string, it is actually a buffer that can hold multiple null-delimited file names. Each file name is terminated by a single NULL character. The last file name is terminated with a double NULL character ("\0\0") to indicate the end of the buffer.
pTo
Type: PCZZTSTR
Note  This string must be double-null terminated.

A pointer to the destination file or directory name. This parameter must be set to NULL if it is not used. Wildcard characters are not allowed. Their use will lead to unpredictable results.
Like pFrom, the pTo member is also a double-null terminated string and is handled in much the same way. However, pTo must meet the following specifications:
Wildcard characters are not supported.
Copy and Move operations can specify destination directories that do not exist. In those cases, the system attempts to create them and normally displays a dialog box to ask the user if they want to create the new directory. To suppress this dialog box and have the directories created silently, set the FOF_NOCONFIRMMKDIR flag in fFlags.
For Copy and Move operations, the buffer can contain multiple destination file names if the fFlags member specifies FOF_MULTIDESTFILES.
Pack multiple names into the pTo string in the same way as for pFrom.
Use fully qualified paths. Using relative paths is not prohibited, but can have unpredictable results.
*/
	TCHAR dst_dir[MAX_PATH] = {0}, src_dir[MAX_PATH]={0};
	_tcsncpy_s(dst_dir,dst, MAX_PATH);
	_tcsncpy_s(src_dir,src, MAX_PATH);

	SHFILEOPSTRUCT fop;
	ZeroMemory(&fop, sizeof fop);
	fop.fFlags = FOF_SILENT;
	fop.wFunc = FO_COPY;
	fop.pFrom = src_dir;
	fop.pTo   = dst_dir;

	int nRet = SHFileOperation(&fop);

	return !nRet;
}

int CWidgets::GetDate(CTime & t)
{
	return t.GetYear()*10000 + t.GetMonth()*100 + t.GetDay();
}

CTime CWidgets::Int2Date(int nDate)
{
	if ( nDate == 0 ){ CTime t; return t;}

	CTime tt(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	return tt;
}

CString CWidgets::GetFileDir(const CString & strFile)
{
	int nPos = strFile.ReverseFind('\\');
	if (nPos <= -1){
		return _T("");
	}

	return strFile.Left(nPos);
}

CString CWidgets::GetModuleDir(HMODULE hModule)
{
    TCHAR szFileName[MAX_PATH] = {0};
    GetModuleFileName(hModule, szFileName, MAX_PATH);
    TCHAR *p = _tcsrchr(szFileName, '\\');
    if( p ) { *p = 0; }
    return szFileName;
}

//utf8 转 Unicode  
std::wstring Utf82Unicode(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<wchar_t> resultstring(widesize);

	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);

	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return std::wstring(&resultstring[0]);
}

void CWidgets::Utf82Unicdoe(const char *utf8, CString & u) {
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		return;
	}
	if (widesize == 0)
	{
		return ;
	}

	wchar_t *pUnicode = new wchar_t[widesize+16];

	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8, -1, pUnicode, widesize);

	if (convresult != widesize)
	{
		delete []pUnicode;
		return;
	}

	u = pUnicode;
	delete []pUnicode;
}


//unicode 转为 ascii  
std::string CWidgets::WideByte2Acsii(std::wstring& wstrcode)
{
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(asciisize);
	int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);

	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}

	return std::string(&resultstring[0]);
}





void CWidgets::SimpleA2w(wchar_t *dst, int dst_len, const char *src)
{
	ZeroMemory(dst, dst_len);

	for (int i=0;i<dst_len && src[i];i++ )
	{
		dst[i] = src[i];
	}
}

void CWidgets::SimpleW2a(char *dst, int dst_len, const wchar_t *src)
{
	ZeroMemory(dst, dst_len);
	for (int i=0;i<dst_len && src[i];i++ )
	{
		dst[i] = (char)(src[i]);
	}
}

bool CWidgets::a2w(wchar_t * w, int wsize, const char * str)
{
    int widesize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION || widesize==0 ){
        return false;
    }

    int convresult = MultiByteToWideChar(CP_ACP, 0, str, -1, w, wsize);

    return convresult == wsize;
}

bool CWidgets::w2a(char *a, int asize, const wchar_t * str)
{
    int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, str, -1, NULL, 0, NULL, NULL);
    if (asciisize == ERROR_NO_UNICODE_TRANSLATION || asciisize==0 )
    {
        return false;
    }

    int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, str, -1, a, asize, NULL, NULL);

    return convresult == asize;
}

int CWidgets::Today()
{
    CTime tNow = CTime::GetCurrentTime();
    return GetDate(tNow);
}

int CWidgets::Now()
{
    CTime tNow = CTime::GetCurrentTime();
    return (tNow.GetHour()*10000+tNow.GetMinute()*100+tNow.GetSecond())*1000;
}

//utf-8 转 ascii  
std::string CWidgets::UTF_82ASCII(std::string& strUtf8Code)
{
	std::string strRet("");
	//先把 utf8 转为 unicode  
	std::wstring wstr = Utf82Unicode(strUtf8Code);
	//最后把 unicode 转为 ascii  
	strRet = WideByte2Acsii(wstr);
	return strRet;
}

std::string CWidgets::Utf8ToAscii(const char *pszUtf8)
{
	return UTF_82ASCII(std::string(pszUtf8));
}

///////////////////////////////////////////////////////////////////////  


//ascii 转 Unicode  
std::wstring CWidgets::Acsii2WideByte(std::string& strascii)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);


	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}

	return std::wstring(&resultstring[0]);
}


//Unicode 转 Utf8  
std::string CWidgets::Unicode2Utf8(const std::wstring& widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<char> resultstring(utf8size);

	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);

	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}

	return std::string(&resultstring[0]);
}


//ascii 转 Utf8  
std::string CWidgets::ASCII2UTF_8(std::string& strAsciiCode)
{
	std::string strRet("");
	//先把 ascii 转为 unicode  
	std::wstring wstr = Acsii2WideByte(strAsciiCode);
	//最后把 unicode 转为 utf8  
	strRet = Unicode2Utf8(wstr);
	return strRet;
}

std::string CWidgets::AsciiToUtf8(const char *pszAscii)
{
	return ASCII2UTF_8(std::string(pszAscii));
}

int CWidgets::next_cyle_time(int nTime, const CTimeSpan & ts){
	CTime t(2000,1,1,nTime/1000/10000,nTime/1000/100%100,0);
	CTime t1(2000, 1, 1, 11, 30, 0), t2(2000,1,1,13,0,0);
	t += ts;
	if (t1 <= t && t < t2){
		CTimeSpan ts2(0,1,30,0);
		t += ts2;
	}
	return 1000 * (t.GetHour()*10000+t.GetMinute()*100);
}

int CWidgets::NextDate(int nDate)
{
	if ( nDate<19900101 ){
		return 19900101;
	}

	if( !ValidateDate(nDate) ){
		return 19900101;
	}

	CTime t(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	CTimeSpan ts(1,0,0,0);
	t += ts;

	return t.GetYear()*10000 + t.GetMonth()*100 + t.GetDay();
}

int CWidgets::NextDate(int nDate, int nStep)
{
    if ( nDate<19900101 ){
        return nDate+nStep;
    }

	CTime t(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	CTimeSpan ts(nStep,0,0,0);
	t += ts;

	return t.GetYear()*10000 + t.GetMonth()*100 + t.GetDay();
}

int CWidgets::GetWeekBeginDate(int nDate)
{
	CTime t(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	if ( t.GetDayOfWeek()==2 ){  // 周一
		return nDate;
	}

	return GetNextMonday(t);
}

int CWidgets::GetWeekEndDate(int nDate)
{
	CTime t(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	if ( t.GetDayOfWeek()==1 ){ // 周日
		return nDate;
	}

	return GetLastSunday(t);
}

int CWidgets::GetNextMonday(CTime & t)
{
	CTimeSpan ts(1, 0,0,0);

	while(true){
		t += ts;
		if ( t.GetDayOfWeek()==2 ){
			return GetDate(t);
		}
	}
	return 0;
}

int CWidgets::GetNextMonday(int nDate)
{
	CTime t(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	return GetNextMonday(t);
}

int CWidgets::GetNextMonday(int nDate, int nStep)
{
	for ( int i=0;i<nStep;++i )
	{
		nDate = GetNextMonday(nDate);
	}

	return nDate;
}

int CWidgets::GetLastSunday(CTime & t)
{
	CTimeSpan ts(1, 0,0,0);
	while(true){
		t -= ts;
		if ( t.GetDayOfWeek()==1 ){
			return GetDate(t);
		}
	}
	return 0;
}

int CWidgets::GetMonthBeginDate(int nDate)
{
	CTime t(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	if ( IsFirstDayOfMonth(t) ){
		return nDate;
	}

	int nMonth = t.GetMonth();
	CTimeSpan ts(1, 0,0,0);
	while(true){
		t += ts;
		if (t.GetMonth()!=nMonth){
			return GetDate(t);
		}
	}

	return 0;
}

int CWidgets::GetMonthEndDate(int nDate)
{
	CTime t(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	if ( IsLastDayOfMonth(t) ){
		return nDate;
	}
	
	int nMonth = t.GetMonth();
	CTimeSpan ts(1, 0,0,0);
	while(true){
		t -= ts;
		if (t.GetMonth()!=nMonth){
			return GetDate(t);
		}
	}

	return 0;
}

bool CWidgets::IsLastDayOfMonth(CTime &t )
{
	CTimeSpan ts(1, 0,0,0);
	int nMonth = t.GetMonth();
	t += ts;
	return nMonth!=t.GetMonth();
}

bool CWidgets::IsFirstDayOfMonth(CTime & t)
{
	return t.GetDay() == 1;
}

int CWidgets::NextMonthFirstDay(int nDate)
{
	CTime t(nDate/10000, nDate/100%100, nDate%100, 0, 0, 0);
	CTimeSpan ts(1, 0,0,0);
	while(true){
		t += ts;
		if (IsFirstDayOfMonth(t)){
			return GetDate(t);
		}
	}

	return 0;
}

int CWidgets::NextMonthFirstDay(int nDate, int nStep)
{
	for (int i=0;i<nStep;++i )
	{
		nDate = NextMonthFirstDay(nDate);
	}

	return nDate;
}

int CWidgets::ParseTime(const char *str)
{
    std::string s = str;
    std::vector<std::string> l;
    CWidgets::SplitStr(l, s, ":");
    if( l.size()!=3 ){
        return 0;
    }

    return 1000*(atoi(l[0].c_str())*10000+atoi(l[1].c_str())*100+atoi(l[2].c_str()));
}

int CWidgets::ParseDate(const char *str)
{
    std::string s = str;
    std::vector<std::string> l;
    CWidgets::SplitStr(l, s, "-");
    if( l.size()!=3 ){
        return 0;
    }

    return atoi(l[0].c_str())*10000+atoi(l[1].c_str())*100+atoi(l[2].c_str());
}


CString CWidgets::TimeStr(int nTime)
{
	CString str;
	str.Format(_T("%02d:%02d:%02d:%03d"), nTime/1000/10000, nTime/1000/100%100, nTime/1000%100, nTime%1000);
	return str;
}

int CWidgets::GetDays(int nBeginDate, int nEndDate)
{
	CTime tBegin(nBeginDate/10000, nBeginDate/100%100, nBeginDate%100, 0, 0, 0);
	CTime tEnd(nEndDate/10000, nEndDate/100%100,  nEndDate%100, 0, 0, 0);
	CTimeSpan ts = tEnd - tBegin;
	return ts.GetDays()+1;
}

int CWidgets::GetSeconds(int nBeginTime, int nEndTime)
{
	return nEndTime/10000*3600+nEndTime/100%100+nEndTime%100 - nBeginTime/10000*3600-nBeginTime/100%100*60-nBeginTime%100;
}

bool CWidgets::split_windcode(const CString & windcode, CString &market, CString &code)
{
	int pos = windcode.Find(_T("."));
	if (pos < 0){
		return false;
	}

	code = windcode.Mid(0, pos);
	market = windcode.Mid(pos + 1, windcode.GetLength() - pos + 1);
	return true;
}

bool CWidgets::split_windcode(const TCHAR *windwode, CString &market, CString &code)
{
	CString strWindCode = windwode;

	return split_windcode(strWindCode, market, code);
}

bool CWidgets::split_windcode(const char *windcode, char *market, char *code)
{
    const char *dot = strchr(windcode, '.');
    if( dot ){
        memcpy(code, windcode, dot-windcode);
        code[dot-windcode] = 0;
        strcpy_s(market, 8, dot+1);
    }
    return dot;
}

bool CWidgets::split_windcode(const TCHAR * windcode, TCHAR * market, TCHAR * code)
{
    const TCHAR *dot = _tcschr(windcode, '.');
    if( dot ){
        memcpy(code, windcode, (dot-windcode)*sizeof(TCHAR));
        code[dot-windcode] = 0;
        _tcscpy_s(market, 8, dot+1);
    }
    return dot;
}

void CWidgets::SplitStr( std::vector<CString> & arr, const CString & str, const CString & separator)
{
    unsigned int b = 0, e =0;
    CString s;
    unsigned int sep_len = separator.GetLength();
    while( -1 != (e=str.Find(separator,b)) ){
        s = str.Mid(b, e-b);
        arr.push_back(s);
        b = e + sep_len;
    }
    s = str.Mid(b, str.GetLength()-b);
    arr.push_back(s);
}

void CWidgets::SplitStr(std::vector<std::string> & arr, const std::string & str, const char *separator)
{
    unsigned int b = 0, e =0;

    std::string s;
    unsigned int sep_len = strlen(separator);
    while ( -1!= ( e = str.find(separator, b) ) ){
        s = str.substr(b, e-b);
        arr.push_back(s);
        b = e + sep_len;
    }

    s = str.substr(b, str.length()-b);
    arr.push_back(s);
}


//
// 年华率计算
double CWidgets::year_repay(int nDays, double dPlRate ){
	if ( nDays <=0 ){
		return 0;
	}

	return 365 * dPlRate/nDays;
}

CString CWidgets::PriceStr(int nPrice)
{
	CString str;
	str.Format(_T("%d.%04d"), nPrice/10000, nPrice%10000);
	return str;
}

CString CWidgets::Split3Bit(double d, int decimalCount)
{
    TCHAR src[32] = {0};
    TCHAR dst[64] = {0};
    _stprintf_s(src, _T("%.*f"), 2, d);
    int len = _tcslen(src);
    TCHAR * p = _tcschr(src, '.');
    TCHAR *q = dst+63;
    if(p){ // 拷贝小数部分
        int cl = len - (p-src)/sizeof(TCHAR);
        _tcsncpy_s(q-cl, 32, p, cl);
        p--;
        q -= cl;
    }

    for (int i=1;p>src;++i,p--)
    {
        q--;
        *q = *p;
        if( (i % 3) == 0 ){
            q--;
            *q = ',';
        }
    }

    q--;
    *q = *p;
    
    return q;
}

bool CWidgets::ValidateDate(int nDate)
{
	int nYear  = (nDate/10000);
	int nMonth = nDate/100%100;
	int nDay   = nDate%100;
	return nYear>1900 && nYear<2099 && nMonth >= 1 && nMonth <= 12 && nDay >= 1 && nDay <= 31 ;
}

bool CWidgets::ValidteTime(int nTime)
{
	nTime = nTime/1000;
	int nHour = nTime/10000;
	int nMin = nTime/100%100;
	int nSec = nTime%100;

	return ( nHour >= 0 && nHour <= 23 )&&
		  ( nMin >= 0 && nMin <= 59 )&&
		   ( nSec >= 0 && nSec <= 59 );
}


void CWidgets::ReadFile(CString &str, const TCHAR * file, const TCHAR *encoding) {
	FILE * f;
	_tfopen_s(&f, file, _T("r"));
	if (!f) {
		return;
	}

	int file_len = _filelength(_fileno(f));
	if (file_len <= 0) {
		fclose(f);
		return;
	}

	char *buf = new char[file_len + 128];
	if (!buf) {
		fclose(f);
		return;
	}

	fread(buf, 1, file_len, f);
	fclose(f);

	if (!encoding) {
		str = Acsii2WideByte(std::string(buf)).c_str();
		delete[]buf;
		return;
	}

	// utf-8
	if (!_tcsicmp(encoding, _T("utf8")) || !_tcsicmp(encoding, _T("utf-8"))) {
		Utf82Unicdoe(buf, str);
		delete[]buf;
	}
	
	return;
}