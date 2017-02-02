////////////////////////////////////////////////////////////
// Comments
//
// This class, like the CString class, is not designed to 
// allow easy derivation. It merely adds useful new member 
// functions and doesn't try to modify the basic behavior 
// of CString. CStringEx is not dependent from any other 
// classes. Therefore it can be used for itself. Like in C
// String, no member function is virtual with exception 
// of the destructor.
//
// CStringEx doesn't manipulate the CStringData structure or
// the m_pchData data member directly. All its member functions 
// use either CString member functions or C++/Win32 APIs. CStringEx
// doesn't rely on any undocumented CString feature.
//
// Unless the function returns a specific value, all these
// functions return a reference to the CStringEx itself (although
// this is less useful than with standard strxxx functions, there
// are some situations where this may help). The only exceptions
// are the path manipulation functions which are static and can
// therefore be called to manipulate a path without instantiating
// a CStringEx.
//
// Exceptions: since none of these additional functions allocates
// memory by itself, all exceptions will be thrown by the CString 
// class.


// Includes
#include "stdafx.h"

#include "CStringEx.h"
#include <tchar.h>

//====== Constructors ======

CStringEx::CStringEx()
{
}

//====== Operations ======

// See Inlines in cstringext.h

CStringEx CStringEx::ExpandTabs(int nTabIncr, BOOL bIgnoreQuotes, int nMaxSize)
// Expands tab characters according to a given tab stop increment.
// nMaxSize defaults to INT_MAX.
{
	int		nNumSpaces;		// Number of spaces to add when a tab is found
	BOOL	bInQuotes;		// Doesn't expand tabs between quotes if requested
	TCHAR	c;				// Current source char
	int		nSourceIndex;	// Index in source
	int		nTargetIndex;	// Index in target
	int		nAllocLen;		// Starting size of target buffer
	int		nSrcLen = GetLength();
	TCHAR	chQuote;		// Current quote character

	nAllocLen = nSrcLen * 2;	// We start with a target buffer being twice
								// the size of *this* string
	CStringEx sTarget(' ', nAllocLen);

	if (nSrcLen == 0)	// empty
		return(sTarget);

	// Initialize variables
	c = GetAt(0);
	nSourceIndex = 0;
	nTargetIndex = 0;
	nMaxSize--;
	bInQuotes = FALSE;

	// for each character in source (this string)...
	while ((nSourceIndex < nSrcLen) && (nTargetIndex < nMaxSize))
	{
		switch (c)
		{
			case '\'':
			case '"' :
				if (!bIgnoreQuotes)
				{
					if (!bInQuotes)
					{
						bInQuotes = TRUE;
						chQuote = c;
					}
					else if ((c == chQuote) 
							 &&
							 (GetAt(nSourceIndex - 1) != '\\'))
					// Closing, non escaped quote
						bInQuotes = FALSE;
				}
				goto default_processing;
				// break;								  

			case '\t':	// Got a tab
				if (!bInQuotes)
				{
					// Compute the number of spaces necessary to go to the next tab stop
					nNumSpaces = nTabIncr - (nTargetIndex % nTabIncr);
					if ((nTabIncr > 0) && (nNumSpaces != 0))
					{
						if (nTargetIndex + nNumSpaces < nMaxSize)
						{
							// Append spaces to target
							LPSTR pBuf = sTarget.GetBuffer(nTargetIndex + nNumSpaces);
							_tcsncset(pBuf + nTargetIndex, ' ', nNumSpaces);
							sTarget.ReleaseBuffer();
							nTargetIndex += nNumSpaces;		// Skip spaces
						}
					}
					break;
				}
				// else fall through to default procesing

default_processing:

			default:
				if (nTargetIndex >= nMaxSize)				// Overflow: return unchanged string
					return(*this);
				if (nTargetIndex >= sTarget.GetLength())	// Grow target
					sTarget += CStringEx(' ', nAllocLen);	// Store char
				sTarget.SetAt(nTargetIndex++, c);
				break;
		}
		if (++nSourceIndex < nSrcLen)
			c = GetAt(nSourceIndex);	// Get next char from source (this string)
	} // switch (c)

	if ((nSourceIndex < nSrcLen) && (nTargetIndex >= nMaxSize))
	// Abnormal termination. Should not happen.
		return(*this);
	else
	{
		// Return a clean string with no extra memory
		sTarget.GetBufferSetLength(nTargetIndex);
		sTarget.ReleaseBuffer(-1);
		return(sTarget);
	}
}

