
#ifndef _XuiWnd_H__
#define _XuiWnd_H__

#include "XuiScreen.h"
#include "GUIElement.h"
#include "GUIFrame.h"
#include "GUIStatic.h"
#include "GUIPicture.h"
#include "GUILiteHtml.h"
#include "GUIEdit.h"
#include "GUITracker.h"
#include "GUIPropDlg.h"
#include "PropertyLib\IPropertyHost.h"
#include "../MainFrm.h"
#include "GUIDroptarget.h"
#include "tinyxml.h"

#ifndef ID_EDIT_GROUP
	#define ID_EDIT_GROUP		ID_EDIT_REDO + 1
	#define ID_EDIT_UNGROUP		ID_EDIT_GROUP + 1
#endif



using namespace std;
typedef list<CGUIElement*>			 CGUIElementList;
typedef list<CGUIElement*>::iterator CGUIElementIt;

typedef UINT (CALLBACK* LPFNDLLFUNC)(HDC,CONST PTRIVERTEX,DWORD,CONST PVOID,DWORD,DWORD);

// Provided for convenience
#define XUICTRL(window, name, type) \
    ((type*)((window).GetElementClass( GetID(name) )))

/////////////////////////////////////////////////////////////////////////////
// CDynWnd window

template <class BASECLASS>
class CDynWnd : public BASECLASS, public IPropertyHost
{
	typedef CDynWnd<BASECLASS> ThisClass;
	typedef BASECLASS TheBaseClass;

public:
	

	enum BackFillMode { Normal, HGradient, VGradient };


	// Construction
public:
	CDynWnd(int nIDD);
	CDynWnd(int nIDD, CWnd* pParent);
	CDynWnd();

	// Attributes
protected:

	// Filename for loading/saving
	CString				m_ResFileName;

	// Drawing limits
	CRect				m_rectDrawing;
	int					m_nIDD;
	CString				m_strElementType;

	// Background color
	int					m_nColorMode;
	COLORREF			m_cBkLowColor;
	COLORREF			m_cBkHiColor;
	int					m_nVoffset;
	CBrush*				m_pBrush;
	HINSTANCE			hinst_msimg32;
	LPFNDLLFUNC			dllfunc_GradientFill;

	// FullScreen
	bool				m_bIsFull;
	CWnd*				m_pOldParentWnd;

	// Our XUI elements
	BOOL				m_bInScreenDesignerMode;
	CGUIElementList		m_GUIElements;

	CWnd*				m_pParentWnd;
	CView*				m_pCurView;
	ULONG				m_nHighestID;
	BOOL				m_bRootParent;
	CGUIElement*		m_curXUIObj;
	map<long, LPCTSTR>  m_ResMap;

	// Design - TO REMOVE if you just want loading capabilities
	CDynDropTarget		m_DynDropTarget;
	CSettingsDlg		m_GUIPropertiesDlg;
	CMenu				m_menu;
	CGUITracker			m_DynTracker;
	BOOL				m_bFormView;
	int					m_nGridX;
	int					m_nGridY;
	CWnd*				m_pChildInScreenDesigner;
	BOOL				m_bShowGrid;

	// Operations
public:
	void	LoadScreen(LPCTSTR szFile);
	void	SaveScreen();
	void	Initialise();

	void	OnDraw(CDC* pDC);
	int		GetID(LPCTSTR szName);
	CWnd*	GetElementClass( int nID );
	void	DestroyControls();
	long	AddDropControl(WPARAM wParam, LPARAM lParam);
	BOOL	AddControl(LPCTSTR szClass, CPoint pos = CPoint(-1,-1), BOOL bSetAsNewRoot = FALSE);
	LPCTSTR GetCtrlType(long nCtrlID);
	long	GetCtrlType(LPCTSTR szResName);
	void	ToggleScreenMode(BOOL bScreenDesignMode);
	void	PreProcessResource(CString csIDDName);
	BOOL	OnInitDialog();
	void	OnInitialUpdate();
	void	OnInitialUpdate(LPCTSTR szFile);
	void	SetGridSize(int nX, int nY) { m_nGridX = nX; m_nGridY = nY; }
	BOOL	InScreenDesignerMode() { return m_bInScreenDesignerMode; }
	void	SetInScreenDesignerMode() { m_bInScreenDesignerMode = TRUE; ToggleScreenMode(TRUE); }
	void	SetChild(CWnd* pWnd) { TRACE("%d", m_nIDD); m_pChildInScreenDesigner = pWnd; }
	CWnd*	GetChild() { return m_pChildInScreenDesigner; }
	void	ShowPopup( CPoint point, CWnd* parent );
	void	SetBkColor( );
	void	DrawGradientFill(CDC* pDC, CRect* pRect, int nFillMode);
	void	ShowProperties(IPropertyHost* pHost);
	void	ShowPropertiesBar();
	bool	PropertyChanging( const void* pvProperty , void* pvNewValue );
	void	GetProperties(EPropList& PropList);
	void	SetParentWnd(CWnd* pParentWnd);
	void	OnFullScreenMode();


public:





