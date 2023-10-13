//////////////////////////////////////////////////////////////////////////////
//
//  LoginInfo for HotBizBar(日本語)
//
static char rcsid[] = "$Id: logininfo.cpp,v 1.9 2004/06/30 10:49:28 hori Exp $";
// $Log: logininfo.cpp,v $
// Revision 1.9  2004/06/30 10:49:28  hori
// fix 1.0.0.1
//
// Revision 1.8  2004/06/29 16:16:25  hori
// no message
//
// Revision 1.7  2004/06/29 10:35:04  hori
// up
//
// Revision 1.6  2004/06/27 15:34:18  hori
// no message
//
// Revision 1.5  2004/06/24 09:59:14  hori
// up
//
// Revision 1.4  2004/06/17 10:06:34  hori
// Change Many
//
// Revision 1.3  2004/06/08 09:13:36  hori
// NoMess
//
// Revision 1.2  2004/06/02 10:03:02  hori
// NoMess
//
// Revision 1.1  2004/05/21 10:19:51  hori
// Add
//
// Revision 1.20  2004/05/18 13:25:28  hori
// no message
//
// Revision 1.19  2004/05/18 09:56:11  hori
// No Mess
//
// Revision 1.18  2004/05/18 03:48:27  hori
// no message
//
// Revision 1.17  2004/05/13 14:27:25  hori
// no message
//
// Revision 1.16  2004/05/12 09:49:39  hori
// No Mess
//
// Revision 1.15  2004/05/11 09:58:29  hori
// No Message
//
// Revision 1.14  2004/05/10 10:10:41  hori
// No Message
//
// Revision 1.13  2004/05/09 16:01:42  hori
// no message
//
// Revision 1.12  2004/05/07 09:58:07  hori
// No Message
//
// Revision 1.11  2004/05/06 09:48:15  hori
// No Mess
//
// Revision 1.10  2004/04/30 11:20:56  hori
// No message
//
// Revision 1.9  2004/04/28 13:56:37  hori
// no message
//
// Revision 1.8  2004/04/28 12:01:57  hori
// for ASCII
//
// Revision 1.7  2004/04/27 15:00:11  hori
// no message
//
// Revision 1.6  2004/04/27 10:28:41  hori
// no message
//
// Revision 1.5  2004/04/23 10:36:03  hori
// No Message
//
// Revision 1.4  2004/04/22 14:30:11  hori
// no message
//
// Revision 1.3  2004/04/20 10:09:24  hori
// No Message
//
// Revision 1.2  2004/04/15 10:10:55  hori
// add icons
//
// Revision 1.1  2004/04/14 10:31:59  hori
// add new staff.
//
//////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "logininfo.h"
#include "encrypt.h"
#include "hbbexport.h"

CLoginInfo::CLoginInfo()
{
	m_pszLoginInfo = NULL;
//	Reload();
}

CLoginInfo::~CLoginInfo()
{
	if (m_pszLoginInfo)
		free((LPVOID)m_pszLoginInfo);
}

LPCTSTR CLoginInfo::GetURL()
{
	HKEY hKey;
	DWORD type;
	DWORD size;

	GetPrivateProfileString(_T("hotbizbar"), _T("URL"), _T(""), m_szURL, ARRAYSIZE(m_szURL), _T("hotbizbar.ini"));
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_SZ;
		size = sizeof(m_szURL);
		RegQueryValueEx(hKey, _T("URL"), NULL, &type, (LPBYTE)&m_szURL, &size);
		RegCloseKey(hKey);
	}

	return m_szURL;
}

LPCTSTR CLoginInfo::GetUserName()
{
	HKEY hKey;
	DWORD type;
	DWORD size;

	m_szUserName[0] = _T('\0');
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_SZ;
		size = sizeof(m_szUserName);
		RegQueryValueEx(hKey, _T("UserName"), NULL, &type, (LPBYTE)&m_szUserName, &size);
		RegCloseKey(hKey);
	}
	return m_szUserName;
}

