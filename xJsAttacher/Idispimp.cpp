/*
 * idispimp.CPP
 * IDispatch for Extending Dynamic HTML Object Model
 *
 * Copyright (c)1995-1999 Microsoft Corporation, All Rights Reserved
 */ 

#include "stdafx.h"
#include "idispimp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString cszCB_IsOurCustomBrowser = L"CB_IsOurCustomBrowser";
CString cszCB_Close = L"CB_Close";
CString cszCB_CustomFunction = L"CB_CustomFunction";
CString cszCB_CustomFunctionWithParams = L"CB_CustomFunctionWithParams";
CString cszCB_OpenWindow = L"CB_OpenWindow";
CString cszCB_ShowModalDialog = L"CB_ShowModalDialog";
CString cszCB_ShowModelessDialog = L"CB_ShowModelessDialog";
CString cszCB_WriteFile = L"WriteFile";

#define DISPID_CB_IsOurCustomBrowser 1
#define DISPID_CB_Close 2
#define DISPID_CB_CustomFunction 3
#define DISPID_CB_CustomFunctionWithParams 4
#define DISPID_CB_OpenWindow 5
#define DISPID_CB_ShowModalDialog 6
#define DISPID_CB_ShowModelessDialog 7



struct JSExternalMethod {
	int nId;
	CString strMethod;
	CImpIDispatch::JSExternalMethod_Entry fnEntry;
};




void *CImpIDispatch::GetCustomMethodMap() {
	static JSExternalMethod js_external_method[] = {
		{ 1, L"OpenFile",  &CImpIDispatch::JsOpenFile },
		{ 2, L"CloseFile", &CImpIDispatch::JsCloseFile },
		{ 3, L"WriteFile", &CImpIDispatch::JsWriteFile },
		{ 4, L"ReadFile" , &CImpIDispatch::JsReadFile },
		{ 0, L"" }
	};
	return js_external_method;
}

/*
 * CImpIDispatch::CImpIDispatch
 * CImpIDispatch::~CImpIDispatch
 *
 * Parameters (Constructor):
 *  pSite           PCSite of the site we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */ 

CImpIDispatch::CImpIDispatch( void )
{
    m_cRef = 0;
}

CImpIDispatch::~CImpIDispatch( void )
{
	ASSERT( m_cRef == 0 );
}


/*
 * CImpIDispatch::QueryInterface
 * CImpIDispatch::AddRef
 * CImpIDispatch::Release
 *
 * Purpose:
 *  IUnknown members for CImpIDispatch object.
 */ 

STDMETHODIMP CImpIDispatch::QueryInterface( REFIID riid, void **ppv )
{
    *ppv = NULL;


    if ( IID_IDispatch == riid )
	{
        *ppv = this;
	}
	
	if ( NULL != *ppv )
    {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
    }

	return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CImpIDispatch::AddRef(void)
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) CImpIDispatch::Release(void)
{
    return --m_cRef;
}


//IDispatch
STDMETHODIMP CImpIDispatch::GetTypeInfoCount(UINT* /*pctinfo*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP CImpIDispatch::GetTypeInfo(
			/* [in] */ UINT /*iTInfo*/,
            /* [in] */ LCID /*lcid*/,
            /* [out] */ ITypeInfo** /*ppTInfo*/)
{
	return E_NOTIMPL;
}

STDMETHODIMP CImpIDispatch::GetIDsOfNames(
			/* [in] */ REFIID riid,
            /* [size_is][in] */ OLECHAR** rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID* rgDispId)
{
	HRESULT hr;
	UINT	i;

	// Assume some degree of success
	hr = NOERROR;

	JSExternalMethod *js_external_method = (JSExternalMethod *)GetCustomMethodMap();

	for ( i=0; i < cNames; i++) {
		CString cszName  = rgszNames[i];
		int j = 0;
		bool find = false;
		while (js_external_method[j].nId) {
			if (js_external_method[j].strMethod == cszName) {
				rgDispId[i] = js_external_method[j].nId;
				find = true;
			}
			j++;
		}

		if( !find ) {
			// One or more are unknown so set the return code accordingly
			hr = ResultFromScode(DISP_E_UNKNOWNNAME);
			rgDispId[i] = DISPID_UNKNOWN;
		}
	}
	return hr;
}

STDMETHODIMP CImpIDispatch::Invoke(
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS* pDispParams,
            /* [out] */ VARIANT* pVarResult,
            /* [out] */ EXCEPINFO* pExcepInfo,
            /* [out] */ UINT* puArgErr)
{

	JSExternalMethod *js_external_method = (JSExternalMethod *)GetCustomMethodMap();
	int j = 0;
	while (js_external_method[j].nId)
	{
		if (js_external_method[j].fnEntry) {
			mufn.fn = js_external_method[j].fnEntry;
			return (this->*mufn.pfnJsOpenFile)(dispIdMember, riid, lcid, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
		}
		j++;
	}

	return S_OK;
}

STDMETHODIMP CImpIDispatch::JsOpenFile( /* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS  *pDispParams,
	/* [out] */ VARIANT  *pVarResult,
	/* [out] */ EXCEPINFO *pExcepInfo,
	/* [out] */ UINT *puArgErr)
{
	if (wFlags & DISPATCH_PROPERTYGET)
	{
		if (pVarResult != NULL)
		{

			VariantInit(pVarResult);
			V_VT(pVarResult) = VT_BOOL;
			V_BOOL(pVarResult) = true;
		}

	}

	if( wFlags & DISPATCH_METHOD)
	{

	}

	return S_OK;
}

STDMETHODIMP CImpIDispatch::JsCloseFile( /* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS  *pDispParams,
	/* [out] */ VARIANT  *pVarResult,
	/* [out] */ EXCEPINFO *pExcepInfo,
	/* [out] */ UINT *puArgErr) {
	return S_OK;
}

STDMETHODIMP CImpIDispatch::JsWriteFile( /* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS  *pDispParams,
	/* [out] */ VARIANT  *pVarResult,
	/* [out] */ EXCEPINFO *pExcepInfo,
	/* [out] */ UINT *puArgErr) {
	return S_OK;
}

STDMETHODIMP CImpIDispatch::JsReadFile( /* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS  *pDispParams,
	/* [out] */ VARIANT  *pVarResult,
	/* [out] */ EXCEPINFO *pExcepInfo,
	/* [out] */ UINT *puArgErr) {
	return S_OK;
}