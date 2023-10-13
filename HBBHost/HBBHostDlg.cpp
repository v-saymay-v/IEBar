// HBBHostDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include <Mmsystem.h>
#include "HBBHost.h"
#include "HBBHostDlg.h"
#include "AboutDlg.h"
#include "LoginDlg.h"
#include "HBBCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct _STR_DATA {
	LPCTSTR pszString;
	DWORD dwData;
} STR_DATA;

static STR_DATA oInterval[] = {
	{_T("30秒"), 30000},
	{_T("1分"), 60000},
	{_T("3分"), 180000},
	{_T("5分"), 300000},
	{_T("10分"), 600000},
	{_T("15分"), 900000},
	{_T("30分"), 1800000},
	{_T("1時間"), 3600000}
};

static TCHAR g_szHelpURL[] = _T("http://www.hotbiz.ne.jp/help/toolbar.htm");

/////////////////////////////////////////////////////////////////////////////
// CHBBHostDlg ダイアログ

CHBBHostDlg::CHBBHostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHBBHostDlg::IDD, pParent)
{
	HKEY hKey;
	TCHAR szFile[MAX_PATH];
	BOOL bAutoStart = FALSE;
	DWORD nInterval;
	DWORD nPopupTime;
	BOOL bPlaySound;

	GetNewsInfo(m_bRecvInfo, nInterval, nPopupTime, bPlaySound, szFile);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		TCHAR szStart[MAX_PATH];
		DWORD type = REG_SZ;
		DWORD size = sizeof(szStart);
		ZeroMemory(szStart, sizeof(szStart));
		LONG nErr = RegQueryValueEx(hKey, _T("HotBizBar"), NULL, &type, (LPBYTE)&szStart, &size);
		if (nErr == ERROR_SUCCESS) {
			TCHAR szProg[MAX_PATH];
			GetModuleFileName(NULL, szProg, ARRAYSIZE(szProg));
			bAutoStart = (_tcsicmp(szStart, szProg) == 0);
		}
		RegCloseKey(hKey);
	}

	//{{AFX_DATA_INIT(CHBBHostDlg)
	m_bAutoStart = bAutoStart;
	m_nInterval = nInterval;
	m_bPlaySound = bPlaySound;
	m_nPopupTime = nPopupTime/1000;
	m_szSoundFile = szFile;
	m_szStatus = _T("");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
}

CHBBHostDlg::~CHBBHostDlg()
{
	ClearVector();
}

void CHBBHostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHBBHostDlg)
	DDX_Control(pDX, IDC_STOPSTART, m_btnStartStop);
	DDX_Check(pDX, IDC_AUTOSTART, m_bAutoStart);
	DDX_CBIndex(pDX, IDC_INTERVAL, m_nInterval);
	DDX_Check(pDX, IDC_PLAYSOUND, m_bPlaySound);
	DDX_Text(pDX, IDC_POPUPTIME, m_nPopupTime);
	DDX_Text(pDX, IDC_SOUNDFILE, m_szSoundFile);
	DDX_Text(pDX, IDC_STATUS, m_szStatus);
	//}}AFX_DATA_MAP
}

void CHBBHostDlg::ClearVector()
{
	std::vector<CPopupDlg*>::iterator it;
	for (it = m_popup.begin(); it != m_popup.end(); ++it) {
		if (::IsWindow((*it)->m_hWnd))
			::DestroyWindow((*it)->m_hWnd);
		delete (*it);
	}
	m_popup.clear();

	std::vector<CPopupInfo*>::iterator iti;
	for (iti = m_pupInfo.begin(); iti != m_pupInfo.end(); ++iti) {
		delete (*iti);
	}
	m_pupInfo.clear();
}

BOOL CHBBHostDlg::Create(CWnd* pParentWnd) 
{
	return CDialog::Create(IDD, pParentWnd);
}

