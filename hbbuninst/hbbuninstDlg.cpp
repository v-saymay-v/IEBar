// hbbuninstDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include <ExDisp.h>
#include <ExDispID.h>
#include <shlwapi.h>
#import <shdocvw.dll> 
#define __IHTMLControlElement_INTERFACE_DEFINED__
#include <msHtml.h>
#undef __IHTMLControlElement_INTERFACE_DEFINED__
#include "hbbuninst.h"
#include "hbbuninstDlg.h"
#include "hbbexport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CHbbuninstApp theApp;

/*
static const char* pszHbbFiles[] = {
	"HBIEBar.dll",
	"HBBCommon.dll",
	"libeay32.dll",
	"ssleay32.dll",
	"HBBHost.exe",
	"hotbizbar.log",
	""
};
*/

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstDlg ダイアログ

CHbbuninstDlg::CHbbuninstDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHbbuninstDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHbbuninstDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHbbuninstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHbbuninstDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHbbuninstDlg, CDialog)
	//{{AFX_MSG_MAP(CHbbuninstDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstDlg メッセージ ハンドラ

BOOL CHbbuninstDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CHbbuninstDlg::OnPaint() 
{
	if (IsIconic()) {
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CHbbuninstDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHbbuninstDlg::GetErrorMess(LPCTSTR pszMain, CString& szMess)
{
	char* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 既定の言語
		(LPTSTR) &lpMsgBuf, 0, NULL);
	szMess = pszMain;
	szMess += "（";
	szMess += lpMsgBuf;
	szMess += "）";
	LocalFree(lpMsgBuf);
}

/*
void CHbbuninstDlg::AddToAutoRd(const char* pszDir, int& ndx)
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	TCHAR szCmd[2048];
	TCHAR szKey[128];

	type = REG_SZ;
	size = sizeof(szCmd);
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"), NULL, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
		_stprintf(szKey, _T("HotBizBar%d"), ndx);
		_stprintf(szCmd, _T("CMD.EXE /C \"RD %s\""), pszDir);
		RegSetValueEx(hKey, szKey, NULL, type, (LPBYTE)&szCmd, sizeof(szCmd));
		RegCloseKey(hKey);
		++ndx;
	}		
}
*/

bool CHbbuninstDlg::QuitAllBrowser()
{
	HRESULT hr;
	SHDocVw::IShellWindowsPtr spSHWinds;
	hr = spSHWinds.CreateInstance(__uuidof(SHDocVw::ShellWindows));
	if (FAILED (hr))
		return false;
	long nCount = spSHWinds->GetCount();
	IDispatchPtr spDisp;
	for (long i = 0; i < nCount; i++) {
		_variant_t va (i, VT_I4);
		spDisp = spSHWinds->Item (va);
		IWebBrowser2 * pWebBrowser = NULL;
		hr = spDisp.QueryInterface (IID_IWebBrowser2, &pWebBrowser);
		if (SUCCEEDED(hr) && pWebBrowser != NULL) {
			pWebBrowser->Quit();
			pWebBrowser->Release();
		}
	}
	return true;
}

BOOL CALLBACK CHbbuninstDlg::EnumCountProc(HWND hwnd, LPARAM lParam)
{
	if (::GetWindowLong(hwnd, GWL_USERDATA) == 'HBBH') {
		::SendMessage(hwnd, WM_HBBQUIT, 0, 0);
		return FALSE;
	}
	return TRUE;
}

BOOL CHbbuninstDlg::EnableShutdownPrivileges()
{
	// Variables...
	HANDLE token;
	TOKEN_PRIVILEGES privileges;

	// Get the current process token handle...
	if( !OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &token ))
		return FALSE;

	// Get the LUID for shutdown privilege...
	LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[ 0 ].Luid );

	// Set parameters for AdjustTokenPrivileges...
	privileges.PrivilegeCount = 1;
	privileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

	// Enable shutdown privilege...
	AdjustTokenPrivileges( token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0 );

	return (GetLastError() == ERROR_SUCCESS);
}

BOOL CHbbuninstDlg::DisableShutdownPrivileges()
{
	// Variables...
	HANDLE token;
	TOKEN_PRIVILEGES privileges;

	// Get the current process token handle...
	if(!OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &token))
		return FALSE;

	// Get the LUID for shutdown privilege...
	LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[ 0 ].Luid );

	// Set parameters for AdjustTokenPrivileges...
	privileges.PrivilegeCount = 1;
	privileges.Privileges[ 0 ].Attributes = 0;

	// Disable shutdown privilege...
	AdjustTokenPrivileges( token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0 );

	return (GetLastError() == ERROR_SUCCESS);
}

