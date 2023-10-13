// HBBCommon.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include "HBBCommon.h"
#include "LogDlg.h"
#include "hbhistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	メモ!
//
//		この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされた
//		どの関数も関数の最初に追加される AFX_MANAGE_STATE 
//		マクロを含んでいなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな
//		らないことを意味します、コンストラクタが MFC 
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

CLoginInfo g_loginInfo;

/////////////////////////////////////////////////////////////////////////////
// 唯一の CHBBCommonApp オブジェクト

CHBBCommonApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHBBCommonApp

BEGIN_MESSAGE_MAP(CHBBCommonApp, CWinApp)
	//{{AFX_MSG_MAP(CHBBCommonApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHBBCommonApp の構築

CHBBCommonApp::CHBBCommonApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance の中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// CHBBCommonApp の初期化

BOOL CHBBCommonApp::InitInstance()
{
//	if (!AfxSocketInit())
//	{
//		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
//		return FALSE;
//	}

	return TRUE;
}


extern "C" VOID PASCAL EXPORT GetLoginInfo(
	BOOL& bAutoLogin,
	LPTSTR pszURL, int nURL,
	LPTSTR pszUserName, int nUserName,
	LPTSTR pszPassword, int nPassword)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	bAutoLogin = g_loginInfo.GetAutoLogin();
	lstrcpyn(pszURL, g_loginInfo.GetURL(), nURL);
	lstrcpyn(pszUserName, g_loginInfo.GetUserName(), nUserName);
	lstrcpyn(pszPassword, g_loginInfo.GetPassword(), nPassword);
}

extern "C" BOOL PASCAL EXPORT LoginHotBiz(
	BOOL bAutoLogin,
	LPCTSTR pszURL,
	LPCTSTR pszUserName,
	LPCTSTR pszPassword)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!theApp.m_connection.Login(pszUserName, pszPassword))
		return FALSE;

	g_loginInfo.SetLastChecked(theApp.m_connection.GetServerTime());
	g_loginInfo.SetAutoLogin(bAutoLogin);
	g_loginInfo.SetURL(pszURL);
	g_loginInfo.SetUserName(pszUserName);
	g_loginInfo.SetPassword(pszPassword);

	return TRUE;
}

extern "C" VOID PASCAL EXPORT LogoutHotBiz()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.Logout();
}

extern "C" VOID PASCAL EXPORT GetNewsInfo(
	BOOL& bNewsValid,
	DWORD& nInterval,
	DWORD& nPopupTime,
	BOOL& bPlaySound,
	LPTSTR pszSoundFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	bNewsValid = g_loginInfo.GetNewsValid();
	nInterval = g_loginInfo.GetInterval();
	nPopupTime = g_loginInfo.GetPopupTime();
	bPlaySound = g_loginInfo.GetPlaySound();
	lstrcpy(pszSoundFile, g_loginInfo.GetSoundFile());
}

extern "C" VOID PASCAL EXPORT SetNewsInfo(
	BOOL bNewsValid,
	DWORD nInterval,
	DWORD nPopupTime,
	BOOL bPlaySound,
	LPCTSTR pszSoundFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	g_loginInfo.SetNewsValid(bNewsValid);
	g_loginInfo.SetInterval(nInterval);
	g_loginInfo.SetPopupTime(nPopupTime);
	g_loginInfo.SetPlaySound(bPlaySound);
	g_loginInfo.SetSoundFile(pszSoundFile);
//	g_loginInfo.WriteBack();
}

extern "C" HICON PASCAL EXPORT LoadHotBizIcon(UINT nFuncID, UINT nSizeX, UINT nSizeY)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return (HICON)LoadImage(theApp.m_hInstance, MAKEINTRESOURCE(g_nFuncIcon[nFuncID]), IMAGE_ICON, nSizeX, nSizeY, LR_DEFAULTCOLOR);
}

extern "C" BOOL PASCAL EXPORT AlreadyLoggedin()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.AlreadyLogin();
}

extern "C" LPCTSTR PASCAL EXPORT ConnectToHotBiz(LPCTSTR pszUserName, LPCTSTR pszPassword, HOTBIZFUNC nFunc, LPCTSTR pszParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.Connect(pszUserName, pszPassword, nFunc, pszParam);
}

