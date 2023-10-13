//////////////////////////////////////////////////////////////////////////////
//
//  LoginInfo for HotBizBar(“ú–{Œê)
//
// $Id: logininfo.h,v 1.7 2004/06/29 16:16:25 hori Exp $
// $Log: logininfo.h,v $
// Revision 1.7  2004/06/29 16:16:25  hori
// no message
//
// Revision 1.6  2004/06/27 15:34:18  hori
// no message
//
// Revision 1.5  2004/06/24 09:59:14  hori
// up
//
// Revision 1.4  2004/06/23 08:22:25  hori
// up
//
// Revision 1.3  2004/05/25 07:48:07  hori
// Add
//
// Revision 1.2  2004/05/24 09:57:43  hori
// NoMess
//
// Revision 1.1  2004/05/21 10:19:51  hori
// Add
//
// Revision 1.13  2004/05/18 13:25:28  hori
// no message
//
// Revision 1.12  2004/05/18 09:56:11  hori
// No Mess
//
// Revision 1.11  2004/05/12 09:49:39  hori
// No Mess
//
// Revision 1.10  2004/05/11 09:58:29  hori
// No Message
//
// Revision 1.9  2004/05/07 09:58:07  hori
// No Message
//
// Revision 1.8  2004/05/06 09:48:15  hori
// No Mess
//
// Revision 1.7  2004/04/30 11:20:56  hori
// No message
//
// Revision 1.6  2004/04/28 10:07:42  hori
// No Messaghe
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
#ifndef __LOGININFO_H__
#define __LOGININFO_H__

#include "hbbexport.h"

class CLoginInfo {
public:
	CLoginInfo();
	virtual ~CLoginInfo();

//	void Reload();
	void DefaultIconItem(PICON_ITEM stIconItem);
	PICON_ITEM DefaultIconItem();

	LPCTSTR GetURL();			//{return m_szURL;}
	LPCTSTR GetUserName();		//{return m_szUserName;}
	LPCTSTR GetPassword();		//{return m_szPassword;}
	BOOL GetPlaySound();		//{return m_bPlaySound;}
	LPCTSTR GetSoundFile();		//{return m_szSoundFile;}
	BOOL GetAutoLogin();		//{return m_bAutoLogin;}
	BOOL GetNewsValid();		//{return m_bNewsValid;}
	DWORD GetInterval();		//{return m_nInterval;}
	DWORD GetPopupTime();		//{return m_nPopupTime;}
	BOOL GetDispWhere();		//{return m_bDispWhere;}
	BOOL GetDispTimeCard();		//{return m_bDispTimeCard;}
	BOOL GetDispBigIcon();		//{return m_bDispBigIcon;}
	PICON_ITEM GetIconItem();	//{return (PICON_ITEM)&m_stIconItem;}
	time_t GetLastChecked();	//{return m_nLastChecked;}
	LPCSTR GetLoginInfo();		//{return m_pszLoginInfo;}

	void SetURL(LPCTSTR pszURL);
	void SetUserName(LPCTSTR pszUserName);
	void SetPassword(LPCTSTR pszPassword);
	void SetPlaySound(BOOL bPlay);
	void SetSoundFile(LPCTSTR pszFile);
	void SetAutoLogin(BOOL bAutoLogin);
	void SetNewsValid(BOOL bValid);
	void SetInterval(DWORD nIner);
	void SetPopupTime(DWORD nPopup);
	void SetDispWhere(BOOL bDisp);
	void SetDispTimeCard(BOOL bDisp);
	void SetDispBigIcon(BOOL bBig);
	void SetIconItem(PICON_ITEM pItem);
	void SetLastChecked(time_t checked);
	void SetLoginInfo(LPCSTR pszHtml, UINT nSize);

//	BOOL WriteBack();
	BOOL ClearAll();

private:
	// CLoginPage
	TCHAR	m_szURL[256];
	TCHAR	m_szUserName[256];
	TCHAR	m_szPassword[256];
	BOOL	m_bAutoLogin;

	// CNewsPage
	BOOL	m_bNewsValid;
	DWORD	m_nInterval;
	DWORD	m_nPopupTime;

	// CIconPage
	BOOL	m_bDispWhere;
	BOOL	m_bDispTimeCard;
	BOOL	m_bDispBigIcon;
	ICON_ITEM m_stIconItem[ITEMTABLESIZE];

	// Common
	BOOL	m_bPlaySound;
	TCHAR	m_szSoundFile[MAX_PATH];
	LPSTR	m_pszLoginInfo;
	time_t	m_nLastChecked;
};

#endif
