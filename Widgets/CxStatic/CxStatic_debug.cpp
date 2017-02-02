// CxStatic.cpp : implementation file
//

#include "stdafx.h"
//#include "Borne.h"
#include "CxStatic.h"


// CxStatic

BEGIN_MESSAGE_MAP(CxStatic, CStatic)
END_MESSAGE_MAP()

CxStatic::CxStatic()
{
}

CxStatic::~CxStatic()
{
}





void CxStatic::SetBkColor(COLORREF rgb, COLORREF crBkgndHigh, BackFillMode mode )
{
	int a = 3;

}

void CxStatic::SetTextColor(COLORREF col)
{

}

void CxStatic::SetFont(const CString& strFont, int nPointSize,int nWeight, BOOL bRedraw)
{

}
void CxStatic::SetFont(LOGFONT *pLogFont, BOOL bRedraw )
{

}

void CxStatic::SetFont(CFont *pFont, BOOL bRedraw)
{

}

void CxStatic::SetFont3D(BOOL bFont3D, Type3D type)
{

}

BOOL CxStatic::SetBitmap(HBITMAP hBitmap, int Emode, COLORREF rgbTransparent)
{
	return TRUE;
}

BOOL CxStatic::SetBitmap(UINT nIDResource, int Emode, COLORREF rgbTransparent)
{
	return TRUE;
}

BOOL CxStatic::SetBitmap(LPCTSTR lpszResourceName, int Emode, COLORREF rgbTransparent)
{
	return TRUE;
}



// CxStatic message handlers