CStringEx CStringEx::CompressSpaces(int nTabIncr, BOOL bIgnoreQuotes)
// Compress space characters to tabs according to the value of the
// nTabIncr parameter. Spaces within quotes are optionally ignored.
{

	TCHAR		c;
	int			nCol;
	int			nNumSpaces;
	TCHAR*		lpszSrc;
	TCHAR*		lpszDest;
	TCHAR*		lpszTarget;
	BOOL		bInQuotes;

	int			nLen = GetLength();

	lpszSrc = GetBuffer(nLen + 1);
	// Allocate space for target string
	lpszDest = (TCHAR*) new	TCHAR[nLen + 1];
	lpszTarget = lpszDest;

	// If there's something to do...
	if ((nLen >= nTabIncr) && (_tcschr(lpszSrc, ' ') != NULL))
	{
		nCol = 0;
		nNumSpaces = 0;
		bInQuotes = FALSE;
		do
		{
			c = *lpszSrc;		// Get next character in source
			switch (c)
			{
				// Special processing for ' and "
				// Doesn't compress spaces inside quotes if !bIgnoreQuotes
				case '"':
				case '\'':
					if (bIgnoreQuotes)
						goto DefaultProcessing;

					if (!bInQuotes)
					{
						nCol++;
						memset(lpszDest, ' ', nNumSpaces);
						lpszDest += nNumSpaces;
						bInQuotes = TRUE;
					}
					else if ((c == '\'') && (*(lpszSrc + 1) == '\''))
					{
						nNumSpaces = 0;
						*lpszDest = '\''; // '' sequence. Insert it and skip second '
						lpszDest++;
						*lpszDest = '\'';
						lpszDest++;
						lpszSrc++;
						goto NextChar;
					}
					else if (((c == '"') && (*(lpszSrc - 1) != '\\')) || (c == '\''))
					{
						nCol++;
						bInQuotes = FALSE;
					}

					*lpszDest = c;
					lpszDest++;
					nNumSpaces = 0;
					break;

				case ' ':
					if (!bInQuotes)
					{
						nNumSpaces++;
						nCol++;
						if ((nTabIncr <= 0) || (nCol % nTabIncr == 0))
						{
							if (nNumSpaces > 1)
								*lpszDest = '\t';
							else
								*lpszDest = ' ';
							nNumSpaces = 0;
							lpszDest++;
						}
					}
					else
					{
						nNumSpaces = 0;
						*lpszDest = ' ';
						lpszDest++;
					}
					break;

				case '\t':
					nCol = 0;
					nNumSpaces = 0;
					*lpszDest = '\t';
					lpszDest++;
					break;

				default:
DefaultProcessing:
					nCol++;
					memset(lpszDest, ' ', nNumSpaces);
					lpszDest += nNumSpaces;
					nNumSpaces = 0;
					*lpszDest = c;
					lpszDest++;
					break;
			}
NextChar:
			lpszSrc++;
		}
		while (c != '\0');
	}
	ReleaseBuffer(-1);

	CStringEx sTarget(lpszTarget);
	delete [] lpszTarget;

	return sTarget;
}

CStringEx& CStringEx::Insert(const CString sSource, int nPos)
// Insert the source string at the given position.
// If specified position is past EOL, overlay string instead.
{
	int nLen;

	if ((nLen = sSource.GetLength()) == 0)
		return (*this);
	if (nPos < GetLength())
	{
		LPSTR pBuf = MakeRoom(nPos, nLen);
		memcpy(pBuf, (LPCTSTR) sSource, nLen);
		ReleaseBuffer();
		return(*this);
	}
	else
		return(Overlay(sSource, nPos));
}

CStringEx& CStringEx::InsertChar(const TCHAR ch, int nPos)
// Insert character at the given position
// If specified position is past EOL, overlay char instead.
{
	if (nPos < GetLength())
	{
		LPTSTR pBuf = MakeRoom(nPos, 1);
		pBuf[0] = ch;
		ReleaseBuffer();
		return(*this);
	}
	else
		return(OverlayChar(ch, nPos));
}

CStringEx& CStringEx::PadRight(const TCHAR ch, int nNewLen)
// Pad string with trailing chars so that the length becomes nNewLen
{
	int nLen = GetLength();
	if (nNewLen > nLen)
		*this += CString(ch, nNewLen - nLen);
	return(*this);
}

CStringEx& CStringEx::PadLeft(const TCHAR ch, int nNewLen)
// Pad string with leading chars so that the length becomes nNewLen
{
	int nLen = GetLength();
	if (nNewLen > nLen)
		Insert(CString(ch, nNewLen - nLen), 0);
	return(*this);
}

