//MFToolbar.cpp : Implementation of CMFToolbar

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson ｩ 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#include "stdafx.h"
#include "MFToolbar.h"
#include "HBIEBar.h"
#include "HotBizBar.h"
#include "HostPage.h"
#include "LoginDlg.h"
#include "WaitDlg.h"
#include "VersionDlg.h"
#include "hotbizconnection.h"
#include "hbhistory.h"
#include "os.h"

#ifndef CCM_SETVERSION
#define CCM_SETVERSION			(CCM_FIRST + 0x7)
#endif
#ifndef TBSTYLE_EX_MIXEDBUTTONS
#define TBSTYLE_EX_MIXEDBUTTONS	0x00000008
#endif
#ifndef BTNS_BUTTON
#define BTNS_BUTTON			TBSTYLE_BUTTON
#endif
#ifndef BTNS_SEP
#define BTNS_SEP			TBSTYLE_SEP
#endif
#ifndef BTNS_DROPDOWN
#define BTNS_DROPDOWN		TBSTYLE_DROPDOWN
#endif
#ifndef BTNS_AUTOSIZE
#define BTNS_AUTOSIZE		TBSTYLE_AUTOSIZE
#endif
#ifndef BTNS_WHOLEDROPDOWN
#define BTNS_WHOLEDROPDOWN	0x0080
#endif
#ifndef TBIF_BYINDEX
#define TBIF_BYINDEX		0x80000000
#endif

static TCHAR g_szHelpURL[] = _T("http://www.hotbiz.ne.jp/help/toolbar.htm");

/////////////////////////////////////////////////////////////////////////////
// CMFToolbar

CMFToolbar::CMFToolbar(CHotBizBar* pBar) : m_RebarContainer(NULL, this, 1)
{
	m_hImageList1 = NULL;
	m_hImageList2 = NULL;
	m_pBrowser = NULL;
	m_hToolTip = NULL;
	m_hStaticGo = NULL;
	m_hStaticLeave = NULL;
	m_nWhereButton = 0;
	m_hMainMenu = NULL;
	m_hWhereMenu = NULL;
	m_hCommonMenu = NULL;
	m_hPrivateMenu = NULL;
	m_hHelperMenu = NULL;
	m_hHyperCursor = NULL;
	m_pHotBizBar = pBar;
}

CMFToolbar::~CMFToolbar()
{
	int nCnt = 0;
	vector<HWND> parents;
	TCHAR szURL[256];
	TCHAR szUserName[21];
	TCHAR szPassword[21];
	BOOL bAutoSave;

	GetLoginInfo(bAutoSave, szURL, ARRAYSIZE(szURL), szUserName, ARRAYSIZE(szUserName), szPassword, ARRAYSIZE(szPassword));

	EnumWindows(EnumWindowProc, (LPARAM)&parents);
	for (int i = 0; i < (int)parents.size(); ++i) {
		if (::GetWindowLong(parents[i], GWL_USERDATA) == 'HBBH')
			++nCnt;
		else
			EnumCount(parents[i], nCnt);
	}
	if (nCnt <= 1)
		ClearLoginInfo();
	if (!bAutoSave)
		ClearUserPass();

	if (::IsWindow(m_RebarContainer.m_hWnd))
		m_RebarContainer.UnsubclassWindow();
	SetBrowser(NULL);
	if (m_hMainMenu)
		DestroyMenu(m_hMainMenu);
	if (m_hWhereMenu)
		DestroyMenu(m_hWhereMenu);
	if (m_hCommonMenu)
		DestroyMenu(m_hCommonMenu);
	if (m_hPrivateMenu)
		DestroyMenu(m_hPrivateMenu);
	if (m_hHelperMenu)
		DestroyMenu(m_hHelperMenu);
	if (m_hHyperCursor)
		::DestroyCursor(m_hHyperCursor);
	CleanupResource();
	if (IsWindow())
		DestroyWindow();
}

void CMFToolbar::CleanupResource()
{
	if (m_hImageList1)
		ImageList_Destroy(m_hImageList1);
	if (m_hImageList2)
		ImageList_Destroy(m_hImageList2);
	if (::IsWindow(m_hToolTip))
		::DestroyWindow(m_hToolTip);
	if (::IsWindow(m_hStaticGo))
		::DestroyWindow(m_hStaticGo);
	if (::IsWindow(m_hStaticLeave))
		::DestroyWindow(m_hStaticLeave);
}

BOOL CALLBACK CMFToolbar::EnumWindowProc(HWND hwnd, LPARAM lParam)
{
	vector<HWND>* p = (vector<HWND>*)lParam;
	p->push_back(hwnd);
	return TRUE;
}

void CMFToolbar::EnumCount(HWND hwnd, int& nCnt)
{
	int j;
	vector<HWND> children;
	EnumChildWindows(hwnd, EnumWindowProc, (LPARAM)&children);
	for (j = 0; j < (int)children.size(); ++j) {
		TCHAR szClassName[256];
		::GetClassName(children[j], szClassName, ARRAYSIZE(szClassName));
		if (_tcsicmp(szClassName, _T(HOTBIZBARCLASS)) == 0) {
			++nCnt;
		}
	}
	children.clear();
	for (j = 0; j < (int)children.size(); ++j) {
		EnumCount(children[j], nCnt);
	}
}

void CMFToolbar::EnumLogin(HWND hwnd, UINT nMess)
{
	int j;
	vector<HWND> children;
	EnumChildWindows(hwnd, EnumWindowProc, (LPARAM)&children);
	for (j = 0; j < (int)children.size(); ++j) {
		TCHAR szClassName[256];
		::GetClassName(children[j], szClassName, ARRAYSIZE(szClassName));
		if (_tcsicmp(szClassName, _T(HOTBIZBARCLASS)) == 0) {
			::SendMessage(children[j], nMess, 0, 0);
		}
	}
	children.clear();
	for (j = 0; j < (int)children.size(); ++j) {
		EnumLogin(children[j], nMess);
	}
}

BOOL CMFToolbar::AdminLogin()
{
	return (_tcsicmp(GetHotBizUserName(), _T("admin")) == 0);
}

void CMFToolbar::ClearButton()
{
	int nCnt = ::SendMessage(m_hWnd, TB_BUTTONCOUNT, 0, 0);
	for (int i = nCnt - 1; i >= 0; --i) {
		::SendMessage(m_hWnd, TB_DELETEBUTTON, i, 0);
	}
}

HOTBIZFUNC CMFToolbar::GetNextFunc(int nSEQ)
{
	PICON_ITEM pItem = GetIconItem();
	if (pItem) {
		for (int i = 0; i < ITEMTABLESIZE; ++i) {
			if (pItem[i].m_nSEQ == nSEQ)
				return (HOTBIZFUNC)i;
		}
	}
	return (HOTBIZFUNC)0;
}

