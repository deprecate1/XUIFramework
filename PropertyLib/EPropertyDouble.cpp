
#include "stdafx.h"
#include "IPropertyHost.h"
#include "EPropListCtrl.h"
#include "EPropertyDouble.h"
#include "EPropWndEdit.h"
#include "math.h"

bool EPropertyDouble::HasEdit()
{
	return true;
}

EPropertyDouble::EPropertyDouble( IPropertyHost* pHost , const CString& sName , double* pProperty , const CString& sUnit , double dMinAllowed , double dMaxAllowed , bool bEnabled ) : EIconTextButtonProperty( pHost , sName , pProperty , bEnabled )
{
	m_dMin         = dMinAllowed;
	m_dMax         = dMaxAllowed;
	m_dScale       = 1.0;
	m_sFixedUnit   = sUnit;
	m_pUnitSymbol  = &m_sFixedUnit;
	m_pScaleMul    = NULL;
	m_pScaleDiv    = NULL;
	m_nNumDecimals = -1;
	m_pUnitScaleHost = NULL;
}

EPropertyDouble::~EPropertyDouble()
{
}

double EPropertyDouble::GetScale()
{
	double dScale = m_dScale;

	if( m_pUnitScaleHost )
	{
		CString s;
		dScale = m_pUnitScaleHost->GetUnitScale(s);
	}
	else
	{
		if( m_pScaleMul != NULL )
		{
			dScale *= (*m_pScaleMul);
		}

		if( m_pScaleDiv != NULL )
		{
			dScale /= (*m_pScaleDiv);
		}
	}

	return dScale;
}

CString EPropertyDouble::GetTextValue()
{
	double d = *(double*)m_pProperty;

	CString s;
	CString sUnit;

	CString sFormat;

	if( ( m_nFormatFlags&EIconTextButtonProperty::SCIENTIFIC) == EIconTextButtonProperty::SCIENTIFIC )
	{
		if( m_nNumDecimals!=-1 )
			sFormat.Format( "%%1.%ie", m_nNumDecimals );
		else
			sFormat.Format( "%e" );

		s.Format( sFormat , d * GetScale() );
	}
	else
	{
		if( m_nNumDecimals!=-1 )
			sFormat.Format( "%%.%ilf" , m_nNumDecimals );
		else
			sFormat = "%lf";

		s.Format( sFormat , d * GetScale() );

		bool bHasComma = (s.Find(',')>0) || (s.Find('.')>0);
		
		if( bHasComma )
		{
			s.TrimRight('0');
			s.TrimRight('.');
			s.TrimRight(',');
		}
		
		if( ( m_nFormatFlags&EIconTextButtonProperty::THOUSANDS) == EIconTextButtonProperty::THOUSANDS )
		{
			s = FormatThousands(s);
		}
	}
	
	if( m_pUnitScaleHost )
	{
		m_pUnitScaleHost->GetUnitScale(sUnit);
	}
	else
	{
		if( m_pUnitSymbol != NULL )
		{
			sUnit = *m_pUnitSymbol;
		}
	}

	if( sUnit.GetLength() > 0 )
	{
		s += " ";
		s += sUnit;
	}

	return s;
}

bool EPropertyDouble::OnPropApply()
{
	ASSERT( m_bSelected == true );
	ASSERT( m_pEdit     != NULL );
	ASSERT( IsEnabled() == true );

	bool bPropertyChanged = false;

	double d1;
	double d2;
	double dGuiValue;

	ASSERT( m_bSelected == true );

	ASSERT( m_pEdit != NULL );

	CString s;
	m_pEdit->GetWindowText(s);

	if( s != m_sInitialValueText )				//not the same
	{
		double dOldGuiValue = *(double*)m_pProperty * GetScale();

		bool bValid = true;

		s.Remove(' ');

		if( sscanf(s,"%lf/%lf",&d1,&d2)==2 )
		{
			dGuiValue = d1/d2;
		}
		else if( sscanf(s,"%lf*%lf",&d1,&d2)==2 )
		{
			dGuiValue = d1*d2;
		}
		else if( sscanf(s,"%lf+%lf",&d1,&d2)==2 )
		{
			dGuiValue = d1+d2;
		}
		else if( sscanf(s,"%lf-%lf",&d1,&d2)==2 )
		{
			dGuiValue = d1-d2;
		}
		else if( sscanf(s,"%lf",&d1)==1 )			//normal situation, entering a new number
		{
			dGuiValue = d1;
		}
		else if( sscanf(s,"/%lf",&d1)==1 )
		{
			dGuiValue = dOldGuiValue/d1;
		}
		else if( sscanf(s,"*%lf",&d1)==1 )
		{
			dGuiValue = dOldGuiValue*d1;
		}
		else if( sscanf(s,"+%lf",&d1)==1 )
		{
			dGuiValue = dOldGuiValue+d1;
		}
		else if( sscanf(s,"-%lf",&d1)==1 )
		{
			dGuiValue = dOldGuiValue-d1;
		}
		else
		{
			bValid = false;
		}

		double dVariableValue = dGuiValue / GetScale();		//gui -> var

		if( bValid )
		{
			if( dVariableValue != *(double*)m_pProperty )	//not the same
			{
				if( (m_dMin==0 && m_dMax==0) || (m_dMin<=dVariableValue && dVariableValue<=m_dMax) )	//within range?
				{
					if( m_pHost->PropertyChanging(m_pProperty,&dVariableValue) )		//true if ok to change property
					{
						*(double*)m_pProperty = dVariableValue;
						bPropertyChanged = true;
					}
				}
			}
		}
	}

	return bPropertyChanged;
}

EPropertyDouble* EPropertyDouble::SetStyle( UINT nFormatFlags , int nNumDecimals )
{
	m_nFormatFlags = nFormatFlags;
	m_nNumDecimals = nNumDecimals;
	return this;
}

EPropertyDouble* EPropertyDouble::SetScale( double dScale )
{
	m_dScale    = dScale;
	return this;
}

EPropertyDouble* EPropertyDouble::SetUnit( const CString* pUnitSymbol )
{
	m_pUnitSymbol = pUnitSymbol;
	return this;
}

EPropertyDouble* EPropertyDouble::SetScale( const double* pMultiply , const double* pDivide )
{
	m_pScaleMul = pMultiply;
	m_pScaleDiv = pDivide;
	return this;
}

EPropertyDouble* EPropertyDouble::SetUnit( UnitScaleHost* pUnitScaleHost )
{
	m_pUnitScaleHost = pUnitScaleHost;
	return this;
}
