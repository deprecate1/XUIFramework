

#include "stdafx.h"
#include "GUITracker.h"
#include "GUIElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUITracker::CGUITracker()
{
   m_nHandleSize = 5;
}

CGUITracker::~CGUITracker()
{

}

void CGUITracker::Add(CRect rect, CWnd* pParentWnd, int nID, void* pObject)
{
	// add a new rectangle

	CGUITrackerObject* pobjTracker = new CGUITrackerObject;
	pobjTracker->m_nID = nID;
	pobjTracker->m_pParentWnd = pParentWnd;
	pobjTracker->m_rect = rect;
	pobjTracker->m_pObject = pObject;

	if (m_pDynTrackerObjects.GetSize() == 0)
	{
		m_nStyle = hatchedBorder | resizeOutside | dottedLine;
		pobjTracker->m_bFirst = TRUE;
	}
	else
	{
		m_nStyle = hatchedBorder | resizeOutside;
		pobjTracker->m_bFirst = FALSE;
	}
	pobjTracker->m_nStyle = m_nStyle;

	m_pDynTrackerObjects.Add(pobjTracker);
	m_pDynTrackerObject = pobjTracker;


}

void CGUITracker::Draw(CDC* pDC)
{	
    for (int nIndex = 0; nIndex < m_pDynTrackerObjects.GetSize(); nIndex++) 
	{
        m_rect.CopyRect(m_pDynTrackerObjects.GetAt(nIndex)->m_rect);
		m_nStyle = m_pDynTrackerObjects.GetAt(nIndex)->m_nStyle;
		CRectTracker::Draw(pDC);
    }
	
}

BOOL CGUITracker::Track(CWnd* pWnd, CPoint point, BOOL bAllowInvert, CWnd* pWndClipTo)
{
	// If the array is empty, do nothing...
    if (m_pDynTrackerObjects.GetSize() == 0)
        return FALSE;

	// save away parent
	m_pWndParent = pWnd;

    // perform hit testing on the handles
	int nHandle = HitTestHandles(point);
	// didn't hit a handle, so just return FALSE
	if (nHandle == hitNothing)
		return FALSE;

    // The selected objects will be moved on the screen
	if (nHandle == hitMiddle) 
        return MultiTrackHandle(pWnd, point, pWndClipTo);
	else 
	{
        // Update the only one object selected,
        // and call CRectTracker::TrackHandle
        m_pDynTrackerObjects.RemoveAll();
        m_pDynTrackerObjects.Add(m_pDynTrackerObject);
        m_rect.CopyRect(m_pDynTrackerObject->m_rect);
        // otherwise, call helper function to do the tracking
	    m_bAllowInvert = bAllowInvert;
	    BOOL bRet = TrackHandle(nHandle, pWnd, point, pWndClipTo);
 
		if (bRet)
            m_pDynTrackerObject->m_rect.CopyRect(m_rect);
  	   
		// now move the actual controls on the screen!
		for (int index2 = 0; index2 < m_pDynTrackerObjects.GetSize(); index2++)
		{
			CWnd* pWnd = m_pDynTrackerObjects.GetAt(index2)->m_pParentWnd;
			int nID = m_pDynTrackerObjects.GetAt(index2)->m_nID;
			CRect rect = m_pDynTrackerObjects.GetAt(index2)->m_rect;

			pWnd->GetDlgItem(nID)->MoveWindow(rect);
		}

		// now tell the dynobjects that they have moved
		for (int index3 = 0; index3 < m_pDynTrackerObjects.GetSize(); index3++)
		{
			CGUIElement* pObject = (CGUIElement*)m_pDynTrackerObjects.GetAt(index3)->m_pObject;
			CRect rect = m_pDynTrackerObjects.GetAt(index3)->m_rect;
			pObject->CopyRect(rect);
		}
		return bRet;
    }
}

