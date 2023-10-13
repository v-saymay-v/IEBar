// hbbsignupDlg.h : ヘッダー ファイル
//

#if !defined(AFX_HBBSIGNUPDLG_H__B336B65E_8B2B_4553_A32A_8C8ADA5C9020__INCLUDED_)
#define AFX_HBBSIGNUPDLG_H__B336B65E_8B2B_4553_A32A_8C8ADA5C9020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHbbsignupDlg ダイアログ

class CHbbsignupDlg : public CDialog
{
// 構築
public:
	CHbbsignupDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CHbbsignupDlg)
	enum { IDD = IDD_HBBSIGNUP_DIALOG };
	CString	m_szCert;
	UINT	m_nEnd;
	CString	m_szFolder;
	CString	m_szPrefix;
	CString	m_szServer;
	UINT	m_nStart;
	CString	m_szPassword;
	CString	m_szPvk;
	CString	m_szCab;
	CString	m_szIni;
	CString	m_szExplain;
	CString	m_szTimestamp;
	CString	m_szWeb;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHbbsignupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CHbbsignupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnReffolder();
	virtual void OnOK();
	afx_msg void OnRefspc();
	afx_msg void OnRefpvk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static void Pump();
	static BOOL CALLBACK EnumSearchWindow(HWND hwnd, LPARAM lParam);
	HWND SearchWindow(HWND hParent, LPCTSTR pszCaption, HWND hFather=NULL);
	BOOL PushButton(HWND hParent, UINT id);
	static BOOL CALLBACK EnumSearchStatic(HWND hwnd, LPARAM lParam);
	static BOOL CALLBACK EnumSearchControl(HWND hwnd, LPARAM lParam);
	HWND SearchControl(HWND hParent, LPCTSTR pszCaption, UINT id);

	BOOL StartWizard(LPCTSTR pszProg, LPCTSTR pszCabFile);
	BOOL StartProg(LPCTSTR pszProg, LPCTSTR pszParam);
	void StartPipe(LPCTSTR pszProg, LPCTSTR pszParam);

private:
	UINT	m_nEditID;
	TCHAR	m_szSearchCaption[MAX_PATH];
	TCHAR	m_szHotbizSpc[MAX_PATH];
	HWND	m_hParentWnd;
	HWND	m_hFoundWnd;
	HWND	m_hStaticWnd;

	HANDLE	hChildStdinRd, hChildStdinWr, hChildStdinWrDup, 
			hChildStdoutRd, hChildStdoutWr, hChildStdoutRdDup, 
			hInputFile, hSaveStdin, hSaveStdout; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HBBSIGNUPDLG_H__B336B65E_8B2B_4553_A32A_8C8ADA5C9020__INCLUDED_)
