#ifndef CSTATICTEST_H
#define CSTATICTEST_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MemDC.h"
#include "DIBSectionLite.h"
#include "Rgbcolor.h"

typedef UINT (CALLBACK* LPFNDLLFUNC)(HDC,CONST PTRIVERTEX,DWORD,CONST PVOID,DWORD,DWORD);


// CxStatic
static enum ImageSize{ OriginalSize, FitControl};
static enum LinkStyle { LinkNone, HyperLink, MailLink };
static enum Type3D { Raised, Sunken};
static enum BackFillMode { Normal, HGradient, VGradient };

class CxStatic : public CStatic
{
public:
	CxStatic();
	virtual ~CxStatic();

	void	SetBkColor(COLORREF rgb, COLORREF crBkgndHigh = 0, BackFillMode mode = Normal);
	void	SetTextColor(COLORREF col);
	void	SetFont(const CString& strFont, int nPointSize,int nWeight, BOOL bRedraw = TRUE);
	void	SetFont(LOGFONT *pLogFont, BOOL bRedraw = TRUE);
	void	SetFont(CFont *pFont, BOOL bRedraw = TRUE);
	void	SetFont3D(BOOL bFont3D, Type3D type);
	BOOL	SetBitmap(HBITMAP hBitmap, int Emode = 0, 
				COLORREF rgbTransparent =  0xFF000000);
	BOOL	SetBitmap(UINT nIDResource, int Emode = 0,
				COLORREF rgbTransparent =  0xFF000000);	// Loads bitmap from resource ID
	BOOL	SetBitmap(LPCTSTR lpszResName, int Emode = 0,
				COLORREF rgbTransparent = 0xFF000000);	// Loads bitmap from resource name

protected:
	DECLARE_MESSAGE_MAP()
};

#endif
