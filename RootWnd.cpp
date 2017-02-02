// RootWnd.cpp : implementation file
//

#include "stdafx.h"
#include "borne.h"
#include "RootWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRootWnd

CRootWnd::CRootWnd()
{
}

CRootWnd::~CRootWnd()
{
}


BEGIN_MESSAGE_MAP(CRootWnd, CWnd)
	//{{AFX_MSG_MAP(CRootWnd)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRootWnd message handlers

BOOL CRootWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect( rect );

	pDC->SelectObject( CStdGrfx::darkshadowPen() );
	pDC->SelectObject( CStdGrfx::dialogBrush() );

	pDC->Rectangle( rect );
	rect.InflateRect( -1, -1 );
	CStdGrfx::draw3dFrame( pDC, rect );

	pDC->SelectStockObject( BLACK_PEN );
	pDC->SelectStockObject( WHITE_BRUSH );

	
	return CWnd::OnEraseBkgnd(pDC);
}
