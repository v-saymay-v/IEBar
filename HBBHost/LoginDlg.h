#if !defined(AFX_LOGINDLG_H__26D0672A_C78A_41E8_A7C6_F5163BE0B882__INCLUDED_)
#define AFX_LOGINDLG_H__26D0672A_C78A_41E8_A7C6_F5163BE0B882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg ダイアログ

class CLoginDlg : public CDialog
{
// コンストラクション
public:
	CLoginDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGINDLG };
	BOOL	m_bAutoLogin;
	CString	m_szPassword;
	CString	m_szURL;
	CString	m_szUserName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CLoginDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL GetLoginResult(){return m_bLoginOK;}

private:
	BOOL	m_bLoginOK;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LOGINDLG_H__26D0672A_C78A_41E8_A7C6_F5163BE0B882__INCLUDED_)