void CHBBHostDlg::ChangeTrayIcon(UINT idIcon, UINT idMess)
{
	CString szMess, szTip;

	szTip.LoadString(AFX_IDS_APP_TITLE);
	AfxFormatString1(szMess, idMess, szTip);

	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd; 
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_MY_NOTIFYICON;
	nid.hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(idIcon), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	lstrcpy(nid.szTip, szMess);
	Shell_NotifyIcon(NIM_MODIFY, &nid);
	if (nid.hIcon)
		DestroyIcon(nid.hIcon); 
}

BOOL CALLBACK CHBBHostDlg::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	vector<HWND>* p = (vector<HWND>*)lParam;
	p->push_back(hwnd);
	return TRUE;
}

void CHBBHostDlg::UpdateHBBStatus(HWND hwnd, ATOM atom)
{
	int j;
	vector<HWND> children;

	EnumChildWindows(hwnd, EnumWindowsProc, (LPARAM)&children);
	for (j = 0; j < (int)children.size(); ++j) {
		TCHAR szClassName[256];
		::GetClassName(children[j], szClassName, ARRAYSIZE(szClassName));
		if (_tcsicmp(szClassName, _T(HOTBIZBARCLASS)) == 0) {
			::SendMessage(children[j], WM_HBBUPDATE, 0, (LPARAM)atom);
		}
	}
	children.clear();
	for (j = 0; j < (int)children.size(); ++j) {
		UpdateHBBStatus(children[j], atom);
	}
}

void CHBBHostDlg::CountHBBWindow(HWND hwnd, int& nCnt)
{
	int j;
	vector<HWND> children;
	EnumChildWindows(hwnd, EnumWindowsProc, (LPARAM)&children);
	for (j = 0; j < (int)children.size(); ++j) {
		TCHAR szClassName[256];
		::GetClassName(children[j], szClassName, ARRAYSIZE(szClassName));
		if (_tcsicmp(szClassName, _T(HOTBIZBARCLASS)) == 0) {
			++nCnt;
		}
	}
	children.clear();
	for (j = 0; j < (int)children.size(); ++j) {
		CountHBBWindow(children[j], nCnt);
	}
}

void CHBBHostDlg::SendHBBLogin(HWND hwnd, UINT nMess)
{
	int j;
	vector<HWND> children;
	EnumChildWindows(hwnd, EnumWindowsProc, (LPARAM)&children);
	for (j = 0; j < (int)children.size(); ++j) {
		TCHAR szClassName[256];
		::GetClassName(children[j], szClassName, ARRAYSIZE(szClassName));
		if (_tcsicmp(szClassName, _T(HOTBIZBARCLASS)) == 0) {
			::PostMessage(children[j], nMess, 0, 0);
		}
	}
	for (j = 0; j < (int)children.size(); ++j) {
		SendHBBLogin(children[j], nMess);
	}
}