void CMFToolbar::DrawTB()
{
	int i;
	int nBtn = 0;
	int nTtPos;
	int nLoginPos;
	int nTcPos;
	int nHisPos;
	int nSEQ;
	int nLogoX, nLogoY;
	int nIconX, nIconY;
	HOTBIZFUNC nFnc;
	HICON hMotley;
	TOOLINFO ti;
	TBBUTTON Button;
	TBBUTTONINFO BtnInfo;

	// Set commom control version.
	::SendMessage(m_hWnd, CCM_SETVERSION, 5, 0);
	// buttons with images and text
	::SendMessage(m_hWnd, TB_SETEXTENDEDSTYLE, 0, (LPARAM)TBSTYLE_EX_MIXEDBUTTONS);
	::SendMessage(m_hWnd, TB_SETEXTENDEDSTYLE, 0, (LPARAM)TBSTYLE_EX_DRAWDDARROWS);
	// Sets the size of the TBBUTTON structure.
	::SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
	// Set the maximum number of text rows and bitmap size.
	::SendMessage(m_hWnd, TB_SETMAXTEXTROWS, 1, 0);

	GetIconSize(nIconX, nIconY);
	GetLogoSize(nLogoX, nLogoY);

	m_hImageList1 = ImageList_Create(nLogoX, nLogoY, ILC_COLOR8|ILC_MASK, 1, 0);
	hMotley = LoadResourceIcon(MAKEINTRESOURCE(IDI_HOTBIZBAR), nLogoX, nLogoY);
	ImageList_AddIcon(m_hImageList1, hMotley);
	DestroyIcon(hMotley);

	m_hImageList2 = ImageList_Create(nIconX, nIconY, ILC_COLOR8|ILC_MASK, 1, 0);
	for (i = 0; i < ITEMTABLESIZE; ++i) {
		// load our button's icon and create the image list to house it.
		hMotley = LoadHotBizIcon(i, nIconX, nIconY);
		ImageList_AddIcon(m_hImageList2, hMotley);
		DestroyIcon(hMotley);
	}
	hMotley = LoadResourceIcon(MAKEINTRESOURCE(IDI_GOTIME), nIconX, nIconY);
	ImageList_AddIcon(m_hImageList2, hMotley);
	DestroyIcon(hMotley);
	hMotley = LoadResourceIcon(MAKEINTRESOURCE(IDI_LEAVETIME), nIconX, nIconY);
	ImageList_AddIcon(m_hImageList2, hMotley);
	DestroyIcon(hMotley);
	hMotley = LoadResourceIcon(MAKEINTRESOURCE(IDI_HISTORY), nIconX, nIconY);
	ImageList_AddIcon(m_hImageList2, hMotley);
	DestroyIcon(hMotley);
	hMotley = LoadResourceIcon(MAKEINTRESOURCE(IDI_LOGIN), nIconX, nIconY);
	ImageList_AddIcon(m_hImageList2, hMotley);
	DestroyIcon(hMotley);
	hMotley = LoadResourceIcon(MAKEINTRESOURCE(IDI_LOGOUT), nIconX, nIconY);
	ImageList_AddIcon(m_hImageList2, hMotley);
	DestroyIcon(hMotley);

	// Set the toolbar's image
	::SendMessage(m_hWnd, TB_SETBITMAPSIZE, 0, MAKELONG(nIconX,nIconY));
	::SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)m_hImageList2);
	::SendMessage(m_hWnd, TB_SETIMAGELIST, 1, (LPARAM)m_hImageList2);
	::SendMessage(m_hWnd, TB_SETIMAGELIST, 2, (LPARAM)m_hImageList1);

	// Draw buttons
	ZeroMemory((void*)&Button, sizeof(TBBUTTON));
	Button.idCommand = IDM_HOME;
	Button.fsState = TBSTATE_ENABLED;
	Button.fsStyle = BTNS_DROPDOWN | BTNS_BUTTON | BTNS_AUTOSIZE;
	Button.iString = -1;
	Button.iBitmap = MAKELONG(0, 2);
	::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
	++nBtn;

	ZeroMemory((void*)&Button, sizeof(TBBUTTON));
	Button.fsStyle = BTNS_SEP;
	::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
	++nBtn;

	nLoginPos = nBtn;
	ZeroMemory((void*)&Button, sizeof(TBBUTTON));
	if (AlreadyLoggedin()) {
		Button.idCommand = IDM_LOGOUT;
		Button.fsState = TBSTATE_ENABLED;
		Button.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
		Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)_T("ログアウト"));
		Button.iBitmap = MAKELONG(FNC_LOGOUT, 1);
	} else {
		Button.idCommand = IDM_LOGIN;
		Button.fsState = TBSTATE_ENABLED;
		Button.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
		Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)_T("ログイン"));
		Button.iBitmap = MAKELONG(FNC_LOGIN, 1);
	}
	::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
	nBtn++;

	ZeroMemory((void*)&Button, sizeof(TBBUTTON));
	Button.fsStyle = BTNS_SEP;
	::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
	++nBtn;
	nTtPos = nBtn;

	PICON_ITEM pItem = GetIconItem();

	if (AlreadyLoggedin()) {
		nSEQ = 1;
		nFnc = GetNextFunc(nSEQ++);
		while (nFnc) {
			if (nFnc != FNC_TODO || !AdminLogin()) {
				ZeroMemory((void*)&Button, sizeof(TBBUTTON));
				Button.idCommand = FuncToCommand(nFnc);
				Button.fsState = TBSTATE_ENABLED;
				Button.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
				Button.iString = -1;
				Button.iBitmap = MAKELONG(nFnc, 1);
				::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
				++nBtn;
			}
			nFnc = GetNextFunc(nSEQ++);
		}
	} else {
		for (int i = 1; i < ITEMTABLESIZE; ++i) {
			if (i != FNC_WHERE && i != FNC_DUMY && i != FNC_MESSENGER && pItem[i].m_szName[0]) {
				ZeroMemory((void*)&Button, sizeof(TBBUTTON));
				Button.idCommand = FuncToCommand((HOTBIZFUNC)i);
				Button.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
				Button.iString = -1;
				Button.iBitmap = MAKELONG(i, 1);
				::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
				++nBtn;
			}
		}
	}

	BOOL bDispWhere, bDispTimecard, bDispBigicon;
	GetDispIconInfo(bDispWhere, bDispTimecard, bDispBigicon);

	OSVERSIONINFO ver;
	ZeroMemory(&ver, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);
	GetVersionEx(&ver);

	if (ver.dwMajorVersion >= 5 && !AdminLogin() && bDispWhere && pItem[FNC_WHERE].m_bValid) {
		TCHAR szWhere[128];
		if (AlreadyLoggedin()) {
			GetWhereString(szWhere);
			if (!szWhere[0])
				_tcscpy_s(szWhere, sizeof(szWhere), _T("所在"));
		} else {
			_tcscpy_s(szWhere, sizeof(szWhere), _T("所在"));
		}

		ZeroMemory((void*)&Button, sizeof(TBBUTTON));
		Button.fsStyle = BTNS_SEP;
		::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
		++nBtn;

		ZeroMemory((void*)&Button, sizeof(TBBUTTON));
		Button.idCommand = IDM_WHERE;
		if (AlreadyLoggedin()) {
			Button.fsState = TBSTATE_ENABLED;
		}
		Button.fsStyle = BTNS_WHOLEDROPDOWN | BTNS_DROPDOWN | BTNS_BUTTON | BTNS_AUTOSIZE;
		Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)&szWhere);
		Button.iBitmap = MAKELONG(FNC_WHERE, 1);
		::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
		m_nWhereButton = nBtn;
		++nBtn;
	}

	BOOL bGo = FALSE;
	BOOL bLeave = FALSE;
	if (!AdminLogin() && bDispTimecard && pItem[FNC_TIMECARD].m_bValid) {
		LPCTSTR pszTime;
		TCHAR szTime[6];

		ZeroMemory((void*)&Button, sizeof(TBBUTTON));
		Button.fsStyle = BTNS_SEP;
		::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
		nBtn++;

		ZeroMemory((void*)&Button, sizeof(TBBUTTON));
		Button.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
		if (AlreadyLoggedin()) {
			pszTime = GetGoTime();
			if (pszTime[0]) {
				_tcsncpy_s(szTime, sizeof(szTime), pszTime, 2);
				szTime[2] = _T(':');
				_tcscpy_s(szTime+3, sizeof(szTime)-3, pszTime+2);
				szTime[5] = _T('\0');
				Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)&szTime);
				bGo = TRUE;
			} else {
				Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)_T("出社"));
				Button.fsState = TBSTATE_ENABLED;
			}
		} else {
			Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)_T("出社"));
		}
		Button.idCommand = IDM_GOTIME;
		Button.iBitmap = MAKELONG(FNC_GOTIME, 1);
		::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
		nTcPos = nBtn;
		nBtn++;

		ZeroMemory((void*)&Button, sizeof(TBBUTTON));
		Button.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
		if (AlreadyLoggedin()) {
			pszTime = GetLeaveTime();
			if (pszTime[0]) {
				_tcsncpy_s(szTime, sizeof(szTime), pszTime, 2);
				szTime[2] = _T(':');
				_tcscpy_s(szTime+3, sizeof(szTime)+3, pszTime+2);
				szTime[5] = _T('\0');
				Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)&szTime);
				bLeave = TRUE;
			} else {
				Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)_T("退社"));
				if (bGo)
					Button.fsState = TBSTATE_ENABLED;
			}
		} else {
			Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)_T("退社"));
		}
		Button.idCommand = IDM_LEAVETIME;
		Button.iBitmap = MAKELONG(FNC_LEAVETIME, 1);
		::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
		nBtn++;
	}

	ZeroMemory((void*)&Button, sizeof(TBBUTTON));
	Button.fsStyle = BTNS_SEP;
	::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
	++nBtn;

	ZeroMemory((void*)&Button, sizeof(TBBUTTON));
	Button.idCommand = IDM_LOG;
	Button.fsState = TBSTATE_ENABLED;
	Button.fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
	Button.iString = SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)_T("履歴"));
	Button.iBitmap = MAKELONG(FNC_HISTORY, 1);
	::SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&Button);
	nHisPos = nBtn;
	++nBtn;

	ZeroMemory((void*)&BtnInfo, sizeof(BtnInfo));
	BtnInfo.cbSize = sizeof(BtnInfo);
	BtnInfo.dwMask = TBIF_BYINDEX | TBIF_SIZE;
	::SendMessage(m_hWnd, TB_GETBUTTONINFO , 0, (LPARAM)&BtnInfo);
	BtnInfo.cx = nLogoX + 20;
	::SendMessage(m_hWnd, TB_SETBUTTONINFO , 0, (LPARAM)&BtnInfo);

	RECT rc;
	if (bGo) {
		::SendMessage(m_hWnd, TB_GETRECT, IDM_GOTIME, (LPARAM)&rc);
		// associate the tooltip for the toolbar
		m_hStaticGo = ::CreateWindowEx(
			0,					// 拡張ウィンドウスタイル
			_T("STATIC"),		// クラスネーム 
			NULL,				// ウィンドウネーム 
			WS_CHILD |			// ウィンドウスタイル
			WS_VISIBLE |
			SS_OWNERDRAW,
			rc.left,			// Ｘ座標 
			rc.top,				// Ｙ座標 
			rc.right-rc.left,	// 幅 
			rc.bottom-rc.top,	// 高さ 
			m_hWnd,				// 親ウィンドウのハンドル 
			NULL,				// メニューハンドル 
			_Module.GetResourceInstance(),
								// インスタンスハンドル 
			NULL);				// WM_CREATEデータ
	}

	if (bLeave) {
		::SendMessage(m_hWnd, TB_GETRECT, IDM_LEAVETIME, (LPARAM)&rc);
		// associate the tooltip for the toolbar
		m_hStaticLeave = ::CreateWindowEx(
			0,					// 拡張ウィンドウスタイル
			_T("STATIC"),		// クラスネーム 
			NULL,				// ウィンドウネーム 
			WS_CHILD |			// ウィンドウスタイル
			WS_VISIBLE |
			SS_OWNERDRAW,
			rc.left,			// Ｘ座標 
			rc.top,				// Ｙ座標 
			rc.right-rc.left,	// 幅 
			rc.bottom-rc.top,	// 高さ 
			m_hWnd,				// 親ウィンドウのハンドル 
			NULL,				// メニューハンドル 
			_Module.GetResourceInstance(),
								// インスタンスハンドル 
			NULL);				// WM_CREATEデータ
	}

	// associate the tooltip for the toolbar
	m_hToolTip = ::CreateWindowEx(
		0,				//拡張ウィンドウスタイル
		TOOLTIPS_CLASS,	//クラスネーム 
		NULL,			//ウィンドウネーム 
		TTS_ALWAYSTIP,	// ウィンドウスタイル 
		CW_USEDEFAULT,	// Ｘ座標 
		CW_USEDEFAULT,	// Ｙ座標 
		CW_USEDEFAULT,	// 幅 
		CW_USEDEFAULT,	// 高さ 
		m_hWnd,			// 親ウィンドウのハンドル 
		NULL,			// メニューハンドル 
		_Module.GetResourceInstance(), // インスタンスハンドル 
		NULL);			// WM_CREATEデータ
	::SendMessage(m_hWnd, TB_SETTOOLTIPS, (WPARAM)m_hToolTip, 0);

	ti.cbSize = sizeof(TOOLINFO);
	ti.hwnd = m_hWnd;
	ti.hinst = _Module.GetResourceInstance();
	ti.uFlags = TTF_SUBCLASS;
	ti.uId = IDM_HOME;
	ti.lpszText = (LPTSTR)IDM_HOME;
	::SendMessage(m_hWnd, TB_GETITEMRECT, 0, (LPARAM)&ti.rect);
	::SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);

	if (AlreadyLoggedin()) {
		ti.uId = IDM_LOGOUT;
		ti.lpszText = (LPTSTR)IDM_LOGOUT;
	} else {
		ti.uId = IDM_LOGIN;
		ti.lpszText = (LPTSTR)IDM_LOGIN;
	}
	::SendMessage(m_hWnd, TB_GETITEMRECT, nLoginPos, (LPARAM)&ti.rect);
	::SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);

	if (AlreadyLoggedin()) {
		nSEQ = 1;
		nFnc = GetNextFunc(nSEQ++);
		while (nFnc) {
			ti.uId = FuncToCommand(nFnc);
			ti.lpszText = (LPTSTR)pItem[nFnc].m_szName;	// FuncToCommand(nFnc);
			::SendMessage(m_hWnd, TB_GETITEMRECT, nTtPos, (LPARAM)&ti.rect);
			::SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);
			++nTtPos;
			nFnc = GetNextFunc(nSEQ++);
		}
	} else {
		for (int i = 1; i < ITEMTABLESIZE; ++i) {
			if (i != FNC_WHERE && i != FNC_DUMY && i != FNC_MESSENGER && pItem[i].m_szName[0]) {
				ti.uId = FuncToCommand((HOTBIZFUNC)i);
				ti.lpszText = (LPTSTR)pItem[i].m_szName;	// FuncToCommand(nFnc);
				::SendMessage(m_hWnd, TB_GETITEMRECT, nTtPos, (LPARAM)&ti.rect);
				::SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);
				++nTtPos;
			}
		}
	}

	if (bDispWhere) {
		ti.uId = IDM_WHERE;
		ti.lpszText = (LPTSTR)IDM_WHERE;
		::SendMessage(m_hWnd, TB_GETITEMRECT, m_nWhereButton, (LPARAM)&ti.rect);
		::SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);
	}

	if (bDispTimecard) {
		ti.uId = IDM_GOTIME;
		ti.lpszText = (LPTSTR)IDM_GOTIME;
		::SendMessage(m_hWnd, TB_GETITEMRECT, nTcPos, (LPARAM)&ti.rect);
		::SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);
		ti.uId = IDM_LEAVETIME;
		ti.lpszText = (LPTSTR)IDM_LEAVETIME;
		::SendMessage(m_hWnd, TB_GETITEMRECT, nTcPos + 1, (LPARAM)&ti.rect);
		::SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);
	}

	ti.uId = IDM_LOG;
	ti.lpszText = (LPTSTR)IDM_LOG;
	::SendMessage(m_hWnd, TB_GETITEMRECT, nHisPos, (LPARAM)&ti.rect);
	::SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);

	::SendMessage(m_hWnd, TB_GETITEMRECT, nLoginPos, (LPARAM)&ti.rect);
	m_nMinWidth = ti.rect.right;
	m_pHotBizBar->SetMinWidth(m_nMinWidth);

	::SendMessage(m_hWnd, TB_GETITEMRECT, nBtn-1, (LPARAM)&ti.rect);
	m_nActualWidth = ti.rect.right;
	m_pHotBizBar->SetActualWidth(m_nActualWidth);

	if (m_pHotBizBar->GetCmdTarget()) {
		_variant_t vaIn((long)m_pHotBizBar->GetBandID());
		VARIANTARG vaOut;
		m_pHotBizBar->GetCmdTarget()->Exec(&CGID_DeskBand, DBID_BANDINFOCHANGED, OLECMDEXECOPT_DODEFAULT, &vaIn, &vaOut);
	}
}

