// GUIElement.cpp: implementation of the CGUIElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../GuiBaker.h"
#include "GUIElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUIElement::CGUIElement()
{
	Initialize();
	m_strName		 = "ID_ELEMENT";
	m_strElementType = "Element";

	m_nHighestID	= 0;
	m_bRootWnd		= FALSE;
	m_pRootElement	= NULL;
	m_pRootWnd		= NULL;
	m_pElementWnd	= NULL;
	m_DefaultSize	= CSize(100, 50);
	m_rectElement	= CRect(0,0,0,0);
	m_rectOrgElement= CRect(0,0,0,0);
	m_bIsMoveable	= TRUE;
	m_bHasImage		= false;
	m_nImgWidth		= 0;
	m_nImgHeight	= 0;
	m_strImgType	= _T("");

	
}

CGUIElement::~CGUIElement()
{
	if (m_pElementWnd){
		TRACE("Destroying control id=%d\n", GetID() );
		SAFEDEL(m_pElementWnd);
	}
}




void CGUIElement::Initialize()
{

}

int CGUIElement::Create(CWnd *pRootWnd, CRect WidgetRect)
{
	if(pRootWnd == NULL)
		return 0;
	

	m_pRootWnd = pRootWnd;
	
	// If no WidgetRec is given and m_rectElement is zero - give default size and pos
	if (WidgetRect.left == -1 && m_rectElement.Width() == 0){

		CPoint	orgPos(0,0); 
		CSize	size = m_DefaultSize;
		
		orgPos	= GetRandomPoint();
		m_rectElement.left	= orgPos.x;
		m_rectElement.top	= orgPos.y;
		m_rectElement.right = orgPos.x + m_DefaultSize.cx;
		m_rectElement.bottom= orgPos.y + m_DefaultSize.cy;
	}

	if (WidgetRect.left != -1){
		CopyRect( WidgetRect );
	}

	return 1;
}


void CGUIElement::OnDraw(CDC* pDC)
{

}


bool CGUIElement::PropertyChanging( const void* pvProperty , void* pvNewValue )
{

	return true;
}

void CGUIElement::GetProperties(EPropList& PropList)
{
	TRACE( _T("CGUIElement::GetProperties()\n"));

	PropList.AddPropSeparator(this, "Widget");
	PropList.AddPropString(this, "Type",  &m_strElementType, false)->SetComment("Control Type");
	
	// Windows ID
	//m_strPropTmp.Format( _T("%d"), GetID() );
	PropList.AddPropInt   ( this , "ID" , &m_nID)->SetComment("Windows Internal ID");
	
	// Show Parent Window(CView or Cwnd like Frame or dialog)
	CRuntimeClass* prt = m_pRootWnd->GetRuntimeClass();
	m_strPropTmp.Format( _T("%s=0x%x"), prt->m_lpszClassName, m_pRootWnd );
	PropList.AddPropString(this, "Parent Window",  &m_strPropTmp, false)->SetComment("Parent Window");
	
	// Show Name
	PropList.AddPropString(this, "Name", &m_strName, true)->SetComment("");

	// Show Position
	m_strPropPos.Format( _T("%d,%d"), m_rectElement.left, m_rectElement.top  );
	PropList.AddPropString(this, "Pos", &m_strPropPos, true)->SetComment("");

	// Show Size
	m_strPropSize.Format( _T("%d,%d"), m_rectElement.Width(), m_rectElement.Height()  );
	PropList.AddPropString(this, "Size", &m_strPropSize, true)->SetComment("");

}



void CGUIElement::SetNotMoveable(BOOL bFlag)
{
	m_bIsMoveable = bFlag;
}

BOOL CGUIElement::IsMoveable()
{
	return m_bIsMoveable;
}


CPoint CGUIElement::GetRandomPoint()
{
	CPoint point(0,0);

	// Get parent dimensions
	CRect rectParent;
	m_pRootWnd->GetClientRect(&rectParent);

	
	point.x = random_range(0, rectParent.Width() );
	point.y = random_range(0, rectParent.Height() );

	TRACE(_T("GetRandomPoint(){Max Width = %d, Max Height=%d, x=%d y=%d }\n"), 
		rectParent.Width(), 
		rectParent.Height(),
		point.x,
		point.y);

	return point;
}



CWnd* CGUIElement::GetWnd()
{
	return m_pElementWnd;
}


void CGUIElement::SetPos(CPoint pos)
{
	CSize size;
	CRect rect;

	size.cx = m_rectElement.Width();
	size.cy = m_rectElement.Height();
	m_rectElement.left	= pos.x;
	m_rectElement.top	= pos.y;
	m_rectElement.right	= pos.x + size.cx;
	m_rectElement.bottom= pos.y + size.cy;

	if (m_pElementWnd){
		MoveWindow( m_pElementWnd->m_hWnd,
			m_rectElement.left,
			m_rectElement.top,
			m_rectElement.Width(),
			m_rectElement.Height(),
			TRUE);
	}
}

void CGUIElement::SetSize(CSize size)
{
	m_rectElement.right	 = m_rectElement.left + size.cx;
	m_rectElement.bottom = m_rectElement.top + size.cy;

	if (m_pElementWnd){
		MoveWindow( m_pElementWnd->m_hWnd,
			m_rectElement.left,
			m_rectElement.top,
			m_rectElement.Width(),
			m_rectElement.Height(),
			TRUE);
	}
}

void CGUIElement::SetRect(const CRect& rect)
{
	m_rectElement = rect;
}

void CGUIElement::SetOrgRect(const CRect& rect)
{
	m_rectOrgElement = rect;
}

CRect CGUIElement::GetRect()
{

	return m_rectElement;
}


void CGUIElement::CopyRect(LPRECT rectElement)
{
	m_rectElement.CopyRect(rectElement);
}


int CGUIElement::GetID()
{
	return m_nID;
}

void CGUIElement::SetID(ULONG nID,BOOL bSetName)
{
	//if (m_pElementWnd == NULL)
	//	return;

	m_pElementWnd->SetDlgCtrlID(nID);
	m_nID = nID;

	if (bSetName)
		SetName();

	if (nID > (ULONG)m_nHighestID)
		m_nHighestID = nID;
}

int CGUIElement::GetHighestID()
{
	return m_nHighestID;
}


void CGUIElement::SetName()
{
	CString strTmp;

	strTmp.Format( _T("%s_%d"), m_strName, m_nID  );
	m_strName = strTmp;
}

void CGUIElement::SetName( CString strName )
{
	m_strName = strName;
}



int	CGUIElement::LoadXML(TiXmlElement* pDataNode)
{

	return 0;
}



int	CGUIElement::SaveXML(TiXmlElement *pDataNode)
{

	TiXmlElement* pNode = new TiXmlElement( "object" );
	pNode->SetAttribute( _T("class"), _T("sdqsdqsd") );
	pNode->SetAttribute( "name", _T("qsdqsdqsdqds") );
	pDataNode->LinkEndChild( pNode );
	
	
	
	
	
	//pCurElement->LinkEndChild( pDataNode->ToElement() );
	
	return 0;
}




/* static */
int CGUIElement::random_range(int lowest_number, int highest_number)
{
	int range = highest_number - lowest_number + 1;
	return lowest_number + int(range * rand()/(RAND_MAX + 1.0));
}
