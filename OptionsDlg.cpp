// OptionsDlg.cpp: implementation of the COptionsDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OptionsDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptionsDlg::COptionsDlg()
{
	m_wndGeneral.m_psp.dwFlags &= ~PSH_HASHELP;

	//CTreePropSheet::SetPageIcon();
	AddPage(&m_wndGeneral);

	SetTreeViewMode( TRUE, TRUE, TRUE);
	SetIsResizable( false );
	//SetTreeWidth( 150 );  
	//SetPaneMinimumSizes( 100, 180 );
	//SetMinSize( CSize( 300, 320 ) );
	//SetAutoExpandTree( true );

}

COptionsDlg::~COptionsDlg()
{

}