extern "C" LPCSTR PASCAL EXPORT HotBizResult()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.GetHtml();
}

extern "C" bool PASCAL EXPORT ReadLine(LPCSTR& pszHtml, LPSTR** szFields, int& nFields, bool& bEOF)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	vector<string> fields;
	nFields = 0;
	if (!theApp.m_connection.ReadLine(pszHtml, fields, bEOF))
		return false;
	nFields = fields.size();
	*szFields = (LPSTR*)malloc(nFields * sizeof(LPSTR));
	for (int i = 0; i < nFields; ++i) {
		(*szFields)[i] = (LPSTR)malloc(fields[i].length() + 1);
		strcpy_s((*szFields)[i], fields[i].length(), fields[i].c_str());
	}
 	return true;
}

extern "C" VOID PASCAL EXPORT FreeReadLine(LPSTR* szFields, int nFields)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	for (int i = 0; i < nFields; ++i) {
		free(szFields[i]);
	}
	free(szFields);
}

extern "C" VOID PASCAL EXPORT HistoryAdd(LPSTR* szFields, int nFields)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CHbHistory his;
	vector<string> fields;
	for (int i = 0; i < nFields; ++i) {
		fields.push_back(szFields[i]);
	}
	his.Add(fields);
}

extern "C" time_t PASCAL EXPORT GetLastChecked()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return g_loginInfo.GetLastChecked();
}

extern "C" VOID PASCAL EXPORT SetLastChecked(time_t checked)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	g_loginInfo.SetLastChecked(checked);
}

extern "C" LPCTSTR PASCAL EXPORT GetProtocol()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.GetProtocol();
}

extern "C" LPCTSTR PASCAL EXPORT GetHost()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.GetHost();
}

extern "C" LPCTSTR PASCAL EXPORT GetServerPath()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.GetPath();
}

extern "C" LPCTSTR PASCAL EXPORT GetCGI(HOTBIZFUNC nFunc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.GetCGI(nFunc);
}

extern "C" VOID PASCAL EXPORT GetHeader(LPTSTR pszHeader)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.GetHeader(pszHeader);
}

extern "C" VOID PASCAL EXPORT GetParam(LPCTSTR pszUserName, LPCTSTR pszPassword, LPCTSTR pszOrg, LPTSTR pszParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.GetParam(pszUserName, pszPassword, pszOrg, pszParam);
}

extern "C" VOID PASCAL EXPORT ClearLoginInfo()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	g_loginInfo.SetLoginInfo(NULL, 0);
}

extern "C" VOID PASCAL EXPORT ClearUserPass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	g_loginInfo.ClearAll();
}

extern "C" VOID PASCAL EXPORT LogDialog(UINT& nRT, HOTBIZFUNC& nFunc, long& nObject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CLogDlg dlg;
	nRT = dlg.DoModal();
	if (nRT == IDOK) {
		dlg.GetSelected(nFunc, nObject);
	}
}

extern "C" VOID PASCAL EXPORT GetIconSize(int& nSizeX, int& nSizeY)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	nSizeX = HBBICONXS;
	nSizeY = HBBICONYS;
	if (g_loginInfo.GetDispBigIcon()) {
		nSizeX = HBBICONXB;
		nSizeY = HBBICONYB;
	}
}

extern "C" PICON_ITEM PASCAL EXPORT GetIconItem()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	PICON_ITEM pItem = g_loginInfo.GetIconItem();
	if (pItem)
		return pItem;
	return g_loginInfo.DefaultIconItem();
}

extern "C" VOID PASCAL EXPORT GetDispIconInfo(BOOL& bDispWhere, BOOL& bDispTimecard, BOOL& bDispBigicon)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	bDispWhere = g_loginInfo.GetDispWhere();
	bDispTimecard = g_loginInfo.GetDispTimeCard();
	bDispBigicon = g_loginInfo.GetDispBigIcon();
}

extern "C" VOID PASCAL EXPORT SetDispIconInfo(PICON_ITEM pItem, BOOL bDispWhere, BOOL bDispTimecard, BOOL bDispBigicon)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	g_loginInfo.SetDispWhere(bDispWhere);
	g_loginInfo.SetDispTimeCard(bDispTimecard);
	g_loginInfo.SetDispBigIcon(bDispBigicon);
	g_loginInfo.SetIconItem(pItem);
}

