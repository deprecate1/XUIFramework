// COptionTree
//
// License
// -------
// This code is provided "as is" with no expressed or implied warranty.
// 
// You may use this code in a commercial product with or without acknowledgement.
// However you may not sell this code or any modification of this code, this includes 
// commercial libraries and anything else for profit.
//
// I would appreciate a notification of any bugs or bug fixes to help the control grow.
//
// History:
// --------
//	See License.txt for full history information.
//
//
// Copyright (c) 1999-2002 
// ComputerSmarts.net 
// mattrmiller@computersmarts.net

#include "stdafx.h"
#include "Borne.h"
#include "COptionTreeDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCOptionTreeDemoDlg dialog
BEGIN_MESSAGE_MAP(CCOptionTreeDemoDlg, CResizeDlg)
	//{{AFX_MSG_MAP(CCOptionTreeDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_MESSAGE(OT_FS_NOTIFY_APPLY, WM_ApplyButton)
	ON_NOTIFY(OT_NOTIFY_ITEMCHANGED, IDC_OPTIONSTREE_OPTIONS, OnTreeItemChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCOptionTreeDemoDlg::CCOptionTreeDemoDlg(CWnd* pParent /*=NULL*/)
	: CResizeDlg(CCOptionTreeDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCOptionTreeDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_uApplyFontID = 0;
}

void CCOptionTreeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizeDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCOptionTreeDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}



/////////////////////////////////////////////////////////////////////////////
// CCOptionTreeDemoDlg message handlers