BOOL CMFToolbar::LoginHotBiz(BOOL bForce)
{
	BOOL bAutoSave;
	TCHAR szURL[256];
	TCHAR szUserName[21];
	TCHAR szPassword[21];
	CLoginDlg dlg;

	if (!bForce && AlreadyLoggedin())
		return TRUE;
	if (dlg.DoModal() != IDOK)
		return FALSE;

	dlg.GetResult(szURL, szUserName, szPassword, bAutoSave);

	CWaitDlg w(_T("HotBizにログインしています..."));
	HWND hDlg = w.Create(m_hWnd);
	if (::IsWindow(hDlg))
		w.ShowWindow(SW_SHOW);

	MSG msg;
	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		DispatchMessage(&msg);

	if (!::LoginHotBiz(bAutoSave, szURL, szUserName, szPassword) || !AlreadyLoggedin()) {
		if (::IsWindow(hDlg))
			w.DestroyWindow();
		MessageBox(_T("ログインに失敗しました。ユーザー名とパスワードを確認してください。"), _T("エラー"), MB_ICONSTOP|MB_OK);
		return FALSE;
	}
	if (::IsWindow(hDlg))
		w.DestroyWindow();

	CleanupResource();
	ClearButton();
	DrawTB();

	vector<HWND> parents;
	EnumWindows(EnumWindowProc, (LPARAM)&parents);
	for (int i = 0; i < (int)parents.size(); ++i) {
		if (::GetWindowLong(parents[i], GWL_USERDATA) == 'HBBH')
			::PostMessage(parents[i], WM_HBBLOGIN, 0, 0);
		else
			EnumLogin(parents[i], WM_HBBLOGIN);
	}

	return TRUE;
}

