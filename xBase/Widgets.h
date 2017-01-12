#pragma once

#ifdef __xBase_lib__
#define xBase_INTFACE _declspec( dllexport )
#else
#define xBase_INTFACE _declspec( dllimport )
#endif
#include <vector>

class xBase_INTFACE CWidgets
{
public:
	CWidgets();
	~CWidgets();

	//************************************
	// Method:    GetBytesStr
	// FullName:  CWidgets::GetBytesStr
	// Access:    public static 
	// Returns:   CString
	// Qualifier: ���ֽ���ת��Ϊ�ɶ������ַ���
	// Parameter: __int64 iBytes
	//************************************
	static CString GetBytesStr(__int64 iBytes);


	//************************************
	// Method:    GetMarketId
	// FullName:  CWidgets::GetMarketId
	// Access:    public static 
	// Returns:   int
	// Qualifier: �����г���id��ϵͳ�Զ����id��������г�����Ĵ���
	//	��̡�����������ӵģ���ʵ������.
	// Parameter: const char * market
	//************************************
	static int GetMarketId(const char *market);
	static int GetMarketId(const wchar_t *market);
	static bool split_windcode(const CString & windcode, CString &market, CString &code);
    static bool split_windcode(const TCHAR * windcode, TCHAR * market, TCHAR * code);
	static bool split_windcode(const TCHAR *windcode, CString &market, CString &code);
	static bool split_windcode(const char *windcode, char *market, char *code);

    static void SplitStr(std::vector<CString> & arr, const CString & str, const CString & separator);
    static void SplitStr(std::vector<std::string> & arr, const std::string & str, const char *separator);
	//-----------------------------------------------------------------
	// �ļ���


	static void ReadFile(CString &str, const TCHAR * file, const TCHAR *encoding);

	//ѭ������Ŀ¼.
	static bool MakeDir(const TCHAR* chDir);

	static bool TruncateFile(FILE *f);

	static void GetDirList(const TCHAR * dir ,std::vector<CString> & dir_list);
	static void GetFileList(std::vector<CString> & file_list,const TCHAR * dir, const TCHAR *ext=NULL);
	static bool IsFileExist( const TCHAR *file );
	//
	// ��ȡ�ϼ�Ŀ¼
	static CString GetParentDir();

    //
    // ����Ŀ¼
    static CString GetLocalDir();

	//
	// �����ļ���
	static bool CopyDir(const TCHAR *dst, const TCHAR *src);

	static CString GetFileDir(const CString & strFile);

    static CString GetModuleDir(HMODULE hModule = NULL);

	//----------------------------------------------------------------------
	

	//-------------------------------------------------------
	// �ַ���ת��
	static void Utf82Unicdoe(const char *utf8, CString & u);
	static std::string UTF_82ASCII(std::string& strUtf8Code);
	static std::string Utf8ToAscii(const char *pszUtf8);
	static std::wstring Acsii2WideByte(std::string& strascii);
	static bool Unicode2Utf8(std::string & str, const wchar_t * widestring);
	static std::string ASCII2UTF_8(std::string& strAsciiCode);
	static std::string AsciiToUtf8(const char *pszAscii);
	static bool WideByte2Acsii(std::string &str, const wchar_t * wstrcode);

	static void SimpleA2w(wchar_t *dst, int dst_len, const char *src);
	static void SimpleW2a(char *dst, int dst_len, const wchar_t *src);

    static bool a2w(wchar_t * w, int wsize, const char * str);
    static bool w2a(char *a, int asize, const wchar_t * str );
	//-------------------------------------------------------------------

	//---------------------------------------------------------
	// ����ʱ����
    static int Today();
    static int Now();
	static int next_cyle_time(int nTime, const CTimeSpan & ts);
	static int NextDate(int nDate);
	static int NextDate(int nDate, int nStep);
	static int GetWeekBeginDate(int nDate);
	static int GetWeekEndDate(int nDate);
	static int GetNextMonday(int nDate); // �������һ����һ
	static int GetNextMonday(int nDate, int nStep);
	static int GetNextMonday(CTime & t);
	static int GetLastSunday(CTime & t);
	static int GetMonthBeginDate(int nDate);
	static int GetMonthEndDate(int nDate);
	static bool IsLastDayOfMonth(CTime & t);
	static bool IsFirstDayOfMonth(CTime & t);
	static int NextMonthFirstDay(int nDate);
	static int NextMonthFirstDay(int nDate, int nStep);
	static bool ValidateDate(int nDate);
	static bool ValidteTime(int nTime);

    //
    // ��HH:MM:SS ʱ���ַ��� ת��ΪHHMMSSsss
    static int ParseTime(const char *str);
    //
    // ��YYYY-MM-DD�����ַ���ת��ΪYYYYMMDD
    static int ParseDate(const char *str);

	//
	// �������ʱ���ַ���
	static CString TimeStr(int nTime);
	//static CString TimeStr(HwBtpDateTime & t);
	//static CString SqlTimeStr(HwBtpDateTime & t);
	//************************************
	// Method:    GetDate
	// FullName:  CWidgets::GetDate
	// Access:    public static 
	// Returns:   int
	// Qualifier: ��ȡʱ����������ڣ�YYYYMMDD��ʽ��
	// Parameter: CTime & t
	//************************************
	static int GetDate(CTime & t);
	static CTime Int2Date( int nDate);
	

	static int GetDays(int nBeginDate, int nEndDate);

	//
	// HHMMSS
	static int GetSeconds(int nBeginTime, int nEndTime);
	//---------------------------------------------------------

	//------------------------------------------------------------
	// ������
	//static double maxRepayRate(std::vector<HwBtpNetValue> & l, double & dMaxAmt);
	static double year_repay(int nDays, double dPlRate );
	//-----------------------------------------------------------

	static CString PriceStr(int nPrice);

    //
    // ��λ�ֽڷ�
    static CString Split3Bit(double d, int decimalCount);
};

