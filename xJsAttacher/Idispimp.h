/*
 * IDispimp.H
 * IDispatch
 *
 * Copyright (c)1995-1999 Microsoft Corporation, All Rights Reserved
 */ 


#ifndef _IDISPIMP_H_
#define _IDISPIMP_H_



class CImpIDispatch : public IDispatch
{
    protected:
        ULONG               m_cRef;

    public:
        CImpIDispatch(void);
        ~CImpIDispatch(void);

        STDMETHODIMP QueryInterface(REFIID, void **);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

		//IDispatch
        STDMETHODIMP GetTypeInfoCount(UINT* pctinfo);
        STDMETHODIMP GetTypeInfo(/* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo** ppTInfo);
		STDMETHODIMP GetIDsOfNames(
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
		STDMETHODIMP Invoke(
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS  *pDispParams,
            /* [out] */ VARIANT  *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);

		typedef HRESULT(__stdcall CImpIDispatch::*JSExternalMethod_Entry)(/* [in] */ DISPID dispIdMember,/* [in] */ REFIID /*riid*/,/* [in] */ LCID /*lcid*/,	/* [in] */ WORD wFlags,	/* [out][in] */ DISPPARAMS* pDispParams,	/* [out] */ VARIANT* pVarResult,	/* [out] */ EXCEPINFO* /*pExcepInfo*/,	/* [out] */ UINT* puArgErr);

private:
	STDMETHODIMP JsOpenFile( /* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS  *pDispParams,
		/* [out] */ VARIANT  *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr);

	STDMETHODIMP JsCloseFile( /* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS  *pDispParams,
		/* [out] */ VARIANT  *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr);

	STDMETHODIMP JsWriteFile( /* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS  *pDispParams,
		/* [out] */ VARIANT  *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr);

	STDMETHODIMP JsReadFile( /* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS  *pDispParams,
		/* [out] */ VARIANT  *pVarResult,
		/* [out] */ EXCEPINFO *pExcepInfo,
		/* [out] */ UINT *puArgErr);
	union MyUnion
	{
		JSExternalMethod_Entry fn;
		HRESULT(__stdcall CImpIDispatch::*pfnJsOpenFile)(/* [in] */ DISPID dispIdMember,/* [in] */ REFIID /*riid*/,/* [in] */ LCID /*lcid*/,	/* [in] */ WORD wFlags,	/* [out][in] */ DISPPARAMS* pDispParams,	/* [out] */ VARIANT* pVarResult,	/* [out] */ EXCEPINFO* /*pExcepInfo*/,	/* [out] */ UINT* puArgErr);
	}mufn;
	static void *GetCustomMethodMap();

};
#endif //_IDISPIMP_H_
