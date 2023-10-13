; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CHBBHostDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HBBHost.h"

ClassCount=7
Class1=CHBBHostApp
Class2=CHBBHostDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_LOGINDLG
Resource2=IDD_ABOUTBOX
Resource3=IDD_POPUPDLG
Class4=CLoginDlg
Resource4=IDR_MAINFRAME
Class5=CPopupDlg
Class6=CPopupMess
Class7=CPopupTitle
Resource5=IDD_HBBHOST_DIALOG

[CLS:CHBBHostApp]
Type=0
HeaderFile=HBBHost.h
ImplementationFile=HBBHost.cpp
Filter=N

[CLS:CHBBHostDlg]
Type=0
HeaderFile=HBBHostDlg.h
ImplementationFile=HBBHostDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CHBBHostDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=aboutdlg.h
ImplementationFile=aboutdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_VERSION,static,1342308480
Control3=IDC_COPYRIGHT,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_HBBHOST_DIALOG]
Type=1
Class=CHBBHostDlg
ControlCount=18
Control1=IDC_AUTOSTART,button,1342242819
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATUS,static,1342308352
Control6=IDC_STOPSTART,button,1476460544
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_INTERVAL,combobox,1344339971
Control10=IDC_STATIC,static,1342308352
Control11=IDC_POPUPTIME,edit,1350631552
Control12=IDC_PPTMSPIN,msctls_updown32,1342177462
Control13=IDC_PLAYSOUND,button,1342242819
Control14=IDC_SOUNDFILE,edit,1350631552
Control15=IDC_REFER,button,1342242816
Control16=IDC_PLAY,button,1342242816
Control17=IDC_STATIC,button,1342177287
Control18=IDOK,button,1342242817

[DLG:IDD_LOGINDLG]
Type=1
Class=CLoginDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_URL,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_USERNAME,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_PASSWORD,edit,1350631584
Control9=IDC_AUTOLOGIN,button,1342242819

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_POPUPDLG]
Type=1
Class=CPopupDlg
ControlCount=3
Control1=IDC_TITLE,static,1342313216
Control2=IDCANCEL,button,1342275584
Control3=IDC_MESS,static,1342312704

[CLS:CPopupDlg]
Type=0
HeaderFile=PopupDlg.h
ImplementationFile=PopupDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPopupDlg

[CLS:CPopupMess]
Type=0
HeaderFile=PopupMess.h
ImplementationFile=PopupMess.cpp
BaseClass=CStatic
Filter=W
LastObject=CPopupMess
VirtualFilter=WC

[CLS:CPopupTitle]
Type=0
HeaderFile=PopupTitle.h
ImplementationFile=PopupTitle.cpp
BaseClass=CStatic
Filter=W
LastObject=CPopupTitle
VirtualFilter=WC

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_HBHISTORY
Command2=IDM_HBLOGIN
Command3=IDM_STARTSTOP
Command4=IDM_HBHOPTION
Command5=IDM_HBHHELP
Command6=IDM_ABOUTBOX
Command7=IDM_HBHQUIT
CommandCount=7

