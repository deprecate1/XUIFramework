#if !defined(AFX_CXFRAME_H__0F241406_64BF_4FA1_9885_02C8E417F6BA__INCLUDED_)
#define AFX_CXFRAME_H__0F241406_64BF_4FA1_9885_02C8E417F6BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CxFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CxFrame window

class CxFrame : public CWnd
{
// Construction
public:
	CxFrame();

// Attributes
public:

// Operations
public:



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CxFrame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CxFrame)
	afx_msg void OnPaint();
	//}}AFX_MSG


	BOOL	m_bGrid;



	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXFRAME_H__0F241406_64BF_4FA1_9885_02C8E417F6BA__INCLUDED_)
