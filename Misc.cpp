#include "stdafx.h"
#include ".\misc.h"

CMisc::CMisc(void)
{
}

CMisc::~CMisc(void)
{
}


/*static*/ 
CString CMisc::GetAppPath()
{
	// GET Current PATH
	// Get PATH frm where this DLL is called
		CString csAppPath;
		::GetModuleFileName(NULL, csAppPath.GetBuffer(MAX_PATH), MAX_PATH);
		csAppPath.ReleaseBuffer();

		if (csAppPath.Find('\\') != -1){
			for (int i = csAppPath.GetLength() - 1; i >= 0; i--){
				TCHAR ch = csAppPath[i];
				//csAppPath.Delete(i);
				if (ch == '\\')
					break;
				else
				csAppPath.Delete(i);
			}
		}
		return csAppPath;
}

/*static*/ 
int CMisc::Message(TCHAR* szFmt, ...)
{
	TCHAR	szBuffer[2048];
	va_list args;
	int		bytesWriten = 0;

	va_start(args, szFmt);
	bytesWriten = _vstprintf(szBuffer, szFmt, args);

	va_end(args);

	return AfxMessageBox( szBuffer );
}

/*static*/
BOOL CMisc::PromptForFileName(CString& fileName, CString csFilter, DWORD dwFlags, 
							  BOOL bOpenFileDialog)
{
	CFileDialog dlgFile(bOpenFileDialog);
	CString title;
	if (bOpenFileDialog) title="Ouvrir le fichier"; else title="Enregistrer le fichier";

	dlgFile.m_ofn.Flags |= dwFlags;

	//int nDocType = (pType != NULL) ? *pType : CXIMAGE_FORMAT_BMP;
	//if (nDocType==0) nDocType=1;

	//int nIndex = GetIndexFromType(nDocType, bOpenFileDialog);
	//if (nIndex == -1) nIndex = 0;

	//dlgFile.m_ofn.nFilterIndex = nIndex +1;
	// strDefExt is necessary to hold onto the memory from GetExtFromType

	//dlgFile.m_ofn.lpstrDefExt = strDefExt;
	dlgFile.m_ofn.lpstrFilter = csFilter;
	dlgFile.m_ofn.lpstrTitle  = title;
	dlgFile.m_ofn.lpstrFile   = fileName.GetBuffer(_MAX_PATH);

	BOOL bRet = (dlgFile.DoModal() == IDOK) ? TRUE : FALSE;
	fileName.ReleaseBuffer();
	
	return bRet;
}
/*static*/
void CMisc::SwitchEndianDW(void *Val)
{
	BYTE T;

    T = ((BYTE *)Val)[0];
    ((BYTE *)Val)[0] = ((BYTE *)Val)[3];
    ((BYTE *)Val)[3] = T;
    T = ((BYTE *)Val)[1];
    ((BYTE *)Val)[1] = ((BYTE *)Val)[2];
    ((BYTE *)Val)[2] = T;
}

/*static*/
void CMisc::GetNameFromPath(CString strPath, CString& strName)
{
	CString strDrive, strDir, strExt;

	_tsplitpath((LPCTSTR) strPath,
			    NULL,
			    NULL, 
			    strName.GetBuffer(_MAX_FNAME), 
			    NULL);
	
	strName.ReleaseBuffer(-1);
}