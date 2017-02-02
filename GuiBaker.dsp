# Microsoft Developer Studio Project File - Name="Borne" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Borne - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GuiBaker.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GuiBaker.mak" CFG="Borne - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Borne - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Borne - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Borne - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "XuiWnd" /I "widgets" /I "Database" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Borne - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "XuiWnd" /I "Widgets" /I "Database" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Borne - Win32 Release"
# Name "Borne - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Borne.rc
# End Source File
# Begin Source File

SOURCE=.\BorneDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiBaker.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BorneDoc.h
# End Source File
# Begin Source File

SOURCE=.\GuiBaker.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\ABTOF Logo.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\banner.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Borne.ico
# End Source File
# Begin Source File

SOURCE=.\res\Borne.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BorneDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\checkcurs.cur
# End Source File
# Begin Source File

SOURCE=.\res\combocurs.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\datecurs.cur
# End Source File
# Begin Source File

SOURCE=.\res\dice.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dyntoolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\editcurs.cur
# End Source File
# Begin Source File

SOURCE=.\res\editorto.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FlecheBN.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FlecheNB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\groupcurs.cur
# End Source File
# Begin Source File

SOURCE=.\res\images_n.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\key9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\KeyDot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\labelcurs.cur
# End Source File
# Begin Source File

SOURCE=.\res\logo_francecard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\multieditcurs.cur
# End Source File
# Begin Source File

SOURCE=.\res\radiocurs.cur
# End Source File
# Begin Source File

SOURCE=.\res\ratp1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RATP2004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\splash1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SplashScreen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\test.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\user1.ico
# End Source File
# Begin Source File

SOURCE=.\res\vetement.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xuicontr.bmp
# End Source File
# End Group
# Begin Group "Widgets"

# PROP Default_Filter ""
# Begin Group "CxStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\CxStatic\CxStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CxStatic\CxStatic.h
# End Source File
# End Group
# Begin Group "CxPicture"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\CxPicture\CxPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CxPicture\CxPicture.h
# End Source File
# End Group
# Begin Group "CStaticHtml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\CStaticHtml\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CStaticHtml\CeXDib.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\CStaticHtml\PPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CStaticHtml\PPDrawManager.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\CStaticHtml\PPHtmlDrawer.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CStaticHtml\PPHtmlDrawer.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\CStaticHtml\PPHtmlStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CStaticHtml\PPHtmlStatic.h
# End Source File
# End Group
# Begin Group "CxImage"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\CxImage\ximacfg.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\CxImage\ximage.h
# End Source File
# Begin Source File

SOURCE=.\lib\msw\jpeg.lib
# End Source File
# Begin Source File

SOURCE=.\lib\msw\png.lib
# End Source File
# Begin Source File

SOURCE=.\lib\msw\zlib.lib
# End Source File
# Begin Source File

SOURCE=.\lib\msw\cximage.lib
# End Source File
# End Group
# Begin Group "CResizeDlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\CResizeDlg\ResizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CResizeDlg\ResizeDlg.h
# End Source File
# End Group
# Begin Group "CxCommon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\CxCommon\CxCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CxCommon\CxCommon.h
# End Source File
# End Group
# Begin Group "CxFrame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\CxFrame\CxFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\CxFrame\CxFrame.h
# End Source File
# End Group
# Begin Group "TreePropSheetEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\hookwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\hookwnd.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\memdc.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrame.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrameBordered.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrameBordered.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrameDefault.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrameDefault.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrameEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrameEx.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrameOffice2003.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\PropPageFrameOffice2003.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableDialog.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableGrip.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableGrip.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableLayout.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableMinMax.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableMinMax.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableMsgSupport.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableMsgSupport.inl
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizablePage.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizablePage.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableSheet.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableState.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ResizableState.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ThemeLibEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\ThemeLibEx.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheet.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetBase.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetBordered.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetBordered.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetEx.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetOffice2003.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetOffice2003.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetResizableLibHook.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetResizableLibHook.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetSplitter.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\TreePropSheetEx\TreePropSheetTreeCtrl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Widgets\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\Rgbcolor.h
# End Source File
# Begin Source File

SOURCE=.\Widgets\StdGrfx.cpp
# End Source File
# Begin Source File

SOURCE=.\Widgets\StdGrfx.h
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CStringEx.cpp
# End Source File
# Begin Source File

SOURCE=.\CStringEx.h
# End Source File
# Begin Source File

SOURCE=.\Misc.cpp
# End Source File
# Begin Source File

SOURCE=.\Misc.h
# End Source File
# End Group
# Begin Group "Settings"

# PROP Default_Filter ""
# Begin Group "PPgGeneral"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PPgGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\PPgGeneral.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Settings.cpp
# End Source File
# Begin Source File

SOURCE=.\Settings.h
# End Source File
# End Group
# Begin Group "XML"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBase64Coding.cpp
# End Source File
# Begin Source File

SOURCE=.\CBase64Coding.h
# End Source File
# Begin Source File

SOURCE=.\tinystr.h
# End Source File
# Begin Source File

SOURCE=.\tinyxml.h
# End Source File
# Begin Source File

SOURCE=.\lib\msw\tinyxml.lib
# End Source File
# End Group
# Begin Group "Log"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# End Group
# Begin Group "WFC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WFC\wfc_validate.h
# End Source File
# End Group
# Begin Group "XuiWnd"

# PROP Default_Filter ""
# Begin Group "XuiProperties"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUIPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIPropDlg.h
# End Source File
# End Group
# Begin Group "XuiElements"

# PROP Default_Filter ""
# Begin Group "XuiElement"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUIElement.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIElement.h
# End Source File
# End Group
# Begin Group "XuiPicture"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUIPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIPicture.h
# End Source File
# End Group
# Begin Group "XuiStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUIStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIStatic.h
# End Source File
# End Group
# Begin Group "XuiLiteHtml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUILiteHtml.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUILiteHtml.h
# End Source File
# End Group
# Begin Group "XuiFrame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUIFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIFrame.h
# End Source File
# End Group
# Begin Group "XuiEdit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUIEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIEdit.h
# End Source File
# End Group
# End Group
# Begin Group "XuiTracker"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUITracker.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUITracker.h
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUITrackerObject.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUITrackerObject.h
# End Source File
# End Group
# Begin Group "XuiToolBar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XuiWnd\GUIControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIControlBar.h
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIDroptarget.cpp
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\GUIDroptarget.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\XuiWnd\XuiScreen.h
# End Source File
# Begin Source File

SOURCE=.\XuiWnd\XuiWnd.h
# End Source File
# End Group
# End Target
# End Project
