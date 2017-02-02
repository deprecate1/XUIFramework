#include "StdAfx.h"
#include "Log.h"

CLog::CLog(void)
{
}

CLog::~CLog(void)
{
}


void CLog::LogString(char* szLogPath, char* szFmt, ...)
{
	CFile	File;
	ULONG	bytesWriten;
	CString	csPath;
	char	szBuffer[2048];
	va_list args;
	long	nCR = 0;
	CString csFullPath;

	
	csFullPath = CMisc::GetAppPath() + szLogPath;

	va_start(args, szFmt);
	bytesWriten = vsprintf(szBuffer, szFmt, args);
	
	if( File.Open( csFullPath,
		CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite) )
	{
		File.SeekToEnd();
		File.Write( szBuffer, bytesWriten);
		File.Write("\r\n", 2);
		File.Close();
	}
	else
		AfxMessageBox(_T("Cannot Open Log File"));

	va_end(args);
}

void CLog::LogArray(char* szLogPath, ELogMode nMode, BYTE* Array, int nTabSize)
{
	CFile	File;
	ULONG	i = 0;
	UINT nOpenFlags = 0;
	CString	csPath;
	CString csTmp;
	CString	csLog;

	if (nTabSize <= 0 || nTabSize > 1024)
		return;

	//CSettings* pSettings = CSettings::getInstance();
	//csPath += (pSettings->GetAppPath() ) + szLogPath;
	
	if (nMode == BINMODE)
		nOpenFlags = CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite|CFile::typeBinary;
	else
		nOpenFlags = CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite;

	if( File.Open( szLogPath,nOpenFlags ) ){
		File.SeekToEnd();

		if (nMode == BINMODE){

			for (ULONG j = 0; j < (ULONG)nTabSize; j++){
				if ((j %29) == 0 && j != 0)
					File.Write("\r\n", 2);

				File.Write((char*)&Array[j], 1);
			}
		} 
		else{
			for (i = 0; i < (ULONG)nTabSize; i++){
				if (i%16 == 0 && i!= 0)
					csLog += _T( "\r\n" );

				csTmp.Format( _T("%.2x,"), Array[i] );
				csLog += csTmp; 
			}
			File.Write(csLog, csLog.GetLength() );
		}

		File.Write("\r\n", 2);
		File.Close();
	}
	else
		AfxMessageBox(_T("Cannot Open Log File"));



}