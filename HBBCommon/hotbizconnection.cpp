//////////////////////////////////////////////////////////////////////////////
//
//  LoginInfo for HotBizBar(“ú–{Œê)
//
static char rcsid[] = "$Id: hotbizconnection.cpp,v 1.20 2007/08/14 02:04:34 hori Exp $";
// $Log: hotbizconnection.cpp,v $
// Revision 1.20  2007/08/14 02:04:34  hori
// no message
//
// Revision 1.19  2005/05/25 10:10:49  hori
// key update
//
// Revision 1.18  2004/07/07 10:15:09  hori
// for NT
//
// Revision 1.17  2004/06/30 10:49:28  hori
// fix 1.0.0.1
//
// Revision 1.16  2004/06/29 16:16:25  hori
// no message
//
// Revision 1.15  2004/06/29 10:35:04  hori
// up
//
// Revision 1.14  2004/06/28 10:00:30  hori
// fix it.
//
// Revision 1.13  2004/06/27 15:34:18  hori
// no message
//
// Revision 1.12  2004/06/25 09:07:32  hori
// up
//
// Revision 1.11  2004/06/24 09:59:14  hori
// up
//
// Revision 1.10  2004/06/21 09:21:22  hori
// change
//
// Revision 1.9  2004/06/17 10:06:34  hori
// Change Many
//
// Revision 1.8  2004/06/14 23:59:35  hori
// bug fix
//
// Revision 1.7  2004/06/11 08:57:59  hori
// No mess
//
// Revision 1.6  2004/06/08 09:13:36  hori
// NoMess
//
// Revision 1.5  2004/06/07 10:17:03  hori
// NoMess
//
// Revision 1.4  2004/06/04 10:24:57  hori
// NoMess
//
// Revision 1.3  2004/06/01 09:48:44  hori
// NoMess
//
// Revision 1.2  2004/05/27 13:38:51  hori
// no message
//
// Revision 1.1  2004/05/21 10:19:51  hori
// Add
//
//////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "os.h"
#include "httppost.h"
#include "hotbizconnection.h"

static LPCTSTR g_pszCgiName[] = {
	_T("hotbiz.cgi"),
	_T("schedule.cgi"),
	_T("message.cgi"),
	_T("mail.cgi"),
	_T("forum.cgi"),
	_T("bulletin.cgi"),
	_T("project.cgi"),
	_T("todo.cgi"),
	_T("reserve.cgi"),
	_T("cabinet.cgi"),
	_T("address.cgi"),
	_T("workflow.cgi"),
	_T(""),
	_T("timecard.cgi"),
	_T("circulate.cgi"),
	_T("message.cgi"),
	_T("report.cgi"),
	_T("hotbiz.cgi")
};

static LPCTSTR g_pszMonthName[] = {
	_T("Jan"),_T("Feb"),_T("Mar"),_T("Apr"),_T("May"),_T("Jun"),
	_T("Jul"),_T("Aug"),_T("Sep"),_T("Oct"),_T("Nov"),_T("Dec")
};

