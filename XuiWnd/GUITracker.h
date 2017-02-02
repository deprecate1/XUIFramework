#if !defined(AFX_GUITRACKER_H__56921C78_467D_4A31_A52B_DD280BD81343__INCLUDED_)
#define AFX_GUITRACKER_H__56921C78_467D_4A31_A52B_DD280BD81343__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "GUITrackerObject.h"

class CGUITracker : public CRectTracker  
{
public:
	CGUITracker();
	virtual ~CGUITracker();


// Attributes
private:
	CArray <CGUITrackerObject*, CGUITrackerObject*> m_pDynTrackerObjects; 
	CGUITrackerObject* m_pDynTrackerObject;
    CArray <CRect*, CRect*> m_CopyPosition; // array of rectangles, objects position copy.
	int		m_nGridSizeX;
	int		m_nGridSizeY;
	BOOL	m_bSnap;
	CWnd*	m_pWndParent;

// Operations
public:
	BOOL Track(CWnd* pWnd, CPoint point, BOOL bAllowInvert = FALSE, CWnd* pWndClipTo = NULL);
 	void Add(CRect rect, CWnd* pParentWnd, int nID, void* pObject);
	void Draw(CDC* pDC);
	int HitTest( CPoint point );
    void RemoveAll();
	BOOL SetCursor(CWnd* pWnd, UINT nHitTest);
	void AdjustLayout(int nOperation); 
	int GetSize() { return m_pDynTrackerObjects.GetSize(); }
	int GetIDSelected();
	void* GetObjectSelected();

private:
    BOOL MultiTrackHandle ( CWnd* pWnd, CPoint point, CWnd* pWndClipTo );
    void CopyPositions (); 
    void UpdateObjects (); 
    int HitTestHandles(CPoint point);
    void ClearPositions (); 

};

#endif // !defined(AFX_GUITRACKER_H__56921C78_467D_4A31_A52B_DD280BD81343__INCLUDED_)
