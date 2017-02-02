/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** Copyright, 2002-2003, Samuel R. Blackburn
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

#if ! defined( WFC_VALIDATE_HEADER_FILE_INCLUDED )

#define WFC_VALIDATE_HEADER_FILE_INCLUDED

// 2000-11-15
/*
** New for Release 51, pointer validation. The funny values in these
** macros are explained in WFC Tech Note 6. In short:
** 0xABABABAB - memory following a block allocated by LocalAlloc()
** 0xBAADF00D - memory allocated via LocalAlloc( LMEM_FIXED, ... ) but
**              not yet written to.
** 0xFEEEFEEE - Memory dedicated to a heap but not yet allocated by
**              HeapAlloc() or LocalAlloc()
** 0xCCCCCCCC - Microsoft Visual C++ compiled code with the /GZ option
**              is automatically initialized the uninitialized variable
**              with this value.
** 0xCDCDCDCD - Microsoft Visual C++ compiled code with memory leak detection
**              turned on. Usually, DEBUG_NEW was defined. Memory with this
**              tag signifies memory that has been allocated (by malloc() or
**              new) but never written to the application.
** 0xDDDDDDDD - Microsoft Visual C++ compiled code with memory leak detection
**              turned on. Usually, DEBUG_NEW was defined. Memory with this
**              tag signifies memory that has been freed (by free() or delete)
**              by the application. It is how you can detect writing to memory
**              that has already been freed. For example, if you look at an
**              allocated memory structure (or C++ class) and most of the
**              members contain this tag value, you are probably writing to
**              a structure that has been freed.
** 0xFDFDFDFD - Microsoft Visual C++ compiled code with memory leak detection
**              turned on. Usually, DEBUG_NEW was defined. Memory with this
**              tag signifies memory that is in "no-mans-land." These are
**              bytes just before and just after an allocated block. They are
**              used to detect array-out-of-bounds errors. This is great for
**              detecting off-by-one errors.
*/

#if ! defined( WFC_VALIDATE_POINTER )
#if defined( _W64 )
// 64-bit version
#if defined( _DEBUG ) && defined( _ASSERTE )
#define WFC_VALIDATE_POINTER( _pointer ) _ASSERTE( (SIZE_T) _pointer != NULL ); \
_ASSERTE( (SIZE_T) _pointer != 0xABABABAB ); \
_ASSERTE( (SIZE_T) _pointer != 0xBAADF00D ); \
_ASSERTE( (SIZE_T) _pointer != 0xFEEEFEEE ); \
_ASSERTE( (SIZE_T) _pointer != 0xCCCCCCCC ); \
_ASSERTE( (SIZE_T) _pointer != 0xCDCDCDCD ); \
_ASSERTE( (SIZE_T) _pointer != 0xDDDDDDDD ); \
_ASSERTE( (SIZE_T) _pointer != 0xFDFDFDFD ); \
_ASSERTE( (SIZE_T) _pointer != 0xABABABABABABABAB ); \
_ASSERTE( (SIZE_T) _pointer != 0xBAADF00DBAADF00D ); \
_ASSERTE( (SIZE_T) _pointer != 0xFEEEFEEEFEEEFEEE ); \
_ASSERTE( (SIZE_T) _pointer != 0xCCCCCCCCCCCCCCCC ); \
_ASSERTE( (SIZE_T) _pointer != 0xCDCDCDCDCDCDCDCD ); \
_ASSERTE( (SIZE_T) _pointer != 0xDDDDDDDDDDDDDDDD ); \
_ASSERTE( (SIZE_T) _pointer != 0xFDFDFDFDFDFDFDFD )
#else // _DEBUG
#define WFC_VALIDATE_POINTER( _pointer )
#endif // _DEBUG
#else // _W64
#if defined( _DEBUG ) && defined( _ASSERTE )
#define WFC_VALIDATE_POINTER( _pointer ) _ASSERTE( (SIZE_T) _pointer != NULL ); \
_ASSERTE( (SIZE_T) _pointer != 0xABABABAB ); \
_ASSERTE( (SIZE_T) _pointer != 0xBAADF00D ); \
_ASSERTE( (SIZE_T) _pointer != 0xFEEEFEEE ); \
_ASSERTE( (SIZE_T) _pointer != 0xCCCCCCCC ); \
_ASSERTE( (SIZE_T) _pointer != 0xCDCDCDCD ); \
_ASSERTE( (SIZE_T) _pointer != 0xDDDDDDDD ); \
_ASSERTE( (SIZE_T) _pointer != 0xFDFDFDFD )
#else // _DEBUG
#define WFC_VALIDATE_POINTER( _pointer )
#endif // _DEBUG
#endif // _W64
#endif // WFC_VALIDATE_POINTER