CHotBizConnection::CHotBizConnection()
{
	TCHAR szHttp[] = _T("http://");
	TCHAR szHttps[] = _T("https://");
	LPCTSTR pszURL = g_loginInfo.GetURL();

	m_bHttps = false;
	m_nUserID = 0;
	m_nGroupID = 0;
	m_pszHost = NULL;
	m_pszPath = NULL;
	m_pszHtml = NULL;
	m_psztHtml = NULL;
	m_pszCookie = NULL;
	_tcscpy_s(m_szProtocol, sizeof(m_szProtocol), szHttp);

	if (!pszURL || !pszURL[0])
		return;

	if (_tcsnicmp(pszURL, szHttps, _tcslen(szHttps)) == 0) {
		pszURL += _tcslen(szHttps);
		_tcscpy_s(m_szProtocol, sizeof(m_szProtocol), szHttps);
		m_bHttps = true;
	} else if (_tcsnicmp(pszURL, szHttp, _tcslen(szHttp)) == 0) {
		pszURL += _tcslen(szHttp);
	}

	LPCTSTR pstr = _tcschr(pszURL, _T('/'));
	if (pstr) {
		m_pszHost = (LPTSTR)malloc((pstr - pszURL + 1) * sizeof(TCHAR));
		_tcsncpy_s(m_pszHost, pstr - pszURL, pszURL, pstr - pszURL);
		m_pszHost[pstr - pszURL] = 0;
		m_pszPath = (LPTSTR)malloc((_tcslen(pstr) + 2) * sizeof(TCHAR));
		_tcscpy_s(m_pszPath, _tcslen(pstr), pstr);
		if (m_pszPath[_tcslen(m_pszPath)-1] != _T('/'))
			_tcscat_s(m_pszPath, _tcslen(_T("/")), _T("/"));
	} else {
		m_pszHost = (LPTSTR)malloc((_tcslen(pszURL) + 1) * sizeof(TCHAR));
		_tcscpy_s(m_pszHost, _tcslen(pszURL), pszURL);
		m_pszPath = (LPTSTR)malloc(2 * sizeof(TCHAR));
		_tcscpy_s(m_pszPath, _tcslen(_T("/")), _T("/"));
	}

	g_loginInfo.SetLastChecked(GetServerTime());

	LPCSTR pszHtml = g_loginInfo.GetLoginInfo();
	if (pszHtml)
		AnalizeLoginInfo((LPSTR)pszHtml, FALSE);
}

CHotBizConnection::~CHotBizConnection()
{
	ClearData();
	ClearLogin();
	if (m_pszHost) {
		free(m_pszHost);
		m_pszHost = NULL;
	}
	if (m_pszPath) {
		free(m_pszPath);
		m_pszPath = NULL;
	}
}

void CHotBizConnection::ClearData()
{
	std::map<long, TCHAR*>::const_iterator it1;
	std::vector<TITLESQL*>::const_iterator it2;
	for (it1 = m_mapWheres.begin(); it1 != m_mapWheres.end(); ++it1)
		delete it1->second;
	for (it2 = m_vecCommonLink.begin(); it2 != m_vecCommonLink.end(); ++it2)
		delete (*it2);
	for (it2 = m_vecPrivateLink.begin(); it2 != m_vecPrivateLink.end(); ++it2)
		delete (*it2);
	for (it2 = m_vecHelperLink.begin(); it2 != m_vecHelperLink.end(); ++it2)
		delete (*it2);
	m_mapWheres.clear();
	m_mapSEQs.clear();
	m_vecCommonLink.clear();
	m_vecPrivateLink.clear();
	m_vecHelperLink.clear();
	m_nUserID = 0;
	m_nGroupID = 0;
	m_nWhereID = 0;
}

void CHotBizConnection::ClearLogin()
{
	if (m_pszHtml) {
		free(m_pszHtml);
		m_pszHtml = NULL;
	}
	if (m_psztHtml) {
		free(m_psztHtml);
		m_psztHtml = NULL;
	}
	if (m_pszCookie) {
		free(m_pszCookie);
		m_pszCookie = NULL;
	}
}

void CHotBizConnection::Reload()
{
	LPCSTR pszHtml = g_loginInfo.GetLoginInfo();
	if (pszHtml) {
		ClearData();
		AnalizeLoginInfo((LPSTR)pszHtml, FALSE);
	}
}

void CHotBizConnection::Logout()
{
	g_loginInfo.SetLoginInfo(NULL, 0);
	ClearData();
	ClearLogin();
}

