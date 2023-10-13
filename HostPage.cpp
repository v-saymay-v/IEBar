// HostPage.cpp : CHostPage �̃C���v�������e�[�V����
#include "stdafx.h"
#include "HBIEBar.h"
#include "HostPage.h"

/////////////////////////////////////////////////////////////////////////////
// CHostPage

CHostPage::CHostPage() 
{
	m_dwTitleID = IDS_TITLEHostPage;
}

BOOL CALLBACK CHostPage::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	if (::GetWindowLong(hwnd, GWL_USERDATA) == 'HBBH') {
		HWND* pWnd = (HWND*)lParam;
		*pWnd = hwnd;
		return FALSE;
	}
	return TRUE;
}

BOOL CHostPage::UpdateButton()
{
	HWND hwnd = NULL;
	EnumWindows(EnumWindowsProc, (LPARAM)&hwnd);
	if (hwnd) {
		hwnd = GetDlgItem(IDC_STARTHOST);
		::SetWindowText(hwnd, _T("���łɋN�����Ă��܂�"));
		::EnableWindow(hwnd, FALSE);
		return TRUE;
	}
	return FALSE;
}

LRESULT CHostPage::OnStartHost(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HKEY hKey;
	TCHAR szMyName[MAX_PATH];
	TCHAR szShortName[MAX_PATH];
	LPTSTR pszStr;
	DWORD type = REG_SZ;
	DWORD size = sizeof(szMyName);

	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{CB07F490-0619-4D1D-B44A-8F458E47D0DF}\\InprocServer32"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS) {
		MessageBox(_T("���W�X�g���̓ǂݎ��Ɏ��s���܂����B"), _T("�G���["), MB_OK|MB_ICONSTOP);
		return 0;
	}
	ZeroMemory(szMyName, sizeof(szMyName));
	RegQueryValueEx(hKey, _T(""), NULL, &type, (LPBYTE)&szMyName, &size);
	RegCloseKey(hKey);
	GetShortPathName(szMyName, szShortName, sizeof(szShortName));
	pszStr = _tcsrchr(szShortName, '\\');
	++pszStr;
	*pszStr = _T('\0');
	_tcscat_s(szShortName, sizeof(szShortName), _T("HBBHost.exe"));

	PROCESS_INFORMATION processInformation;
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	ZeroMemory(&processInformation, sizeof(processInformation));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = SW_SHOW;
	if (!CreateProcess(NULL, szShortName, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation)) {
		MessageBox(_T("�V�����̋N���Ɏ��s���܂����B"), _T("�G���["), MB_OK|MB_ICONSTOP);
	}

	int cnt = 0;
	HWND hwnd = GetDlgItem(IDC_STARTHOST);
	while (cnt < 3 && !UpdateButton()) {
		++cnt;
		Sleep(500);
	}

	return 0;
}

STDMETHODIMP CHostPage::Activate(HWND hWndParent, LPCRECT prc, BOOL bModal)
{
	// Call the base class implementation
	HRESULT hr = IPropertyPageImpl<CHostPage>::Activate(hWndParent, prc, bModal);
	if (FAILED(hr)) {
		return hr;
	}
	UpdateButton();
	return S_OK;
}

STDMETHODIMP CHostPage::Apply()
{
	m_bDirty = FALSE;
	return S_OK;
}
