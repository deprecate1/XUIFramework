// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "wfc_validate.h"


//#include <afxsock.h>		// MFC socket extensions
#include <afxole.h>
#include <afxdb.h>
#include <afx.h>
#include <afxmt.h>



// The STL classes we use.
#pragma warning(disable:4786)
#include <vector>
#include <map>
#include <set>
#include <list>
#include <deque>




#define round(a)			( int ) ( a + .5 )
#define SAFEDEL(x)			{if(x != NULL) {delete x; x = NULL;} }
#define SAFEDEL_ARRAY(x)	{if(x !=NULL) {delete[] x; x = NULL;} }


#include "CStringEx.h"
#include "Log.h"
#include "Misc.h"
#include "XuiScreen.h"
#include "Settings.h"
#include "wfc_validate.h"
#include "CBase64Coding.h"
#include "tinyxml.h"

/*
WARNING :
Make sure that message users you define here are not already used in :
DynScreen.h
*/

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
