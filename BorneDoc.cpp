// BorneDoc.cpp : implementation of the CBorneDoc class
//

#include "stdafx.h"
#include "GuiBaker.h"

#include "BorneDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBorneDoc

IMPLEMENT_DYNCREATE(CBorneDoc, CDocument)

BEGIN_MESSAGE_MAP(CBorneDoc, CDocument)
	//{{AFX_MSG_MAP(CBorneDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBorneDoc construction/destruction

CBorneDoc::CBorneDoc()
{
	// TODO: add one-time construction code here

}

CBorneDoc::~CBorneDoc()
{
}

BOOL CBorneDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBorneDoc serialization

void CBorneDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBorneDoc diagnostics

#ifdef _DEBUG
void CBorneDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBorneDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBorneDoc commands
