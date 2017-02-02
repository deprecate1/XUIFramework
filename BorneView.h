#if !defined(AFX_BORNEVIEW_H__26110042_D139_4AFE_AA91_D31AF39F8568__INCLUDED_)
#define AFX_BORNEVIEW_H__26110042_D139_4AFE_AA91_D31AF39F8568__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BorneView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBorneView view


#include "DynWnd.h"


class CBorneView : public CDynWnd<CView>
{
protected:
	CBorneView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBorneView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorneView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBorneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CBorneView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG



	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORNEVIEW_H__26110042_D139_4AFE_AA91_D31AF39F8568__INCLUDED_)
