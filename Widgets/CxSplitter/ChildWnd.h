#if !defined(CHILDWND_H)
#define CHILDWND_H

class CChildWnd : public CWnd
{
public:
	CChildWnd();
	virtual ~CChildWnd();

protected:
	//{{AFX_MSG(CChildWnd)
	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 