void CHBBHostDlg::ChangeStatus()
{
	if (m_bRecvInfo) {
		m_btnStartStop.SetWindowText(_T("停止する(&S)"));
		m_szStatus = _T("開始");
		ChangeTrayIcon(IDI_LOGGEDIN, IDS_LOGGEDIN);
	} else {
		m_btnStartStop.SetWindowText(_T("開始する(&S)"));
		m_szStatus = _T("停止");
		ChangeTrayIcon(IDI_STOPPED, IDS_STOPPED);
	}
	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CHBBHostDlg, CDialog)
	//{{AFX_MSG_MAP(CHBBHostDlg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_REFER, OnRefer)
	ON_BN_CLICKED(IDC_STOPSTART, OnStopstart)
	ON_MESSAGE(WM_MY_NOTIFYICON, OnMyNotifyIcon)
	ON_MESSAGE(WM_HBBLOGIN, OnHbbLogin)
	ON_MESSAGE(WM_HBBLOGOUT, OnHbbLogout)
	ON_MESSAGE(WM_HBBQUIT, OnHbbQuit)
	ON_COMMAND(IDM_ABOUTBOX, OnAboutBox)
	ON_COMMAND(IDM_HBLOGIN, OnLogin)
	ON_COMMAND(IDM_HBLOGOUT, OnLogout)
	ON_COMMAND(IDM_HBHISTORY, OnHistory)
	ON_COMMAND(IDM_HBHHELP, OnHbhhelp)
	ON_COMMAND(IDM_HBHOPTION, OnHbhoption)
	ON_COMMAND(IDM_HBHQUIT, OnHbhquit)
	ON_COMMAND(IDM_STARTSTOP, OnStopstart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHBBHostDlg メッセージ ハンドラ

BOOL CHBBHostDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	::SetWindowLong(m_hWnd, GWL_USERDATA, 'HBBH');
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定

	int nSel = 0;
	CWnd* pDlgItem = GetDlgItem(IDC_INTERVAL);
	for (int i = 0; i < ARRAYSIZE(oInterval); ++i) {
		pDlgItem->SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)oInterval[i].pszString);
		pDlgItem->SendMessage(CB_SETITEMDATA, i, (LPARAM)oInterval[i].dwData);
		if (oInterval[i].dwData == (DWORD)m_nInterval)
			nSel = i;
	}
	pDlgItem->SendMessage(CB_SETCURSEL, nSel, 0);

	pDlgItem = GetDlgItem(IDC_PPTMSPIN);
	pDlgItem->SendMessage(UDM_SETRANGE, 0, MAKELONG(999, 1));

	ChangeStatus();
	if (AlreadyLoggedin())
		m_btnStartStop.EnableWindow();

	ClearVector();
	if (m_bRecvInfo && m_nInterval >= 30000) {
		SetTimer(1, m_nInterval, NULL);
		SetTimer(2, 500, NULL);
	}

	return FALSE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CHBBHostDlg::OnPaint() 
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
HCURSOR CHBBHostDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHBBHostDlg::OnPlay() 
{
	UpdateData(TRUE);
	PlaySound(m_szSoundFile, AfxGetInstanceHandle(), SND_FILENAME);
}

void CHBBHostDlg::OnRefer() 
{
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, _T("wav"), m_szSoundFile, OFN_FILEMUSTEXIST, _T("サウンドファイル(*.wav)|*.wav|すべてのファイル(*.*)|*.*||"));
	if (dlg.DoModal() == IDOK) {
		m_szSoundFile = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CHBBHostDlg::OnOK() 
{
	UpdateData(TRUE);
	if (m_nPopupTime < 1 || m_nPopupTime > 999) {
		MessageBox(_T("新着ウィンドウの表示時間は１～９９９の値を指定してください。"), _T("エラー"), MB_ICONSTOP|MB_OK);
		return;
	}
	m_nInterval = oInterval[m_nInterval].dwData;
	SetNewsInfo(m_bRecvInfo, m_nInterval, m_nPopupTime*1000, m_bPlaySound, m_szSoundFile);

	if (m_bRecvInfo && m_nInterval >= 30000) {
		KillTimer(1);
		SetTimer(1, m_nInterval, NULL);
	}

	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), NULL, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
		if (m_bAutoStart) {
			TCHAR szProg[MAX_PATH];
			GetModuleFileName(NULL, szProg, ARRAYSIZE(szProg));
			RegSetValueEx(hKey, _T("HotBizBar"), NULL, REG_SZ, (const BYTE*)&szProg, (_tcslen(szProg)+1)*sizeof(TCHAR));
		} else {
			RegDeleteValue(hKey, _T("HotBizBar"));
		}
		RegCloseKey(hKey);
	}
	ShowWindow(SW_HIDE);
}