LPCTSTR CLoginInfo::GetPassword()
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	DWORD dwTemp;

	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS) {
		m_szPassword[0] = _T('\0');
		return m_szPassword;
	}

	dwTemp = 0;
	type = REG_DWORD;
	size = sizeof(dwTemp);
	if (RegQueryValueEx(hKey, _T("TimeNull"), NULL, &type, (LPBYTE)&dwTemp, &size) == ERROR_SUCCESS) {
		TCHAR szTempPass[1024];
		type = REG_SZ;
		size = sizeof(szTempPass);
		ZeroMemory(szTempPass, sizeof(szTempPass));
		if (RegQueryValueEx(hKey, _T("Password"), NULL, &type, (LPBYTE)&szTempPass, &size) == ERROR_SUCCESS) {
			char szLastChecked[128];
			LPSTR pszDecrypt;
			LPSTR pszTemp = (LPSTR)malloc(_tcslen(szTempPass) + 1);
#ifdef _UNICODE
			ZeroMemory(pszTemp, _tcslen(szTempPass) + 1);
			WideCharToMultiByte(CP_THREAD_ACP, 0, szTempPass, _tcslen(szTempPass), pszTemp, _tcslen(szTempPass) + 1, NULL, NULL);
#else
			strcpy(szTempPass, m_szPassword);
#endif
			sprintf_s(szLastChecked, sizeof(szLastChecked), "%ld", dwTemp);
			decrypt(pszTemp, szLastChecked, &pszDecrypt);
#ifdef _UNICODE
			ZeroMemory(m_szPassword, sizeof(m_szPassword));
			MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, pszDecrypt, strlen(pszDecrypt), m_szPassword, ARRAYSIZE(m_szPassword));
#else
			strcpy(m_szPassword, pszDecrypt);
#endif
			free(pszTemp);
			free(pszDecrypt);
		}
	}

	RegCloseKey(hKey);

	return m_szPassword;
}

BOOL CLoginInfo::GetPlaySound()
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	DWORD dwTemp;

	m_bPlaySound = FALSE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(dwTemp);
		dwTemp = (DWORD)m_bPlaySound;
		if (RegQueryValueEx(hKey, _T("PlaySound"), NULL, &type, (LPBYTE)&dwTemp, &size) == ERROR_SUCCESS)
			m_bPlaySound = (dwTemp != 0);
		RegCloseKey(hKey);
	}

	return m_bPlaySound;
}

LPCTSTR CLoginInfo::GetSoundFile()
{
	HKEY hKey;
	DWORD type;
	DWORD size;

	m_szSoundFile[0] = _T('\0');
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_SZ;
		size = sizeof(m_szSoundFile);
		RegQueryValueEx(hKey, _T("SoundFile"), NULL, &type, (LPBYTE)&m_szSoundFile, &size);
		RegCloseKey(hKey);
	}
	return m_szSoundFile;
}

BOOL CLoginInfo::GetAutoLogin()
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	DWORD dwTemp;

	m_bAutoLogin = FALSE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(dwTemp);
		dwTemp = (DWORD)m_bAutoLogin;
		if (RegQueryValueEx(hKey, _T("AutoLogin"), NULL, &type, (LPBYTE)&dwTemp, &size) == ERROR_SUCCESS)
			m_bAutoLogin = (dwTemp != 0);
		RegCloseKey(hKey);
	}

	return m_bAutoLogin;
}

BOOL CLoginInfo::GetNewsValid()
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	DWORD dwTemp;

	m_bNewsValid = FALSE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(dwTemp);
		dwTemp = (DWORD)m_bNewsValid;
		if (RegQueryValueEx(hKey, _T("NewsValid"), NULL, &type, (LPBYTE)&dwTemp, &size) == ERROR_SUCCESS)
			m_bNewsValid = (dwTemp != 0);
		RegCloseKey(hKey);
	}

	return m_bNewsValid;
}

DWORD CLoginInfo::GetInterval()
{
	HKEY hKey;
	DWORD type;
	DWORD size;

	m_nInterval = 180000;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(m_nInterval);
		RegQueryValueEx(hKey, _T("Interval"), NULL, &type, (LPBYTE)&m_nInterval, &size);
		RegCloseKey(hKey);
	}

	return m_nInterval;
}

DWORD CLoginInfo::GetPopupTime()
{
	HKEY hKey;
	DWORD type;
	DWORD size;

	m_nPopupTime = 10000;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(m_nPopupTime);
		RegQueryValueEx(hKey, _T("PopupTime"), NULL, &type, (LPBYTE)&m_nPopupTime, &size);
			m_nInterval = 180000;
		RegCloseKey(hKey);
	}

	return m_nPopupTime;
}

