#pragma once

#include "tinyxml.h"



class CSettings
{
public:

	static CSettings *m_staSingle;

	//Application
	CString		m_csAppPath;
	CString		m_csSchedulePath;
	CString		m_csBorneType;
	HWND		m_hWnd;
	LPCTSTR		szXmlSkeleton;

	// XML
	TiXmlDocument m_Doc;
	


	CSettings();
	CSettings(const CSettings&);
    CSettings& operator= (const CSettings&);
	~CSettings();

public:
	static	
		CSettings* getInstance();
	void		SetAppPath( CString csPath);
	 CString	GetAppPath();
	BOOL		LoadFile( LPCTSTR szPath );
	BOOL		SaveSettings();
	int			GetStrSetting( CString csTag,  CString csUniqueAttr,  CString& csValue);
	int			GetNumSetting( CString csTag,  CString csUniqueAttr, int& nValue);
	CString		SetStrSetting( CString csTag,  CString csUniqueAttr  );
	TiXmlDocument*	GetXMLDocument(){return &m_Doc;}

private:
	BOOL		m_bIsOK;
	CString		m_csDocRoot;

};