bool CHotBizConnection::ReadLine(LPCSTR& pszHtml, vector<string>& szFields, bool& bEOF)
{
	char c,d=0;
	bool bInQuote = false;
	bool bStart = true;
	bool bString = false;
	bool bExit = false;
	bool bRead = false;
	string str;
	bEOF = false;

	while (!bExit) {
		if (bRead) {
			c = d;
			bRead = false;
		} else {
			c = *pszHtml++;
		}
		if (!c) {
			if (!str.empty()) {
				szFields.push_back(str);
			}
			bEOF = true;
			break;
		}
		switch (c) {
		case '"':
			if (bInQuote) {
				d = *pszHtml++;
				if (!d) {
					bEOF = true;
					bExit = true;
				} else {
					if (d == '"') {
						str += c;
					} else {
						szFields.push_back(str);
						str = "";
						bInQuote = false;
						bStart = false;
						bRead = true;
					}
				}
			} else {
				bInQuote = true;
				bString = true;
			}
			break;
		case ',':
			if (bInQuote) {
				str += c;
				bString = true;
			} else if (bStart) {
				szFields.push_back(str);
				str = "";
			} else {
				bStart = true;
			}
			break;
		case EOF:
		case 0xFF:
			bExit = true;
			break;
		case 0x0D:
			if (bInQuote) {
				str += c;
				bString = true;
			}
			break;
		case 0x0A:
			if (bInQuote) {
				str += c;
				bString = true;
			} else {
				if (bStart) {
					szFields.push_back(str);
				}
				bExit = true;
			}
			break;
		case 0x20:
		case 0x9:
			if (bString) {
				str += c;
			}
			break;
		default:
			bString = true;
			if (bStart) {
				str += c;
			}
		}
	}
	return true;
}

LPCSTR CHotBizConnection::SkipHeader(LPSTR pszHtml)
{
	LPSTR pszP = strstr(pszHtml, "\r\n\r\n");
	if (pszP) {
		pszP += strlen("\r\n\r\n");
	} else {
		pszP = strstr(pszHtml, "\n\n");
		if (pszP) {
			pszP += strlen("\n\n");
		} else {
			pszP = pszHtml;
		}
	}
	return pszP;
}

#ifdef _UNICODE
LPCTSTR CHotBizConnection::SkipHeader(LPTSTR psztHtml)
{
	LPTSTR pszP = _tcsstr(psztHtml, _T("\r\n\r\n"));
	if (pszP) {
		pszP += _tcslen(_T("\r\n\r\n"));
	} else {
		pszP = _tcsstr(psztHtml, _T("\n\n"));
		if (pszP) {
			pszP += _tcslen(_T("\n\n"));
		} else {
			pszP = psztHtml;
		}
	}
	return pszP;
}
#endif

void CHotBizConnection::AnalizeLoginInfo(LPSTR pszHtml, BOOL bIcon)
{
	bool bEOF;
	int i, nSEQ = 1;
	vector<string> szFields;
	ICON_ITEM iconItem[ITEMTABLESIZE];
	PICON_ITEM pItem;

	if (bIcon) {
		pItem = g_loginInfo.GetIconItem();
		if (!pItem) {
			g_loginInfo.DefaultIconItem((PICON_ITEM)&iconItem);
		} else {
			memcpy(&iconItem, pItem, sizeof(iconItem));
		}
		for (int i = 0; i < ITEMTABLESIZE; ++i) {
			iconItem[i].m_bValid = FALSE;
		}
	}

	do {
		ReadLine((LPCSTR&)pszHtml, szFields, bEOF);
		if (!szFields.size())
			break;
		switch (atoi(szFields[0].c_str())) {
		case 1:
			if (szFields.size() >= 7) {
				int nCookie = (szFields[1].length() + 1) * sizeof(TCHAR);
				m_pszCookie = (LPTSTR)malloc(nCookie);
#ifdef _UNICODE
				ZeroMemory(m_pszCookie, nCookie);
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[1].c_str(), szFields[1].length(), m_pszCookie, nCookie);
#else
				strcpy(m_pszCookie, szFields[1].c_str());
#endif
				m_nUserID = atol(szFields[2].c_str());
				m_nGroupID = atol(szFields[3].c_str());
				m_nWhereID = atol(szFields[4].c_str());
#ifdef _UNICODE
				ZeroMemory(m_szGoTime, sizeof(m_szGoTime));
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[5].c_str(), szFields[5].length(), m_szGoTime, ARRAYSIZE(m_szGoTime));
#else
				strcpy(m_szGoTime, szFields[5].c_str());
#endif
#ifdef _UNICODE
				ZeroMemory(m_szLeaveTime, sizeof(m_szLeaveTime));
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[6].c_str(), szFields[6].length(), m_szLeaveTime, ARRAYSIZE(m_szLeaveTime));
#else
				strcpy(m_szLeaveTime, szFields[6].c_str());
#endif
			}
			break;
		case 2:
			if (szFields.size() >= 4) {
				long nWhere = atol(szFields[1].c_str());
				LPTSTR pNm = new TCHAR[HBBNAMELEN];
				long nSEQ = atol(szFields[3].c_str());
#ifdef _UNICODE
				ZeroMemory(pNm, sizeof(HBBNAME));
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[2].c_str(), szFields[2].length(), pNm, HBBNAMELEN);
#else
				strcpy(pNm, szFields[2].c_str());