BOOL CLoginInfo::GetDispWhere()
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	DWORD dwTemp;

	m_bDispWhere = TRUE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(dwTemp);
		dwTemp = (DWORD)m_bDispWhere;
		if (RegQueryValueEx(hKey, _T("DispWhere"), NULL, &type, (LPBYTE)&dwTemp, &size) == ERROR_SUCCESS)
			m_bDispWhere = (dwTemp != 0);
		RegCloseKey(hKey);
	}

	return m_bDispWhere;
}

BOOL CLoginInfo::GetDispTimeCard()
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	DWORD dwTemp;

	m_bDispTimeCard = FALSE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(dwTemp);
		dwTemp = (DWORD)m_bDispTimeCard;
		if (RegQueryValueEx(hKey, _T("DispTimeCard"), NULL, &type, (LPBYTE)&dwTemp, &size) == ERROR_SUCCESS)
			m_bDispTimeCard = (dwTemp != 0);
		RegCloseKey(hKey);
	}

	return m_bDispTimeCard;
}

BOOL CLoginInfo::GetDispBigIcon()
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	DWORD dwTemp;

	m_bDispBigIcon = FALSE;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(dwTemp);
		dwTemp = (DWORD)m_bDispBigIcon;
		if (RegQueryValueEx(hKey, _T("DispBigIcon"), NULL, &type, (LPBYTE)&dwTemp, &size) == ERROR_SUCCESS)
			m_bDispBigIcon = (dwTemp != 0);
		RegCloseKey(hKey);
	}

	return m_bDispBigIcon;
}

void CLoginInfo::DefaultIconItem(PICON_ITEM stIconItem)
{
	for (int i = 0; i < ITEMTABLESIZE; ++i) {
		stIconItem[i].m_szMode[0] = _T('\0');
		stIconItem[i].m_szAdMode[0] = _T('\0');
	}
	stIconItem[FNC_MAIN].m_nSEQ = 0;
	stIconItem[FNC_MAIN].m_bValid = FALSE;
	stIconItem[FNC_MAIN].m_szName[0] = _T('\0');

	stIconItem[FNC_SCHEDULE].m_nSEQ = 1;
	stIconItem[FNC_SCHEDULE].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_SCHEDULE].m_szName, sizeof(stIconItem[FNC_SCHEDULE].m_szName), _T("予定表"));

	stIconItem[FNC_MESSAGE].m_nSEQ = 2;
	stIconItem[FNC_MESSAGE].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_MESSAGE].m_szName, sizeof(stIconItem[FNC_MESSAGE].m_szName), _T("伝言所在"));

	stIconItem[FNC_MAIL].m_nSEQ = 3;
	stIconItem[FNC_MAIL].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_MAIL].m_szName, sizeof(stIconItem[FNC_MAIL].m_szName), _T("メール"));

	stIconItem[FNC_FORUM].m_nSEQ = 4;
	stIconItem[FNC_FORUM].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_FORUM].m_szName, sizeof(stIconItem[FNC_FORUM].m_szName), _T("掲示板"));

	stIconItem[FNC_BULLETIN].m_nSEQ = 5;
	stIconItem[FNC_BULLETIN].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_BULLETIN].m_szName, sizeof(stIconItem[FNC_BULLETIN].m_szName), _T("会議室"));

	stIconItem[FNC_PROJECT].m_nSEQ = 6;
	stIconItem[FNC_PROJECT].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_PROJECT].m_szName, sizeof(stIconItem[FNC_PROJECT].m_szName), _T("プロジェクト"));

	stIconItem[FNC_TODO].m_nSEQ = 7;
	stIconItem[FNC_TODO].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_TODO].m_szName, sizeof(stIconItem[FNC_TODO].m_szName), _T("TODO"));

	stIconItem[FNC_RESERVE].m_nSEQ = 8;
	stIconItem[FNC_RESERVE].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_RESERVE].m_szName, sizeof(stIconItem[FNC_RESERVE].m_szName), _T("設備予約"));

	stIconItem[FNC_CABINET].m_nSEQ = 9;
	stIconItem[FNC_CABINET].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_CABINET].m_szName, sizeof(stIconItem[FNC_CABINET].m_szName), _T("キャビネット"));

	stIconItem[FNC_ADDRESS].m_nSEQ = 10;
	stIconItem[FNC_ADDRESS].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_ADDRESS].m_szName, sizeof(stIconItem[FNC_ADDRESS].m_szName), _T("連絡先"));

	stIconItem[FNC_WORKFLOW].m_nSEQ = 11;
	stIconItem[FNC_WORKFLOW].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_WORKFLOW].m_szName, sizeof(stIconItem[FNC_WORKFLOW].m_szName), _T("ワークフロー"));

	stIconItem[FNC_DUMY].m_nSEQ = 0;
	stIconItem[FNC_DUMY].m_bValid = FALSE;
	stIconItem[FNC_DUMY].m_szName[0] = _T('\0');

	stIconItem[FNC_TIMECARD].m_nSEQ = 12;
	stIconItem[FNC_TIMECARD].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_TIMECARD].m_szName, sizeof(stIconItem[FNC_TIMECARD].m_szName), _T("タイムカード"));

	stIconItem[FNC_CIRCULATE].m_nSEQ = 13;
	stIconItem[FNC_CIRCULATE].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_CIRCULATE].m_szName, sizeof(stIconItem[FNC_CIRCULATE].m_szName), _T("回覧板"));

	stIconItem[FNC_WHERE].m_nSEQ = 0;
	stIconItem[FNC_WHERE].m_bValid = FALSE;
	_tcscpy_s(stIconItem[FNC_WHERE].m_szName, sizeof(stIconItem[FNC_WHERE].m_szName), _T("所在"));

	stIconItem[FNC_REPORT].m_nSEQ = 14;
	stIconItem[FNC_REPORT].m_bValid = TRUE;
	_tcscpy_s(stIconItem[FNC_REPORT].m_szName, sizeof(stIconItem[FNC_REPORT].m_szName), _T("報告書"));

	stIconItem[FNC_MESSENGER].m_nSEQ = 0;
	stIconItem[FNC_MESSENGER].m_bValid = FALSE;
	stIconItem[FNC_MESSENGER].m_szName[0] = _T('\0');
}