void CHbbuninstDlg::OnOK() 
{
	int ndx = 0;
	HKEY hKey;
	TCHAR szDll[MAX_PATH];
	TCHAR szShortName[MAX_PATH];
	TCHAR szCmd[1024];
	CString szMess;
	CString szBase;
	DWORD type = REG_SZ;
	DWORD size = sizeof(szDll);

	if (!QuitAllBrowser()) {
		GetErrorMess(_T("エクスプローラを閉じられません。"), szMess);
		MessageBox(szMess, "エラー", MB_OK|MB_ICONSTOP);
		return;
	}

	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{CB07F490-0619-4D1D-B44A-8F458E47D0DF}\\InprocServer32"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS) {
		GetErrorMess(_T("HotBizツールバーが登録されていません。"), szMess);
		MessageBox(szMess, "エラー", MB_OK|MB_ICONSTOP);
		return;
	}

	ZeroMemory(szDll, sizeof(szDll));
	RegQueryValueEx(hKey, _T(""), NULL, &type, (LPBYTE)&szDll, &size);
	RegCloseKey(hKey);

	GetShortPathName(szDll, szShortName, sizeof(szShortName));
	_stprintf_s(szCmd, sizeof(szCmd), "Regsvr32.EXE /s /u %s", szShortName);

	PROCESS_INFORMATION processInformation;
	STARTUPINFO startupInfo;
	memset(&startupInfo, 0, sizeof(startupInfo));
	memset(&processInformation, 0, sizeof(processInformation));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = SW_MINIMIZE;
	if (CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation)) {
		WaitForSingleObject(processInformation.hProcess, INFINITE);
	} else {
		GetErrorMess(_T("サーバー登録解除に失敗しました。"), szMess);
		MessageBox(szMess, "エラー", MB_OK|MB_ICONSTOP);
		return;
	}
	RegDeleteKey(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"));

	while (!EnumWindows(EnumCountProc, NULL)) {
		Sleep(100);
	}

	szMess = theApp.m_lpCmdLine;
	szMess.TrimLeft();
	szMess.TrimRight();
	GetShortPathName(szMess, szShortName, sizeof(szShortName));

	GetWindowsDirectory(szDll, sizeof(szDll));
	SetCurrentDirectory(szDll);
	_tcscat_s(szDll, sizeof(szDll), "\\hotbizbar.ini");
	DeleteFile(szDll);

	_tcscpy_s(szDll, sizeof(szDll), szShortName);
	_tcscat_s(szDll, sizeof(szDll), _T("*.*"));
	WIN32_FIND_DATA find;
	HANDLE hFind = FindFirstFile(szDll, &find);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				_tcscpy_s(szDll, sizeof(szDll), szShortName);
				_tcscat_s(szDll, sizeof(szDll), find.cFileName);
				if (!DeleteFile(szDll)) {
					MoveFileEx(szDll, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
					++ndx;
				}
			}
		} while (FindNextFile(hFind, &find));
		FindClose(hFind);
	}
/*
	int i = 0;
	while (pszHbbFiles[i][0]) {
		_tcscpy(szDll, szShortName);
		_tcscat(szDll, pszHbbFiles[i]);
		if (!DeleteFile(szDll)) {
			MoveFileEx(szDll, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
			++ndx;
		}
		++i;
	}
*/
	if (szShortName[_tcslen(szShortName)-1] == _T('\\')) {
		szShortName[_tcslen(szShortName)-1] = _T('\0');
	}
	if (!RemoveDirectory(szShortName)) {
		MoveFileEx(szShortName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
		++ndx;
	}

	GetModuleFileName(NULL, szDll, MAX_PATH);
	MoveFileEx(szDll, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);

	if (!ndx) {
		MessageBox("HotBizツールバーのアンインストールが完了しました。", "正常終了", MB_YESNO|MB_ICONINFORMATION);
	} else if (MessageBox("HotBizツールバーのアンインストールを完了するためにはコンピュータの再起動が必要です。\r\nコンピュータを再起動しますか？", "再起動確認", MB_YESNO|MB_ICONQUESTION) == IDYES) {
		if (!EnableShutdownPrivileges()) {
			MessageBox("Windowsの再起動に失敗しました。\r\nスタートメニューから再起動させてください。", "エラー", MB_YESNO|MB_ICONSTOP);
			return;
		}
		ExitWindowsEx(EWX_REBOOT, 0);
	//	DisableShutdownPrivileges();
	}
	CDialog::OnOK();
}
