

#ifndef _DYNDROPTARGET_
#define _DYNDROPTARGET_

/////////////////////////////////////////////////////////////////////////////
// CDynDropTarget command target

class CDynDropTarget : public COleDropTarget
{
	DECLARE_DYNCREATE(CDynDropTarget)

	CDynDropTarget();           // protected constructor used by dynamic creation

// Attributes
public:
	UINT m_nIDClipFormat;

// Operations
public:
	virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual BOOL OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point );
	virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynDropTarget)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDynDropTarget();

	// Generated message map functions
	//{{AFX_MSG(CDynDropTarget)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif