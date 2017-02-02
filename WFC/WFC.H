/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** Copyright, 1995-2003, Samuel R. Blackburn
**
** "You can get credit for something or get it done, but not both."
** Dr. Richard Garwin
**
** BSD License follows.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** Redistributions of source code must retain the above copyright notice,
** this list of conditions and the following disclaimer. Redistributions
** in binary form must reproduce the above copyright notice, this list
** of conditions and the following disclaimer in the documentation and/or
** other materials provided with the distribution. Neither the name of
** the WFC nor the names of its contributors may be used to endorse or
** promote products derived from this software without specific prior
** written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** $Workfile: wfc.h $
** $Revision: 76 $
** $Modtime: 1/05/02 7:14a $
*/

#if ! defined( WIN32_FOUNDATION_CLASSES )

#define WIN32_FOUNDATION_CLASSES

#define WFC_RELEASE_NUMBER (73)
#pragma message( "WFC Release 73." )
//#pragma message( "Patch 2." )

#if ! defined( ONE_KILOBYTE )
#define ONE_KILOBYTE (1024)
#endif // ONE_KILOBYTE

#if ! defined( ONE_MEGABYTE )
#define ONE_MEGABYTE (1048576)
#endif // ONE_MEGABYTE

#if ! defined( ONE_GIGABYTE )
#define ONE_GIGABYTE (1073741824)
#endif // ONE_GIGABYTE

#if ! defined( ONE_TERABYTE )
#define ONE_TERABYTE (1099511627776I64)
#endif // ONE_TERABYTE

#if ! defined( ONE_PETABYTE )
#define ONE_PETABYTE (1125899906842624I64)
#endif // ONE_PETABYTE

#if ! defined( ONE_EXABYTE )
#define ONE_EXABYTE (1152921504606846976I64)
#endif // ONE_EXABYTE

#if ! defined( NUMBER_OF_FILETIME_TICKS_IN_ONE_SECOND )
#define NUMBER_OF_FILETIME_TICKS_IN_ONE_SECOND (10000000)
#endif // NUMBER_OF_FILETIME_TICKS_IN_ONE_SECOND

#if ( _MSC_VER > 1000 )
#pragma once
#endif // _MSV_VER

#if defined( UNICODE )
#if ! defined( _UNICODE )
#define _UNICODE
#endif // _UNICODE
#endif // UNICODE

#if defined( _UNICODE )
#if ! defined( UNICODE )
#define UNICODE
#endif // UNICODE
#endif // _UNICODE

#if ( WINVER < 0x401 )
#pragma message( "WARNING! You are compiling for a version of NT before 4.0, you may have problems in the RAS stuff." )
#pragma message( "You will probably have problems in the RAS stuff." )
#pragma message( "To get rid of this warning, add WINVER=0x401 to the Preprocessor definitions in the project settings." )
#else
#if ! defined( _WIN32_WINNT )
#define _WIN32_WINNT WINVER
#endif // _WIN32_WINNT
#endif // WINVER

#if ( WINVER >= 0x0401 ) && ! defined( _WIN32_WINNT )
#pragma message( "Enabling TryEnterCriticalSection compilation." )
#define _WIN32_WINNT 0x0400
#elif ! defined( _WIN32_WINNT ) || ( _WIN32_WINNT < 0x400 )
#pragma message( "Warning! TryEnterCriticalSection will not be compiled. #define _WIN32_WINNT to be 0x400 or greater before including wfc.h." )
#endif

/*
** Need to define NO_ANSI_ONLY (an undocumented "feature", someone in Redmond let the
** children play in the header files again...)
*/

#define NO_ANSIUNI_ONLY

/*
** Yet another undocumented feature we gotta worry about
*/

#if defined( WIN32_LEAN_AND_MEAN )
#undef WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

/*
** Need to un-define VC_EXTRALEAN, another undocumented feature...
*/

#if defined( VC_EXTRALEAN )
#undef VC_EXTRALEAN
#endif // _VC_EXTRALEAN

// _MSC_VER == 1300 on Visual Studio 7.0
#if defined( _DEBUG ) && ( _MSC_VER < 1300 )
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG

#if ! defined( WFC_DEPRECATED )
#if ! defined( _WIN64 ) && ( _MSC_VER >= 1300 )
#define WFC_DEPRECATED __declspec(deprecated)
#else // _WIN64
#define WFC_DEPRECATED
#endif // _WIN64
#endif // WFC_DEPRECATED

#include "wfc_exceptions.h"

#if ! defined( _WIN32_WINNT )
#define _WIN32_WINNT 0x0500
#endif

#if defined( WFC_STL )
// We are building an MFC-free version of the library

#if ! defined( WFC_USE_SMALL_SIZES )
// 64-bit friendly

#if ! defined( CFILE_LENGTH )
#define CFILE_LENGTH ULONGLONG
#endif

#if ! defined( CFILE_POSITION )
#define CFILE_POSITION ULONGLONG
#endif

#if ! defined( CFILE_SEEK_OFFSET )
#define CFILE_SEEK_OFFSET LONGLONG
#endif

#if ! defined( CFILE_HFILE )
#define CFILE_HFILE HANDLE
#endif

#else // WFC_USE_SMALL_SIZES

// 32-bit friendly

#if ! defined( CFILE_LENGTH )
#define CFILE_LENGTH DWORD
#endif

#if ! defined( CFILE_POSITION )
#define CFILE_POSITION DWORD
#endif

#if ! defined( CFILE_SEEK_OFFSET )
#define CFILE_SEEK_OFFSET long
#endif

#if ! defined( CFILE_HFILE )
#define CFILE_HFILE UINT
#endif

#endif // WFC_USE_SMALL_SIZES

// The STL classes generate a horrendous number of warnings
#pragma warning( push, 3 )

#define WFC_NO_DUMPING
#define WFC_NO_SERIALIZATION

#if ! defined( DIMENSION_OF )
#define DIMENSION_OF( argument ) ( sizeof( argument ) / sizeof( *( argument ) ) )
#endif

#include "Mfc2Stl.h"

#else

// MFC Build, we need to include this here so wfc_linker_setup will
// do the right thing (i.e. set the _MFC_VER constant). 

#if ! defined( _AFX )
#include <afxver_.h>
#endif // _AFX

#endif // WFC_STL

/*
** Now setup the linker, we must include our .lib before the
** Microsoft libraries in order to avoid LNK2005 errors
*/

#if defined( _MSC_VER ) && ! defined( WFC_NOFORCE_LIBS )
#include "wfc_linker_setup.h"
#endif // WFC_NOFORCE_LIBS

#if defined( WFC_STL )

#include <process.h>
#include <time.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h> // for GCC isdigit and friends
#include <tchar.h>

#if ! defined( __MINGW32__ )
// 2001-09-15
// Putting crtdbg.h here (outside of _DEBUG) means _ASSERTE macros will compile

// 2001-03-22
// Thanks go to C.Y. Liu (inete32@panasonic.com.tw) for finding out how
// to prevent linker errors here.

#define _MFC_OVERRIDES_NEW
#include <crtdbg.h>
#endif // __MINGW32__

#if defined( _DEBUG ) && ! defined( __MINGW32__ )

inline void * __cdecl operator new( size_t number_of_bytes, LPCSTR filename, int line_number )
{
   return ::operator new( number_of_bytes, _NORMAL_BLOCK, filename, line_number );
}

inline void __cdecl operator delete( void * address, const char *, int )
{
   ::operator delete( address );
}

#define WFC_DUMP_MEMORY_LEAKS_AT_PROGRAM_EXIT() _CrtSetDbgFlag( ( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) | _CRT_LEAK_CHECK_DF ) )

#else // _DEBUG

#define WFC_DUMP_MEMORY_LEAKS_AT_PROGRAM_EXIT()

#endif // _DEBUG

#else //  defined( WFC_STL )

#define WFC_DUMP_MEMORY_LEAKS_AT_PROGRAM_EXIT()

/*
** Include all the needed MFC stuff
*/

#include <afx.h>
#include <afxwin.h>
#include <afxcoll.h>
#include <afxmt.h>
#include <afxdisp.h> // For COleDateTime

// Thanks go to COLIN N EBERHARDT <phycne@phys-irc.novell.leeds.ac.uk>
// for finding a bug here (I had a trailing semicolon)

#if ( _MSC_VER < 1020 )
#pragma message( "WFC was designed to be compiled with Visual C++ 4.2 or later, some classes won't be compiled" )
#else // _MSC_VER < 1020
#include <afxinet.h>
#endif // _MSC_VER < 1020

#endif // WFC_STL

#if ! defined( DIMENSION_OF )
#define DIMENSION_OF( argument ) ( sizeof( argument ) / sizeof( *( argument ) ) )
#endif

// new for 52
// The children at Microsoft screwed up CFile...
#if ( _MFC_VER < 0x0700 )

#if ! defined( CFILE_LENGTH )
#define CFILE_LENGTH DWORD
#endif

#if ! defined( CFILE_POSITION )
#define CFILE_POSITION DWORD
#endif

#if ! defined( CFILE_SEEK_OFFSET )
#define CFILE_SEEK_OFFSET long
#endif

#if ! defined( CFILE_HFILE )
#define CFILE_HFILE UINT
#endif

#else // _MFC_VER < 0x0700

#if ! defined( CFILE_LENGTH )
#define CFILE_LENGTH ULONGLONG
#endif

#if ! defined( CFILE_POSITION )
#define CFILE_POSITION ULONGLONG
#endif

#if ! defined( CFILE_SEEK_OFFSET )
#define CFILE_SEEK_OFFSET LONGLONG
#endif

#if ! defined( CFILE_HFILE )
#define CFILE_HFILE HANDLE
#endif

#endif // // _MFC_VER < 0x0700

#if defined( _DEBUG ) && defined( _INC_CRTDBG )
#define WFC_REPORT_MEMORY_LEAKS() _CrtSetDbgFlag( _CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) )
#else
#define WFC_REPORT_MEMORY_LEAKS()
#endif

#include "wfc_validate.h"

/*
** Include all the NT stuff
*/

#include <winspool.h>
#include <winperf.h>
#include <winsock.h>

#if ! defined( _WINUSER_ )
#include <winuser.h>
#endif // _WINUSER_

#if ( _MSC_VER > 1000 ) || defined( WFC_HAVE_WINCRYPT )
#include <wincrypt.h>
#endif // _MSC_VER

#include <ras.h>
#include <raserror.h>

#if ( _MSC_VER > 1000 ) || defined( WFC_HAVE_RASSAPI )
extern "C" {
#include <rassapi.h>
}
#endif // _MSC_VER

#if ! defined( PDWORD_PTR )
#define PDWORD_PTR LPDWORD
#endif

#include <winuser.h>
#include <lm.h>
#include <lmat.h>
#include <lzexpand.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <math.h> // used in CRandomNumberGenerator
#include <process.h> // used in beginthreadex() in CService
#include <sqltypes.h> // For CSystemTime's support of TIMESTAMP_STRUCT
#include <winioctl.h> // For CVolume stuff
#include <commdlg.h> // For GetFileTitle() in CFile64
#include <wininet.h> // For InternetOpenUrl() etc

#if defined ( __MINGW32__ ) // windows.h doesn't ole2.h include by default 
#include <ole2.h>           // Note: COM only works with new ABI (-fvtable-thunks)
#endif

#if ! defined( _NTSECAPI_ )
#include <ntsecapi.h>
#endif // _NTSECAPI_

// Thus endeth the Microsoft specific section, let's start our own
// declarations now.

// 2000-03-12
// Thanks go to Nick Britzman for clueing me in on the LMSTR data type
// that is new for Win2000 (NT5). For years (and many bug reports from
// this author that obviously fell on deaf ears), Microsoft has screwed up
// the LanManager API. In NT, you could pass only UNICODE strings even though
// the API's were prototyped to take either ANSI or UNICODE strings. In the
// Jan 2000 Platform SDK, they created a new string type called LMSTR
// (LanManager string). This broke my class library. :-(

#if ! defined( LMSTR )

// We are not compiling with the new LMSTR data type. Let's use the
// old data type

#define LMSTR LPTSTR

#endif // LMSTR

// 1999-08-17
// Thanks go to Brad Hubbard (hygbradh@mpx.com.au) for finding
// a TCHAR.H bug when using Visual C++ 5.0 (KB Q168433)

#if ( _MSC_VER < 1200 )
#ifdef _UNICODE
   #ifdef  _ttoi64
      #undef  _ttoi64
      #define _ttoi64 _wtoi64
   #endif
#else
   #ifdef  _ttoi64
      #undef  _ttoi64
      #define _ttoi64 _atoi64
   #endif
#endif // _UNICODE

#if ! defined( atoi64 )
#define atoi64 _atoi64
#endif // atoi64

#endif // _MSC_VER < 1200

// 2000-11-10
// Thanks to Danny Smith for the MINGW stuff

#if defined( __MINGW32__ )
// GCC compiler has different names for structures than Visual C++
#define _COMMCONFIG  _COMM_CONFIG
#define tagWINDOWPLACEMENT _WINDOWPLACEMENT
#endif // __MINGW32__

#if ! defined( NO_WFC_CONVERT_TO_UNICODE )
#include <mlang.h>
#endif

#if ! defined( NUMBER_OF_MICROSECONDS_IN_ONE_SECOND )
#define NUMBER_OF_MICROSECONDS_IN_ONE_SECOND (1000000)
#endif // NUMBER_OF_MICROSECONDS_IN_ONE_SECOND

