; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CHbbsignupDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "hbbsignup.h"

ClassCount=3
Class1=CHbbsignupApp
Class2=CHbbsignupDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_PROGRESSDLG_DIALOG
Class3=CProgressDlg
Resource3=IDD_HBBSIGNUP_DIALOG

[CLS:CHbbsignupApp]
Type=0
HeaderFile=hbbsignup.h
ImplementationFile=hbbsignup.cpp
Filter=N

[CLS:CHbbsignupDlg]
Type=0
HeaderFile=hbbsignupDlg.h
ImplementationFile=hbbsignupDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CHbbsignupDlg



[DLG:IDD_HBBSIGNUP_DIALOG]
Type=1
Class=CHbbsignupDlg
ControlCount=31
Control1=IDC_STATIC,static,1342308352
Control2=IDC_SERVER,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PREFIX,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_START,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_END,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_INI,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CAB,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_FOLDER,edit,1350631552
Control15=IDC_REFFOLDER,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_CERT,edit,1350631552
Control18=IDC_REFSPC,button,1342242816
Control19=IDC_STATIC,static,1342308352
Control20=IDC_PVK,edit,1350631552
Control21=IDC_REFPVK,button,1342242816
Control22=IDC_STATIC,static,1342308352
Control23=IDC_PASSWORD,edit,1350631584
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EXPLAIN,edit,1350631552
Control26=IDC_STATIC,static,1342308352
Control27=IDC_WEB,edit,1350631552
Control28=IDC_STATIC,static,1342308352
Control29=IDC_TIMESTAMP,edit,1350631552
Control30=IDOK,button,1342242817
Control31=IDCANCEL,button,1342242816

[DLG:IDD_PROGRESSDLG_DIALOG]
Type=1
Class=CProgressDlg
ControlCount=3
Control1=IDC_NAME,static,1342308352
Control2=IDC_PROGRESS,msctls_progress32,1350565888
Control3=IDCANCEL,button,1342242816

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgressDlg.h
ImplementationFile=ProgressDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CProgressDlg

