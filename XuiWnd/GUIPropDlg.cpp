

#include "stdafx.h"
#include "../GuiBaker.h"
#include "GUIPropDlg.h"
#include "../MainFrm.h"

// CSettingsDlg dialog

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialog)
CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
{
	m_pCurrentHost = NULL;
}

CSettingsDlg::~CSettingsDlg()
{

}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CSettingsDlg::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return FALSE;

	m_PropCtrl.Create(this, IDC_PROP);
	return TRUE;
}

void CSettingsDlg::SetPropPointer(IPropertyHost *pHost)
{
	if(pHost !=NULL){
		m_pCurrentHost = pHost;
		m_PropCtrl.SetPropertyHost(pHost);
	}
	else
	{
		m_pCurrentHost = NULL;
		m_PropCtrl.SetPropertyChangeListener(NULL);
		m_PropCtrl.SetPropertyHost(NULL);
	}
}

void CSettingsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}