CStringEx& CStringEx::Overlay(const CString sSource, int nPos)
// Overlay sSource at specified position. Pad with spaces if necessary.
{
	int nLen = GetLength();
	LPTSTR pBuf;
	int nSrcLen = sSource.GetLength();

	if (nPos > nLen)
		PadRight(' ', nPos);
	if (nPos + nSrcLen > nLen)
		pBuf = GetBufferSetLength(nPos + nSrcLen);		// String must grow
	else
		pBuf = GetBuffer(nLen);							// Source fit into target
	memcpy(pBuf + nPos, (LPCTSTR) sSource, nSrcLen);
	ReleaseBuffer(-1);
	return(*this);
}

CStringEx& CStringEx::OverlayChar(const TCHAR ch, int nPos)
// Overlay character at specified position. Pad with spaces if necessary.
{
	if (nPos >= GetLength())
		PadRight(' ', nPos + 1);
	SetAt(nPos, ch);
	return(*this);
}

CString CStringEx::FullPath(CString sRelPath)
// static function encapsulating the _tfullpath function
{
	CString sTemp;

	_tfullpath( sTemp.GetBuffer(_MAX_PATH), sRelPath, _MAX_PATH);
	sTemp.ReleaseBuffer();

	return(sTemp);
}

void CStringEx::SplitPath(CString const sPath, CString& sDrive, CString& sDir, CString& sName, CString& sExt, BOOL bIsDir)
// static function encapsulating the _tsplitpath function
{
	_tsplitpath((LPCTSTR) sPath,
			    sDrive.GetBuffer(_MAX_DRIVE),
			    sDir.GetBuffer(_MAX_DIR), 
			    sName.GetBuffer(_MAX_FNAME), 
			    sExt.GetBuffer(_MAX_EXT));
	sDrive.ReleaseBuffer(-1);
	sDir.ReleaseBuffer(-1);
	sName.ReleaseBuffer(-1);
	sExt.ReleaseBuffer(-1);

	// If the passed string is a directory path and if the last subfolder 
	// of this path contains a dot, the returned extension will actually
	// be a part of the path itself, so we re-append it.
	if (bIsDir)
		sName += sExt;
}

CString CStringEx::MakePath(CString sDrive, CString sDir, CString sName, CString sExt)
// static function encapsulating the _tmakepath function
{
	CString sTemp;

	_tmakepath( sTemp.GetBuffer(_MAX_PATH), 
				(LPCTSTR) sDrive,
				(LPCTSTR) sDir,
				(LPCTSTR) sName,
				(LPCTSTR) sExt);
	sTemp.ReleaseBuffer(-1);
	return(sTemp);
}

CStringEx& CStringEx::ReplaceNameComponent(const CString sNewComponent, int nComponent)
// Assumes current string is a path. Replace specified name component.
{
	CString	sDrive;
	CString sDir;
	CString	sName;
	CString sExt;
	CString	sPath;

	ASSERT ((nComponent == EX_STRING_REPDRIVE) 
			|| (nComponent == EX_STRING_REPDIR) 
			|| (nComponent == EX_STRING_REPNAME) 
			|| (nComponent == EX_STRING_REPEXT));

	// First retrieve current filename components...
	SplitPath(*this, sDrive, sDir, sName, sExt);

	// then rebuild the filename using the new component
	switch (nComponent)
	{
		case EX_STRING_REPDRIVE:
			*this = MakePath(sNewComponent, sDir, sName, sExt);
			break;
		case EX_STRING_REPDIR:
			*this = MakePath(sDrive, sNewComponent, sName, sExt);
			break;
		case EX_STRING_REPNAME:
			*this = MakePath(sDrive, sDir, sNewComponent, sExt);
			break;
		case EX_STRING_REPEXT:
			*this = MakePath(sDrive, sDir, sName, sNewComponent);
			break;
	}
	
	return(*this);
}

CString CStringEx::GetExtension()
{
	CString sExt;

	int nDotPos = ReverseFind('.');
	if (nDotPos != -1)
		sExt = Mid(nDotPos);

	return(sExt);
}

int CStringEx::FindNoCase(CString sTarget, int nStart)
{
	// bUGGY I think
	/*
	CStringEx sThis = *this;

	sThis.MakeUpper();
	sTarget.MakeUpper();

	return(sThis.Find(sTarget, nStart));
	*/
	return 0;
}

