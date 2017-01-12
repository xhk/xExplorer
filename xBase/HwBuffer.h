#pragma once

#ifdef __xBase_lib__
#define xBase_INTFACE _declspec( dllexport )
#else
#define xBase_INTFACE _declspec( dllimport )
#endif

class xBase_INTFACE CHwBuffer
{
public:
	CHwBuffer(void);
	~CHwBuffer(void);

	void *Get(int nSize);
private:
	static const int m_default_buf_size = 8*1024;
	char m_data[m_default_buf_size];
	char *m_pData;
	int m_nSize ;
};