	// Overrides
#if _MFC_VER >= 0x0700
public:
#endif
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynWnd)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg long ScreenDesigner(WPARAM wParam, LPARAM lParam);
	afx_msg long AddControl(WPARAM wParam, LPARAM lParam);
	afx_msg long DeleteControl(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);

	// message handlers for controls
	afx_msg void OnButtonFrame();
	afx_msg void OnButtonedit();
	afx_msg void OnButtonmledit();
	afx_msg void OnButtonlabel();
	afx_msg void OnButtonLiteHtml();
	afx_msg void OnButtoncombo();
	afx_msg void OnButtongroup();
	afx_msg void OnButtoncheck();
	afx_msg void OnButtondate();
	afx_msg void OnButtonradio();
	afx_msg void OnButtonpicture();
	// end of message handlers for controls

	afx_msg void OnButtonLeftAlign();
	afx_msg void OnButtonRightAlign();
	afx_msg void OnButtonTopAlign();
	afx_msg void OnButtonBottomAlign();
	afx_msg void OnButtonMakeSameWidth();
	afx_msg void OnButtonMakeSameHeight();
	afx_msg void OnButtonMakeSameSize();
	afx_msg void ShowGrid();
	afx_msg void OnSetTopWnd();

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_VIRTUAL
	virtual void OverrideVisible();

	// Implementation
public:
	virtual ~CDynWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDynWnd)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	static const AFX_MSGMAP* PASCAL GetBaseMessageMap();
	static const AFX_MSGMAP_ENTRY _messageEntries[];
	static const AFX_MSGMAP messageMap;
	virtual const AFX_MSGMAP* GetMessageMap() const;

};

template <class BASECLASS>
CDynWnd<BASECLASS>::CDynWnd(int nIDD)
: BASECLASS(nIDD)
{
	// constructor for baseclasses requiring a dialog
	TRACE(_T("CDynWnd<BASECLASS>::CDynWnd(int nIDD)\n"));
	m_bFormView	= TRUE;
	m_nIDD = nIDD;
	Initialise();
}

template <class BASECLASS>
CDynWnd<BASECLASS>::CDynWnd(int nIDD, CWnd* pParent)
: BASECLASS(nIDD, pParent)
{
	// constructor for baseclasses requiring a parent window and dialog ID
	TRACE(_T("CDynWnd<BASECLASS>::CDynWnd(int nIDD, CWnd* pParent)\n"));
	m_bFormView = TRUE;
	m_nIDD = nIDD;
	Initialise();

}

template <class BASECLASS>
CDynWnd<BASECLASS>::CDynWnd()
{
	Initialise();

	// Background color
	m_nVoffset		 = 0;
	m_nColorMode	 = 0;
	hinst_msimg32	 = NULL;
	m_cBkLowColor	 = RGB(255,255,255);
	m_cBkHiColor	 = RGB(255,255,255);
	m_pBrush         = new CBrush(m_cBkLowColor);

	// LIBRARY TO DRAW COLOR GRADIENTS
	hinst_msimg32 = LoadLibrary( "msimg32.dll" );
	if( hinst_msimg32 ){
		dllfunc_GradientFill = ((LPFNDLLFUNC) GetProcAddress( hinst_msimg32, "GradientFill" ));
	}

	// FullScreen
	m_pOldParentWnd	= NULL;
	m_bIsFull		= false;


	m_pCurView		= NULL;
	m_nHighestID	= 1000;
	m_bRootParent	= FALSE;
	m_pCurView		= this;
	m_pParentWnd	= (CWnd*) this;



}