LONG CHBBHostDlg::OnMyNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	switch (lParam) {
		case WM_LBUTTONDBLCLK: {
			ShowWindow(SW_RESTORE);
			SetForegroundWindow();
			break;
		}
		case WM_RBUTTONUP: {
			CPoint pt;
			HMENU hMenu = LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
			HMENU hSub = GetSubMenu(hMenu, 0);
			MENUITEMINFO mi;
			TCHAR szString[] = _T("開始(&S)");

			ZeroMemory(&mi, sizeof(mi));
			mi.cbSize = sizeof(mi);
			mi.fMask = MIIM_STATE;
			mi.fState = AlreadyLoggedin() ? MFS_ENABLED : MFS_DISABLED;
			if (!m_bRecvInfo) {
				mi.fMask |= MIIM_STRING;
				mi.dwTypeData = szString;
				mi.cch = sizeof(szString);
			}
			::SetMenuItemInfo(hSub, IDM_STARTSTOP, FALSE, &mi);

			if (AlreadyLoggedin()) {
				TCHAR szLogout[] = _T("ログアウト(&N)");
				ZeroMemory(&mi, sizeof(mi));
				mi.cbSize = sizeof(mi);
				mi.fMask = MIIM_ID | MIIM_STRING;
				mi.wID = IDM_HBLOGOUT;
				mi.dwTypeData = szLogout;
				mi.cch = sizeof(szLogout);
				SetMenuItemInfo(hSub, 2, TRUE, &mi);
			}

			GetCursorPos(&pt);
			SetForegroundWindow();
			::TrackPopupMenuEx(hSub, TPM_RIGHTALIGN|TPM_LEFTBUTTON|TPM_VERPOSANIMATION, pt.x, pt.y, m_hWnd, NULL);
			::DestroyMenu(hSub);
			::DestroyMenu(hMenu);
			break;
		}
	}
	return 0;
}

LONG CHBBHostDlg::OnHbbLogin(WPARAM wParam, LPARAM lParam)
{
	Reload();
	ChangeTrayIcon(m_bRecvInfo?IDI_LOGGEDIN:IDI_STOPPED, m_bRecvInfo?IDS_LOGGEDIN:IDS_STOPPED);
	if (m_bRecvInfo && m_nInterval >= 30000) {
		SetTimer(1, m_nInterval, NULL);
		SetTimer(2, 500, NULL);
	}
	m_btnStartStop.EnableWindow();
	return 0;
}

LONG CHBBHostDlg::OnHbbLogout(WPARAM wParam, LPARAM lParam)
{
	LogoutHotBiz();
	m_btnStartStop.EnableWindow(FALSE);
	ChangeTrayIcon(IDR_MAINFRAME, IDS_NOTLOGGEDIN);
	return 0;
}

LONG CHBBHostDlg::OnHbbQuit(WPARAM wParam, LPARAM lParam)
{
	::PostQuitMessage(0);
	return 0;
}

void CHBBHostDlg::OnAboutBox()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CHBBHostDlg::OnLogin()
{
	CLoginDlg dlgLogin;
	if (dlgLogin.DoModal() == IDOK) {
		if (!dlgLogin.GetLoginResult()) {
			MessageBox(_T("ログインに失敗しました。ユーザー名とパスワードを確認してください。"), _T("エラー"), MB_ICONSTOP|MB_OK);
			return;
		}
		ChangeTrayIcon(m_bRecvInfo?IDI_LOGGEDIN:IDI_STOPPED, m_bRecvInfo?IDS_LOGGEDIN:IDS_STOPPED);
		if (m_bRecvInfo && m_nInterval >= 30000) {
			SetTimer(1, m_nInterval, NULL);
			SetTimer(2, 500, NULL);
		}
		m_btnStartStop.EnableWindow();
		SendHBBLogin(GetDesktopWindow()->GetSafeHwnd(), WM_HBBLOGIN);
	}
}

void CHBBHostDlg::OnLogout()
{
	LogoutHotBiz();
	m_btnStartStop.EnableWindow(FALSE);
	ChangeTrayIcon(IDR_MAINFRAME, IDS_NOTLOGGEDIN);
	SendHBBLogin(GetDesktopWindow()->GetSafeHwnd(), WM_HBBLOGOUT);
}

