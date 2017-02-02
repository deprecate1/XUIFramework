#pragma once

//#define HEX 0
//#define OCT	1
//#define BIN	2

class CLog
{
public:
	typedef enum
	{ 
		HEXMODE = 0,
		OCTMODE,
		BINMODE 
	} ELogMode;

	CLog(void);
	~CLog(void);
static	void	LogString(char* szLogPath, char* szFmt, ...);
static	void	LogArray(char* szLogPath, ELogMode nMode, BYTE* ucTab, int nTabSize);

static CLog*	pThis;

CString			m_csPath;

};
