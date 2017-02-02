// ECommentPane.h: interface for the ECommentPane class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_ECOMMENTPANE_H__B7BA3966_D957_4AC6_9CA2_38975CBE8B42__INCLUDED_
#define AFX_ECOMMENTPANE_H__B7BA3966_D957_4AC6_9CA2_38975CBE8B42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHoverButton;

class ECommentPane : public CWnd
{

	DECLARE_MESSAGE_MAP();
	DECLARE_DYNCREATE(ECommentPane);

protected:

	CHoverButton* m_pHoverButton;

	CString m_sComment;
	bool m_bMinimized;

public:

	ECommentPane();
	virtual ~ECommentPane();

protected:

	//{{AFX_MSG(ECommentPane)
	afx_msg void OnPaint();
	afx_msg void OnMinimizeButton();
	//}}AFX_MSG

public:

	virtual BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	void SetComment( const CString& sComment );
	int GetHeight();
};

#endif // !defined(AFX_ECOMMENTPANE_H__B7BA3966_D957_4AC6_9CA2_38975CBE8B42__INCLUDED_)