#endif
				m_mapSEQs[nSEQ] = nWhere;
				m_mapWheres[nWhere] = pNm;
			}
			break;
		case 3:
			if (szFields.size() >= 3) {
				PTITLESQL pItm = new TITLESQL;
#ifdef _UNICODE
				ZeroMemory(pItm, sizeof(TITLESQL));
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[1].c_str(), szFields[1].length(), pItm->szTitle, HBBNAMELEN);
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[2].c_str(), szFields[2].length(), pItm->szSQL, HBBNAMELEN);
#else
				strcpy(pItm->szTitle, szFields[1].c_str());
				strcpy(pItm->szSQL, szFields[2].c_str());
#endif
				m_vecCommonLink.push_back(pItm);
			}
			break;
		case 4:
			if (szFields.size() >= 3) {
				PTITLESQL pItm = new TITLESQL;
#ifdef _UNICODE
				ZeroMemory(pItm, sizeof(TITLESQL));
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[1].c_str(), szFields[1].length(), pItm->szTitle, HBBNAMELEN);
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[2].c_str(), szFields[2].length(), pItm->szSQL, HBBNAMELEN);
#else
				strcpy(pItm->szTitle, szFields[1].c_str());
				strcpy(pItm->szSQL, szFields[2].c_str());
#endif
				m_vecPrivateLink.push_back(pItm);
			}
			break;
		case 5:
			if (szFields.size() >= 3) {
				PTITLESQL pItm = new TITLESQL;
#ifdef _UNICODE
				ZeroMemory(pItm, sizeof(TITLESQL));
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[1].c_str(), szFields[1].length(), pItm->szTitle, HBBNAMELEN);
				MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[2].c_str(), szFields[2].length(), pItm->szSQL, HBBNAMELEN);
#else
				strcpy(pItm->szTitle, szFields[1].c_str());
				strcpy(pItm->szSQL, szFields[2].c_str());
#endif
				m_vecHelperLink.push_back(pItm);
			}
			break;
		case 6:
			if (bIcon && szFields.size() >= 5) {
				int nFnc = atoi(szFields[1].c_str());
				if (nFnc < ITEMTABLESIZE) {
					iconItem[nFnc].m_bValid = TRUE;
#ifdef _UNICODE
					ZeroMemory(iconItem[nFnc].m_szName, sizeof(iconItem[nFnc].m_szName));
					ZeroMemory(iconItem[nFnc].m_szMode, sizeof(iconItem[nFnc].m_szMode));
					ZeroMemory(iconItem[nFnc].m_szAdMode, sizeof(iconItem[nFnc].m_szAdMode));
					MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[2].c_str(), szFields[2].length(), iconItem[nFnc].m_szName, ARRAYSIZE(iconItem[nFnc].m_szName));
					MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[3].c_str(), szFields[3].length(), iconItem[nFnc].m_szMode, ARRAYSIZE(iconItem[nFnc].m_szMode));
					MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[4].c_str(), szFields[4].length(), iconItem[nFnc].m_szAdMode, ARRAYSIZE(iconItem[nFnc].m_szAdMode));
#else
					strcpy(iconItem[nFnc].m_szName, szFields[2].c_str());
					strcpy(iconItem[nFnc].m_szMode, szFields[3].c_str());
					strcpy(iconItem[nFnc].m_szAdMode, szFields[4].c_str());
