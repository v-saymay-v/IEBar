; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
ClassCount=3
Class1=CHBBCommonApp
LastClass=CLogDlg
NewFileInclude2=#include "HBBCommon.h"
ResourceCount=1
NewFileInclude1=#include "stdafx.h"
Class2=CLogDlg
LastTemplate=CListBox
Class3=CLogList
Resource1=IDD_LOGDLG

[CLS:CHBBCommonApp]
Type=0
HeaderFile=HBBCommon.h
ImplementationFile=HBBCommon.cpp
Filter=N
LastObject=CHBBCommonApp

[DLG:IDD_LOGDLG]
Type=1
Class=CLogDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_DELETE,button,1342242816
Control3=IDC_SELALL,button,1342242816
Control4=IDC_CLRALL,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_NEWSLOG,listbox,1353777435

[CLS:CLogDlg]
Type=0
HeaderFile=LogDlg.h
ImplementationFile=LogDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NEWSLOG
VirtualFilter=dWC

[CLS:CLogList]
Type=0
HeaderFile=LogList.h
ImplementationFile=LogList.cpp
BaseClass=CListBox
Filter=W
LastObject=CLogList
VirtualFilter=bWC





