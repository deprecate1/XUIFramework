// PageContact.h : header file
//


#ifndef _PAGECONTACT_H__INCLUDED_
#define _PAGECONTACT_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreePropSheetEx/ResizablePage.h"
#include "TreePropSheetEx/TreePropSheetUtil.hpp"

//#include "CxButton/BtnST.h"
#include "GuiBaker.h"


/////////////////////////////////////////////////////////////////////////////
// CPageContact dialog

class CPPgGeneral
 : public CResizablePage,
   public TreePropSheet::CWhiteBackgroundProvider
{
	DECLARE_DYNCREATE(CPPgGeneral)

// Construction
public:
	CPPgGeneral();
	~CPPgGeneral();

// 
// Dialog Data
	//{{AFX_DATA(CPPgGeneral)
	enum { IDD = IDD_PPG_GENERAL };
	CButton	m_btnReaderStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPgGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPgGeneral)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG







	CSettings*	m_pOpt;

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // _PAGECONTACT_H__INCLUDED_
