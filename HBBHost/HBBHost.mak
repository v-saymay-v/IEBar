# Microsoft Developer Studio Generated NMAKE File, Based on HBBHost.dsp
!IF "$(CFG)" == ""
CFG=HBBHost - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの HBBHost - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "HBBHost - Win32 Release" && "$(CFG)" != "HBBHost - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "HBBHost.mak" CFG="HBBHost - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "HBBHost - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "HBBHost - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HBBHost - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HBBHost.exe"

!ELSE 

ALL : "HBBCommon - Win32 Release" "$(OUTDIR)\HBBHost.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"HBBCommon - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\HBBHost.obj"
	-@erase "$(INTDIR)\HBBHost.pch"
	-@erase "$(INTDIR)\HBBHost.res"
	-@erase "$(INTDIR)\HBBHostDlg.obj"
	-@erase "$(INTDIR)\LoginDlg.obj"
	-@erase "$(INTDIR)\PopupDlg.obj"
	-@erase "$(INTDIR)\PopupMess.obj"
	-@erase "$(INTDIR)\PopupTitle.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBBHost.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\HBBCommon" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\HBBHost.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\HBBHost.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBBHost.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib comsupp.lib Version.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\HBBHost.pdb" /machine:I386 /out:"$(OUTDIR)\HBBHost.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\HBBHost.obj" \
	"$(INTDIR)\HBBHostDlg.obj" \
	"$(INTDIR)\LoginDlg.obj" \
	"$(INTDIR)\PopupDlg.obj" \
	"$(INTDIR)\PopupMess.obj" \
	"$(INTDIR)\PopupTitle.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBBHost.res" \
	"..\HBBCommon\Release\HBBCommon.lib"

"$(OUTDIR)\HBBHost.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HBBHost - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HBBHost.exe"

!ELSE 

ALL : "HBBCommon - Win32 Debug" "$(OUTDIR)\HBBHost.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"HBBCommon - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\HBBHost.obj"
	-@erase "$(INTDIR)\HBBHost.pch"
	-@erase "$(INTDIR)\HBBHost.res"
	-@erase "$(INTDIR)\HBBHostDlg.obj"
	-@erase "$(INTDIR)\LoginDlg.obj"
	-@erase "$(INTDIR)\PopupDlg.obj"
	-@erase "$(INTDIR)\PopupMess.obj"
	-@erase "$(INTDIR)\PopupTitle.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HBBHost.exe"
	-@erase "$(OUTDIR)\HBBHost.ilk"
	-@erase "$(OUTDIR)\HBBHost.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\HBBCommon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\HBBHost.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\HBBHost.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBBHost.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Winmm.lib comsupp.lib Version.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\HBBHost.pdb" /debug /machine:I386 /out:"$(OUTDIR)\HBBHost.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\HBBHost.obj" \
	"$(INTDIR)\HBBHostDlg.obj" \
	"$(INTDIR)\LoginDlg.obj" \
	"$(INTDIR)\PopupDlg.obj" \
	"$(INTDIR)\PopupMess.obj" \
	"$(INTDIR)\PopupTitle.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBBHost.res" \
	"..\HBBCommon\Debug\HBBCommon.lib"

"$(OUTDIR)\HBBHost.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("HBBHost.dep")
!INCLUDE "HBBHost.dep"
!ELSE 
!MESSAGE Warning: cannot find "HBBHost.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HBBHost - Win32 Release" || "$(CFG)" == "HBBHost - Win32 Debug"
SOURCE=.\AboutDlg.cpp

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBHost.pch"


SOURCE=.\HBBHost.cpp

"$(INTDIR)\HBBHost.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBHost.pch"


SOURCE=.\HBBHost.rc

"$(INTDIR)\HBBHost.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\HBBHostDlg.cpp

"$(INTDIR)\HBBHostDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBHost.pch"


SOURCE=.\LoginDlg.cpp

"$(INTDIR)\LoginDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBHost.pch"


SOURCE=.\PopupDlg.cpp

"$(INTDIR)\PopupDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBHost.pch"


SOURCE=.\PopupMess.cpp

"$(INTDIR)\PopupMess.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBHost.pch"


SOURCE=.\PopupTitle.cpp

"$(INTDIR)\PopupTitle.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBHost.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "HBBHost - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\HBBCommon" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\HBBHost.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBBHost.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBBHost - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\HBBCommon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\HBBHost.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBBHost.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

!IF  "$(CFG)" == "HBBHost - Win32 Release"

"HBBCommon - Win32 Release" : 
   cd "..\HBBCommon"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBCommon.mak CFG="HBBCommon - Win32 Release" 
   cd "..\HBBHost"

"HBBCommon - Win32 ReleaseCLEAN" : 
   cd "..\HBBCommon"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBCommon.mak CFG="HBBCommon - Win32 Release" RECURSE=1 CLEAN 
   cd "..\HBBHost"

!ELSEIF  "$(CFG)" == "HBBHost - Win32 Debug"

"HBBCommon - Win32 Debug" : 
   cd "..\HBBCommon"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBCommon.mak CFG="HBBCommon - Win32 Debug" 
   cd "..\HBBHost"

"HBBCommon - Win32 DebugCLEAN" : 
   cd "..\HBBCommon"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBCommon.mak CFG="HBBCommon - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\HBBHost"

!ENDIF 


!ENDIF 

