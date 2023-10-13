//////////////////////////////////////////////////////////////////////////////
//
//  Connection to HotBiz for HotBizBar(“ú–{Œê)
//
// $Id: hotbizconnection.h,v 1.9 2004/06/30 10:49:28 hori Exp $
// $Log: hotbizconnection.h,v $
// Revision 1.9  2004/06/30 10:49:28  hori
// fix 1.0.0.1
//
// Revision 1.8  2004/06/29 16:16:25  hori
// no message
//
// Revision 1.7  2004/06/27 15:34:18  hori
// no message
//
// Revision 1.6  2004/06/24 09:59:14  hori
// up
//
// Revision 1.5  2004/06/21 09:21:22  hori
// change
//
// Revision 1.4  2004/06/08 09:13:36  hori
// NoMess
//
// Revision 1.3  2004/06/04 10:24:57  hori
// NoMess
//
// Revision 1.2  2004/06/01 09:48:44  hori
// NoMess
//
// Revision 1.1  2004/05/21 10:19:51  hori
// Add
//
// Revision 1.12  2004/05/20 10:10:12  hori
// NoMess
//
// Revision 1.11  2004/05/13 09:53:29  hori
// No Message
//
// Revision 1.10  2004/05/12 09:49:39  hori
// No Mess
//
// Revision 1.9  2004/05/06 09:48:15  hori
// No Mess
//
// Revision 1.8  2004/04/30 11:20:56  hori
// No message
//
// Revision 1.7  2004/04/28 10:07:42  hori
// No Messaghe
//
// Revision 1.6  2004/04/23 10:36:03  hori
// No Message
//
// Revision 1.5  2004/04/20 10:09:24  hori
// No Message
//
// Revision 1.4  2004/04/19 15:41:42  hori
// no message
//
// Revision 1.3  2004/04/19 09:39:29  hori
// No Message
//
// Revision 1.2  2004/04/15 10:10:55  hori
// add icons
//
// Revision 1.1  2004/04/14 10:32:43  hori
// add new staff.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef __HOTBIZCONNECTION_H__
#define __HOTBIZCONNECTION_H__

#pragma warning(disable: 4100)
#pragma warning(disable: 4511)
#pragma warning(disable: 4512)
#pragma warning(disable: 4530)
#pragma warning(disable: 4663)
#pragma warning(disable: 4786)

#include "logininfo.h"
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::map;

extern CLoginInfo g_loginInfo;

#define HBBNAMELEN 256
typedef TCHAR HBBNAME[HBBNAMELEN];
typedef struct _TITLESQL {
	HBBNAME szTitle;
	HBBNAME szSQL;
} TITLESQL, *PTITLESQL;

class CHotBizConnection
{
public:
	CHotBizConnection();
	virtual ~CHotBizConnection();

	void Reload();
	BOOL AlreadyLogin(){return (m_pszCookie!=NULL);}
	BOOL Login(LPCTSTR pszUserName, LPCTSTR pszPassword);
	BOOL Status();
	void Logout();
	LPCTSTR Connect(LPCTSTR pszUserName, LPCTSTR pszPassword, HOTBIZFUNC nFunc, LPCTSTR pszParam);

	LPCTSTR GetHost(){return m_pszHost;}
	LPCTSTR GetPath(){return m_pszPath;}
	LPCTSTR GetProtocol(){return m_szProtocol;}
	LPCTSTR GetGoTime(){return m_szGoTime;}
	void SetGoTime();
	void SetGoTime(LPCSTR pszTime);
	LPCTSTR GetLeaveTime(){return m_szLeaveTime;}
	void SetLeaveTime();
	void SetLeaveTime(LPCSTR pszTime);
	LPCTSTR GetCGI(HOTBIZFUNC nFunc);
	void GetHeader(LPTSTR pszHeader);
	void GetParam(LPCTSTR pszUserName, LPCTSTR pszPassword, LPCTSTR pszOrg, LPTSTR pszParam);
	bool ReadLine(LPCSTR& pszHtml, vector<string>& szFields, bool& bEOF);
	LPCSTR SkipHeader(LPSTR pszHtml);
#ifdef _UNICODE
	LPCTSTR SkipHeader(LPTSTR psztHtml);
#endif
	LPCSTR GetHtml(){return SkipHeader(m_pszHtml);}
	bool SetWhere(LPCTSTR pszUserName, LPCTSTR pszPassword, long nWhereID);
	void SetWhereID(long nWhereID);
	void SetLastChecked(time_t checked) {g_loginInfo.SetLastChecked(checked);}
	long GetWhereID(){return m_nWhereID;}
	void GetWheres(map<long, long>** ppSEQ, map<long, TCHAR*>** ppWhere) {
		*ppSEQ = &m_mapSEQs;
		*ppWhere = &m_mapWheres;
	}
	vector<TITLESQL*>* GetCommonLink(){return &m_vecCommonLink;}
	vector<TITLESQL*>* GetPrivateLink(){return &m_vecPrivateLink;}
	vector<TITLESQL*>* GetHelperLink(){return &m_vecHelperLink;}
	time_t GetServerTime();

private:
	void ClearData();
	void ClearLogin();
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	void EnumChild(HWND hwnd, int& nCnt);
	void AnalizeLoginInfo(LPSTR psztHtml, BOOL bIcon=TRUE);

private:
	TCHAR		m_szProtocol[20];
	LPTSTR		m_pszHost;
	LPTSTR		m_pszPath;
	LPSTR		m_pszHtml;
	LPTSTR		m_psztHtml;
	LPTSTR		m_pszCookie;
	BOOL		m_bHttps;
	long		m_nUserID;
	long		m_nGroupID;
	long		m_nWhereID;
	TCHAR		m_szGoTime[5];
	TCHAR		m_szLeaveTime[5];
	map<long, long>		m_mapSEQs;
	map<long, TCHAR*>	m_mapWheres;
	vector<TITLESQL*>	m_vecCommonLink;
	vector<TITLESQL*>	m_vecPrivateLink;
	vector<TITLESQL*>	m_vecHelperLink;
};

#endif
