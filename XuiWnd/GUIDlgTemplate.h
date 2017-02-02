// DynDlgTemplate.h: interface for the CDynDlgTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNDLGTEMPLATE_H__3102197B_49F1_435A_BE85_F834F517EF35__INCLUDED_)
#define AFX_DYNDLGTEMPLATE_H__3102197B_49F1_435A_BE85_F834F517EF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "XUIFramework.h"

class CDynDlgTemplate  
{
public:
	
	enum ControlType
	{
		CTLTYPE_LISTVIEW   = 0x53,
		CTLTYPE_BUTTON     = 0x80,
		CTLTYPE_EDIT       = 0x81,
		CTLTYPE_STATIC     = 0x82,
		CTLTYPE_LISTBOX    = 0x83,
		CTLTYPE_SCROLLBAR  = 0x84,
		CTLTYPE_COMBOBOX   = 0x85
	};

public:
	CDynDlgTemplate(HWND hWnd, CXUIFramework* pDynContainer);
	virtual ~CDynDlgTemplate();

	void	BuildFromTemplate(int nIDD);
	BOOL	ExtractInfo();
	void	MapRectDialog(CRect& rect, int &x, int &y, int &cx, int &cy);
	int		SkipOrdinalOrTextField(LPBYTE* pplDlgResource, CString* pstrTextValue = NULL);

private:
	
	HWND			m_hWnd;
	CXUIFramework*	m_pDynContainer;
	LPBYTE			m_pDlgRes;
	CString			m_strDialogFont;
	WORD			m_wpSize;

};

#endif // !defined(AFX_DYNDLGTEMPLATE_H__3102197B_49F1_435A_BE85_F834F517EF35__INCLUDED_)
