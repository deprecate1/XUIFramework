// TestView.cpp : implementation file
//

#include "stdafx.h"
#include "GuiBaker.h"
#include "TestView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CDynWnd<CView>)
	//{{AFX_MSG_MAP(CTestView)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FULL_SCREEN_MODE, OnFullScreenMode)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands

#if _MFC_VER >= 0x0700
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_SCREENDESIGNER,	ScreenDesigner)
	ON_MESSAGE(WM_DROPCONTROL,		AddDropControl)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()

	// command handlers for controls (FOR VS .NET)
	ON_COMMAND(ID_XUIFRAME,				OnButtonFrame)
	ON_COMMAND(ID_DYNBUTTONPICTURE,		OnButtonpicture)
	ON_COMMAND(ID_XUIEDIT,				OnButtonedit)
	ON_COMMAND(ID_DYNBUTTONEDITMULTI,	OnButtonmledit)
	ON_COMMAND(ID_DYNBUTTONLABEL,		OnButtonlabel)
	ON_COMMAND(ID_DYNBUTTONCOMBO,		OnButtoncombo)
	ON_COMMAND(ID_DYNBUTTONGROUP,		OnButtongroup)
	ON_COMMAND(ID_DYNBUTTONCHECK,		OnButtoncheck)
	ON_COMMAND(ID_DYNBUTTONRADIO,		OnButtonradio)
	ON_COMMAND(ID_DYNBUTTONDATE,		OnButtondate)
	// end of command handlers for controls

	ON_COMMAND(ID_DYNBUTTONLEFTALIGN,	OnButtonLeftAlign)
	ON_COMMAND(ID_DYNBUTTONRIGHTALIGN,	OnButtonRightAlign)
	ON_COMMAND(ID_DYNBUTTONTOPALIGN,	OnButtonTopAlign)
	ON_COMMAND(ID_DYNBUTTONBOTTOMALIGN, OnButtonBottomAlign)
	ON_COMMAND(ID_DYNBUTTONMAKESAMEWIDTH,OnButtonMakeSameWidth)
	ON_COMMAND(ID_DYNBUTTONMAKESAMEHEIGHT, OnButtonMakeSameHeight)
	ON_COMMAND(ID_DYNBUTTONMAKESAMESIZE, OnButtonMakeSameSize)
	ON_COMMAND(ID_DYNBUTTONTOGGLEGRID,	ShowGrid)


#endif

	ON_COMMAND(ID_FILE_PRINT,			CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT,	CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW,	CView::OnFilePrintPreview)
END_MESSAGE_MAP()


CTestView::CTestView()
: CDynWnd<CView>()
{
	//{{AFX_DATA_INIT(CTestView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pOpt			= CSettings::getInstance();
	m_bIsFull		= false;
	m_pContextMenu	= NULL;
	m_pOldParentWnd = NULL;
	m_bColor		= FALSE;



	m_nXMLTmp = 0;



	// Context menu
	m_pContextMenu = new CMenu();

	if (!m_pContextMenu->LoadMenu(IDR_CONTEXT)){
		AfxMessageBox("Impossible de créer le menu contextuel");
	}

	//CMisc::Message("Value 0x%x", m_cBkLowColor);
}

CTestView::~CTestView()
{
	
}

void CTestView::OnDestroy() 
{
	CDynWnd<CView>::OnDestroy();
	
	
	if (m_pContextMenu)
		delete m_pContextMenu;
}




void CTestView::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestView)
	//DDX_Control(pDX, IDC_FLECHED, m_staFlecheD);
	//DDX_Control(pDX, IDC_FLECHEG, m_staFlecheG);
	//DDX_Control(pDX, IDC_BANNER, m_pctBanner);
	//DDX_Control(pDX, IDC_LABEL7, m_staLabel7);
	//DDX_Control(pDX, IDC_LABEL8, m_staLabel8);
	//DDX_Control(pDX, IDC_TEXT_DISPLAY, m_staDisplay);
	//}}AFX_DATA_MAP
}


void CTestView::OnInitialUpdate() 
{
	CDynWnd<CView>::OnInitialUpdate(_T("gui.xui"));

	m_staFlecheD = XUICTRL(*this, "ID_FLECHED", CxStatic);
	m_staFlecheG = XUICTRL(*this, "ID_FLECHEG", CxStatic);
	m_staDisplay = XUICTRL(*this, "ID_DISPLAY", CPPHtmlStatic);
	m_staLabel7  = XUICTRL(*this, "ID_LABEL7",  CxStatic);
	m_staLabel8  = XUICTRL(*this, "ID_LABEL8",  CxStatic);


	if (m_staFlecheD == NULL || m_staFlecheG == NULL ||
		m_staDisplay == NULL || m_staLabel7 == NULL || 
		m_staLabel8 == NULL)
		return;

	// Main Display
	m_staDisplay->SetBkColor(RGB(255,255,255));
	m_staDisplay->SetFont("Arial", 60, FW_BOLD);

	m_staLabel7->SetTransparent(TRUE);
	m_staLabel7->SetFont("Arial", 18, FW_BOLD);
	
	m_staLabel8->SetTransparent(TRUE);
	m_staLabel8->SetFont("Arial", 18, FW_BOLD);
}






/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers


void CTestView::OnDraw(CDC* pDC)
{
	CDynWnd<CView>::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CPersoGraphiqueView printing


BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	AfxMessageBox("Je print\n");
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	AfxMessageBox("Je print\n");
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	AfxMessageBox("Je print\n");
	// TODO: add cleanup after printing
}


void CTestView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (!m_bInScreenDesignerMode){

		ClientToScreen(&point);
		if(m_pContextMenu->GetSubMenu(0)){
			CMenu *pSubMenu= m_pContextMenu->GetSubMenu(0);

			/*
			if(m_bIsFull){
				pSubMenu->MenuItem(ID_FULL_SCREEN_MODE,MF_CHECKED );
			}
			else{
				pSubMenu->CheckMenuItem(ID_FULL_SCREEN_MODE,MF_UNCHECKED );
			}
			*/

			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
				point.x,point.y,this);
		}
	}

	CDynWnd<CView>::OnRButtonDown(nFlags, point);
}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	 SHORT VKControl = GetAsyncKeyState(VK_CONTROL);
	 SHORT VKShift   = GetAsyncKeyState(VK_SHIFT);
	
		
	CDynWnd<CView>::OnKeyDown(nChar, nRepCnt, nFlags);
}


