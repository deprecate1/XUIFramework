// Borne.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GuiBaker.h"

#include "MainFrm.h"
#include "BorneDoc.h"

// Our different views
#include "TestView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiBakerApp

BEGIN_MESSAGE_MAP(CGuiBakerApp, CWinApp)
	//{{AFX_MSG_MAP(CGuiBakerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()



// Enum Views
enum eViews 
{
	eBorneView,
};


/////////////////////////////////////////////////////////////////////////////
// CGuiBakerApp construction

CGuiBakerApp theApp(_T("Borne"));
CGuiBakerApp::CGuiBakerApp(LPCTSTR lpszAppName)
	:CWinApp(lpszAppName)
{
	
}


/////////////////////////////////////////////////////////////////////////////
// CGuiBakerApp initialization

BOOL CGuiBakerApp::InitInstance()
{


	AfxOleInit();
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


	// Only one instance allowed
	BOOL bFound=FALSE;
	HANDLE hMutexOneInstance =  CreateMutex(NULL,TRUE,_T("BorneApp27S35D5"));
	if(GetLastError() == ERROR_ALREADY_EXISTS)
		bFound = TRUE;
	if(hMutexOneInstance) 
		ReleaseMutex(hMutexOneInstance);
	if(bFound){
		AfxMessageBox( _T("Application already active.") );	
		return FALSE;
	}

	
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	
	


	// Load global settings
	m_pOpt = CSettings::getInstance();
	m_pOpt->SetAppPath( CMisc::GetAppPath() );
	LoadSettings();
	
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBorneDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CTestView));
	AddDocTemplate(pDocTemplate);



	


	// GUILIB MDI BUG FIX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
	//add this code to make programe work even if it has no document opened
	//pMainFrame->OnUpdateFrameMenu(pMainFrame->m_hMenuDefault);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Don't display a new child window at startup
    //if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	//	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//InitViews();
	
	
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CGuiBakerApp::ExitInstance() 
{	
	
	return CWinApp::ExitInstance();
}





int CGuiBakerApp::LoadSettings()
{
	CString csTmp;
	int		nTmp = 0;

	if (m_pOpt->LoadFile( "GuiBakerConf.xml") == FALSE){
		return FALSE;
	}
	
	// Get global settings
	

	return TRUE;
}










/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGuiBakerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGuiBakerApp message handlers



