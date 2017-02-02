#pragma once

#include "../PropertyLib\EPropCtrl.h"
//#include "ChildFrm.h"

// CSettingsDlg dialog
class CSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingsDlg();

	EPropCtrl m_PropCtrl;
	
	IPropertyHost* m_pCurrentHost;
	
	void SetPropPointer(IPropertyHost *pHost);
// Dialog Data
	enum { IDD = IDD_SETTINGS };

protected:


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int CY);

	DECLARE_MESSAGE_MAP()
};
