// GUIPicture.cpp: implementation of the CGUIPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "../Borne.h"
#include "GUIPicture.h"
#include "../Widgets/cxpicture/cxpicture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIPicture::CGUIPicture()
{
	m_strElementType = "Picture";
	m_strName		 = "ID_PICTURE";

	m_DefaultSize = CSize(100, 40);
}

CGUIPicture::~CGUIPicture()
{

}


void CGUIPicture::Initialize()
{
	
}


int CGUIPicture::Create(CWnd* pParent, CRect WidgetRect)
{
	if( !CGUIElement::Create(pParent, WidgetRect) )
		return 0;

	TRACE(_T("CGUIStatic::Create(CWnd* pParent = 0x%x\n"), pParent);

	CxPicture* pControl = new CxPicture;
	m_pRootWnd = pParent;
		
	//m_hWnd = pControl->GetSafeHwnd();
	
	BOOL bRet = pControl->CreateEx(0,_T("STATIC"),_T(""), WS_CHILD| WS_VISIBLE,
			m_rectElement.left,
			m_rectElement.top,
			m_rectElement.Width(),
			m_rectElement.Height(),
			m_pRootWnd->m_hWnd,NULL);

	if (!bRet)
		return 0;

	m_pElementWnd = pControl;	

	return 1;
}


void CGUIPicture::GetProperties(EPropList& PropList)
{
	TRACE( _T("CGUIStatic::GetProperties()\n"));
	
	//CxPicture* pElement = (CxPicture*)m_pElementWnd;

	// Show Common widgets properties (Control Type, pos and size)
	CGUIElement::GetProperties(PropList);
	

	
}