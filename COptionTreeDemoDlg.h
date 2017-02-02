#if !defined(AFX_COPTIONTREEDEMODLG_H__244E5C67_47F0_4263_844D_26B88306B113__INCLUDED_)
#define AFX_COPTIONTREEDEMODLG_H__244E5C67_47F0_4263_844D_26B88306B113__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Added Headers
#include "COptionTree/OptionTree.h"
#include "cxstatic/cxstatic.h"
#include "CResizeDlg/ResizeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CCOptionTreeDemoDlg dialog

class CCOptionTreeDemoDlg : public CResizeDlg
{
// Construction
public:
	CCOptionTreeDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCOptionTreeDemoDlg)
	enum { IDD = IDD_COPTIONTREEDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCOptionTreeDemoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnApplyFont(LPARAM lParam);
	LRESULT WM_ApplyButton(WPARAM wParam, LPARAM lParam);
	HICON m_hIcon;
	COptionTree m_otTree;
	UINT m_uApplyFontID;
	// Generated message map functions
	//{{AFX_MSG(CCOptionTreeDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnTreeItemChanged(NMHDR* pNotifyStruct, LRESULT* plResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPTIONTREEDEMODLG_H__244E5C67_47F0_4263_844D_26B88306B113__INCLUDED_)
