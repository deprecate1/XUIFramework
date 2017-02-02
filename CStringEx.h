#ifndef __CStringExt_H__
#define __CStringExt_H__

// Includes
#include "limits.h"

////////////////////////////////////////////////////////////
// Declaration of CStringEx
////////////////////////////////////////////////////////////

class CStringEx : public CString
{
//====== Constructors ======
public:
	CStringEx();
	CStringEx(const CString& stringSrc) : CString(stringSrc) {}
	CStringEx(TCHAR ch, int nRepeat = 1) : CString(ch, nRepeat) {}
	CStringEx(LPCSTR lpsz) : CString(lpsz) {}
	CStringEx(LPCWSTR lpsz) : CString(lpsz) {}
	CStringEx(LPCTSTR lpch, int nLength) : CString(lpch, nLength) {}
	CStringEx(const unsigned char* psz) : CString(psz) {}

	// overloaded assignment operator is not inherited from CString

	const CStringEx& operator=(const CString& stringSrc)
		{CString::operator=(stringSrc); return *this;}
	const CStringEx& operator=(TCHAR ch)
		{CString::operator=(ch); return *this;}
#ifdef _UNICODE
	const CStringEx& operator=(char ch)
		{CString::operator=(ch); return *this;}
#endif
	const CStringEx& operator=(LPCSTR lpsz)
		{CString::operator=(lpsz); return *this;}
	const CStringEx& operator=(LPCWSTR lpsz)
		{CString::operator=(lpsz); return *this;}
	const CStringEx& operator=(const unsigned char* psz)
		{CString::operator=(psz); return *this;}

//====== Attributes ======

public:

protected:

private:


//====== Operations ======

public:

// Inlines 

	CStringEx&	Delete(int nFirst, int nCount = INT_MAX);
	CStringEx&	MakeCharUpper(int nIndex);
	CStringEx&	MakeCharLower(int nIndex);
	CStringEx&	AddSlash(void);
	int			FirstNonSpace() const;
	void		Trim();
	int			FindNoCase(CString sTarget, int nStart = 0);

	//===== Classification functions =====
	BOOL IsTab(int nIndex) const;
	BOOL IsSpace(int nIndex) const;
	BOOL IsAlpha(int nIndex) const;
	BOOL IsAlNum(int nIndex) const;
	BOOL IsBlank(int nIndex) const;
	BOOL IsPunct(int nIndex) const;
	BOOL IsUpper(int nIndex) const;
	BOOL IsLower(int nIndex) const;
	BOOL IsDigit(int nIndex) const;
	BOOL IsHexDigit(int nIndex) const;

// Non-inlines
	

	int			CompareNoCase(CString sTarget, int nCount=0);
	CStringEx	ExpandTabs(int nTabIncr, BOOL bIgnoreQuotes = TRUE, int nMaxSize = INT_MAX);
	CStringEx	CompressSpaces(int nTabIncr, BOOL bIgnoreQuotes);
	CStringEx&	Insert(const CString sSource, int nPos);
	CStringEx&	InsertChar(const TCHAR ch, int nPos);
	CStringEx&	PadRight(const TCHAR ch, int nNewLen);
	CStringEx&	PadLeft(const TCHAR ch, int nNewLen);
	CStringEx&	Overlay(const CString sSource, int nPos);
 	CStringEx&	OverlayChar(const TCHAR ch, int nPos);
	CStringEx&	Replace(CString sToken, CString sNewToken, int nMode, BOOL bCase = FALSE);
	CStringEx&	StripSlash(void);
	CStringEx&	RemoveQuotes();
	CStringEx	URLDecode();
	CStringEx 	URLEncode();

	//===== Path manipulation functions =====
	static CString 	FullPath(CString sRelPath);
	static void		SplitPath(CString	const sPath, 
							  CString&	sDrive, 
							  CString& 	sDir, 
							  CString&	sName, 
							  CString&	sExt,
							  BOOL bIsDir = FALSE);
	static CString 	MakePath(CString sDrive, 
							 CString sDir, 
							 CString sName, 
							 CString sExt);
	CString GetExtension();
	
	CString&	StripToPath();
	CStringEx&	ReplaceNameComponent(const CString sNewComponent, int nComponent);

	CStringEx	GetFirstToken(CString& sDelimiters, int nMaxLen = 255);
	CStringEx	GetNextToken(CString& sDelimiters);
	
	//===== Conversion functions =====
	CStringEx&	ItoA(int value, int radix = 10);
	CStringEx&	LtoA(int value, CString sNum, int radix);
	long		AtoL();
	double		AtoD();

protected:

private:

//====== Overridables ======

//====== Implementation ======
public:
	virtual ~CStringEx();

protected:
	LPTSTR MakeRoom(int nPos, int nExtra);
private:

};

// Inlines

inline CStringEx& CStringEx::Delete(int nFirst, int nCount)
{
	*this = Left(nFirst) + Mid(nFirst + nCount);
	
	return (*this);
}

inline CStringEx& CStringEx::MakeCharUpper(int nIndex)
{
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < GetLength());
	SetAt(nIndex, (TCHAR) CharUpper((LPTSTR) GetAt(nIndex)));

	return (*this);
}

inline CStringEx& CStringEx::MakeCharLower(int nIndex)
{
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < GetLength());

	SetAt(nIndex, (TCHAR) CharLower((LPTSTR) GetAt(nIndex)));

	return (*this);
}

inline int CStringEx::IsTab (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return GetAt(nIndex) == '\t';
}

inline BOOL CStringEx::IsAlpha (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return IsCharAlpha(GetAt(nIndex));
}

inline BOOL CStringEx::IsAlNum (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return IsCharAlphaNumeric(GetAt(nIndex));
}

inline BOOL CStringEx::IsSpace (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return _istspace(GetAt(nIndex));
}

inline BOOL CStringEx::IsBlank (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return GetAt(nIndex) == ' ';
}

inline BOOL CStringEx::IsPunct (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return _istpunct(GetAt(nIndex));
}

inline BOOL CStringEx::IsUpper (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return IsCharUpper(GetAt(nIndex));
}

inline BOOL CStringEx::IsLower (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return IsCharLower(GetAt(nIndex));
}

inline BOOL CStringEx::IsDigit (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return _istdigit(GetAt(nIndex));
}

inline BOOL CStringEx::IsHexDigit (int nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < GetLength());
   return _istxdigit(GetAt(nIndex));
 }

inline CStringEx& CStringEx::AddSlash(void)
// Adds a trailing slash if not present
{
	ASSERT(GetLength() > 0);

	if (GetAt(GetLength() - 1) != '\\')
		*this += '\\';

	return (*this);
}

inline int CStringEx::FirstNonSpace(void) const
// Returns the index of the first non space character
{
	ASSERT(GetLength() > 0);

	int nIndex = -1;
	while (IsSpace(++nIndex));
	return(nIndex);
}

inline void CStringEx::Trim()
{
	TrimLeft();
	TrimRight();
}

#define EX_STRING_REPDRIVE		0
#define EX_STRING_REPDIR		1
#define EX_STRING_REPNAME		2
#define EX_STRING_REPEXT		3
#define EX_STRING_REPFIRST		4
#define EX_STRING_REPLAST		5
#define EX_STRING_REPALL		6


/////////////////////////////////////////////////////////////////////////////
#endif // __CStringExt_H__