int	CStringEx::CompareNoCase(CString sTarget, int nCount)
{	
	TCHAR*		lpszSrc;
	long		nNbToCmp = 0;
	long		nLen = GetLength();

	lpszSrc = GetBuffer(nLen + 1);

	// No Argument nCount provided
	if (nCount == 0)
		nNbToCmp = nLen;
	else
		nNbToCmp = nCount;

	return _tcsncicmp(lpszSrc, (LPCTSTR)sTarget, nNbToCmp);

}




CStringEx& CStringEx::Replace(CString sToken, CString sNewToken, int nMode, BOOL bCase)
// Replace a token with another. Can replace first, last or all tokens.
{
	int			nPos;
	BOOL		bReversed;			
	int			nTokenLen = sToken.GetLength();
	CString&	sTokenRef = sToken;			// Different references will be used
	CStringEx&	sSourceRef = *this;			// if we are doing a Replace Last
	CString&	sNewTokenRef = sNewToken;
	CString		sTokenRev;
	CString		sSourceRev;
	CString		sNewTokenRev;

	ASSERT ((nMode == EX_STRING_REPFIRST) || (nMode == EX_STRING_REPLAST) || (nMode == EX_STRING_REPALL));

	if ((sToken.GetLength() == 0) || (GetLength() == 0))
		return(*this);

	bReversed = nMode == EX_STRING_REPLAST;
	if (bReversed)
	{
		nMode = EX_STRING_REPFIRST;		// Will proceed like "Replace First..."
		sTokenRev = sToken;
		sTokenRev.MakeReverse();		// but will reverse all strings before.
		sTokenRef = sTokenRev;				
		sNewTokenRev = sNewToken;		// We work on copies anyway. 
		sNewTokenRev.MakeReverse();		
		sNewTokenRef = sNewTokenRev;		
		sSourceRev = *this;				
		sSourceRev.MakeReverse();
		sSourceRef = sSourceRev;
	}

	// Find first occurence of sToken...
	int nLen = sNewToken.GetLength();

	nPos = bCase ? sSourceRef.Find(sTokenRef) : sSourceRef.FindNoCase(sTokenRef);
	while (nPos != -1)
	{
		// Delete and replace it
		sSourceRef.Delete(nPos, nTokenLen);
		sSourceRef.Insert(sNewTokenRef, nPos);
		// Get next occurence - Replace only one occurence if Replace All not specified
		nPos = (nMode == EX_STRING_REPALL) ? (bCase ? sSourceRef.Find(sTokenRef, nPos + nLen) : sSourceRef.FindNoCase(sTokenRef, nPos + nLen)) : -1;
	};

	if (bReversed)
	{
		sSourceRef.MakeReverse();
		*this = sSourceRef;
	}

	return(*this);
}

CStringEx& CStringEx::StripSlash(void)
// Removes trailing slash if any but not if the string represents a root directory
{
	int nLen = GetLength();
	if ((nLen > 0) && (GetAt(nLen - 1) == '\\') && (!((nLen == 3) && (GetAt(1) == ':'))))
		SetAt(nLen - 1, '\0');

	return (*this);
}

CString& CStringEx::StripToPath()
{
	int nSlashPos = ReverseFind('\\');
	if (nSlashPos != -1)
		Delete(nSlashPos + 1);

	return (*this);
}

CStringEx CStringEx::GetFirstToken(CString& sDelimiters, int nMaxLen)
// Please be aware that the string **is** modified by each call to
// _tcstok (null chars inserted). So using a copy of the string
// is certainly a good choice.

// The first separator will be translated to a special character
// '\1' before parsing when found within quotes. It is then translated
// to sDelimiters[0] when returning the token to the caller. This will 
// also happen for GetNextToken even if the delimiters have changed.
{


	CString sToken;
	TCHAR*	p;
	BOOL	bInQuotes = FALSE;
	int		nLen = GetLength();

	// Protect first separator if within quotes
	for (int nIndex = 0; nIndex < nLen; nIndex++)
	{
		if (GetAt(nIndex) == '"')
			bInQuotes = !bInQuotes;
		else if (bInQuotes && (GetAt(nIndex) == sDelimiters[0]))
			SetAt(nIndex, '\1');
	}

	if ((p = _tcstok(GetBuffer(nMaxLen), sDelimiters)) != NULL)
	{
		sToken = p;

		BOOL bInQuotes = FALSE;
		int	nLen = sToken.GetLength();
		// Restore original characters before returning
		for (int nIndex = 0; nIndex < nLen; nIndex++)
		{
			if (sToken.GetAt(nIndex) == '"')
				bInQuotes = !bInQuotes;
			else if (bInQuotes && sToken.GetAt(nIndex) == '\1')
				sToken.SetAt(nIndex, sDelimiters[0]);
		}
	}

	return(sToken);		
}