BOOL CCOptionTreeDemoDlg::OnInitDialog()
{
	CResizeDlg::OnInitDialog();

	// Declare variables
	COptionTreeItem *otiRoot = NULL;
	COptionTreeItem *otiItem = NULL;
	COptionTreeItemStatic *otiStatic = NULL;
	COptionTreeItemEdit *otiEdit = NULL;
	COptionTreeItemComboBox *otiCombo = NULL;
	COptionTreeItemCheckBox *otiCheck = NULL;
	COptionTreeItemRadio *otiRadio = NULL;
	COptionTreeItemSpinner *otiSpinner = NULL;
	COptionTreeItemColor *otiColor = NULL;
	COptionTreeItemDate *otiDate = NULL;
	COptionTreeItemImage *otiImage = NULL;
	COptionTreeItemFont *otiFont = NULL;
	COptionTreeItemFile *otiFile = NULL;
	COptionTreeItemIPAddress *otiIPAddress = NULL;
	COptionTreeItemHyperLink *oti_Hyperlink = NULL;
	CRect rcClient;
	DWORD dwStyle, dwOptions;
	LOGFONT lfFont, lfDefaultFont;



	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Get log fonts
	GetFont()->GetLogFont(&lfFont);
	GetFont()->GetLogFont(&lfDefaultFont);
	strcpy(lfDefaultFont.lfFaceName, _T("Arial"));

	// Get the clients rectangle
	GetClientRect(rcClient);
	
	// Setup the window style
	dwStyle = WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// Setup the tree options 
	// OT_OPTIONS_SHOWINFOWINDOW
	dwOptions = OT_OPTIONS_SHADEEXPANDCOLUMN | OT_OPTIONS_SHADEROOTITEMS | OT_OPTIONS_SHOWINFOWINDOW;

	// Create tree options
	if (m_otTree.Create(dwStyle, rcClient, this, dwOptions, IDC_OPTIONSTREE_OPTIONS) == FALSE)
	{
		TRACE0("Failed to create options control.\r\n");
		return FALSE;
	}

	// Want to be notified
	m_otTree.SetNotify(TRUE, this);

	// Setup options tree
	// -- Sub Item Test
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Sub Item Test"));
	otiRoot->SetInfoText(_T("This is an example of numerous sub items."));
	// -- Sub Item Test -> Sub Item 1
	otiStatic = (COptionTreeItemStatic*)m_otTree.InsertItem(new COptionTreeItemStatic(), otiRoot);
	otiStatic->SetLabelText(_T("Sub Item 1"));
	otiStatic->SetInfoText(_T("Sub item 1."));
	otiStatic->SetStaticText(_T("I am a sub item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
	}
	// -- Sub Item Test -> Sub Item 2
	otiStatic = (COptionTreeItemStatic*)m_otTree.InsertItem(new COptionTreeItemStatic(), otiStatic);
	otiStatic->SetLabelText(_T("Sub Item 2"));
	otiStatic->SetInfoText(_T("Sub item 2."));
	otiStatic->SetStaticText(_T("I am a sub item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
	}
	// -- Sub Item Test -> Sub Item 3
	otiStatic = (COptionTreeItemStatic*)m_otTree.InsertItem(new COptionTreeItemStatic(), otiStatic);
	otiStatic->SetLabelText(_T("Sub Item 3"));
	otiStatic->SetInfoText(_T("Sub item 3."));
	otiStatic->SetStaticText(_T("I am a sub item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
	}
	// -- Sub Item Test -> Sub Item 4
	otiStatic = (COptionTreeItemStatic*)m_otTree.InsertItem(new COptionTreeItemStatic(), otiStatic);
	otiStatic->SetLabelText(_T("Sub Item 4"));
	otiStatic->SetInfoText(_T("Sub item 4."));
	otiStatic->SetStaticText(_T("I am a sub item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
	}
	// -- Style Test
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Style Test"));
	otiRoot->SetInfoText(_T("This is an example of numerous styles."));
	otiRoot->SetRootBackgroundColor(RGB(0, 150, 200));
	otiRoot->SetLabelTextColor(RGB(0, 0, 0));
	// -- Style Test-> Label Text Color
	otiStatic = (COptionTreeItemStatic*) m_otTree.InsertItem(new COptionTreeItemStatic(), otiRoot);
	otiStatic->SetLabelText(_T("Label Text Color"));
	otiStatic->SetInfoText(_T("This is an example of setting the label text color."));
	otiStatic->SetStaticText(_T("I am a static item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
		otiStatic->SetLabelTextColor(RGB(0, 0, 255));
	}
	// -- Style Test-> Label Background Color
	otiStatic = (COptionTreeItemStatic*) m_otTree.InsertItem(new COptionTreeItemStatic(), otiRoot);
	otiStatic->SetLabelText(_T("Label Background Color"));
	otiStatic->SetInfoText(_T("This is an example of setting the label background color."));
	otiStatic->SetStaticText(_T("I am a static item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
		otiStatic->SetLabelBackgroundColor(RGB(0, 150, 200));
	}
	// -- Style Test-> Text Color
	otiStatic = (COptionTreeItemStatic*) m_otTree.InsertItem(new COptionTreeItemStatic(), otiRoot);
	otiStatic->SetLabelText(_T("Text Color"));
	otiStatic->SetInfoText(_T("This is an example of setting the text color of an item."));
	otiStatic->SetStaticText(_T("I am a static item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
		otiStatic->SetTextColor(RGB(0, 0, 255));
	}
	// -- Style Test-> Background Color
	otiStatic = (COptionTreeItemStatic*) m_otTree.InsertItem(new COptionTreeItemStatic(), otiRoot);
	otiStatic->SetLabelText(_T("Background Color"));
	otiStatic->SetInfoText(_T("This is an example of setting the background color of an item."));
	otiStatic->SetStaticText(_T("I am a static item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
		otiStatic->SetBackgroundColor(RGB(0, 150, 200));
	}

	// -- Static Items
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Static Items"));
	otiRoot->SetInfoText(_T("These are examples of static items."));
	// -- Static Items -> Static Item
	otiStatic = (COptionTreeItemStatic*) m_otTree.InsertItem(new COptionTreeItemStatic(), otiRoot);
	otiStatic->SetLabelText(_T("Static Item"));
	otiStatic->SetInfoText(_T("This is an example of a static item."));
	otiStatic->SetStaticText(_T("I am a static item."));
	if (otiStatic->CreateStaticItem(0) == TRUE)
	{
	}
	// -- Edit Items
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Edit Items"));
	otiRoot->SetInfoText(_T("These are examples of edit items."));
	// -- Edit Items -> Edit Item
	otiEdit = (COptionTreeItemEdit*)m_otTree.InsertItem(new COptionTreeItemEdit(), otiRoot);
	otiEdit->SetLabelText(_T("Edit Item"));
	otiEdit->SetInfoText(_T("This is an example of a edit item."));
	if (otiEdit->CreateEditItem(NULL, NULL) == TRUE)
	{
		otiEdit->SetWindowText(_T("I am a edit item."));	
	}
	// -- Edit Items -> Multiline
	otiEdit = (COptionTreeItemEdit*) m_otTree.InsertItem(new COptionTreeItemEdit(), otiRoot);
	otiEdit->SetLabelText(_T("Multiline"));
	otiEdit->SetInfoText(_T("This is an example of a multiline edit item."));
	if (otiEdit->CreateEditItem(OT_EDIT_MULTILINE, ES_WANTRETURN | ES_AUTOVSCROLL) == TRUE)
	{
		otiEdit->SetWindowText(_T("I am a multiline edit item.\r\nHere is my second line."));
	}
	// -- Edit Items -> Password
	otiEdit = (COptionTreeItemEdit*) m_otTree.InsertItem(new COptionTreeItemEdit(), otiRoot);
	otiEdit->SetLabelText(_T("Password"));
	otiEdit->SetInfoText(_T("This is an example of a password edit item."));
	if (otiEdit->CreateEditItem(OT_EDIT_PASSWORD, NULL) == TRUE)
	{
		otiEdit->SetWindowText(_T("Password"));
	}
	// -- Edit Items -> Numerical
	otiEdit = (COptionTreeItemEdit*) m_otTree.InsertItem(new COptionTreeItemEdit(), otiRoot);
	otiEdit->SetLabelText(_T("Numerical"));
	otiEdit->SetInfoText(_T("This is an example of a numerical edit item."));
	if (otiEdit->CreateEditItem(OT_EDIT_NUMERICAL, NULL) == TRUE)
	{
		otiEdit->SetWindowText(_T("100"));
	}
	// -- Edit Items -> Read Only
	otiEdit = (COptionTreeItemEdit*) m_otTree.InsertItem(new COptionTreeItemEdit(), otiRoot);
	otiEdit->SetLabelText(_T("Read Only"));
	otiEdit->SetInfoText(_T("This is an example of a read only edit item."));
	if (otiEdit->CreateEditItem(NULL, NULL) == TRUE)
	{
		otiEdit->SetWindowText(_T("I am a read only edit."));
		otiEdit->ReadOnly(TRUE);
	}
	// -- Combo Box Items
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Combo Box Items"));
	otiRoot->SetInfoText(_T("These are examples of combo box items."));
	// -- Combo Box Items -> Sorted Combo Box
	otiCombo = (COptionTreeItemComboBox*)m_otTree.InsertItem(new COptionTreeItemComboBox(), otiRoot);
	otiCombo->SetLabelText(_T("Sorted"));
	otiCombo->SetInfoText(_T("This is an example of a sorted combo box item."));
	if (otiCombo->CreateComboItem(CBS_SORT) == TRUE)
	{
		otiCombo->AddString("Blue");
		otiCombo->AddString("Red");
		otiCombo->AddString("Green");
		otiCombo->AddString("Yellow");
		otiCombo->AddString("Purple");
		otiCombo->AddString("Orange");

		otiCombo->SelectString(0, "Blue");
	}
	// -- Combo Box Items -> Combo Box
	otiCombo = (COptionTreeItemComboBox*)m_otTree.InsertItem(new COptionTreeItemComboBox(), otiRoot);
	otiCombo->SetLabelText(_T("Combo Box"));
	otiCombo->SetInfoText(_T("This is an example of a combo box item."));
	if (otiCombo->CreateComboItem(NULL) == TRUE)
	{
		otiCombo->AddString("Yes");
		otiCombo->AddString("No");

		otiCombo->SelectString(0, "No");
	}
	// -- Combo Box Items -> Read Only
	otiCombo = (COptionTreeItemComboBox*)m_otTree.InsertItem(new COptionTreeItemComboBox(), otiRoot);
	otiCombo->SetLabelText(_T("Read Only"));
	otiCombo->SetInfoText(_T("This is an example of a read only combo box item."));
	if (otiCombo->CreateComboItem(NULL) == TRUE)
	{
		otiCombo->AddString("I am a read only combo box.");

		otiCombo->SelectString(0, "I am a read only combo box.");

		otiCombo->ReadOnly(TRUE);
	}
	// -- Check Box Items
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Check Box Items"));
	otiRoot->SetInfoText(_T("These are examples of check box items."));
	// -- Check Box Items-> Without Text
	otiCheck = (COptionTreeItemCheckBox*)m_otTree.InsertItem(new COptionTreeItemCheckBox(), otiRoot);
	otiCheck->SetLabelText(_T("Without Text"));
	otiCheck->SetInfoText(_T("This is an example of a check box item without text."));
	if (otiCheck->CreateCheckBoxItem(FALSE, OT_CHECKBOX_SHOWCHECK) == TRUE)
	{
		otiCheck->SetCheckText(_T("Checked"), _T("UnChecked"));
	}
	// -- Check Box Items -> With Text
	otiCheck = (COptionTreeItemCheckBox*)m_otTree.InsertItem(new COptionTreeItemCheckBox(), otiRoot);
	otiCheck->SetLabelText(_T("With Text"));
	otiCheck->SetInfoText(_T("This is an example of a check box item with text."));
	if (otiCheck->CreateCheckBoxItem(FALSE, OT_CHECKBOX_SHOWCHECK | OT_CHECKBOX_SHOWTEXT) == TRUE)
	{
		otiCheck->SetCheckText(_T("Checked"), _T("UnChecked"));
	}
	// -- Check Box Items -> Without Check Box
	otiCheck = (COptionTreeItemCheckBox*)m_otTree.InsertItem(new COptionTreeItemCheckBox(), otiRoot);
	otiCheck->SetLabelText(_T("Without Check Box"));
	otiCheck->SetInfoText(_T("This is an example of a check box item without check box when not activated."));
	if (otiCheck->CreateCheckBoxItem(FALSE, OT_CHECKBOX_SHOWTEXT) == TRUE)
	{
		otiCheck->SetCheckText(_T("Checked"), _T("UnChecked"));
	}
	// -- Check Box Items -> Read Only
	otiCheck = (COptionTreeItemCheckBox*)m_otTree.InsertItem(new COptionTreeItemCheckBox(), otiRoot);
	otiCheck->SetLabelText(_T("Read Only"));
	otiCheck->SetInfoText(_T("This is an example of a check box item that is read only."));
	if (otiCheck->CreateCheckBoxItem(FALSE, OT_CHECKBOX_SHOWCHECK | OT_CHECKBOX_SHOWTEXT) == TRUE)
	{
		otiCheck->SetCheckText(_T("Checked"), _T("UnChecked"));
		
		otiCheck->ReadOnly(TRUE);
	}
	// -- Radio Items
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Radio Items"));
	otiRoot->SetInfoText(_T("These are examples of radio items."));
	// -- Radio Items -> Radio Items
	otiRadio = (COptionTreeItemRadio*)m_otTree.InsertItem(new COptionTreeItemRadio(), otiRoot);
	otiRadio->SetLabelText(_T("Radio Items"));
	otiRadio->SetInfoText(_T("This is an example of a radio item."));
	if (otiRadio->CreateRadioItem() == TRUE)
	{
		otiRadio->InsertNewRadio(_T("One"), TRUE);
		otiRadio->InsertNewRadio(_T("Two"), FALSE);
		otiRadio->InsertNewRadio(_T("Three"), FALSE);
	}
	// -- Radio Items -> Read Only
	otiRadio = (COptionTreeItemRadio*)m_otTree.InsertItem(new COptionTreeItemRadio(), otiRoot);
	otiRadio->SetLabelText(_T("Read Only"));
	otiRadio->SetInfoText(_T("This is an example of a radio item that is read only."));
	if (otiRadio->CreateRadioItem() == TRUE)
	{
		otiRadio->InsertNewRadio(_T("Cat"), FALSE);
		otiRadio->InsertNewRadio(_T("Dog"), TRUE);

		otiRadio->ReadOnly(TRUE);
	}
	// -- Spinner Items
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Spinner Items"));
	otiRoot->SetInfoText(_T("These are examples of spinner items."));
	// -- Spinner Items -> Wrap Around
	otiSpinner = (COptionTreeItemSpinner*)m_otTree.InsertItem(new COptionTreeItemSpinner(), otiRoot);
	otiSpinner->SetLabelText(_T("Wrap Around"));
	otiSpinner->SetInfoText(_T("This is an example of a spinner item that wraps around."));
	if (otiSpinner->CreateSpinnerItem(OT_EDIT_WRAPAROUND | OT_EDIT_USEREDIT, 80, 1, 100) == TRUE)
	{
	}
	// -- Spinner Items -> No User Edit
	otiSpinner = (COptionTreeItemSpinner*)m_otTree.InsertItem(new COptionTreeItemSpinner(), otiRoot);
	otiSpinner->SetLabelText(_T("No User Edit"));
	otiSpinner->SetInfoText(_T("This is an example of spinner item that disallows user edit."));
	if (otiSpinner->CreateSpinnerItem(OT_EDIT_WRAPAROUND, 80, 1, 100) == TRUE)
	{
	}
	// -- Spinner Items -> No Wrap Around
	otiSpinner = (COptionTreeItemSpinner*)m_otTree.InsertItem(new COptionTreeItemSpinner(), otiRoot);
	otiSpinner->SetLabelText(_T("No Wrap Around"));
	otiSpinner->SetInfoText(_T("This is an example of spinner item that does not wrap around."));
	if (otiSpinner->CreateSpinnerItem(OT_EDIT_USEREDIT, 80, 1, 100) == TRUE)
	{
	}
	// -- Color Items
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Color Items"));
	otiRoot->SetInfoText(_T("These are examples of color items."));
	// -- Color Items -> Hex Color
	otiColor = (COptionTreeItemColor*)m_otTree.InsertItem(new COptionTreeItemColor(), otiRoot);
	otiColor->SetLabelText(_T("Hex Color"));
	otiColor->SetInfoText(_T("This is an example of hexadecimal color item."));
	if (otiColor->CreateColorItem(OT_COLOR_SHOWHEX, RGB(0, 0, 255), RGB(0, 0, 0)) == TRUE)
	{
	}
	// -- Color Items -> RGB Color
	otiColor = (COptionTreeItemColor*)m_otTree.InsertItem(new COptionTreeItemColor(), otiRoot);
	otiColor->SetLabelText(_T("RGB Color"));
	otiColor->SetInfoText(_T("This is an example of RGB color item."));
	if (otiColor->CreateColorItem(NULL, RGB(0, 0, 255), RGB(0, 0, 0)) == TRUE)
	{
	}
	// -- Color Items -> Live Update
	otiColor = (COptionTreeItemColor*)m_otTree.InsertItem(new COptionTreeItemColor(), otiRoot);
	otiColor->SetLabelText(_T("Live Update"));
	otiColor->SetInfoText(_T("This is an example of live update color item."));
	if (otiColor->CreateColorItem(OT_COLOR_SHOWHEX | OT_COLOR_LIVEUPDATE, RGB(255, 100, 255), RGB(0, 0, 0)) == TRUE)
	{
	}
	// -- Color Items -> Read Only
	otiColor = (COptionTreeItemColor*)m_otTree.InsertItem(new COptionTreeItemColor(), otiRoot);
	otiColor->SetLabelText(_T("Read Only"));
	otiColor->SetInfoText(_T("This is an example of read only color item."));
	if (otiColor->CreateColorItem(OT_COLOR_SHOWHEX | OT_COLOR_LIVEUPDATE, RGB(130, 100, 255), RGB(0, 0, 0)) == TRUE)
	{
		otiColor->ReadOnly(TRUE);
	}
	// -- Date and Time
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Date and Time"));
	otiRoot->SetInfoText(_T("These are examples of date and time items."));
	// -- Date and Time -> Date
	otiDate = (COptionTreeItemDate*)m_otTree.InsertItem(new COptionTreeItemDate(), otiRoot);
	otiDate->SetLabelText(_T("Date"));
	otiDate->SetInfoText(_T("This is an example of a date item."));
	if (otiDate->CreateDateItem(_T("ddd, MMM d, yyyy"), DTS_LONGDATEFORMAT) == TRUE)
	{
	}
	// -- Date and Time -> Time
	otiDate = (COptionTreeItemDate*)m_otTree.InsertItem(new COptionTreeItemDate(), otiRoot);
	otiDate->SetLabelText(_T("Time"));
	otiDate->SetInfoText(_T("This is an example of a time item."));
	if (otiDate->CreateDateItem(_T("hh:mm tt"), DTS_TIMEFORMAT | DTS_UPDOWN) == TRUE)
	{
	}
	// -- Date and Time -> Read Only
	otiDate = (COptionTreeItemDate*)m_otTree.InsertItem(new COptionTreeItemDate(), otiRoot);
	otiDate->SetLabelText(_T("Read Only"));
	otiDate->SetInfoText(_T("This is an example of a time item that is read only."));
	if (otiDate->CreateDateItem(_T("hh:mm tt"), DTS_TIMEFORMAT | DTS_UPDOWN) == TRUE)
	{
		otiDate->ReadOnly(TRUE);
	}
	// -- Images
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Images"));
	otiRoot->SetInfoText(_T("These are examples of image items."));
	// -- Images -> 16x16
	otiImage = (COptionTreeItemImage*)m_otTree.InsertItem(new COptionTreeItemImage(), otiRoot);
	otiImage->SetLabelText(_T("16x16"));
	otiImage->SetInfoText(_T("This is an example of a 16x16 image item."));
	
	// -- Images -> 32x32
	otiImage = (COptionTreeItemImage*)m_otTree.InsertItem(new COptionTreeItemImage(), otiRoot);
	otiImage->SetLabelText(_T("32x32"));
	otiImage->SetInfoText(_T("This is an example of a 32x32 image item."));
	
	// -- Images -> 48x48
	otiImage = (COptionTreeItemImage*)m_otTree.InsertItem(new COptionTreeItemImage(), otiRoot);
	otiImage->SetLabelText(_T("48x48"));
	otiImage->SetInfoText(_T("This is an example of a 48x48 image item."));
	
	// -- Images -> Read Only
	otiImage = (COptionTreeItemImage*)m_otTree.InsertItem(new COptionTreeItemImage(), otiRoot);
	otiImage->SetLabelText(_T("Read Only"));
	otiImage->SetInfoText(_T("This is an example of a read only image item."));
	
	// -- Fonts
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Fonts"));
	otiRoot->SetInfoText(_T("These are examples of font items."));
	// -- Fonts -> True Type
	otiFont = (COptionTreeItemFont*)m_otTree.InsertItem(new COptionTreeItemFont(), otiRoot);
	otiFont->SetLabelText(_T("True Type"));
	otiFont->SetInfoText(_T("This is an example of a font item with only true type fonts."));
	if (otiFont->CreateFontItem(lfFont, RGB(0, 0, 255), OT_FS_TTONLY) == TRUE)
	{
	}
	// -- Fonts -> Default Button
	otiFont = (COptionTreeItemFont*)m_otTree.InsertItem(new COptionTreeItemFont(), otiRoot);
	otiFont->SetLabelText(_T("Default Button"));
	otiFont->SetInfoText(_T("This is an example of a font item with a default button."));
	if (otiFont->CreateFontItem(lfFont, RGB(0, 0, 255), lfDefaultFont, RGB(0, 0, 0), OT_FS_USEDEFAULT) == TRUE)
	{
	}
	// -- Fonts -> Limited Styles
	otiFont = (COptionTreeItemFont*)m_otTree.InsertItem(new COptionTreeItemFont(), otiRoot);
	otiFont->SetLabelText(_T("Limited Styles"));
	otiFont->SetInfoText(_T("This is an example of a font item with a limited styles."));
	if (otiFont->CreateFontItem(lfFont, RGB(0, 0, 0), lfDefaultFont, RGB(0, 0, 0), OT_FS_USEDEFAULT | OT_FS_NOTEXTCOLOR | OT_FS_NOSTYLES | OT_FS_NOEFFECTS) == TRUE)
	{
	}
	// -- Fonts -> Apply Button
	otiFont = (COptionTreeItemFont*)m_otTree.InsertItem(new COptionTreeItemFont(), otiRoot);
	otiFont->SetLabelText(_T("Apply Button"));
	otiFont->SetInfoText(_T("This is an example of a font item with a apply button."));
	if (otiFont->CreateFontItem(lfFont, RGB(0, 0, 0), lfDefaultFont, RGB(0, 0, 0), OT_FS_USEDEFAULT | OT_FS_USEAPPLY) == TRUE)
	{
		otiFont->SetApplyWindow(this);
		m_uApplyFontID = otiFont->GetCtrlID();
	}	
	// -- Fonts -> Background Color
	otiFont = (COptionTreeItemFont*)m_otTree.InsertItem(new COptionTreeItemFont(), otiRoot);
	otiFont->SetLabelText(_T("Background Color"));
	otiFont->SetInfoText(_T("This is an example of a font item with a different background color."));
	if (otiFont->CreateFontItem(lfFont, RGB(255, 255, 255), lfDefaultFont, RGB(255, 255, 255), OT_FS_USEDEFAULT) == TRUE)
	{
		otiFont->SetBackgroundColor(RGB(192, 192, 192));
	}
	// -- Fonts -> Read Only
	otiFont = (COptionTreeItemFont*)m_otTree.InsertItem(new COptionTreeItemFont(), otiRoot);
	otiFont->SetLabelText(_T("Read Only"));
	otiFont->SetInfoText(_T("This is an example of a font item that is read only."));
	if (otiFont->CreateFontItem(lfFont, RGB(255, 255, 255), lfDefaultFont, RGB(255, 255, 255), OT_FS_USEDEFAULT) == TRUE)
	{
		otiFont->ReadOnly(TRUE);
	}
	// -- Files and Folders
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Files and Folders"));
	otiRoot->SetInfoText(_T("These are examples of file and folders items."));
	// -- Files and Folders -> File Full Path
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("File Full Path"));
	otiFile->SetInfoText(_T("This is an example of a file item displaying the full path."));
	if (otiFile->CreateFileItem(_T("C:\\AutoExec.Bat"), _T(""), _T("All files|*.*|"), OT_FILE_OPENDIALOG | OT_FILE_SHOWFULLPATH, OFN_OVERWRITEPROMPT) == TRUE)
	{
	}
	// -- Files and Folders -> File Name
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("File Name"));
	otiFile->SetInfoText(_T("This is an example of a file item displaying the full name."));
	if (otiFile->CreateFileItem(_T("C:\\AutoExec.Bat"), _T(""), _T("All files|*.*|"), OT_FILE_OPENDIALOG | OT_FILE_SHOWFILENAME, OFN_OVERWRITEPROMPT) == TRUE)
	{
	}
	// -- Files and Folders -> File Title
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("File Title"));
	otiFile->SetInfoText(_T("This is an example of a file item displaying the full title."));
	if (otiFile->CreateFileItem(_T("C:\\AutoExec.Bat"), _T(""), _T("All files|*.*|"), OT_FILE_OPENDIALOG | OT_FILE_SHOWFILETITLE, OFN_OVERWRITEPROMPT) == TRUE)
	{
	}
	// -- Files and Folders -> File Extention
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("File Extention"));
	otiFile->SetInfoText(_T("This is an example of a file item displaying the full extention."));
	if (otiFile->CreateFileItem(_T("C:\\AutoExec.Bat"), _T(""), _T("All files|*.*|"), OT_FILE_OPENDIALOG | OT_FILE_SHOWFILEEXT, OFN_OVERWRITEPROMPT) == TRUE)
	{
	}
	// -- Files and Folders -> File Directory
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("File Directory"));
	otiFile->SetInfoText(_T("This is an example of a file item displaying the full directory."));
	if (otiFile->CreateFileItem(_T("C:\\AutoExec.Bat"), _T(""), _T("All files|*.*|"), OT_FILE_OPENDIALOG | OT_FILE_SHOWFILEDIR, OFN_OVERWRITEPROMPT) == TRUE)
	{
	}
	// -- Files and Folders -> File Drive
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("File Drive"));
	otiFile->SetInfoText(_T("This is an example of a file item displaying the full drive."));
	if (otiFile->CreateFileItem(_T("C:\\AutoExec.Bat"), _T(""), _T("All files|*.*|"), OT_FILE_OPENDIALOG | OT_FILE_SHOWFILEDRIVE, OFN_OVERWRITEPROMPT) == TRUE)
	{
	}
	// -- Files and Folders -> Multi Select
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("Multi Select"));
	otiFile->SetInfoText(_T("This is an example of a file item allowing multi file selection."));
	if (otiFile->CreateFileItem(_T("C:\\AutoExec.Bat"), _T(""), _T("All files|*.*|"), OT_FILE_OPENDIALOG | OT_FILE_SHOWFULLPATH, OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT) == TRUE)
	{
	}
	// -- Files and Folders -> Folder Select
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("Folder Select"));
	otiFile->SetInfoText(_T("This is an example of a file item allowing folder selection."));
	if (otiFile->CreateFileItem(_T("C:\\Program Files"), _T(""), _T(""), OT_FILE_SELECTDIALOG | OT_FILE_SHOWFULLPATH, 0x40 | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS) == TRUE)
	{
	}
	// -- Files and Folders -> Read Only
	otiFile = (COptionTreeItemFile*)m_otTree.InsertItem(new COptionTreeItemFile(), otiRoot);
	otiFile->SetLabelText(_T("Read Only"));
	otiFile->SetInfoText(_T("This is an example of a file item that is read only."));
	if (otiFile->CreateFileItem(_T("C:\\AutoExec.Bat"), _T(""), _T("All files|*.*|"), OT_FILE_OPENDIALOG | OT_FILE_SHOWFULLPATH, OFN_OVERWRITEPROMPT) == TRUE)
	{
		otiFile->ReadOnly(TRUE);
	}
	// -- IP Address
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("IP Address"));
	otiRoot->SetInfoText(_T("These are examples of IP address items."));
	// -- IP Address -> Normal
	otiIPAddress = (COptionTreeItemIPAddress*)m_otTree.InsertItem(new COptionTreeItemIPAddress(), otiRoot);
	otiIPAddress->SetLabelText(_T("Normal"));
	otiIPAddress->SetInfoText(_T("This is an example of a normal IP address."));
	if (otiIPAddress->CreateIPAddressItem(0) == TRUE)
	{
		otiIPAddress->SetAddress(1, 2, 3, 4);
	}
	// -- IP Address -> Read Only
	otiIPAddress = (COptionTreeItemIPAddress*)m_otTree.InsertItem(new COptionTreeItemIPAddress(), otiRoot);
	otiIPAddress->SetLabelText(_T("Read Only"));
	otiIPAddress->SetInfoText(_T("This is an example of a read only IP address."));
	if (otiIPAddress->CreateIPAddressItem(0) == TRUE)
	{
		otiIPAddress->SetAddress(4, 3, 2, 1);
		otiIPAddress->ReadOnly(TRUE);
	}
	// -- Hyperlink
	otiRoot = m_otTree.InsertItem(new COptionTreeItem());
	otiRoot->SetLabelText(_T("Hyperlink"));
	otiRoot->SetInfoText(_T("These are examples of hyperlink items."));
	// -- Hyperlink -> Hover
	oti_Hyperlink = (COptionTreeItemHyperLink*)m_otTree.InsertItem(new COptionTreeItemHyperLink(), otiRoot);
	oti_Hyperlink->SetLabelText(_T("Hover"));
	oti_Hyperlink->SetInfoText(_T("This is an example of a hyperlink with the hover option."));
	if (oti_Hyperlink->CreateHyperlinkItem(OT_HL_HOVER, _T("http://www.computersmarts.net"), RGB(0, 0, 255), RGB(150, 0, 150), RGB(255, 0, 255)) == TRUE)
	{
	}
	// -- Hyperlink -> Visited
	oti_Hyperlink = (COptionTreeItemHyperLink*)m_otTree.InsertItem(new COptionTreeItemHyperLink(), otiRoot);
	oti_Hyperlink->SetLabelText(_T("Visited"));
	oti_Hyperlink->SetInfoText(_T("This is an example of a hyperlink with the visited option."));
	if (oti_Hyperlink->CreateHyperlinkItem(OT_HL_HOVER | OT_HL_VISITED, _T("http://www.computersmarts.net"), RGB(0, 0, 255), RGB(150, 0, 150), RGB(255, 0, 255)) == TRUE)
	{
	}
	// -- Hyperlink -> Underlined Hover
	oti_Hyperlink = (COptionTreeItemHyperLink*)m_otTree.InsertItem(new COptionTreeItemHyperLink(), otiRoot);
	oti_Hyperlink->SetLabelText(_T("Underlined Hover"));
	oti_Hyperlink->SetInfoText(_T("This is an example of a hyperlink with underlined text when hovered."));
	if (oti_Hyperlink->CreateHyperlinkItem(OT_HL_HOVER | OT_HL_UNDERLINEHOVER, _T("http://www.computersmarts.net"), RGB(0, 0, 255), RGB(150, 0, 150), RGB(255, 0, 255)) == TRUE)
	{
	}		
	// -- Hyperlink -> Underlined
	oti_Hyperlink = (COptionTreeItemHyperLink*)m_otTree.InsertItem(new COptionTreeItemHyperLink(), otiRoot);
	oti_Hyperlink->SetLabelText(_T("Underlined"));
	oti_Hyperlink->SetInfoText(_T("This is an example of a hyperlink with underlined text."));
	if (oti_Hyperlink->CreateHyperlinkItem(OT_HL_HOVER | OT_HL_UNDERLINE, _T("http://www.computersmarts.net"), RGB(0, 0, 255), RGB(150, 0, 150), RGB(255, 0, 255)) == TRUE)
	{
	}	
	// -- Hyperlink -> Read Only
	oti_Hyperlink = (COptionTreeItemHyperLink*)m_otTree.InsertItem(new COptionTreeItemHyperLink(), otiRoot);
	oti_Hyperlink->SetLabelText(_T("Read Only"));
	oti_Hyperlink->SetInfoText(_T("This is an example of a hyperlink that is read only."));
	if (oti_Hyperlink->CreateHyperlinkItem(OT_HL_HOVER, _T("http://www.computersmarts.net"), RGB(0, 0, 255), RGB(150, 0, 150), RGB(255, 0, 255)) == TRUE)
	{
		oti_Hyperlink->ReadOnly(TRUE);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCOptionTreeDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
		CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCOptionTreeDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CResizeDlg::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCOptionTreeDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CCOptionTreeDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// Don't exit when press Enter of Esc
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CCOptionTreeDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	// Resize the control
	if ((cx > 0) && (cy > 0))
	{
		if (::IsWindow(m_otTree.GetSafeHwnd()))
		{
			m_otTree.MoveWindow(0, 0, cx, cy);
		}
	}
	
	CDialog::OnSize(nType, cx, cy);	
}

