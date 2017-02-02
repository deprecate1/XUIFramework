// OptionsDlg.h: interface for the COptionsDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONSDLG_H__1FDA9E8F_FF4D_4E7E_9019_F813A6B07EED__INCLUDED_)
#define AFX_OPTIONSDLG_H__1FDA9E8F_FF4D_4E7E_9019_F813A6B07EED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "TreePropSheetEx/TreePropSheet.h"
#include "TreePropSheetEx/TreePropSheetEx.h"
#include "TreePropSheetEx/TreePropSheetOffice2003.h"
#include "TreePropSheetEx/ResizableSheet.h"
#include "PPgGeneral.h"

using namespace TreePropSheet;

class COptionsDlg : public CTreePropSheetEx  
{
public:
	COptionsDlg();
	virtual ~COptionsDlg();

	CPPgGeneral		m_wndGeneral;

};

#endif // !defined(AFX_OPTIONSDLG_H__1FDA9E8F_FF4D_4E7E_9019_F813A6B07EED__INCLUDED_)