BOOL CGUITracker::MultiTrackHandle (CWnd* pWnd, CPoint point, CWnd* pWndClipTo)
{
	// don't handle if capture already set
	if (::GetCapture() != NULL)
		return FALSE;

	AfxLockTempMaps();  // protect maps while looping

	ASSERT(!m_bFinalErase);

	// set capture to the window which received this message
	pWnd->SetCapture();
	ASSERT(pWnd == CWnd::GetCapture());
	pWnd->UpdateWindow();
	if (pWndClipTo != NULL)
		pWndClipTo->UpdateWindow();

    CPoint oldPoint = point;

    // We work on the rects copies, not the objects
    CopyPositions();

	// get DC for drawing
	CDC* pDrawDC;
	if (pWndClipTo != NULL)
	{
		// clip to arbitrary window by using adjusted Window DC
		pDrawDC = pWndClipTo->GetDCEx(NULL, DCX_CACHE);
	}
	else
	{
		// otherwise, just use normal DC
		pDrawDC = pWnd->GetDC();
	}
	ASSERT_VALID(pDrawDC);

	CRect rectOld;
	BOOL bMoved = FALSE;

    int index;
    CRect* pRect;

	// get messages until capture lost or cancelled/accepted
	for (;;)
	{
		MSG msg;
		VERIFY(::GetMessage(&msg, NULL, 0, 0));

		if (CWnd::GetCapture() != pWnd)
			break;

		switch (msg.message)
		{
		// handle movement/accept messages
		case WM_LBUTTONUP:
		case WM_MOUSEMOVE:
            
			// only redraw and callback if the rect actually changed!
			m_bFinalErase = (msg.message == WM_LBUTTONUP);

            for (index = 0; index < m_CopyPosition.GetSize(); index++) {
                pRect = m_CopyPosition.GetAt(index);
                m_rect.CopyRect(pRect);

			    rectOld = m_rect;

				m_rect.left += (int)(short)LOWORD(msg.lParam) - oldPoint.x;
                m_rect.top += (int)(short)HIWORD(msg.lParam) - oldPoint.y;

                m_rect.right = m_rect.left + rectOld.Width();
				m_rect.bottom = m_rect.top + rectOld.Height();

			    if (!rectOld.EqualRect(&m_rect) || m_bFinalErase)
			    {
				    if (bMoved)
				    {
					    m_bErase = TRUE;
					    DrawTrackerRect(&rectOld, pWndClipTo, pDrawDC, pWnd);
				    }
				    if (!m_bFinalErase)
					    bMoved = TRUE;
			    }
			    if (!rectOld.EqualRect(&m_rect) && !m_bFinalErase)
			    {
				    m_bErase = FALSE;
				    DrawTrackerRect(&m_rect, pWndClipTo, pDrawDC, pWnd);
			    }

                pRect->CopyRect(m_rect);

            }
            oldPoint = msg.lParam;
		    if (m_bFinalErase)
			    goto ExitLoop;

			break;

		// handle cancel messages
		case WM_KEYDOWN:
			if (msg.wParam != VK_ESCAPE)
				break;
		case WM_RBUTTONDOWN:
			if (bMoved)
			{
                for (int index = 0; index < m_CopyPosition.GetSize(); index++) {
                    m_rect.CopyRect(m_CopyPosition.GetAt(index));
				    m_bErase = m_bFinalErase = TRUE;
				    DrawTrackerRect(&m_rect, pWndClipTo, pDrawDC, pWnd);
                }
			}
            //RestoreRectangles ( m_pDynTrackerObjects );
			goto ExitLoop;

		// just dispatch rest of the messages
		default:
			DispatchMessage(&msg);
			break;
		}
	}

ExitLoop:
	if (pWndClipTo != NULL)
		pWndClipTo->ReleaseDC(pDrawDC);
	else
		pWnd->ReleaseDC(pDrawDC);
	ReleaseCapture();

	AfxUnlockTempMaps(FALSE);

	// update object's rect pos in case bMoved is TRUE
	if (bMoved)
		UpdateObjects ();

	m_bFinalErase = FALSE;
	m_bErase = FALSE;

	// return TRUE only if rect has changed
	return bMoved;
}

void CGUITracker::CopyPositions ()
{
    ClearPositions ();

    for (int index = 0; index < m_pDynTrackerObjects.GetSize(); index++)
        m_CopyPosition.Add (new CRect(m_pDynTrackerObjects.GetAt(index)->m_rect));
}

