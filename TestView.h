#if !defined(AFX_TESTVIEW_H__B4B316BA_1E29_482F_86C4_C17D42EB18DB__INCLUDED_)
#define AFX_TESTVIEW_H__B4B316BA_1E29_482F_86C4_C17D42EB18DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "XuiWnd.h"
#include "cxstatic/cxstatic.h"
#include "cxpicture/cxpicture.h"
#include "cstatichtml/PPHtmlStatic.h"
#include "Rgbcolor.h"




class CMultimediaTimer;
class CSchedulerCallback;


class CTestView : public CDynWnd<CView>
{

	friend class CGuiBakerApp;

protected:
	CTestView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestView)


// Form Data
public:
	//{{AFX_DATA(CTestView)
	enum { IDD = IDD_TEST_VIEW };
	//CxStatic		m_staFlecheD;
	//CxStatic		m_staFlecheG;
	//CxPicture		m_pctBanner;
	//CPPHtmlStatic	m_staLabel7;
	//CPPHtmlStatic	m_staLabel8;
	//CPPHtmlStatic	m_staDisplay;
	//}}AFX_DATA

	CxStatic*		m_staFlecheD;
	CxStatic*		m_staFlecheG;
	CPPHtmlStatic*  m_staDisplay;
	CxStatic*		m_staLabel7;
	CxStatic*		m_staLabel8;



// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL


// Implementation
protected:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	


	CMenu*	m_pContextMenu;
	boolean m_bIsFull;
	CWnd*	m_pOldParentWnd;
	BOOL	m_bColor;
	
	// Borne settings
	CSettings*			m_pOpt;


	
	// XML attributes- 
	CString				m_csXMLTmp;
	CString				m_csXMLTag;
	int					m_nXMLTmp;
	

	



	

	// Generated message map functions
	//{{AFX_MSG(CTestView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__B4B316BA_1E29_482F_86C4_C17D42EB18DB__INCLUDED_)
