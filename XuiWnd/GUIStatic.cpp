// GUIStatic.cpp: implementation of the CGUIStatic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../GuiBaker.h"
#include "GUIStatic.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIStatic::CGUIStatic()
{
	m_strElementType = _T("Static");
	m_strName		 = "ID_STATIC";
	m_strText		 = _T("Label");	 
	m_DefaultSize    = CSize(100, 40);
	m_nHAlignCbo	 = 0;
	m_nVAlignCbo	 = 0;
	//m_cTranspColor	 = -1;
	m_pCxStatic		 = NULL;
	m_bTransp		 = FALSE;
}



CGUIStatic::~CGUIStatic()
{

}


void CGUIStatic::Initialize()
{
	
}


int CGUIStatic::Create(CWnd* pParent, CRect WidgetRect)
{
	if( !CGUIElement::Create(pParent, WidgetRect) )
		return 0;

	TRACE(_T("CGUIStatic::Create(CWnd* pParent = 0x%x\n"), pParent);

	CxStatic* pControl = new CxStatic();
	m_pRootWnd = pParent;

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

void CGUIStatic::OnDraw(CDC* pDC)
{
	CRect rect;

	if (m_pElementWnd){
		m_pCxStatic = (CxStatic*)m_pElementWnd;

		 m_pCxStatic->GetWindowRect(&rect); 
		 m_pRootWnd->ScreenToClient(rect);
		 m_pCxStatic->OnDraw(pDC, &rect);
	}
}




bool CGUIStatic::PropertyChanging( const void* pvProperty , void* pvNewValue )
{
	bool bChangeOK = CGUIElement::PropertyChanging(pvProperty, pvNewValue);

	CxStatic* pElement = (CxStatic*)m_pElementWnd;

	// Caption change
	if(pvProperty == &m_strText){
		CString strNewCaption = *(CString *)pvNewValue;
		m_strText = strNewCaption;
		pElement->SetWindowText( m_strText );	
	}

	// Transparent controls
	if(pvProperty == &m_bTransp){
		m_bTransp = *(bool *)pvNewValue;
		pElement->SetTransparent( m_bTransp );
	}

	// Background color change
	if(pvProperty == &m_cBkColor){
		m_cBkColor = *(COLORREF *)pvNewValue;
		pElement->SetBkColor( m_cBkColor );
	}

	// Text change
	if(pvProperty == &m_nHAlignCbo){
		m_nHAlignCbo = *(int *)pvNewValue;
		pElement->SetHAlign((CxStatic::EHAlign) m_nHAlignCbo);
	}
	if(pvProperty == &m_nVAlignCbo){
		m_nVAlignCbo = *(int *)pvNewValue;
		pElement->SetVAlign((CxStatic::EVAlign)m_nVAlignCbo);
	}



	if(pvProperty == &m_cTextColor){
		m_cTextColor = *(COLORREF *)pvNewValue;
		pElement->SetTextColor( m_cTextColor );
	}

	// Image Properties
	if(pvProperty == &m_strImgPath){
		CString strImagepath = *(CString *)pvNewValue;
		pElement->SetBitmap( strImagepath );
		CMisc::GetNameFromPath( strImagepath, m_strImgPath );
		
	}

	// Image transparent color changing
	if(pvProperty == &m_cTranspColor){
		m_cTranspColor = *(COLORREF *)pvNewValue;
		pElement->SetTransColor(m_cTranspColor);
	}

	//AfxMessageBox(m_strImgPath);

	//pElement->UpdateWindow();

	return true;
}


void CGUIStatic::GetProperties(EPropList& PropList)
{
	TRACE( _T("CGUIStatic::GetProperties()\n"));
	
	m_pCxStatic = (CxStatic*)m_pElementWnd;

	// Show Common widgets properties (Control Type, pos and size)
	CGUIElement::GetProperties(PropList);
	
	// Caption
	//m_pCxStatic->GetWindowText(m_strText);
	PropList.AddPropString(this, "Caption", &m_strText, true)->SetComment("");

	PropList.AddPropCheck ( this , "Transparent"  , &m_bTransp )->SetComment("");

	// Background color
	m_cBkColor = m_pCxStatic->GetBkColor();
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

	m_cTextColor = m_pCxStatic->GetTextColor();
	PropList.AddPropColor ( this , "Text color", &m_cTextColor )->SetComment("");
	
	// Image Properties
	PropList.AddPropSeparator(this, "Image");
	PropList.AddPropFile(this, "From File", &m_strImgPath, 
		"Image Files (*.bmp;*.jpg;*.jpeg;*.png;*.ico;*.gif)|*.bmp; *.jpg; *.jpeg; *.png; *.ico; *.gif|All Files (*.*)|*.*||")->SetComment("");
	
	if (m_pCxStatic->HasImage(m_strImgType, m_nImgWidth,m_nImgHeight, m_cTranspColor)){
		
		PropList.AddPropString(this, "Type",   &m_strImgType, true)->SetComment("");
		PropList.AddPropInt   (this ,"Original Width" , &m_nImgWidth)->SetComment("");
		PropList.AddPropInt   (this ,"Original Height", &m_nImgHeight)->SetComment("");
		PropList.AddPropColor ( this ,"Transp color", &m_cTranspColor )->SetComment("");
	}

}


int	CGUIStatic::LoadXML(TiXmlElement* pDataElm)
{
	TiXmlText* pTextElm = NULL;
	TiXmlNode* pNode	= NULL;
	CString strTmp;
	int nTokPos = 0;
	m_pCxStatic = (CxStatic*)m_pElementWnd;

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
			m_pCxStatic->SetWindowText( m_strText );
		}
		else if ( _tcsicmp(pDataElm->Value(), _T("background") ) == 0 ){
			int nColorMode  = _tcstol ( pDataElm->Attribute( _T("FillMode") ), NULL, 10 );
			int cBkLowColor = _tcstol ( pDataElm->Attribute( _T("LowColor") ), NULL, 16 );
			int cBkHiColor  = _tcstol ( pDataElm->Attribute( _T("HiColor") ),  NULL, 16 );
			m_pCxStatic->SetBkColor(cBkLowColor, cBkHiColor, (enum CxCommon::FillMode)nColorMode);
		}
		else if( _tcsicmp(pDataElm->Value(), _T("image"))  == 0){
			CString	strImgType = pDataElm->Attribute("ImgType");
			int nWidth =  _ttoi( pDataElm->Attribute("Width") );
			int nHeight=  _ttoi( pDataElm->Attribute("Height") );
			//COLORREF cTranspColor = ;
			
			
			strTmp = pDataElm->FirstChild()->ToText()->Value();
			CBase64Coding	B64Decoder;
			CByteArray		ByteArray;
			B64Decoder.Decode(strTmp, ByteArray);

			int nImgType = m_pCxStatic->FindImgType( strImgType );
			

			m_pCxStatic->SetBitmap(ByteArray, nImgType);

		}
		
		pDataElm = pDataElm->NextSiblingElement();
	}

	
	return 1;
}