PICON_ITEM CLoginInfo::DefaultIconItem()
{
	DefaultIconItem(m_stIconItem);
	return (PICON_ITEM)&m_stIconItem;
}

PICON_ITEM CLoginInfo::GetIconItem()
{
	HKEY hKey;
	DWORD type;
	DWORD size;

	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
		return NULL;
	type = REG_BINARY;
	size = sizeof(m_stIconItem);
	if (RegQueryValueEx(hKey, _T("IconItem"), NULL, &type, (LPBYTE)m_stIconItem, &size) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		return NULL;
	}
	RegCloseKey(hKey);

	return (PICON_ITEM)&m_stIconItem;
}

time_t CLoginInfo::GetLastChecked()
{
	HKEY hKey;
	DWORD type;
	DWORD size;
	DWORD dwTemp;

	m_nLastChecked = time(NULL);
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) == ERROR_SUCCESS) {
		type = REG_DWORD;
		size = sizeof(dwTemp);
		dwTemp = (DWORD)m_nLastChecked;
		if (RegQueryValueEx(hKey, _T("LastChecked"), NULL, &type, (LPBYTE)&dwTemp, &size) == ERROR_SUCCESS)
			m_nLastChecked = (time_t)dwTemp;
		RegCloseKey(hKey);
	}

	return m_nLastChecked;
}

LPCSTR CLoginInfo::GetLoginInfo()
{
	HKEY hKey;
	DWORD type;
	DWORD size;

	if (m_pszLoginInfo)
		free((LPVOID)m_pszLoginInfo);

	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS) {
		return NULL;
	}

	type = REG_BINARY;
	size = 0;
	if (RegQueryValueEx(hKey, _T("LoginInfo"), NULL, &type, NULL, &size) == ERROR_SUCCESS) {
		m_pszLoginInfo = (LPSTR)malloc(size+1);
		if (RegQueryValueEx(hKey, _T("LoginInfo"), NULL, &type, (LPBYTE)m_pszLoginInfo, &size) != ERROR_SUCCESS) {
			free((LPVOID)m_pszLoginInfo);
			m_pszLoginInfo = NULL;
		} else {
			m_pszLoginInfo[size] = '\0';
		}
	}

	RegCloseKey(hKey);

	return m_pszLoginInfo;
}

