
#include "../resource.h"

#ifndef _DYNCONTROLBAR_
#define _DYNCONTROLBAR_

class CDynControlBar : public CToolBar
{
// Construction
public:
	CDynControlBar();
	UINT m_nIDClipFormat;

	class CDynDropSource : public COleDropSource
	{
	public:
		enum CursorType
		{
			EDIT,
			LABEL,
			GROUP,
			COMBO,
			CHECK,
			DATE,
			RADIO
		} nCursorType;

		SCODE GiveFeedback(DROPEFFECT dropEffect)
		{
			HCURSOR hCursor;
			if (nCursorType == EDIT)
				hCursor = AfxGetApp()->LoadCursor(IDC_EDITCURSOR);
			if (nCursorType == LABEL)
				hCursor = AfxGetApp()->LoadCursor(IDC_LABELCURSOR);
			if (nCursorType == GROUP)
				hCursor = AfxGetApp()->LoadCursor(IDC_GROUPCURSOR);
			if (nCursorType == COMBO)
				hCursor = AfxGetApp()->LoadCursor(IDC_COMBOCURSOR);
			if (nCursorType == CHECK)
				hCursor = AfxGetApp()->LoadCursor(IDC_CHECKCURSOR);
			if (nCursorType == DATE)
				hCursor = AfxGetApp()->LoadCursor(IDC_DATECURSOR);
			if (nCursorType == RADIO)
				hCursor = AfxGetApp()->LoadCursor(IDC_RADIOCURSOR);
			SetCursor(hCursor);
			return S_OK;
		} 
	};

	CDynDropSource dynDropSource;

// Attributes
public:
	BOOL m_bMakingVisible;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynControlBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDynControlBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDynControlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	//}}AFX_MSG
	afx_msg void BeginDrag(NMHDR * pNotifyStruct, LRESULT* result);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
