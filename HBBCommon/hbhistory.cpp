//////////////////////////////////////////////////////////////////////////////
//
//  History for HotBizBar(“ú–{Œê)
//
static char rcsid[] = "$Id: hbhistory.cpp,v 1.6 2004/06/25 09:07:32 hori Exp $";
// $Log: hbhistory.cpp,v $
// Revision 1.6  2004/06/25 09:07:32  hori
// up
//
// Revision 1.5  2004/06/24 09:59:13  hori
// up
//
// Revision 1.4  2004/06/09 09:45:29  hori
// NoMess
//
// Revision 1.3  2004/06/03 09:53:27  hori
// NoMess
//
// Revision 1.2  2004/05/25 07:48:07  hori
// Add
//
// Revision 1.1  2004/05/24 10:53:12  hori
// NoMess
//
// Revision 1.5  2004/05/19 09:47:16  hori
// NoMess
//
// Revision 1.4  2004/05/10 14:04:22  hori
// no message
//
// Revision 1.3  2004/04/28 13:56:37  hori
// no message
//
// Revision 1.2  2004/04/28 12:01:57  hori
// for ASCII
//
// Revision 1.1  2004/04/26 10:05:17  hori
// No Message
//
//////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "hbhistory.h"
#include "os.h"

CHbHistory::CHbHistory()
{
	Read(m_histories);
}

CHbHistory::~CHbHistory()
{
	for (int i = 0; i < (int)m_histories.size(); ++i) {
		delete m_histories[i];
	}
}

BOOL CHbHistory::GetLogFileName(LPTSTR pszShortName, int nSize)
{
	HKEY hKey;
	TCHAR szHisName[] = _T("hotbizbar.log");
	TCHAR szMyName[MAX_PATH];
	LPTSTR pstr;
	DWORD type = REG_SZ;
	DWORD size = sizeof(szMyName);

	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{CB07F490-0619-4D1D-B44A-8F458E47D0DF}\\InprocServer32"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS) {
		return FALSE;
	}
	ZeroMemory(szMyName, sizeof(szMyName));
	RegQueryValueEx(hKey, _T(""), NULL, &type, (LPBYTE)&szMyName, &size);
	RegCloseKey(hKey);

	GetShortPathName(szMyName, pszShortName, nSize);
	pstr = _tcsrchr(pszShortName, '\\');
	if (pstr) {
		++pstr;
	} else {
		pstr = pszShortName;
	}
	_tcscpy_s(pstr, _tcslen(szHisName), szHisName);

	return TRUE;
}

void CHbHistory::PrintStr(FILE* fp, LPCSTR p)
{
	while (*p) {
		fputc(*p, fp);
		if (*p == '"')
			fputc('"', fp);
		++p;
	}
}

BOOL CHbHistory::Add(const vector<string>& szFields)
{
	TCHAR szShortName[MAX_PATH];
	FILE* fp;

	GetLogFileName(szShortName, sizeof(szShortName));
	_tfopen_s(&fp, szShortName, _T("a"));
	if (fp) {
		UINT i;
		for (i = 0; i < szFields.size(); ++i) {
			if (i)
				fprintf(fp, ",");
			fprintf(fp, "\"");
			PrintStr(fp, szFields[i].c_str());
			fprintf(fp, "\"");
		}
		fprintf(fp, "\r\n");
		fclose(fp);
	}
	return TRUE;
}

