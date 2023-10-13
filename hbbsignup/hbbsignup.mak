# Microsoft Developer Studio Generated NMAKE File, Based on hbbsignup.dsp
!IF "$(CFG)" == ""
CFG=hbbsignup - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの hbbsignup - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "hbbsignup - Win32 Release" && "$(CFG)" != "hbbsignup - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "hbbsignup.mak" CFG="hbbsignup - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "hbbsignup - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "hbbsignup - Win32 Debug" ("Win32 (x86) Application" 用)
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

!IF  "$(CFG)" == "hbbsignup - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\hbbsignup.exe"


CLEAN :
	-@erase "$(INTDIR)\hbbsignup.obj"
	-@erase "$(INTDIR)\hbbsignup.pch"
	-@erase "$(INTDIR)\hbbsignup.res"
	-@erase "$(INTDIR)\hbbsignupDlg.obj"
	-@erase "$(INTDIR)\ProgressDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\hbbsignup.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\hbbsignup.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\hbbsignup.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\hbbsignup.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\hbbsignup.pdb" /machine:I386 /out:"$(OUTDIR)\hbbsignup.exe" 
LINK32_OBJS= \
	"$(INTDIR)\hbbsignup.obj" \
	"$(INTDIR)\hbbsignupDlg.obj" \
	"$(INTDIR)\ProgressDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\hbbsignup.res"

"$(OUTDIR)\hbbsignup.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "hbbsignup - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\hbbsignup.exe"


CLEAN :
	-@erase "$(INTDIR)\hbbsignup.obj"
	-@erase "$(INTDIR)\hbbsignup.pch"
	-@erase "$(INTDIR)\hbbsignup.res"
	-@erase "$(INTDIR)\hbbsignupDlg.obj"
	-@erase "$(INTDIR)\ProgressDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\hbbsignup.exe"
	-@erase "$(OUTDIR)\hbbsignup.ilk"
	-@erase "$(OUTDIR)\hbbsignup.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\hbbsignup.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\hbbsignup.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\hbbsignup.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\hbbsignup.pdb" /debug /machine:I386 /out:"$(OUTDIR)\hbbsignup.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\hbbsignup.obj" \
	"$(INTDIR)\hbbsignupDlg.obj" \
	"$(INTDIR)\ProgressDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\hbbsignup.res"

"$(OUTDIR)\hbbsignup.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("hbbsignup.dep")
!INCLUDE "hbbsignup.dep"
!ELSE 
!MESSAGE Warning: cannot find "hbbsignup.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "hbbsignup - Win32 Release" || "$(CFG)" == "hbbsignup - Win32 Debug"
SOURCE=.\hbbsignup.cpp

"$(INTDIR)\hbbsignup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\hbbsignup.pch"


SOURCE=.\hbbsignup.rc

"$(INTDIR)\hbbsignup.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\hbbsignupDlg.cpp

"$(INTDIR)\hbbsignupDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\hbbsignup.pch"


SOURCE=.\ProgressDlg.cpp

"$(INTDIR)\ProgressDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\hbbsignup.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "hbbsignup - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\hbbsignup.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\hbbsignup.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "hbbsignup - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\hbbsignup.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\hbbsignup.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

