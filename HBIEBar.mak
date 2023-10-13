# Microsoft Developer Studio Generated NMAKE File, Based on HBIEBar.dsp
!IF "$(CFG)" == ""
CFG=HBIEBar - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの HBIEBar - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "HBIEBar - Win32 Debug" && "$(CFG)" != "HBIEBar - Win32 Release"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "HBIEBar.mak" CFG="HBIEBar - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "HBIEBar - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "HBIEBar - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
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

!IF  "$(CFG)" == "HBIEBar - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HBIEBar.dll" ".\HBIEBar.tlb" ".\HBIEBar.h" ".\HBIEBar_i.c" ".\Debug\regsvr32.trg"

!ELSE 

ALL : "hbbsetup - Win32 Debug" "HBBHost - Win32 Debug" "HBBCommon - Win32 Debug" "hbbsignup - Win32 Debug" "hbbuninst - Win32 Debug" "$(OUTDIR)\HBIEBar.dll" ".\HBIEBar.tlb" ".\HBIEBar.h" ".\HBIEBar_i.c" ".\Debug\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"hbbuninst - Win32 DebugCLEAN" "hbbsignup - Win32 DebugCLEAN" "HBBCommon - Win32 DebugCLEAN" "HBBHost - Win32 DebugCLEAN" "hbbsetup - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\HBIEBar.obj"
	-@erase "$(INTDIR)\HBIEBar.pch"
	-@erase "$(INTDIR)\HBIEBar.res"
	-@erase "$(INTDIR)\HostPage.obj"
	-@erase "$(INTDIR)\HotBizBar.obj"
	-@erase "$(INTDIR)\IconPage.obj"
	-@erase "$(INTDIR)\kanji.obj"
	-@erase "$(INTDIR)\LoginDlg.obj"
	-@erase "$(INTDIR)\MFToolbar.obj"
	-@erase "$(INTDIR)\ReflectionWnd.obj"
	-@erase "$(INTDIR)\resource.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VersionDlg.obj"
	-@erase "$(INTDIR)\WaitDlg.obj"
	-@erase "$(OUTDIR)\HBIEBar.dll"
	-@erase "$(OUTDIR)\HBIEBar.exp"
	-@erase "$(OUTDIR)\HBIEBar.ilk"
	-@erase "$(OUTDIR)\HBIEBar.lib"
	-@erase "$(OUTDIR)\HBIEBar.pdb"
	-@erase ".\HBIEBar.h"
	-@erase ".\HBIEBar.tlb"
	-@erase ".\HBIEBar_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "..\openssl-0.9.6l\inc32" /I "HBBCommon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBIEBar.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\HBIEBar.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBIEBar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib Version.lib Winmm.lib HBBCommon.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\HBIEBar.pdb" /debug /machine:I386 /def:".\HBIEBar.def" /out:"$(OUTDIR)\HBIEBar.dll" /implib:"$(OUTDIR)\HBIEBar.lib" /pdbtype:sept /libpath:"..\openssl-0.9.6l\out32dll" /libpath:"HBBCommon\Debug" 
DEF_FILE= \
	".\HBIEBar.def"
LINK32_OBJS= \
	"$(INTDIR)\HBIEBar.obj" \
	"$(INTDIR)\HBIEBar.res" \
	"$(INTDIR)\HostPage.obj" \
	"$(INTDIR)\HotBizBar.obj" \
	"$(INTDIR)\IconPage.obj" \
	"$(INTDIR)\kanji.obj" \
	"$(INTDIR)\LoginDlg.obj" \
	"$(INTDIR)\MFToolbar.obj" \
	"$(INTDIR)\ReflectionWnd.obj" \
	"$(INTDIR)\resource.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VersionDlg.obj" \
	"$(INTDIR)\WaitDlg.obj" \
	".\HBBCommon\Debug\HBBCommon.lib"

"$(OUTDIR)\HBIEBar.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\HBIEBar.dll
InputPath=.\Debug\HBIEBar.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo 警告 : Windows 95 に Unicode DLL を登録することはできません 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "HBIEBar - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HBIEBar.dll" ".\HBIEBar.tlb" ".\HBIEBar.h" ".\HBIEBar_i.c" ".\Release\regsvr32.trg"

!ELSE 

