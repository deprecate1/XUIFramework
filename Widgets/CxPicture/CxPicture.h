

#if !defined(AFX_PICTUREEX_H__0EFE5DE0_7B68_4DB7_8B34_5DC634948438__INCLUDED_)
#define AFX_PICTUREEX_H__0EFE5DE0_7B68_4DB7_8B34_5DC634948438__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <process.h>
#include "../cxcommon/cxcommon.h"


typedef UINT (CALLBACK* LPFNDLLFUNC)(HDC,CONST PTRIVERTEX,DWORD,CONST PVOID,DWORD,DWORD);

class CxPicture : public CStatic, public CxCommon
{
public:

	enum ImageSize{ OriginalSize, FitControl};
	enum LinkStyle { LinkNone, HyperLink, MailLink };
	enum Type3D { Raised, Sunken};
	enum EHAlign {Left, Middle , Right };
	enum EVAlign {Top,  Center , Bottom};

struct TFrame    // structure that keeps a single frame info
{
	CxImage* m_pPicture;  // pointer to the interface used for drawing
	SIZE     m_frameSize;
	SIZE     m_frameOffset;
	UINT     m_nDelay;     // delay (in 1/100s of a second)
	UINT     m_nDisposal;  // disposal method
};


public:
	BOOL GetPaintRect(RECT *lpRect);
	BOOL SetPaintRect(const RECT *lpRect);
	CxPicture();
	virtual ~CxPicture();
	void Stop();   // stops animation
	void UnLoad(); // stops animation plus releases all resources


	void	OnDraw(CDC* pDC, LPRECT lpRect = NULL){}
	void	SetHAlign(EHAlign enuHAlign){}
	void	SetVAlign(EVAlign enuVAlign){}
	BOOL	IsMoveable() { return m_bAllowMove; }
	void	SetMoveable(BOOL moveAble = TRUE);
	BOOL	IsGIF() const;
	BOOL	IsPlaying() const;
	BOOL	IsAnimatedGIF() const;
	SIZE	GetSize() const;
	int		GetFrameCount() const;
	COLORREF GetBkColor() const;

	void	SetBkColor(COLORREF rgb, COLORREF crBkgndHigh = 0, FillMode mode = Normal);
	void	SetTransparent(BOOL bTranspMode);
	
	void	SetTextColor(COLORREF col);
	COLORREF GetTextColor() {return 0;}
	void	SetFont(const CString& strFont, int nPointSize,int nWeight);
	void	SetFont(LOGFONT* pLogFont, BOOL bRedraw = TRUE);
	void	SetFont(CFont* pFont, BOOL bRedraw = TRUE);

	
	BOOL	SetBitmap(HBITMAP hBitmap, ImageSize Emode = FitControl,
				COLORREF rgbTransp =  0xFF000000);
	BOOL	SetBitmap(UINT nIDResource, ImageSize Emode = FitControl,
				COLORREF rgbTransp =  0xFF000000);	// Loads bitmap from resource ID

	BOOL	SetBitmap(LPCTSTR lpszResName, ImageSize Emode = FitControl,
				COLORREF rgbTransp = 0xFF000000);	// Loads bitmap from resource name

	BOOL	SetBitmap(const CByteArray& ImgBuffer, int nImgType,
				COLORREF rgbTransp = 0xFF000000);

	void	SetTransColor(COLORREF coltrans){}
	int		GetImgBuffer(CByteArray& ImgBuffer){ return 0;}
	int		HasImage(CString& strImgType, int& nImgWidth, int& nImgHeight, COLORREF& rgbTransp);
	
	void	SetOriginalSize();

	// TODO Transform CxPicture into CxStatic
	// Need Help - If you do some modifications please email me
	// richom.v@free.fr

	void	SetWindowText(LPCTSTR strText);
	void	AppendText(LPCTSTR szFmt, ...);
	void	Format(LPCTSTR szFmt, ...);



protected:
	HINSTANCE		hinst_msimg32;
	LPFNDLLFUNC		dllfunc_GradientFill;
	BOOL			m_bNotifyParent;
	BOOL			m_bTransparentBk;
	int				m_nSizeMode;
	UINT			m_nFrameCount;
	RECT			m_PaintRect;
	SIZE			m_PictureSize;
	COLORREF		m_clrBackground;
	UINT			m_nCurrFrame;
	UINT			m_nDataSize;
	UINT			m_nCurrOffset;
	UINT			m_nGlobalCTSize;
	BOOL			m_bIsGIF;
	BOOL			m_bIsPlaying;
	volatile BOOL	m_bExitThread;
	BOOL			m_bIsInitialized;
	HDC				m_hMemDC;

	CxImage*		m_pImage;
	int				m_nImgType;
	HDC				m_hDispMemDC;
	HBITMAP			m_hDispMemBM;
	HBITMAP			m_hDispOldBM;

	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	HANDLE			m_hThread;
	HANDLE			m_hExitEvent;
	CxImage*		m_pPicture;
	CxMemFile		m_MemFile;
	
	// FILL ATTRIBUTES
	CBrush*			m_pBrush;
	COLORREF		m_rgbBkgnd;
	COLORREF		m_crHiColor;
	COLORREF		m_crLoColor;
	FillMode		m_fillmode;

	// TEXT ATTRIBUTES
	COLORREF		m_rgbText;
	BOOL			m_bAutoWrapping;
	CString			m_strText;

	// FONT ATTRIBUTES
	BOOL			m_bAutoAdjustFont;
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

	std::vector<TFrame> m_arrFrames;

	int		FindType(const CString& ext);
	BOOL	DrawBitmap();
	BOOL	RenderText();
	BOOL	Load(int nImgType);
	void	ThreadAnimation();
	static UINT WINAPI _ThreadAnimation(LPVOID pParam);


	BOOL	PrepareDC(int nWidth, int nHeight);
	BOOL	RedrawWindow();

	// MESSAGE HANDLER
	virtual void PreSubclassWindow();

	// Generated message map functions
	//{{AFX_MSG(CxPicture)
	afx_msg void	OnDestroy();
	afx_msg void	OnPaint();
	afx_msg LRESULT	OnSetText(WPARAM wParam, LPARAM lParam); // WM_SETTEXT for UpdateData
	afx_msg LRESULT	OnSetFont(WPARAM wParam, LPARAM lParam); // WM_SETFONT
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg void	OnDropFiles(HDROP hDropInfo); // WM_DROPFILES
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam) ;
	afx_msg void	OnRButtonDown( UINT nFlags, CPoint point );
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_PICTUREEX_H__0EFE5DE0_7B68_4DB7_8B34_5DC634948438__INCLUDED_)
