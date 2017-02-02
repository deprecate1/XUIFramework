#include "stdafx.h"
#include "CxPicture.h"
#include <process.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CxPicture, CStatic)
	//{{AFX_MSG_MAP(CxPicture)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_WM_SIZE()
	ON_WM_DROPFILES()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_RBUTTONDOWN()
	//ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CxPicture::CxPicture()
{
	hinst_msimg32		= NULL;
	m_bAutoWrapping		= TRUE;
	m_bAutoAdjustFont	= TRUE;
	m_pPicture			= new CxImage();
	m_nFrameCount		= 0;
	m_hThread			= NULL;
	m_hExitEvent		= CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hBitmap			= NULL;
	m_hMemDC			= NULL;

	m_hDispMemDC		= NULL;
	m_hDispMemBM		= NULL;
	m_hDispOldBM		= NULL;

	m_bTransparentBk	= FALSE;
	m_bNotifyParent		= FALSE;
	m_bIsInitialized	= FALSE;
	m_bExitThread		= FALSE;
	m_bIsPlaying		= FALSE;
	m_bIsGIF			= FALSE;
	m_clrBackground		= RGB(255,255,255); // white by default
	m_nGlobalCTSize		= 0;
	m_nCurrOffset		= 0;
	m_nCurrFrame		= 0;
	m_nDataSize			= 0;
	m_PictureSize.cx	= 0;
	m_PictureSize.cy	= 0;
	SetRect(&m_PaintRect,0,0,0,0);

	m_bHover			= FALSE;
	m_bTracking			= FALSE;
	m_bAllowMove		= FALSE;
	m_pTrack			= NULL;

	m_fillmode		  = Normal;
	m_rgbBkgnd		  = ::GetSysColor(COLOR_BTNFACE);
	m_rgbText		  = ::GetSysColor(COLOR_WINDOWTEXT);
	m_crHiColor		  =	m_rgbBkgnd;
	m_crLoColor		  =	m_rgbBkgnd;
	m_pBrush          = new CBrush(m_rgbBkgnd);

	

	// LIBRARY TO DRAW COLOR GRADIENTS
	hinst_msimg32 = LoadLibrary( "msimg32.dll" );
	if( hinst_msimg32 ){
		dllfunc_GradientFill = ((LPFNDLLFUNC) GetProcAddress( hinst_msimg32, "GradientFill" ));
	}
}

CxPicture::~CxPicture()
{
	UnLoad();
	CloseHandle(m_hExitEvent);
	

	// Clean up our Brush
	if (m_pBrush){
		delete m_pBrush;
		m_pBrush = NULL;
	}

	// Clean our main Picture
	if (m_pPicture){
		delete m_pPicture;
		m_pPicture = NULL;
	}

	if ( hinst_msimg32 ){
		::FreeLibrary( hinst_msimg32 );
		hinst_msimg32 = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//// PreSubclassWindow
void CxPicture::PreSubclassWindow()
{
	CFont* pFont = GetFont();
	if (!pFont){
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		if (hFont == NULL)
			hFont = (HFONT) GetStockObject(ANSI_VAR_FONT);
		if (hFont)
			pFont = CFont::FromHandle(hFont);
	}
	ASSERT(pFont);
	ASSERT(pFont->GetSafeHandle());

	// create the font for this control
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	pFont->GetLogFont(&m_DefLogFont);
	
	m_font.CreateFontIndirect(&lf);

	this->GetWindowText(m_strText);
	DragAcceptFiles(TRUE);
	Invalidate();
}

//============================================================================
// If you are interested to implement this function - do not hesitate
// In this case drop me an email at richom.v@free.fr
// See http://www.codeproject.com/staticctrl/CxStatic.asp
//============================================================================
void CxPicture::SetWindowText(LPCTSTR strText) 
{
	m_strText = strText;
	RenderText();
}

void CxPicture::AppendText(LPCTSTR szFmt, ...) {}
void CxPicture::Format(LPCTSTR szFmt, ...){}
void CxPicture::SetFont(const CString& strFont, int nPointSize,int nWeight){}
void CxPicture::SetFont(LOGFONT *pLogFont, BOOL bRedraw){}
void CxPicture::SetFont(CFont *pFont, BOOL bRedraw){}
void CxPicture::SetTextColor(COLORREF col){}
LRESULT CxPicture::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	LRESULT lrReturn(Default());
	return lrReturn;
}
LRESULT CxPicture::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT lrReturn(Default());
	this->GetWindowText(m_strText);
	return lrReturn;
}