LRESULT CMFToolbar::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	TCHAR szWindowsDir[MAX_PATH*2];
	GetWindowsDirectory(szWindowsDir, MAX_PATH*2);
	_tcscat_s(szWindowsDir, sizeof(szWindowsDir), _T("\\Winhlp32.exe"));

	HMODULE hModule = LoadLibrary(szWindowsDir);
	if (hModule){
		m_hHyperCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
		FreeLibrary(hModule);
	}
	DrawTB();

	return 0;
}

void CMFToolbar::SetBrowser(IWebBrowser2* pBrowser)
{
	if (m_pBrowser)
		m_pBrowser->Release();
	m_pBrowser = pBrowser;
	if (m_pBrowser)
		m_pBrowser->AddRef();
}

BOOL CMFToolbar::LaunchHotBiz(HOTBIZFUNC nFunc, LPCTSTR pszOrg)
{
	TCHAR szURL[256];
	TCHAR szHeader[1024];
	TCHAR szParam[1024];
	TCHAR szUserName[21];
	TCHAR szPassword[21];
	BOOL bAutoSave;
	LPCTSTR pszProto = GetProtocol();
	LPCTSTR pszHost = GetHost();
	LPCTSTR pszPath = GetServerPath();
	LPCTSTR pszCGI = GetCGI(nFunc);

	if (!m_pBrowser || !pszHost || !pszPath)
		return false;

	GetLoginInfo(bAutoSave, szURL, ARRAYSIZE(szURL), szUserName, ARRAYSIZE(szUserName), szPassword, ARRAYSIZE(szPassword));

	GetHeader(szHeader);
	GetParam(szUserName, szPassword, pszOrg, szParam);
	_tcscpy_s(szURL, sizeof(szURL), pszProto);
	_tcscat_s(szURL, sizeof(szURL), pszHost);
	_tcscat_s(szURL, sizeof(szURL), pszPath);
	_tcscat_s(szURL, sizeof(szURL), pszCGI);

	_variant_t u(szURL);
	_variant_t f(0L);
	_variant_t n(_T(""));
	_variant_t h(szHeader);

	VARIANT p;
	SAFEARRAYBOUND sabound[1];
	SAFEARRAY* psp;
	char* pszElems;
	char* pszTemp;

	pszTemp = (LPSTR)malloc(_tcslen(szParam) + 1);
#ifdef _UNICODE
	ZeroMemory(pszTemp, _tcslen(szParam) + 1);
	WideCharToMultiByte(CP_THREAD_ACP, 0, szParam, _tcslen(szParam), pszTemp, _tcslen(szParam)+1, NULL, NULL);
#else
	strcpy(pszTemp, szParam);
#endif

	sabound[0].cElements = _tcslen(szParam);
	sabound[0].lLbound = 0;
	psp = SafeArrayCreate(VT_UI1, 1, sabound);

	SafeArrayAccessData(psp, (LPVOID*)&pszElems);
	for (UINT i = 0; i < strlen(pszTemp); ++i)
		pszElems[i] = pszTemp[i];
	SafeArrayUnaccessData(psp);
	free(pszTemp);

	VariantInit(&p);
	V_VT(&p) = VT_ARRAY | VT_UI1;
	V_ARRAY(&p) = psp;

	m_pBrowser->Navigate2( &u, &f, &n, &p, &h );
	SafeArrayDestroy(psp);
	return TRUE;
}

