#if !defined(AFX_POPUPDLG_H__D054EC65_9989_40D4_A240_FBD3640FF353__INCLUDED_)
#define AFX_POPUPDLG_H__D054EC65_9989_40D4_A240_FBD3640FF353__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupDlg.h : ヘッダー ファイル
//

#include "PopupMess.h"
#include "PopupTitle.h"
#include "HBBCommon.h"

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg ダイアログ

class CPopupDlg : public CDialog
{
// コンストラクション
public:
	CPopupDlg(int nIndex, UINT nFunc, long nObject, LPCTSTR pszTitle, LPCTSTR pszMess, HWND hLastFocus, CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CPopupDlg)
	enum { IDD = IDD_POPUPDLG };
	CPopupTitle	m_stTitle;
	CPopupMess	m_stMess;
	CString		m_szMess;
	CString		m_szTitle;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPopupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CPopupDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
//	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	static BOOL LaunchHotBiz(HOTBIZFUNC nFunc, LPCTSTR pszOrg, IWebBrowser2* pBrowser);
	static BOOL DispFuncObj(HOTBIZFUNC nFunc, long nObject, IWebBrowser2* pBrowser);
	static bool WildcardCompareNoCase (LPCTSTR strWild, LPCTSTR strText);
	static IWebBrowser2* FindUsingTitle(LPCTSTR pszSearch);

public:
	BOOL Create(){return CDialog::Create(IDD_POPUPDLG);}
	static BOOL DispFuncObj(HOTBIZFUNC nFunc, long nObject);
	static BOOL NavigateBrowser(LPCTSTR pszURL);

protected:
	UINT	m_nStartX;
	UINT	m_nStartY;
	UINT	m_nFuncID;
	long	m_nObjectID;
	HWND	m_hLastFocus;
	int		m_size;
	BOOL	m_bChildHide;
	int		m_nIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_POPUPDLG_H__D054EC65_9989_40D4_A240_FBD3640FF353__INCLUDED_)