#endif
				}
			}
			break;
		}
		szFields.clear();
	} while (!bEOF);

	if (bIcon) {
		for (i = 1; i < ITEMTABLESIZE; ++i) {
			if (!iconItem[i].m_bValid) {
				if (iconItem[i].m_nSEQ) {
					for (int j = 0; j < ITEMTABLESIZE; ++j) {
						if (iconItem[j].m_nSEQ > iconItem[i].m_nSEQ)
							--iconItem[j].m_nSEQ;
					}
				}
				iconItem[i].m_nSEQ = 0;
			}
		}
		g_loginInfo.SetIconItem((PICON_ITEM)&iconItem);
	}
}

BOOL CHotBizConnection::Login(LPCTSTR pszUserName, LPCTSTR pszPassword)
{
	int err;
	LPSTR pszSave;
	LPSTR pszHtml;
	LPTSTR pszPath;
	LPTSTR pszParam;
	HCURSOR hOldCursor;

	if (m_pszCookie) {
		free(m_pszCookie);
		m_pszCookie = NULL;
	}

	ClearData();

	asprintf(&pszPath, _T("%s%s"), m_pszPath, g_pszCgiName[FNC_MAIN]);
	asprintf(&pszParam, _T("USERID=%s&PASSWORD=%s&mode=HBBQuery"), pszUserName, pszPassword);
	hOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (_tcscmp(m_szProtocol, _T("https://")) == 0) {
		err = Https_Post_Get_Result(m_pszHost, pszPath, pszParam, _T(""), &pszSave);
	} else{
		err = Http_Post_Get_Result(m_pszHost, pszPath, pszParam, _T(""), &pszSave);
	}

	SetCursor(hOldCursor);
	if (err) {
		free(pszPath);
		free(pszParam);
		return FALSE;
	}
	free(pszPath);
	free(pszParam);

	pszHtml = pszSave;
	pszHtml = (LPSTR)SkipHeader(pszHtml);
	g_loginInfo.SetLoginInfo(pszHtml, strlen(pszHtml));
	AnalizeLoginInfo(pszHtml);
	free(pszSave);

	if (!m_nUserID) {
		g_loginInfo.DefaultIconItem();
		return FALSE;
	}

	return TRUE;
}

BOOL CHotBizConnection::Status()
{
	int err;
	bool bEOF;
	LPSTR pszSave;
	LPSTR pszHtml;
	LPTSTR pszPath;
	LPTSTR pszParam;
	HCURSOR hOldCursor;
	vector<string> szFields;

	asprintf(&pszPath, _T("%s%s"), m_pszPath, g_pszCgiName[FNC_MAIN]);
	asprintf(&pszParam, _T("USERID=%s&PASSWORD=%s&mode=HBBStatus"), g_loginInfo.GetUserName(), g_loginInfo.GetPassword());
	hOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (_tcscmp(m_szProtocol, _T("https://")) == 0) {
		err = Https_Post_Get_Result(m_pszHost, pszPath, pszParam, _T(""), &pszSave);
	} else{
		err = Http_Post_Get_Result(m_pszHost, pszPath, pszParam, _T(""), &pszSave);
	}

	SetCursor(hOldCursor);
	if (err) {
		free(pszPath);
		free(pszParam);
		return FALSE;
	}
	free(pszPath);
	free(pszParam);
	pszHtml = pszSave;
	pszHtml = (LPSTR)SkipHeader(pszHtml);

	ReadLine((LPCSTR&)pszHtml, szFields, bEOF);
	if (szFields.size() >= 7) {
		int nCookie = (szFields[1].length() + 1) * sizeof(TCHAR);
		if (m_pszCookie)
			free(m_pszCookie);
		m_pszCookie = (LPTSTR)malloc(nCookie);
#ifdef _UNICODE
		ZeroMemory(m_pszCookie, nCookie);
		MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[1].c_str(), szFields[1].length(), m_pszCookie, nCookie);
#else
		strcpy(m_pszCookie, szFields[1].c_str());
#endif
		m_nUserID = atol(szFields[2].c_str());
		m_nGroupID = atol(szFields[3].c_str());
		m_nWhereID = atol(szFields[4].c_str());
#ifdef _UNICODE
		ZeroMemory(m_szGoTime, sizeof(m_szGoTime));
		MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[5].c_str(), szFields[5].length(), m_szGoTime, ARRAYSIZE(m_szGoTime));
