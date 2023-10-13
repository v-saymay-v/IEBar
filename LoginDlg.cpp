// LoginDlg.cpp : CLoginDlg のインプリメンテーション
#include "stdafx.h"
#include "LoginDlg.h"
#include "hbbexport.h"

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg

CLoginDlg::CLoginDlg()
{
}

CLoginDlg::~CLoginDlg()
{
}

LRESULT CLoginDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	GetLoginInfo(m_bAutoSave, m_szURL, ARRAYSIZE(m_szURL), m_szUserName, ARRAYSIZE(m_szUserName), m_szPassword, ARRAYSIZE(m_szPassword));
	SetDlgItemText(IDC_URL, m_szURL);
	if (m_bAutoSave) {
		SetDlgItemText(IDC_USERNAME, m_szUserName);
		SetDlgItemText(IDC_PASSWORD, m_szPassword);
	}
	CheckDlgButton(IDC_AUTOLOGIN, m_bAutoSave ? BST_CHECKED : BST_UNCHECKED);
	return 1;  // システムにフォーカスを設定させます
}

LRESULT CLoginDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	GetDlgItemText(IDC_URL, m_szURL, ARRAYSIZE(m_szURL));
	GetDlgItemText(IDC_USERNAME, m_szUserName, ARRAYSIZE(m_szUserName));
	GetDlgItemText(IDC_PASSWORD, m_szPassword, ARRAYSIZE(m_szPassword));
	m_bAutoSave = (IsDlgButtonChecked(IDC_AUTOLOGIN) == BST_CHECKED);
//	if (!m_szPassword[0] || !m_szUserName[0]) {
//		MessageBox(_T("ログインに失敗しました。ユーザー名とパスワードを確認してください。"), _T("エラー"), MB_ICONSTOP|MB_OK);
//		return 0;
//	}
	EndDialog(wID);
	return 0;
}

LRESULT CLoginDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

void CLoginDlg::GetResult(LPTSTR pszURL, LPTSTR pszUserName, LPTSTR pszPassword, BOOL& bAutoSave)
{
	_tcscpy_s(pszURL, _tcslen(m_szURL), m_szURL);
	_tcscpy_s(pszUserName, _tcslen(m_szUserName), m_szUserName);
	_tcscpy_s(pszPassword, _tcslen(m_szPassword), m_szPassword);
	bAutoSave = m_bAutoSave;
}
