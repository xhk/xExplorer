#include "stdafx.h"
#include "xQuery.h"


void cut_str(LPCTSTR selector, std::vector<CString> &l) 
{
	TCHAR s[128] = { 0 };
	TCHAR *p = (TCHAR *)selector;
	
	int i = 0;
	do {
		if (*p == '#' || *p == '.') {
			if (_tcslen(s) > 0) {
				l.push_back(s);
				i = 0;
				ZeroMemory(s, sizeof(s));
			}
		}
		s[i++] = *p;
	} while (*(p++));

	if (_tcslen(s) > 0) {
		l.push_back(s);
	}
}

bool ParseSelector(LPCTSTR selector, CString &tagName, std::vector<CString> & css_name_list, CString & nextLevel)
{
	const TCHAR *p = _tcschr(selector, ' ');
	std::vector<CString> cuts;

	if (p) {
		nextLevel = p;
		TCHAR s[128] = { 0 };
		memcpy(s, selector, min(p - selector,sizeof(s)));
		cut_str(s, cuts);
	}
	else {
		cut_str(selector, cuts);
	}

	if (cuts.empty()) {
		return false;
	}

	auto i = cuts.begin();
	auto e = cuts.end();
	for (; i != e; ++i) {
		if (i->GetAt(0) == '.') {
			css_name_list.push_back(i->Mid(1, i->GetLength() - 1));
		}
		else if (i->GetAt(0) == '#') {

		}
		else {
			tagName = *i;
		}
	}
	
	return true;
}

xQuery::xQuery() {}
xQuery::~xQuery() {}

bool xQuery::Attach(CComPtr<IDispatch> doc)
{
	if (S_OK != doc->QueryInterface<IHTMLDocument>(&m_doc)) {
		return false;
	}
	if (S_OK != doc->QueryInterface<IHTMLDocument2>(&m_doc2)) {
		return false;
	}
	if (S_OK != doc->QueryInterface<IHTMLDocument3>(&m_doc3)) {
		return false;
	}
	if (S_OK != doc->QueryInterface<IHTMLDocument4>(&m_doc4)) {
		return false;
	}
	if (S_OK != doc->QueryInterface<IHTMLDocument7>(&m_doc7)) {
		return false;
	}
	return true;
}

xHtmlElement xQuery::$(LPCTSTR selector)
{
	if (!selector) {
		return xHtmlElement();
	}

	if (selector[0] == '#') {
		_bstr_t bstr = selector+1;
		CComPtr<IHTMLElement> e;
		if (m_doc3->getElementById(bstr, &e) == S_OK) {
			return xHtmlElement(e);
		}
	}
	else if (selector[0] == '.') { // class
		std::vector<xHtmlElement> l;
		if( !query(selector, l)){
			return l[0];
		}
	}
	else { // tag
		std::vector<xHtmlElement> l;
		if (!query(selector, l) ){
			return l[0];
		}
	}

	return xHtmlElement();
}

bool xQuery::query(LPCTSTR selector, std::vector<xHtmlElement> & l)
{
	CComPtr<IHTMLElementCollection> ec;

	CString tagName;
	std::vector<CString> css_name_list;
	CString nextLevel;
	if (!ParseSelector(selector, tagName, css_name_list, nextLevel)) {
		return false;
	}
	
	if (tagName.IsEmpty()) { //class
		_bstr_t bstr = selector + 1;
		if (S_OK != m_doc7->getElementsByClassName(bstr, &ec)) {
			return false;
		}		
	}
	else { // tag
		_bstr_t bstr = selector;
		if (S_OK != m_doc3->getElementsByTagName(bstr, &ec)) {
			return false;
		}
	}

	if (nextLevel.IsEmpty()) {
		return toList(ec, l);
	}
	else {
		std::vector<xHtmlElement> curr;
		if (!toList(ec, curr)) {
			return false;
		}

		auto i = curr.begin();
		auto e = curr.end();
		for (; i != e; ++i) {
			i->children(nextLevel, l);
		}
	}

	return l.size() > 0;
}

