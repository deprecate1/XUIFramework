
#include "stdafx.h"
#include "GUIControlBar.h"
#include <afxadv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynControlBar

CDynControlBar::CDynControlBar()
{
	// default constructor

	// initialise the clipboard format for drag and drop
	m_nIDClipFormat = RegisterClipboardFormat("ScreenDesigner");
	m_bMakingVisible = FALSE;
}

CDynControlBar::~CDynControlBar()
{
}

BEGIN_MESSAGE_MAP(CDynControlBar, CToolBar)
	//{{AFX_MSG_MAP(CDynControlBar)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TBN_BEGINDRAG,BeginDrag)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynControlBar message handlers


void CDynControlBar::BeginDrag(NMHDR* pNotifyStruct, LRESULT* result)
{
	// called when the user attempts to drag a button

	if (pNotifyStruct->code == TBN_BEGINDRAG)
	{
		COleDataSource srcItem;
		CString sType = _T("");
		HGLOBAL hTextData = 0;	
		TBNOTIFY* sat = (TBNOTIFY*)pNotifyStruct;

		CSharedFile clipb (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);

		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUIFRAME)
		{
			dynDropSource.nCursorType = dynDropSource.EDIT;
			CString strText;
			strText.Format("%d",ID_XUIFRAME);
			sType = strText;
		}
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUIPICTURE)
		{
			dynDropSource.nCursorType = dynDropSource.EDIT;
			CString strText;
			strText.Format("%d",ID_XUIPICTURE);
			sType = strText;
		}
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUILABEL)
		{
			dynDropSource.nCursorType = dynDropSource.LABEL;
			CString strText;
			strText.Format("%d",ID_XUILABEL);
			sType = strText;
		}
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUILITEHTML)
		{
			dynDropSource.nCursorType = dynDropSource.LABEL;
			CString strText;
			strText.Format("%d",ID_XUILITEHTML);
			sType = strText;
		}

		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUIEDIT)
		{
			dynDropSource.nCursorType = dynDropSource.EDIT;
			CString strText;
			strText.Format("%d",ID_XUIEDIT);
			sType = strText;
		}
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUIEDITMULTI)
		{
			dynDropSource.nCursorType = dynDropSource.EDIT;
			CString strText;
			strText.Format("%d",ID_XUIEDITMULTI);
			sType = strText;
		}
		
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUICOMBO)
		{
			dynDropSource.nCursorType = dynDropSource.COMBO;
			CString strText;
			strText.Format("%d",ID_XUICOMBO);
			sType = strText;
		}
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUIGROUP)
		{
			dynDropSource.nCursorType = dynDropSource.GROUP;
			CString strText;
			strText.Format("%d",ID_XUIGROUP);
			sType = strText;
		}
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUICHECK)
		{
			dynDropSource.nCursorType = dynDropSource.CHECK;
			CString strText;
			strText.Format("%d",ID_XUICHECK);
			sType = strText;
		}
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUIDATE)
		{
			dynDropSource.nCursorType = dynDropSource.DATE;
			CString strText;
			strText.Format("%d",ID_XUIDATE);
			sType = strText;
		}
		if (((TBNOTIFY*)pNotifyStruct)->iItem == ID_XUIRADIO)
		{
			dynDropSource.nCursorType = dynDropSource.RADIO;
			CString strText;
			strText.Format("%d",ID_XUIRADIO);
			sType = strText;
		}
		
		if (sType.IsEmpty())
		{
			// no control selected?
			return;
		}

		GetToolBarCtrl().SetState(((TBNOTIFY*)pNotifyStruct)->iItem,TBSTATE_PRESSED);

		clipb.Write(sType, sType.GetLength()*sizeof(TCHAR));
		hTextData = clipb.Detach();

		srcItem.CacheGlobalData(m_nIDClipFormat, hTextData);
		srcItem.DoDragDrop(DROPEFFECT_COPY,NULL,&dynDropSource);

		GetToolBarCtrl().SetState(((TBNOTIFY*)pNotifyStruct)->iItem,TBSTATE_ENABLED);
	}
}

int CDynControlBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	// called to create the toolbar

	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CDynControlBar::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	// controls closing the screen

	CToolBar::OnWindowPosChanged(lpwndpos);
}

