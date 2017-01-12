#include "StdAfx.h"
#include "HwBuffer.h"


CHwBuffer::CHwBuffer(void)
{
	m_pData = nullptr;
	m_nSize = 0;
}


CHwBuffer::~CHwBuffer(void)
{
	if ( m_pData ){
		delete []m_pData;
	}
}

void * CHwBuffer::Get(int nSize)
{
	if( m_default_buf_size>=nSize ){
		return m_data;
	}

	if( m_pData ){
		if ( m_nSize>=nSize ){
			return m_pData;
		}
		delete []m_pData;
	}

	m_pData = new char[nSize];
	m_nSize = nSize;
	return m_pData;
}
