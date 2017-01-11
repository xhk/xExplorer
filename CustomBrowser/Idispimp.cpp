/*
 * idispimp.CPP
 * IDispatch for Extending Dynamic HTML Object Model
 *
 * Copyright (c)1995-1999 Microsoft Corporation, All Rights Reserved
 */ 

#include "stdafx.h"
#include "idispimp.h"

#include "CustomBrowser.h"
#include "CustomBrowserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString cszCB_IsOurCustomBrowser = "CB_IsOurCustomBrowser";
CString cszCB_Close = "CB_Close";
CString cszCB_CustomFunction = "CB_CustomFunction";
CString cszCB_CustomFunctionWithParams = "CB_CustomFunctionWithParams";
CString cszCB_OpenWindow = "CB_OpenWindow";
CString cszCB_ShowModalDialog = "CB_ShowModalDialog";
CString cszCB_ShowModelessDialog = "CB_ShowModelessDialog";

#define DISPID_CB_IsOurCustomBrowser 1
#define DISPID_CB_Close 2
#define DISPID_CB_CustomFunction 3
#define DISPID_CB_CustomFunctionWithParams 4
#define DISPID_CB_OpenWindow 5
#define DISPID_CB_ShowModalDialog 6
#define DISPID_CB_ShowModelessDialog 7



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


		for ( i=0; i < cNames; i++) {
		CString cszName  = rgszNames[i];

		if(cszName == cszCB_IsOurCustomBrowser)
		{
			rgDispId[i] = DISPID_CB_IsOurCustomBrowser;
		}
		else if(cszName == cszCB_Close)
		{
			rgDispId[i] = DISPID_CB_Close;
		}
		else if(cszName == cszCB_CustomFunction)
		{
			rgDispId[i] = DISPID_CB_CustomFunction;
		}
		else if(cszName == cszCB_CustomFunctionWithParams)
		{
			rgDispId[i] = DISPID_CB_CustomFunctionWithParams;
		}	
		else if(cszName == cszCB_OpenWindow)
		{
			rgDispId[i] = DISPID_CB_OpenWindow;
		}
		else if(cszName == cszCB_ShowModalDialog)
		{
			rgDispId[i] = DISPID_CB_ShowModalDialog;
		}
		else if(cszName == cszCB_ShowModelessDialog)
		{
			rgDispId[i] = DISPID_CB_ShowModelessDialog;
		}
		else {
			// One or more are unknown so set the return code accordingly
			hr = ResultFromScode(DISP_E_UNKNOWNNAME);
			rgDispId[i] = DISPID_UNKNOWN;
		}
	}
	return hr;
}

