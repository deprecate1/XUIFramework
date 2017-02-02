// DynDlgTemplate.cpp: implementation of the CDynDlgTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../resource.h"
#include "DynDlgTemplate.h"



#define ID_DYNBUTTONDATE                32774
#define ID_DYNBUTTONEDITMULTI           32780
#define ID_DYNBUTTONLABEL               32843
#define ID_DYNBUTTONCOMBO               32844
#define ID_DYNBUTTONCHECK               32846
#define ID_DYNBUTTONGROUP               40001
#define ID_DYNBUTTONLEFTALIGN           40003
#define ID_DYNBUTTONTOPALIGN            40005
#define ID_DYNBUTTONBOTTOMALIGN         40006
#define ID_DYNBUTTONMAKESAMEWIDTH       40010
#define ID_DYNBUTTONMAKESAMEHEIGHT      40011
#define ID_DYNBUTTONMAKESAMESIZE        40012
#define ID_DYNBUTTONRIGHTALIGN          40015
#define ID_DYNBUTTONEDIT                40016
#define ID_DYNBUTTONTOGGLEGRID          40017
#define ID_DYNBUTTONPICTURE             40019


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynDlgTemplate::CDynDlgTemplate(HWND hWnd, CXUIFramework* pDynContainer)
{
	m_pDynContainer = pDynContainer;
	m_pDlgRes		= NULL;
	m_strDialogFont = _T("");
	m_wpSize		= 0;
	m_hWnd			= hWnd;
}

CDynDlgTemplate::~CDynDlgTemplate()
{

}



void CDynDlgTemplate::BuildFromTemplate(int nIDD)
{
	if (m_pDynContainer == NULL)
		return;

	// get a handle to the resource for this window
	// and open it
	HRSRC hResource = ::FindResource(AfxGetResourceHandle(),MAKEINTRESOURCE(nIDD),RT_DIALOG);
	HGLOBAL hData	= ::LoadResource(AfxGetResourceHandle(),hResource);

	if (hData != NULL){
		
		
		DLGTEMPLATE dlgTemplate;
		LPBYTE		pDlgResItems;
		LPBYTE		pDlgResFirstByte;
		CString		strCtlText;
		CRect		rectItem;

		m_pDlgRes = (LPBYTE)::LockResource(hData);		
		pDlgResFirstByte = m_pDlgRes;
		memcpy(&dlgTemplate,m_pDlgRes,sizeof(DLGTEMPLATE));

		pDlgResItems = m_pDlgRes + sizeof(DLGTEMPLATE);

		// move past the menu
		SkipOrdinalOrTextField(&pDlgResItems);
		// move past the class
		SkipOrdinalOrTextField(&pDlgResItems);
		// move past the caption
		SkipOrdinalOrTextField(&pDlgResItems);

		// the following will be present ONLY if "DS_SETFONT" style has been
		// specified for the dialog box.
		// 4 - Check if a unique font is specified for this dialog.
		// 5 - Check if a FACE NAME is specified.
		if (DS_SETFONT & dlgTemplate.style){
			// get the point size
			m_wpSize = (WORD)*pDlgResItems;

			// move past the point size field
			pDlgResItems += sizeof(WORD);  

			// "szFontName" contains "DOUBLE-NULL" terminated string. Se we
			// need to advance the pointer TWO UNICODE characters. Since
			// "SkipOrdinalOrText()" only advances past ONE null char, then
			// we need to advance it past the second NULL char.
			m_strDialogFont = "";
			SkipOrdinalOrTextField(&pDlgResItems, &m_strDialogFont);
			// move past the NULL char
			pDlgResItems += sizeof(WCHAR);   
		}

		// go through all the control in the resource
		for (int nLoop = 0; nLoop < dlgTemplate.cdit; nLoop++){
			CGUIElement* pDynControl = NULL;
			DLGITEMTEMPLATE* pdlgItem;
			DLGITEMTEMPLATE dlgItem;
			BYTE	byClassType;
			CString strClassName;

			WORD nExtraOffsetBytes;
			nExtraOffsetBytes = (WORD)(4 - (((WORD)(DWORD)pDlgResItems) & 3)) % 4;
			pDlgResItems += nExtraOffsetBytes;			

			pdlgItem = (DLGITEMTEMPLATE*)pDlgResItems;
			memcpy(&dlgItem,pdlgItem,sizeof(DLGITEMTEMPLATE));
			pDlgResItems = pDlgResItems + sizeof(DLGITEMTEMPLATE);

			if (0xFFFF == *(WORD*)pDlgResItems){
				pDlgResItems += sizeof(WORD);

				switch(byClassType = (BYTE)*pDlgResItems)
				{
				case  CTLTYPE_LISTVIEW : strClassName = _T("SysListView32") ; break;
				case  CTLTYPE_BUTTON   : strClassName = _T("button")   ; break;
				case  CTLTYPE_EDIT     : strClassName = _T("edit")     ; break;
				case  CTLTYPE_STATIC   : strClassName = _T("static")   ; break;
				case  CTLTYPE_LISTBOX  : strClassName = _T("listbox")  ; break;
				case  CTLTYPE_SCROLLBAR: strClassName = _T("scrollbar"); break;
				case  CTLTYPE_COMBOBOX : strClassName = _T("combobox") ; break;
#pragma warning (disable: 4244)
				default                : strClassName = *(WCHAR*)pDlgResItems;
#pragma warning (default: 4244)
					byClassType = 0;
				}

				pDlgResItems += sizeof(WORD);         
			}
			else{
				char pcOut[60];
				WideCharToMultiByte(CP_ACP, 0, (WCHAR*)pDlgResItems, -1, pcOut, sizeof(pcOut), NULL, NULL);
				strClassName = CString(pcOut);
				pDlgResItems += strClassName.GetLength() * sizeof(WCHAR);
				pDlgResItems += sizeof(WORD);         
			}

			strCtlText = "";
			if(0xFFFF != *(WORD*)pDlgResItems)
				strCtlText = (WCHAR*)pDlgResItems;

			// TRACE("%s %s %d\n", strClassName, strCtlText, pdlgItem->id);

			// cope with the up-down controls
			SkipOrdinalOrTextField(&pDlgResItems);
			if (strCtlText == "msctls_updown32")
				SkipOrdinalOrTextField(&pDlgResItems);

			if (strClassName	== "edit"
				|| strClassName == "static"
				|| strClassName == "combobox"
				|| strClassName == "button"){
				BOOL bFound = FALSE;
				pDynControl = m_pDynContainer->GetControl( (int) pdlgItem->id );
				if (pDynControl){
					bFound = TRUE;
				}
			
				if (!bFound){
					rectItem.left	= (int)pdlgItem->x;
					rectItem.top	= (int)pdlgItem->y;
					rectItem.right	= (int)pdlgItem->x + pdlgItem->cx;
					rectItem.bottom = (int)pdlgItem->y + pdlgItem->cy;
					TRACE("rectItem (left=%d, top=%d)\n", rectItem.left, rectItem.top);

					m_pDynContainer->AddControl( strClassName, (int) pdlgItem->id ); 
					// keep a note of the controls original values
					
					pDynControl = m_pDynContainer->GetControl();
					pDynControl->SetRect( rectItem );
					pDynControl->SetOrgRect( rectItem );
				}
				pDynControl = NULL;
			}

			// Move past the extra byte
			pDlgResItems += sizeof(WORD);
		}
		
		UnlockResource(hData);
		FreeResource(hData);
	}
}


