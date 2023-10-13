// PopupDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include <afxdisp.h>
#include <Mmsystem.h>
#include <ExDisp.h>
#include <ExDispID.h>
#include <shlwapi.h>
#import <shdocvw.dll> 
#define __IHTMLControlElement_INTERFACE_DEFINED__
#include <msHtml.h>
#undef __IHTMLControlElement_INTERFACE_DEFINED__
#include "HBBHost.h"
#include "HBBCommon.h"
#include "PopupDlg.h"

#pragma warning(disable: 4100)
#pragma warning(disable: 4511)
#pragma warning(disable: 4512)
#pragma warning(disable: 4530)
#pragma warning(disable: 4663)
#pragma warning(disable: 4786)

#include <map>
using std::map;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg ダイアログ


CPopupDlg::CPopupDlg(int nIndex, UINT nFunc, long nObject, LPCTSTR pszTitle, LPCTSTR pszMess, HWND hLastFocus, CWnd* pParent /*=NULL*/)
	: CDialog(CPopupDlg::IDD, pParent)
{
	m_size = 0;
	m_nFuncID = nFunc;
	m_nObjectID = nObject;
	m_hLastFocus = hLastFocus;
	m_bChildHide = FALSE;
	m_nIndex = nIndex;
	//{{AFX_DATA_INIT(CPopupDlg)
	m_szMess = pszMess;
	m_szTitle = pszTitle;
	//}}AFX_DATA_INIT
}


void CPopupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupDlg)
	DDX_Control(pDX, IDC_TITLE, m_stTitle);
	DDX_Control(pDX, IDC_MESS, m_stMess);
	DDX_Text(pDX, IDC_MESS, m_szMess);
	DDX_Text(pDX, IDC_TITLE, m_szTitle);
	//}}AFX_DATA_MAP
}

/*
BOOL CALLBACK CPopupDlg::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	if (::GetWindowLong(hwnd, GWL_USERDATA) == 'HBBW') {
		RECT rcDsk;
		RECT rcDlg;
		map<UINT, HWND>* p = (map<UINT, HWND>*)lParam;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDsk, 0); 
		::GetWindowRect(hwnd, &rcDlg);
		(*p)[(rcDsk.bottom-rcDlg.bottom)/(rcDlg.bottom-rcDlg.top)] = hwnd;
	}
	return TRUE;
}
*/

BOOL CPopupDlg::LaunchHotBiz(HOTBIZFUNC nFunc, LPCTSTR pszOrg, IWebBrowser2* pBrowser)
{
	BOOL bAutoLogin;
	TCHAR szURL[256];
	TCHAR szHeader[1024];
	TCHAR szParam[1024];
	TCHAR szUserName[21];
	TCHAR szPassword[21];
	LPCTSTR pszProto = GetProtocol();
	LPCTSTR pszHost = GetHost();
	LPCTSTR pszPath = GetServerPath();
	LPCTSTR pszCGI = GetCGI(nFunc);

	if (!pszHost || !pszPath)
		return false;

	GetLoginInfo(bAutoLogin, szURL, ARRAYSIZE(szURL), szUserName, ARRAYSIZE(szUserName), szPassword, ARRAYSIZE(szPassword));

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
	pBrowser->Navigate2( &u, &f, &n, &p, &h );
	SafeArrayDestroy(psp);

	return TRUE;
}

BOOL CPopupDlg::DispFuncObj(HOTBIZFUNC nFunc, long nObject, IWebBrowser2* pBrowser)
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
		LaunchHotBiz(FNC_MAIN, szURL, pBrowser);
	}
	return TRUE;
}

bool CPopupDlg::WildcardCompareNoCase (LPCTSTR strWild, LPCTSTR strText)
{
	int cp = 0, mp = 0;
	int idxWild = 0, idxString = 0;
	int nStrLen = _tcslen (strText);
	int nWildLen = _tcslen (strWild);

	while (idxString < nStrLen) {
		if (idxWild >= nWildLen)
			break;
		if (strWild [idxWild] == _T ('*'))
			break;
		if ((toupper (strWild [idxWild]) != toupper (strText [idxString]) && (strWild [idxWild] != _T ('?'))))
			return false;
		++ idxWild;
		++ idxString;
	}
	
	while (idxString < nStrLen) {
		if (idxWild >= nWildLen)
			break;
		if (strWild [idxWild] == _T ('*')) {
			++ idxWild;
			if (idxWild >= nWildLen)
				return true;
			
			mp = idxWild;
			cp = idxString + 1;
		} else if ((toupper (strWild [idxWild]) == toupper (strText [idxString])) || (strWild [idxWild] == _T ('?'))) {
			++ idxWild;
			++ idxString;
		} else {
			idxWild = mp;
			idxString = cp ++;
		}
	}
	
	while (idxWild < nWildLen) {
		if (strWild [idxWild] != _T ('*'))
			break;
		++ idxWild;
	}
	
	if (idxWild < nWildLen)
		return false;
	else
		return true;
}

