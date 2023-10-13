// LoginDlg.h : CLoginDlg の宣言

#ifndef __LOGINDLG_H_
#define __LOGINDLG_H_

#include "resource.h"       // メイン シンボル
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg
class CLoginDlg : 
	public CAxDialogImpl<CLoginDlg>
{
public:
	CLoginDlg();
	~CLoginDlg();

	enum { IDD = IDD_LOGINDLG };

BEGIN_MSG_MAP(CLoginDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// ハンドラのプロトタイプ:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	void GetResult(LPTSTR pszURL, LPTSTR pszUserName, LPTSTR pszPassword, BOOL& bAutoSave);

private:
	TCHAR	m_szURL[256];
	TCHAR	m_szUserName[21];
	TCHAR	m_szPassword[21];
	BOOL	m_bAutoSave;
};

#endif //__LOGINDLG_H_