void CDynDlgTemplate::MapRectDialog(CRect& rect, int &x, int &y, int &cx, int &cy)
{
		// maps pixels to dialog units

		CRect r = CRect(0,0,4,8);
		::MapDialogRect(this->m_hWnd,r);
		int pixelX = MulDiv( 201, r.right, 4 );
		int dlgx = MulDiv(302,4,r.right);

		x = MulDiv(rect.left,4,r.right);
		cx = MulDiv(rect.right,4,r.right) - x; // this is the width 

		y = MulDiv(rect.top,8,r.bottom);
		cy = MulDiv(rect.bottom,8,r.bottom) - y; // this is the height
}


int CDynDlgTemplate::SkipOrdinalOrTextField(LPBYTE* pplDlgResource, CString* pstrTextValue)
{
		// Skips a word or char in the resource file

		//ASSERT_VALID(this);
		ASSERT(pplDlgResource);          
		int nCount = 0;
		CString strText("");

		// Ordinal number start with '0xFFFF'
		if (0xFFFF == (WORD)**pplDlgResource)
		{
			*pplDlgResource += sizeof(WORD);
			nCount = sizeof(WORD);
		}
		else
		{
			while (**pplDlgResource)
			{
#if _MFC_VER < 0x0700
				strText = strText + CString(**pplDlgResource);
#else
				strText = strText + CString((WCHAR)**pplDlgResource);
#endif
				*pplDlgResource += sizeof(WCHAR);
				nCount += sizeof(WCHAR);
			}
			// Move past the null character
			*pplDlgResource += sizeof(WCHAR); 
			nCount += sizeof(WCHAR);
		}
		if (pstrTextValue != NULL)
			*pstrTextValue = strText;
		return nCount;
	}