#else
		strcpy(m_szGoTime, szFields[5].c_str());
#endif
#ifdef _UNICODE
		ZeroMemory(m_szLeaveTime, sizeof(m_szLeaveTime));
		MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, szFields[6].c_str(), szFields[6].length(), m_szLeaveTime, ARRAYSIZE(m_szLeaveTime));
#else
		strcpy(m_szLeaveTime, szFields[6].c_str());
#endif
	}
	free(pszSave);

	return true;
}

LPCTSTR CHotBizConnection::Connect(LPCTSTR pszUserName, LPCTSTR pszPassword, HOTBIZFUNC nFunc, LPCTSTR pszParam)
{
	int err;
	LPTSTR pszPath;
//	LPTSTR pszCookie;
	LPTSTR pszRealParam;
	vector<string> szFields;

	if (m_pszHtml) {
		free(m_pszHtml);
		m_pszHtml = NULL;
	}
	if (m_psztHtml) {
		free(m_psztHtml);
		m_psztHtml = NULL;
	}
	if (!m_pszCookie)
		return NULL;

//	asprintf(&pszCookie, _T("Cookie: HotBiz=%s;\r\n"), m_pszCookie);
	asprintf(&pszPath, _T("%s%s"), m_pszPath, g_pszCgiName[nFunc]);
	asprintf(&pszRealParam, _T("USERID=%s&PASSWORD=%s&Login=1&%s"), g_loginInfo.GetUserName(), g_loginInfo.GetPassword(), pszParam);
	HCURSOR hOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
	if (_tcscmp(m_szProtocol, _T("https://")) == 0) {
		err = Https_Post_Get_Result(m_pszHost, pszPath, pszRealParam, NULL/*pszCookie*/, &m_pszHtml);
	} else {
		err = Http_Post_Get_Result(m_pszHost, pszPath, pszRealParam, NULL/*pszCookie*/, &m_pszHtml);
	}
	SetCursor(hOldCursor);
	free(pszPath);
//	free(pszCookie);
	free(pszRealParam);
	if (err)
		return NULL;
	if (!m_pszHtml)
		return NULL;

	m_psztHtml = (LPTSTR)malloc((strlen(m_pszHtml) + 1)*sizeof(TCHAR));
#ifdef _UNICODE
	ZeroMemory(m_psztHtml, (strlen(m_pszHtml) + 1)*sizeof(TCHAR));
	MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, m_pszHtml, strlen(m_pszHtml), m_psztHtml, strlen(m_pszHtml) + 1);
#else
	strcpy(m_psztHtml, m_pszHtml);
#endif

	return SkipHeader(m_psztHtml);
}

bool CHotBizConnection::SetWhere(LPCTSTR pszUserName, LPCTSTR pszPassword, long nWhereID)
{
	TCHAR szSQL[256];
	if (!m_pszCookie)
		return false;
	_stprintf_s(szSQL, sizeof(szSQL), _T("mode=DengonTuika&UID=%ld&GID=%ld&Place=%ld"), m_nUserID, m_nGroupID, nWhereID);
	if (!Connect(pszUserName, pszPassword, FNC_MESSAGE, szSQL))
		return false;
	return true;
}

void CHotBizConnection::SetWhereID(long nWhereID)
{
	m_nWhereID = nWhereID;
}

LPCTSTR CHotBizConnection::GetCGI(HOTBIZFUNC nFunc)
{
	return g_pszCgiName[nFunc];
}

