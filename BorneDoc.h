// BorneDoc.h : interface of the CBorneDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BORNEDOC_H__E98F3A01_03CF_4A56_BE41_A1008A812216__INCLUDED_)
#define AFX_BORNEDOC_H__E98F3A01_03CF_4A56_BE41_A1008A812216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBorneDoc : public CDocument
{
protected: // create from serialization only
	CBorneDoc();
	DECLARE_DYNCREATE(CBorneDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorneDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBorneDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBorneDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORNEDOC_H__E98F3A01_03CF_4A56_BE41_A1008A812216__INCLUDED_)