void CGUITracker::UpdateObjects()
{
    ASSERT (m_pDynTrackerObjects.GetSize() == m_CopyPosition.GetSize());
    for (int index = 0; index < m_pDynTrackerObjects.GetSize(); index++)
        m_pDynTrackerObjects.GetAt(index)->m_rect.CopyRect(m_CopyPosition.GetAt(index));

	// now move the actual controls on the screen!
	for (int index2 = 0; index2 < m_pDynTrackerObjects.GetSize(); index2++)
	{
		CWnd* pWnd = m_pDynTrackerObjects.GetAt(index2)->m_pParentWnd;
		int nID = m_pDynTrackerObjects.GetAt(index2)->m_nID;
		CRect rect = m_pDynTrackerObjects.GetAt(index2)->m_rect;

		pWnd->GetDlgItem(nID)->MoveWindow(rect);
	}

	// now tell the dynobjects that they have moved
	for (int index3 = 0; index3 < m_pDynTrackerObjects.GetSize(); index3++)
	{
		CGUIElement* pObject = (CGUIElement*)m_pDynTrackerObjects.GetAt(index3)->m_pObject;
		CRect rect = m_pDynTrackerObjects.GetAt(index3)->m_rect;
		pObject->CopyRect(rect);
	}

    ClearPositions();
}

void CGUITracker::ClearPositions ()
{
    for (int index = 0; index < m_CopyPosition.GetSize(); index++)
        delete m_CopyPosition.GetAt(index);
    m_CopyPosition.RemoveAll();
}

void CGUITracker::RemoveAll ()
{
    for (int index = 0; index < m_pDynTrackerObjects.GetSize(); index++)
        delete m_pDynTrackerObjects.GetAt(index);
    m_pDynTrackerObjects.RemoveAll();
    m_rect.SetRectEmpty();
}

int CGUITracker::HitTestHandles(CPoint point) 
{
    int iHit = hitNothing;
    for (int index = 0; index < m_pDynTrackerObjects.GetSize(); index++) {
        m_rect.CopyRect(m_pDynTrackerObjects.GetAt(index)->m_rect);
        iHit = CRectTracker::HitTestHandles(point);
        if (iHit != hitNothing) {
            m_pDynTrackerObject = m_pDynTrackerObjects.GetAt(index);
            return iHit;
        }
    }
    return hitNothing;
}


//////////////////////////////////////////////////////////////////////
//
//
int CGUITracker::HitTest(CPoint point)
{
    int iHit = hitNothing;
    for (int index = 0; index < m_pDynTrackerObjects.GetSize(); index++) {
        m_rect.CopyRect(m_pDynTrackerObjects.GetAt(index)->m_rect);
        iHit = CRectTracker::HitTest(point);
        if (iHit != hitNothing) {
            m_pDynTrackerObject = m_pDynTrackerObjects.GetAt(index);
            return iHit;
        }
    }
    return hitNothing;
}


//////////////////////////////////////////////////////////////////////
// Ask each objects to get a cursor change or not
//
BOOL CGUITracker::SetCursor(CWnd *pWnd, UINT nHitTest)
{
    CRect rectSave = m_rect;
    for (int index = 0; index < m_pDynTrackerObjects.GetSize(); index++) 
	{
        m_rect.CopyRect(m_pDynTrackerObjects.GetAt(index)->m_rect);
        if (CRectTracker::SetCursor(pWnd, nHitTest)) {
            m_rect = rectSave;
            return TRUE;
        }
    }
    m_rect = rectSave;
    return FALSE;
}

