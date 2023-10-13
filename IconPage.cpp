// IconPage.cpp : CIconPage のインプリメンテーション
#include "stdafx.h"
#include "HBIEBar.h"
#include "hbbexport.h"
#include "IconPage.h"

/////////////////////////////////////////////////////////////////////////////
// CIconPage

CIconPage::CIconPage()
{
	m_dwTitleID = IDS_TITLEIconPage;
}

LRESULT CIconPage::OnUIChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetDirty(true);
	return 0;
}

LRESULT CIconPage::OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HWND hSelect = GetDlgItem(IDC_SELECT);
	HWND hNotSel = GetDlgItem(IDC_NOTSEL);
	int nSel = ::SendMessage(hNotSel, LB_GETCURSEL, 0, 0);
	if (nSel == LB_ERR)
		return 0;
	int nFnc = ::SendMessage(hNotSel, LB_GETITEMDATA, nSel, 0);
	::SendMessage(hNotSel, LB_DELETESTRING, nSel, 0);

	int nSEQ = 0;
	for (int i = 0; i < ITEMTABLESIZE; ++i) {
		if (m_stIconItem[i].m_nSEQ > nSEQ)
			nSEQ = m_stIconItem[i].m_nSEQ;
	}
	m_stIconItem[nFnc].m_nSEQ = nSEQ+1;
	::SendMessage(hSelect, LB_ADDSTRING, 0, (LPARAM)nFnc);

	SetDirty(true);
	return 0;
}

LRESULT CIconPage::OnDel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HWND hSelect = GetDlgItem(IDC_SELECT);
	HWND hNotSel = GetDlgItem(IDC_NOTSEL);
	int nSel = ::SendMessage(hSelect, LB_GETCURSEL, 0, 0);
	if (nSel == LB_ERR)
		return 0;
	int nFnc = ::SendMessage(hSelect, LB_GETITEMDATA, nSel, 0);
	::SendMessage(hSelect, LB_DELETESTRING, nSel, 0);

	int nSEQ = m_stIconItem[nFnc].m_nSEQ;
	m_stIconItem[nFnc].m_nSEQ = 0;
	for (int i = 0; i < ITEMTABLESIZE; ++i) {
		if (m_stIconItem[i].m_nSEQ > nSEQ)
			--m_stIconItem[i].m_nSEQ;
	}
	::SendMessage(hNotSel, LB_ADDSTRING, 0, (LPARAM)nFnc);

	SetDirty(true);
	return 0;
}

LRESULT CIconPage::OnUp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HWND hSelect = GetDlgItem(IDC_SELECT);
	int nSel = ::SendMessage(hSelect, LB_GETCURSEL, 0, 0);
	if (nSel == LB_ERR)
		return 0;
	int nFnc = ::SendMessage(hSelect, LB_GETITEMDATA, nSel, 0);
	if (m_stIconItem[nFnc].m_nSEQ == 1)
		return 0;

	for (int i = 0; i < ITEMTABLESIZE; ++i) {
		if (m_stIconItem[i].m_nSEQ == m_stIconItem[nFnc].m_nSEQ - 1) {
			RECT rc;
			++m_stIconItem[i].m_nSEQ;
			--m_stIconItem[nFnc].m_nSEQ;
			for (int j = 0; j < ::SendMessage(hSelect, LB_GETCOUNT, 0, 0); ++j) {
				if (::SendMessage(hSelect, LB_GETITEMDATA, j, 0) == i) {
					::SendMessage(hSelect, LB_SETITEMDATA, j, (LPARAM)nFnc);
					::SendMessage(hSelect, LB_GETITEMRECT, j, (LPARAM)&rc);
					::SendMessage(hSelect, LB_SETCURSEL, j, 0);
					::InvalidateRect(hSelect, &rc, TRUE);
					break;
				}
			}
			::SendMessage(hSelect, LB_SETITEMDATA, nSel, (LPARAM)i);
			::SendMessage(hSelect, LB_GETITEMRECT, nSel, (LPARAM)&rc);
			::InvalidateRect(hSelect, &rc, TRUE);
			SetDirty(true);
			break;
		}
	}

	return 0;
}

