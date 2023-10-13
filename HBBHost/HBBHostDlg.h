// HBBHostDlg.h : ヘッダー ファイル
//

#if !defined(AFX_HBBHOSTDLG_H__1D069986_99AB_421C_AF8C_147A7DD400D8__INCLUDED_)
#define AFX_HBBHOSTDLG_H__1D069986_99AB_421C_AF8C_147A7DD400D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4100)
#pragma warning(disable: 4511)
#pragma warning(disable: 4512)
#pragma warning(disable: 4530)
#pragma warning(disable: 4663)
#pragma warning(disable: 4786)

#include <vector>
using std::vector;

#include "PopupDlg.h"

#define WM_MY_NOTIFYICON WM_USER+200

class CPopupInfo
{
public:
	CString	m_szTitle;
	CString	m_szMess;
	int		m_nFunc;
	long	m_nObject;
	CPopupInfo(LPCSTR pszTitle, LPCSTR pszMess, int nFunc, long nObject) {
		LPTSTR pszSubject = (LPTSTR)malloc((strlen(pszTitle) + 1) * sizeof(TCHAR));
		LPTSTR pszContents = (LPTSTR)malloc((strlen(pszMess) + 1) * sizeof(TCHAR));
#ifdef _UNICODE
		ZeroMemory(pszSubject, (strlen(pszTitle) + 1) * sizeof(TCHAR));
		MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, pszTitle, strlen(pszTitle), pszSubject, strlen(pszTitle) + 1);
#else
		strcpy(pszSubject, pszTitle);
#endif

#ifdef _UNICODE
		ZeroMemory(pszContents, (strlen(pszMess) + 1) * sizeof(TCHAR));
		MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, pszMess, strlen(pszMess), pszContents, strlen(pszMess) + 1);
#else
		strcpy(pszContents, pszMess);
#endif
		m_szTitle = pszSubject;
		m_szMess = pszContents;
		m_nFunc = nFunc;
		m_nObject = nObject;

		free(pszSubject);
		free(pszContents);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CHBBHostDlg ダイアログ

class CHBBHostDlg : public CDialog
{
// 構築
public:
	CHBBHostDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	virtual ~CHBBHostDlg();

// ダイアログ データ
	//{{AFX_DATA(CHBBHostDlg)
	public:
	enum { IDD = IDD_HBBHOST_DIALOG };
	CButton	m_btnStartStop;
	BOOL	m_bAutoStart;
	int		m_nInterval;
	BOOL	m_bPlaySound;
	UINT	m_nPopupTime;
	CString	m_szSoundFile;
	CString	m_szStatus;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHBBHostDlg)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON	m_hIcon;
	BOOL	m_bRecvInfo;
	vector<CPopupDlg*>	m_popup;
	vector<CPopupInfo*>	m_pupInfo;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CHBBHostDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnRefer();
	virtual void OnOK();
	afx_msg LONG OnMyNotifyIcon(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnHbbLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnHbbLogout(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnHbbQuit(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStopstart();
	afx_msg void OnAboutBox();
	afx_msg void OnLogin();
	afx_msg void OnLogout();
	afx_msg void OnHistory();
	afx_msg void OnHbhhelp();
	afx_msg void OnHbhoption();
	afx_msg void OnHbhquit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ClearVector();
	void ChangeTrayIcon(UINT idIcon, UINT idMess);
	void ChangeStatus();
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	void UpdateHBBStatus(HWND hwnd, ATOM atom);
	void CountHBBWindow(HWND hwnd, int& nCnt);
	void SendHBBLogin(HWND hwnd, UINT nMess);
	static UINT ControllingFunction( LPVOID pParam );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HBBHOSTDLG_H__1D069986_99AB_421C_AF8C_147A7DD400D8__INCLUDED_)
