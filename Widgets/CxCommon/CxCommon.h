// CxCommon.h: interface for the CxCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CXCOMMON_H__328969D0_546F_495B_82FA_30360CECB377__INCLUDED_)
#define AFX_CXCOMMON_H__328969D0_546F_495B_82FA_30360CECB377__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../cximage/ximage.h"
#include <map>

using namespace std;


#if defined(_AFXDLL)||defined(_USRDLL)
 #define DLLEXPORT __declspec(dllexport)
#elif defined(_MSC_VER)&&(_MSC_VER<1200)
 #define DLLEXPORT __declspec(dllimport)
#else
 #define DLLEXPORT
#endif

//============================================================================
// CMemDC : Implementation of memory DC for flicker free drawing
//============================================================================
class CMemDC : public CDC {
private:
	CBitmap		m_bitmap;		// Offscreen bitmap
	CBitmap*	m_oldBitmap;	// bitmap originally found in CMemDC
	CDC*		m_pDC;			// Saves CDC passed in constructor
	CRect		m_rect;			// Rectangle of drawing area.
	BOOL		m_bMemDC;		// TRUE if CDC really is a Memory DC.
public:

	CMemDC(CDC* pDC, const CRect* pRect = NULL, BOOL transparent = FALSE) : CDC()
	{
		ASSERT(pDC != NULL);

		// Some initialization
		m_pDC = pDC;
		m_oldBitmap = NULL;
		m_bMemDC = !pDC->IsPrinting();

		// Get the rectangle to draw
		if (pRect == NULL) {
			pDC->GetClipBox(&m_rect);
		} else {
			m_rect = *pRect;
		}

		if (m_bMemDC) {
			// Create a Memory DC
			CreateCompatibleDC(pDC);
			pDC->LPtoDP(&m_rect);

			m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_oldBitmap = SelectObject(&m_bitmap);

			SetMapMode(pDC->GetMapMode());
			pDC->DPtoLP(&m_rect);
			SetWindowOrg(m_rect.left, m_rect.top);
		} else {
			// Make a copy of the relevent parts of the current DC for printing
			m_bPrinting = pDC->m_bPrinting;
			m_hDC       = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}

		SetBkMode(TRANSPARENT);

		// Fill background
		if (transparent){
			BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				m_pDC, 0, 0, SRCCOPY);
		}
		else{
			//SetBkMode(TRANSPARENT);
			FillSolidRect(m_rect, pDC->GetBkColor()); // Not needed in OPAQUE mode???  See documentation
		}
	}


	~CMemDC()
	{
		if (m_bMemDC) {
			// Copy the offscreen bitmap onto the screen.
			m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				this, m_rect.left, m_rect.top, SRCCOPY);

			//Swap back the original bitmap.
			SelectObject(m_oldBitmap);
		} else {
			// All we need to do is replace the DC with an illegal value,
			// this keeps us from accidently deleting the handles associated with
			// the CDC that was passed to the constructor.
			m_hDC = m_hAttribDC = NULL;
		}
	}

	// Allow usage as a pointer
	CMemDC* operator->()
	{
		return this;
	}

	// Allow usage as a pointer
	operator CMemDC*()
	{
		return this;
	}
};



class CxCommon
{
// Enumerations
public:

typedef UINT (CALLBACK* LPFNDLLFUNC)(HDC,CONST PTRIVERTEX,DWORD,CONST PVOID,DWORD,DWORD);
static enum FillMode { Normal, HGradient, VGradient };


public:
	CxCommon();
	virtual ~CxCommon();

	// Common Image properties;
	int 		FindImgType( const CString& strExt);
	LPCTSTR		FindImgType(int nImgType);
	void		DrawGradientFill(CDC* pDC, CRect* pRect, FillMode enuFillMode, 
					COLORREF crLoColor, COLORREF crHiColor);

	//int			GetImgBuffer(CByteArray& ImgBuffer);

protected:
	map<CString, int> m_MapExtType;
	
	// Gradient color
	HINSTANCE		hinst_msimg32;
	LPFNDLLFUNC		dllfunc_GradientFill;

	// Image buffer
	CByteArray		m_ImgBuffer;

};

#endif // !defined(AFX_CXCOMMON_H__328969D0_546F_495B_82FA_30360CECB377__INCLUDED_)
