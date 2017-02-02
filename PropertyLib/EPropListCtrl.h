
#ifndef EPROPLISTCTRL_H
#define EPROPLISTCTRL_H

class EProperty;
class IPropertyHost;

#include "EPropList.h"
#include "IPropertyChangeListener.h"
#include "EPropWnd.h"

class EPropListCtrl : public EPropWnd
{

private:

	IPropertyHost* m_pPropertyHost;

	bool m_bVScrollEnabled;
	bool m_bHScrollEnabled;

protected:

	CRect m_SplitRectCP;

	int m_nKeyColumnWidth;	//col are widths inclusive frame edge
	bool m_bAutoSizeKeyColumn;

	int m_nSplitWidth;
	int m_nValColumnWidth;


	int m_nMouseDownKeyColumnWidth;
	int m_nMouseDownMousePosition;


	int m_nViewWidth;

	//{{AFX_MSG(EPropListCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg void OnPaint();
	//}}AFX_MSG

	virtual CSize GetScrollPageSize( int nViewWidth , int nViewHeight );

protected:
		
	DECLARE_MESSAGE_MAP();
	DECLARE_DYNCREATE(EPropListCtrl);

protected:

	EPropList m_PropList;

	EProperty** m_pDrawnProperties;
	int m_nDrawnPropertiesSize;
	int m_nNumDrawnProperties;

public:
	
	//
	//
	//

	EPropListCtrl();
	virtual ~EPropListCtrl();

	//
	//
	//


//	#ifdef _DEBUG
//	virtual void AssertValid() const;
//	virtual void Dump(CDumpContext& dc) const;
//	#endif

	//{{AFX_VIRTUAL(EPropListCtrl)
	public:
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	protected:
//	virtual void OnInitialUpdate(); // called first time after construct
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:

	IPropertyHost* GetPropertyHost(){return m_pPropertyHost;}
	void SetPropertyChangeListener( IPropertyChangeListener* pListener );
	void SetPropertyHost( IPropertyHost* pHost );
	void RefreshHostList();
	void SetActiveTab(int i);
	EPropList* GetPropertyList();
	void EnableAutoSizeKeyColumn(bool bEnable=true)		{ m_bAutoSizeKeyColumn = bEnable; }

protected:

	void AutoSizeKeyColumn();
	void EnsureVisibility( EProperty* pProperty );
	void EnsureVisibility( const CRect& r );
	void StepSelection( int nStep );
	void OpenNode( EProperty* pProp );
	int  _UpdateDrawnPropertiesList( CDC* pDC , int y0 );

};

#endif