void CHBBHostDlg::OnHistory()
{
	UINT nRT;
	HOTBIZFUNC nFunc;
	long nObject;
	LogDialog(nRT, nFunc, nObject);
	if (nRT == IDOK)
		CPopupDlg::DispFuncObj(nFunc, nObject);
}

void CHBBHostDlg::OnTimer(UINT nIDEvent) 
{
	char szYear[5];
	char szMonth[3];
	char szDay[3];
	char szHour[3];
	char szMinute[3];
	char szSecond[3];
	BOOL bAutoLogin;
	TCHAR szURL[256];
	TCHAR szUserName[21];
	TCHAR szPassword[21];

	KillTimer(nIDEvent);

	if (!AlreadyLoggedin())
		return;

	switch (nIDEvent) {
		case 1: {
			time_t last = GetServerTime();
			GetLoginInfo(bAutoLogin, szURL, ARRAYSIZE(szURL), szUserName, ARRAYSIZE(szUserName), szPassword, ARRAYSIZE(szPassword));
			do {
				struct tm mt;
				TCHAR szAtom[1024];
				LPCSTR pszHtml;
				LPSTR* szFields;
				bool bEOF;
				time_t t;
				int nFields;

				if (!ConnectToHotBiz(szUserName, szPassword, FNC_MAIN, _T("mode=HBBGetLog")))
					break;
				pszHtml = HotBizResult();
				if (pszHtml[0] == '<')
					break;

				ReadLine(pszHtml, &szFields, nFields, bEOF);
				if (nFields < 7) {
					FreeReadLine(szFields, nFields);
					break;
				}

				TCHAR szGo[5];
				TCHAR szLv[5];
#ifdef _UNICODE
				ZeroMemory(szGo, sizeof(szGo));
				ZeroMemory(szLv, sizeof(szLv));
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[5], strlen(szFields[5]), szGo, ARRAYSIZE(szGo));
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[6], strlen(szFields[6]), szLv, ARRAYSIZE(szLv));
#else
				strcpy(szGo, szFields[5]);
				strcpy(szLv, szFields[6]);
#endif
				if (!szGo[0])
					_tcscpy_s(szGo, sizeof(szGo), _T("----"));
				if (!szLv[0])
					_tcscpy_s(szLv, sizeof(szLv), _T("----"));
				_stprintf_s(szAtom, sizeof(szAtom), _T("%s\r\n%s\r\n%d\r\n"), szGo, szLv, atoi(szFields[4]));

				ATOM atom = GlobalAddAtom(szAtom);
				FreeReadLine(szFields, nFields);
				UpdateHBBStatus(GetDesktopWindow()->GetSafeHwnd(), atom);
				GlobalDeleteAtom(atom);

				do {
					ReadLine(pszHtml, &szFields, nFields, bEOF);
					if (nFields < 8) {
						FreeReadLine(szFields, nFields);
						break;
					}
					strncpy_s(szYear, sizeof(szYear), szFields[4], sizeof(szYear)-1);
					szYear[sizeof(szYear)-1] = '\0';
					strncpy_s(szMonth, sizeof(szMonth), szFields[4]+4, sizeof(szMonth)-1);
					szMonth[sizeof(szMonth)-1] = '\0';
					strncpy_s(szDay, sizeof(szDay), szFields[4]+6, sizeof(szDay)-1);
					szDay[sizeof(szDay)-1] = '\0';
					strncpy_s(szHour, sizeof(szHour), szFields[5], sizeof(szHour)-1);
					szHour[sizeof(szHour)-1] = '\0';
					strncpy_s(szMinute, sizeof(szMinute), szFields[5]+2, sizeof(szMinute)-1);
					szMinute[sizeof(szMinute)-1] = '\0';
					strncpy_s(szSecond, sizeof(szSecond), szFields[5]+4, sizeof(szSecond)-1);
					szSecond[sizeof(szSecond)-1] = '\0';

					t = GetLastChecked();
					localtime_s(&mt, &t);
					mt.tm_year = atoi(szYear) - 1900;
					mt.tm_mon = atoi(szMonth) - 1;
					mt.tm_mday = atoi(szDay);
					mt.tm_hour = atoi(szHour);
					mt.tm_min = atoi(szMinute);
					mt.tm_sec = atoi(szSecond);
					t = mktime(&mt);

					if (t > GetLastChecked()) {
						CPopupInfo* pInfo = new CPopupInfo(szFields[6], szFields[7], atoi(szFields[0]), atoi(szFields[1]));
						m_pupInfo.push_back(pInfo);
						HistoryAdd(szFields, nFields);
					}
					FreeReadLine(szFields, nFields);

				} while (!bEOF);
			} while (false);

			SetLastChecked(last);
			if (m_bRecvInfo && m_nInterval >= 30000)
				SetTimer(1, m_nInterval, NULL);
			break;
		}
		case 2: {
			if (m_pupInfo.size()) {
				RECT rc;
				int cnt;
				int hei = 0;
				for (cnt = 0; cnt < (int)m_popup.size(); ++cnt) {
					if (!IsWindow(m_popup[cnt]->m_hWnd)) {
						break;
					} else if (!hei) {
						::GetWindowRect(m_popup[cnt]->m_hWnd, &rc);
						hei = rc.bottom - rc.top;
					}
				}
				if (hei) {
					SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
					if (cnt >= (rc.bottom - rc.top) / hei) {
						cnt = -1;
					}
				}
				if (cnt != -1) {
					std::vector<CPopupInfo*>::iterator it = m_pupInfo.begin();
					CPopupDlg* pDlg = new CPopupDlg(cnt, (*it)->m_nFunc, (*it)->m_nObject, (*it)->m_szTitle, (*it)->m_szMess, GetFocus()->GetSafeHwnd());
					if (pDlg->Create()) {
						if (cnt >= (int)m_popup.size()) {
							m_popup.push_back(pDlg);
						} else {
							delete m_popup[cnt];
							m_popup[cnt] = pDlg;
						}
						CPopupInfo* p = *it;
						m_pupInfo.erase(it);
						delete (p);
					}
				}
			}
			SetTimer(2, 500, NULL);
			break;
		}
	}
}

