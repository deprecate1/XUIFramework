// PPGGeneral.cpp : implementation file
//


#include "stdafx.h"
#include "PPgGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPgGeneral property page

IMPLEMENT_DYNCREATE(CPPgGeneral, CResizablePage)

#pragma warning(push)
#pragma warning(disable: 4355)      // Fine, we only store the pointer.

CPPgGeneral::CPPgGeneral()
 : CResizablePage(CPPgGeneral::IDD)
{
	//{{AFX_DATA_INIT(CPPgGeneral)
	//}}AFX_DATA_INIT

  m_pOpt = CSettings::getInstance();

  m_psp.dwFlags &= (~PSP_HASHELP);
  m_psp.dwFlags |= PSP_USEHICON;
  HICON hIconTab = AfxGetApp()->LoadIcon( IDI_CONTACT );
  m_psp.hIcon = hIconTab;
}

#pragma warning(pop)

CPPgGeneral::~CPPgGeneral()
{
}

void CPPgGeneral::DoDataExchange(CDataExchange* pDX)
{
	CResizablePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPgGeneral)
	DDX_Control(pDX, IDC_STATUS_BTN, m_btnReaderStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPgGeneral, CResizablePage)
	//{{AFX_MSG_MAP(CPPgGeneral)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPgGeneral message handlers

BOOL CPPgGeneral::OnInitDialog() 
{
	CResizablePage::OnInitDialog();
	
	// Preset layout
	/*UINT arrCtlID1[]={
		IDC_GROUPBOX_GNRAL,
		IDC_LABEL_TYPEBORNE,
		IDC_LABEL_BORNEID};	
	AddAnchorList(arrCtlID1, 3, TOP_LEFT);
	
	UINT arrCtlID2[]={
		IDC_GROUPBOX_COUPLEUR,
		IDC_LABEL_COUPLEUR,
		IDC_LABEL_COMPORT,
		IDC_LABEL_SAMADDR,
		IDC_LABEL_LOG_READER,
		IDC_COMBO_COUPLEUR_MODEL,
		IDC_EDIT_READER_COMPORT,
		IDC_EDIT_SAMADDR,
		IDC_COMBO_LOGREADER
	};	
	AddAnchorList(arrCtlID2, 9, TOP_RIGHT);*/
	
	

	
	//AddAnchor(IDC_GROUPBOX_GNRAL, TOP_LEFT);
	//AddAnchor(IDC_GROUPBOX_COUPLEUR, TOP_RIGHT);
	
	//m_btnReaderStatus.SetFlat(FALSE);
	
		





	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CPPgGeneral::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if( HasWhiteBackground() )
  {
    pDC->SetBkMode(TRANSPARENT);
    return ::GetSysColorBrush( COLOR_WINDOW );
  }

	return  CResizablePage::OnCtlColor(pDC, pWnd, nCtlColor);
}