void CGUITracker::AdjustLayout(int nOperation)
{
	// adjust size and position

	BOOL bFound = FALSE;
	CRect rect;
    for (int index = 0; index < m_pDynTrackerObjects.GetSize(); index++) 
	{
		if (m_pDynTrackerObjects.GetAt(index)->m_bFirst)
		{
			rect.CopyRect(m_pDynTrackerObjects.GetAt(index)->m_rect);
			bFound = TRUE;
		}
    }

	if (!bFound)
		return;

    for (int index = 0; index < m_pDynTrackerObjects.GetSize(); index++) 
	{
		if (nOperation == 1) // left
		{
			int nAdjust =  (m_pDynTrackerObjects.GetAt(index)->m_rect.left - rect.left);
			m_pDynTrackerObjects.GetAt(index)->m_rect.left = m_pDynTrackerObjects.GetAt(index)->m_rect.left - nAdjust;
			m_pDynTrackerObjects.GetAt(index)->m_rect.right = m_pDynTrackerObjects.GetAt(index)->m_rect.right - nAdjust;
		}
		if (nOperation == 2) // right
		{
			int nAdjust =  (m_pDynTrackerObjects.GetAt(index)->m_rect.right - rect.right);
			m_pDynTrackerObjects.GetAt(index)->m_rect.right = m_pDynTrackerObjects.GetAt(index)->m_rect.right - nAdjust;
			m_pDynTrackerObjects.GetAt(index)->m_rect.left = m_pDynTrackerObjects.GetAt(index)->m_rect.left - nAdjust;
		}
		if (nOperation == 3) // top
		{
			int nAdjust =  (m_pDynTrackerObjects.GetAt(index)->m_rect.top - rect.top);
			m_pDynTrackerObjects.GetAt(index)->m_rect.top = m_pDynTrackerObjects.GetAt(index)->m_rect.top - nAdjust;
			m_pDynTrackerObjects.GetAt(index)->m_rect.bottom = m_pDynTrackerObjects.GetAt(index)->m_rect.bottom - nAdjust;
		}
		if (nOperation == 4) // bottom
		{
			int nAdjust =  (m_pDynTrackerObjects.GetAt(index)->m_rect.bottom - rect.bottom);
			m_pDynTrackerObjects.GetAt(index)->m_rect.bottom = m_pDynTrackerObjects.GetAt(index)->m_rect.bottom - nAdjust;
			m_pDynTrackerObjects.GetAt(index)->m_rect.top = m_pDynTrackerObjects.GetAt(index)->m_rect.top - nAdjust;
		}
		if (nOperation == 5 || nOperation == 7) // width or same size
		{
			int nAdjust =  (m_pDynTrackerObjects.GetAt(index)->m_rect.Width() - rect.Width());
			m_pDynTrackerObjects.GetAt(index)->m_rect.right = m_pDynTrackerObjects.GetAt(index)->m_rect.right - nAdjust;
		}
		if (nOperation == 6 || nOperation == 7) // height or same size
		{
			int nAdjust =  (m_pDynTrackerObjects.GetAt(index)->m_rect.Height() - rect.Height());
			m_pDynTrackerObjects.GetAt(index)->m_rect.bottom = m_pDynTrackerObjects.GetAt(index)->m_rect.bottom - nAdjust;
		}
    }

	// now move the actual controls on the screen!
	for (int index2 = 0; index2 < m_pDynTrackerObjects.GetSize(); index2++)
	{
		CWnd* pWnd = m_pDynTrackerObjects.GetAt(index2)->m_pParentWnd;
		int nID = m_pDynTrackerObjects.GetAt(index2)->m_nID;
		CRect rect = m_pDynTrackerObjects.GetAt(index2)->m_rect;

		pWnd->GetDlgItem(nID)->MoveWindow(rect);
	}

	// now tell the dynobjects that they have moved
	for (int index3 = 0; index3 < m_pDynTrackerObjects.GetSize(); index3++)
	{
		CGUIElement* pObject = (CGUIElement*)m_pDynTrackerObjects.GetAt(index3)->m_pObject;
		CRect rect = m_pDynTrackerObjects.GetAt(index3)->m_rect;
		pObject->CopyRect(rect);
	}
}

int CGUITracker::GetIDSelected()
{
	// get id of selected control

	return m_pDynTrackerObjects.GetAt(0)->m_nID;

}

void* CGUITracker::GetObjectSelected()
{
	// get pObject of selected control

	return m_pDynTrackerObjects.GetAt(0)->m_pObject;
}