IWebBrowser2* CPopupDlg::FindUsingTitle(LPCTSTR pszSearch)
{
	HRESULT hr;
	SHDocVw::IShellWindowsPtr spSHWinds;
	hr = spSHWinds.CreateInstance(__uuidof(SHDocVw::ShellWindows));
	if (FAILED (hr))
		return false;

	ASSERT (spSHWinds != NULL);

	long nCount = spSHWinds->GetCount();

	CString sTitleToSearch = pszSearch;
	IDispatchPtr spDisp;

	for (long i = 0; i < nCount; i++) {
		_variant_t va (i, VT_I4);
		spDisp = spSHWinds->Item (va);

		IWebBrowser2 * pWebBrowser = NULL;
		hr = spDisp.QueryInterface (IID_IWebBrowser2, &pWebBrowser);

		if (pWebBrowser != NULL) {
			HRESULT hr;
			IDispatch* pHtmlDocDispatch = NULL;
			IHTMLDocument2 * pHtmlDoc = NULL;

			// Retrieve the document object.
			hr = pWebBrowser->get_Document(&pHtmlDocDispatch);
			if (SUCCEEDED (hr) && (pHtmlDocDispatch != NULL)) {
				// Query for IPersistStreamInit.
				hr = pHtmlDocDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pHtmlDoc);
				if (SUCCEEDED (hr) && (pHtmlDoc != NULL)) {
					CString sTitle;

					HWND hWnd = NULL;
					pWebBrowser->get_HWND ((long*)(&hWnd));
					if (::IsWindow (hWnd)) {
						int nLen = ::GetWindowTextLength (hWnd);
						::GetWindowText (hWnd, sTitle.GetBufferSetLength(nLen), nLen + 1);
						sTitle.ReleaseBuffer ();
					}

					// If I cannot get the window title
					// (should never happen, though)
					// So, let's just use the title of the document
					if (sTitle.IsEmpty ()) {
						BSTR bstrTitle;
						hr = pHtmlDoc->get_title (&bstrTitle);
						if (!FAILED (hr)) {
							sTitle = bstrTitle;
							SysFreeString (bstrTitle); 
						}
					}

					if (WildcardCompareNoCase(sTitleToSearch, sTitle)) {
						pHtmlDoc->Release ();
						pHtmlDocDispatch->Release ();
						// Exit the method safely!
						return pWebBrowser;
					}
					pHtmlDoc->Release();
				}
				pHtmlDocDispatch->Release ();
			}
			pWebBrowser->Release();
		}
	}
	return false;
}

BOOL CPopupDlg::DispFuncObj(HOTBIZFUNC nFunc, long nObject)
{
	IWebBrowser2* pWeb = FindUsingTitle(_T("HotBiz*"));
	if (!pWeb && FAILED(CoCreateInstance (CLSID_InternetExplorer, NULL, CLSCTX_SERVER, IID_IWebBrowser2, (LPVOID*)&pWeb)))
		return FALSE;
	pWeb->put_Visible (VARIANT_TRUE);
	DispFuncObj(nFunc, nObject, pWeb);
	pWeb->Release();
	return TRUE;
}

BOOL CPopupDlg::NavigateBrowser(LPCTSTR pszURL)
{
	IWebBrowser2* pWeb = FindUsingTitle(_T("*"));
	if (!pWeb && FAILED(CoCreateInstance (CLSID_InternetExplorer, NULL, CLSCTX_SERVER, IID_IWebBrowser2, (LPVOID*)&pWeb)))
		return FALSE;
	pWeb->put_Visible (VARIANT_TRUE);

	COleVariant u(pszURL);
	COleVariant e;
	pWeb->Navigate2(u, e, e, e, e);

	pWeb->Release();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CPopupDlg, CDialog)
	//{{AFX_MSG_MAP(CPopupDlg)
	ON_WM_DRAWITEM()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg メッセージ ハンドラ

void CPopupDlg::OnCancel() 
{
	DestroyWindow();
//	CDialog::OnCancel();
}

BOOL CPopupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	RECT rcDlg;
	RECT rcDsk;
//	map<UINT, HWND> mapMyDlg;
//	std::map<UINT, HWND>::const_iterator it;

	GetWindowRect(&rcDlg);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDsk, 0); 
//	EnumWindows(EnumWindowsProc, (LPARAM)&mapMyDlg);
	::SetWindowLong(m_hWnd, GWL_USERDATA, 'HBBW');

