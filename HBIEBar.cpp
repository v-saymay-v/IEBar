// HBIEBar.cpp : DLL �G�N�X�|�[�g�̃C���v�������e�[�V����
//
// ����: Proxy/Stub ���
//  �ʁX�� proxy/stub DLL ���r���h���邽�߂ɂ́A�v���W�F�N�g�̃f�B���N�g���� 
//      nmake -f HBIEBarps.mak �����s���Ă��������B

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "HBIEBar.h"
#include "HBIEBar_i.c"
#include "HotBizBar.h"
#include "IconPage.h"
#include "HostPage.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_HotBizBar, CHotBizBar)
	OBJECT_ENTRY(CLSID_IconPage, CIconPage)
	OBJECT_ENTRY(CLSID_HostPage, CHostPage)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL �G���g�� �|�C���g

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
ATLTRACE("DllMain _Module.Init\r\n");
		_Module.Init(ObjectMap, hInstance, &LIBID_HBIEBARLib);
		DisableThreadLibraryCalls(hInstance);
    } else if (dwReason == DLL_PROCESS_DETACH) {
ATLTRACE("DllMain _Module.Term\r\n");
		_Module.Term();
	}
ATLTRACE("End DllMain\r\n");
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// DLL �� OLE �ɂ���ăA�����[�h�\���ǂ����𒲂ׂ邽�߂Ɏg�p����܂�

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// �v�����ꂽ�^�̃I�u�W�F�N�g���쐬���邽�߂ɃN���X �t�@�N�g����Ԃ��܂�

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
ATLTRACE("DllGetClassObject Start\r\n");
    return _Module.GetClassObject(rclsid, riid, ppv);
}

BOOL WriteVersionString()
{
	HKEY hKey;
	TCHAR szMyName[MAX_PATH];
	TCHAR szShortName[MAX_PATH];
	LPTSTR pszBuff;
	DWORD type = REG_SZ;
	DWORD size = sizeof(szMyName);

	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{CB07F490-0619-4D1D-B44A-8F458E47D0DF}\\InprocServer32"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		ZeroMemory(szMyName, sizeof(szMyName));
		RegQueryValueEx(hKey, _T(""), NULL, &type, (LPBYTE)&szMyName, &size);
		RegCloseKey(hKey);
		GetShortPathName(szMyName, szShortName, sizeof(szShortName));
	} else {
		_tcscpy_s(szShortName, sizeof(szShortName), _T("HBIEBar.dll"));
	}

	size = GetFileVersionInfoSize(szShortName, &type);
	pszBuff = (LPTSTR)malloc(size);
	if (GetFileVersionInfo(szMyName, NULL, size, pszBuff)) {
		UINT uLen;
		VS_FIXEDFILEINFO* pApp;
		if (VerQueryValue(pszBuff, _T("\\"), (LPVOID*)&pApp, &uLen)) {
			TCHAR szVer[128];
			_stprintf_s(szVer, sizeof(szVer), _T("%d.%d.%d.%d"),
						HIWORD(pApp->dwProductVersionMS),
						LOWORD(pApp->dwProductVersionMS),
						HIWORD(pApp->dwProductVersionLS),
						LOWORD(pApp->dwProductVersionLS));
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\ASJ\\HotBizBar"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
			RegSetValueEx(hKey, _T("Version"), 0, REG_SZ, (const BYTE*)szVer, _tcslen(szVer) * sizeof(TCHAR));
			RegCloseKey(hKey);
		}
	}
	free(pszBuff);

	return TRUE;  // �V�X�e���Ƀt�H�[�J�X��ݒ肳���܂�
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - �V�X�e�� ���W�X�g���փG���g����ǉ����܂�

STDAPI DllRegisterServer(void)
{
	HKEY hKeyLocal = NULL;

    // �I�u�W�F�N�g�A�^�C�v���C�u��������у^�C�v���C�u�������̑S�ẴC���^�[�t�F�C�X��o�^���܂�
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Internet Explorer\\Toolbar"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyLocal, NULL);
	RegSetValueEx(hKeyLocal, _T("{CB07F490-0619-4D1D-B44A-8F458E47D0DF}"), 0, REG_BINARY, NULL, 0);
	RegCloseKey(hKeyLocal);

	HRESULT hr = _Module.RegisterServer(TRUE);
	if (SUCCEEDED(hr)) {
		RegDeleteKey(HKEY_CLASSES_ROOT, _T("CLSID\\{CB07F490-0619-4D1D-B44A-8F458E47D0DF}\\Implemented Categories\\{00021492-0000-0000-C000-000000000046}"));
		RegDeleteKey(HKEY_CLASSES_ROOT, _T("CLSID\\{CB07F490-0619-4D1D-B44A-8F458E47D0DF}\\Implemented Categories"));
	}
	WriteVersionString();
ATLTRACE("DllRegisterServer Finisht\r\n");

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - �V�X�e�� ���W�X�g������G���g�����폜���܂�

STDAPI DllUnregisterServer(void)
{
	HKEY hKeyLocal = NULL;

	RegDeleteKey(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"));
	RegDeleteKey(HKEY_LOCAL_MACHINE, _T("Software\\ASJ\\HotBizBar"));
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Internet Explorer\\Toolbar"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyLocal, NULL);
	RegDeleteValue(hKeyLocal, _T("{CB07F490-0619-4D1D-B44A-8F458E47D0DF}"));
	RegCloseKey(hKeyLocal);

ATLTRACE("DllUnregisterServer End\r\n");
    return _Module.UnregisterServer(TRUE);
}