ALL : "hbbsetup - Win32 Release" "HBBHost - Win32 Release" "HBBCommon - Win32 Release" "hbbsignup - Win32 Release" "hbbuninst - Win32 Release" "$(OUTDIR)\HBIEBar.dll" ".\HBIEBar.tlb" ".\HBIEBar.h" ".\HBIEBar_i.c" ".\Release\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"hbbuninst - Win32 ReleaseCLEAN" "hbbsignup - Win32 ReleaseCLEAN" "HBBCommon - Win32 ReleaseCLEAN" "HBBHost - Win32 ReleaseCLEAN" "hbbsetup - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\HBIEBar.obj"
	-@erase "$(INTDIR)\HBIEBar.pch"
	-@erase "$(INTDIR)\HBIEBar.res"
	-@erase "$(INTDIR)\HostPage.obj"
	-@erase "$(INTDIR)\HotBizBar.obj"
	-@erase "$(INTDIR)\IconPage.obj"
	-@erase "$(INTDIR)\kanji.obj"
	-@erase "$(INTDIR)\LoginDlg.obj"
	-@erase "$(INTDIR)\MFToolbar.obj"
	-@erase "$(INTDIR)\ReflectionWnd.obj"
	-@erase "$(INTDIR)\resource.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VersionDlg.obj"
	-@erase "$(INTDIR)\WaitDlg.obj"
	-@erase "$(OUTDIR)\HBIEBar.dll"
	-@erase "$(OUTDIR)\HBIEBar.exp"
	-@erase "$(OUTDIR)\HBIEBar.lib"
	-@erase ".\HBIEBar.h"
	-@erase ".\HBIEBar.tlb"
	-@erase ".\HBIEBar_i.c"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "..\openssl-0.9.6l\inc32" /I "HBBCommon" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBIEBar.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\HBIEBar.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBIEBar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib Version.lib Winmm.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBIEBar.pdb" /machine:I386 /def:".\HBIEBar.def" /out:"$(OUTDIR)\HBIEBar.dll" /implib:"$(OUTDIR)\HBIEBar.lib" /libpath:"..\openssl-0.9.6l\out32dll" 
DEF_FILE= \
	".\HBIEBar.def"
LINK32_OBJS= \
	"$(INTDIR)\HBIEBar.obj" \
	"$(INTDIR)\HBIEBar.res" \
	"$(INTDIR)\HostPage.obj" \
	"$(INTDIR)\HotBizBar.obj" \
	"$(INTDIR)\IconPage.obj" \
	"$(INTDIR)\kanji.obj" \
	"$(INTDIR)\LoginDlg.obj" \
	"$(INTDIR)\MFToolbar.obj" \
	"$(INTDIR)\ReflectionWnd.obj" \
	"$(INTDIR)\resource.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VersionDlg.obj" \
	"$(INTDIR)\WaitDlg.obj" \
	".\HBBCommon\Release\HBBCommon.lib"

"$(OUTDIR)\HBIEBar.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\Release\HBIEBar.dll
InputPath=.\Release\HBIEBar.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo 警告 : Windows 95 に Unicode DLL を登録することはできません 
	:end 
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

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("HBIEBar.dep")
!INCLUDE "HBIEBar.dep"
!ELSE 
!MESSAGE Warning: cannot find "HBIEBar.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HBIEBar - Win32 Debug" || "$(CFG)" == "HBIEBar - Win32 Release"
SOURCE=.\HBIEBar.cpp

"$(INTDIR)\HBIEBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\HBIEBar.idl
MTL_SWITCHES=/tlb ".\HBIEBar.tlb" /h "HBIEBar.h" /iid "HBIEBar_i.c" /Oicf 

".\HBIEBar.tlb"	".\HBIEBar.h"	".\HBIEBar_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\HBIEBar.rc

"$(INTDIR)\HBIEBar.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\HostPage.cpp

"$(INTDIR)\HostPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\HotBizBar.cpp

"$(INTDIR)\HotBizBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\IconPage.cpp

"$(INTDIR)\IconPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\kanji.cpp

"$(INTDIR)\kanji.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\LoginDlg.cpp

"$(INTDIR)\LoginDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\MFToolbar.cpp

"$(INTDIR)\MFToolbar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\ReflectionWnd.cpp