bool xQuery::toList(CComPtr<IHTMLElementCollection> ec, std::vector<xHtmlElement> & l)
{
	long count = 0;
	if (S_OK != ec->get_length(&count)) {
		return false;
	}

	for (int i = 0; i < count; ++i) {
		_variant_t index = i;
		CComPtr<IDispatch> dp;
		if (ec->item(index, index, &dp) != S_OK) {
			continue;
		}

		CComPtr<IHTMLElement> e;
		if (!dp || dp->QueryInterface(IID_IHTMLElement, (void **)&e) != S_OK) {
			continue;
		}
		l.push_back(xHtmlElement(e));
	}

	return l.size() > 0;
}

xHtmlElement::xHtmlElement()
{
}

xHtmlElement::xHtmlElement(CComPtr<IHTMLElement> e)
{
	m_ele = e;
	if (m_ele) {
		m_ele.QueryInterface(&m_node);
	}
}

bool xHtmlElement::append(LPCTSTR lpszHtml) {
	/*
	https://msdn.microsoft.com/en-us/library/aa752300(v=vs.85).aspx

	insertAdjacentHTML method

		Inserts the given HTML text into the element at the location.
		Syntax

		HRESULT retVal = object.insertAdjacentHTML(where, html);

	Parameters
	where[in]
		Type: BSTR
			BSTR that specifies where to insert the HTML text, using one of the following values :
		beforeBegin
			Inserts html immediately before the object.
		afterBegin
			Inserts html after the start of the object but before all other content in the object.
		beforeEnd
			Inserts html immediately before the end of the object but after all other content in the object.
		afterEnd
			Inserts html immediately after the end of the object.
	html[in]
		Type: BSTR
		BSTR that specifies the HTML text to insert.The string can be a combination of text and HTML tags.This must be well - formed, valid HTML or this method will fail.
	Return value
		Type: HRESULT
		If this method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code.
		Standards information
		There are no standards that apply here.
		Remarks
		If the text contains HTML tags, the method parses and formats the text as it is inserted.
		You cannot insert text while the document is loading. Wait for the HTMLFrameSiteEvents::onload event to fire before attempting to call this method.
		When using the IHTMLElement::insertAdjacentHTML method to insert script, you must include the IHTMLScriptElement::defer attribute in the script element.
		*/
	
	_bstr_t where = _T("afterBegin");
	_bstr_t html = lpszHtml;
	if (S_OK != m_ele->insertAdjacentHTML(where, html)) {
		return false;
	}
	return true;
}

bool xHtmlElement::appendChild()
{
	CComPtr<IDispatch> dis;
	if (S_OK != m_ele->get_document(&dis)) {
		return false;
	}

	CComPtr<IHTMLDocument2> doc2;
	dis->QueryInterface(&doc2);
	CComPtr<IHTMLElement> e;
	_bstr_t tag = _T("script");
	if (S_OK != doc2->createElement(tag, &e)) {
		return false;
	}

	CComPtr<IHTMLScriptElement> se;
	if (S_OK != e->QueryInterface(&se)) {
		return false;
	}

	_bstr_t s = _T("alert(1);");
	if (S_OK != se->put_text(s)) {
		return false;
	}

	CComPtr<IHTMLDOMNode> seNode;
	se->QueryInterface(&seNode);

	CComPtr<IHTMLDOMNode> node;
	m_ele->QueryInterface(&node);

	CComPtr<IHTMLDOMNode> retNode;
	node->appendChild(seNode, &retNode);
	return true;
}

