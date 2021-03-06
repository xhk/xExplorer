#pragma once
#include <Mshtml.h>
#include <vector>

class xHtmlElement {
public:
	xHtmlElement();
	xHtmlElement(CComPtr<IHTMLElement> e);

	bool children(LPCTSTR selector, std::vector<xHtmlElement> & l);
	bool append(LPCTSTR lpszHtml);
	bool appendChild();
	bool appendJS(LPCTSTR lpszContent, LPCTSTR src = NULL);
	CString html();
private:
	CComPtr<IHTMLElement> m_ele;
	CComPtr<IHTMLDOMNode> m_node;
};

class xHtmlDocument {
public:
	xHtmlDocument(CComPtr<IDispatch> dis);
	~xHtmlDocument();

	bool createElement();
	CComPtr<IHTMLDocument> doc;
	CComPtr<IHTMLDocument2> doc2;
};

class xQuery {
public:
	xQuery();
	~xQuery();

	bool Attach(CComPtr<IDispatch> doc);
	xHtmlElement $(LPCTSTR selector);
	bool query(LPCTSTR selector, std::vector<xHtmlElement> & l);

	
private:

	 bool toList(CComPtr<IHTMLElementCollection> ec, std::vector<xHtmlElement> & l);

	 CComPtr<IDispatch> m_docDisp;
	CComPtr<IHTMLDocument> m_doc;
	CComPtr<IHTMLDocument2> m_doc2;
	CComPtr<IHTMLDocument3> m_doc3;
	CComPtr<IHTMLDocument4> m_doc4;
	CComPtr<IHTMLDocument7> m_doc7;
};


