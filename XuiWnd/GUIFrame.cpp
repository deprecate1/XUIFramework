// GUIFrame.cpp: implementation of the CGUIFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUIFrame.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIFrame::CGUIFrame()
{
	m_DefaultSize = CSize(100, 40);
	m_strElementType = "Frame";
	m_strName		 = "ID_FRAME";
	m_pWidget		 = NULL;
	m_strCaption	 = _T("Default title");
}

CGUIFrame::~CGUIFrame()
{

}

void CGUIFrame::Initialize()
{

}


int CGUIFrame::Create(CWnd* pParent, CRect WidgetRect)
{
	if( !CGUIElement::Create(pParent, WidgetRect) )
		return 0;

	TRACE(_T("CGUIFrame::Create(CWnd* pParent = 0x%x\n"), pParent);

	CxFrame* pControl = new CxFrame;
	m_pRootWnd = pParent;

	BOOL bRet = pControl->CreateEx(WS_EX_TRANSPARENT,
			_T("STATIC"),
			_T(""), 
			WS_CHILD| WS_VISIBLE,
			m_rectElement.left,
			m_rectElement.top,
			m_rectElement.Width(),
			m_rectElement.Height(),
			m_pRootWnd->m_hWnd,NULL);

	if (!bRet)
		return 0;

	m_pElementWnd = pControl;
	m_pElementWnd->SetWindowText( m_strCaption );

	return 1;
}

bool CGUIFrame::PropertyChanging( const void* pvProperty , void* pvNewValue )
{
	bool bChangeOK = CGUIElement::PropertyChanging(pvProperty, pvNewValue);

	CxFrame* pElement = (CxFrame*)m_pElementWnd;

	// Caption change
	if(pvProperty == &m_strCaption){
		CString strNewCaption = *(CString *)pvNewValue;
		m_strCaption = strNewCaption;
		pElement->SetWindowText( m_strCaption );	
	}

	return true;
}



void CGUIFrame::GetProperties(EPropList& PropList)
{
	TRACE( _T("CGUIFrame::GetProperties()\n"));
	
	m_pWidget = (CxFrame*)m_pElementWnd;

	// Show Common widgets properties (Control Type, pos and size)
	CGUIElement::GetProperties(PropList);
	
	// Caption
	//m_pCxStatic->GetWindowText(m_strText);
	PropList.AddPropString(this, "Caption", &m_strCaption, true)->SetComment("");

}

int	CGUIFrame::LoadXML(TiXmlElement* pDataElm)
{
	TiXmlText* pTextElm = NULL;
	TiXmlNode* pNode	= NULL;
	CString strTmp;
	int nTokPos = 0;
	m_pWidget = (CxFrame*)m_pElementWnd;

	// Get Control name from <object> attribute
	strTmp	= pDataElm->Attribute( _T("name") );
	SetName( strTmp );

	// Go deeper
	pDataElm = pDataElm->FirstChild()->ToElement();
	while( pDataElm ){

		strTmp = pDataElm->Value();
		if( _tcsicmp(pDataElm->Value(), _T("id"))  == 0){

			strTmp = pDataElm->FirstChild()->ToText()->Value();
			SetID( _ttoi(strTmp ) );
		}
		else if( _tcsicmp(pDataElm->Value(), _T("pos"))  == 0){
			CPoint point;
			strTmp = pDataElm->FirstChild()->ToText()->Value();
			nTokPos = strTmp.Find(',',0);
			point.x = _ttoi( strTmp.Mid(0, nTokPos) );
			point.y = _ttoi( strTmp.Mid( ++nTokPos ) );
			SetPos( point );
		}
		else if( _tcsicmp(pDataElm->Value(), _T("size"))  == 0){
			CSize size;
			strTmp = pDataElm->FirstChild()->ToText()->Value();
			nTokPos = strTmp.Find(',',0);
			size.cx = _ttoi( strTmp.Mid(0, nTokPos) );
			size.cy = _ttoi( strTmp.Mid( ++nTokPos ) );
			SetSize( size );
		}
		else if( _tcsicmp(pDataElm->Value(), _T("caption"))  == 0){
			pNode = pDataElm->FirstChild();
			if (pNode){
				m_strCaption = pNode->ToText()->Value();
			}
			else{
				m_strCaption = _T("");
			}
			m_pWidget->SetWindowText( m_strCaption );

		}
		
		
		pDataElm = pDataElm->NextSiblingElement();
	}

	
	return 1;
}






int	CGUIFrame::SaveXML(TiXmlElement *pDataNode)
{
	TiXmlElement*	pSaveXMLRoot = NULL;
	TiXmlElement*	pSaveXMLElement = NULL;
	TiXmlText*		pSaveXMLText	= NULL; 
	CString			strTmp;
	CRect			rect;

	m_pWidget = (CxFrame*)m_pElementWnd;
	
	pSaveXMLRoot = new TiXmlElement( "object" );
	pSaveXMLRoot->SetAttribute( _T("class"),  m_strElementType);
	pSaveXMLRoot->SetAttribute( "name", m_strName );
	pDataNode->LinkEndChild( pSaveXMLRoot );

	pSaveXMLElement = new TiXmlElement( "id" );
	strTmp.Format( _T("%d"), GetID() );
	pSaveXMLText = new TiXmlText( strTmp );
	pSaveXMLElement->LinkEndChild( pSaveXMLText );
	pSaveXMLRoot->LinkEndChild( pSaveXMLElement );

	pSaveXMLElement = new TiXmlElement( "pos" );
	strTmp.Format( _T("%d,%d"), m_rectElement.left, m_rectElement.top );
	pSaveXMLText = new TiXmlText( strTmp );
	pSaveXMLElement->LinkEndChild( pSaveXMLText );
	pSaveXMLRoot->LinkEndChild( pSaveXMLElement );

	pSaveXMLElement = new TiXmlElement( "size" );
	strTmp.Format( _T("%d,%d"), m_rectElement.Width(), m_rectElement.Height() );
	pSaveXMLText = new TiXmlText( strTmp );
	pSaveXMLElement->LinkEndChild( pSaveXMLText );
	pSaveXMLRoot->LinkEndChild( pSaveXMLElement );

	pSaveXMLElement = new TiXmlElement( "caption" );
	pSaveXMLText = new TiXmlText( m_strCaption );
	pSaveXMLElement->LinkEndChild( pSaveXMLText );
	pSaveXMLRoot->LinkEndChild( pSaveXMLElement );

	return 0;
}



