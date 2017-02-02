

#ifndef _CGUIPicture_H__
#define _CGUIPicture_H__

#include "GUIElement.h"

class CGUIPicture : public CGUIElement  
{
public:

	CGUIPicture();
	virtual ~CGUIPicture();

	virtual void	Initialize();
	virtual int		Create(CWnd* pParent, CRect WidgetRect);
	//virtual void	OnDraw(CDC* pDC);
	virtual void	GetProperties(EPropList& PropList);

protected:

	COLORREF		m_cBkColor;
	COLORREF		m_cTextColor;
};

#endif
