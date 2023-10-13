# Microsoft Developer Studio Project File - Name="HBBCommon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=HBBCommon - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "HBBCommon.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "HBBCommon.mak" CFG="HBBCommon - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "HBBCommon - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "HBBCommon - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HBBCommon - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\openssl-0.9.6l\inc32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Ws2_32.lib Mswsock.lib Crypt32.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"..\..\openssl-0.9.6l\out32dll"

!ELSEIF  "$(CFG)" == "HBBCommon - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\openssl-0.9.6l\inc32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Ws2_32.lib Mswsock.lib Crypt32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\openssl-0.9.6l\out32dll"

!ENDIF 

# Begin Target

# Name "HBBCommon - Win32 Release"
# Name "HBBCommon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\encrypt.cpp
# End Source File
# Begin Source File

SOURCE=.\HBBCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\HBBCommon.def
# End Source File
# Begin Source File

SOURCE=.\HBBCommon.rc
# End Source File
# Begin Source File

SOURCE=.\hbbexport.cpp
# End Source File
# Begin Source File

SOURCE=.\hbhistory.cpp
# End Source File
# Begin Source File

SOURCE=.\hotbizconnection.cpp
# End Source File
# Begin Source File

SOURCE=.\httppost.cpp
# End Source File
# Begin Source File

SOURCE=.\LogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\logininfo.cpp
# End Source File
# Begin Source File

SOURCE=.\os.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\encrypt.h
# End Source File
# Begin Source File

SOURCE=.\HBBCommon.h
# End Source File
# Begin Source File

SOURCE=.\hbbexport.h
# End Source File
# Begin Source File

SOURCE=.\hbhistory.h
# End Source File
# Begin Source File

SOURCE=.\hotbizconnection.h
# End Source File
# Begin Source File

SOURCE=.\httppost.h
# End Source File
# Begin Source File

SOURCE=.\LogDlg.h
# End Source File
# Begin Source File

SOURCE=.\logininfo.h
# End Source File
# Begin Source File

SOURCE=.\os.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\address.ico
# End Source File
# Begin Source File

SOURCE=.\bulletin.ico
# End Source File
# Begin Source File

SOURCE=.\cabinet.ico
# End Source File
# Begin Source File

SOURCE=.\circulat.ico
# End Source File
# Begin Source File

SOURCE=.\forum.ico
# End Source File
# Begin Source File

SOURCE=.\gotime.ico
# End Source File
# Begin Source File

SOURCE=.\res\HBBCommon.rc2
# End Source File
# Begin Source File

SOURCE=.\history.ico
# End Source File
# Begin Source File

SOURCE=.\hotbizbar.ico
# End Source File
# Begin Source File

SOURCE=.\leavetime.ico
# End Source File
# Begin Source File

SOURCE=.\login.ico
# End Source File
# Begin Source File

SOURCE=.\logout.ico
# End Source File
# Begin Source File

SOURCE=.\mail.ico
# End Source File
# Begin Source File

SOURCE=.\message.ico
# End Source File
# Begin Source File

SOURCE=.\project.ico
# End Source File
# Begin Source File

SOURCE=.\report.ico
# End Source File
# Begin Source File

SOURCE=.\reserve.ico
# End Source File
# Begin Source File

SOURCE=.\schedule.ico
# End Source File
# Begin Source File

SOURCE=.\timecard.ico
# End Source File
# Begin Source File

SOURCE=.\todo.ico
# End Source File
# Begin Source File

SOURCE=.\where.ico
# End Source File
# Begin Source File

SOURCE=.\workflow.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
