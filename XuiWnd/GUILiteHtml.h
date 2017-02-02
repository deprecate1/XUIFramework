// GUILiteHtml.h: interface for the CGUILiteHtml class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUILITEHTML_H__77D31328_9C2B_49DD_994B_4FA03AF959B9__INCLUDED_)
#define AFX_GUILITEHTML_H__77D31328_9C2B_49DD_994B_4FA03AF959B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GUIElement.h"
#include "../widgets/cstatichtml/pphtmlstatic.h" 

class CGUILiteHtml : public CGUIElement  
{
public:
	CGUILiteHtml();
	virtual ~CGUILiteHtml();

	virtual void	Initialize();
	virtual int		Create(CWnd* pParent, CRect WidgetRect);
	//virtual void	OnDraw(CDC* pDC);
	virtual bool	PropertyChanging( const void* pvProperty , void* pvNewValue );
	virtual void	GetProperties(EPropList& PropList);
	virtual	int		LoadXML(TiXmlElement* pDataNode);
	virtual int		SaveXML(TiXmlElement *pDataNode);

protected:
	CPPHtmlStatic*	m_pHtmlLite;
	CString			m_strText;
	COLORREF		m_cBkColor;
	COLORREF		m_cTextColor;

};

#endif // !defined(AFX_GUILITEHTML_H__77D31328_9C2B_49DD_994B_4FA03AF959B9__INCLUDED_)
