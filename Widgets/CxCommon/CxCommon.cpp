// CxCommon.cpp: implementation of the CxCommon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CxCommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CxCommon::CxCommon()
{
	m_MapExtType[ _T("bmp") ]	= CXIMAGE_FORMAT_BMP;

#if CXIMAGE_SUPPORT_JPG
	m_MapExtType[ _T("jpg") ]	= CXIMAGE_FORMAT_JPG;
	m_MapExtType[ _T("jpeg")]	= CXIMAGE_FORMAT_JPG;
#endif

#if CXIMAGE_SUPPORT_GIF
	m_MapExtType[ _T("gif") ]	= CXIMAGE_FORMAT_GIF;
#endif

#if CXIMAGE_SUPPORT_PNG
	m_MapExtType[ _T("png") ]	= CXIMAGE_FORMAT_PNG;
#endif

#if CXIMAGE_SUPPORT_MNG
	m_MapExtType[ _T("mng") ]	= CXIMAGE_FORMAT_MNG;
	m_MapExtType[ _T("jng") ]	= CXIMAGE_FORMAT_MNG;
#endif

#if CXIMAGE_SUPPORT_ICO
	m_MapExtType[ _T("ico") ]	= CXIMAGE_SUPPORT_ICO;
#endif

#if CXIMAGE_SUPPORT_TIF
	m_MapExtType[ _T("tiff")]	= CXIMAGE_FORMAT_TIF;
	m_MapExtType[ _T("tif") ]	= CXIMAGE_FORMAT_TIF;
#endif

#if CXIMAGE_SUPPORT_TGA
	m_MapExtType[ _T("tga") ]	= CXIMAGE_FORMAT_TGA;
#endif

#if CXIMAGE_SUPPORT_PCX
	m_MapExtType[ _T("pcx") ]	= CXIMAGE_FORMAT_PCX;
#endif

#if CXIMAGE_SUPPORT_WBMP
	m_MapExtType[ _T("wbmp")]	= CXIMAGE_FORMAT_WBMP;
#endif

#if CXIMAGE_SUPPORT_WMF
	m_MapExtType[ _T("wmf") ]	= CXIMAGE_FORMAT_WMF;
	m_MapExtType[ _T("emf") ]	= CXIMAGE_FORMAT_WMF;
#endif

#if CXIMAGE_SUPPORT_JP2
	//m_MapExtType[ _T("jp2") ]	= CXIMAGE_FORMAT_J2K;
	//m_MapExtType[ _T("j2k") ]	= CXIMAGE_FORMAT_J2K;
#endif

#if CXIMAGE_SUPPORT_JBG
	m_MapExtType[ _T("jbg") ]	= CXIMAGE_FORMAT_JBG;
#endif

#if CXIMAGE_SUPPORT_JPC
	m_MapExtType[ _T("jpc") ]	= CXIMAGE_SUPPORT_JPC;
	m_MapExtType[ _T("j2c") ]	= CXIMAGE_SUPPORT_JPC;
#endif

#if CXIMAGE_SUPPORT_PGX
	m_MapExtType[ _T("pgx") ]	= CXIMAGE_FORMAT_PGX;
#endif

#if CXIMAGE_SUPPORT_RAS
	m_MapExtType[ _T("ras") ]	= CXIMAGE_FORMAT_RAS;
#endif

#if CXIMAGE_SUPPORT_PNM
	m_MapExtType[ _T("pnm") ]	= CXIMAGE_FORMAT_PNM;
	m_MapExtType[ _T("pgm") ]	= CXIMAGE_FORMAT_PNM;
	m_MapExtType[ _T("ppm") ]	= CXIMAGE_FORMAT_PNM;
#endif

	m_MapExtType[ _T("000") ]	= CXIMAGE_FORMAT_UNKNOWN;

	
	// LIBRARY TO DRAW COLOR GRADIENTS
	hinst_msimg32 = LoadLibrary( "msimg32.dll" );
	if( hinst_msimg32 ){
		dllfunc_GradientFill = ((LPFNDLLFUNC) GetProcAddress( hinst_msimg32, "GradientFill" ));
	}

}

CxCommon::~CxCommon()
{
	// Dsetroy our map
	m_MapExtType.clear();

	// Release our dll for gradient drawing
	if ( hinst_msimg32 ){
		::FreeLibrary( hinst_msimg32 );
		dllfunc_GradientFill = NULL;
	}
}


// Take an Image ext (ex bmp) and return the CxImage type
int CxCommon::FindImgType( const CString& strExt)
{
	CString strLocal = strExt;

	strLocal.MakeLower();

	// If cannot find this ext return CXIMAGE_FORMAT_UNKNOWN
	if (m_MapExtType.find( strLocal ) == m_MapExtType.end() )
		return CXIMAGE_FORMAT_UNKNOWN;

	return m_MapExtType[ strLocal ];
}


// Take a cxImage type and returns an file extension
LPCTSTR	CxCommon::FindImgType(int nImgType)
{
	map<CString, int>::iterator it;

	for (it = m_MapExtType.begin(); it != m_MapExtType.end(); ++it){

		if ( (*it).second ==  nImgType)
			return (*it).first;
	}

	return _T("000");
}

void CxCommon::DrawGradientFill(CDC* pDC, CRect* pRect, FillMode enuFillMode,
								COLORREF crLoColor, COLORREF crHiColor)
{
	TRIVERTEX rcVertex[2];
	rcVertex[0].x=pRect->left;
	rcVertex[0].y=pRect->top;
	rcVertex[0].Red=GetRValue(crLoColor)<<8;
	rcVertex[0].Green=GetGValue(crLoColor)<<8;
	rcVertex[0].Blue=GetBValue(crLoColor)<<8;
	rcVertex[0].Alpha=0x0000;
	rcVertex[1].x=pRect->right;
	rcVertex[1].y=pRect->bottom;
	rcVertex[1].Red=GetRValue(crHiColor)<<8;
	rcVertex[1].Green=GetGValue(crHiColor)<<8;
	rcVertex[1].Blue=GetBValue(crHiColor)<<8;
	rcVertex[1].Alpha=0;

	GRADIENT_RECT grect;
	grect.UpperLeft=0;
	grect.LowerRight=1;

	dllfunc_GradientFill( *pDC ,rcVertex,2,&grect,1,
	enuFillMode == HGradient ? GRADIENT_FILL_RECT_H :  GRADIENT_FILL_RECT_V);
}


/*
int	CxCommon::GetImgBuffer(CByteArray& ImgBuffer)
{

	return 1;
}
*/