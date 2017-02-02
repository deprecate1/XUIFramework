
#include "stdafx.h"
#include "GUIDroptarget.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynDropTarget

IMPLEMENT_DYNCREATE(CDynDropTarget, CCmdTarget)

CDynDropTarget::CDynDropTarget()
{
}

CDynDropTarget::~CDynDropTarget()
{
}


BEGIN_MESSAGE_MAP(CDynDropTarget, COleDropTarget)
	//{{AFX_MSG_MAP(CDynDropTarget)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynDropTarget message handlers

BOOL CDynDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect,CPoint point)
{
	// Detects a drop and adds a new control to the screen
	
	if (!(pDataObject->IsDataAvailable(m_nIDClipFormat)))
		return FALSE; 
	
	STGMEDIUM stgmedium;
	int nType;

	{
		if (pDataObject->GetData(m_nIDClipFormat, &stgmedium))
		{
			HGLOBAL hGlobal = stgmedium.hGlobal;
			LPCTSTR pText = (LPCTSTR)GlobalLock(hGlobal);
			nType = atoi(pText);
			// free memory
			GlobalUnlock(hGlobal);
			GlobalFree(hGlobal);
		}

		pWnd->SendMessage(WM_DROPCONTROL,(WPARAM)nType,(LPARAM)&point);
	}

	return FALSE;
}

DROPEFFECT CDynDropTarget::OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
{
	// Determines if data is available to drop

	if (pDataObject->IsDataAvailable(m_nIDClipFormat))
			return DROPEFFECT_COPY;

	return DROPEFFECT_NONE; 
}

DROPEFFECT CDynDropTarget::OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point )
{
	// Determines if data is available to drop

	CString strPos;
	strPos.Format(" x: %d, y: %d ",point.x,point.y);

	if (pDataObject->IsDataAvailable(m_nIDClipFormat))
		return DROPEFFECT_COPY;

	return DROPEFFECT_NONE; 
}