void CLoginInfo::SetURL(LPCTSTR pszURL)
{
	UINT a = ARRAYSIZE(m_szURL);
	ZeroMemory(m_szURL, sizeof(m_szURL));
	if (_tcslen(pszURL) >= a) {
		_tcsncpy_s(m_szURL, sizeof(m_szURL), pszURL, a-1);
	} else {
		_tcscpy_s(m_szURL, sizeof(m_szURL), pszURL);
	}

	HKEY hKey;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("URL"), NULL, REG_SZ, (const BYTE*)&m_szURL, (_tcslen(m_szURL)+1)*sizeof(TCHAR));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetUserName(LPCTSTR pszUserName)
{
	UINT a = ARRAYSIZE(m_szUserName);
	ZeroMemory(m_szUserName, sizeof(m_szUserName));
	if (_tcslen(pszUserName) >= a) {
		_tcsncpy_s(m_szUserName, sizeof(m_szUserName), pszUserName, a-1);
	} else {
		_tcscpy_s(m_szUserName, sizeof(m_szUserName), pszUserName);
	}
	if (m_szUserName[0]) {
		HKEY hKey;
		if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
			RegSetValueEx(hKey, _T("UserName"), NULL, REG_SZ, (const BYTE*)&m_szUserName, (_tcslen(m_szUserName)+1)*sizeof(TCHAR));
			RegCloseKey(hKey);
		}
	}
}

void CLoginInfo::SetPassword(LPCTSTR pszPass)
{
	UINT a = ARRAYSIZE(m_szPassword);
	ZeroMemory(m_szPassword, sizeof(m_szPassword));
	if (_tcslen(pszPass) >= a) {
		_tcsncpy_s(m_szPassword, sizeof(m_szPassword), pszPass, a-1);
	} else {
		_tcscpy_s(m_szPassword, sizeof(m_szPassword), pszPass);
	}

	DWORD dwTimeNull = (DWORD)time(NULL);
	LPSTR pszPassword;
	LPSTR pszEncrypt;
	char szLastChecked[128];

	if (m_szPassword[0]) {
		pszPassword = (LPSTR)malloc(ARRAYSIZE(m_szPassword));
#ifdef _UNICODE
		ZeroMemory(pszPassword, ARRAYSIZE(m_szPassword));
		WideCharToMultiByte(CP_THREAD_ACP, 0, m_szPassword, _tcslen(m_szPassword), pszPassword, ARRAYSIZE(m_szPassword), NULL, NULL);
#else
		strcpy(pszPassword, m_szPassword);
#endif
		sprintf_s(szLastChecked, sizeof(szLastChecked), "%ld", dwTimeNull);
		encrypt(pszPassword, szLastChecked, &pszEncrypt);
	} else {
		pszPassword = (LPSTR)malloc(sizeof(char));
		pszEncrypt = (LPSTR)malloc(sizeof(char));
		pszEncrypt[0] = '\0';
	}

	if (pszEncrypt[0]) {
		HKEY hKey;
		if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
			TCHAR szTemp[1024];
#ifdef _UNICODE
			ZeroMemory(szTemp, sizeof(szTemp));
			MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, pszEncrypt, strlen(pszEncrypt), szTemp, ARRAYSIZE(szTemp));
#else
			strcpy(szTemp, pszEncrypt);
#endif
			RegSetValueEx(hKey, _T("Password"), NULL, REG_SZ, (const BYTE*)szTemp, (_tcslen(szTemp)+1)*sizeof(TCHAR));
			RegSetValueEx(hKey, _T("TimeNull"), NULL, REG_DWORD, (const BYTE*)&dwTimeNull, sizeof(dwTimeNull));
			RegCloseKey(hKey);
		}
	}
	free(pszPassword);
	free(pszEncrypt);
}

