#ifndef __HBBEXPORT_H__
#define __HBBEXPORT_H__

#include "resource.h"		// ÉÅÉCÉì ÉVÉìÉ{Éã

#ifndef MIIM_FTYPE
	#define MIIM_FTYPE	0x00000100
#endif
#ifndef MIIM_STRING
	#define MIIM_STRING	0x00000040
#endif

#define WM_HBBLOGIN		(WM_USER+100)
#define WM_HBBUPDATE	(WM_USER+101)
#define WM_HBBQUIT		(WM_USER+102)
#define WM_HBBLOGOUT	(WM_USER+103)


#define HBBICONXS	16
#define HBBICONYS	16
#define HBBICONXB	24
#define HBBICONYB	24
#define HBBLOGOXS	60
#define HBBLOGOYS	16
#define HBBLOGOXB	72
#define HBBLOGOYB	24
#define ITEMTABLESIZE 18

//#define ARRAYSIZE(array) (sizeof(array) / sizeof(array[0]))

#define HOTBIZBARCLASS	"HotBizBar"

typedef struct _ICON_ITEM {
	int		m_nSEQ;
	BOOL	m_bValid;
	TCHAR	m_szName[20];
	TCHAR	m_szMode[50];
	TCHAR	m_szAdMode[50];
} ICON_ITEM, *PICON_ITEM;


enum HOTBIZFUNC {
	FNC_MAIN = 0,
	FNC_SCHEDULE = 1,
	FNC_MESSAGE = 2,
	FNC_MAIL = 3,
	FNC_FORUM = 4,
	FNC_BULLETIN = 5,
	FNC_PROJECT = 6,
	FNC_TODO = 7,
	FNC_RESERVE = 8,
	FNC_CABINET = 9,
	FNC_ADDRESS = 10,
	FNC_WORKFLOW = 11,
	FNC_DUMY = 12,
	FNC_TIMECARD = 13,
	FNC_CIRCULATE = 14,
	FNC_WHERE = 15,
	FNC_REPORT = 16,
	FNC_MESSENGER =17
};
#define FNC_GOTIME		18
#define FNC_LEAVETIME	19
#define FNC_HISTORY		20
#define FNC_LOGIN		21
#define FNC_LOGOUT		22

extern UINT g_nFuncIcon[ITEMTABLESIZE];
extern UINT g_nFuncItem[ITEMTABLESIZE];


extern "C" VOID PASCAL EXPORT DbgMessageBox(LPCTSTR format, ...);
extern "C" VOID PASCAL EXPORT GetLoginInfo(
	BOOL& bAutoLogin,
	LPTSTR pszURL, int nURL,
	LPTSTR pszUserName, int nUserName,
	LPTSTR pszPassword, int nPassword);
extern "C" BOOL PASCAL EXPORT LoginHotBiz(
	BOOL bAutoLogin,
	LPCTSTR pszURL,
	LPCTSTR pszUserName,
	LPCTSTR pszPassword);
extern "C" VOID PASCAL EXPORT LogoutHotBiz();
extern "C" VOID PASCAL EXPORT GetNewsInfo(
	BOOL& bNewsValid,
	DWORD& nInterval,
	DWORD& nPopupTime,
	BOOL& bPlaySound,
	LPTSTR pszSoundFile);
extern "C" VOID PASCAL EXPORT SetNewsInfo(
	BOOL bNewsValid,
	DWORD nInterval,
	DWORD nPopupTime,
	BOOL bPlaySound,
	LPCTSTR pszSoundFile);