CStringEx CStringEx::GetNextToken(CString& sDelimiters)
// Please be aware that the string **is** modified by each call to
// _tcstok (null chars inserted). So using a copy of the string
// is certainly a good choice.
{
	CString sToken;
	TCHAR*	p;

	if ((p = _tcstok(NULL, sDelimiters)) != NULL)
	{
		sToken = p;

		BOOL bInQuotes = FALSE;
		int	nLen = sToken.GetLength();
		// Restore original characters before returning
		for (int nIndex = 0; nIndex < nLen; nIndex++)
		{
			if (sToken.GetAt(nIndex) == '"')
				bInQuotes = !bInQuotes;
			else if (bInQuotes && sToken.GetAt(nIndex) == '\1')
				sToken.SetAt(nIndex, sDelimiters[0]);
		}
	}
	else
		ReleaseBuffer(-1);

	return(sToken);		
}

CStringEx& CStringEx::RemoveQuotes()
{
	if ((GetLength() >= 2) && (GetAt(0) == '"') && (GetAt(GetLength() - 1) == '"'))
	{
		Delete(0, 1);
		Delete(GetLength() - 1, 1);
	}

	return (*this);
}

CStringEx& CStringEx::ItoA(int value, int radix)
{
	TCHAR szBuf[20];

	_itot(value, szBuf, radix);
	*this = szBuf;
	
	return(*this);		
}

CStringEx& CStringEx::LtoA(int value, CString sNum, int radix)
{
	TCHAR szBuf[20];

	_ltot(value, szBuf, radix);
	*this = szBuf;
		
	return(*this);		
}

long CStringEx::AtoL()
{
	long lResult;
	
	lResult = _tcstol(GetBuffer(GetLength() + 1), NULL, 10);
	ReleaseBuffer(-1);
	
	return(lResult);
}

double CStringEx::AtoD()
{
	double dResult;
	
	dResult = _tcstod(GetBuffer(GetLength() + 1), NULL);
	ReleaseBuffer(-1);
		
	return(dResult);		
}

CStringEx CStringEx::URLEncode()
{
	CStringEx 	sEncoded;
	int			nSrcLen = GetLength();
	int			nIndex;

	for (nIndex = 0; nIndex < nSrcLen; nIndex++)
	{
		TCHAR ch = GetAt(nIndex);
		
		if ((ch > 126)
			 || (ch < 32)
			 || (ch == '?')
			 || (ch == '&')
			 || (ch == '=')
			 || (ch == '+')
			 || (ch == '%'))
		{
			CString sHexCode;
			sHexCode.Format("%%%0.2x", (BYTE) ch);
			sEncoded += sHexCode;
		}
		else
			sEncoded += ch;
	}
	
	return sEncoded;	
}

CStringEx CStringEx::URLDecode()
{
	CStringEx sDecoded;

	int nIndex = 0;
    while (nIndex < GetLength())
	{
		TCHAR chCur = GetAt(nIndex);

		if (chCur == '+')
			sDecoded += ' ';
		else if (chCur == '%')
		{
			CString sValue;
			
			if (IsHexDigit(nIndex + 1))
			{
				nIndex++;
				sValue += GetAt(nIndex);
				if (IsHexDigit(nIndex + 1))
				{
					nIndex++;
					sValue += GetAt(nIndex);
				}
				else
				{
					sDecoded += chCur + sValue;
					goto nextchar;
				}

				int nCode;
				sscanf(sValue, "%x", &nCode);
				sDecoded += (TCHAR) nCode;
			}
			else
				sDecoded += chCur;
		}
		else
			sDecoded += chCur;
nextchar:
		nIndex++;
	}

	return sDecoded;
}
//====== Overridables ======

		
//====== Implementation ======

CStringEx::~CStringEx()
{
}

LPTSTR CStringEx::MakeRoom(int nPos, int nExtra)
// Insert nExtra character slots at nPos and returns
// a pointer to the first inserted slot. ReleaseBuffer
// must be invoked by the caller.
{
	int nLen = GetLength();

	ASSERT(nPos < nLen);

	LPTSTR pBuf = GetBuffer(nLen + nExtra) + nPos;
	memmove(pBuf + nExtra, pBuf, nLen + 1 - nPos);

	return(pBuf);
}