LRESULT CIconPage::OnDown(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HWND hSelect = GetDlgItem(IDC_SELECT);
	int nSel = ::SendMessage(hSelect, LB_GETCURSEL, 0, 0);
	if (nSel == LB_ERR)
		return 0;
	int nFnc = ::SendMessage(hSelect, LB_GETITEMDATA, nSel, 0);

	int nSEQ = m_stIconItem[nFnc].m_nSEQ;
	for (int i = 0; i < ITEMTABLESIZE; ++i) {
		if (m_stIconItem[i].m_nSEQ == nSEQ + 1) {
			RECT rc;
			--m_stIconItem[i].m_nSEQ;
			++m_stIconItem[nFnc].m_nSEQ;
			for (int j = 0; j < ::SendMessage(hSelect, LB_GETCOUNT, 0, 0); ++j) {
				if (::SendMessage(hSelect, LB_GETITEMDATA, j, 0) == i) {
					::SendMessage(hSelect, LB_SETITEMDATA, j, (LPARAM)nFnc);
					::SendMessage(hSelect, LB_GETITEMRECT, j, (LPARAM)&rc);
					::SendMessage(hSelect, LB_SETCURSEL, j, 0);
					::InvalidateRect(hSelect, &rc, TRUE);
					break;
				}
			}
			::SendMessage(hSelect, LB_SETITEMDATA, nSel, (LPARAM)i);
			::SendMessage(hSelect, LB_GETITEMRECT, nSel, (LPARAM)&rc);
			::InvalidateRect(hSelect, &rc, TRUE);
			SetDirty(true);
			break;
		}
	}

	return 0;
}

LRESULT CIconPage::OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nIconX, nIconY;
	LPMEASUREITEMSTRUCT lpMeasureItem = (LPMEASUREITEMSTRUCT)lParam;
	GetIconSize(nIconX, nIconY);
	lpMeasureItem->itemHeight = nIconY + 4;
	return TRUE;
}

LRESULT CIconPage::OnCompareItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LPCOMPAREITEMSTRUCT lpCompareItem = (LPCOMPAREITEMSTRUCT)lParam;
	if (m_stIconItem[lpCompareItem->itemData1].m_nSEQ > m_stIconItem[lpCompareItem->itemData2].m_nSEQ)
		return 1;
	if (m_stIconItem[lpCompareItem->itemData1].m_nSEQ < m_stIconItem[lpCompareItem->itemData2].m_nSEQ)
		return -1;
	if (lpCompareItem->itemData1 > lpCompareItem->itemData2)
		return 1;
	if (lpCompareItem->itemData1 < lpCompareItem->itemData2)
		return -1;
	return 0;
}

LRESULT CIconPage::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
//	TCHAR szItem[256];
	TEXTMETRIC metrics;
	HICON hIcon;
	HBRUSH hBrush;
	COLORREF clrTextSave;
	COLORREF clrBkSave;
	int nWid = lpDrawItem->rcItem.right - lpDrawItem->rcItem.left;
	int nHgh = lpDrawItem->rcItem.bottom - lpDrawItem->rcItem.top;
	int nFnc = ::SendMessage(lpDrawItem->hwndItem, LB_GETITEMDATA, lpDrawItem->itemID, 0);
	int nCrt = ::SendMessage(lpDrawItem->hwndItem, LB_GETCARETINDEX, 0, 0);
	int nSel = ::SendMessage(lpDrawItem->hwndItem, LB_GETSEL, lpDrawItem->itemID, 0);
	BOOL bReverse = (lpDrawItem->itemAction & ODA_FOCUS) && (lpDrawItem->itemState & ODS_FOCUS);
	int nIconX, nIconY;

	GetIconSize(nIconX, nIconY);

	if (bReverse) {
		hBrush = CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
		::FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, hBrush);
		clrTextSave = ::SetTextColor(lpDrawItem->hDC, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave = ::SetBkColor(lpDrawItem->hDC, ::GetSysColor(COLOR_HIGHLIGHT));
	} else {
		hBrush = CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
		::FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, hBrush);
		clrTextSave = ::SetTextColor(lpDrawItem->hDC, ::GetSysColor(COLOR_WINDOWTEXT));
		clrBkSave = ::SetBkColor(lpDrawItem->hDC, ::GetSysColor(COLOR_WINDOW));
	}

	if (nFnc >= FNC_SCHEDULE && nFnc < ITEMTABLESIZE) {
		hIcon = LoadHotBizIcon(nFnc, nIconX, nIconY);
		::DrawIconEx(lpDrawItem->hDC, 1, lpDrawItem->rcItem.top + (nHgh - nIconY) / 2, hIcon, nIconX, nIconY, 0, NULL, DI_NORMAL);

		::GetTextMetrics(lpDrawItem->hDC, &metrics);
		::TextOut(lpDrawItem->hDC, nIconX + 3, lpDrawItem->rcItem.top + (nHgh - metrics.tmHeight) / 2, m_stIconItem[nFnc].m_szName, _tcslen(m_stIconItem[nFnc].m_szName));

		::DeleteObject(hBrush);
		::SetTextColor(lpDrawItem->hDC, clrTextSave);
		::SetBkColor(lpDrawItem->hDC, clrBkSave);
	}

	if (lpDrawItem->itemState & ODS_SELECTED)
		::DrawFocusRect(lpDrawItem->hDC, &lpDrawItem->rcItem);

	return TRUE;
}

