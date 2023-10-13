// hbbsetup.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

#ifndef CSIDL_PROGRAM_FILES
#define CSIDL_PROGRAM_FILES		0x0026
#endif

static const char* pszHbbFiles[] = {
	"HBIEBar.dll",
	"HBBCommon.dll",
//	"libeay32.dll",
//	"ssleay32.dll",
	"HBBHost.exe",
	"hbbuninst.exe",
};
//static const char* pszVersion = "1.0.0.1";

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	char szTemp[1024];
	char szDest[1024];
	char szFolder[1024];
	char szCurDir[1024];
	char* pstr;

	GetModuleFileName(hInstance, szTemp, sizeof(szTemp));
	GetShortPathName(szTemp, szCurDir, sizeof(szCurDir));
	pstr = strrchr(szCurDir, '\\');
	++pstr;
	*pstr = '\0';

	if (!SUCCEEDED(SHGetSpecialFolderPath(NULL, szTemp, CSIDL_PROGRAM_FILES, FALSE)))
		return 1;

	if (!szTemp[0]) {
		HKEY hKey;
		DWORD type = REG_SZ;
		DWORD size = sizeof(szTemp);
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
			ZeroMemory(szTemp, sizeof(szTemp));
			RegQueryValueEx(hKey, "ProgramFilesDir", NULL, &type, (LPBYTE)&szTemp, &size);
			RegCloseKey(hKey);
		}
	}

	strcat_s(szTemp, sizeof(szTemp), "\\ASJ");
	CreateDirectory(szTemp, NULL);
	strcat_s(szTemp, sizeof(szTemp), "\\HotBizBar");
	CreateDirectory(szTemp, NULL);
	GetShortPathName(szTemp, szFolder, sizeof(szFolder));
	strcat_s(szFolder, sizeof(szFolder), "\\");

	for (int i = 0; i < (int)(sizeof(pszHbbFiles)/sizeof(char*)); ++i) {
		strcpy_s(szTemp, sizeof(szTemp), szCurDir);
		strcat_s(szTemp, sizeof(szTemp), pszHbbFiles[i]);
		strcpy_s(szDest, sizeof(szDest), szFolder);
		strcat_s(szDest, sizeof(szDest), pszHbbFiles[i]);
		MoveFile(szTemp, szDest);
	}

	strcpy_s(szDest, sizeof(szDest), szFolder);
	strcat_s(szDest, sizeof(szDest), pszHbbFiles[0]);
	sprintf_s(szTemp, sizeof(szTemp), "Regsvr32.EXE /s %s", szDest);

	PROCESS_INFORMATION processInformation;
	STARTUPINFO startupInfo;
	memset(&startupInfo, 0, sizeof(startupInfo));
	memset(&processInformation, 0, sizeof(processInformation));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = SW_MINIMIZE;
	if (CreateProcess(NULL, szTemp, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation)) {
		WaitForSingleObject(processInformation.hProcess, INFINITE);
	} else {
		return 1;
	}
/*
	HKEY hkey;
	DWORD dwDisposition;
	strcpy(szDest, "SOFTWARE\\ASJ\\HotBizBar");
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szDest, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &dwDisposition) == ERROR_SUCCESS) {
		RegSetValueEx(hkey, "Version", 0, REG_SZ, (const BYTE*)pszVersion, (DWORD)strlen(pszVersion));
		RegCloseKey(hkey);
	} else {
		MessageBox(NULL, "レジストリ登録に失敗しました。", "ERROR", MB_OK);
		return 1;
	}
*/
	return 0;
}



