// HBBHost.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "HBBHost.h"
#include "HBBCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// 唯一の CHBBHostApp オブジェクト

CHBBHostApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHBBHostApp

BEGIN_MESSAGE_MAP(CHBBHostApp, CWinApp)
	//{{AFX_MSG_MAP(CHBBHostApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHBBHostApp クラスの構築

CHBBHostApp::CHBBHostApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

void CHBBHostApp::AddTrayIcon()
{
	CString szMess, szTip;
	UINT nIcon, nMess;
	if (AlreadyLoggedin()) {
		BOOL bRecvInfo;
		DWORD nInterval;
		DWORD nPopupTime;
		BOOL bPlaySound;
		TCHAR szFile[MAX_PATH];
		GetNewsInfo(bRecvInfo, nInterval, nPopupTime, bPlaySound, szFile);
		if (bRecvInfo) {
			nIcon = IDI_LOGGEDIN;
			nMess = IDS_LOGGEDIN;
		} else {
			nIcon = IDI_STOPPED;
			nMess = IDS_STOPPED;
		}
	} else {
		nIcon = IDR_MAINFRAME;
		nMess = IDS_NOTLOGGEDIN;
	}

	szTip.LoadString(AFX_IDS_APP_TITLE);
	AfxFormatString1(szMess, nMess, szTip);

	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_dlgMain.m_hWnd; 
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_MY_NOTIFYICON;
	nid.hIcon = (HICON)LoadImage(theApp.m_hInstance, MAKEINTRESOURCE(nIcon), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	lstrcpy(nid.szTip, szMess);
	Shell_NotifyIcon(NIM_ADD, &nid);
	if (nid.hIcon) 
		DestroyIcon(nid.hIcon); 
}

void CHBBHostApp::DelTrayIcon()
{
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_dlgMain.m_hWnd; 
	nid.uID = IDR_MAINFRAME;
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

/////////////////////////////////////////////////////////////////////////////
// CHBBHostApp クラスの初期化

BOOL CHBBHostApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDS_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CoInitialize(NULL);

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
//	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	m_pMainWnd = &m_dlgMain;
	m_dlgMain.Create(NULL);
	AddTrayIcon();

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return TRUE;
}

int CHBBHostApp::ExitInstance() 
{
	CoUninitialize();
	DelTrayIcon();
	m_dlgMain.DestroyWindow();
	return CWinApp::ExitInstance();
}
