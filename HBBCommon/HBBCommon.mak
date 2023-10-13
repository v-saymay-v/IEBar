# Microsoft Developer Studio Generated NMAKE File, Based on HBBCommon.dsp
!IF "$(CFG)" == ""
CFG=HBBCommon - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの HBBCommon - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "HBBCommon - Win32 Release" && "$(CFG)" != "HBBCommon - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
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

!IF  "$(CFG)" == "HBBCommon - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\HBBCommon.dll"


CLEAN :
	-@erase "$(INTDIR)\encrypt.obj"
	-@erase "$(INTDIR)\HBBCommon.obj"
	-@erase "$(INTDIR)\HBBCommon.pch"
	-@erase "$(INTDIR)\HBBCommon.res"
	-@erase "$(INTDIR)\hbbexport.obj"
	-@erase "$(INTDIR)\hbhistory.obj"
	-@erase "$(INTDIR)\hotbizconnection.obj"
	-@erase "$(INTDIR)\httppost.obj"
	-@erase "$(INTDIR)\LogDlg.obj"
	-@erase "$(INTDIR)\logininfo.obj"
	-@erase "$(INTDIR)\os.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HBBCommon.dll"
	-@erase "$(OUTDIR)\HBBCommon.exp"
	-@erase "$(OUTDIR)\HBBCommon.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\openssl-0.9.6l\inc32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBBCommon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\HBBCommon.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBBCommon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Ws2_32.lib Mswsock.lib Crypt32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\HBBCommon.pdb" /machine:I386 /def:".\HBBCommon.def" /out:"$(OUTDIR)\HBBCommon.dll" /implib:"$(OUTDIR)\HBBCommon.lib" /libpath:"..\..\openssl-0.9.6l\out32dll" 
DEF_FILE= \
	".\HBBCommon.def"
LINK32_OBJS= \
	"$(INTDIR)\encrypt.obj" \
	"$(INTDIR)\HBBCommon.obj" \
	"$(INTDIR)\hbbexport.obj" \
	"$(INTDIR)\hbhistory.obj" \
	"$(INTDIR)\hotbizconnection.obj" \
	"$(INTDIR)\httppost.obj" \
	"$(INTDIR)\LogDlg.obj" \
	"$(INTDIR)\logininfo.obj" \
	"$(INTDIR)\os.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBBCommon.res"

"$(OUTDIR)\HBBCommon.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HBBCommon - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\HBBCommon.dll"


CLEAN :
	-@erase "$(INTDIR)\encrypt.obj"
	-@erase "$(INTDIR)\HBBCommon.obj"
	-@erase "$(INTDIR)\HBBCommon.pch"
	-@erase "$(INTDIR)\HBBCommon.res"
	-@erase "$(INTDIR)\hbbexport.obj"
	-@erase "$(INTDIR)\hbhistory.obj"
	-@erase "$(INTDIR)\hotbizconnection.obj"
	-@erase "$(INTDIR)\httppost.obj"
	-@erase "$(INTDIR)\LogDlg.obj"
	-@erase "$(INTDIR)\logininfo.obj"
	-@erase "$(INTDIR)\os.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HBBCommon.dll"
	-@erase "$(OUTDIR)\HBBCommon.exp"
	-@erase "$(OUTDIR)\HBBCommon.ilk"
	-@erase "$(OUTDIR)\HBBCommon.lib"
	-@erase "$(OUTDIR)\HBBCommon.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\openssl-0.9.6l\inc32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBBCommon.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\HBBCommon.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HBBCommon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Ws2_32.lib Mswsock.lib Crypt32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\HBBCommon.pdb" /debug /machine:I386 /def:".\HBBCommon.def" /out:"$(OUTDIR)\HBBCommon.dll" /implib:"$(OUTDIR)\HBBCommon.lib" /pdbtype:sept /libpath:"..\..\openssl-0.9.6l\out32dll" 
DEF_FILE= \
	".\HBBCommon.def"
LINK32_OBJS= \
	"$(INTDIR)\encrypt.obj" \
	"$(INTDIR)\HBBCommon.obj" \
	"$(INTDIR)\hbbexport.obj" \
	"$(INTDIR)\hbhistory.obj" \
	"$(INTDIR)\hotbizconnection.obj" \
	"$(INTDIR)\httppost.obj" \
	"$(INTDIR)\LogDlg.obj" \
	"$(INTDIR)\logininfo.obj" \
	"$(INTDIR)\os.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\HBBCommon.res"

"$(OUTDIR)\HBBCommon.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("HBBCommon.dep")
!INCLUDE "HBBCommon.dep"
!ELSE 
!MESSAGE Warning: cannot find "HBBCommon.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HBBCommon - Win32 Release" || "$(CFG)" == "HBBCommon - Win32 Debug"
SOURCE=.\encrypt.cpp

"$(INTDIR)\encrypt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\HBBCommon.cpp

"$(INTDIR)\HBBCommon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\HBBCommon.rc

"$(INTDIR)\HBBCommon.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\hbbexport.cpp

"$(INTDIR)\hbbexport.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\hbhistory.cpp

"$(INTDIR)\hbhistory.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\hotbizconnection.cpp

"$(INTDIR)\hotbizconnection.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\httppost.cpp

"$(INTDIR)\httppost.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\LogDlg.cpp

"$(INTDIR)\LogDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\logininfo.cpp

"$(INTDIR)\logininfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\os.cpp

"$(INTDIR)\os.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\HBBCommon.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "HBBCommon - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\openssl-0.9.6l\inc32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBBCommon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBBCommon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "HBBCommon - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\openssl-0.9.6l\inc32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\HBBCommon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\HBBCommon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

