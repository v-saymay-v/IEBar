#if !defined(AFX_LOGDLG1_H__4A74115D_9E32_4794_AB91_92AF19CEBB78__INCLUDED_)
#define AFX_LOGDLG1_H__4A74115D_9E32_4794_AB91_92AF19CEBB78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "hbhistory.h"

// LogDlg1.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CLogDlg ダイアログ

class CLogDlg : public CDialog
{
// コンストラクション
public:
	CLogDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ
	virtual ~CLogDlg();

// ダイアログ データ
	//{{AFX_DATA(CLogDlg)
	enum { IDD = IDD_LOGDLG };
	CListBox	m_listNews;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CLogDlg)
	afx_msg void OnDelete();
	afx_msg void OnSelall();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkNewslog();
	afx_msg int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void OnOK();
	afx_msg void OnClrall();
	afx_msg void OnSelchangeNewslog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void GetSelected(HOTBIZFUNC& nFunc, long& nObject);

private:
	CHbHistory	m_history;
	CHistory*	m_pSelHistory;
	HIMAGELIST	m_hImageList16;
	HIMAGELIST	m_hImageList32;
	BOOL		m_bMouseOver;
	HCURSOR		m_hOldCursor;
	HCURSOR		m_hHyperCursor;
	HOTBIZFUNC	m_nCurFunc;
	long		m_nCurObject;
	int			m_nLastSel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LOGDLG1_H__4A74115D_9E32_4794_AB91_92AF19CEBB78__INCLUDED_)