bool CHbHistory::ReadLine(FILE* fp, vector<string>& szFields, bool& bEOF)
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
			c = fgetc(fp);
		}
		if (ferror(fp))
			return false;
		if (feof(fp)) {
			if (!str.empty()) {
				szFields.push_back(str);
			}
			bEOF = true;
			break;
		}
		switch (c) {
		case '"':
			if (bInQuote) {
				d = fgetc(fp);
				if (ferror(fp))
					return false;
				if (feof(fp)) {
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
#ifdef WIN32
		case 0xFF:
#endif
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

BOOL CHbHistory::Read(vector<CHistory*>& histories)
{
	TCHAR szShortName[MAX_PATH];
	FILE* fp;
	bool bEOF;
	vector<string> szFields;

	GetLogFileName(szShortName, sizeof(szShortName));
	_tfopen_s(&fp, szShortName, _T("r"));
	if (fp) {
		do {
			CHistory* pHis;
			struct tm mt;
			char szYear[5];
			char szMonth[3];
			char szDay[3];
			char szHour[3];
			char szMinute[3];
			char szSecond[3];

			if (!ReadLine(fp, szFields, bEOF))
				break;
			if (szFields.size() >= 8) {
				pHis = new CHistory;
				pHis->m_nFuncID = (HOTBIZFUNC)atoi(szFields[0].c_str());
				pHis->m_nObjectID = atol(szFields[1].c_str());
				pHis->m_szUser = szFields[2].c_str();
				pHis->m_szGroup = szFields[3].c_str();

				strncpy_s(szYear, sizeof(szYear), szFields[4].c_str(), sizeof(szYear)-1);
				szYear[sizeof(szYear)-1] = '\0';
				strncpy_s(szMonth, sizeof(szMonth), szFields[4].c_str()+4, sizeof(szMonth)-1);
				szMonth[sizeof(szMonth)-1] = '\0';
				strncpy_s(szDay, sizeof(szDay), szFields[4].c_str()+6, sizeof(szDay)-1);
				szDay[sizeof(szDay)-1] = '\0';
				strncpy_s(szHour, sizeof(szHour), szFields[5].c_str(), sizeof(szHour)-1);
				szHour[sizeof(szHour)-1] = '\0';
				strncpy_s(szMinute, sizeof(szMinute), szFields[5].c_str()+2, sizeof(szMinute)-1);
				szMinute[sizeof(szMinute)-1] = '\0';
				strncpy_s(szSecond, sizeof(szSecond), szFields[5].c_str()+4, sizeof(szSecond)-1);
				szSecond[sizeof(szSecond)-1] = '\0';
				ZeroMemory(&mt, sizeof(mt));
				mt.tm_year = atoi(szYear) - 1900;
				mt.tm_mon = atoi(szMonth) - 1;
				mt.tm_mday = atoi(szDay);
				mt.tm_hour = atoi(szHour);
				mt.tm_min = atoi(szMinute);
				mt.tm_sec = atoi(szSecond);
				pHis->m_tmTime = mktime(&mt);

				pHis->m_szSubject = szFields[6].c_str();
				pHis->m_szContents = szFields[7].c_str();
				histories.push_back(pHis);
			}
			szFields.clear();
		} while (!bEOF);
		fclose(fp);
	}

	return TRUE;
}

BOOL CHbHistory::Write()
{
	TCHAR szShortName[MAX_PATH];
	FILE* fp;

	GetLogFileName(szShortName, sizeof(szShortName));
	_tfopen_s(&fp, szShortName, _T("w+"));
	if (fp) {
		for (int i = 0; i < (int)m_histories.size(); ++i) {
			struct tm ptm;
			char szDate[9] = {0};
			char szTime[7] = {0};
			localtime_s(&ptm, &m_histories[i]->m_tmTime);

			sprintf_s(szDate, sizeof(szDate), "%04d%02d%02d", ptm.tm_year+1900, ptm.tm_mon+1, ptm.tm_mday);
			sprintf_s(szTime, sizeof(szTime), "%02d%02d%02d", ptm.tm_hour, ptm.tm_min, ptm.tm_sec);

			fprintf(fp, "\"%d\",\"%ld\",", m_histories[i]->m_nFuncID, m_histories[i]->m_nObjectID);
			fprintf(fp, "\"");
			PrintStr(fp, m_histories[i]->m_szUser.c_str());
			fprintf(fp, "\",");
			fprintf(fp, "\"");
			PrintStr(fp, m_histories[i]->m_szGroup.c_str());
			fprintf(fp, "\",");
			fprintf(fp, "\"");
			PrintStr(fp, szDate);
			fprintf(fp, "\",");
			fprintf(fp, "\"");
			PrintStr(fp, szTime);
			fprintf(fp, "\",");
			fprintf(fp, "\"");
			PrintStr(fp, m_histories[i]->m_szSubject.c_str());
			fprintf(fp, "\",");
			fprintf(fp, "\"");
			PrintStr(fp, m_histories[i]->m_szContents.c_str());
			fprintf(fp, "\"\r\n");
		}
		fclose(fp);
	}

	return TRUE;
}

void CHbHistory::Remove(CHistory* pHis)
{
	std::vector<CHistory*>::iterator it;
	for (it = m_histories.begin(); it < m_histories.end(); ++it) {
		if (*it == pHis) {
			m_histories.erase(it);
			break;
		}
	}
}
