// WaitDlg.h : CWaitDlg の宣言

#ifndef __WAITDLG_H_
#define __WAITDLG_H_

#include "resource.h"       // メイン シンボル
#include <atlhost.h>


/////////////////////////////////////////////////////////////////////////////
// CWaitDlg
class CWaitDlg : 
	public CAxDialogImpl<CWaitDlg>
{
public:
	CWaitDlg(LPCTSTR pszMess)
	{
		m_pszMess = (LPTSTR)malloc((_tcslen(pszMess)+1) * sizeof(TCHAR));
		_tcscpy(m_pszMess, pszMess);
	}

	~CWaitDlg()
	{
		free(m_pszMess);
	}

	enum { IDD = IDD_WAITDLG };

BEGIN_MSG_MAP(CWaitDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// ハンドラのプロトタイプ:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		SetDlgItemText(IDC_WAITMESS, m_pszMess);
		return 1;  // システムにフォーカスを設定させます
	}

private:
	LPTSTR	m_pszMess;
};

#endif //__WAITDLG_H_
