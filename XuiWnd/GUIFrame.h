

#ifndef _CGUIFrame_H__
#define _CGUIFrame_H__

#include "GUIElement.h"
#include "../Widgets/cxframe/cxframe.h"

class CGUIFrame : public CGUIElement  
{
public:
	CGUIFrame();
	virtual ~CGUIFrame();

	virtual void	Initialize();
	virtual int		Create(CWnd* pParent, CRect WidgetRect);
	//virtual void	OnDraw(CDC* pDC);
	virtual bool	PropertyChanging( const void* pvProperty , void* pvNewValue );
	virtual void	GetProperties(EPropList& PropList);
	virtual	int		LoadXML(TiXmlElement* pDataNode);
	virtual int		SaveXML(TiXmlElement *pDataNode);

protected:
	CxFrame*		m_pWidget;
	CString			m_strCaption;

};

#endif 
