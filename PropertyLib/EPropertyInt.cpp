// EPropertyInt.cpp: implementation of the EPropertyInt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPropertyHost.h"
#include "EPropWndEdit.h"
#include "EPropertyInt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropertyInt::EPropertyInt( IPropertyHost* pHost , const CString& sName , void* pProperty , const CString& sUnit , bool bEnabled ) : EIconTextButtonProperty( pHost , sName , pProperty , bEnabled )
{
	m_sUnit = sUnit;
	m_nByteWidth = 4;
	m_bSigned    = true;
}

EPropertyInt::~EPropertyInt()
{
}

bool EPropertyInt::HasEdit()
{
	return true;
}

int EPropertyInt::GetIntegerValue()
{
	int i = 0;

	switch( m_nByteWidth )
	{
	case 1:
		i = *( (char*) m_pProperty );
		break;
	case 2:
		i = *( (short*)m_pProperty );
		break;
	case 4:
		i = *( (int*)  m_pProperty );
		break;
	default:
		ASSERT(1);
	}

	return i;
}

CString EPropertyInt::GetTextValue()
{
	int i = GetIntegerValue();

	CString s;

	if( m_bSigned )
	{
		s.Format("%d" , i );
	}
	else
	{
		s.Format("%u" , i );
	}

	if( ( m_nFormatFlags&EIconTextButtonProperty::THOUSANDS) == EIconTextButtonProperty::THOUSANDS )
	{
		s = FormatThousands(s);
	}

	if( m_sUnit.GetLength() > 0 )
	{
		s += ' ';
		s += m_sUnit;
	}

	return s;
}

bool EPropertyInt::OnPropApply()
{
	ASSERT( m_bSelected == true );
	ASSERT( m_pEdit     != NULL );
	ASSERT( IsEnabled() == true );

	bool bPropertyChanged = false;
	int n;

	CString s;
	m_pEdit->GetWindowText(s);

	if( sscanf(s, _T("%d"),&n) == 1 )
	{
		if( n != *((int*)m_pProperty) )
		{
			if( m_pHost->PropertyChanging(m_pProperty,&n) )
			{
				*((int*)m_pProperty) = n;
				bPropertyChanged = true;
			}
		}
	}

	return bPropertyChanged;
}

EPropertyInt* EPropertyInt::SetType( int nByteWidth , bool bSigned )
{
	m_nByteWidth = nByteWidth;
	m_bSigned    = bSigned;

	ASSERT( nByteWidth==1 || nByteWidth==2 || nByteWidth==4 );
	
	return this;
}

EPropertyInt* EPropertyInt::SetStyle( UINT nFormatFlags )
{
	m_nFormatFlags = nFormatFlags;
	return this;
}

bool EPropertyInt::GetSortValueDouble( double& dValue )
{
	dValue = GetIntegerValue();
	return true;
}