void CHBBHostDlg::OnStopstart() 
{
	UpdateData(TRUE);
	m_bRecvInfo = !m_bRecvInfo;
	ChangeStatus();
	m_nInterval = oInterval[m_nInterval].dwData;
	SetNewsInfo(m_bRecvInfo, m_nInterval, m_nPopupTime*1000, m_bPlaySound, m_szSoundFile);
	if (m_bRecvInfo) {
		if (m_nInterval >= 30000) {
			SetTimer(1, m_nInterval, NULL);
			SetTimer(2, 500, NULL);
		}
	} else {
		KillTimer(1);
		KillTimer(2);
	}
}

void CHBBHostDlg::OnHbhhelp() 
{
	CPopupDlg::NavigateBrowser(g_szHelpURL);
}

void CHBBHostDlg::OnHbhoption() 
{
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();
//	PostMessage(WM_SYSCOMMAND, SC_RESTORE);
}

void CHBBHostDlg::OnHbhquit() 
{
	if (MessageBox(_T("終了すると、HotBizからの新着情報を受け取れなくなります。\r\n終了してもよろしいですか？"), _T("終了確認"), MB_ICONQUESTION|MB_YESNO) == IDYES) {
		int nCnt = 0;
		vector<HWND> parents;
		EnumWindows(EnumWindowsProc, (LPARAM)&parents);
		for (int i = 0; i < (int)parents.size(); ++i)
			CountHBBWindow(parents[i], nCnt);
		if (!nCnt)
			ClearLoginInfo();
		::PostQuitMessage(0);
	}
}
