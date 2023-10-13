#if !defined(AFX_PROGRESSDLG_H__2A343DEE_D1B3_4054_8AAC_B60FB97E387E__INCLUDED_)
#define AFX_PROGRESSDLG_H__2A343DEE_D1B3_4054_8AAC_B60FB97E387E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg ダイアログ

class CProgressDlg : public CDialog
{
// コンストラクション
public:
	CProgressDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESSDLG_DIALOG };
	CProgressCtrl	m_ctlProgress;
	CString	m_szName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CProgressDlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetMax(UINT nMax);
	void SetCur(LPCTSTR pszName, UINT nCur);
	BOOL Canceled(){return m_bCanceled;}

private:
	BOOL	m_bCanceled;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PROGRESSDLG_H__2A343DEE_D1B3_4054_8AAC_B60FB97E387E__INCLUDED_)
