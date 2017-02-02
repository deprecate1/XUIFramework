/*===========================================================================
====    Project : CxStatic (www.codeproject.com)                         ====
====    File name           :  CxStatic.h                                ====
====    Creation date       :  09/2004                                   ====
====    Author(s)           :  Vincent Richomme                          ====
===========================================================================*/

#ifndef CSTATICTEST_H
#define CSTATICTEST_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <process.h>
#include "../cxcommon/cxcommon.h"


class DLLEXPORT CxStatic : public CStatic, public CxCommon
{
public:

	enum ImageSize{ OriginalSize, FitControl};
	enum LinkStyle { LinkNone, HyperLink, MailLink };
	enum Type3D { Raised, Sunken};
	enum EHAlign {Left, Middle , Right };
	enum EVAlign {Top,  Center , Bottom};

	// structure that keeps a single frame info
	struct TFrame    
	{
		CxImage* m_pPicture;  // pointer to the interface used for drawing
		SIZE     m_frameSize;
		SIZE     m_frameOffset;
		UINT     m_nDelay;     // delay (in 1/100s of a second)
		UINT     m_nDisposal;  // disposal method
	};

	struct TThreadParams
	{
		CxStatic*	pThis;
		CDC*		pDC;
		LPRECT		pRect;
	};


	CxStatic();
	virtual ~CxStatic();

	void	OnDraw(CDC* pDC, LPRECT lpRect = NULL);
	void	SetHAlign(EHAlign enuHAlign);
	void	SetVAlign(EVAlign enuVAlign);
	BOOL	IsMoveable() { return m_bAllowMove; }
	void	SetMoveable(BOOL moveAble = TRUE);
	void	BlinkBmp(UINT nIDBmp1, UINT nIDBmp2, DWORD dwTimeout);
	void	SetBkColor(COLORREF rgb, COLORREF crBkgndHigh = 0, FillMode mode = Normal);
	COLORREF GetBkColor() {return m_rgbBkgnd;}
	void	SetTransparent(BOOL bTranspMode);
	void	SetTextColor(COLORREF col);
	COLORREF GetTextColor() {return m_rgbText;}
	void	SetFont(LPCTSTR szFont, int nPointSize,int nWeight, BOOL bRedraw = TRUE);
	void	SetFont(LOGFONT *pLogFont, BOOL bRedraw = TRUE);
	void	SetFont(CFont *pFont, BOOL bRedraw = TRUE);
	void	SetFont3D(BOOL bFont3D, Type3D type);

	void	SetAutoAdjustFont(BOOL bAutoAdjustFont);

	BOOL	SetBitmap(HBITMAP hBitmap, ImageSize Emode = FitControl,
				COLORREF rgbTransp =  0xFF000000);
	BOOL	SetBitmap(UINT nIDResource, ImageSize Emode = FitControl,
				COLORREF rgbTransp =  0xFF000000);	// Loads bitmap from resource ID

	BOOL	SetBitmap(LPCTSTR lpszResName, ImageSize Emode = FitControl,
				COLORREF rgbTransp = 0xFF000000);	// Loads bitmap from resource name

	BOOL	SetBitmap(const CByteArray& ImgBuffer, int nImgType,
				COLORREF rgbTransp = 0xFF000000);

	void	SetTransColor(COLORREF coltrans);

	int		GetImgBuffer(CByteArray& ImgBuffer);

	void	StopAnimatedGif();
	void	SetRounded(BOOL bRounded);

	void	SetWindowText(LPCTSTR strText);
	void	AppendText(LPCTSTR szFmt, ...);
	void	Format(LPCTSTR szFmt, ...);

	int		HasImage(CString& strImgType, int& nImgWidth, int& nImgHeight, COLORREF& rgbTransp);

protected:
	CDC*			m_pDC;
	CString			m_strText;
	BOOL			m_bNotifyParent;
	BOOL			m_bTransparentBk;
	BOOL			m_bAutoAdjustFont;
	BOOL			m_bAutoWrapping;
	BOOL			m_bRounded;
	COLORREF		m_rgbText;
	FillMode		m_fillmode;
	COLORREF		m_rgbBkgnd;
	COLORREF		m_crHiColor;
	COLORREF		m_crLoColor;
	COLORREF		m_cr3DHiliteColor;
	CBrush *		m_pBrush;
	CRect			m_rc;
	DWORD			m_dwTxtFlags;

	//HINSTANCE		hinst_msimg32;
	//LPFNDLLFUNC		dllfunc_GradientFill;

	// BITMAP ATTRIBUTES
	CxImage*		m_pImage;
	int				m_nImgType;
	ULONG			m_nImgWidth;
	ULONG			m_nImgHeight;
	TFrame			m_frame;
	vector<TFrame>  m_arrFrames;
	TThreadParams	m_thrParams;
	//CPtrList		m_ptrFrames;
	int				m_nCurrFrame;
	int				m_nFrames;
	BOOL			m_bAnimPainting;
	BOOL			m_bIsPlaying;
	volatile BOOL	m_bExitThread;
	HANDLE			m_hThread; // Gif  Thread animation
	HANDLE			m_hExitEvent;
	//COLORREF		m_rgbTransp;
	COLORREF		m_clrBackground;
	SIZE			m_PictureSize;
	int				m_EDispMode;
	BOOL			m_bBitmap;
	int				m_nResourceID;
	HBITMAP			m_hBitmap;
    BITMAP			m_bmInfo;
    CString			m_strResourceName;

	// FONT ATTRIBUTES
	Type3D			m_3dType;
	BOOL			m_bFont3d;
	LOGFONT			m_DefLogFont;
	LOGFONT			m_lf;
	CFont			m_font;
	int				m_nFontSize;
	int				m_nFontSizeVar;
	CString			m_csFontFamilly;

	// MODIFIABLE ATTRIBUTES
	BOOL			m_bAllowMove;
	BOOL			m_bHover;
	BOOL			m_bTracking;
	CPoint			m_point;
	CRectTracker*	m_pTrack;

	// FONT METHODS
	void	ReconstructFont();
	int		GetFontPointSize(int nHeight);
	int		GetFontHeight(int nPointSize);

	// TEXT METHODS
	void	DrawText(CDC* pDC, CRect* pRect, CString csText);
	BOOL	IsASingleWord(const CString & csText);
	//void	DrawGradientFill(CDC* pDC, CRect* pRect, FillMode enumFillMode);

	// IMAGE METHODS
	void	UnLoad(); // stops animation plus releases all resources
	void	SetSizeMode(long nWidth, long nHeight);
	int		FindType(const CString& ext);
	void	DrawBitmap(CDC* pDC, CRect* pRect);
	BOOL	RedrawWindow();
	void	ThreadAnimation(TThreadParams* pThrParams);
	static UINT WINAPI _ThreadAnimation(LPVOID pParam);


	// MESSAGE HANDLER
	virtual void PreSubclassWindow();
	//virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

	afx_msg void	OnPaint();
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT	OnSetText(WPARAM wParam, LPARAM lParam); // WM_SETTEXT for UpdateData
	afx_msg LRESULT	OnSetFont(WPARAM wParam, LPARAM lParam); // WM_SETFONT
	afx_msg void	OnDropFiles(HDROP hDropInfo); // WM_DROPFILES
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	//afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam) ;
	afx_msg void	OnRButtonDown( UINT nFlags, CPoint point );


	DECLARE_MESSAGE_MAP()

};

#endif // CXSTATIC_H
