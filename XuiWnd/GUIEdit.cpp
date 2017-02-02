// GUIStatic.cpp: implementation of the CGUIStatic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../GuiBaker.h"
#include "GUIEdit.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIEdit::CGUIEdit()
{
	m_strElementType = _T("Edit");
	m_strName		 = "ID_EDIT";
	m_strText		 = _T("");
	m_DefaultSize    = CSize(100, 40);
	m_nHAlignCbo	 = 0;
	m_nVAlignCbo	 = 0;
	//m_cTranspColor	 = -1;
	m_pWidget		 = NULL;
	m_bTransp		 = FALSE;
}



CGUIEdit::~CGUIEdit()
{

}


void CGUIEdit::Initialize()
{

}


int CGUIEdit::Create(CWnd* pParent, CRect WidgetRect)
{
	if( !CGUIElement::Create(pParent, WidgetRect) )
		return 0;

	TRACE(_T("CGUIEdit::Create(CWnd* pParent = 0x%x\n"), pParent);

	CEdit* pControl = new CEdit();
	m_pRootWnd = pParent;

	BOOL bRet = pControl->CreateEx(0,_T("EDIT"),_T(""), 
		ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		m_rectElement.left,
		m_rectElement.top,
		m_rectElement.Width(),
		m_rectElement.Height(),
		m_pRootWnd->m_hWnd,NULL);

	if (!bRet)
		return 0;

	m_pElementWnd = pControl;
	m_pElementWnd->SetWindowText( m_strText );

	return 1;
}

void CGUIEdit::OnDraw(CDC* pDC)
{
	
}




bool CGUIEdit::PropertyChanging( const void* pvProperty , void* pvNewValue )
{
	bool bChangeOK = CGUIElement::PropertyChanging(pvProperty, pvNewValue);

	CEdit* pElement = (CEdit*)m_pElementWnd;

	

	pElement->UpdateWindow();

	return true;
}


void CGUIEdit::GetProperties(EPropList& PropList)
{
	TRACE( _T("CGUIEdit::GetProperties()\n"));

	m_pWidget = (CEdit*)m_pElementWnd;

	// Show Common widgets properties (Control Type, pos and size)
	CGUIElement::GetProperties(PropList);

	// Caption
	//m_pCxStatic->GetWindowText(m_strText);
	PropList.AddPropString(this, "Caption", &m_strText, true)->SetComment("");

	PropList.AddPropCheck ( this , "Transparent"  , &m_bTransp )->SetComment("");

	// Background color
	//m_cBkColor = m_pCxStatic->GetBkColor();
	PropList.AddPropColor ( this , "Background color", &m_cBkColor )->SetComment("");

	// Text Properties
	PropList.AddPropSeparator(this, "Text");
	PropList.AddPropCombo ( this , "HAlign"   , &m_nHAlignCbo          )
	->AddString("Left")
	->AddString("Middle")
	->AddString("Right");
	PropList.AddPropCombo ( this , "VAlign"   , &m_nVAlignCbo          )
	->AddString("Top")
	->AddString("Middle")
	->AddString("Bottom");	
}


int	CGUIEdit::LoadXML(TiXmlElement* pDataElm)
{
	


	return 1;
}






int	CGUIEdit::SaveXML(TiXmlElement *pDataNode)
{
	

	return 0;
}