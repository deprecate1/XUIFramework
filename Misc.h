#pragma once

class CMisc
{
public:
	CMisc(void);
	~CMisc(void);

static 
CString	GetAppPath();

static 
int		Message(TCHAR* szFmt, ...);

static
BOOL	PromptForFileName(CString& fileName, CString csFilter, 
						  DWORD dwFlags, BOOL bOpenFileDialog);

static inline
void	SwitchEndianDW(void *Val);

static
void	GetNameFromPath(CString strPath, CString& strName);

};
