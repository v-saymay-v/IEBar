// ProgressDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "hbbsignup.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg ダイアログ


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	m_bCanceled = FALSE;
	//{{AFX_DATA_INIT(CProgressDlg)
	m_szName = _T("");
	//}}AFX_DATA_INIT
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_ctlProgress);
	DDX_Text(pDX, IDC_NAME, m_szName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CProgressDlg::SetMax(UINT nMax)
{
	m_ctlProgress.SetRange(0, nMax);
}

void CProgressDlg::SetCur(LPCTSTR pszName, UINT nCur)
{
	m_szName = pszName;
	m_ctlProgress.SetPos(nCur);
	UpdateData(FALSE);

	MSG msg;
	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		DispatchMessage(&msg);
}

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg メッセージ ハンドラ

void CProgressDlg::OnCancel() 
{
	m_bCanceled = TRUE;
}
