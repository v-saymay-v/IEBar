// LoginDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "HBBHost.h"
#include "LoginDlg.h"
#include "HBBCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg ダイアログ


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	BOOL bAutoLogin;
	TCHAR szURL[256];
	TCHAR szUserName[21];
	TCHAR szPassword[21];

	GetLoginInfo(bAutoLogin, szURL, ARRAYSIZE(szURL), szUserName, ARRAYSIZE(szUserName), szPassword, ARRAYSIZE(szPassword));
	if (!bAutoLogin) {
		szUserName[0] = '\0';
		szPassword[0] = '\0';
	}

	//{{AFX_DATA_INIT(CLoginDlg)
	m_bAutoLogin = bAutoLogin;
	m_szURL = szURL;
	m_szUserName = szUserName;
	m_szPassword = szPassword;
	//}}AFX_DATA_INIT
	m_bLoginOK = FALSE;
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Check(pDX, IDC_AUTOLOGIN, m_bAutoLogin);
	DDX_Text(pDX, IDC_PASSWORD, m_szPassword);
	DDV_MaxChars(pDX, m_szPassword, 20);
	DDX_Text(pDX, IDC_URL, m_szURL);
	DDV_MaxChars(pDX, m_szURL, 255);
	DDX_Text(pDX, IDC_USERNAME, m_szUserName);
	DDV_MaxChars(pDX, m_szUserName, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg メッセージ ハンドラ

void CLoginDlg::OnOK() 
{
	UpdateData(TRUE);
	m_bLoginOK = LoginHotBiz(m_bAutoLogin, m_szURL, m_szUserName, m_szPassword);
	CDialog::OnOK();
}