LRESULT CCOptionTreeDemoDlg::WM_ApplyButton(WPARAM wParam, LPARAM lParam)
{
	// Declare variables
	UINT uID;

	// Get incoming ID
	uID = (UINT) wParam;

	// See what ID it is
	if (uID == m_uApplyFontID)
	{
		OnApplyFont(lParam);
	}

	return 0;
}

void CCOptionTreeDemoDlg::OnTreeItemChanged(NMHDR* pNotifyStruct, LRESULT* plResult)
{
	// Declare variables
	LPNMOPTIONTREE pNMOptionTree = (LPNMOPTIONTREE)pNotifyStruct;

	if (pNMOptionTree == NULL)
		*plResult = 1;
	else
		*plResult = 0;
	return;

	//// Validate MFC < 7
	//if (pNMOptionTree == NULL)
	//{
	//	return 1;
	//}
	//return 0;
}

void CCOptionTreeDemoDlg::OnApplyFont(LPARAM lParam)
{
	// Note depending on if you are usng OT_FS_USECHARFORMAT or not
	// for this item a LOGFONT or CHARFORMAT font is sent.

	// Declare variables
	PLOGFONTA lf;

	// Get font
	lf = (PLOGFONTA) lParam;

	MessageBox("Include apply code to be able to accept font chages live.", "COptionTreeDemo", MB_OK);
}

void CCOptionTreeDemoDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{		
	// Set minimum and maximum dimensions
	lpMMI->ptMinTrackSize.x = 425;
	lpMMI->ptMinTrackSize.y = 450;

	CDialog::OnGetMinMaxInfo(lpMMI);
}