void CxPicture::SetMoveable(BOOL moveAble)
{
	ModifyStyle(0, SS_NOTIFY);
	m_bAllowMove = moveAble;
}

void CxPicture::SetTransparent(BOOL bTranspMode)
{
	m_bTransparentBk = bTranspMode;
	ModifyStyleEx(0,WS_EX_TRANSPARENT);
	RedrawWindow();
}

int CxPicture::HasImage(CString& strImgType, int& nImgWidth, int& nImgHeight, COLORREF& rgbTransp)
{
	m_pImage = NULL;
	int nImages = m_arrFrames.size();
	if ( nImages == 0)
		return 0;

	vector<TFrame>::iterator it = m_arrFrames.begin();
	m_pImage = (CxImage*) (*it).m_pPicture;
	if (m_pImage == NULL)
		return 0;


	strImgType = FindImgType ( m_pImage->GetType() );
	nImgWidth  = m_pImage->GetWidth();
	nImgHeight = m_pImage->GetHeight();

	rgbTransp = m_pImage->RGBQUADtoRGB( m_pImage->GetTransColor() );
	
	return TRUE;

}

void CxPicture::UnLoad()
{

	Stop();
	if (m_pPicture){
		m_pPicture->Destroy();
		//m_pPicture = NULL;
	};
	
	std::vector<TFrame>::iterator it;
	for (it=m_arrFrames.begin();it<m_arrFrames.end();it++){
		(*it).m_pPicture->Destroy();
		if ( (*it).m_pPicture ){
			delete (*it).m_pPicture;
		}
	}
	
	m_arrFrames.clear();

	if (m_hMemDC){
		SelectObject(m_hMemDC,m_hOldBitmap);
		::DeleteDC(m_hMemDC); ::DeleteObject(m_hBitmap);
		m_hMemDC  = NULL;
		m_hBitmap = NULL;
	};

	if (m_hDispMemDC){
		SelectObject(m_hDispMemDC,m_hDispOldBM);
		::DeleteDC(m_hDispMemDC); ::DeleteObject(m_hDispMemBM);
		m_hDispMemDC  = NULL;
		m_hDispMemBM = NULL;
	};

	//SetRect(&m_PaintRect,0,0,0,0);
	m_hThread		   = NULL;
	m_bIsInitialized   = FALSE;
	m_bExitThread	   = FALSE;
	m_bIsGIF		   = FALSE;
	m_clrBackground    = RGB(255,255,255); // white by default
	m_nCurrOffset	   = 0;
	m_nCurrFrame	   = 0;
	m_nDataSize		   = 0;
	m_nSizeMode		   = FitControl;
}

BOOL CxPicture::PrepareDC(int nWidth, int nHeight)
{
	if (m_nSizeMode == OriginalSize)
		SetWindowPos(NULL,0,0,nWidth,nHeight,SWP_NOMOVE | SWP_NOZORDER);

	HDC hWinDC = ::GetDC(m_hWnd);
	if (!hWinDC) return FALSE;
	
	m_hMemDC = CreateCompatibleDC(hWinDC);
	if (!m_hMemDC) 
	{
		::ReleaseDC(m_hWnd,hWinDC);
		return FALSE;
	};

	m_hBitmap  = CreateCompatibleBitmap(hWinDC,nWidth,nHeight);
	if (!m_hBitmap) 
	{
		::ReleaseDC(m_hWnd,hWinDC);
		::DeleteDC(m_hMemDC);
		return FALSE;
	};

	m_hOldBitmap = reinterpret_cast<HBITMAP> 
						(SelectObject(m_hMemDC,m_hBitmap));
	
	// fill the background
	m_clrBackground = GetSysColor(RGB(255,0,0));
	RECT rect = {0,0,nWidth,nHeight};
	FillRect(m_hMemDC,&rect,(HBRUSH)(COLOR_WINDOW));

	::ReleaseDC(m_hWnd,hWinDC);
	m_bIsInitialized = TRUE;
	return TRUE;
}