extern "C" VOID PASCAL EXPORT GetWhereString(LPTSTR pszText)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	map<long, TCHAR*>* pWhere;
	map<long, long>* pSEQ;
	theApp.m_connection.GetWheres(&pSEQ, &pWhere);
	std::map<long, TCHAR*>::const_iterator it;
	pszText[0] = _T('\0');
	for (it = pWhere->begin(); it != pWhere->end(); ++it) {
		if (theApp.m_connection.GetWhereID() == it->first) {
			_tcscpy_s(pszText, _tcslen(it->second), it->second);
			break;
		}
	}
}

extern "C" LPCTSTR PASCAL EXPORT GetGoTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.GetGoTime();
}

extern "C" LPCTSTR PASCAL EXPORT GetLeaveTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.GetLeaveTime();
}

extern "C" VOID PASCAL EXPORT SetGoTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.SetGoTime();
}

extern "C" VOID PASCAL EXPORT SetGoTimeStr(LPCSTR pszTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.SetGoTime(pszTime);
}

extern "C" VOID PASCAL EXPORT SetLeaveTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.SetLeaveTime();
}

extern "C" VOID PASCAL EXPORT SetLeaveTimeStr(LPCSTR pszTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.SetLeaveTime(pszTime);
}

extern "C" VOID PASCAL EXPORT SetWhereMem(long nWhereID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.SetWhereID(nWhereID);
}

extern "C" bool PASCAL EXPORT SetWhere(LPCTSTR pszUserName, LPCTSTR pszPassword, long nWhereID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.SetWhere(pszUserName, pszPassword, nWhereID);
}

extern "C" VOID PASCAL EXPORT Reload()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.m_connection.Reload();
}

extern "C" VOID PASCAL EXPORT BuildCommonLink(HMENU hMenu)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UINT i = 0;
	WORD wID = IDM_COMMONLINK;
	MENUITEMINFO mi;
	vector<TITLESQL*>* pCL = theApp.m_connection.GetCommonLink();
	std::vector<TITLESQL*>::const_iterator cit;
	OSVERSIONINFO ver;

	ZeroMemory(&ver, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);
	GetVersionEx(&ver);
	for (cit = pCL->begin(); cit != pCL->end(); ++cit) {
		ZeroMemory(&mi, sizeof(mi));
		mi.cbSize = sizeof(mi);
		if (!(*cit)->szSQL[0] && !(*cit)->szTitle[0]) {
			if (ver.dwMajorVersion >= 5)
				mi.fMask = MIIM_FTYPE;
			else
				mi.fMask = MIIM_TYPE;
			mi.fType = MFT_SEPARATOR;
		} else {
			if (ver.dwMajorVersion >= 5)
				mi.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING;
			else
				mi.fMask = MIIM_DATA | MIIM_TYPE | MIIM_ID | MIIM_STATE;
			mi.fType = MFT_STRING;
			mi.fState = MFS_ENABLED;
			mi.wID = wID;
			mi.dwItemData = (LPARAM)((*cit)->szSQL);
			mi.dwTypeData = (*cit)->szTitle;
			mi.cch = _tcslen((*cit)->szTitle);
		}
		InsertMenuItem(hMenu, i, TRUE, &mi);
		++i;
	}
}

extern "C" VOID PASCAL EXPORT BuildPrivateLink(HMENU hMenu)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UINT i = 0;
	WORD wID = IDM_PRIVATELINK;
	MENUITEMINFO mi;
	vector<TITLESQL*>* pCL = theApp.m_connection.GetPrivateLink();
	std::vector<TITLESQL*>::const_iterator cit;
	OSVERSIONINFO ver;

	ZeroMemory(&ver, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);
	GetVersionEx(&ver);
	for (cit = pCL->begin(); cit != pCL->end(); ++cit) {
		ZeroMemory(&mi, sizeof(mi));
		mi.cbSize = sizeof(mi);
		if (!(*cit)->szSQL[0] && !(*cit)->szTitle[0]) {
			if (ver.dwMajorVersion >= 5)
				mi.fMask = MIIM_FTYPE;
			else
				mi.fMask = MIIM_TYPE;
			mi.fType = MFT_SEPARATOR;
		} else {
			if (ver.dwMajorVersion >= 5)
				mi.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING;
			else
				mi.fMask = MIIM_DATA | MIIM_TYPE | MIIM_ID | MIIM_STATE;
			mi.fType = MFT_STRING;
			mi.fState = MFS_ENABLED;
			mi.wID = wID;
			mi.dwItemData = (LPARAM)((*cit)->szSQL);
			mi.dwTypeData = (*cit)->szTitle;
			mi.cch = _tcslen((*cit)->szTitle);
		}
		InsertMenuItem(hMenu, i, TRUE, &mi);
		++i;
	}
}

