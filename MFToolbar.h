//MFToolbar.h : Declaration of the CMFToolbar

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson © 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#ifndef __MFTOOLBAR_H_
#define __MFTOOLBAR_H_

#include <EXDISPID.H>
#include "resource.h"
#include "hbbexport.h"

#define WM_HBBLOGIN		(WM_USER+100)
#ifndef WM_MENUCOMMAND
#define WM_MENUCOMMAND	0x0126
#endif

class CHotBizBar;

/////////////////////////////////////////////////////////////////////////////
// CMFToolbar
class CMFToolbar : public CWindowImpl<CMFToolbar>
{
friend class CPopupDlg;
public:
	DECLARE_WND_SUPERCLASS(TEXT(HOTBIZBARCLASS), TOOLBARCLASSNAME)

	BEGIN_MSG_MAP(CMFToolbar)
		COMMAND_ID_HANDLER(IDM_OPTION, OnOption)
		COMMAND_ID_HANDLER(IDM_LOG, OnLog)
		COMMAND_ID_HANDLER(IDM_LOGIN, OnMenuLogin)
		COMMAND_ID_HANDLER(IDM_LOGOUT, OnMenuLogout)
		COMMAND_ID_HANDLER(IDM_UNINST, OnUninst)
		COMMAND_ID_HANDLER(IDM_VERSION, OnVersion)
		COMMAND_ID_HANDLER(IDM_HELP, OnHelp)
		COMMAND_ID_HANDLER(IDM_HOME, OnHome)
		COMMAND_ID_HANDLER(IDM_SCHEDULE, OnSchedule)
		COMMAND_ID_HANDLER(IDM_MESSAGE, OnMessage)
		COMMAND_ID_HANDLER(IDM_MAIL, OnMail)
		COMMAND_ID_HANDLER(IDM_FORUM, OnForum)
		COMMAND_ID_HANDLER(IDM_BULLETIN, OnBulletin)
		COMMAND_ID_HANDLER(IDM_PROJECT, OnProject)
		COMMAND_ID_HANDLER(IDM_TODO, OnTodo)
		COMMAND_ID_HANDLER(IDM_RESERVE, OnReserve)
		COMMAND_ID_HANDLER(IDM_CABINET, OnCabinet)
		COMMAND_ID_HANDLER(IDM_ADDRESS, OnAddress)
		COMMAND_ID_HANDLER(IDM_WORKFLOW, OnWorkflow)
		COMMAND_ID_HANDLER(IDM_TIMECARD, OnTimecard)
		COMMAND_ID_HANDLER(IDM_CIRCULATE, OnCirculate)
		COMMAND_ID_HANDLER(IDM_REPORT, OnReport)
		COMMAND_ID_HANDLER(IDM_GOTIME, OnGotime)
		COMMAND_ID_HANDLER(IDM_LEAVETIME, OnLeavetime)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_MENUCOMMAND, OnMenuCommand)
		MESSAGE_HANDLER(WM_SETTINGCHANGE, OnSettingChange)
		MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
		MESSAGE_HANDLER(WM_MOVE, OnMove)
		MESSAGE_HANDLER(WM_HBBLOGIN, OnLogin)
		MESSAGE_HANDLER(WM_HBBLOGOUT, OnLogout)
		MESSAGE_HANDLER(WM_HBBUPDATE, OnUpdate)
		NOTIFY_CODE_HANDLER(TBN_DROPDOWN, OnDropDown)
		DEFAULT_REFLECTION_HANDLER()
	ALT_MSG_MAP(1)
		COMMAND_ID_HANDLER(IDM_LOG, OnLog)
		COMMAND_ID_HANDLER(IDM_SCHEDULE, OnSchedule)
		COMMAND_ID_HANDLER(IDM_MESSAGE, OnMessage)
		COMMAND_ID_HANDLER(IDM_MAIL, OnMail)
		COMMAND_ID_HANDLER(IDM_FORUM, OnForum)
		COMMAND_ID_HANDLER(IDM_BULLETIN, OnBulletin)
		COMMAND_ID_HANDLER(IDM_PROJECT, OnProject)
		COMMAND_ID_HANDLER(IDM_TODO, OnTodo)
		COMMAND_ID_HANDLER(IDM_RESERVE, OnReserve)
		COMMAND_ID_HANDLER(IDM_CABINET, OnCabinet)
		COMMAND_ID_HANDLER(IDM_ADDRESS, OnAddress)
		COMMAND_ID_HANDLER(IDM_WORKFLOW, OnWorkflow)
		COMMAND_ID_HANDLER(IDM_TIMECARD, OnTimecard)
		COMMAND_ID_HANDLER(IDM_CIRCULATE, OnCirculate)
		COMMAND_ID_HANDLER(IDM_REPORT, OnReport)
		COMMAND_ID_HANDLER(IDM_GOTIME, OnGotime)
		COMMAND_ID_HANDLER(IDM_LEAVETIME, OnLeavetime)
		NOTIFY_CODE_HANDLER(TBN_DROPDOWN, OnDropDown)
	END_MSG_MAP()

// Handler prototypes:
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMenuCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSettingChange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLogin(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLogout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnUpdate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOption(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnUninst(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLog(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnMenuLogin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnMenuLogout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnVersion(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnHome(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSchedule(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnMessage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnMail(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnForum(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBulletin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnProject(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTodo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnReserve(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCabinet(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAddress(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnWorkflow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTimecard(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCirculate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnReport(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnGotime(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLeavetime(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDropDown(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	CMFToolbar(CHotBizBar* pBar);
	virtual ~CMFToolbar();
	void SetBrowser(IWebBrowser2* pBrowser);
	UINT GetMinWidth(){return m_nMinWidth;}
	UINT GetActualWidth(){return m_nActualWidth;}
	BOOL SetBandRebar();

private:
	static BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam);
	void EnumCount(HWND hwnd, int& nCnt);
	void EnumLogin(HWND hwnd, UINT nMess);
	BOOL AdminLogin();
	void CleanupResource();
	void ClearButton();
	void DrawTB();
	BOOL LaunchHotBiz(HOTBIZFUNC nFunc, LPCTSTR pszOrg);
	BOOL DispFuncObj(HOTBIZFUNC nFunc, long nObject);
	BOOL PunchTimecard(BOOL bGo);
	BOOL LoginHotBiz(BOOL bForce=FALSE);
	HOTBIZFUNC GetNextFunc(int nSEQ);
	void SetMenuStates();
	HWND FindRebar(HWND hwndStart);
	LRESULT OnFunction(HOTBIZFUNC nFunc);

private:
	vector<CPopupDlg*>	m_popup;
	IWebBrowser2*		m_pBrowser;
	CHotBizBar*			m_pHotBizBar;
	CContainedWindow	m_RebarContainer;
	HIMAGELIST			m_hImageList1;
	HIMAGELIST			m_hImageList2;
	HCURSOR				m_hHyperCursor;
	HMENU				m_hMainMenu;
	HMENU				m_hWhereMenu;
	HMENU				m_hCommonMenu;
	HMENU				m_hPrivateMenu;
	HMENU				m_hHelperMenu;
	HFONT				m_hStaticFont;
	HWND				m_ctlRebar;
	HWND				m_hToolTip;
	HWND				m_hStaticGo;
	HWND				m_hStaticLeave;
	DWORD				m_dwCookie;
	UINT				m_nWhereButton;
	UINT				m_nMinWidth;
	UINT				m_nActualWidth;
};

#endif //__MFTOOLBAR_H_