BOOL CxPicture::RedrawWindow()
{
	/*CRect rect;

	GetClientRect( rect );
	InvalidateRect( rect );*/
	Invalidate();
	return TRUE;
}


BOOL CxPicture::SetBitmap(HBITMAP hBitmap, ImageSize Emode, COLORREF rgbTransp)
{
	UnLoad();

	m_nSizeMode = Emode;

	BOOL bRet = m_pPicture->CreateFromHBITMAP(hBitmap);
	if (!bRet) return FALSE;

	m_PictureSize.cx = m_pPicture->GetWidth();
	m_PictureSize.cy = m_pPicture->GetHeight();
	m_nFrameCount = m_pPicture->GetNumFrames();
	
	bRet = PrepareDC(m_PictureSize.cx, m_PictureSize.cy);
	if (!bRet) return FALSE;

	DrawBitmap();

	return TRUE;
}


void CxPicture::SetOriginalSize()
{


}

BOOL CxPicture::SetBitmap(UINT nIDResource, ImageSize Emode, COLORREF rgbTransp)
{
	UnLoad();

	m_nSizeMode = Emode;

	HBITMAP hBmp = ::LoadBitmap( AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(nIDResource));

	return SetBitmap(hBmp, Emode);
}


BOOL CxPicture::SetBitmap(LPCTSTR lpszFileName, ImageSize Emode, COLORREF rgbTransp)
{
	UnLoad();

	m_nSizeMode = Emode;

	TRACE("m_arrFrames Size = %d\n", m_arrFrames.size());
	CString csExt = lpszFileName;
	int nDotPos = csExt.ReverseFind('.');
	if (nDotPos != -1) 
		csExt = csExt.Mid(++nDotPos);
	
	m_nImgType = CxCommon::FindImgType(csExt);
	if (m_nImgType == CXIMAGE_FORMAT_GIF)
		m_bIsGIF = TRUE;

	// Load Image From disk
	BOOL bRet = m_pPicture->Load(lpszFileName, m_nImgType);
	if (!bRet) return FALSE;
	
	m_PictureSize.cx = m_pPicture->GetWidth();
	m_PictureSize.cy = m_pPicture->GetHeight();

	TFrame	frame;
	UINT	nCurFrame = 0;

	m_nFrameCount = m_pPicture->GetNumFrames();
	for(unsigned int i=0; i < m_nFrameCount; i++){
		CxImage *newImage = new CxImage();
		newImage->SetFrame(i);
		newImage->Load(lpszFileName,m_nImgType);

		frame.m_pPicture = newImage;
		frame.m_frameOffset.cx= 0; 
		frame.m_frameOffset.cy = 0;
		frame.m_frameSize.cx = newImage->GetWidth();  
		frame.m_frameSize.cy = newImage->GetHeight();
		frame.m_nDelay = newImage->GetFrameDelay();
		frame.m_nDisposal = 1;

		m_arrFrames.push_back(frame);
	}
	bRet = PrepareDC(m_pPicture->GetWidth(), m_pPicture->GetHeight());
	if (!bRet) return FALSE;

	DrawBitmap();
	return TRUE;
}


BOOL CxPicture::SetBitmap(const CByteArray& ImgBuffer, int nImgType, COLORREF rgbTransp)
{
	
	return TRUE;
}



BOOL CxPicture::RenderText()
{
	CRect rect;
	GetClientRect(rect);

	::DrawText(m_hMemDC, "HELLO", 5, &rect, 0);

	Invalidate(FALSE);
	return TRUE;
}

