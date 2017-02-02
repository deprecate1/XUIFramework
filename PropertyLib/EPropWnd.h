// EPropWnd.h: interface for the EPropWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EPROPWND_H__5E144A53_9017_412C_BB8C_14BB2407CA47__INCLUDED_)
#define AFX_EPROPWND_H__5E144A53_9017_412C_BB8C_14BB2407CA47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//static const UINT UWM_PROPERTY_LOOSING_FOCUS = ::RegisterWindowMessage(_T("EPROPERTYLIB_UWM_PROPERTY_LOOSING_FOCUS"));


class EProperty;
class IPropertyChangeListener;
class ECommentPane;

//PropWnd
//|
//+-- PropListCtrl
//|
//+-- GridCtrl


class EPropWnd : public CWnd
{

	DECLARE_MESSAGE_MAP();
	DECLARE_DYNCREATE(EPropWnd);

protected:

	IPropertyChangeListener* m_pChangeListener;
	COLORREF m_cLigh;
	COLORREF m_cPane;
	COLORREF m_cDark;
	COLORREF m_cOuts;
	CPen m_PenLigh;
	CPen m_PenDark;
	CFont m_Font;
	EProperty* m_pActiveProperty;
	int m_nFontHeight;
	int m_nEdgeWidth;

public:

	ECommentPane* m_pCommentPane;

	bool m_bApplyOnKillFocus;
	bool m_bCloseOnKillFocus;

protected:

	void NotifyPropertyChanged();
	void SetScrollPage( int nViewWidth , int nViewHeight );
	void SetActiveProperty( EProperty* pNewActiveProperty );

	virtual CSize GetScrollPageSize( int nViewWidth , int nViewHeight );

	void DrawFrame( CDC* pDC , const CRect& r , bool bRaised , int nColor );

public:

	EPropWnd();
	virtual ~EPropWnd();

	virtual void GetIDRange( int& nID_PROPERTY_RANGE_BEG , int& nID_PROPERTY_RANGE_END );

	void PropertyChanged();
	
	void OnDoPropApply();
	void OnDoPropClose();

	int GetFontHeight();


	COLORREF GetColorPaneKey();
	COLORREF GetColorPaneKeyActive();
	COLORREF GetColorPaneVal();
	COLORREF GetColorPaneValActive();

	CFont* GetFont();


	//{{AFX_MSG(EPropWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnEditKillFocus();
	//}}AFX_MSG
//	afx_msg LRESULT OnUwmEditKillFocus(WPARAM, LPARAM);

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

};

#endif // !defined(AFX_EPROPWND_H__5E144A53_9017_412C_BB8C_14BB2407CA47__INCLUDED_)