BOOL CMFToolbar::DispFuncObj(HOTBIZFUNC nFunc, long nObject)
{
	TCHAR szURL[512];

	_stprintf_s(szURL, sizeof(szURL), _T("mode=HBBGoto&Goto=%%2E%%2F%s%%3Fmode%%3D"), GetCGI(nFunc));
	switch (nFunc) {
	case FNC_SCHEDULE:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("YoteiHenshu%%26SID%%3D%ld"), nObject);
		break;
	case FNC_MESSAGE:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("DengonRireki%%26UID%%3D%ld"), nObject);
		break;
	case FNC_FORUM:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("KeijibanToukou%%26AID%%3D%ld%%23ARTICLE%ld"), nObject, nObject);
		break;
	case FNC_BULLETIN:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("KaigiHatugenIchiran%%26AID%%3D%ld"), nObject);
		break;
	case FNC_TODO:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("TodoSansho%%26TID%%3D%ld"), nObject);
		break;
	case FNC_RESERVE:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("SetubiYoyakuHenshu%%26RID%%3D%ld"), nObject);
		break;
	case FNC_WORKFLOW:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("SinseiNaiyouKakunin%%26WID%%3D%ld"), nObject);
		break;
	case FNC_CIRCULATE:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("KairanbanHyouji%%26CID%%3D%ld"), nObject);
		break;
	case FNC_WHERE:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("DengonIchiran%%26UID%%3D%ld"), nObject);
		break;
	case FNC_REPORT:
		_stprintf_s(szURL+_tcslen(szURL), sizeof(szURL)-_tcslen(szURL), _T("HoukokuNaiyou%%26RID%%3D%ld"), nObject);
		break;
	default:
		_tcscpy_s(szURL, sizeof(szURL), _T(""));
	}
	if (szURL[0]) {
		LaunchHotBiz(FNC_MAIN, szURL);
	}
	return TRUE;
}

BOOL CMFToolbar::PunchTimecard(BOOL bGo)
{
	HCURSOR hOld = SetCursor(LoadCursor(NULL, IDC_WAIT));
	TCHAR szParam[256] = _T("mode=TcPunchTime&");
	TCHAR szURL[256];
	TCHAR szUserName[21];
	TCHAR szPassword[21];
	BOOL bAutoSave;

	GetLoginInfo(bAutoSave, szURL, ARRAYSIZE(szURL), szUserName, ARRAYSIZE(szUserName), szPassword, ARRAYSIZE(szPassword));

	if (bGo)
		_tcscat_s(szParam, sizeof(szParam), _T("ClockIn=SHUSSHA"));
	else
		_tcscat_s(szParam, sizeof(szParam), _T("ClockOut=TAISHA"));
	LPCTSTR p = ConnectToHotBiz(szUserName, szPassword, FNC_TIMECARD, szParam);
	SetCursor(hOld);

	if (!p) {
		MessageBox(_T("タイムカードの打刻に失敗しました。"), _T("エラー"), MB_ICONSTOP|MB_OK);
		return FALSE;
	}

	if (bGo)
		SetGoTime();
	else
		SetLeaveTime();
	HotBizStatus();

	CleanupResource();
	ClearButton();
	DrawTB();

	if (m_pBrowser) {
		_variant_t v = (short)REFRESH_IFEXPIRED;
		m_pBrowser->Refresh2(&v);
	}

	return TRUE;
}

LRESULT CMFToolbar::OnMenuCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MENUITEMINFO mii;
	TCHAR szItem[256];
	TCHAR szURL[256];
	TCHAR szUserName[21];
	TCHAR szPassword[21];
	BOOL bAutoSave;

	GetLoginInfo(bAutoSave, szURL, ARRAYSIZE(szURL), szUserName, ARRAYSIZE(szUserName), szPassword, ARRAYSIZE(szPassword));

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_ID | MIIM_DATA | MIIM_STRING;
	mii.dwTypeData = szItem;
	mii.cch = ARRAYSIZE(szItem);
	GetMenuItemInfo((HMENU)lParam, wParam, TRUE, &mii);
