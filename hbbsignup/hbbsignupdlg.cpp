// hbbsignupDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "hbbsignup.h"
#include "hbbsignupDlg.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUFSIZE 4096 

static char g_szTimeStampURL[] = _T("http://timestamp.verisign.com/scripts/timstamp.dll");
 
/////////////////////////////////////////////////////////////////////////////
// CHbbsignupDlg ダイアログ

CHbbsignupDlg::CHbbsignupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHbbsignupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHbbsignupDlg)
	m_szCert = _T("");
	m_nEnd = 0;
	m_szFolder = _T("");
	m_szPrefix = _T("");
	m_szServer = _T("");
	m_nStart = 0;
	m_szPassword = _T("");
	m_szPvk = _T("");
	m_szCab = _T("");
	m_szIni = _T("");
	m_szExplain = _T("");
	m_szTimestamp = _T("http://timestamp.verisign.com/scripts/timstamp.dll");
	m_szWeb = _T("");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHbbsignupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHbbsignupDlg)
	DDX_Text(pDX, IDC_CERT, m_szCert);
	DDX_Text(pDX, IDC_END, m_nEnd);
	DDX_Text(pDX, IDC_FOLDER, m_szFolder);
	DDX_Text(pDX, IDC_PREFIX, m_szPrefix);
	DDX_Text(pDX, IDC_SERVER, m_szServer);
	DDX_Text(pDX, IDC_START, m_nStart);
	DDX_Text(pDX, IDC_PASSWORD, m_szPassword);
	DDX_Text(pDX, IDC_PVK, m_szPvk);
	DDX_Text(pDX, IDC_CAB, m_szCab);
	DDX_Text(pDX, IDC_INI, m_szIni);
	DDX_Text(pDX, IDC_EXPLAIN, m_szExplain);
	DDX_Text(pDX, IDC_TIMESTAMP, m_szTimestamp);
	DDX_Text(pDX, IDC_WEB, m_szWeb);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHbbsignupDlg, CDialog)
	//{{AFX_MSG_MAP(CHbbsignupDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REFFOLDER, OnReffolder)
	ON_BN_CLICKED(IDC_REFSPC, OnRefspc)
	ON_BN_CLICKED(IDC_REFPVK, OnRefpvk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHbbsignupDlg メッセージ ハンドラ

BOOL CHbbsignupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CHbbsignupDlg::OnPaint() 
{
	if (IsIconic())
	{
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
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CHbbsignupDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CALLBACK BackupCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg==BFFM_INITIALIZED) {
		SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
	}
	return 0;
}

void CHbbsignupDlg::OnReffolder() 
{
	BROWSEINFO bi; 
	TCHAR szTitle[MAX_PATH] = _T("HotBizツールバーのインストールイメージ作成先フォルダを指定してください");
	LPTSTR lpBuffer; 
	LPITEMIDLIST pidlPrograms;  // PIDL for Programs folder 
	LPITEMIDLIST pidlBrowse;    // PIDL selected by user 
	LPMALLOC g_pMalloc;

	if (!SUCCEEDED(SHGetMalloc(&g_pMalloc)))
		return; 

	// Allocate a buffer to receive browse information. 
	if ((lpBuffer = (LPTSTR) g_pMalloc->Alloc(MAX_PATH)) == NULL) 
		return; 

	// Get the PIDL for the Programs folder. 
	if (!SUCCEEDED(SHGetSpecialFolderLocation(m_hWnd, CSIDL_DESKTOP, &pidlPrograms))) {
		g_pMalloc->Free(lpBuffer); 
		return; 
	} 

	// Fill in the BROWSEINFO structure. 
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = pidlPrograms;
	bi.pszDisplayName = lpBuffer;
	bi.lpszTitle = szTitle;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = &BackupCallbackProc;
	bi.lParam = (LONG)(LPCSTR)m_szFolder;

	// Browse for a folder and return its PIDL. 
	pidlBrowse = SHBrowseForFolder(&bi); 
	if (pidlBrowse != NULL) { 
		// Show the display name, title, and file system path. 
		if (SHGetPathFromIDList(pidlBrowse, lpBuffer)) { 
			UpdateData(true);
			m_szFolder = lpBuffer; 
			UpdateData(false);
		}
		// Free the PIDL returned by SHBrowseForFolder. 
		g_pMalloc->Free(pidlBrowse); 
	} 

	// Clean up. 
	g_pMalloc->Free(pidlPrograms); 
	g_pMalloc->Free(lpBuffer); 
	g_pMalloc->Release();
}

void CHbbsignupDlg::Pump()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		DispatchMessage(&msg);
}