int	CGUIStatic::SaveXML(TiXmlElement *pDataNode)
{
	TiXmlElement*	pSaveXMLRoot = NULL;
	TiXmlElement*	pSaveXMLElement = NULL;
	TiXmlText*		pSaveXMLText	= NULL; 
	CString			strTmp;
	CRect			rect;

	m_pCxStatic = (CxStatic*)m_pElementWnd;
	
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

	pSaveXMLElement = new TiXmlElement( "background" );
	pSaveXMLElement->SetAttribute( _T("FillMode"), 0 );
	strTmp.Format(_T("0x%6.6x"), m_pCxStatic->GetBkColor() );
	pSaveXMLElement->SetAttribute( "LowColor", strTmp );
	strTmp.Format(_T("0x%6.6x"), m_pCxStatic->GetBkColor());
	pSaveXMLElement->SetAttribute( "HiColor", strTmp );
	pSaveXMLRoot->LinkEndChild( pSaveXMLElement );

	int		 nWidth, nHeight;
	CString  strImgType;
	COLORREF rgbTransp = 0xff000000;
	if (m_pCxStatic->HasImage(strImgType, nWidth,nHeight, rgbTransp)){
	

	CByteArray		imgBuffer;
	CBase64Coding	B64Encoder;

	m_pCxStatic->GetImgBuffer( imgBuffer );

	pSaveXMLElement = new TiXmlElement( "Image" );
	strTmp.Format("%s", strImgType );
	pSaveXMLElement->SetAttribute( "ImgType", strTmp );
	strTmp.Format("%d", nWidth );
	pSaveXMLElement->SetAttribute( "Width", strTmp );
	strTmp.Format("%d", nHeight );
	pSaveXMLElement->SetAttribute( "Height", strTmp );

	B64Encoder.Encode(imgBuffer, strTmp);
	pSaveXMLText = new TiXmlText( strTmp );
	pSaveXMLElement->LinkEndChild( pSaveXMLText );
	pSaveXMLRoot->LinkEndChild( pSaveXMLElement );
	}

	return 0;
}