#if !defined(AFX_ROOTWND_H__B0A80847_07AF_4C25_BA63_9FDC7F376B4C__INCLUDED_)
#define AFX_ROOTWND_H__B0A80847_07AF_4C25_BA63_9FDC7F376B4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RootWnd.h : header file
//

#include "StdGrfx.h"
/////////////////////////////////////////////////////////////////////////////
// CRootWnd window

class CRootWnd : public CWnd
{
// Construction
public:
	CRootWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRootWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRootWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRootWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOTWND_H__B0A80847_07AF_4C25_BA63_9FDC7F376B4C__INCLUDED_)