BOOL CALLBACK CHbbsignupDlg::EnumSearchWindow(HWND hwnd, LPARAM lParam)
{
	Pump();
	CHbbsignupDlg* pThis = (CHbbsignupDlg*)lParam;
	TCHAR szCaption[MAX_PATH];
	::GetWindowText(hwnd, szCaption, MAX_PATH);
	if ((_tcscmp(szCaption, pThis->m_szSearchCaption) == 0) &&
		(!pThis->m_hParentWnd || pThis->m_hParentWnd == ::GetParent(hwnd))) {
		pThis->m_hFoundWnd = hwnd;
		return FALSE;
	}
	return TRUE;
}

HWND CHbbsignupDlg::SearchWindow(HWND hParent, LPCTSTR pszCaption, HWND hFather)
{
	m_hFoundWnd = NULL;
	m_hParentWnd = hFather;
	_tcscpy(m_szSearchCaption, pszCaption);
	for (int i = 0; i < 10 && !m_hFoundWnd; ++i) {
		if (hParent) {
			EnumChildWindows(hParent, EnumSearchWindow, (LPARAM)this);
		} else {
			EnumWindows(EnumSearchWindow, (LPARAM)this);
		}
		Sleep(1000);
	}
	return m_hFoundWnd;
}

BOOL CHbbsignupDlg::PushButton(HWND hParent, UINT id)
{
	Pump();
	HWND hCtl = ::GetDlgItem(hParent, id);
	if (!hCtl)
		return FALSE;
	::PostMessage(hParent, WM_COMMAND, (WPARAM)MAKELONG(id, BN_CLICKED), (LPARAM)hCtl);
	return TRUE;
}