BOOL CxPicture::DrawBitmap()
{
	if (!m_bIsInitialized)
		return FALSE;

	if (IsAnimatedGIF()){
	// the picture needs animation
	// we'll start the thread that will handle it for us
	
		unsigned int nDummy;
		m_hThread = (HANDLE) _beginthreadex(NULL,0,_ThreadAnimation,this,
			CREATE_SUSPENDED,&nDummy);
		if (!m_hThread){
			TRACE(_T("Draw: Couldn't start a GIF animation thread\n"));
			return FALSE;
		} 
		else 
			ResumeThread(m_hThread);
	} 
	else{
		if (m_pPicture){
			long hmWidth  = m_pPicture->GetWidth();
			long hmHeight = m_pPicture->GetHeight();
			if (m_pPicture->Draw2(m_hMemDC, 0, 0, m_PictureSize.cx, m_PictureSize.cy) == TRUE){
				Invalidate(FALSE);
				return TRUE;
			};
		};
	};

	return FALSE;	
}

SIZE CxPicture::GetSize() const
{
	return m_PictureSize;
}




//============================================================================
// GIF ANIMATION THREAD 
//============================================================================

UINT WINAPI CxPicture::_ThreadAnimation(LPVOID pParam)
{
	ASSERT(pParam);
	CxPicture *pPic = reinterpret_cast<CxPicture *> (pParam);

	pPic->m_bIsPlaying = TRUE;
	pPic->ThreadAnimation();
	pPic->m_bIsPlaying = FALSE;

	// this thread has finished its work so we close the handle
	CloseHandle(pPic->m_hThread); 
	// and init the handle to zero (so that Stop() doesn't Wait on it)
	pPic->m_hThread = 0;
	return 0;
}

void CxPicture::ThreadAnimation()
{
	while (!m_bExitThread)
	{
		if (m_arrFrames[m_nCurrFrame].m_pPicture)
		{
			long hmWidth = m_arrFrames[m_nCurrFrame].m_pPicture->GetWidth();
			long hmHeight= m_arrFrames[m_nCurrFrame].m_pPicture->GetHeight();
			
			if (m_arrFrames[m_nCurrFrame].m_pPicture->Draw2(m_hMemDC, 
				m_arrFrames[m_nCurrFrame].m_frameOffset.cx, 
				m_arrFrames[m_nCurrFrame].m_frameOffset.cy, 
				m_arrFrames[m_nCurrFrame].m_frameSize.cx, 
				m_arrFrames[m_nCurrFrame].m_frameSize.cy) == TRUE)
			{
				Invalidate(FALSE);
			};
			
			if (m_bExitThread) break;

			// if the delay time is too short (like in old GIFs), wait for 100ms
			if (m_arrFrames[m_nCurrFrame].m_nDelay < 5) 
				WaitForSingleObject(m_hExitEvent, 100);
			else
				WaitForSingleObject(m_hExitEvent, 10*m_arrFrames[m_nCurrFrame].m_nDelay);

			if (m_bExitThread) break;

		};
		m_nCurrFrame++;
		if (m_nCurrFrame == m_arrFrames.size())
		{
			m_nCurrFrame
				= 0; 
		// init the screen for the first frame,
			HBRUSH hBrush = CreateSolidBrush(m_clrBackground);
			if (hBrush)
			{
				RECT rect = {0,0,m_PictureSize.cx,m_PictureSize.cy};
				FillRect(m_hMemDC,&rect,hBrush);
				DeleteObject(hBrush);
			};
		};
	};
}