bool xHtmlElement::appendJS(LPCTSTR lpszContent, LPCTSTR src)
{
	CComPtr<IDispatch> dis;
	if (S_OK != m_ele->get_document(&dis)) {
		return false;
	}

	CComPtr<IHTMLDocument2> doc2;
	dis->QueryInterface(&doc2);
	CComPtr<IHTMLElement> e;
	_bstr_t tag = _T("script");
	if (S_OK != doc2->createElement(tag, &e)) {
		return false;
	}

	CComPtr<IHTMLScriptElement> se;
	if (S_OK != e->QueryInterface(&se)) {
		return false;
	}

	if (lpszContent) {
		_bstr_t s = lpszContent;
		if (S_OK != se->put_text(s)) {
			return false;
		}
	}
	
	if (src) {
		_bstr_t s = src;
		if (S_OK != se->put_src(s)) {
			return false;
		}
	}

	CComPtr<IHTMLDOMNode> seNode;
	se->QueryInterface(&seNode);

	CComPtr<IHTMLDOMNode> node;
	m_ele->QueryInterface(&node);

	CComPtr<IHTMLDOMNode> retNode;
	node->appendChild(seNode, &retNode);
	return true;
}

CString xHtmlElement::html() {
	CString ret;
	BSTR bstr = NULL;
	m_ele->get_outerHTML(&bstr);
	ret = bstr;
	SysFreeString(bstr);
	return ret;
}

bool xHtmlElement::children(LPCTSTR selector, std::vector<xHtmlElement>& l)
{
	if (!m_ele) {
		return false;
	}

	CString tagName;
	std::vector<CString> css_name_list;
	CString nextLevel;
	if (!ParseSelector(selector, tagName, css_name_list, nextLevel)) {
		return false;
	}

	std::vector<xHtmlElement> curr;
	CComPtr<IDispatch> dp;
	if (S_OK!=m_ele->get_children(&dp)) {
		return false;
	}

	CComPtr<IHTMLElementCollection> ec;
	if (!dp || dp->QueryInterface(IID_IHTMLElementCollection, (void **)&ec) != S_OK) {
		return false;
	}

	long count = 0;
	if (!ec || ec->get_length(&count) != S_OK) {
		return false;
	}

	for (int i = 0; i < count; ++i) {
		_variant_t v = i;
		CComPtr<IDispatch> dp;
		if (ec->item(v, v, &dp) != S_OK) {
			continue;
		}

		CComPtr<IHTMLElement> e;
		if (!dp || dp->QueryInterface(IID_IHTMLElement, (void **)&e) != S_OK) {
			continue;
		}

		BSTR bstrTag;
		if (S_OK != e->get_tagName(&bstrTag)) {
			continue;
		}
		CString tag = bstrTag;

		if (tagName.CompareNoCase(tag) ) {
			continue;
		}

		if (css_name_list.empty()) {
			curr.push_back(xHtmlElement(e));
		}
		else {
			BSTR bstr;
			if (S_OK != e->get_className(&bstr)) {
				continue;
			}
			CString className = bstr;
			SysFreeString(bstr);
			if (className.Find(css_name_list[0]) == -1) {
				continue;
			}
			curr.push_back(xHtmlElement(e));
		}
	}

	if ( nextLevel.IsEmpty() ) {
		auto i = curr.begin();
		auto e = curr.end();
		for (; i != e; ++i) {
			l.push_back(*i);
		}
	}
	else {
		auto i = curr.begin();
		auto e = curr.end();
		for (; i != e; ++i) {
			i->children(nextLevel, l);
		}
	}

	return l.size()>0;
}

xHtmlDocument::xHtmlDocument(CComPtr<IDispatch> dis) {

}

xHtmlDocument::~xHtmlDocument() {

}

bool xHtmlDocument::createElement()
{
	_bstr_t tag = _T("script");
	CComPtr<IHTMLElement> e;
	if (S_OK != doc2->createElement(tag, &e)) {
		return false;
	}

	CComPtr<IHTMLScriptElement> se;
	if (S_OK != e->QueryInterface(&se)) {
		return false;
	}

	_bstr_t s = _T("alert(1);");
	if (S_OK != se->put_text(s)) {
		return false;
	}

	return true;
}