#if ! defined( WFC_VALIDATE_POINTER_NULL_OK )
#if defined( _W64 )
// 64-bit version
#if defined( _DEBUG ) && defined( _ASSERTE )
#define WFC_VALIDATE_POINTER_NULL_OK( _pointer ) \
_ASSERTE( (SIZE_T) _pointer != 0xABABABAB ); \
_ASSERTE( (SIZE_T) _pointer != 0xBAADF00D ); \
_ASSERTE( (SIZE_T) _pointer != 0xFEEEFEEE ); \
_ASSERTE( (SIZE_T) _pointer != 0xCCCCCCCC ); \
_ASSERTE( (SIZE_T) _pointer != 0xCDCDCDCD ); \
_ASSERTE( (SIZE_T) _pointer != 0xDDDDDDDD ); \
_ASSERTE( (SIZE_T) _pointer != 0xFDFDFDFD ); \
_ASSERTE( (SIZE_T) _pointer != 0xABABABABABABABAB ); \
_ASSERTE( (SIZE_T) _pointer != 0xBAADF00DBAADF00D ); \
_ASSERTE( (SIZE_T) _pointer != 0xFEEEFEEEFEEEFEEE ); \
_ASSERTE( (SIZE_T) _pointer != 0xCCCCCCCCCCCCCCCC ); \
_ASSERTE( (SIZE_T) _pointer != 0xCDCDCDCDCDCDCDCD ); \
_ASSERTE( (SIZE_T) _pointer != 0xDDDDDDDDDDDDDDDD ); \
_ASSERTE( (SIZE_T) _pointer != 0xFDFDFDFDFDFDFDFD )
#else // _DEBUG
#define WFC_VALIDATE_POINTER_NULL_OK( _pointer )
#endif // _DEBUG
#else // _W64
#if defined( _DEBUG ) && defined( _ASSERTE )
#define WFC_VALIDATE_POINTER_NULL_OK( _pointer ) \
_ASSERTE( (SIZE_T) _pointer != 0xABABABAB ); \
_ASSERTE( (SIZE_T) _pointer != 0xBAADF00D ); \
_ASSERTE( (SIZE_T) _pointer != 0xFEEEFEEE ); \
_ASSERTE( (SIZE_T) _pointer != 0xCCCCCCCC ); \
_ASSERTE( (SIZE_T) _pointer != 0xCDCDCDCD ); \
_ASSERTE( (SIZE_T) _pointer != 0xDDDDDDDD ); \
_ASSERTE( (SIZE_T) _pointer != 0xFDFDFDFD )
#else // _DEBUG
#define WFC_VALIDATE_POINTER_NULL_OK( _pointer )
#endif // _DEBUG
#endif // _W64
#endif // WFC_VALIDATE_POINTER_NULL_OK

#if ! defined( WFC_VALIDATE_POINTER_NULL_OK )
#if defined( _DEBUG ) && defined( _ASSERTE )
#define WFC_VALIDATE_POINTER_NULL_OK( _pointer ) \
_ASSERTE( (DWORD) _pointer != 0xABABABAB ); \
_ASSERTE( (DWORD) _pointer != 0xBAADF00D ); \
_ASSERTE( (DWORD) _pointer != 0xFEEEFEEE ); \
_ASSERTE( (DWORD) _pointer != 0xCCCCCCCC ); \
_ASSERTE( (DWORD) _pointer != 0xCDCDCDCD ); \
_ASSERTE( (DWORD) _pointer != 0xDDDDDDDD ); \
_ASSERTE( (DWORD) _pointer != 0xFDFDFDFD )
#else // _DEBUG
#define WFC_VALIDATE_POINTER_NULL_OK( _pointer )
#endif // _DEBUG
#endif // WFC_VALIDATE_POINTER_NULL_OK

#if ! defined( WFC_VALIDATE_BOOL )
#if defined( _DEBUG ) && defined( _ASSERTE )
#define WFC_VALIDATE_BOOL( _BOOLean_value ) \
_ASSERTE( _BOOLean_value == TRUE || _BOOLean_value == FALSE )
#else // _DEBUG
#define WFC_VALIDATE_BOOL( _BOOLean_value )
#endif // _DEBUG
#endif // WFC_VALIDATE_BOOL

#if ! defined( WFC_VALIDATE_bool )
#if defined( _DEBUG ) && defined( _ASSERTE )
#define WFC_VALIDATE_bool( _BOOLean_value ) \
_ASSERTE( _BOOLean_value == true || _BOOLean_value == false )
#else // _DEBUG
#define WFC_VALIDATE_bool( _BOOLean_value )
#endif // _DEBUG
#endif // WFC_VALIDATE_bool

#endif // WFC_VALIDATE_HEADER_FILE_INCLUDED
