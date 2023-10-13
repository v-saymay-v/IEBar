// hbbuninstDlg.h : ヘッダー ファイル
//

#if !defined(AFX_HBBUNINSTDLG_H__EED2F93E_8B14_4E9D_B705_A8CAA8E27F0F__INCLUDED_)
#define AFX_HBBUNINSTDLG_H__EED2F93E_8B14_4E9D_B705_A8CAA8E27F0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstDlg ダイアログ

class CHbbuninstDlg : public CDialog
{
// 構築
public:
	CHbbuninstDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CHbbuninstDlg)
	enum { IDD = IDD_HBBUNINST_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHbbuninstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CHbbuninstDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void GetErrorMess(LPCTSTR pszMain, CString& szMess);
//	void AddToAutoRd(const char* pszDir, int& ndx);
	bool QuitAllBrowser();
	static BOOL CALLBACK EnumCountProc(HWND hwnd, LPARAM lParam);
	BOOL EnableShutdownPrivileges();
	BOOL DisableShutdownPrivileges();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HBBUNINSTDLG_H__EED2F93E_8B14_4E9D_B705_A8CAA8E27F0F__INCLUDED_)
