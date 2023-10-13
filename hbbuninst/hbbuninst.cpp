// hbbuninst.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "hbbuninst.h"
#include "hbbuninstDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstApp

BEGIN_MESSAGE_MAP(CHbbuninstApp, CWinApp)
	//{{AFX_MSG_MAP(CHbbuninstApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstApp クラスの構築

CHbbuninstApp::CHbbuninstApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CHbbuninstApp オブジェクト

CHbbuninstApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstApp クラスの初期化

BOOL CHbbuninstApp::InitInstance()
{
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。
	CString szCmdLine = m_lpCmdLine;
	if (szCmdLine.IsEmpty()) {
		TCHAR szTmp[MAX_PATH];
		TCHAR szDir[MAX_PATH];
		TCHAR szSrc[MAX_PATH];
		TCHAR szDest[MAX_PATH];
		TCHAR szCmd[1024];
		LPTSTR pstr;
		GetTempPath(MAX_PATH, szDest);
		GetTempFileName(szDest, _T("hbb"), 0, szDest);
		GetModuleFileName(m_hInstance, szSrc, MAX_PATH);
		if (!CopyFile(szSrc, szDest, FALSE)) {
			MessageBox(NULL, _T("アンインストールに失敗しました。"), _T("エラー"), MB_ICONSTOP|MB_OK);
			return FALSE;
		}

		pstr = _tcsrchr(szSrc, _T('\\'));
		++pstr;
		_tcsncpy_s(szTmp, sizeof(szTmp), szSrc, pstr-szSrc);
		szTmp[pstr-szSrc] = _T('\0');
		GetShortPathName(szTmp, szDir, sizeof(szDir));
		_stprintf_s(szCmd, sizeof(szCmd), "%s %s", szDest, szDir);

		PROCESS_INFORMATION processInformation;
		STARTUPINFO startupInfo;
		memset(&startupInfo, 0, sizeof(startupInfo));
		memset(&processInformation, 0, sizeof(processInformation));
		startupInfo.cb = sizeof(startupInfo);
		startupInfo.dwFlags = STARTF_USESHOWWINDOW;
		startupInfo.wShowWindow = SW_SHOW;
		if (!CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation)) {
			MessageBox(NULL, _T("アンインストールに失敗しました。"), _T("エラー"), MB_ICONSTOP|MB_OK);
			return FALSE;
		}
		return FALSE;
	}

	CoInitialize(NULL);

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
//	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	CHbbuninstDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	CoUninitialize();

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
