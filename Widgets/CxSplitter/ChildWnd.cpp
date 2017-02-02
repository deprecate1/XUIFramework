#include "stdafx.h"
//#include "SimpleSplitterApp.h"
#include "ChildWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildWnd

BEGIN_MESSAGE_MAP(CChildWnd, CWnd)
	//{{AFX_MSG_MAP(CChildWnd)
	ON_WM_PAINT()
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CChildWnd::CChildWnd()
{}

CChildWnd::~CChildWnd()
{}

void CChildWnd::OnPaint() 
{
	CPaintDC dc(this);
	CFont font;
	CRect rcClient;
	LOGBRUSH lb;

	CBrush::FromHandle((HBRUSH)::GetClassLong(m_hWnd, GCL_HBRBACKGROUND))->GetLogBrush(&lb);
	dc.SetBkColor(lb.lbColor);
	font.CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, "Times New Roman");
	dc.SelectObject(&font);
	dc.SetTextAlign(TA_TOP | TA_CENTER);
	GetClientRect(&rcClient);
	dc.ExtTextOut(rcClient.CenterPoint().x, 50, ETO_OPAQUE, NULL, CString("Simple splitter pane"), NULL);
}

void CChildWnd::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	lpwndpos->flags |= SWP_NOCOPYBITS;
	CWnd::OnWindowPosChanging(lpwndpos);
}
