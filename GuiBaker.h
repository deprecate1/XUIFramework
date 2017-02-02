// Borne.h : main header file for the BORNE application
//

#if !defined(AFX_BORNE_H__1E511F59_8C91_4CF2_B73F_A4C2C9A27B9E__INCLUDED_)
#define AFX_BORNE_H__1E511F59_8C91_4CF2_B73F_A4C2C9A27B9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols



// Objet accessible depuis toutes les vues
// A terme convertir cet appli en SDI
 


/////////////////////////////////////////////////////////////////////////////
// CGuiBakerApp:
// See Borne.cpp for the implementation of this class
//
class CGuiBakerApp : public CWinApp
{
public:
	CGuiBakerApp(LPCTSTR lpszAppName = NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiBakerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGuiBakerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	
	
	int		LoadSettings();
	

	CSettings*		m_pOpt;

	DECLARE_MESSAGE_MAP()
};

extern CGuiBakerApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORNE_H__1E511F59_8C91_4CF2_B73F_A4C2C9A27B9E__INCLUDED_)
