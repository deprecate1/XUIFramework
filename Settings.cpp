#include "stdafx.h"
#include "settings.h"

CSettings::CSettings(void)
{
	// Squelette Fichier conf XML
	szXmlSkeleton =
		"<?xml version=\"1.0\">\n"
		"<!-- Fichier de conf -->"
		"<GuiBaker>"
		"<Options>"
		"</Options>"
		"</GuiBaker>";

	m_bIsOK		= FALSE;
	m_csDocRoot = _T("");

	m_csAppPath			= _T("");



	//CMisc::Message("Constructeur settings");

	//Init first activity to 0
	//CurrentActivity.nActID = 0;
}

CSettings::~CSettings(void)
{
}

CSettings* CSettings::m_staSingle = NULL;
CSettings* CSettings::getInstance()
{
	if (m_staSingle == NULL)
	{
		m_staSingle = new CSettings;
	}
	return m_staSingle;
}


BOOL CSettings::LoadFile( LPCTSTR szPath )
{
	 CString csFullPath;

	csFullPath =  m_csAppPath + szPath;

	if (m_Doc.LoadFile( csFullPath ) == false){

		CMisc::Message(
		"Cannot Open File %s.\n"
		"Creating a default configuration file",
			csFullPath);

		m_Doc.Parse( szXmlSkeleton );
		m_Doc.SaveFile();

		m_Doc.LoadFile( csFullPath );
		

		m_bIsOK = FALSE;
	}

	m_csDocRoot = m_Doc.RootElement()->Value();
	m_bIsOK = TRUE;

	return m_bIsOK;
}

int	CSettings::GetStrSetting( CString csTag,  CString csAttr,  CString& csValue)
{
	if ( !m_bIsOK )
		return 0;

	TiXmlElement*	pElement = NULL;
	TiXmlHandle		docH( &m_Doc );
	 CString		csTmp;

	// Only for DocRoot Attribute
	if (!csTag.CompareNoCase(m_csDocRoot)){
		pElement = docH.FirstChild( m_csDocRoot ).Element();
		csValue = pElement->Attribute((LPCTSTR)csAttr);
		csValue.TrimLeft();csValue.TrimRight();
		return 1;
	}


	// Go directly to <csTag> section
	pElement = docH.FirstChild( m_csDocRoot ).FirstChild( csTag ).Element();
	if (pElement){
		csValue = pElement->Attribute((LPCTSTR)csAttr);
		csValue.TrimLeft();csValue.TrimRight();
		return 1;
	}
	else{
		return -1;
	}

	return 1;
}

int	CSettings::GetNumSetting( CString csTag,  CString csAttr, int& nValue )
{
	if ( !m_bIsOK )
		return 0;

	TiXmlElement*	pElement = NULL;
	TiXmlHandle		docH( &m_Doc );
	 CString			csTmp;

	// Only for DocRoot Attribute
	if (!csTag.CompareNoCase(m_csDocRoot)){
		pElement = docH.FirstChild( m_csDocRoot ).Element();
		csTmp = pElement->Attribute((LPCTSTR)csAttr);
		csTmp.TrimLeft();csTmp.TrimRight();
		nValue = atoi( csTmp );
		return 1;
	}


	// Go directly to <csTag> section
	pElement = docH.FirstChild( m_csDocRoot ).FirstChild( csTag ).Element();
	if (pElement){
		csTmp = pElement->Attribute((LPCTSTR)csAttr);
			csTmp.TrimLeft();csTmp.TrimRight();
		nValue = atoi( csTmp );
	}
	else{
		return -1;
	}

	return 1;
}




void CSettings::SetAppPath( CString csAppPath)
{
	m_csAppPath = csAppPath;
}

 CString CSettings::GetAppPath()
{
	return m_csAppPath;
}