template <class BASECLASS>
CDynWnd<BASECLASS>::~CDynWnd()
{
	// destructor
	TRACE(_T("CDynWnd<BASECLASS>::~CDynWnd()\n"));

	// Clean up
	if (m_pBrush){
		delete m_pBrush;
		m_pBrush = NULL;
	}

	if ( hinst_msimg32 )
		::FreeLibrary( hinst_msimg32 );

	m_ResMap.clear();

	// Destroy our controls
	DestroyControls();
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::DestroyControls()
{
	CGUIElement* pObject = NULL;

	CGUIElementIt pos;
	for( pos = m_GUIElements.begin(); pos != m_GUIElements.end(); ++pos){

		pObject = (CGUIElement*)( *pos );
		if (pObject){
			SAFEDEL(pObject);
		}
	}

	m_GUIElements.clear();
}





template <class BASECLASS>
int CDynWnd<BASECLASS>::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (BASECLASS::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_DynDropTarget.Register(this);
	m_DynDropTarget.m_nIDClipFormat = RegisterClipboardFormat("ScreenDesigner");

	return 0;
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::OverrideVisible()
{
	// override to show/hide any specific controls, after the screen designer has
	// shown or hidden them
	TRACE(_T("CDynWnd<BASECLASS>::OverrideVisible()\n"));
}


template <class BASECLASS>
void CDynWnd<BASECLASS>::Initialise()
{
	TRACE(_T("CDynWnd<BASECLASS>::Initialise()\n"));

	 // Map resource name and ID
	m_ResMap[ID_XUIFRAME]	= _T("Frame");
	m_ResMap[ID_XUIPICTURE]	= _T("Picture");
	m_ResMap[ID_XUILABEL]	= _T("Static");
	m_ResMap[ID_XUILITEHTML]= _T("LiteHtml");
	m_ResMap[ID_XUIEDIT]	= _T("EditBox");


	//m_nHighestID = 0;
	//CString csIDDName;
	//csIDDName.Format( _T("IDD_%d"),  m_nIDD);
	//PreProcessResource( csIDDName );
	m_bInScreenDesignerMode = FALSE;
	m_pChildInScreenDesigner = NULL;
	m_bShowGrid = FALSE;

	// default grid size
	m_nGridX = 5;
	m_nGridY = 5;


	//SetBkColor();
}


template <class BASECLASS>
void CDynWnd<BASECLASS>::OnFullScreenMode()
{
	//CString csDebug;


	//csDebug.Format("OnFullScreenMode : m_bIsFull=%d", m_bIsFull);
	//AfxMessageBox( csDebug );

	if(!m_bIsFull){
		m_bIsFull = true;
		m_pOldParentWnd=this->GetParent();

		this->SetParent(GetDesktopWindow());
		CRect rect;
		GetDesktopWindow()->GetWindowRect(&rect);
		this->SetWindowPos(&wndTopMost,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);
	}
	else{
		//TRACE("Je vais en plein ecran\n");
		m_bIsFull = false;
		this->SetParent( m_pOldParentWnd );
		( (CMainFrame *)AfxGetMainWnd() )->RecalcLayout();
	}
}


template <class BASECLASS>
int CDynWnd<BASECLASS>::GetID(LPCTSTR szName)
{
	CGUIElement*	pObject = NULL;

	CGUIElementIt pos = m_GUIElements.begin();
	while (pos != m_GUIElements.end() ) {
		pObject = (CGUIElement*)( *pos );

		if (!_tcsicmp( szName, pObject->GetName() ) ){
			return pObject->GetID();
		}

		pos++;
	}

	return 0;
}


template <class BASECLASS>
LPCTSTR CDynWnd<BASECLASS>::GetCtrlType(long nCtrlID)
{
		if (m_ResMap.find(nCtrlID) == m_ResMap.end() )
		return _T("");

	return m_ResMap[nCtrlID];
}

template <class BASECLASS>
long CDynWnd<BASECLASS>::GetCtrlType(LPCTSTR szCtrlID)
{
	map<long, LPCTSTR>::iterator it = NULL;

	for (it = m_ResMap.begin(); it != m_ResMap.end(); ++it){

		if ( !_tcsicmp(szCtrlID, (*it).second) )
			return (*it).first;
	}

	return 0;
}

//#define BEGIN_MESSAGE_MAP(theClass, baseClass) \
//	PTM_WARNING_DISABLE \
//	const AFX_MSGMAP* theClass::GetMessageMap() const \
//		{ return GetThisMessageMap(); } \
//	const AFX_MSGMAP* PASCAL theClass::GetThisMessageMap() \
//	{ \
//		typedef theClass ThisClass;						   \
//		typedef baseClass TheBaseClass;					   \
//		static const AFX_MSGMAP_ENTRY _messageEntries[] =  \
//		{

template <class BASECLASS> 
const AFX_MSGMAP* PASCAL CDynWnd<BASECLASS>::GetBaseMessageMap()
{
	// returns a pointer to the base class message map
	return &BASECLASS::messageMap;
}

// The functions below are the actual expanded macro definitions of BEGIN_MESSAGEMAP
template <class BASECLASS> 
const AFX_MSGMAP* CDynWnd<BASECLASS>::GetMessageMap() const
{ 
	return &CDynWnd<BASECLASS>::messageMap;
}

template <class BASECLASS> 
AFX_DATADEF const AFX_MSGMAP CDynWnd<BASECLASS>::messageMap =
#if _MFC_VER < 0x0700
{ CDynWnd<BASECLASS>::GetBaseMessageMap, &CDynWnd<BASECLASS>::_messageEntries[0]};
#else
{ CDynWnd<BASECLASS>::GetThisMessageMap, &CDynWnd<BASECLASS>::_messageEntries[0]};
#endif

template <class BASECLASS> 
const AFX_MSGMAP_ENTRY CDynWnd<BASECLASS>::_messageEntries[] =
{
		ON_WM_PAINT()
		ON_WM_ERASEBKGND()
		ON_WM_KEYDOWN()
		ON_MESSAGE(WM_SCREENDESIGNER,		&ThisClass::ScreenDesigner)
		ON_MESSAGE(WM_DROPCONTROL,			&ThisClass::AddDropControl)
		ON_WM_LBUTTONDOWN()
		ON_WM_RBUTTONDOWN()
		ON_WM_SETCURSOR()
		ON_WM_CREATE()

		// command handlers for controls
		//OnButtonFrame
		ON_COMMAND(ID_XUIFRAME,				&ThisClass::OnButtonFrame)
		ON_COMMAND(ID_DYNBUTTONPICTURE,		&ThisClass::OnButtonpicture)
		ON_COMMAND(ID_XUIEDIT,				&ThisClass::OnButtonedit)
		ON_COMMAND(ID_DYNBUTTONEDITMULTI,	&ThisClass::OnButtonmledit)
		ON_COMMAND(ID_DYNBUTTONLABEL,		&ThisClass::OnButtonlabel)
		ON_COMMAND(ID_XUILITEHTML,			&ThisClass::OnButtonLiteHtml)
		ON_COMMAND(ID_DYNBUTTONCOMBO,		&ThisClass::OnButtoncombo)
		ON_COMMAND(ID_DYNBUTTONGROUP,		&ThisClass::OnButtongroup)
		ON_COMMAND(ID_DYNBUTTONCHECK,		&ThisClass::OnButtoncheck)
		ON_COMMAND(ID_DYNBUTTONRADIO,		&ThisClass::OnButtonradio)
		ON_COMMAND(ID_DYNBUTTONDATE,		&ThisClass::OnButtondate)
		// end of command handlers for controls

		ON_COMMAND(ID_DYNBUTTONLEFTALIGN,	&ThisClass::OnButtonLeftAlign)
		ON_COMMAND(ID_DYNBUTTONRIGHTALIGN,	&ThisClass::OnButtonRightAlign)
		ON_COMMAND(ID_DYNBUTTONTOPALIGN,	&ThisClass::OnButtonTopAlign)
		ON_COMMAND(ID_DYNBUTTONBOTTOMALIGN, &ThisClass::OnButtonBottomAlign)
		ON_COMMAND(ID_DYNBUTTONMAKESAMEWIDTH,&ThisClass::OnButtonMakeSameWidth)
		ON_COMMAND(ID_DYNBUTTONMAKESAMEHEIGHT,&ThisClass::OnButtonMakeSameHeight)
		ON_COMMAND(ID_DYNBUTTONMAKESAMESIZE, &ThisClass::OnButtonMakeSameSize)
		ON_COMMAND(ID_DYNBUTTONTOGGLEGRID,	&ThisClass::ShowGrid)

		// command handlers for context menu
		ON_COMMAND(CMD_PROPERTIES, &ThisClass::ShowPropertiesBar)
		ON_COMMAND(CMD_UP, &ThisClass::OnSetTopWnd)
	{0,0,0,0,AfxSig_end, (AFX_PMSG)0}
};

template <class BASECLASS>
void CDynWnd<BASECLASS>::PreProcessResource(CString csIDDName)
{

}

template <class BASECLASS>
long CDynWnd<BASECLASS>::AddControl(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("qsdqsdqsdqds");
	return 0;
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::ShowGrid()
{
	// toggles the grid

	if (m_bShowGrid)
		m_bShowGrid = FALSE;
	else
		m_bShowGrid = TRUE;

	Invalidate();
}

template <class BASECLASS>
long CDynWnd<BASECLASS>::ScreenDesigner(WPARAM wParam, LPARAM lParam)
{
	// Message sent when screen is requested to toggle between screen designer and run mode


	m_bInScreenDesignerMode = wParam;
	m_DynTracker.RemoveAll();

	// comming out of screen designer mode
	if (!m_bInScreenDesignerMode)
	{
		m_GUIPropertiesDlg.DestroyWindow();

		if (m_pChildInScreenDesigner != NULL){
			m_pChildInScreenDesigner->SendMessage(WM_SCREENDESIGNER,wParam,lParam);
			m_pChildInScreenDesigner->PostMessage(WM_SYSCOMMAND,SC_CLOSE,0);
			m_pChildInScreenDesigner = NULL;
		}

		SaveScreen();
	}
	else
		ShowProperties(this);

	ToggleScreenMode(m_bInScreenDesignerMode);
	GetActiveWindow()->SetFocus();
	Invalidate();
	return 0;

}

template <class BASECLASS>
void CDynWnd<BASECLASS>::ToggleScreenMode(BOOL bScreenDesignMode)
{
	// Toggles screen between designer and run mode, normally used by ::ScreenDesigner

	/*
	// go through all the controls on the screen
	CDynControl* pDynControl;
	POSITION pos = m_ptrDynControls.GetHeadPosition();
	while (pos)
	{
		pDynControl = (CDynControl*)m_ptrDynControls.GetNext(pos);
		if (bScreenDesignMode)
		{
			// show any windows which may of have been hidden
			GetDlgItem(pDynControl->GetID())->ShowWindow(SW_NORMAL);
			pDynControl->EnableWindow(FALSE);

		}
		else
		{
			pDynControl->EnableWindow(TRUE);
			// see if the visible flag is enabled
			if (pDynControl->GetVisible() == FALSE)
				GetDlgItem(pDynControl->GetID())->ShowWindow(SW_HIDE);
		}
	}
	*/

	// virtual function
	// that allows base class to hide
	// any controls that should not be
	// seen
	if (!bScreenDesignMode)
		OverrideVisible();

}

template <class BASECLASS>
void CDynWnd<BASECLASS>::OnDraw(CDC* pDC)
{
	CGUIElement*	pObject = NULL;

	CGUIElementIt pos = m_GUIElements.begin();
	while (pos != m_GUIElements.end() ) {
		pObject = (CGUIElement*)( *pos );

		pObject->OnDraw(pDC);
		pos++;
	}
}



template <class BASECLASS>
void CDynWnd<BASECLASS>::OnPaint()
{
	// paints the screen

	// device context for painting
	CPaintDC pDC(this);

	// if in screen designer mode
	if (m_bInScreenDesignerMode)
	{
		if (m_bShowGrid)
		{
			// Pen for grid
			CPen dashPen(PS_DASH, 1, 1);
			CPen* oldpen;

			// calculate grid size
			CRect rect(m_nGridX,m_nGridY,0,0);
			::MapDialogRect(this->m_hWnd,&rect);
			int nGridX = rect.left;
			int nGridY = rect.top;

			// Are gridlines turned on ?
			oldpen = (CPen*)pDC.SelectObject(&dashPen);

			// Get our screen area
			RECT rectScrn;
			GetClientRect(&rectScrn);

			// We will draw as many grids as possible given the size
			// of the grid variables and the size of the client area
			ldiv_t nX = div((long)rectScrn.right, (long)m_nGridX);
			ldiv_t nY = div((long)rectScrn.bottom, (long)m_nGridY);

			for(int x = 1; x < nX.quot + 1; x++)
			{
				for(int y = 1; y < nY.quot + 1; y++)
				{
					pDC.SetPixel(x * nGridX,  y * nGridY, 0);
				}
			}

			pDC.SelectObject(oldpen);
		}
	}

	m_DynTracker.Draw(&pDC);

}


template <class BASECLASS>
CWnd* CDynWnd<BASECLASS>::GetElementClass( int nID )
{
	CGUIElement*	pObject = NULL;

	CGUIElementIt pos = m_GUIElements.begin();
	while (pos != m_GUIElements.end() ) {
		pObject = (CGUIElement*)( *pos );

		if (nID == pObject->GetID() )
			return pObject->GetWnd();

		pos++;
	}

	return NULL;
}


template <class BASECLASS>
void CDynWnd<BASECLASS>::SetParentWnd(CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;
}


template <class BASECLASS>
long CDynWnd<BASECLASS>::AddDropControl(WPARAM wParam, LPARAM lParam)
{
	int nType = wParam;
	CPoint* ppoint;
	ppoint = (CPoint*)lParam;
	CString strCtrlType;

	strCtrlType = GetCtrlType(nType);
	if (strCtrlType.IsEmpty() == TRUE){
		AfxMessageBox( _T("Control not yet implemented") );
		return 0;
	}

	AddControl( strCtrlType, *ppoint );

	return 1;
}


template <class BASECLASS>
BOOL CDynWnd<BASECLASS>::AddControl(LPCTSTR szClass, CPoint pos, BOOL bSetAsNewRoot)
{
	if (m_pParentWnd == NULL)
		return FALSE;

	// Check we don't already have a root parent
	if (bSetAsNewRoot && m_bRootParent){
		AfxMessageBox( _T("RootParent already initialized\n") );
		return FALSE;
	}

	TRACE(_T("m_pParentWnd = 0x%x\n"));

	CGUIElement* pGUIElement = NULL;
	int nRet = 0;
	CRect rectCreate = CRect(pos, CSize(100, 50));


	if (!_tcsicmp(szClass, _T("Frame")) ){
		pGUIElement = new CGUIFrame( );
	}
	else if (!_tcsicmp(szClass, _T("Static")) ){
		pGUIElement = new CGUIStatic( );
	}
	else if (!_tcsicmp(szClass, _T("Picture")) ){
		pGUIElement = new CGUIPicture( );

	}
	else if (!_tcsicmp(szClass, _T("EditBox")) ){
		pGUIElement = new CGUIEdit( );
	}
	else if (!_tcsicmp(szClass, _T("LiteHtml")) ){
		pGUIElement = new CGUILiteHtml( );
	}


	// CREATE a new CWND
	ASSERT(pGUIElement);
	nRet = pGUIElement->Create(m_pParentWnd, rectCreate);
	if (!nRet){
		return FALSE;
	}

	// Set windows ID and compute a name from it
	pGUIElement->SetID(m_nHighestID, TRUE);
	m_nHighestID++;

	if (bSetAsNewRoot){
		pGUIElement->SetNotMoveable( TRUE);
		SetParentWnd( pGUIElement->GetWnd() );
		m_bRootParent = TRUE;
	}

	m_GUIElements.push_back( pGUIElement );

	//select the new control
	m_DynTracker.RemoveAll();
	m_DynTracker.Add(pGUIElement->GetRect(), m_pParentWnd, pGUIElement->GetID(), pGUIElement); // add just one object to the multitrac
	m_curXUIObj = (CGUIElement*) pGUIElement;
	ShowProperties( m_curXUIObj );

	Invalidate();
	UpdateWindow();

	return TRUE;

}


template <class BASECLASS>
BOOL CDynWnd<BASECLASS>::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect( rect );

     CBrush backBrush(m_cBkLowColor);
     pDC->FillRect(&rect, &backBrush);

	rect.top += m_nVoffset;

	if (m_nColorMode == 0){
		pDC->FillRect(&rect, m_pBrush);
	}
	else{
		DrawGradientFill(pDC, &rect, m_nColorMode);
	}

	return TRUE;
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_curXUIObj = NULL;
	if (m_bInScreenDesignerMode)
	{
	bool bIsAWidget = false;
	if (m_DynTracker.HitTest(point) < 0  )
		{
			// Reset the multitrack only if there
			// is no CTRL key.
			if (!(nFlags & MK_CONTROL))
				m_DynTracker.RemoveAll();

			CRect rcObject;
			CGUIElement* pObject = NULL;

			// local tracker...
			CRectTracker tracker;
			if (tracker.TrackRubberBand(m_pParentWnd, point, TRUE))
			{
				// see if rubber band intersects with the objects
				CRect rectT;
				tracker.m_rect.NormalizeRect();


				//POSITION pos = m_ptrDynControls.GetHeadPosition ();
				CGUIElementIt pos = m_GUIElements.begin();
				while (pos != m_GUIElements.end() )
				{
					// from the controls create rect tracker objects
					pObject = (CGUIElement*)( *pos );
					rcObject = pObject->GetRect();
					rectT.IntersectRect(tracker.m_rect, rcObject);
					if (rectT == rcObject){
						m_DynTracker.Add(pObject->GetRect(), m_pParentWnd, pObject->GetID(), pObject); // add it to the multitrack, nd continue the loop
					}

					pos++;
				}
				bIsAWidget = true;
			}
			else
			{
				CRect rcSelected;
				CGUIElement* pObjectSelected;

				BOOL bFirst = TRUE;
				BOOL bFoundOne = FALSE;


				TRACE( _T("CXUIFramework::OnLButtonDown() {XUIVisualObjList size = %d}\n"), m_GUIElements.size() );
				//POSITION pos = m_ptrDynControls.GetHeadPosition ();
				CGUIElementIt pos = m_GUIElements.begin();
				while (pos != m_GUIElements.end())
				{
					pObject = (CGUIElement*)( *pos );
					rcObject = pObject->GetRect();

					if (rcObject.PtInRect(point))
					{
						if ((rcObject.left > rcSelected.left
							&& rcObject.left < rcSelected.right
							&& rcObject.top > rcSelected.top
							&& rcObject.top < rcSelected.bottom
							&& !bFirst)
							|| bFirst)
						{

							bFirst = FALSE;
							rcSelected = pObject->GetRect();
							pObjectSelected = pObject;
							bFoundOne = TRUE;
						}
					}
					pos++;
				}

				// Found one visual element MOVEABLE (not a frame or dialog)
				if (bFoundOne && pObjectSelected->IsMoveable() )
				{
					TRACE(_T("CXUIFramework::OnLButtonDown(){bFoundOne=TRUE}\n"));
					//m_curXUIObj = pObjectSelected;
					m_DynTracker.Add(pObjectSelected->GetRect(), m_pParentWnd, pObjectSelected->GetID(), pObjectSelected); // add just one object to the multitrac
					//ShowProperties( m_curXUIObj );

					if(1 == m_DynTracker.GetSize())
					{
						m_curXUIObj = (CGUIElement*) m_DynTracker.GetObjectSelected();
						ShowProperties( m_curXUIObj );
					}
					//bIsAWidget = true;
				}
				else
					m_curXUIObj = NULL;


				//ShowProperties(NULL);

			}
		}
	else
    {
			// Click on the multitrack, forward actions to it.
			m_DynTracker.Track(m_pParentWnd, point, FALSE);
			bIsAWidget = true;

			if(1 == m_DynTracker.GetSize())
			{
				m_curXUIObj = (CGUIElement*) m_DynTracker.GetObjectSelected();
				ShowProperties( m_curXUIObj );
			}
	}

	if (m_curXUIObj == NULL)
		ShowProperties( this );

	Invalidate();
	UpdateWindow();
}

	BASECLASS::OnLButtonDown(nFlags, point);
}


template <class BASECLASS>
void CDynWnd<BASECLASS>::OnRButtonDown(UINT nFlags, CPoint point)
{
	// set the properties for the control
	if (m_bInScreenDesignerMode && m_DynTracker.GetSize() == 1)
	{
		ShowPopup( CPoint(50,50), NULL);
		m_menu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	}
}


template <class BASECLASS>
void CDynWnd<BASECLASS>::OnSetTopWnd()
{
	if (m_bInScreenDesignerMode && m_DynTracker.GetSize() == 1)
	{
		int nID = m_DynTracker.GetIDSelected();

		CGUIElementIt pos = m_GUIElements.begin();
		CGUIElement* pWidget = NULL;
		BOOL bFound = FALSE;
		while (pos != m_GUIElements.end())
		{
			pWidget = (CGUIElement*)( *pos );
			if (pWidget->GetID() == nID)
			{
				bFound = TRUE;
				break;
			}
			pos++;
		}
		ASSERT(bFound);



		CWnd* pWnd = pWidget->GetWnd();
		pWnd->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,SWP_NOMOVE|SWP_NOSIZE);

		/*
		// get the control
		POSITION posDynControl = m_ptrDynControls.GetHeadPosition();
		CDynControl* pDynControl;
		BOOL bFound = FALSE;
		while (posDynControl)
		{
			pDynControl = (CDynControl*)m_ptrDynControls.GetNext(posDynControl);
			if (pDynControl->GetID() == nID)
			{
				bFound = TRUE;
				break;
			}
		}
		ASSERT(bFound);

		CWnd* pWnd = pDynControl->GetWnd();

		pWnd->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,
    SWP_NOMOVE|SWP_NOSIZE);
	*/
	}
}

template <class BASECLASS>
bool CDynWnd<BASECLASS>::PropertyChanging( const void* pvProperty , void* pvNewValue )
{
	//bool bChangeColor = false;

	// Background color change
	if(pvProperty == &m_nColorMode){
		m_nColorMode = *(int *)pvNewValue;
	}

	// Low color change
	if(pvProperty == &m_cBkLowColor){
		m_cBkLowColor = *(COLORREF *)pvNewValue;
	}

	// Hi color change
	if(pvProperty == &m_cBkHiColor){
		m_cBkHiColor = *(COLORREF *)pvNewValue;
	}

	if(pvProperty == &m_nVoffset){
		m_nVoffset = *(COLORREF *)pvNewValue;
	}

	SetBkColor();

	return true;
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::GetProperties(EPropList& PropList)
{
	TRACE( _T("CGuiBakerView::GetProperties()\n"));

	PropList.AddPropSeparator(this, "Widget");
	PropList.AddPropString(this, "Type",  &m_strElementType, false)->SetComment("Control Type");

	// Color filling mode
	PropList.AddPropSeparator( this , "Background" );
	PropList.AddPropCombo ( this , "Color mode"   , &m_nColorMode)
	->AddString("Normal")
	->AddString("Horizontal gradient")
	->AddString("Vertical gradient");

	// Background Low color
	PropList.AddPropColor ( this , "Low color", &m_cBkLowColor );

	// Background Hi color
	PropList.AddPropColor ( this , "High color", &m_cBkHiColor );

	PropList.AddPropInt   ( this , "Vertical Offset" , &m_nVoffset );
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::ShowProperties(IPropertyHost* pHost)
{
	ShowPropertiesBar();

	if (pHost != NULL){
		m_GUIPropertiesDlg.SetPropPointer(pHost);
		return;
	}

	if( m_curXUIObj !=NULL){
		m_GUIPropertiesDlg.SetPropPointer(m_curXUIObj);
		return;
	}
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::ShowPropertiesBar()
{

	if (m_GUIPropertiesDlg.m_hWnd == NULL)
		m_GUIPropertiesDlg.Create(IDD_SETTINGS, m_pParentWnd);

	m_GUIPropertiesDlg.ShowWindow(SW_SHOW);

	/*
	if (m_curXUIObj == NULL)
		ShowProperties( this );
	else
		ShowProperties( m_curXUIObj );
	*/

}


template <class BASECLASS>
BOOL CDynWnd<BASECLASS>::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// Called to determine what the cursor shape should be

	if (pWnd == this && m_DynTracker.SetCursor(this, nHitTest))
		return TRUE;

	return BASECLASS::OnSetCursor(pWnd, nHitTest, message);

}


template <class BASECLASS>
void CDynWnd<BASECLASS>::ShowPopup( CPoint point, CWnd* parent )
{
	if (m_menu.m_hMenu == NULL){

	if( m_menu.CreatePopupMenu() ){
		m_menu.AppendMenu( MF_STRING, CMD_CUT, _T( "Cut" ) );
		m_menu.AppendMenu( MF_STRING, CMD_COPY, _T( "Copy" ) );
		m_menu.AppendMenu( MF_STRING, CMD_DUPLICATE, _T( "Duplicate" ) );
		m_menu.AppendMenu( MF_SEPARATOR );
		m_menu.AppendMenu( MF_STRING, CMD_UP, _T( "Up" ) );
		m_menu.AppendMenu( MF_STRING, CMD_DOWN, _T( "Down" ) );
		m_menu.AppendMenu( MF_STRING, CMD_FRONT, _T( "To front" ) );
		m_menu.AppendMenu( MF_STRING, CMD_BOTTOM, _T( "To back" ) );
		m_menu.AppendMenu( MF_SEPARATOR );
		m_menu.AppendMenu( MF_STRING, CMD_PROPERTIES, _T( "Properties" ) );
	}
	}

	m_menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, parent );
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::OnInitialUpdate()
{
	BASECLASS::OnInitialUpdate();
	ToggleScreenMode(m_bInScreenDesignerMode);
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::OnInitialUpdate(LPCTSTR szFile)
{
	// Used only for CView dervied classes
	TRACE("CDynWnd<BASECLASS>::OnInitialUpdate()\n");

	m_ResFileName = szFile;


	LoadScreen( szFile );


	BASECLASS::OnInitialUpdate();
	ToggleScreenMode(m_bInScreenDesignerMode);

}

template <class BASECLASS>
BOOL CDynWnd<BASECLASS>::OnInitDialog()
{


	BASECLASS::OnInitDialog();
	ToggleScreenMode(m_bInScreenDesignerMode);
	return TRUE;
}


// command handlers for buttons
// empty command handler to always have button enabled

template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonFrame() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonedit() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonmledit() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonlabel() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonLiteHtml() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtoncombo() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtongroup() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtoncheck() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtondate() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonradio() {}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonpicture() {}
// end of command handlers for buttons

template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonLeftAlign()
{
	// align the controls

	m_DynTracker.AdjustLayout(1);
	Invalidate();
}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonRightAlign()
{
	// align the controls

	m_DynTracker.AdjustLayout(2);
	Invalidate();
}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonTopAlign()
{
	// align the controls

	m_DynTracker.AdjustLayout(3);
	Invalidate();
}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonBottomAlign()
{
	// align the controls

	m_DynTracker.AdjustLayout(4);
	Invalidate();
}
template <class BASECLASS> void CDynWnd<BASECLASS>::OnButtonMakeSameWidth()
{
	// make same width

	m_DynTracker.AdjustLayout(5);
	Invalidate();
}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonMakeSameHeight()
{
	// make same height

	m_DynTracker.AdjustLayout(6);
	Invalidate();
}
template <class BASECLASS>
void CDynWnd<BASECLASS>::OnButtonMakeSameSize()
{
	// make same size

	m_DynTracker.AdjustLayout(7);
	Invalidate();
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CGUIElement* pObject = NULL;

	// In designer mode
	if (m_bInScreenDesignerMode )
	{
		if (nChar == VK_DELETE && m_DynTracker.GetSize() == 1)
		{
			// Get Control ID
			int nID = m_DynTracker.GetIDSelected();
			CGUIElementIt pos = m_GUIElements.begin();

			// Parse list and remove element
			while (pos != m_GUIElements.end() ) {
				pObject = (CGUIElement*)( *pos );

				if (nID == pObject->GetID())
				{
					pObject->GetWnd()->ShowWindow(SW_HIDE);
					//m_GUIPropertiesDlg..DestroyWindow();
					m_GUIPropertiesDlg.SetPropPointer(this);

					m_GUIElements.erase( pos);
					delete pObject;
					pObject = NULL;

					m_DynTracker.RemoveAll();

					Invalidate();
					UpdateWindow();

					break;
				}
				else
					pos++;
			}



		}
	}
	else
	{
		if (nChar == 'F')
		{
			OnFullScreenMode ();
		}
	}


	BASECLASS::OnKeyDown(nChar, nRepCnt, nFlags);
}


template <class BASECLASS>
void CDynWnd<BASECLASS>::SetBkColor( )
{
	if (m_pBrush){
		delete m_pBrush;
		m_pBrush = new CBrush(m_cBkLowColor);
	}
	else
		m_pBrush = new CBrush(m_cBkLowColor);

	Invalidate();

}



/* Has nothing to do here, I should create a graphics class */
template <class BASECLASS>
void CDynWnd<BASECLASS>::DrawGradientFill(CDC* pDCMem, CRect* pRect, int FillMode)
{
	TRIVERTEX rcVertex[2];
	rcVertex[0].x=pRect->left;
	rcVertex[0].y=pRect->top;
	rcVertex[0].Red=GetRValue(m_cBkLowColor)<<8;
	rcVertex[0].Green=GetGValue(m_cBkLowColor)<<8;
	rcVertex[0].Blue=GetBValue(m_cBkLowColor)<<8;
	rcVertex[0].Alpha=0x0000;
	rcVertex[1].x=pRect->right;
	rcVertex[1].y=pRect->bottom;
	rcVertex[1].Red=GetRValue(m_cBkHiColor)<<8;
	rcVertex[1].Green=GetGValue(m_cBkHiColor)<<8;
	rcVertex[1].Blue=GetBValue(m_cBkHiColor)<<8;
	rcVertex[1].Alpha=0;

	GRADIENT_RECT grect;
	grect.UpperLeft=0;
	grect.LowerRight=1;

	dllfunc_GradientFill( *pDCMem ,rcVertex,2,&grect,1,
		FillMode == HGradient ? GRADIENT_FILL_RECT_H :  GRADIENT_FILL_RECT_V);
}



template <class BASECLASS>
void CDynWnd<BASECLASS>::LoadScreen(LPCTSTR szFile)
{
	TiXmlDocument	doc;
	TiXmlElement*	pXMLElement = NULL;
	TiXmlText*		pXMLText	= NULL;
	CString			strTmp;

	// Load Xml
	bool bRet = doc.LoadFile( CMisc::GetAppPath() + szFile  );
	if (!bRet)
		return;

	// Destroy our current GUI
	m_GUIElements.clear();


	// Go directly to  <object> section
	TiXmlHandle docHandle( &doc );
	TiXmlHandle resHandle = docHandle.FirstChild( _T("resource") ).FirstChild( _T("object") );

	pXMLElement = resHandle.Element();
	TRACE( _T("<%s class=%s>\n"), pXMLElement->Value(), pXMLElement->Attribute("class") );


	TiXmlElement* pXMLView = pXMLElement->FirstChild()->ToElement();
	if ( _tcsicmp( pXMLView->Value(), _T("background") ) == 0 ){
		m_nColorMode  = _tcstol ( pXMLView->Attribute( _T("FillMode") ), NULL, 10 );
		m_cBkLowColor = _tcstol ( pXMLView->Attribute( _T("LowColor") ), NULL, 16 );
		m_cBkHiColor  = _tcstol ( pXMLView->Attribute( _T("HiColor") ),  NULL, 16 );
		m_nVoffset	  = _tcstol ( pXMLView->Attribute( _T("VOffset") ),  NULL, 10 );
		SetBkColor();
	}


	pXMLElement = pXMLElement->FirstChild( "object" )->ToElement();
	while( pXMLElement ){

		TRACE( _T("<%s class=%s name=%s>\n"), pXMLElement->Value(),
			pXMLElement->Attribute("class"),
			pXMLElement->Attribute("name"));


		CGUIElement* NewWidget = NULL;

		if (!_tcsicmp(pXMLElement->Attribute( _T("class") ), _T("Frame")) ){
			NewWidget = new CGUIFrame( );
		}
		else if (!_tcsicmp(pXMLElement->Attribute( _T("class") ), _T("Static")) ){
			NewWidget = new CGUIStatic( );
		}
		else if (!_tcsicmp(pXMLElement->Attribute( _T("class") ), _T("Picture")) ){
			NewWidget = new CGUIPicture( );
		}
		else if (!_tcsicmp(pXMLElement->Attribute( _T("class") ), _T("LiteHtml")) ){
			NewWidget = new CGUILiteHtml( );
		}

		// Go deeper
		//pXMLElement = pXMLElement->FirstChild()->ToElement();
		if(NewWidget !=NULL)
		{
			NewWidget->Create(m_pParentWnd);
			NewWidget->LoadXML(pXMLElement);

			m_GUIElements.push_back( NewWidget );

			// Since ID is parsed by each control need to know highest ID
			// We suppose
			if (m_nHighestID <= (ULONG)NewWidget->GetHighestID() )
			{
				m_nHighestID = (ULONG)NewWidget->GetHighestID();
				m_nHighestID++;
			}
		}

		// move to the next control
		pXMLElement = pXMLElement->NextSiblingElement("object");
	}
}

template <class BASECLASS>
void CDynWnd<BASECLASS>::SaveScreen()
{
	CString			csTmp;
	TiXmlDocument	doc;
	CGUIElement*	pObject = NULL;
	TiXmlElement*	pNode	= NULL;
	TiXmlElement*	pNode2  = NULL;
	TiXmlElement*	pNode3  = NULL;

	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

	pNode = new TiXmlElement( "resource" );
	pNode->SetAttribute( "version", "0.1" );
	doc.LinkEndChild( pNode );

	pNode2 = new TiXmlElement( "object" );
	pNode2->SetAttribute( _T("class"), _T("CView") );
	pNode2->SetAttribute( "name", _T("Default") );
	pNode->LinkEndChild( pNode2 );

	pNode = new TiXmlElement( "background" );
	csTmp.Format( _T("%d"), m_nColorMode );
	pNode->SetAttribute( "FillMode",  csTmp);

	csTmp.Format( _T("0x%6.6x"), m_cBkLowColor );
	pNode->SetAttribute( "LowColor",  csTmp);
	csTmp.Format( _T("0x%6.6x"), m_cBkHiColor );
	pNode->SetAttribute( "HiColor",  csTmp);
	csTmp.Format( _T("%d"),  m_nVoffset);
	pNode->SetAttribute( "VOffset",  csTmp);
	pNode2->LinkEndChild( pNode );


	CGUIElementIt pos = m_GUIElements.begin();
	while (pos != m_GUIElements.end() ) {
		pObject = (CGUIElement*)( *pos );

		pObject->SaveXML( pNode2 );
		pos++;
	}

	doc.SaveFile( CMisc::GetAppPath() + m_ResFileName );
}



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.



#endif


