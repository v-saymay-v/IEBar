// VersionDlg.cpp : CVersionDlg のインプリメンテーション
#include "stdafx.h"
#include "VersionDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CVersionDlg

CVersionDlg::CVersionDlg()
{
}

CVersionDlg::~CVersionDlg()
{
}

LRESULT CVersionDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HKEY hKey;
	TCHAR szMyName[MAX_PATH];
	TCHAR szShortName[MAX_PATH];
	LPTSTR pszBuff;
	DWORD type = REG_SZ;
	DWORD size = sizeof(szMyName);

	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{CB07F490-0619-4D1D-B44A-8F458E47D0DF}\\InprocServer32"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS) {
		return 1;
	}

	ZeroMemory(szMyName, sizeof(szMyName));
	RegQueryValueEx(hKey, _T(""), NULL, &type, (LPBYTE)&szMyName, &size);
	RegCloseKey(hKey);
	GetShortPathName(szMyName, szShortName, sizeof(szShortName));

	size = GetFileVersionInfoSize(szShortName, &type);
	pszBuff = (LPTSTR)malloc(size);
	if (GetFileVersionInfo(szMyName, NULL, size, pszBuff)) {
		UINT uLen;
		VS_FIXEDFILEINFO* pApp;
		LPTSTR pszCopyright;
		if (VerQueryValue(pszBuff, _T("\\"), (LPVOID*)&pApp, &uLen)) {
			TCHAR szVer[128];
			_stprintf_s(szVer, sizeof(szVer), _T("HotBizツールバー Ver.%d.%d.%d (build %d)"),
						HIWORD(pApp->dwProductVersionMS),
						LOWORD(pApp->dwProductVersionMS),
						HIWORD(pApp->dwProductVersionLS),
						LOWORD(pApp->dwProductVersionLS));
			SetDlgItemText(IDC_VER, szVer);
		}
		if (VerQueryValue(pszBuff, _T("\\StringFileInfo\\041104b0\\LegalCopyright"), (LPVOID*)&pszCopyright, &uLen)) {
			SetDlgItemText(IDC_COPYRIGHT, pszCopyright);
		}
	}
	free(pszBuff);

	return 1;  // システムにフォーカスを設定させます
}

LRESULT CVersionDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndDialog(IDOK);
	return 0;
}

LRESULT CVersionDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}