STDMETHODIMP CIconPage::Activate(HWND hWndParent, LPCRECT prc, BOOL bModal)
{
	// Call the base class implementation
	HRESULT hr = IPropertyPageImpl<CIconPage>::Activate(hWndParent, prc, bModal);
	if (FAILED(hr)) {
		return hr;
	}

	::SetWindowText(::GetParent(hWndParent), _T("HotBizツールバー オプション設定"));

	BOOL bDispWhere, bDispTimecard, bDispBigicon;
	GetDispIconInfo(bDispWhere, bDispTimecard, bDispBigicon);

	OSVERSIONINFO ver;
	ZeroMemory(&ver, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);
	GetVersionEx(&ver);
	if (ver.dwMajorVersion < 5) {
		HWND hChk = GetDlgItem(IDC_DISPWHERE);
		::EnableWindow(hChk, FALSE);
		CheckDlgButton(IDC_DISPWHERE, BST_UNCHECKED);
	} else {
		CheckDlgButton(IDC_DISPWHERE, bDispWhere ? BST_CHECKED : BST_UNCHECKED);
	}
	CheckDlgButton(IDC_DISPTC, bDispTimecard ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_BIGICON, bDispBigicon ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_SMALLICON, !bDispBigicon ? BST_CHECKED : BST_UNCHECKED);

	memcpy(m_stIconItem, GetIconItem(), sizeof(m_stIconItem));

	HWND hList = GetDlgItem(IDC_NOTSEL);
	UINT i, cnt = 0;
	for (i = 0; i < ITEMTABLESIZE; ++i) {
		if (i != FNC_WHERE && m_stIconItem[i].m_bValid && !m_stIconItem[i].m_nSEQ && m_stIconItem[i].m_szName[0]) {
			::SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)i);
			++cnt;
		}
	}

	hList = GetDlgItem(IDC_SELECT);
	cnt = 0;
	for (i = 0; i < ITEMTABLESIZE; ++i) {
		if (m_stIconItem[i].m_bValid && m_stIconItem[i].m_nSEQ) {
			::SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)i);
			++cnt;
		}
	}

	SetDirty(false);

	return hr;
}

BOOL CIconPage::ApplyChange()
{
	BOOL bDispWhere = (IsDlgButtonChecked(IDC_DISPWHERE) == BST_CHECKED);
	BOOL bDispTimeCard = (IsDlgButtonChecked(IDC_DISPTC) == BST_CHECKED);
	BOOL bDispBigIcon = (IsDlgButtonChecked(IDC_BIGICON) == BST_CHECKED);
	SetDispIconInfo((PICON_ITEM)&m_stIconItem, bDispWhere, bDispTimeCard, bDispBigIcon);
	SetDirty(false);
	return TRUE;
}

STDMETHODIMP CIconPage::Deactivate()
{
	if (IsPageDirty()) {
		ApplyChange();
	}
	return IPropertyPageImpl<CIconPage>::Deactivate();
}

BOOL CALLBACK CIconPage::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	vector<HWND>* p = (vector<HWND>*)lParam;
	p->push_back(hwnd);
	return TRUE;
}

void CIconPage::UpdateHBBStatus(HWND hwnd)
{
	int j;
	vector<HWND> children;
	EnumChildWindows(hwnd, EnumWindowsProc, (LPARAM)&children);
	for (j = 0; j < (int)children.size(); ++j) {
		TCHAR szClassName[256];
		::GetClassName(children[j], szClassName, ARRAYSIZE(szClassName));
		if (_tcsicmp(szClassName, _T(HOTBIZBARCLASS)) == 0) {
			::SendMessage(children[j], WM_SETTINGCHANGE, 0, 0);
		}
	}
	children.clear();
	for (j = 0; j < (int)children.size(); ++j) {
		UpdateHBBStatus(children[j]);
	}
}

STDMETHODIMP CIconPage::Apply()
{
	if (!ApplyChange())
		return E_INVALIDARG;
	UpdateHBBStatus(GetDesktopWindow());
	return S_OK;
}
