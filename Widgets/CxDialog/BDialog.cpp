// BDialog.cpp : implementation file
//

#include "stdafx.h"
#include "BDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBDialog dialog


CBDialog::CBDialog(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CBDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	// LIBRARY TO DRAW COLOR GRADIENTS
	hinst_msimg32 = LoadLibrary( "msimg32.dll" );
	if( hinst_msimg32 ){
		dllfunc_GradientFill = ((LPFNDLLFUNC) GetProcAddress( hinst_msimg32, "GradientFill" ));
	}
}


BEGIN_MESSAGE_MAP(CBDialog, CDialog)
	//{{AFX_MSG_MAP(CBDialog)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBDialog message handlers

BOOL CBDialog::OnEraseBkgnd(CDC* pDC)
{
	CDialog::OnEraseBkgnd(pDC);


	CRect rect;
	GetClientRect(&rect);
	rect.top += 144;

	/*
	int r1=0,g1=263,b1=230; //Any start color
	int r2=127,g2=127,b2=127; //Any stop color

	for(int i=0;i<rect.Height();i++)
	{
	    int r,g,b;
	    r = r1 + (i * (r2-r1) / rect.Height());
	    g = g1 + (i * (g2-g1) / rect.Height());
	    b = b1 + (i * (b2-b1) / rect.Height());
	    pDC->FillSolidRect(0,i,rect.Width(),1,RGB(r,g,b));
	}
	*/

	COLORREF m_crLoColor= RGB(0, 163, 230);
	COLORREF m_crHiColor= RGB(127, 127, 127);
	
	


	TRIVERTEX rcVertex[2];
	rcVertex[0].x=rect.left;
	rcVertex[0].y=rect.top;
	rcVertex[0].Red=GetRValue(m_crLoColor)<<8;
	rcVertex[0].Green=GetGValue(m_crLoColor)<<8;
	rcVertex[0].Blue=GetBValue(m_crLoColor)<<8;
	rcVertex[0].Alpha=0x0000;
	rcVertex[1].x=rect.right;
	rcVertex[1].y=rect.bottom;
	rcVertex[1].Red=GetRValue(m_crHiColor)<<8;
	rcVertex[1].Green=GetGValue(m_crHiColor)<<8;
	rcVertex[1].Blue=GetBValue(m_crHiColor)<<8;
	rcVertex[1].Alpha=0;

	GRADIENT_RECT grect;
	grect.UpperLeft=0;
	grect.LowerRight=1;

	dllfunc_GradientFill( *pDC ,rcVertex,2,&grect,1,GRADIENT_FILL_RECT_V);
	
	return true;
}

void CBDialog::SetBitmapStyle(int style)
{
	

}

int CBDialog::SetBitmap(UINT nIDResource)
{
	if(m_bitmap.LoadBitmap(nIDResource))
		return 0;
	else
		return 1;//error
}
