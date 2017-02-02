#ifndef _CGUIEdit_H__
#define _CGUIEdit_H__

#include "GUIElement.h"


class CGUIEdit : public CGUIElement
{
public:

	CGUIEdit();
	virtual ~CGUIEdit();

	virtual void	Initialize();
	virtual int		Create(CWnd* pParent, CRect WidgetRect);
	virtual void	OnDraw(CDC* pDC);
	virtual bool	PropertyChanging( const void* pvProperty , void* pvNewValue );
	virtual void	GetProperties(EPropList& PropList);
	virtual	int		LoadXML(TiXmlElement* pDataNode);
	virtual int		SaveXML(TiXmlElement *pDataNode);

protected:

	// Properties
	bool			m_bTransp;
	COLORREF		m_cBkColor;
	COLORREF		m_cTextColor;
	COLORREF		m_cTranspColor;
	CString			m_strImgPath;
	CString			m_strText;
	int				m_nHAlignCbo;
	int				m_nVAlignCbo;
	CEdit*			m_pWidget;


};

#endif 
