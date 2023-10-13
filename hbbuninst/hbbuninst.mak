# Microsoft Developer Studio Generated NMAKE File, Based on hbbuninst.dsp
!IF "$(CFG)" == ""
CFG=hbbuninst - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの hbbuninst - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "hbbuninst - Win32 Release" && "$(CFG)" != "hbbuninst - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "hbbuninst.mak" CFG="hbbuninst - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "hbbuninst - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "hbbuninst - Win32 Debug" ("Win32 (x86) Application" 用)
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

!IF  "$(CFG)" == "hbbuninst - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\hbbuninst.exe"


CLEAN :
	-@erase "$(INTDIR)\hbbuninst.obj"
	-@erase "$(INTDIR)\hbbuninst.pch"
	-@erase "$(INTDIR)\hbbuninst.res"
	-@erase "$(INTDIR)\hbbuninstDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\hbbuninst.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\HBBCommon" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\hbbuninst.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\hbbuninst.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\hbbuninst.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\hbbuninst.pdb" /machine:I386 /out:"$(OUTDIR)\hbbuninst.exe" 
LINK32_OBJS= \
	"$(INTDIR)\hbbuninst.obj" \
	"$(INTDIR)\hbbuninstDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\hbbuninst.res"

"$(OUTDIR)\hbbuninst.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "hbbuninst - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\hbbuninst.exe"


CLEAN :
	-@erase "$(INTDIR)\hbbuninst.obj"
	-@erase "$(INTDIR)\hbbuninst.pch"
	-@erase "$(INTDIR)\hbbuninst.res"
	-@erase "$(INTDIR)\hbbuninstDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\hbbuninst.exe"
	-@erase "$(OUTDIR)\hbbuninst.ilk"
	-@erase "$(OUTDIR)\hbbuninst.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\HBBCommon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\hbbuninst.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\hbbuninst.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\hbbuninst.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\hbbuninst.pdb" /debug /machine:I386 /out:"$(OUTDIR)\hbbuninst.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\hbbuninst.obj" \
	"$(INTDIR)\hbbuninstDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\hbbuninst.res"

"$(OUTDIR)\hbbuninst.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("hbbuninst.dep")
!INCLUDE "hbbuninst.dep"
!ELSE 
!MESSAGE Warning: cannot find "hbbuninst.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "hbbuninst - Win32 Release" || "$(CFG)" == "hbbuninst - Win32 Debug"
SOURCE=.\hbbuninst.cpp

"$(INTDIR)\hbbuninst.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\hbbuninst.pch"


SOURCE=.\hbbuninst.rc

"$(INTDIR)\hbbuninst.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\hbbuninstDlg.cpp

"$(INTDIR)\hbbuninstDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\hbbuninst.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "hbbuninst - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\HBBCommon" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\hbbuninst.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\hbbuninst.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "hbbuninst - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\HBBCommon" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\hbbuninst.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\hbbuninst.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