BOOL CALLBACK CHbbsignupDlg::EnumSearchStatic(HWND hwnd, LPARAM lParam)
{
	Pump();
	CHbbsignupDlg* pThis = (CHbbsignupDlg*)lParam;
	TCHAR szCaption[MAX_PATH];
	::GetWindowText(hwnd, szCaption, MAX_PATH);
	if (_tcscmp(szCaption, pThis->m_szSearchCaption) == 0) {
		pThis->m_hStaticWnd = hwnd;
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK CHbbsignupDlg::EnumSearchControl(HWND hwnd, LPARAM lParam)
{
	EnumChildWindows(hwnd, EnumSearchStatic, lParam);
	CHbbsignupDlg* pThis = (CHbbsignupDlg*)lParam;
	if (pThis->m_hStaticWnd) {
		pThis->m_hFoundWnd = ::GetDlgItem(hwnd, pThis->m_nEditID);
		if (pThis->m_hFoundWnd) {
			pThis->m_hParentWnd = hwnd;
			return FALSE;
		}
	}
	return TRUE;
}

HWND CHbbsignupDlg::SearchControl(HWND hParent, LPCTSTR pszCaption, UINT id)
{
	m_hFoundWnd = NULL;
	m_hParentWnd = NULL;
	m_hStaticWnd = NULL;
	m_nEditID = id;

	_tcscpy(m_szSearchCaption, pszCaption);
	for (int i = 0; i < 10 && !m_hFoundWnd; ++i) {
		EnumChildWindows(hParent, EnumSearchControl, (LPARAM)this);
		Sleep(1000);
	}

	return m_hFoundWnd;
}

BOOL CHbbsignupDlg::StartWizard(LPCTSTR pszProg, LPCTSTR pszCabFile)
{
	TCHAR szCmd[1024];
	TCHAR szMyName[MAX_PATH];
	TCHAR szShortName[MAX_PATH];
	LPTSTR pszStr;

	GetModuleFileName(NULL, szMyName, MAX_PATH);
	GetShortPathName(szMyName, szShortName, MAX_PATH);
	pszStr = _tcsrchr(szShortName, '\\');
	++pszStr;
	_tcscpy(pszStr, pszProg);
	_stprintf(szCmd, "%s signwizard", szShortName);

	PROCESS_INFORMATION processInformation;
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	ZeroMemory(&processInformation, sizeof(processInformation));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = SW_MINIMIZE;
	if (!CreateProcess(NULL, szCmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation)) {
		MessageBox(_T("プログラムの起動に失敗しました。"), pszProg, MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	HWND hDlg;
	HWND hWnd;
	HWND hCtrl;

	// 初期ページ
	hDlg = SearchWindow(NULL, _T("デジタル署名ウィザード"));
	if (!hDlg) {
		MessageBox(_T("デジタル署名ウィザードが見つかりません。"), pszProg, MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("デジタル署名ウィザード"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// CABファイル指定
	hWnd = SearchControl(hDlg, _T("ファイルの選択"), 0x3EB);
	if (!hWnd) {
		MessageBox(_T("エディットコントロールが見つかりません。"), _T("ファイルの選択"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)pszCabFile);
	hWnd = SearchWindow(hDlg, _T("次へ(&N) >"));
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("ファイルの選択"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// 署名オプション
	hWnd = SearchControl(hDlg, _T("署名のオプション"), 0x3F4);
	if (!hWnd) {
		MessageBox(_T("ラジオボタンが見つかりません。"), _T("署名のオプション"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::CheckDlgButton(m_hParentWnd, 0x3F3, BST_UNCHECKED);
	::CheckDlgButton(m_hParentWnd, 0x3F4, BST_CHECKED);
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("署名のオプション"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// 証明書の署名
	hWnd = SearchControl(hDlg, _T("証明書の署名"), 0x427);
	if (!hWnd) {
		MessageBox(_T("ボタンが見つかりません。"), _T("証明書の署名"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::PostMessage(m_hParentWnd, WM_COMMAND, (WPARAM)MAKELONG(0x427, BN_CLICKED), (LPARAM)hWnd);

	// ファイルの選択
	hWnd = SearchWindow(NULL, _T("ファイルを開く"), hDlg);
	if (!hWnd) {
		MessageBox(_T("ファイルダイアログが見つかりません。"), _T("ファイルを開く"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	hCtrl = ::GetDlgItem(hWnd, 0x47C);
	if (!hCtrl) {
		MessageBox(_T("「ファイル名」が見つかりません。"), _T("ファイルを開く"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::SendMessage(hCtrl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_szCert);
	if (!PushButton(hWnd, 1)) {
		MessageBox(_T("「開く」が見つかりません。"), _T("ファイルを開く"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("ファイルを開く"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// 秘密鍵ファイル指定
	hWnd = SearchControl(hDlg, _T("秘密キー"), 0x43A);
	if (!hWnd) {
		MessageBox(_T("エディットコントロールが見つかりません。"), _T("秘密キー"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_szPvk);
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("秘密キー"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// ダイアログにパスワード入力
	hWnd = SearchWindow(NULL, _T("秘密キーのパスワードの入力"));
	if (!hWnd) {
		MessageBox(_T("パスワード入力ダイアログが見つかりません。"), _T("秘密キーのパスワードの入力"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	hCtrl = ::GetDlgItem(hWnd, 0x1F5);
	if (!hCtrl) {
		MessageBox(_T("「パスワード」が見つかりません。"), _T("秘密キーのパスワードの入力"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::SendMessage(hCtrl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_szPassword);
	if (!PushButton(hWnd, 1)) {
		MessageBox(_T("「OK」が見つかりません。"), _T("秘密キーのパスワードの入力"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// ハッシュアルゴリズムの選択
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("ハッシュアルゴリズムの選択"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// 追加の証明書
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("追加の証明書"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// データの説明
	hWnd = SearchControl(hDlg, _T("データの説明"), 0x3EB);
	if (!hWnd) {
		MessageBox(_T("エディットコントロールが見つかりません。"), _T("データの説明"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_szExplain);
	hWnd = SearchControl(hDlg, _T("データの説明"), 0x3EC);
	if (!hWnd) {
		MessageBox(_T("エディットコントロールが見つかりません。"), _T("データの説明"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_szWeb);
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("データの説明"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// タイムスタンプ
	hWnd = SearchControl(hDlg, _T("タイムスタンプ"), 0x3EA);
	if (!hWnd) {
		MessageBox(_T("チェックボックスが見つかりません。"), _T("タイムスタンプ"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::CheckDlgButton(m_hParentWnd, 0x3EA, BST_CHECKED);
	hWnd = SearchControl(hDlg, _T("タイムスタンプ"), 0x3EB);
	if (!hWnd) {
		MessageBox(_T("エディットコントロールが見つかりません。"), _T("タイムスタンプ"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_szTimestamp);
	if (!PushButton(hDlg, 0x3024)) {
		MessageBox(_T("「次へ」が見つかりません。"), _T("タイムスタンプ"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	if (!PushButton(hDlg, 0x3025)) {
		MessageBox(_T("「完了」が見つかりません。"), _T("タイムスタンプ"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// ダイアログにパスワード入力
	hWnd = SearchWindow(NULL, _T("秘密キーのパスワードの入力"));
	if (!hWnd) {
		MessageBox(_T("パスワード入力ダイアログが見つかりません。"), _T("秘密キーのパスワードの入力"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	hCtrl = ::GetDlgItem(hWnd, 0x1F5);
	if (!hCtrl) {
		MessageBox(_T("「パスワード」が見つかりません。"), _T("秘密キーのパスワードの入力"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	::SendMessage(hCtrl, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)m_szPassword);
	if (!PushButton(hWnd, 1)) {
		MessageBox(_T("「OK」が見つかりません。"), _T("秘密キーのパスワードの入力"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	// 正常終了
	do {
		Sleep(100);
		hCtrl = NULL;
		hWnd = SearchWindow(NULL, _T("デジタル署名ウィザード"));
		if (hWnd) {
			if (::GetDlgItem(hWnd, 2) && ::GetDlgItem(hWnd, 0x14) && ::GetDlgItem(hWnd, 0xFFFF))
				hCtrl = ::GetDlgItem(hWnd, 2);
		}
	} while (!hCtrl);
	::SendMessage(hWnd, WM_COMMAND, (WPARAM)MAKELONG(2, BN_CLICKED), (LPARAM)hCtrl);

	return TRUE;
}

BOOL CHbbsignupDlg::StartProg(LPCTSTR pszProg, LPCTSTR pszParam)
{
	TCHAR szCmd[1024];
	TCHAR szMyName[MAX_PATH];
	TCHAR szShortName[MAX_PATH];
	LPTSTR pszStr;

	GetModuleFileName(NULL, szMyName, MAX_PATH);
	GetShortPathName(szMyName, szShortName, MAX_PATH);
	pszStr = _tcsrchr(szShortName, '\\');
	++pszStr;
	_tcscpy(pszStr, pszProg);
	_stprintf(szCmd, "%s /C \"%s %s > ..\\%s.log\"", getenv("COMSPEC"), szShortName, pszParam, pszProg);
//DebugLog("%s\r\n", szCmd);

	PROCESS_INFORMATION processInformation;
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	ZeroMemory(&processInformation, sizeof(processInformation));
	startupInfo.cb = sizeof(startupInfo);
	if (CreateProcess(NULL, szCmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation)) {
		WaitForSingleObject(processInformation.hProcess, INFINITE);
	//	CloseHandle(processInformation.hProcess);
	//	CloseHandle(processInformation.hThread);
	} else {
		MessageBox(_T("プログラムの起動に失敗しました。"), pszProg, MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	return TRUE;
}

void CHbbsignupDlg::OnOK() 
{
	TCHAR szMyName[MAX_PATH];
	TCHAR szShortName[MAX_PATH];
	TCHAR szIniFile[MAX_PATH];
	TCHAR szCabFile[MAX_PATH];
	LPTSTR pszStr;
	CStdioFile file;

	UpdateData(TRUE);

	if (m_szServer.IsEmpty()) {
		MessageBox(_T("サーバー名が入力されていません。"), _T("サーバー名エラー"), MB_ICONSTOP|MB_OK);
		return;
	}
	if (m_szPrefix.IsEmpty()) {
		MessageBox(_T("ユーザー名のPrefixが入力されていません。"), _T("Prefixエラー"), MB_ICONSTOP|MB_OK);
		return;
	}
	if (m_szFolder.IsEmpty()) {
		MessageBox(_T("作成先フォルダーが入力されていません。"), _T("フォルダーエラー"), MB_ICONSTOP|MB_OK);
		return;
	}
	if (m_szCert.IsEmpty()) {
		MessageBox(_T("証明書ファイル名が入力されていません。"), _T("証明書エラー"), MB_ICONSTOP|MB_OK);
		return;
	}
	if (m_szPassword.IsEmpty()) {
		MessageBox(_T("パスワードが入力されていません。"), _T("パスワードエラー"), MB_ICONSTOP|MB_OK);
		return;
	}

	GetModuleFileName(NULL, szMyName, MAX_PATH);
	GetShortPathName(szMyName, szShortName, MAX_PATH);
	pszStr = _tcsrchr(szShortName, '\\');
	++pszStr;
	*pszStr = _T('\0');

	_tcscpy(szCabFile, szShortName);
	_tcscat(szCabFile, _T("source\\"));
	_tcscat(szCabFile, m_szCab);

	_tcscpy(szIniFile, szShortName);
	_tcscat(szIniFile, _T("source\\"));
	_tcscat(szIniFile, m_szIni);

	CProgressDlg dlg;
	dlg.Create(IDD_PROGRESSDLG_DIALOG, this);
	dlg.ShowWindow(SW_SHOW);
	dlg.SetMax(m_nEnd - m_nStart);

	for (UINT i = m_nStart; i <= m_nEnd; ++i) {
		WIN32_FIND_DATA find;
		HANDLE hFind;
		CString szURL;
		CString szTo;

		szURL.Format(_T("%s%04d"), (LPCTSTR)m_szPrefix, i);
		dlg.SetCur(szURL, i - m_nStart);
		if (dlg.Canceled()) {
			dlg.DestroyWindow();
			return;
		}

		if (!file.Open(szIniFile, CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone)) {
			dlg.DestroyWindow();
			MessageBox(_T("hotbizbar.iniファイルを作成できません。"), _T("エラー"), MB_ICONSTOP|MB_OK);
			return;
		}
		file.WriteString(_T("[hotbizbar]\r\n"));
		szURL.Format(_T("URL=https://%s/%s%04d/\r\n"), (LPCTSTR)m_szServer, (LPCTSTR)m_szPrefix, i);
		file.WriteString(szURL);
		file.Close();

		_tcscpy(szMyName, szShortName);
		_tcscat(szMyName, _T("source"));
		SetCurrentDirectory(szMyName);

		hFind = FindFirstFile(_T("*.*"), &find);
		if (hFind == INVALID_HANDLE_VALUE) {
			dlg.DestroyWindow();
			MessageBox(_T("ファイルの検索に失敗しました。"), _T("エラー"), MB_ICONSTOP|MB_OK);
			return;
		}
		szURL.Format(_T("-s 6144 N %s"), m_szCab);
		do {
			if (!(find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				szURL += _T(" ");
				szURL += find.cFileName;
			}
		} while (FindNextFile(hFind, &find));
		FindClose(hFind);
		StartProg(_T("cabarc.exe"), szURL);

	//	SetCurrentDirectory(szMyName);
	//	szURL.Format(_T("sign /f %s /p %s /d %s /du %s /t %s %s"), szPfxFile, (LPCTSTR)m_szPassword, g_szHotBizBarTTL, g_szHotBizBarURL, g_szTimeStampURL, g_szHotBizBarCAB);
		StartWizard(_T("SignTool.exe"), szCabFile);

		szURL = m_szFolder;
		if (szURL.GetAt(szURL.GetLength()-1) != _T('\\'))
			szURL += _T("\\");
		szTo.Format(_T("%s%s%04d"), (LPCTSTR)szURL, (LPCTSTR)m_szPrefix, i);
		CreateDirectory(szTo, NULL);
		szTo += _T("\\public_html");
		CreateDirectory(szTo, NULL);
		szTo += _T("\\");
		szTo += m_szCab;
		MoveFile(m_szCab, szTo);
		DeleteFile(szIniFile);
	}
	dlg.DestroyWindow();
	MessageBox(_T("完了しました。"), _T("正常終了"), MB_ICONINFORMATION|MB_OK);

//	CDialog::OnOK();
}

void CHbbsignupDlg::OnRefspc() 
{
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, _T("spc"), m_szCert, OFN_FILEMUSTEXIST, _T("証明書ファイル(*.spc)|*.spc|すべてのファイル(*.*)|*.*||"));
	if (dlg.DoModal() == IDOK) {
		m_szCert = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CHbbsignupDlg::OnRefpvk() 
{
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, _T("pvk"), m_szPvk, OFN_FILEMUSTEXIST, _T("秘密鍵ファイル(*.pvk)|*.pvk|すべてのファイル(*.*)|*.*||"));
	if (dlg.DoModal() == IDOK) {
		m_szPvk = dlg.GetPathName();
		UpdateData(FALSE);
	}
}