void CHotBizConnection::GetHeader(LPTSTR pszHeader)
{
	_tcscpy_s(pszHeader, _tcslen(_T("Content-Type: application/x-www-form-urlencoded\r\n")), _T("Content-Type: application/x-www-form-urlencoded\r\n"));
//	if (m_pszCookie)
//		_stprintf(pszHeader+_tcslen(pszHeader), _T("Cookie: HotBiz=%s\r\n"), m_pszCookie);
}

void CHotBizConnection::GetParam(LPCTSTR pszUserName, LPCTSTR pszPassword, LPCTSTR pszOrg, LPTSTR pszParam)
{
	_tcscpy_s(pszParam, _tcslen(pszOrg), pszOrg);
//	if (!m_pszCookie)
		_stprintf_s(pszParam+_tcslen(pszParam), 1024, _T("&USERID=%s&PASSWORD=%s&Login=1"), pszUserName, pszPassword);
}

void CHotBizConnection::SetGoTime()
{
	struct tm p;
	time_t t = GetServerTime();
	localtime_s(&p, &t);
	_stprintf_s(m_szGoTime, sizeof(m_szGoTime), _T("%02d%02d"), p.tm_hour, p.tm_min);
}

void CHotBizConnection::SetGoTime(LPCSTR pszTime)
{
#ifdef _UNICODE
	ZeroMemory(m_szGoTime, sizeof(m_szGoTime));
	MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, pszTime, strlen(pszTime), m_szGoTime, ARRAYSIZE(m_szGoTime));
#else
	strcpy(m_szGoTime, pszTime);
#endif
}

void CHotBizConnection::SetLeaveTime()
{
	struct tm p;
	time_t t = GetServerTime();
	localtime_s(&p, &t);
	_stprintf_s(m_szLeaveTime, sizeof(m_szLeaveTime), _T("%02d%02d"), p.tm_hour, p.tm_min);
}

void CHotBizConnection::SetLeaveTime(LPCSTR pszTime)
{
#ifdef _UNICODE
	ZeroMemory(m_szLeaveTime, sizeof(m_szLeaveTime));
	MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, pszTime, strlen(pszTime), m_szLeaveTime, ARRAYSIZE(m_szLeaveTime));
#else
	strcpy(m_szLeaveTime, pszTime);
#endif
}

time_t CHotBizConnection::GetServerTime()
{
	int err;
	TCHAR szDate[] = _T("Date: ");
	LPTSTR pszReturn;
	LPTSTR pszStr;
	time_t cur = time(NULL);

	if (!m_pszHost)
		return cur;
	err = Http_Head_Get_Result(m_pszHost, &pszReturn);
	if (err)
		return cur;

	_tcstok_s(pszReturn, _T("\r\n"), &pszStr);
	while (pszStr) {
		if (_tcsncmp(pszStr, szDate, _tcslen(szDate)) == 0) {
			TCHAR szWeek[256];
			TCHAR szMonth[256];
			TCHAR szTimezone[256];
			int nDay;
			int nMonth;
			int nYear;
			int nHour;
			int nMinute;
			int nSecond;
			struct tm mt;

			_stscanf_s(pszStr, _T("Date: %255s %d %255s %d %d:%d:%d %255s"), szWeek, &nDay, szMonth, &nYear, &nHour, &nMinute, &nSecond, szTimezone);
			for (nMonth = 0; nMonth < (int)(sizeof(g_pszMonthName)/sizeof(LPCTSTR)); ++nMonth) {
				if (_tcsicmp(szMonth, g_pszMonthName[nMonth]) == 0)
					break;
			}

			localtime_s(&mt, &cur);
			mt.tm_year = nYear - 1900;
			mt.tm_mon = nMonth;
			mt.tm_mday = nDay;
			mt.tm_hour = nHour;
			mt.tm_min = nMinute;
			mt.tm_sec = nSecond;
			cur = mktime(&mt);
			if (_tcsicmp(szTimezone, _T("GMT")) == 0) {
				cur += (9 * 60 * 60);
			}
			break;
		}
		_tcstok_s(NULL, _T("\r\n"), &pszStr);
	}
	free(pszReturn);

	return cur;
}