STDMETHODIMP CImpIDispatch::Invoke(
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID /*riid*/,
            /* [in] */ LCID /*lcid*/,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS* pDispParams,
            /* [out] */ VARIANT* pVarResult,
            /* [out] */ EXCEPINFO* /*pExcepInfo*/,
            /* [out] */ UINT* puArgErr)
{

	CCustomBrowserDlg* pDlg = (CCustomBrowserDlg*) AfxGetMainWnd();
	
	if(dispIdMember == DISPID_CB_IsOurCustomBrowser) 
	{
		if(wFlags & DISPATCH_PROPERTYGET)
		{
			if(pVarResult != NULL)
			{
				VariantInit(pVarResult);
				V_VT(pVarResult)=VT_BOOL;
				V_BOOL(pVarResult) = true;
			}
		}
		
		if ( wFlags & DISPATCH_METHOD )
		{
			bool bResult = pDlg->CB_IsOurCustomBrowser();
			
			VariantInit(pVarResult);
			V_VT(pVarResult)=VT_BOOL;
			V_BOOL(pVarResult) = bResult;
		}
		
	}
	
	if(dispIdMember == DISPID_CB_Close) 
	{
		if(wFlags & DISPATCH_PROPERTYGET)
		{
			if(pVarResult != NULL)
			{	
				VariantInit(pVarResult);
				V_VT(pVarResult)=VT_BOOL;
				V_BOOL(pVarResult) = true;
			}
		}
		
		if ( wFlags & DISPATCH_METHOD )
		{
			
			pDlg->CB_Close();
		}
		
	}
	
	
	if(dispIdMember == DISPID_CB_CustomFunction) 
	{
		if(wFlags & DISPATCH_PROPERTYGET)
		{
			if(pVarResult != NULL)
			{
				VariantInit(pVarResult);
				V_VT(pVarResult)=VT_BOOL;
				V_BOOL(pVarResult) = true;
			}
		}
		
		if ( wFlags & DISPATCH_METHOD )
		{
			pDlg->CB_CustomFunction();
		}
        
		
	}
	
	if(dispIdMember == DISPID_CB_CustomFunctionWithParams) 
	{
		if(wFlags & DISPATCH_PROPERTYGET)
		{
			if(pVarResult != NULL)
			{
				
				VariantInit(pVarResult);
				V_VT(pVarResult)=VT_BOOL;
				V_BOOL(pVarResult) = true;
			}
		}
		
		if ( wFlags & DISPATCH_METHOD )
		{
			//arguments come in reverse order
			//for some reason
			CString cszArg1= pDispParams->rgvarg[1].bstrVal; // in case you want a CString copy
			int nArg2= pDispParams->rgvarg[0].intVal;
			
			pDlg->CB_CustomFunctionWithParams(cszArg1, nArg2);
		}
		
	}

	if(dispIdMember == DISPID_CB_OpenWindow) 
	{
		if(wFlags & DISPATCH_PROPERTYGET)
		{
			if(pVarResult != NULL)
			{
				
				VariantInit(pVarResult);
				V_VT(pVarResult)=VT_BOOL;
				V_BOOL(pVarResult) = true;
			}
		}
		
		if ( wFlags & DISPATCH_METHOD )
		{
			//arguments come in reverse order
			//for some reason
			CString cszArg1= pDispParams->rgvarg[5].bstrVal; // in case you want a CString copy
			int nArg2= pDispParams->rgvarg[4].intVal;
			int nArg3= pDispParams->rgvarg[3].intVal;
			int nArg4= pDispParams->rgvarg[2].intVal;
			int nArg5= pDispParams->rgvarg[1].intVal;
			int nArg6 = pDispParams->rgvarg[0].intVal;
			
			pDlg->CB_OpenWindow(cszArg1, nArg2, nArg3, nArg4, nArg5, nArg6);
		}
		
	}
	
	if(dispIdMember == DISPID_CB_ShowModelessDialog) 
	{
		if(wFlags & DISPATCH_PROPERTYGET)
		{
			if(pVarResult != NULL)
			{
				
				VariantInit(pVarResult);
				V_VT(pVarResult)=VT_BOOL;
				V_BOOL(pVarResult) = true;
			}
		}
		
		if ( wFlags & DISPATCH_METHOD )
		{
			//arguments come in reverse order
			//for some reason
			CString cszArg1= pDispParams->rgvarg[4].bstrVal; // in case you want a CString copy
			int nArg2= pDispParams->rgvarg[3].intVal;
			int nArg3= pDispParams->rgvarg[2].intVal;
			int nArg4= pDispParams->rgvarg[1].intVal;
			int nArg5= pDispParams->rgvarg[0].intVal;
			
			pDlg->CB_ShowModelessDialog(cszArg1, nArg2, nArg3, nArg4, nArg5);
		}
		
	}
	
	if(dispIdMember == DISPID_CB_ShowModalDialog) 
	{
		if(wFlags & DISPATCH_PROPERTYGET)
		{
			if(pVarResult != NULL)
			{
				
				VariantInit(pVarResult);
				V_VT(pVarResult)=VT_BOOL;
				V_BOOL(pVarResult) = true;
			}
		}
		
		if ( wFlags & DISPATCH_METHOD )
		{
			//arguments come in reverse order
			//for some reason
			CString cszArg1= pDispParams->rgvarg[4].bstrVal; // in case you want a CString copy
			int nArg2= pDispParams->rgvarg[3].intVal;
			int nArg3= pDispParams->rgvarg[2].intVal;
			int nArg4= pDispParams->rgvarg[1].intVal;
			int nArg5= pDispParams->rgvarg[0].intVal;
			
			pDlg->CB_ShowModalDialog(cszArg1, nArg2, nArg3, nArg4, nArg5);
		}
		
	}

	return S_OK;
}
