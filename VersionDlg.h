// VersionDlg.h : CVersionDlg の宣言

#ifndef __VERSIONDLG_H_
#define __VERSIONDLG_H_

#include "resource.h"       // メイン シンボル
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CVersionDlg
class CVersionDlg : 
	public CAxDialogImpl<CVersionDlg>
{
public:
	CVersionDlg();
	~CVersionDlg();

	enum { IDD = IDD_VERSIONDLG };

BEGIN_MSG_MAP(CVersionDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	COMMAND_ID_HANDLER(IDOK, OnOK)
END_MSG_MAP()
// ハンドラのプロトタイプ:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif //__VERSIONDLG_H_