void CLoginInfo::SetSoundFile(LPCTSTR pszFile)
{
	UINT a = ARRAYSIZE(m_szSoundFile);
	ZeroMemory(m_szSoundFile, sizeof(m_szSoundFile));
	if (_tcslen(pszFile) >= a) {
		_tcsncpy_s(m_szSoundFile, sizeof(m_szSoundFile), pszFile, a-1);
	} else {
		_tcscpy_s(m_szSoundFile, sizeof(m_szSoundFile), pszFile);
	}

	HKEY hKey;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		if (m_szSoundFile[0]) {
			RegSetValueEx(hKey, _T("SoundFile"), NULL, REG_SZ, (const BYTE*)&m_szSoundFile, (_tcslen(m_szSoundFile)+1)*sizeof(TCHAR));
		} else {
			RegDeleteValue(hKey, _T("SoundFile"));
		}
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetPlaySound(BOOL bPlaySound)
{
	HKEY hKey;
	m_bPlaySound = bPlaySound;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("PlaySound"), NULL, REG_DWORD, (const BYTE*)&bPlaySound, sizeof(bPlaySound));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetAutoLogin(BOOL bAuto)
{
	HKEY hKey;
	m_bAutoLogin = bAuto;
	DWORD bAutoLogin = (DWORD)m_bAutoLogin;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("AutoLogin"), NULL, REG_DWORD, (const BYTE*)&bAutoLogin, sizeof(bAutoLogin));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetLastChecked(time_t checked)
{
	HKEY hKey;
	m_nLastChecked = checked;
	DWORD dwLastChecked = (DWORD)m_nLastChecked;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("LastChecked"), NULL, REG_DWORD, (const BYTE*)&dwLastChecked, sizeof(dwLastChecked));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetNewsValid(BOOL bValid)
{
	HKEY hKey;
	m_bNewsValid = bValid;
	DWORD bNewsValid = (DWORD)m_bNewsValid;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("NewsValid"), NULL, REG_DWORD, (const BYTE*)&bNewsValid, sizeof(bNewsValid));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetInterval(DWORD nInter)
{
	HKEY hKey;
	m_nInterval = nInter;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("Interval"), NULL, REG_DWORD, (const BYTE*)&m_nInterval, sizeof(m_nInterval));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetPopupTime(DWORD nPopup)
{
	HKEY hKey;
	m_nPopupTime = nPopup;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("PopupTime"), NULL, REG_DWORD, (const BYTE*)&m_nPopupTime, sizeof(m_nPopupTime));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetDispWhere(BOOL bDisp)
{
	HKEY hKey;
	m_bDispWhere = bDisp;
	DWORD dwDispWhere = (DWORD)m_bDispWhere;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("DispWhere"), NULL, REG_DWORD, (const BYTE*)&dwDispWhere, sizeof(dwDispWhere));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetDispTimeCard(BOOL bDisp)
{
	HKEY hKey;
	m_bDispTimeCard = bDisp;
	DWORD dwDispTimeCard = (DWORD)m_bDispTimeCard;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("DispTimeCard"), NULL, REG_DWORD, (const BYTE*)&dwDispTimeCard, sizeof(dwDispTimeCard));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetDispBigIcon(BOOL bBig)
{
	HKEY hKey;
	m_bDispBigIcon = bBig;
	DWORD dwDispBigIcon = (DWORD)m_bDispBigIcon;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, _T("DispBigIcon"), NULL, REG_DWORD, (const BYTE*)&dwDispBigIcon, sizeof(dwDispBigIcon));
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetIconItem(PICON_ITEM pItem)
{
	HKEY hKey;
	CopyMemory(&m_stIconItem, pItem, sizeof(m_stIconItem));
	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
		if (RegSetValueEx(hKey, _T("IconItem"), NULL, REG_BINARY, (const BYTE*)&m_stIconItem, sizeof(m_stIconItem)) != ERROR_SUCCESS) {
		}
		RegCloseKey(hKey);
	}
}

void CLoginInfo::SetLoginInfo(LPCSTR pszHtml, UINT nSize)
{
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
		return;
	}
	RegDeleteValue(hKey, _T("LoginInfo"));
	if (pszHtml) {
		RegSetValueEx(hKey, _T("LoginInfo"), NULL, REG_BINARY, (const BYTE*)pszHtml, nSize);
	}
	RegCloseKey(hKey);

	if (m_pszLoginInfo) {
		free(m_pszLoginInfo);
		m_pszLoginInfo = NULL;
	}
	if (pszHtml) {
		m_pszLoginInfo = (LPSTR)malloc(nSize+1);
		strcpy_s(m_pszLoginInfo, nSize+1, pszHtml);
	}
}

BOOL CLoginInfo::ClearAll()
{
	HKEY hKey;
	TCHAR szPass[1] = {0};

	if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\ASJ\\HotBizBar"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		return FALSE;
	}

	SetUserName((LPCTSTR)_T(""));
	SetPassword((LPCTSTR)_T(""));

	RegSetValueEx(hKey, _T("UserName"), NULL, REG_SZ, (const BYTE*)&m_szUserName, ARRAYSIZE(m_szUserName));
	RegSetValueEx(hKey, _T("Password"), NULL, REG_SZ, (const BYTE*)&m_szPassword, ARRAYSIZE(m_szPassword));

	RegCloseKey(hKey);

	return TRUE;
}