extern "C" BOOL PASCAL EXPORT AlreadyLoggedin();
extern "C" HICON PASCAL EXPORT LoadHotBizIcon(UINT nFuncID, UINT nSizeX, UINT nSizeY);
extern "C" LPCTSTR PASCAL EXPORT ConnectToHotBiz(LPCTSTR pszUserName, LPCTSTR pszPassword, HOTBIZFUNC nFunc, LPCTSTR pszParam);
extern "C" LPCSTR PASCAL EXPORT HotBizResult();
extern "C" bool PASCAL EXPORT ReadLine(LPCSTR& pszHtml, LPSTR** szFields, int& nFields, bool& bEOF);
extern "C" VOID PASCAL EXPORT FreeReadLine(LPSTR* szFields, int nFields);
extern "C" VOID PASCAL EXPORT HistoryAdd(LPSTR* szFields, int nFields);
extern "C" time_t PASCAL EXPORT GetLastChecked();
extern "C" VOID PASCAL EXPORT SetLastChecked(time_t checked);
extern "C" LPCTSTR PASCAL EXPORT GetProtocol();
extern "C" LPCTSTR PASCAL EXPORT GetHost();
extern "C" LPCTSTR PASCAL EXPORT GetServerPath();
extern "C" LPCTSTR PASCAL EXPORT GetCGI(HOTBIZFUNC nFunc);
extern "C" VOID PASCAL EXPORT GetHeader(LPTSTR pszHeader);
extern "C" VOID PASCAL EXPORT GetParam(LPCTSTR pszUserName, LPCTSTR pszPassword, LPCTSTR pszOrg, LPTSTR pszParam);
extern "C" VOID PASCAL EXPORT ClearLoginInfo();
extern "C" VOID PASCAL EXPORT LogDialog(UINT& nRT, HOTBIZFUNC& nFunc, long& nObject);
extern "C" VOID PASCAL EXPORT GetIconSize(int& nSizeX, int& nSizeY);
extern "C" PICON_ITEM PASCAL EXPORT GetIconItem();
extern "C" VOID PASCAL EXPORT GetDispIconInfo(BOOL& bDispWhere, BOOL& bDispTimecard, BOOL& bDispBigicon);
extern "C" VOID PASCAL EXPORT SetDispIconInfo(PICON_ITEM pItem, BOOL bDispWhere, BOOL bDispTimecard, BOOL bDispBigicon);
extern "C" VOID PASCAL EXPORT GetWhereString(LPTSTR pszText);
extern "C" LPCTSTR PASCAL EXPORT GetGoTime();
extern "C" LPCTSTR PASCAL EXPORT GetLeaveTime();
extern "C" VOID PASCAL EXPORT SetGoTime();
extern "C" VOID PASCAL EXPORT SetLeaveTime();
extern "C" bool PASCAL EXPORT SetWhere(LPCTSTR pszUserName, LPCTSTR pszPassword, long nWhereID);
extern "C" VOID PASCAL EXPORT Reload();
extern "C" VOID PASCAL EXPORT BuildCommonLink(HMENU hMenu);
extern "C" VOID PASCAL EXPORT BuildPrivateLink(HMENU hMenu);
extern "C" VOID PASCAL EXPORT BuildHelperLink(HMENU hMenu);
extern "C" VOID PASCAL EXPORT BuildWhereMenu(HMENU hMenu);
extern "C" VOID PASCAL EXPORT ClearUserPass();
extern "C" VOID PASCAL EXPORT GetLogoSize(int& nSizeX, int& nSizeY);
extern "C" HICON PASCAL EXPORT LoadResourceIcon(LPCTSTR pszResource, UINT nSizeX, UINT nSizeY);
extern "C" UINT PASCAL EXPORT FuncToCommand(HOTBIZFUNC nFunc);
extern "C" LPCTSTR PASCAL EXPORT GetHotBizUserName();
extern "C" VOID PASCAL EXPORT SetGoTimeStr(LPCSTR pszTime);
extern "C" VOID PASCAL EXPORT SetLeaveTimeStr(LPCSTR pszTime);
extern "C" VOID PASCAL EXPORT SetWhereMem(long nWhereID);
extern "C" BOOL PASCAL EXPORT HotBizStatus();
extern "C" time_t PASCAL EXPORT GetServerTime();

#endif