ATLTRACE("OnMenuCommand - %d - %d - %08x - %08lx\r\n", uMsg, mii.wID, wParam, lParam);

	if ((HMENU)lParam == m_hWhereMenu) {
		if (SetWhere(szUserName, szPassword, mii.dwItemData)) {
			SetWhereMem(mii.dwItemData);
			CleanupResource();
			ClearButton();
			DrawTB();
			if (m_pBrowser) {
				_variant_t v = (short)REFRESH_IFEXPIRED;
				m_pBrowser->Refresh2(&v);
			}
		}
	} else {
		switch (mii.wID) {
			case IDM_COMMONLINK:
			case IDM_PRIVATELINK:
			case IDM_HELPERLINK: {
				if (m_pBrowser) {
					_bstr_t str((LPTSTR)mii.dwItemData);
					m_pBrowser->Navigate(str, NULL, NULL, NULL, NULL);
				}
				break;
			}
			case IDM_OPTION: {
				OnOption((WORD)NM_CLICK, mii.wID, m_hWnd, bHandled);
				break;
			}
			case IDM_LOG: {
				OnLog((WORD)NM_CLICK, (WORD)IDM_LOG, m_hWnd, bHandled);
				break;
			}
			case IDM_LOGIN: {
				OnMenuLogin((WORD)NM_CLICK, mii.wID, m_hWnd, bHandled);
				break;
			}
			case IDM_LOGOUT: {
				OnMenuLogout((WORD)NM_CLICK, mii.wID, m_hWnd, bHandled);
				break;
			}
			case IDM_UNINST: {
				OnUninst((WORD)NM_CLICK, mii.wID, m_hWnd, bHandled);
				break;
			}
			case IDM_VERSION: {
				OnVersion((WORD)NM_CLICK, mii.wID, m_hWnd, bHandled);
				break;
			}
			case IDM_HELP: {
				OnHelp((WORD)NM_CLICK, mii.wID, m_hWnd, bHandled);
				break;
			}
			case IDM_SCHEDULE:
				OnSchedule((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_MESSAGE:
				OnMessage((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_MAIL:
				OnMail((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_FORUM:
				OnForum((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_BULLETIN:
				OnBulletin((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_PROJECT:
				OnProject((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_TODO:
				OnTodo((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_RESERVE:
				OnReserve((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_CABINET:
				OnCabinet((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_ADDRESS:
				OnAddress((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_WORKFLOW:
				OnWorkflow((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_TIMECARD:
				OnTimecard((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_CIRCULATE:
				OnCirculate((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
			case IDM_REPORT:
				OnReport((WORD)NM_CLICK, (WORD)mii.wID, m_hWnd, bHandled);
				break;
		}
	}

	return 0;
}

void CMFToolbar::SetMenuStates()
{
	MENUITEMINFO mii;
	PICON_ITEM pItem = GetIconItem();
	OSVERSIONINFO ver;

	ZeroMemory(&ver, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);
	GetVersionEx(&ver);
	if (ver.dwMajorVersion < 5) {
		RemoveMenu(m_hMainMenu, IDM_COMMONLINK, MF_BYCOMMAND);
		RemoveMenu(m_hMainMenu, IDM_PRIVATELINK, MF_BYCOMMAND);
		RemoveMenu(m_hMainMenu, IDM_HELPERLINK, MF_BYCOMMAND);
		RemoveMenu(m_hMainMenu, 16, MF_BYPOSITION);
	}

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	for (int i = 0; i < ITEMTABLESIZE; ++i) {
		if (FuncToCommand((HOTBIZFUNC)i) != IDM_NOP) {
			if (AlreadyLoggedin()) {
				if (pItem[i].m_nSEQ) {
					mii.fMask = MIIM_STATE;
					mii.fState = MFS_ENABLED;
					SetMenuItemInfo(m_hMainMenu, FuncToCommand((HOTBIZFUNC)i), FALSE, &mii);
				} else {
					mii.fMask = MIIM_FTYPE;
					if (GetMenuItemInfo(m_hMainMenu, FuncToCommand((HOTBIZFUNC)i), FALSE, &mii) && mii.fType != MFT_SEPARATOR)
						RemoveMenu(m_hMainMenu, FuncToCommand((HOTBIZFUNC)i), MF_BYCOMMAND);
				}
			} else {
				mii.fMask = MIIM_STATE;
				mii.fState = MFS_DISABLED;
				SetMenuItemInfo(m_hMainMenu, FuncToCommand((HOTBIZFUNC)i), FALSE, &mii);
			}
		}
	}

	mii.fMask = MIIM_STATE;
	if (ver.dwMajorVersion >= 5) {
		if (AlreadyLoggedin()) {
			mii.fState = MFS_ENABLED;
		} else {
			mii.fState = MFS_DISABLED;
		}
		SetMenuItemInfo(m_hMainMenu, IDM_COMMONLINK, FALSE, &mii);
		SetMenuItemInfo(m_hMainMenu, IDM_PRIVATELINK, FALSE, &mii);
		SetMenuItemInfo(m_hMainMenu, IDM_HELPERLINK, FALSE, &mii);
	}

	if (AlreadyLoggedin() && AdminLogin()) {
		mii.fState = MFS_DISABLED;
		SetMenuItemInfo(m_hMainMenu, FuncToCommand(FNC_TODO), FALSE, &mii);
	}
}

LRESULT CMFToolbar::OnSettingChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Reload();
	CleanupResource();
	ClearButton();
	DrawTB();
	return 0;
}

LRESULT CMFToolbar::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
	TEXTMETRIC metrics;
	int nIconX, nIconY;

	GetIconSize(nIconX, nIconY);
	int y = (lpDrawItem->rcItem.bottom - lpDrawItem->rcItem.top - nIconY) / 2;
	int x = y;

	HBRUSH br = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	::FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, br);
	DeleteObject(br);

	UINT nCmd;
	HICON hIcon;
	if (lpDrawItem->hwndItem == m_hStaticGo) {
		hIcon = LoadResourceIcon(MAKEINTRESOURCE(IDI_GOTIME), nIconX, nIconY);
		nCmd = IDM_GOTIME;
	} else {
		hIcon = LoadResourceIcon(MAKEINTRESOURCE(IDI_LEAVETIME), nIconX, nIconY);
		nCmd = IDM_LEAVETIME;
	}
	DrawIconEx(lpDrawItem->hDC, x, y, hIcon, nIconX, nIconY, 0, NULL, DI_NORMAL);
	DestroyIcon(hIcon);

	TCHAR szText[256];
	::SendMessage(m_hWnd, TB_GETBUTTONTEXT, nCmd, (LPARAM)&szText);
	SelectObject(lpDrawItem->hDC, GetFont());
	x *= 2;
	x += (nIconX + 4);
	GetTextMetrics(lpDrawItem->hDC, &metrics);
	y = (lpDrawItem->rcItem.bottom - lpDrawItem->rcItem.top - metrics.tmHeight) / 2;
	TextOut(lpDrawItem->hDC, x, y, szText, _tcslen(szText));

	return TRUE;
}

LRESULT CMFToolbar::OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RECT rc;
	if (m_hStaticGo) {
		::SendMessage(m_hWnd, TB_GETRECT, IDM_GOTIME, (LPARAM)&rc);
		::MoveWindow(m_hStaticGo, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, TRUE);
	}
	if (m_hStaticLeave) {
		::SendMessage(m_hWnd, TB_GETRECT, IDM_LEAVETIME, (LPARAM)&rc);
		::MoveWindow(m_hStaticGo, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, TRUE);
	}
	return 1;
}

LRESULT CMFToolbar::OnLogin(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!AlreadyLoggedin()) {
		Reload();
		CleanupResource();
		ClearButton();
		DrawTB();
	}
	return 0;
}

LRESULT CMFToolbar::OnLogout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (AlreadyLoggedin()) {
		LogoutHotBiz();
		CleanupResource();
		ClearButton();
		DrawTB();
	}
	return 0;
}

LRESULT CMFToolbar::OnUpdate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (AlreadyLoggedin()) {
		ATOM atom = (ATOM)lParam;
		if (atom) {
			TCHAR szBuff[1024];
			char szGo[5];
			char szLv[5];
			long nWhere;

			GlobalGetAtomName(atom, szBuff, ARRAYSIZE(szBuff));

			LPTSTR pszGo = NULL;
			LPTSTR pszLv = NULL;
			LPTSTR pszWh = NULL;
			_tcstok_s(szBuff, _T("\r\n"), &pszGo);
			if (pszGo) {
				_tcstok_s(NULL, _T("\r\n"), &pszLv);
				if (pszLv) {
					_tcstok_s(NULL, _T("\r\n"), &pszWh);
				}
			}
			if (pszGo && pszLv && pszWh) {
#ifdef _UNICODE
				ZeroMemory(szGo, sizeof(szGo));
				ZeroMemory(szLv, sizeof(szLv));
				WideCharToMultiByte(CP_THREAD_ACP, 0, pszGo, _tcslen(pszGo), szGo, ARRAYSIZE(szGo), NULL, NULL);
				WideCharToMultiByte(CP_THREAD_ACP, 0, pszLv, _tcslen(pszLv), szLv, ARRAYSIZE(szLv), NULL, NULL);
#else
				strcpy(szGo, pszGo);
				strcpy(szLv, pszLv);
#endif
				if (strcmp(szGo, "----") == 0)
					szGo[0] = '\0';
				if (strcmp(szLv, "----") == 0)
					szLv[0] = '\0';
				nWhere = _ttol(pszWh);

				SetGoTimeStr(szGo);
				SetLeaveTimeStr(szLv);
				SetWhereMem(nWhere);

				CleanupResource();
				ClearButton();
				DrawTB();
			}
		}
	}
	return 0;
}

LRESULT CMFToolbar::OnLog(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	UINT nRT;
	HOTBIZFUNC nFunc;
	long nObject;
	LogDialog(nRT, nFunc, nObject);
	if (nRT == IDOK)
		DispFuncObj(nFunc, nObject);
	return 0;
}

LRESULT CMFToolbar::OnMenuLogin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	LoginHotBiz(TRUE);
	return 0;
}

LRESULT CMFToolbar::OnMenuLogout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	LogoutHotBiz();
	CleanupResource();
	ClearButton();
	DrawTB();

	vector<HWND> parents;
	EnumWindows(EnumWindowProc, (LPARAM)&parents);
	for (int i = 0; i < (int)parents.size(); ++i) {
		if (::GetWindowLong(parents[i], GWL_USERDATA) == 'HBBH')
			::PostMessage(parents[i], WM_HBBLOGOUT, 0, 0);
		else
			EnumLogin(parents[i], WM_HBBLOGOUT);
	}

	return 0;
}

LRESULT CMFToolbar::OnHome(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (!AlreadyLoggedin()) {
		MessageBox(_T("HotBizにログインされていません。"), _T("エラー"), MB_ICONSTOP|MB_OK);
	} else {
		LaunchHotBiz(FNC_MAIN, _T("mode=main"));
	}
	return 0;
}

LRESULT CMFToolbar::OnFunction(HOTBIZFUNC nFunc)
{
	PICON_ITEM pItem = GetIconItem();
	TCHAR szParam[1024];
	if (AdminLogin()) {
		_stprintf_s(szParam, sizeof(szParam), _T("mode=%s"), pItem[nFunc].m_szAdMode);
	} else {
		_stprintf_s(szParam, sizeof(szParam), _T("mode=%s"), pItem[nFunc].m_szMode);
	}
	LaunchHotBiz(nFunc, szParam);
	return 0;
}

LRESULT CMFToolbar::OnSchedule(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_SCHEDULE);
}

LRESULT CMFToolbar::OnMessage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_MESSAGE);
}

LRESULT CMFToolbar::OnMail(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_MAIL);
}

LRESULT CMFToolbar::OnForum(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_FORUM);
}

LRESULT CMFToolbar::OnBulletin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_BULLETIN);
}

LRESULT CMFToolbar::OnProject(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_PROJECT);
}

LRESULT CMFToolbar::OnTodo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_TODO);
}

LRESULT CMFToolbar::OnReserve(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_RESERVE);
}

LRESULT CMFToolbar::OnCabinet(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_CABINET);
}

LRESULT CMFToolbar::OnAddress(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_ADDRESS);
}

LRESULT CMFToolbar::OnWorkflow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_WORKFLOW);
}

LRESULT CMFToolbar::OnTimecard(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_TIMECARD);
}