void CxPicture::Stop()
{
	m_bIsPlaying = FALSE;
	m_bExitThread = TRUE;
	SetEvent(m_hExitEvent);
	if (m_hThread)
	{
		// we'll wait for 5 seconds then continue execution
		WaitForSingleObject(m_hThread,5000);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	// make it possible to Draw() again
	ResetEvent(m_hExitEvent);
	m_bExitThread = FALSE;
}


BOOL CxPicture::IsAnimatedGIF() const
{
	return (m_bIsGIF && (m_arrFrames.size() > 1));
}

BOOL CxPicture::IsPlaying() const
{
	return m_bIsPlaying;
}

int CxPicture::GetFrameCount() const
{
	if (!IsAnimatedGIF())
		return 0;

	return m_arrFrames.size();
}

COLORREF CxPicture::GetBkColor() const
{
	return m_clrBackground;
}


//============================================================================
// WINDOWS MESSAGE HANDLING
//============================================================================

void CxPicture::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(rect);
	
	dc.SetBkMode(TRANSPARENT);

	CBrush backBrush(RGB(255,255,255));
    dc.FillRect(&rect, &backBrush);

	// Render background color
	//if (m_fillmode == Normal)
	//	dc.FillRect(&rect, m_pBrush);
	//else
	//	DrawGradientFill(&dc, &rect, m_fillmode);

	// Render Bitmap
	::StretchBlt(dc.m_hDC, 0, 0, rect.Width(), rect.Height(),
		m_hMemDC, 0, 0, m_PictureSize.cx, m_PictureSize.cy, SRCCOPY);

	//::DrawText(dc.m_hDC, "HELLO", 5, &rect, 0);
}



void CxPicture::OnDestroy() 
{
	Stop();	
	CStatic::OnDestroy();
}

void CxPicture::OnSize(UINT nType, int cx, int cy)
{
  CStatic::OnSize(nType, cx, cy);
  Invalidate();
}

//Credits goes to Aquiruse http://www.thecodeproject.com/buttonctrl/hoverbuttonex.asp
void CxPicture::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACE("OnMouseMove : %d %d\r\n", point.x, point.y);

	if (!m_bTracking){
		/*TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
		m_point = point;*/
	}
	CStatic::OnMouseMove(nFlags, point);
}

LRESULT CxPicture::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	m_bHover=TRUE;
	::SetActiveWindow(GetParent()->GetSafeHwnd());
	Invalidate();

	return 0;
}

LRESULT CxPicture::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bTracking = FALSE;
	m_bHover=FALSE;
	Invalidate();

	return 0;
}

void CxPicture::OnDropFiles(HDROP hDropInfo)
{
	int		nFiles = 0;
	TCHAR	szFile[MAX_PATH];


	nFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	if (nFiles != 1)
		return;

	DragQueryFile(hDropInfo, 0, szFile, sizeof(szFile));
	SetBitmap(szFile);
	

	DragFinish(hDropInfo);

}

void CxPicture::OnRButtonDown(UINT nFlags, CPoint point)
{

	if (IsMoveable() == TRUE)
	{
		m_point = point;
		CRect rect;
		GetWindowRect( rect );
		ScreenToClient( rect );
		m_pTrack = new CRectTracker(&rect, CRectTracker::dottedLine |
								CRectTracker::resizeInside |
								CRectTracker::hatchedBorder);
		// RIGHT-CLICK + CONTROL
		if (nFlags & MK_CONTROL){
			GetWindowRect(rect);
			GetParent()->ScreenToClient(rect);
			m_pTrack->TrackRubberBand(GetParent(), rect.TopLeft());
			m_pTrack->m_rect.NormalizeRect();
		}
		else {
			m_pTrack->Track(GetParent(), point);
		}
		rect = LPRECT(m_pTrack->m_rect);
		MoveWindow(&rect,TRUE);//Move Window to our new position
		
		
		// Clean our mess
		if (m_pTrack)
			delete m_pTrack;

		rect = NULL;
	}

	CStatic::OnRButtonDown(nFlags, point);
}



void CxPicture::SetBkColor(COLORREF rgb, COLORREF rgbHigh , FillMode mode)
{
	/*
	m_crLoColor = rgb;
	m_crHiColor = rgbHigh;
	m_fillmode = mode;

	m_rgbBkgnd = rgb;
	if (m_pBrush){
		delete m_pBrush;
		m_pBrush = new CBrush(m_rgbBkgnd);
	}
	else
		m_pBrush = new CBrush(m_rgbBkgnd);

		Invalidate();
	*/
}

BOOL CxPicture::SetPaintRect(const RECT *lpRect)
{
	return CopyRect(&m_PaintRect, lpRect);
}

BOOL CxPicture::GetPaintRect(RECT *lpRect)
{
	return CopyRect(lpRect, &m_PaintRect);
}




