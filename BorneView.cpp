// BorneView.cpp : implementation file
//

#include "stdafx.h"
#include "borne.h"
#include "BorneView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBorneView

IMPLEMENT_DYNCREATE(CBorneView, CView)

BEGIN_MESSAGE_MAP(CBorneView, CDynWnd<CView>)
	//{{AFX_MSG_MAP(CBorneView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBorneView::CBorneView()
:CDynWnd<CView>()
{
	TRACE("CBorneView\n");
}

CBorneView::~CBorneView()
{
	TRACE("~CBorneView\n");
}








/////////////////////////////////////////////////////////////////////////////
// CBorneView drawing

void CBorneView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CBorneView diagnostics

#ifdef _DEBUG
void CBorneView::AssertValid() const
{
	CView::AssertValid();
}

void CBorneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBorneView message handlers

void CBorneView::OnInitialUpdate() 
{

	
	CDynWnd<CView>::OnInitialUpdate();

	TRACE("CBorneView::OnInitialUpdate()\n");

	
	
	CRect rect;
	GetClientRect( rect );
	
	//m_editor.Create( WS_CHILD | WS_VISIBLE, rect, this, pDoc->GetData() );
	
}