LRESULT CMFToolbar::OnCirculate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_CIRCULATE);
}

LRESULT CMFToolbar::OnReport(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return OnFunction(FNC_REPORT);
}

LRESULT CMFToolbar::OnGotime(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (!AdminLogin()) {
		PunchTimecard(TRUE);
	}
	return 0;
}

LRESULT CMFToolbar::OnLeavetime(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (!AdminLogin()) {
		PunchTimecard(FALSE);
	}
	return 0;
}

LRESULT CMFToolbar::OnDropDown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	RECT rc;
	TPMPARAMS tpm;
	LPNMTOOLBAR pnmtb = (LPNMTOOLBAR)pnmh;
#if(WINVER >= 0x0500)
	MENUINFO mn;
	ZeroMemory(&mn, sizeof(mn));
	mn.cbSize = sizeof(mn);
	mn.fMask = MIM_STYLE;
	mn.dwStyle = MNS_NOTIFYBYPOS;
#endif
	if (pnmh->hwndFrom != m_hWnd) {
		bHandled = false;
		return TRUE;
	}

	switch (pnmtb->iItem) {
		case IDM_HOME: {
			HMENU hPopupMenu;
			if (m_hMainMenu)
				DestroyMenu(m_hMainMenu);
			if (m_hCommonMenu)
				DestroyMenu(m_hCommonMenu);
			if (m_hPrivateMenu)
				DestroyMenu(m_hPrivateMenu);
			if (m_hHelperMenu)
				DestroyMenu(m_hHelperMenu);

			SendMessage(pnmtb->hdr.hwndFrom, TB_GETRECT, (WPARAM)pnmtb->iItem, (LPARAM)&rc);
			ClientToScreen(&rc);
			MapWindowPoints(pnmtb->hdr.hwndFrom, (LPPOINT)&rc, 2);

			m_hMainMenu = LoadMenu(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDR_HOTBIZBAR));
			hPopupMenu = GetSubMenu(m_hMainMenu, 0);
#if(WINVER >= 0x0500)
			SetMenuInfo(hPopupMenu, &mn);
#endif
			if (AlreadyLoggedin()) {
				TCHAR szString[] = _T("ログアウト(&N)");
				MENUITEMINFO mi;

				m_hCommonMenu = CreatePopupMenu();
#if(WINVER >= 0x0500)
				SetMenuInfo(m_hCommonMenu, &mn);
#endif
				BuildCommonLink(m_hCommonMenu);
				ZeroMemory(&mi, sizeof(mi));
				mi.cbSize = sizeof(mi);
				mi.fMask = MIIM_SUBMENU;
				mi.hSubMenu = m_hCommonMenu;
				SetMenuItemInfo(hPopupMenu, IDM_COMMONLINK, FALSE, &mi);

				m_hPrivateMenu = CreatePopupMenu();
#if(WINVER >= 0x0500)
				SetMenuInfo(m_hPrivateMenu, &mn);
#endif
				BuildPrivateLink(m_hPrivateMenu);
				ZeroMemory(&mi, sizeof(mi));
				mi.cbSize = sizeof(mi);
				mi.fMask = MIIM_SUBMENU;
				mi.hSubMenu = m_hPrivateMenu;
				SetMenuItemInfo(hPopupMenu, IDM_PRIVATELINK, FALSE, &mi);

				m_hHelperMenu = CreatePopupMenu();
#if(WINVER >= 0x0500)
				SetMenuInfo(m_hHelperMenu, &mn);
#endif
				BuildHelperLink(m_hHelperMenu);
				ZeroMemory(&mi, sizeof(mi));
				mi.cbSize = sizeof(mi);
				mi.fMask = MIIM_SUBMENU;
				mi.hSubMenu = m_hHelperMenu;
				SetMenuItemInfo(hPopupMenu, IDM_HELPERLINK, FALSE, &mi);

				ZeroMemory(&mi, sizeof(mi));
				mi.cbSize = sizeof(mi);
				mi.fMask = MIIM_ID | MIIM_STRING;
				mi.wID = IDM_LOGOUT;
				mi.dwTypeData = szString;
				mi.cch = sizeof(szString);
				SetMenuItemInfo(hPopupMenu, 21, TRUE, &mi);
			}
			SetMenuStates();

			tpm.cbSize = sizeof(TPMPARAMS);
			tpm.rcExclude = rc;
			TrackPopupMenuEx(hPopupMenu,
				TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_TOPALIGN|TPM_VERTICAL,
				rc.left, rc.bottom, m_hWnd, &tpm);
			break;
		}
		case IDM_WHERE: {
			SendMessage(pnmtb->hdr.hwndFrom, TB_GETRECT, (WPARAM)pnmtb->iItem, (LPARAM)&rc);
			ClientToScreen(&rc);
			MapWindowPoints(pnmtb->hdr.hwndFrom, (LPPOINT)&rc, 2);

			if (m_hWhereMenu)
				DestroyMenu(m_hWhereMenu);
			m_hWhereMenu = CreatePopupMenu();
#if(WINVER >= 0x0500)
			SetMenuInfo(m_hWhereMenu, &mn);
#endif
			BuildWhereMenu(m_hWhereMenu);

			tpm.cbSize = sizeof(TPMPARAMS);
			tpm.rcExclude = rc;
			TrackPopupMenuEx(m_hWhereMenu,
				TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_TOPALIGN|TPM_VERTICAL,
				rc.left, rc.bottom, m_hWnd, &tpm);
			break;
		}
	}

	return 0;
}

