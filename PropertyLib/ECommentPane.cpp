// ECommentPane.cpp: implementation of the ECommentPane class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ECommentPane.h"
#include "hoverbutton.h"
#include "EPropCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


IMPLEMENT_DYNCREATE(ECommentPane, CWnd)

BEGIN_MESSAGE_MAP( ECommentPane , CWnd )
	//{{AFX_MSG_MAP(ECommentPane)
	ON_WM_PAINT()
	ON_BN_CLICKED( 1 , OnMinimizeButton )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


ECommentPane::ECommentPane()
{
	m_bMinimized = false;
	m_pHoverButton = NULL;
}

ECommentPane::~ECommentPane()
{
	if( m_pHoverButton != NULL )
	{
		delete m_pHoverButton;
	}
}

void ECommentPane::OnPaint()
{
	CPaintDC dc(this);

	CRect r;

	GetClientRect(&r);


	CFont f;

	dc.SetBkColor(RGB(255,255,255));

	CRect rlef = r;
	CRect rrig = r;

	rlef.right = 17;
	rrig.left  = rlef.right;

	dc.FillSolidRect( r , ::GetSysColor(COLOR_3DFACE  ));
//	dc.DrawEdge( rlef , BDR_RAISEDOUTER , BF_RECT );
//	dc.DrawFrameControl( rlef , DFC_CAPTION , 

	rrig.DeflateRect(2,2);

	if( m_bMinimized )
	{
		f.CreateFont( 13 , 0, 0, 0, FW_BOLD, FALSE,	FALSE,
			0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH , "tahoma" );
		dc.SelectObject(&f);

		dc.DrawText( "Info..." , rrig , DT_SINGLELINE );
	}
	else
	{
		f.CreateFont( 13 , 0, 0, 0, FW_MEDIUM, FALSE,	FALSE,
			0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH , "tahoma" );
		dc.SelectObject(&f);

//		dc.DrawEdge( rlef , BDR_RAISEDINNER , BF_RECT );
		dc.DrawText( m_sComment , rrig , DT_LEFT | DT_WORDBREAK );
	}

//	dc.DrawEdge( r , BDR_RAISEDINNER , BF_RECT );

}

BOOL ECommentPane::Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	BOOL bResult = CWnd::Create(lpszClassName,lpszWindowName,dwStyle,rect,pParentWnd,nID,pContext);

	if( bResult )
	{
		if( m_pHoverButton != NULL )
		{
			delete m_pHoverButton;
		}
		m_pHoverButton = new CHoverButton();

		CRect r(0,0,13,13);
		r.OffsetRect( 2 , 2 );

		m_pHoverButton->Create( m_pHoverButton->GetRuntimeClass()->m_lpszClassName , BS_OWNERDRAW | WS_CHILD | WS_VISIBLE , r , this , 1 );
	}

	return bResult;

}

void ECommentPane::SetComment( const CString& sComment )
{
	m_sComment = sComment;
	Invalidate();
}

int ECommentPane::GetHeight()
{
	int nHeight = 13*3 + 4;	//text + edge;

	if( m_bMinimized )
	{
		nHeight = 17;
	}

	return nHeight;
}

void ECommentPane::OnMinimizeButton()
{
	m_bMinimized = !m_bMinimized;
//	TRACE("click\n");

	EPropCtrl* pParent = (EPropCtrl*)GetParent();
	pParent->ChildSizeChanged();

	m_pHoverButton->SetState( !m_bMinimized );
}