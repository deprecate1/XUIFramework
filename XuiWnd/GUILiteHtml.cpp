// GUILiteHtml.cpp: implementation of the CGUILiteHtml class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUILiteHtml.h"
#include "../GuiBaker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUILiteHtml::CGUILiteHtml()
{
	m_strElementType = _T("LiteHtml");
	m_strName		 = "ID_LITEHTML";
	m_strText		 = _T("LiteHtml");	 
	m_DefaultSize    = CSize(100, 40);
	m_pHtmlLite		 = NULL;
}

CGUILiteHtml::~CGUILiteHtml()
{

}

void CGUILiteHtml::Initialize()
{
	
}


int CGUILiteHtml::Create(CWnd* pParent, CRect WidgetRect)
{
	if( !CGUIElement::Create(pParent, WidgetRect) )
		return 0;

	TRACE(_T("CGUILiteHtml::Create(CWnd* pParent = 0x%x\n"), pParent);

	CPPHtmlStatic* pControl = new CPPHtmlStatic();
	m_pRootWnd = pParent;
		
	
	//BOOL bRet = pControl->Create("", WS_VISIBLE|WS_CHILD, m_rectElement,m_pRootWnd);
	//pControl->SetWindowText( _T("ZOB") );

	BOOL bRet = pControl->CreateEx(0,_T("STATIC"),_T(""), WS_CHILD| WS_VISIBLE,
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

bool CGUILiteHtml::PropertyChanging( const void* pvProperty , void* pvNewValue )
{
	bool bChangeOK = CGUIElement::PropertyChanging(pvProperty, pvNewValue);

 
	CPPHtmlStatic* pElement = (CPPHtmlStatic*)m_pElementWnd;

	// Caption change
	if(pvProperty == &m_strText){
		CString strNewCaption = *(CString *)pvNewValue;
		m_strText = strNewCaption;
		pElement->SetWindowText( m_strText );	
	}

	// Background color change
	if(pvProperty == &m_cBkColor){
		m_cBkColor = *(COLORREF *)pvNewValue;
		pElement->SetBkColor( m_cBkColor );
	}

	// Text color change
	if(pvProperty == &m_cTextColor){
		m_cTextColor = *(COLORREF *)pvNewValue;
		pElement->SetTextColor( m_cTextColor );
	}

	/*
	// Image Properties
	if(pvProperty == &m_strImgPath){
		CString strImagepath = *(CString *)pvNewValue;
		m_strImgPath = strImagepath;
		if (m_strImgPath.IsEmpty() == 0 ){
			pElement->SetBitmap( m_strImgPath );
			//m_bHasImage = true;
		}
		//else
			//m_bHasImage = false;
	}
	*/

	return true;
}


void CGUILiteHtml::GetProperties(EPropList& PropList)
{
	TRACE( _T("CGUILiteHtml::GetProperties()\n"));
	
	m_pHtmlLite = (CPPHtmlStatic*)m_pElementWnd;

	// Show Common widgets properties (Control Type, pos and size)
	CGUIElement::GetProperties(PropList);
	
	// Caption
	//m_pHtmlLite->GetWindowText(m_strText);
	PropList.AddPropString(this, "Caption", &m_strText, true)->SetComment("");

	// Background color
	m_cBkColor = m_pHtmlLite->GetBkColor();
	PropList.AddPropColor ( this , "Background color", &m_cBkColor )->SetComment("");
	
	// Text color
	m_cTextColor = m_pHtmlLite->GetTextColor();
	PropList.AddPropColor ( this , "Text color", &m_cTextColor )->SetComment("");

	/*
	// Image
	PropList.AddPropSeparator(this, "Image");
	PropList.AddPropFile(this, "From File", &m_strImgPath, "Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||")->SetComment("");
	if (m_pCxStatic->HasImage(m_strImgType, m_nImgWidth,m_nImgHeight)){
		
		PropList.AddPropString(this, "Type",   &m_strImgType, true)->SetComment("");
		PropList.AddPropInt   (this ,"Width" , &m_nImgWidth)->SetComment("");
		PropList.AddPropInt   (this ,"Height", &m_nImgHeight)->SetComment("");
	}
	*/

}


int	CGUILiteHtml::LoadXML(TiXmlElement* pDataElm)
{
	TiXmlText* pTextElm = NULL;
	TiXmlNode* pNode	= NULL;

	CString strTmp;
	int nTokPos = 0;
	m_pHtmlLite = (CPPHtmlStatic*)m_pElementWnd;

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
				m_strText = pNode->ToText()->Value();
			}
			else{
				m_strText = _T("");
			}
			m_pHtmlLite->SetWindowText( m_strText );
		}
	
	

		pDataElm = pDataElm->NextSiblingElement();
	}
	
	return 1;
}






int	CGUILiteHtml::SaveXML(TiXmlElement *pDataNode)
{
	TiXmlElement*	pSaveXMLRoot = NULL;
	TiXmlElement*	pSaveXMLElement = NULL;
	TiXmlText*		pSaveXMLText	= NULL; 
	CString			strTmp;
	CRect			rect;

	m_pHtmlLite = (CPPHtmlStatic*)m_pElementWnd;
	
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
	pSaveXMLText = new TiXmlText( m_strText );
	pSaveXMLElement->LinkEndChild( pSaveXMLText );
	pSaveXMLRoot->LinkEndChild( pSaveXMLElement );

	pSaveXMLElement = new TiXmlElement( "bg" );
	pSaveXMLElement->SetAttribute( _T("fillmode"), 0 );
	strTmp.Format(_T("0x%6.6x"), m_pHtmlLite->GetBkColor() );
	pSaveXMLElement->SetAttribute( "LowColor", strTmp );
	strTmp.Format(_T("0x%6.6x"), m_pHtmlLite->GetBkColor() );
	pSaveXMLElement->SetAttribute( "HiColor", strTmp );
	pSaveXMLRoot->LinkEndChild( pSaveXMLElement );

	
	return 1;
}
