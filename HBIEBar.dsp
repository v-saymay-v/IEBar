# Microsoft Developer Studio Project File - Name="HBIEBar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** ï“èWÇµÇ»Ç¢Ç≈Ç≠ÇæÇ≥Ç¢ **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=HBIEBar - Win32 Debug
!MESSAGE Ç±ÇÍÇÕóLå¯Ç»“≤∏Ãß≤ŸÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒÅB Ç±ÇÃÃﬂ€ºﬁ™∏ƒÇÀﬁŸƒﬁÇ∑ÇÈÇΩÇﬂÇ…ÇÕ NMAKE ÇégópÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
!MESSAGE [“≤∏Ãß≤ŸÇÃ¥∏ΩŒﬂ∞ƒ] ∫œ›ƒﬁÇégópÇµÇƒé¿çsÇµÇƒÇ≠ÇæÇ≥Ç¢
!MESSAGE 
!MESSAGE NMAKE /f "HBIEBar.mak".
!MESSAGE 
!MESSAGE NMAKE ÇÃé¿çséûÇ…ç\ê¨ÇéwíËÇ≈Ç´Ç‹Ç∑
!MESSAGE ∫œ›ƒﬁ ◊≤›è„Ç≈œ∏€ÇÃê›íËÇíËã`ÇµÇ‹Ç∑ÅBó·:
!MESSAGE 
!MESSAGE NMAKE /f "HBIEBar.mak" CFG="HBIEBar - Win32 Debug"
!MESSAGE 
!MESSAGE ëIëâ¬î\Ç»ÀﬁŸƒﬁ ”∞ƒﬁ:
!MESSAGE 
!MESSAGE "HBIEBar - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" óp)
!MESSAGE "HBIEBar - Win32 Release" ("Win32 (x86) Dynamic-Link Library" óp)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/HotBizToolBar/HBIEBar", OPWAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HBIEBar - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "HBIEBar___Win32_Debug"
# PROP BASE Intermediate_Dir "HBIEBar___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /I "..\openssl-0.9.6l\inc32" /I "HBBCommon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I "..\openssl-0.9.6l\inc32" /I "HBBCommon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D WINVER=0x0500 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib wsock32.lib Version.lib Winmm.lib libeay32.lib ssleay32.lib HBBCommon.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\openssl-0.9.6l\out32dll" /libpath:"HBBCommon\Debug"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib Version.lib Winmm.lib HBBCommon.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\openssl-0.9.6l\out32dll" /libpath:"HBBCommon\Debug"
# Begin Custom Build - ìoò^ÇçsÇ¡ÇƒÇ¢Ç‹Ç∑
OutDir=.\Debug
TargetPath=.\Debug\HBIEBar.dll
InputPath=.\Debug\HBIEBar.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo åxçê : Windows 95 Ç… Unicode DLL Çìoò^Ç∑ÇÈÇ±Ç∆ÇÕÇ≈Ç´Ç‹ÇπÇÒ 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "HBIEBar - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "HBIEBar___Win32_Release"
# PROP BASE Intermediate_Dir "HBIEBar___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /I "..\openssl-0.9.6l\inc32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I "..\openssl-0.9.6l\inc32" /I "HBBCommon" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D WINVER=0x0500 /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib wsock32.lib Version.lib Winmm.lib libeay32.lib ssleay32.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"..\openssl-0.9.6l\out32dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib Version.lib Winmm.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"..\openssl-0.9.6l\out32dll"
# Begin Custom Build - ìoò^ÇçsÇ¡ÇƒÇ¢Ç‹Ç∑
OutDir=.\Release
TargetPath=.\Release\HBIEBar.dll
InputPath=.\Release\HBIEBar.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo åxçê : Windows 95 Ç… Unicode DLL Çìoò^Ç∑ÇÈÇ±Ç∆ÇÕÇ≈Ç´Ç‹ÇπÇÒ 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "HBIEBar - Win32 Debug"
# Name "HBIEBar - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\HBIEBar.cpp
# End Source File
# Begin Source File

SOURCE=.\HBIEBar.def
# End Source File
# Begin Source File

SOURCE=.\HBIEBar.idl
# ADD MTL /tlb ".\HBIEBar.tlb" /h "HBIEBar.h" /iid "HBIEBar_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\HBIEBar.rc
# End Source File
# Begin Source File

SOURCE=.\HostPage.cpp
# End Source File
# Begin Source File

SOURCE=.\HotBizBar.cpp
# End Source File
# Begin Source File

SOURCE=.\IconPage.cpp
# End Source File
# Begin Source File

SOURCE=.\kanji.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MFToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\ReflectionWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VersionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WaitDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\HBIEBar.h
# End Source File
# Begin Source File

SOURCE=.\HostPage.h
# End Source File
# Begin Source File

SOURCE=.\HotBizBar.h
# End Source File
# Begin Source File

SOURCE=.\IconPage.h
# End Source File
# Begin Source File

SOURCE=.\kanji.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\MFToolbar.h
# End Source File
# Begin Source File

SOURCE=.\ReflectionWnd.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VersionDlg.h
# End Source File
# Begin Source File

SOURCE=.\WaitDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\address.ico
# End Source File
# Begin Source File

SOURCE=.\address_hot.ico
# End Source File
# Begin Source File

SOURCE=.\bulletin.ico
# End Source File
# Begin Source File

SOURCE=.\bulletin_hot.ico
# End Source File
# Begin Source File

SOURCE=.\cabinet.ico
# End Source File
# Begin Source File

SOURCE=.\cabinet_hot.ico
# End Source File
# Begin Source File

SOURCE=.\circulat.ico
# End Source File
# Begin Source File

SOURCE=.\circulate_hot.ico
# End Source File
# Begin Source File

SOURCE=.\forum.ico
# End Source File
# Begin Source File

SOURCE=.\forum_hot.ico
# End Source File
# Begin Source File

SOURCE=.\gotime.ico
# End Source File
# Begin Source File

SOURCE=.\hbiebar.ico
# End Source File
# Begin Source File

SOURCE=.\history.ico
# End Source File
# Begin Source File

SOURCE=.\home.ico
# End Source File
# Begin Source File

SOURCE=.\home_hot.ico
# End Source File
# Begin Source File

SOURCE=.\HostPage.rgs
# End Source File
# Begin Source File

SOURCE=.\hotbizbar.ico
# End Source File
# Begin Source File

SOURCE=.\HotBizBar.rgs
# End Source File
# Begin Source File

SOURCE=.\IconPage.rgs
# End Source File
# Begin Source File

SOURCE=.\leavetime.ico
# End Source File
# Begin Source File

SOURCE=.\login.ico
# End Source File
# Begin Source File

SOURCE=.\LoginPage.rgs
# End Source File
# Begin Source File

SOURCE=.\LogPage.rgs
# End Source File
# Begin Source File

SOURCE=.\mail.ico
# End Source File
# Begin Source File

SOURCE=.\mail_hot.ico
# End Source File
# Begin Source File

SOURCE=.\message.ico
# End Source File
# Begin Source File

SOURCE=.\message_hot.ico
# End Source File
# Begin Source File

SOURCE=.\NewsPage.rgs
# End Source File
# Begin Source File

SOURCE=.\project.ico
# End Source File
# Begin Source File

SOURCE=.\project_hot.ico
# End Source File
# Begin Source File

SOURCE=.\report.ico
# End Source File
# Begin Source File

SOURCE=.\reserve.ico
# End Source File
# Begin Source File

SOURCE=.\reserve_hot.ico
# End Source File
# Begin Source File

SOURCE=.\schedule.ico
# End Source File
# Begin Source File

SOURCE=.\schedule_hot.ico
# End Source File
# Begin Source File

SOURCE=.\ShowBarObj.rgs
# End Source File
# Begin Source File

SOURCE=.\timecard.ico
# End Source File
# Begin Source File

SOURCE=.\timecard_hot.ico
# End Source File
# Begin Source File

SOURCE=.\todo.ico
# End Source File
# Begin Source File

SOURCE=.\todo_hot.ico
# End Source File
# Begin Source File

SOURCE=.\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\toolbar_hot.bmp
# End Source File
# Begin Source File

SOURCE=.\where.ico
# End Source File
# Begin Source File

SOURCE=.\workflow.ico
# End Source File
# Begin Source File

SOURCE=.\workflow_hot.ico
# End Source File
# End Group
# End Target
# End Project
# Section HBIEBar : {00000000-0000-0000-0000-800000800000}
# 	1:21:IDS_DOCSTRINGHostPage:155
# 	1:12:IDD_HOSTPAGE:157
# 	1:12:IDR_HOSTPAGE:156
# 	1:20:IDS_HELPFILEHostPage:154
# 	1:17:IDS_TITLEHostPage:153
# End Section