"$(INTDIR)\ReflectionWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\resource.cpp

"$(INTDIR)\resource.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "HBIEBar - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\openssl-0.9.6l\inc32" /I "HBBCommon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBIEBar.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBIEBar.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBIEBar - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\openssl-0.9.6l\inc32" /I "HBBCommon" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBIEBar.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBIEBar.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VersionDlg.cpp

"$(INTDIR)\VersionDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


SOURCE=.\WaitDlg.cpp

"$(INTDIR)\WaitDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBIEBar.pch"


!IF  "$(CFG)" == "HBIEBar - Win32 Debug"

"hbbuninst - Win32 Debug" : 
   cd ".\hbbuninst"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbuninst.mak CFG="hbbuninst - Win32 Debug" 
   cd ".."

"hbbuninst - Win32 DebugCLEAN" : 
   cd ".\hbbuninst"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbuninst.mak CFG="hbbuninst - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "HBIEBar - Win32 Release"

"hbbuninst - Win32 Release" : 
   cd ".\hbbuninst"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbuninst.mak CFG="hbbuninst - Win32 Release" 
   cd ".."

"hbbuninst - Win32 ReleaseCLEAN" : 
   cd ".\hbbuninst"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbuninst.mak CFG="hbbuninst - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "HBIEBar - Win32 Debug"

"hbbsignup - Win32 Debug" : 
   cd ".\hbbsignup"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbsignup.mak CFG="hbbsignup - Win32 Debug" 
   cd ".."

"hbbsignup - Win32 DebugCLEAN" : 
   cd ".\hbbsignup"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbsignup.mak CFG="hbbsignup - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "HBIEBar - Win32 Release"

"hbbsignup - Win32 Release" : 
   cd ".\hbbsignup"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbsignup.mak CFG="hbbsignup - Win32 Release" 
   cd ".."

"hbbsignup - Win32 ReleaseCLEAN" : 
   cd ".\hbbsignup"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbsignup.mak CFG="hbbsignup - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "HBIEBar - Win32 Debug"

"HBBCommon - Win32 Debug" : 
   cd ".\HBBCommon"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBCommon.mak CFG="HBBCommon - Win32 Debug" 
   cd ".."

"HBBCommon - Win32 DebugCLEAN" : 
   cd ".\HBBCommon"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBCommon.mak CFG="HBBCommon - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "HBIEBar - Win32 Release"

"HBBCommon - Win32 Release" : 
   cd ".\HBBCommon"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBCommon.mak CFG="HBBCommon - Win32 Release" 
   cd ".."

"HBBCommon - Win32 ReleaseCLEAN" : 
   cd ".\HBBCommon"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBCommon.mak CFG="HBBCommon - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "HBIEBar - Win32 Debug"

"HBBHost - Win32 Debug" : 
   cd ".\HBBHost"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBHost.mak CFG="HBBHost - Win32 Debug" 
   cd ".."

"HBBHost - Win32 DebugCLEAN" : 
   cd ".\HBBHost"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBHost.mak CFG="HBBHost - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "HBIEBar - Win32 Release"

"HBBHost - Win32 Release" : 
   cd ".\HBBHost"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBHost.mak CFG="HBBHost - Win32 Release" 
   cd ".."

"HBBHost - Win32 ReleaseCLEAN" : 
   cd ".\HBBHost"
   $(MAKE) /$(MAKEFLAGS) /F .\HBBHost.mak CFG="HBBHost - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "HBIEBar - Win32 Debug"

"hbbsetup - Win32 Debug" : 
   cd ".\hbbsetup"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbsetup.mak CFG="hbbsetup - Win32 Debug" 
   cd ".."

"hbbsetup - Win32 DebugCLEAN" : 
   cd ".\hbbsetup"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbsetup.mak CFG="hbbsetup - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "HBIEBar - Win32 Release"

"hbbsetup - Win32 Release" : 
   cd ".\hbbsetup"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbsetup.mak CFG="hbbsetup - Win32 Release" 
   cd ".."

"hbbsetup - Win32 ReleaseCLEAN" : 
   cd ".\hbbsetup"
   $(MAKE) /$(MAKEFLAGS) /F .\hbbsetup.mak CFG="hbbsetup - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

