#include "stdafx.h"
#include "HBBHost.h"
#include "AboutDlg.h"

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_szCopyright = _T("");
	m_szVersion = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_COPYRIGHT, m_szCopyright);
	DDX_Text(pDX, IDC_VERSION, m_szVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	TCHAR szMyName[MAX_PATH];
	DWORD type;
	DWORD size;
	LPTSTR pszBuff;

	GetModuleFileName(NULL, szMyName, ARRAYSIZE(szMyName));
	size = GetFileVersionInfoSize(szMyName, &type);
	pszBuff = (LPTSTR)malloc(size);
	if (GetFileVersionInfo(szMyName, NULL, size, pszBuff)) {
		UINT uLen;
		VS_FIXEDFILEINFO* pApp;
		LPTSTR pszCopyright;
		if (VerQueryValue(pszBuff, _T("\\"), (LPVOID*)&pApp, &uLen)) {
			TCHAR szVer[128];
			_stprintf(szVer, _T("HotBizツールバー 新着情報 Ver.%d.%d.%d (build %d)"),
						HIWORD(pApp->dwProductVersionMS),
						LOWORD(pApp->dwProductVersionMS),
						HIWORD(pApp->dwProductVersionLS),
						LOWORD(pApp->dwProductVersionLS));
			m_szVersion = szVer;
		}
		if (VerQueryValue(pszBuff, _T("\\StringFileInfo\\041104b0\\LegalCopyright"), (LPVOID*)&pszCopyright, &uLen)) {
			m_szCopyright = pszCopyright;
		}
		UpdateData(FALSE);
	}
	free(pszBuff);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
