#if !defined(AFX_GUITRACKEROBJECT_H__64472A51_BF5D_4B52_B7F3_6E64A835AD3B__INCLUDED_)
#define AFX_GUITRACKEROBJECT_H__64472A51_BF5D_4B52_B7F3_6E64A835AD3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGUITrackerObject  
{
public:
	CGUITrackerObject();
	virtual ~CGUITrackerObject();

// Attributes
public:
	CRect	m_rect;
	CWnd*	m_pParentWnd;
	int		m_nID;
	void*	m_pObject;
	int		m_nStyle;
	BOOL	m_bFirst;

};

#endif // !defined(AFX_GUITRACKEROBJECT_H__64472A51_BF5D_4B52_B7F3_6E64A835AD3B__INCLUDED_)
