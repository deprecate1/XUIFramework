// GUIElement.h: interface for the CGUIElement class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CGUIElement_H__
#define _CGUIElement_H__


#include "../PropertyLib\IPropertyHost.h"
#include "../tinyxml.h"

class CGUIElement  : public CObject, public IPropertyHost 
{
public:
	CGUIElement();
	virtual ~CGUIElement();

	virtual void	Initialize();
	virtual int		Create(CWnd* pParent, CRect WidgetRect = CRect(-1,-1,-1,-1));
	virtual void	OnDraw(CDC* pDC);
	virtual bool	PropertyChanging( const void* pvProperty , void* pvNewValue );
	virtual void	GetProperties(EPropList& PropList);
	virtual int		GetHighestID();
	virtual	int		GetID(void);
	virtual void	SetID(ULONG nID,BOOL bSetName = FALSE);
	virtual	LPCTSTR	GetName(){ return m_strName; }
	virtual	void	SetName();
	virtual	void	SetName( CString strName);
	virtual	CRect	GetRect();
	virtual	void	SetRect(const CRect& rect);
	virtual void	SetPos(CPoint pos);
	virtual void	SetSize(CSize size);
	virtual	void	SetOrgRect(const CRect& rect);
	virtual void	CopyRect(LPRECT rect);
	virtual CWnd*	GetWnd();
	virtual CPoint	GetRandomPoint();
	virtual void	SetNotMoveable(BOOL bFlag = TRUE); 
	virtual BOOL	IsMoveable();
	virtual	int		LoadXML(TiXmlElement* pDataNode);
	virtual	int		SaveXML(TiXmlElement* pDataNode);

protected:
	int				m_nHighestID;
	ULONG			m_nID;
	CString			m_strName;
	CString			m_strPropTmp;
	CWnd*			m_pRootWnd;
	HWND			m_hRootWnd;
	CWnd*			m_pElementWnd;
	CGUIElement*	m_pRootElement;
	CRect			m_rectElement;
	CRect			m_rectOrgElement;
	CSize			m_DefaultSize;
	BOOL			m_bRootWnd;
	BOOL			m_bIsMoveable;

	//Properties
	CString			m_strElementType;
	CString			m_strPropPos;
	CString			m_strPropSize;
	bool			m_bHasImage;
	CString			m_strImgType;
	int				m_nImgWidth;
	int				m_nImgHeight;

	static int		random_range(int lowest_number, int highest_number);
};

#endif
