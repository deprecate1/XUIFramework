// EPropCtrl.cpp: implementation of the EPropCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EPropCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropCtrl::EPropCtrl()
{
	m_nTabHeight = 30;
	m_PropListCtrl.m_pCommentPane = &m_CommentPane;
	m_bCommentPaneEnabled = false;
}

EPropCtrl::~EPropCtrl()
{

}

IMPLEMENT_DYNCREATE(EPropCtrl, CWnd)

BEGIN_MESSAGE_MAP(EPropCtrl, CWnd)
	//{{AFX_MSG_MAP(EPropCtrl)
	ON_NOTIFY(TCN_SELCHANGE, 1 , OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void EPropCtrl::Create( CWnd* pParent , int nDestinationCWndID )
{
	CRect r;
	CWnd* pWnd = pParent->GetDlgItem( nDestinationCWndID );
	pWnd->GetWindowRect(&r);
	pParent->ScreenToClient(&r);
	pWnd->DestroyWindow();
	Create( pParent , r );
}

void EPropCtrl::Create( CWnd* pParent , const CRect& rect , IPropertyChangeListener* pListener )
{
	//
	// create myselc
	//
	CRuntimeClass* rtc = GetRuntimeClass();

	CWnd::Create( NULL , GetRuntimeClass()->m_lpszClassName , WS_VISIBLE | WS_CHILD , rect , pParent , -1 );

	//
	// adjust rect for tab control
	//

	int w = rect.Width();
	int h = rect.Height();


	int y0 = 0;
	int y1 = h-m_nTabHeight-m_CommentPane.GetHeight();
	int y2 = h-m_nTabHeight;
	int y3 = h;

	
	CRect r( 0 , 0 , w , 0 );


	r.top    = y0;
	r.bottom = y1;
	m_PropListCtrl.Create( NULL , m_PropListCtrl.GetRuntimeClass()->m_lpszClassName , WS_VISIBLE | WS_CHILD , r , this , -1 );

	r.top    = y1;
	r.bottom = y2;
	m_CommentPane.Create( NULL , m_CommentPane.GetRuntimeClass()->m_lpszClassName , WS_VISIBLE | WS_CHILD , r , this , 2 );

	r.top    = y2;
	r.bottom = y3;
	m_TabCtrl.Create( WS_VISIBLE | WS_CHILD | TCS_RIGHT , r , this , 1 );
	m_TabCtrl.SetFont( m_PropListCtrl.GetFont() );

	//
	//
	//
	SetPropertyChangeListener(pListener);
}

void EPropCtrl::SetImageList( int nBitmapID , int nIconWidth , COLORREF nTransparentColor )
{
	m_ImageList.DeleteImageList();
	m_ImageList.Create( nBitmapID , nIconWidth , 10 , nTransparentColor );
	m_TabCtrl.SetImageList(&m_ImageList);
}

void EPropCtrl::Resize( const CRect& Rect ) 
{
	MoveWindow(Rect);

	int cx = Rect.Width();
	int cy = Rect.Height();

	int nTabHeight = m_nTabHeight;
	int nComHeight = m_bCommentPaneEnabled ? m_CommentPane.GetHeight() : 0;

	if( m_PropListCtrl.GetPropertyList()->HasUserTabs() )
	{
		m_TabCtrl.ShowWindow(SW_SHOW);
	}
	else
	{
		nTabHeight = 0;
		m_TabCtrl.ShowWindow(SW_HIDE);
	}

	if( nComHeight > 0 )
	{
		m_CommentPane.ShowWindow(SW_SHOW);
	}
	else
	{
		m_CommentPane.ShowWindow(SW_HIDE);
	}

	int nPropPaneHeight = cy - nComHeight - nTabHeight;

	CRect r( 0 , 0 , cx , 0 );
	
	r.top    = 0;
	r.bottom = nPropPaneHeight;
	m_PropListCtrl.MoveWindow(&r);

	r.top    = r.bottom;
	r.bottom = r.top + nTabHeight;
	m_TabCtrl.MoveWindow(&r);

	r.top    = r.bottom;
	r.bottom = r.top + nComHeight;
	m_CommentPane.MoveWindow(&r);
}


void EPropCtrl::SetPropertyChangeListener( IPropertyChangeListener* pListener )
{
	m_PropListCtrl.SetPropertyChangeListener( pListener );
}

void EPropCtrl::RefreshHostList()
{
	m_PropListCtrl.RefreshHostList();
	RefreshTabCtrl();
}

void EPropCtrl::RefreshTabCtrl()
{
	IPropertyHost* pHost = m_PropListCtrl.GetPropertyHost();

	m_TabCtrl.DeleteAllItems();

	if( pHost != NULL )
	{
		EPropList* pList = m_PropListCtrl.GetPropertyList();

		int nNumTabs = pList->GetTabCount();

		if( pList->HasUserTabs() )
		{
			for( int i=0 ; i<nNumTabs ; i++ )
			{
				EPropList::ETabGroup* pTab = pList->GetTab(i);
				CString* pName = pTab->GetName();
				int      nIcon = pTab->GetIcon();

				if( nIcon==-1 )
				{
					m_TabCtrl.InsertItem(i,*pName);
				}
				else
				{
					ASSERT( m_ImageList.GetSafeHandle()!=0 );	//dont' forget to SetImageList()
					m_TabCtrl.InsertItem(i,*pName,nIcon);
				}
			}

			int nActiveTab = m_PropListCtrl.GetPropertyList()->GetActiveTab();
			m_TabCtrl.SetCurSel( nActiveTab );
		}

		CRect r;
		GetWindowRect(&r);
		GetParent()->ScreenToClient(&r);
		Resize(r);

//		m_PropListCtrl.SetActiveTab(0);
	}
}


void EPropCtrl::SetPropertyHost( IPropertyHost* pHost )
{
//	IPropertyHost*pPrevHost = m_PropListCtrl.GetPropertyHost();
//	if(pPrevHost == pHost)
//		return;

	m_PropListCtrl.SetPropertyHost( pHost );

	//
	//
	//

	RefreshTabCtrl();
}

void EPropCtrl::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	int n = m_TabCtrl.GetCurSel();
	m_PropListCtrl.SetActiveTab(n);
}

void EPropCtrl::ChildSizeChanged()
{
	CRect r;
	GetWindowRect(&r);
	GetParent()->ScreenToClient(&r);
	Resize(r);
}

void EPropCtrl::EnableCommentPane( bool bEnable )
{
	m_bCommentPaneEnabled = bEnable;
	CRect r;
	GetWindowRect(&r);
	GetParent()->ScreenToClient(&r);
	Resize(r);
}
