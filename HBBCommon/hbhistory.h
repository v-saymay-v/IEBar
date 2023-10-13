//////////////////////////////////////////////////////////////////////////////
//
//  History for HotBizBar(“ú–{Œê)
//
// $Id: hbhistory.h,v 1.4 2004/06/25 09:07:32 hori Exp $
// $Log: hbhistory.h,v $
// Revision 1.4  2004/06/25 09:07:32  hori
// up
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
// Revision 1.2  2004/05/10 14:04:22  hori
// no message
//
// Revision 1.1  2004/04/26 10:05:17  hori
// No Message
//
//////////////////////////////////////////////////////////////////////////////
#ifndef __HBHISTORY_H__
#define __HBHISTORY_H__

#pragma warning(disable: 4100)
#pragma warning(disable: 4511)
#pragma warning(disable: 4512)
#pragma warning(disable: 4530)
#pragma warning(disable: 4663)
#pragma warning(disable: 4786)

#include "logininfo.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class CHistory {
public:
	HOTBIZFUNC	m_nFuncID;
	long		m_nObjectID;
	string		m_szUser;
	string		m_szGroup;
	time_t		m_tmTime;
	string		m_szSubject;
	string		m_szContents;
};

class CHbHistory {
public:
	CHbHistory();
	virtual ~CHbHistory();

	static bool ReadLine(FILE* fp, vector<string>& szFields, bool& bEOF);
	BOOL Add(const vector<string>& szFields);
	BOOL Read(vector<CHistory*>& histories);
	BOOL Write();
	void Remove(CHistory* pHis);
	vector<CHistory*>* GetHistories(){return &m_histories;}

private:
	void PrintStr(FILE* fp, LPCSTR p);
	BOOL GetLogFileName(LPTSTR pszShortName, int nSize);

private:
	vector<CHistory*>	m_histories;
};

#endif
