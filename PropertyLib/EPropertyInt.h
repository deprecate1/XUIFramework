// EPropertyInt.h: interface for the EPropertyInt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EPROPERTYINT_H__8A232506_B2CC_45B7_A136_F167F6A1B89D__INCLUDED_)
#define AFX_EPROPERTYINT_H__8A232506_B2CC_45B7_A136_F167F6A1B89D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EIconTextButtonProperty.h"

class EPropertyInt : public EIconTextButtonProperty
{

protected:

	int m_nByteWidth;
	int m_bSigned;

	CString m_sUnit;

public:

	EPropertyInt( IPropertyHost* pHost , const CString& sName , void* pProperty , const CString& sUnit="" , bool bEnabled=true );
	virtual ~EPropertyInt();

	//
	// EProperty
	//
	virtual bool GetSortValueDouble( double& dValue );
	virtual bool OnPropApply();

	//
	// icontextbutton overrides
	//
	virtual CString GetTextValue();
	virtual bool HasEdit();

protected:

	int GetIntegerValue();	//depending on signed flag and bytewith, this returns the proper value

public:

	EPropertyInt* SetStyle( UINT nFormatFlags=EIconTextButtonProperty::DEFAULT );
	EPropertyInt* SetType( int nByteWidth , bool bSigned );

};

#endif // !defined(AFX_EPROPERTYINT_H__8A232506_B2CC_45B7_A136_F167F6A1B89D__INCLUDED_)