LRESULT CMFToolbar::OnOption(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	IUnknown* ppUnk[2];
	CLSID pClsID[2];
	pClsID[0] = CLSID_IconPage;
	pClsID[1] = CLSID_HostPage;
	if (SUCCEEDED(CoCreateInstance(pClsID[0], NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&ppUnk[0])) &&
		SUCCEEDED(CoCreateInstance(pClsID[1], NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&ppUnk[1])) &&
		ppUnk[0] && ppUnk[1])
	{
		HRESULT hr = OleCreatePropertyFrame(
			m_hWnd, 0, 0, L"HotBizツールバー",
			2, (IUnknown**)&ppUnk,
			2, (GUID*)&pClsID,
			0, 0, NULL);
		if (SUCCEEDED(hr)) {
			Reload();
			CleanupResource();
			ClearButton();
			DrawTB();
		}
	}
	return 0;
}

LRESULT CMFToolbar::OnUninst(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HKEY hKey;
	TCHAR szMyName[MAX_PATH];
	TCHAR szShortName[MAX_PATH];
	LPTSTR pszStr;
	DWORD type = REG_SZ;
	DWORD size = sizeof(szMyName);
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{CB07F490-0619-4D1D-B44A-8F458E47D0DF}\\InprocServer32"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS) {
		MessageBox(_T("レジストリの読み取りに失敗しました。"), _T("エラー"), MB_OK|MB_ICONSTOP);
		return 0;
	}
	ZeroMemory(szMyName, sizeof(szMyName));
	RegQueryValueEx(hKey, _T(""), NULL, &type, (LPBYTE)&szMyName, &size);
	RegCloseKey(hKey);
	GetShortPathName(szMyName, szShortName, sizeof(szShortName));
	pszStr = _tcsrchr(szShortName, '\\');
	++pszStr;
	*pszStr = _T('\0');
	_tcscat_s(szShortName, sizeof(szShortName), _T("hbbuninst.exe"));

	PROCESS_INFORMATION processInformation;
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	ZeroMemory(&processInformation, sizeof(processInformation));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = SW_SHOW;
	if (!CreateProcess(NULL, szShortName, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation)) {
		MessageBox(_T("アンインストーラの起動に失敗しました。"), _T("エラー"), MB_OK|MB_ICONSTOP);
	}
	return 0;
}

LRESULT CMFToolbar::OnVersion(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CVersionDlg ver;
	ver.DoModal();
	return 0;
}

LRESULT CMFToolbar::OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_pBrowser) {
		_variant_t u(g_szHelpURL);
		m_pBrowser->Navigate2(&u, NULL, NULL, NULL, NULL);
	}
	return 0;
}

HWND CMFToolbar::FindRebar(HWND hwndStart)
{
	HWND hwndFound=NULL;
	HWND hwndEnum=NULL;

	hwndFound = FindWindowEx(hwndStart, NULL, REBARCLASSNAME, NULL);
	if (hwndFound)
		return hwndFound;
	while ((hwndEnum = FindWindowEx(hwndStart, hwndEnum, NULL, NULL)) != NULL) {
		if ((hwndFound = FindRebar(hwndEnum)) != NULL)
			return hwndFound;
	}
	return NULL;
}

BOOL CMFToolbar::SetBandRebar() 
{
	HWND hWnd = NULL;

	if (!m_pBrowser)
		return FALSE;
	m_pBrowser->get_HWND((long*)&hWnd);
	if (hWnd == NULL) 
		return FALSE;
	m_ctlRebar = FindRebar(hWnd);
	if (m_ctlRebar == NULL) 
		return FALSE;
	m_RebarContainer.SubclassWindow(m_ctlRebar);

	return TRUE;
}