//	int idx = 0;
//	if (mapMyDlg.size()) {
//		while (TRUE) {
//			it = mapMyDlg.upper_bound(idx);
//			if (it == mapMyDlg.end() || it->first > idx+1) {
//				++idx;
//				break;
//			}
//			++idx;
//		}
//	}
	m_nStartX = rcDlg.left + (rcDsk.right - rcDlg.right);
	m_nStartY = rcDsk.bottom - (m_nIndex * (rcDlg.bottom - rcDlg.top));
	::SetWindowPos(m_hWnd, HWND_TOPMOST, m_nStartX, m_nStartY, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER);

	DWORD dwStyle = ::GetWindowLong(m_stTitle.m_hWnd, GWL_STYLE);
	::SetWindowLong(m_stTitle.m_hWnd, GWL_STYLE, dwStyle|SS_OWNERDRAW);
	::SetWindowPos(m_stTitle.m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);

	dwStyle = ::GetWindowLong(m_stMess.m_hWnd, GWL_STYLE);
	::SetWindowLong(m_stMess.m_hWnd, GWL_STYLE, dwStyle|SS_OWNERDRAW);
	::SetWindowPos(m_stMess.m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);

	m_stMess.InitMess();

	SetTimer(1, 10, NULL);
	::SetFocus(m_hLastFocus);

	return FALSE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	               // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CPopupDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl == IDC_TITLE) {
		TEXTMETRIC metrics;
		int y = (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top - HBBICONYS) / 2;
		int x = y;
		HICON hIcon = LoadHotBizIcon(m_nFuncID, HBBICONXS, HBBICONYS);
		DrawIconEx(lpDrawItemStruct->hDC, x, y, hIcon, HBBICONXS, HBBICONYS, 0, NULL, DI_NORMAL);
		DestroyIcon(hIcon);
		x *= 2;
		x += HBBICONXS;
		GetTextMetrics(lpDrawItemStruct->hDC, &metrics);
		y = (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top - metrics.tmHeight) / 2;
		SetBkColor(lpDrawItemStruct->hDC, RGB(0xFF,0xFF,0xFF));
		SetTextColor(lpDrawItemStruct->hDC, RGB(0,0,0));
		TextOut(lpDrawItemStruct->hDC, x, y, m_szTitle, m_szTitle.GetLength());
	} else {
		RECT rc = lpDrawItemStruct->rcItem;
		rc.top += 4;
		rc.left += 4;
		rc.bottom -= 4;
		rc.right -= 4;
		SetBkColor(lpDrawItemStruct->hDC, RGB(0xFF,0xFF,0xFF));
		if (m_stMess.GetMouseOver())
			SetTextColor(lpDrawItemStruct->hDC, RGB(0,0,0xFF));
		DrawText(lpDrawItemStruct->hDC, m_szMess, m_szMess.GetLength(), &rc, DT_END_ELLIPSIS|DT_NOCLIP|DT_NOPREFIX);
	}
//	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

BOOL CPopupDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	UINT nCode = HIWORD(wParam);
	UINT nID = LOWORD(wParam);
//	HWND hCntrl = (HWND)lParam;

	if (nCode == STN_CLICKED && nID == IDC_MESS) {
		DispFuncObj((HOTBIZFUNC)m_nFuncID, m_nObjectID);
		return TRUE;
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CPopupDlg::OnTimer(UINT nIDEvent) 
{
//	CDialog::OnTimer(nIDEvent);

	int x, y;
	RECT rcDsk;
	RECT rcDlg;

	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDsk, 0); 
	GetWindowRect(&rcDlg);

	int nChildWidth = rcDlg.right - rcDlg.left;
	int nChildHeight = rcDlg.bottom - rcDlg.top;
	int nHeight = nChildHeight / 25;

	KillTimer(1);

	if (!m_bChildHide) {
		if (nChildHeight >= m_size * nHeight) {
			x = m_nStartX;
			y = m_nStartY - m_size * nHeight;
			SetWindowPos(&CWnd::wndTopMost, x, y, nChildWidth, nChildHeight, SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER);
 			m_size++;
			SetTimer(1, 10, NULL);
		} else {
			BOOL bNewsValid;
			DWORD nInterval;
			DWORD nPopupTime;
			BOOL bPlaySound;
			TCHAR szSoundFile[MAX_PATH];
			GetNewsInfo(bNewsValid, nInterval, nPopupTime, bPlaySound, szSoundFile);
			x = m_nStartX;
			y = m_nStartY - nChildHeight;
			SetWindowPos(&CWnd::wndTopMost, x, y, nChildWidth, nChildHeight, SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER);
			m_size = 1;
			m_bChildHide = TRUE;
			SetTimer(1, nPopupTime, NULL);
			if (bPlaySound) {
				PlaySound(szSoundFile, AfxGetInstanceHandle(), SND_FILENAME);
			}
		}
	} else {
		x = m_nStartX;
		y = m_nStartY - nChildHeight + m_size * nHeight;
		if (y <= rcDsk.bottom) {
			SetWindowPos(&CWnd::wndTopMost, x, y, nChildWidth, nChildHeight, SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER);
			m_size++;
			SetTimer(1, 10, NULL);
		} else {
			DestroyWindow();
		}
	}
}
