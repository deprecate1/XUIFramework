// CxFrame.cpp : implementation file
//

#include "stdafx.h"
#include "../StdGrfx.h"
#include "CxFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CxFrame

CxFrame::CxFrame()
{
	m_bGrid = TRUE;
}

CxFrame::~CxFrame()
{
}


BEGIN_MESSAGE_MAP(CxFrame, CWnd)
	//{{AFX_MSG_MAP(CxFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CxFrame message handlers