extern "C" VOID PASCAL EXPORT BuildHelperLink(HMENU hMenu)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UINT i = 0;
	WORD wID = IDM_HELPERLINK;
	MENUITEMINFO mi;
	vector<TITLESQL*>* pCL = theApp.m_connection.GetHelperLink();
	std::vector<TITLESQL*>::const_iterator cit;
	OSVERSIONINFO ver;

	ZeroMemory(&ver, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);
	GetVersionEx(&ver);
	for (cit = pCL->begin(); cit != pCL->end(); ++cit) {
		ZeroMemory(&mi, sizeof(mi));
		mi.cbSize = sizeof(mi);
		if (ver.dwMajorVersion >= 5)
			mi.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING;
		else
			mi.fMask = MIIM_DATA | MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mi.fType = MFT_STRING;
		mi.fState = MFS_ENABLED;
		mi.wID = wID;
		mi.dwItemData = (LPARAM)((*cit)->szSQL);
		mi.dwTypeData = (*cit)->szTitle;
		mi.cch = _tcslen((*cit)->szTitle);
		InsertMenuItem(hMenu, i, TRUE, &mi);
		++i;
	}
}

extern "C" VOID PASCAL EXPORT BuildWhereMenu(HMENU hMenu)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UINT i = 0;
	map<long, TCHAR*>* pWhere;
	map<long, long>* pSEQ;
	theApp.m_connection.GetWheres(&pSEQ, &pWhere);
	std::map<long, long>::const_iterator it;
	OSVERSIONINFO ver;

	ZeroMemory(&ver, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);
	GetVersionEx(&ver);
	for (it = pSEQ->begin(); it != pSEQ->end(); ++it) {
		MENUITEMINFO mi;
		ZeroMemory(&mi, sizeof(mi));
		mi.cbSize = sizeof(mi);
		if (ver.dwMajorVersion >= 5)
			mi.fMask = MIIM_DATA | MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING;
		else
			mi.fMask = MIIM_DATA | MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mi.fType = MFT_STRING;
		mi.fState = MFS_ENABLED;
		mi.wID = IDM_WHERE;
		mi.dwItemData = it->second;
		mi.dwTypeData = (*pWhere)[it->second];
		mi.cch = _tcslen((*pWhere)[it->second]);
		InsertMenuItem(hMenu, i, TRUE, &mi);
		++i;
	}
}

extern "C" VOID PASCAL EXPORT GetLogoSize(int& nSizeX, int& nSizeY)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	nSizeX = HBBLOGOXS;
	nSizeY = HBBLOGOYS;
	if (g_loginInfo.GetDispBigIcon()) {
		nSizeX = HBBLOGOXB;
		nSizeY = HBBLOGOYB;
	}
}

extern "C" HICON PASCAL EXPORT LoadResourceIcon(LPCTSTR pszResource, UINT nSizeX, UINT nSizeY)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return (HICON)LoadImage(theApp.m_hInstance, pszResource, IMAGE_ICON, nSizeX, nSizeY, LR_DEFAULTCOLOR);
}

extern "C" UINT PASCAL EXPORT FuncToCommand(HOTBIZFUNC nFunc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return g_nFuncItem[nFunc];
}

extern "C" LPCTSTR PASCAL EXPORT GetHotBizUserName()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return g_loginInfo.GetUserName();
}

extern "C" BOOL PASCAL EXPORT HotBizStatus()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.Status();
}

extern "C" time_t PASCAL EXPORT GetServerTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return theApp.m_connection.GetServerTime();
}
