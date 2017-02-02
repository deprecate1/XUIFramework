// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GuiBaker.h"

#include "MainFrm.h"
#include "TestView.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SCREEN_DESIGNER, OnScreenDesigner)
	ON_COMMAND(ID_BORNE_DEMARRER, OnBorneDemarrer)
	//ON_COMMAND(ID_EDIT_OPTIONS, OnEditOptions)
	ON_COMMAND(ID_BORNE_VIEW, OnBorneView)
	ON_COMMAND(ID_HOME_VIEW, OnHomeView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	// Screen designer control bar
	if (!m_wndDynControlBar.CreateEx(this) ||
		!m_wndDynControlBar.LoadToolBar(IDR_XUICONTROLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	
	// screen Designer control bar
	m_wndDynControlBar.SetBarStyle(m_wndDynControlBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndDynControlBar.EnableDocking(0);
	DockControlBar(&m_wndDynControlBar);
	m_wndDynControlBar.SetWindowText(_T("XUI Resource toolbar"));
	ShowControlBar(&m_wndDynControlBar, FALSE, FALSE);
	


   // TODO: Delete these three lines if you don't want the toolbar to 
   //  be dockable 
   m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY); 

   EnableDocking(CBRS_ALIGN_ANY); 
   DockControlBar(&m_wndToolBar); //placement 1 toolbar 

   RecalcLayout(); 

    
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{

	//InitViews();

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnScreenDesigner() 
{
	CPoint x(500,100);
	FloatControlBar(&m_wndDynControlBar,x,CBRS_ALIGN_LEFT);
	BOOL bVisible = ((m_wndDynControlBar.GetStyle() & WS_VISIBLE) != 0);
	m_wndDynControlBar.m_bMakingVisible = TRUE;
	ShowControlBar(&m_wndDynControlBar, !bVisible, FALSE);
	m_wndDynControlBar.m_bMakingVisible = FALSE;
	RecalcLayout();
	GetActiveView()->SendMessage(WM_SCREENDESIGNER, !bVisible, 0);
	//SendMessageToDescendants(WM_SCREENDESIGNER, !bVisible, 0, TRUE, TRUE);	
}

void CMainFrame::OnBorneDemarrer() 
{

	
}


void CMainFrame::OnEditOptions() 
{
	//COptionsDlg dlg;

	//dlg.DoModal();
}

void CMainFrame::OnHomeView() 
{

}


void CMainFrame::OnBorneView() 
{

}