#if ! defined( NUMBER_OF_MILLISECONDS_IN_ONE_SECOND )
#define NUMBER_OF_MILLISECONDS_IN_ONE_SECOND (1000)
#endif // NUMBER_OF_MILLISECONDS_IN_ONE_SECOND

#if ! defined( WFC_DONT_USE_NAMESPACES )
#if ( _MSC_VER > 1000 )
namespace Win32FoundationClasses
{
#endif // _MSC_VER > 1000
#endif // WFC_DONT_USE_NAMESPACES

#if ! defined( WFC_DONT_USE_NAMESPACES )
#define USING_WFC_NAMESPACE using namespace Win32FoundationClasses;
#else // WFC_DONT_USE_NAMESPACES
#define USING_WFC_NAMESPACE
#endif // WFC_DONT_USE_NAMESPACES

#include "wfcfloat.h" // For UNICODE floating point routines
#include "wfctrace.hpp"

#define CARRIAGE_RETURN (13)
#define LINE_FEED       (10)
#define WFC_STANDARD_TIME_FORMAT TEXT( "%H:%M:%S %d %b %Y" ) 

/*
** An easy way to refer to colors . . .
*/

#define BLACK     RGB( 0x00, 0x00, 0x00 )
#define RED       RGB( 0xFF, 0x00, 0x00 )
#define GREEN     RGB( 0x00, 0xFF, 0x00 )
#define YELLOW    RGB( 0xFF, 0xFF, 0x00 )
#define DKGRAY    RGB( 0x7F, 0x7F, 0x7F )
#define DARK_GRAY DKGRAY
#define LTGRAY    RGB( 0xC0, 0xC0, 0xC0 )
#define LIGHT_GRAY LTGRAY
#define DKRED     RGB( 0x7F, 0x00, 0x00 )
#define DARK_RED  DKRED
#define MAGENTA   RGB( 0xFF, 0x00, 0xFF )
#define PURPLE    RGB( 0x7F, 0x00, 0x7F )
#define BLUE      RGB( 0x00, 0x00, 0xFF )
#define DKBLUE    RGB( 0x00, 0x00, 0x7F )
#define DARK_BLUE DKBLUE
#define INDIGO    RGB( 0x00, 0xFF, 0xFF )
#define DKINDIGO  RGB( 0x00, 0x7F, 0x7F )
#define DARK_INDIGO DKINDIGO
#define WHITE     RGB( 0xFF, 0xFF, 0xFF )
#define DKGREEN   RGB( 0x00, 0x7F, 0x00 )
#define DARK_GREEN DKGREEN
#define DKTYELLOW RGB( 0x7F, 0x7F, 0x00 )
#define DARK_YELLOW DKYELLOW
#define LTYELLOW  RGB( 0xFF, 0xFF, 0x7F )
#define LIGHT_YELLOW LTYELLOW

// Bits...

#define BIT_0  (0x1)
#define BIT_1  (0x2)
#define BIT_2  (0x4)
#define BIT_3  (0x8)
#define BIT_4  (0x10)
#define BIT_5  (0x20)
#define BIT_6  (0x40)
#define BIT_7  (0x80)
#define BIT_8  (0x100)
#define BIT_9  (0x200)
#define BIT_10 (0x400)
#define BIT_11 (0x800)
#define BIT_12 (0x1000)
#define BIT_13 (0x2000)
#define BIT_14 (0x4000)
#define BIT_15 (0x8000)
#define BIT_16 (0x10000)
#define BIT_17 (0x20000)
#define BIT_18 (0x40000)
#define BIT_19 (0x80000)
#define BIT_20 (0x100000)
#define BIT_21 (0x200000)
#define BIT_22 (0x400000)
#define BIT_23 (0x800000)
#define BIT_24 (0x1000000)
#define BIT_25 (0x2000000)
#define BIT_26 (0x4000000)
#define BIT_27 (0x8000000)
#define BIT_28 (0x10000000)
#define BIT_29 (0x20000000)
#define BIT_30 (0x40000000)
#define BIT_31 (0x80000000)

#if ! defined( MFC_TO_STL_HEADER_FILE )
void PASCAL ASCII_to_UNICODE( LPCSTR ansi_string, LPWSTR unicode_string ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL UNICODE_to_ASCII( LPCWSTR unicode_string, LPSTR ansi_string, long number_of_unicode_characters_to_convert = (-1), UINT code_page = CP_ACP ) WFC_DOESNT_THROW_EXCEPTIONS;
#endif

void PASCAL Convert_NERR_Code_to_String( DWORD error_code, CString& error_message ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_append_text_to_edit_control( HWND edit_control_handle, LPCTSTR text_string ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_convert_lpcstr_to_cstring( const char * source_string, CString& destination_string ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_convert_lpcwstr_to_cstring( LPCWSTR source_string, CString& destination_string ) WFC_DOESNT_THROW_EXCEPTIONS;

#include "samtf.h"

#if ! defined( BITBOOL )
#define BITBOOL(x) (!(!(x)))
#endif

#if ! defined( bit_set )
#define bit_set(   arg, posn ) ((arg) |= (1L << (posn)))
#endif

#if ! defined( bit_clear )
#define bit_clear( arg, posn ) ((arg) &= ~(1L << (posn)))
#endif

#if ! defined( bit_test )
#define bit_test(  arg, posn ) BITBOOL((arg) & (1L << (posn)))
#endif

#include "CWideString.hpp"
#include "CTimeEx.hpp"

#if defined( WFC_STL )
#include "CCriticalSection.hpp"
#include "CFile.hpp"
#endif // WFC_STL

#include "CFile64.hpp"

/*
** Structure Helpers
*/

#include "Structs.hpp"
#include "Guards.hpp"

/*
** The Registration Database API
*/

#include "CRegisty.hpp"

/*
** Event Logging
*/

#include "CEventLogRecord.hpp"
#include "CEvntLog.hpp"

#include "CUNC.hpp"
#include "CURL.hpp"

/*
** Remote Access Service
*/

#include "CRASPORT.hpp"
#include "CRAS.hpp"

/*
** CFile stuff
*/

#include "DumyFile.hpp"
#include "Serial.hpp"
#include "Modem.hpp"

/*
** Simple Sockets
*/

#include "sockets.hpp"
#include "lsockets.hpp"
#include "tsockets.hpp"
#include "SockFile.hpp"
#include "CPing.hpp"

/*
** Named Pipes
*/

#include "cnmpipe.hpp"

#include "CBitArray.hpp"
#include "CBase64Coding.hpp"
#include "CUUCoding.hpp"
#include "CQueue.hpp"
#include "CFileTime.hpp"
#include "CSystemTime.hpp"
#include "lzfile.hpp"
#include "PortInformation.hpp"
#include "CNetwork.hpp"
#include "crasadm.hpp"
#include "CServer.hpp"
#include "CNetRsrc.hpp"
#include "CNetSess.hpp"
#include "CNetWkst.hpp"
#include "CNetFile.hpp"
#include "CNetConn.hpp"
#include "CNetShar.hpp"
#include "CNetInfo.hpp"
#include "CNetUser.hpp"
#include "Ovrlpd.hpp"
#include "dcb.hpp"
#include "ServiceConfiguration.hpp"
#include "CService.hpp"
#include "CSvcMgr.hpp"
//#include "CWait.hpp"
//#include "CBubble.hpp" // abandoned in release 73

#if ! defined( WFC_STL )
// Sorry, there's no GUI stuff in the STL build of WFC
// #include <DrawObj.hpp> // abandoned in release 73
//#include <DrawGrid.hpp> // abandoned in release 73
//#include <CSquigl.hpp> // abandoned in release 73
//#include <CConstellation.hpp> // abandoned in release 73
#endif // WFC_STL

#include "CSMTF.hpp"
#include "CTape.hpp"
#include "CMicrosoftTape.hpp"
// #include "Pager.hpp" // // abandoned in release 73
// #include "SkyWord.hpp" // abandoned in release 73
// #include "SprintSpectrum.hpp" // abandoned in release 73
#include "CMixer.hpp"
#include "CCrypto.hpp"
// #include "CWeather.hpp" // abandoned in release 73
#include "CRandomNumberGenerator.hpp"
#include "CRandomNumberGenerator2.hpp"
#include "CSuperRandomNumberGenerator.hpp"
#include "CDesktop.hpp"
#include "CGarbageCollector.hpp"
#include "CDataChunk.hpp"
#include "CDataFile.hpp"
#include "CDataMemory.hpp"
#include "CDataSocket.hpp"
#include "CDataArchive.hpp"
#include "CPasswordChangeFilter.hpp"
#include "CReedSolomonErrorCorrectionCode.hpp"
#include "CFileTransferProtocol.hpp"
#include "CNetworkScheduleJob.hpp"
#include "CParsePoint.hpp"
#include "CDataParser.hpp"
#include "CExtensibleMarkupLanguage.hpp"
#include "CXMLArchive.hpp"
// #include "CDragQuery.hpp" // abandoned in release 73
#include "CVolume.hpp"
#include "CServiceApplication.hpp"
#include "CPhysicalDiskFile.hpp"
#include "CFileDirectory.hpp"
#include "CMemoryFile.hpp"
#include "CJulianDate.hpp"
#include "CSharedMemoryObject.hpp"
#include "wfc_thread_information_block.h"
#include "wfc_undocumented.h"
#include "CCOMSucks.hpp"
#include "wfc_web_post.h"
// #include "CVeryLargeArray.hpp" // New for 70 // abandoned in release 73
// #include "CVeryLargeMemoryArray.hpp" // New for 70 // abandoned in release 73
// #include "CVeryLargeDiskArray.hpp" // New for 70 // abandoned in release 73

#if ! defined( MANUAL_RESET_EVENT )
#define MANUAL_RESET_EVENT() CreateEvent( NULL, TRUE, FALSE, NULL )
#endif // MANUAL_EVENT

#if ! defined( AUTO_RESET_EVENT )
#define AUTO_RESET_EVENT() CreateEvent( NULL, FALSE, FALSE, NULL )
#endif // AUTO_RESET_EVENT

// Some new NT5 privileges

#if ! defined( SE_DENY_INTERACTIVE_LOGON_NAME )
#define SE_DENY_INTERACTIVE_LOGON_NAME TEXT( "SeDenyInteractiveLogonRight" )
#endif // SE_DENY_INTERACTIVE_LOGON_NAME

#if ! defined( SE_DENY_NETWORK_LOGON_NAME )
#define SE_DENY_NETWORK_LOGON_NAME TEXT( "SeDenyNetworkLogonRight" )
#endif // SE_DENY_NETWORK_LOGON_NAME

#if ! defined( SE_DENY_BATCH_LOGON_NAME )
#define SE_DENY_BATCH_LOGON_NAME TEXT( "SeDenyBatchLogonRight" )
#endif // SE_DENY_BATCH_LOGON_NAME

#if ! defined( SE_DENY_SERVICE_LOGON_NAME )
#define SE_DENY_SERVICE_LOGON_NAME TEXT( "SeDenyServiceLogonRight" )
#endif // SE_DENY_SERVICE_LOGON_NAME

#if ! defined( SE_UNDOCK_NAME )
#define SE_UNDOCK_NAME TEXT( "SeUndockPrivilege" )
#endif // SE_UNDOCK_NAME

#if ! defined( SE_SYNC_AGENT_NAME )
#define SE_SYNC_AGENT_NAME TEXT( "SeSyncAgentPrivilege" )
#endif // SE_SYNC_AGENT_NAME

#if ! defined( SE_ENABLE_DELEGATION_NAME )
#define SE_ENABLE_DELEGATION_NAME TEXT( "SeEnableDelegationPrivilege" )
#endif // SE_ENABLE_DELEGATION_NAME

#if ! defined( SE_MANAGE_VOLUME_NAME )
#define SE_MANAGE_VOLUME_NAME TEXT( "SeManageVolumePrivilege" )
#endif // SE_SYNC_AGENT_NAME

// Some new Longhorn Privileges
#if ! defined( SE_REMOTE_INTERACTIVE_LOGON_NAME )
#define SE_REMOTE_INTERACTIVE_LOGON_NAME    TEXT("SeRemoteInteractiveLogonRight")
#endif // SE_REMOTE_INTERACTIVE_LOGON_NAME

#if ! defined( SE_DENY_REMOTE_INTERACTIVE_LOGON_NAME )
#define SE_DENY_REMOTE_INTERACTIVE_LOGON_NAME TEXT("SeDenyRemoteInteractiveLogonRight")
#endif // SE_DENY_REMOTE_INTERACTIVE_LOGON_NAME

#if ! defined( SE_IMPERSONATE_NAME )
#define SE_IMPERSONATE_NAME               TEXT("SeImpersonatePrivilege")
#endif

#if ! defined( SE_CREATE_GLOBAL_NAME )
#define SE_CREATE_GLOBAL_NAME             TEXT("SeCreateGlobalPrivilege")
#endif

// C Helper functions...

BOOL PASCAL wfc_am_i_administrator( void ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_close_handle( HANDLE handle ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_create_hard_link( LPCTSTR new_filename, LPCTSTR existing_filename, LPSECURITY_ATTRIBUTES security_attributes_p ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_delete_oldest_file( const CString& directory_path ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_disable_privilege( LPCTSTR privilege_name ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_enable_privilege( LPCTSTR privilege_name ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_enable_all_privileges( void ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_get_day_of_week( int year_with_century, int month, int day, int& day_of_week ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_get_filename_from_handle( HANDLE file_handle, CString& filename ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_move_file_at_reboot( const CString& existing_file, const CString& file_to_move ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CFileTime&    the_time ) WFC_DOESNT_THROW_EXCEPTIONS;
BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CSystemTime&  the_time ) WFC_DOESNT_THROW_EXCEPTIONS;

#if ! defined( WFC_STL )
BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, COleDateTime& the_time ) WFC_DOESNT_THROW_EXCEPTIONS;
#endif // WFC_STL

BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CTime&        the_time ) WFC_DOESNT_THROW_EXCEPTIONS;

DWORD PASCAL wfc_get_directory_usage_percentage( const CString& directory_path ) WFC_DOESNT_THROW_EXCEPTIONS;

void PASCAL wfc_append_string_to_CByteArray( const CString& string_to_append, CByteArray& bytes ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_append_ascii_string_to_CByteArray( const char * string_to_append, CByteArray& bytes ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_append_unicode_string_to_CByteArray( const wchar_t * string_to_append, CByteArray& bytes ) WFC_DOESNT_THROW_EXCEPTIONS;

#if ! defined( WFC_DEFAULT_WEB_PAGE_OPTIONS )
#define WFC_DEFAULT_WEB_PAGE_OPTIONS (INTERNET_FLAG_RELOAD|INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_NO_CACHE_WRITE|INTERNET_FLAG_IGNORE_CERT_CN_INVALID|INTERNET_FLAG_IGNORE_CERT_DATE_INVALID)
#endif // WFC_DEFAULT_WEB_PAGE_OPTIONS

double PASCAL wfc_calculate_entropy( const unsigned __int64 * counts, size_t number_of_counts ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 52
double PASCAL wfc_calculate_entropy( const unsigned long    * counts, size_t number_of_counts ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 52
double PASCAL wfc_calculate_entropy( const unsigned short   * counts, size_t number_of_counts ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 52
void PASCAL wfc_convert_double_null_terminated_string( const BYTE * buffer, CStringArray& string_array ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 41
void PASCAL wfc_convert_double_null_terminated_UNICODE_string( const WORD * buffer, CStringArray& string_array ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 45
bool PASCAL wfc_create_path( LPCTSTR path_name, LPSECURITY_ATTRIBUTES security_attributes_p = NULL ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 51
bool PASCAL wfc_create_wide_path( const wchar_t * path_name, LPSECURITY_ATTRIBUTES security_attributes_p = NULL ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 52
void PASCAL wfc_exit_process_and_delete_exe( void ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_get_activex_servers( CStringArray& server_list ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_get_error_string( DWORD error_code, CString& error_string ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_get_executable_directory( CString& directory_name_ending_in_a_slash ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_get_operating_system_version_string( CString& version_string ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_get_string_from_clipboard( CString& string_to_return ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_get_thread_name( CString& thread_name ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_get_web_page( CUniformResourceLocator& url, CStringArray& page_contents, DWORD options = WFC_DEFAULT_WEB_PAGE_OPTIONS ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_get_web_page( CUniformResourceLocator& url, CByteArray& page_contents, DWORD options = WFC_DEFAULT_WEB_PAGE_OPTIONS ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_make_ntfs_go_fast( void ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_protect_data( const BYTE * plaintext, const size_t number_of_bytes_in_plaintext, BYTE * ciphertext, size_t * address_of_number_of_cipher_bytes ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_unprotect_data( const BYTE * ciphertext, const size_t number_of_bytes_in_ciphertext, BYTE * plaintext, size_t * address_of_number_of_plain_bytes ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_set_activex_servers( const CStringArray& server_list ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_set_thread_name( LPCTSTR thread_name ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_start_screen_saver( void ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_kill_most_recently_used_document_list( void ) WFC_DOESNT_THROW_EXCEPTIONS;

inline bool PASCAL wfc_does_file_exist( LPCTSTR file_name ) WFC_DOESNT_THROW_EXCEPTIONS
{
   HANDLE file_handle = CreateFile( file_name,
                                    0, // zero means we want NO access, we just want to query the device
                                    0,
                                    NULL,
                                    OPEN_EXISTING,
                                    0,
                                    NULL );

   if ( file_handle == INVALID_HANDLE_VALUE )
   {
      return( false );
   }

   CloseHandle( file_handle );
   return( true );
}

// Coverage analysis stuff
#define WFC_COVERAGE_DECLARE
#define WFC_COVERAGE( x )
#define WFC_COVERAGE_WITH_NAME
#define WFC_COVERAGE_REPORT()
#define WFC_COVERAGE_SET_NUMBER_OF_POINTS
#define WFC_COVERAGE_EXTERN_DECLARE
#define WFC_COVERAGE_RECORD_TIME
#define WFC_SET_COVERAGE_POINT_NAME

#if ! defined( NO_WFC_CONVERT_TO_UNICODE )

#if ! defined( WFC_AUTOMATICALLY_SELECT_CODEPAGE )
#define WFC_AUTOMATICALLY_SELECT_CODEPAGE (50001)
#endif // WFC_AUTOMATICALLY_SELECT_CODEPAGE

#if ! defined( WFC_DEFAULT_CODEPAGE )
#define WFC_DEFAULT_CODEPAGE (WFC_AUTOMATICALLY_SELECT_CODEPAGE)
#endif // WFC_DEFAULT_CODEPAGE

bool PASCAL wfc_read_xml_from_file( LPCTSTR filename, CExtensibleMarkupLanguageDocument& xml ) WFC_DOESNT_THROW_EXCEPTIONS;
void PASCAL wfc_free_unicode_conversion_context( VOID * unicode_conversion_context ) WFC_DOESNT_THROW_EXCEPTIONS;
VOID * PASCAL wfc_get_unicode_conversion_context( bool is_com_already_started_in_this_thread ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_detect_code_page( VOID * unicode_conversion_context, const BYTE * buffer, size_t number_of_bytes_in_buffer, DWORD encoding_hints, DWORD& code_page ) WFC_DOESNT_THROW_EXCEPTIONS;
bool PASCAL wfc_convert_to_unicode( VOID *            unicode_conversion_context,
                                    const CByteArray& bytes,
                                    wchar_t *         unicode_string,
                                    size_t            number_of_wide_characters,
                                    DWORD             suggested_code_page,
                                    DWORD             encoding_hints   = 0xFFFFFFFF,
                                    DWORD *           real_code_page_p = NULL ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 52
bool PASCAL wfc_convert_to_unicode( VOID *       unicode_conversion_context,
                                    const BYTE * byte_buffer,
                                    size_t       number_of_bytes_in_buffer,
                                    wchar_t *    unicode_string,
                                    size_t       number_of_wide_characters,
                                    DWORD        suggested_code_page,
                                    DWORD        encoding_hints   = 0xFFFFFFFF,
                                    DWORD *      real_code_page_p = NULL ) WFC_DOESNT_THROW_EXCEPTIONS; // New for 52
#endif // NO_WFC_CONVERT_TO_UNICODE

#define WFC_INITIALIZE_SINGLE_THREADED_COM() ::CoInitialize( NULL )
#define WFC_INITIALIZE_SINGLE_THREADED_COM_NO_DDE() ::CoInitializeEx( NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE | COINIT_SPEED_OVER_MEMORY )
#define WFC_INITIALIZE_MULTITHREADED_COM() ::CoInitializeEx( NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE | COINIT_SPEED_OVER_MEMORY )

/*
** Last but not least, let's see if we are building a UNICODE console
** application, if so, we need to do one last thing for the user:
*/

// 2001-07-25
// If the user is building a UNICODE DLL (which I can't detect automatically)
// we need to NOT specify an entry point.

#if ! defined( WFC_DONT_FIX_UNICODE_LINK )
#if defined( _UNICODE )
#if defined( _CONSOLE )
// We're building a console application
#pragma message( "NOTE: If you get a linker problem about wmainCRTStartup you are probably building a Unicode DLL." )
#pragma comment( linker, "/ENTRY:wmainCRTStartup" )
#else // _CONSOLE
// We're building a GUI application
#pragma message( "NOTE: If you get a linker problem about wWinMainCRTStartup you are probably building a Unicode DLL." )
#pragma comment( linker, "/ENTRY:wWinMainCRTStartup" )
#endif // _CONSOLE
#pragma message( "      To fix the problem. #define WFC_DONT_FIX_UNICODE_LINK before including wfc.h" )
#endif // _UNICODE
#endif // WFC_DONT_FIX_UNICODE_LINK

#if ! defined( WFC_DONT_USE_NAMESPACES )
#if ( _MSC_VER > 1000 )
// Terminate the namespace declaration
}
#endif // _MSC_VER > 1000
#endif // WFC_DONT_USE_NAMESPACES

#pragma warning( disable : 4699 )

#endif // WIN32_FOUNDATION_CLASSES
