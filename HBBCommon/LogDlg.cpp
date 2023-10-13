// LogDlg1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "HBBCommon.h"
#include "LogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern UINT g_nFuncItem[18];

/////////////////////////////////////////////////////////////////////////////
// CLogDlg ダイアログ


CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
	m_hImageList16 = NULL;
	m_hImageList32 = NULL;
	m_bMouseOver = FALSE;
	m_hOldCursor = NULL;
	m_hHyperCursor = NULL;
	m_pSelHistory = NULL;
	m_nLastSel = 0;
}

CLogDlg::~CLogDlg()
{
	if (m_hImageList16)
		ImageList_Destroy(m_hImageList16);
	if (m_hImageList32)
		ImageList_Destroy(m_hImageList32);
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogDlg)
	DDX_Control(pDX, IDC_NEWSLOG, m_listNews);
	//}}AFX_DATA_MAP
}

void CLogDlg::GetSelected(HOTBIZFUNC& nFunc, long& nObject)
{
	nFunc = m_nCurFunc;
	nObject = m_nCurObject;
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	//{{AFX_MSG_MAP(CLogDlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_SELALL, OnSelall)
	ON_LBN_DBLCLK(IDC_NEWSLOG, OnDblclkNewslog)
	ON_WM_COMPAREITEM()
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CLRALL, OnClrall)
	ON_LBN_SELCHANGE(IDC_NEWSLOG, OnSelchangeNewslog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogDlg メッセージ ハンドラ

BOOL CLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!AlreadyLoggedin()) {
		CWnd* pOK = GetDlgItem(IDOK);
		pOK->EnableWindow(FALSE);
	}

	vector<CHistory*>* histories = m_history.GetHistories();
	std::vector<CHistory*>::const_iterator it;
	for (it = histories->begin(); it < histories->end(); ++it) {
		m_listNews.AddString((LPCTSTR)(*it));
	}
	m_listNews.SetCurSel(0);

	TCHAR szWindowsDir[MAX_PATH*2];
	GetWindowsDirectory(szWindowsDir, MAX_PATH*2);
	_tcscat_s(szWindowsDir, sizeof(szWindowsDir), _T("\\Winhlp32.exe"));

	HMODULE hModule = LoadLibrary(szWindowsDir);
	if (hModule){
		m_hHyperCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
		FreeLibrary(hModule);
	}
	m_listNews.SetFocus();

	return FALSE; // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CLogDlg::OnDelete() 
{
	int i;
	int nCnt = 0;
	for (i = 0; i < m_listNews.GetCount(); ++i) {
		if (m_listNews.GetSel(i)) {
			++nCnt;
			break;
		}
	}
	if (nCnt && MessageBox(_T("選択された履歴を削除します。よろしいですか？"), _T("削除"), MB_ICONQUESTION|MB_YESNO) == IDYES) {
		BOOL bDel = FALSE;
		do {
			bDel = FALSE;
			for (i = 0; i < m_listNews.GetCount(); ++i) {
				if (m_listNews.GetSel(i)) {
					CHistory* pHis = (CHistory*)m_listNews.GetItemData(i);
					m_listNews.DeleteString(i);
					m_history.Remove(pHis);
					delete pHis;
					bDel = TRUE;
					break;
				}
			}
		} while (bDel);
		m_history.Write();
	}
}

void CLogDlg::OnSelall() 
{
	int nCrt = m_listNews.GetCount();
	for (int i = 0; i < nCrt; ++i)
		m_listNews.SetSel(i);
/*
	if (MessageBox(_T("履歴をすべて削除します。よろしいですか？"), _T("全削除"), MB_ICONQUESTION|MB_YESNO) == IDYES) {
		vector<CHistory*>* histories = m_history.GetHistories();
		for (int i = 0; i < histories->size(); ++i) {
			delete (*histories)[i];
		}
		histories->clear();
		m_history.Write();
		m_listNews.ResetContent();
	}
*/
}

void CLogDlg::OnDblclkNewslog() 
{
	if (AlreadyLoggedin()) {
		int nCur = m_listNews.GetCaretIndex();
		if (nCur != LB_ERR && nCur < m_listNews.GetCount()) {
			CHistory* pHis = (CHistory*)m_listNews.GetItemData(nCur);
			m_nCurFunc = pHis->m_nFuncID;
			m_nCurObject = pHis->m_nObjectID;
			EndDialog(IDOK);
		}
	}
}

int CLogDlg::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItem) 
{
	CHistory* it1 = (CHistory*)lpCompareItem->itemData1;
	CHistory* it2 = (CHistory*)lpCompareItem->itemData2;
	if (it1->m_tmTime > it2->m_tmTime)
		return -1;
	if (it1->m_tmTime < it2->m_tmTime)
		return 1;
	return 0;
}

void CLogDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	int nSizeX, nSizeY;
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
	GetIconSize(nSizeX, nSizeY);
	lpMeasureItemStruct->itemHeight = nSizeY + 4;
}

void CLogDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItem)
{
#define COLHEIGHT	20
	TCHAR szItem[256];
	LPTSTR pszSubject;
	TEXTMETRIC metrics;
	HICON hIcon;
	HBRUSH hBrush;
	COLORREF clrTextSave;
	COLORREF clrBkSave;
	CHistory* it = (CHistory*)lpDrawItem->itemData;
	int nSizeX, nSizeY;
	int nIconPos, nFuncPos, nTimePos, nSubjectPos;
	int nWid = lpDrawItem->rcItem.right - lpDrawItem->rcItem.left;
	int nHgh = lpDrawItem->rcItem.bottom - lpDrawItem->rcItem.top;
	int nCrt = m_listNews.GetCaretIndex();
	int nSel = m_listNews.GetSel(lpDrawItem->itemID);
//	BOOL bReverse = (lpDrawItem->itemAction & ODA_FOCUS) && (lpDrawItem->itemState & ODS_FOCUS);
	BOOL bReverse = (lpDrawItem->itemState & ODS_SELECTED) != 0;
	::GetTextMetrics(lpDrawItem->hDC, &metrics);

	GetIconSize(nSizeX, nSizeY);
	nIconPos = (COLHEIGHT-nSizeX)/2;
	nFuncPos = nIconPos+24;
	nTimePos = nFuncPos+100;
	nSubjectPos = nTimePos+40;

	if (bReverse) {
		hBrush = CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
		::FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, hBrush);
		clrTextSave = ::SetTextColor(lpDrawItem->hDC, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave = ::SetBkColor(lpDrawItem->hDC, ::GetSysColor(COLOR_HIGHLIGHT));
	} else {
		hBrush = CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
		::FillRect(lpDrawItem->hDC, &lpDrawItem->rcItem, hBrush);
		clrTextSave = ::SetTextColor(lpDrawItem->hDC, ::GetSysColor(COLOR_WINDOWTEXT));
		clrBkSave = ::SetBkColor(lpDrawItem->hDC, ::GetSysColor(COLOR_WINDOW));
	}

	if (it) {
		PICON_ITEM pItem = GetIconItem();
		hIcon = (HICON)LoadHotBizIcon(it->m_nFuncID, nSizeX, nSizeY);
		::DrawIconEx(lpDrawItem->hDC, nIconPos, lpDrawItem->rcItem.top + (nHgh - nSizeY) / 2, hIcon, nSizeX, nSizeY, 0, NULL, DI_NORMAL);
	//	::LoadString(AfxGetInstanceHandle(), g_nFuncItem[it->m_nFuncID], szItem, ARRAYSIZE(szItem));
		::TextOut(lpDrawItem->hDC, nFuncPos, lpDrawItem->rcItem.top + (nHgh - metrics.tmHeight) / 2, pItem[it->m_nFuncID].m_szName, _tcslen(pItem[it->m_nFuncID].m_szName));

		struct tm ptm;
		localtime_s(&ptm, &(it->m_tmTime));
		_stprintf_s(szItem, sizeof(szItem), _T("%02d:%02d"), ptm.tm_hour, ptm.tm_min);
		::TextOut(lpDrawItem->hDC, nTimePos, lpDrawItem->rcItem.top + (nHgh - metrics.tmHeight) / 2, szItem, _tcslen(szItem));

		pszSubject = (LPTSTR)malloc((it->m_szContents.length() + 1) * sizeof(TCHAR));
		ZeroMemory(pszSubject, (it->m_szContents.length() + 1) * sizeof(TCHAR));
#ifdef _UNICODE
		MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, it->m_szContents.c_str(), it->m_szContents.length(), pszSubject, it->m_szContents.length() + 1);
#else
		strcpy(pszSubject, it->m_szContents.c_str());
#endif
		for (int i = 0; i < (int)_tcslen(pszSubject); ++ i) {
			if (pszSubject[i] == _T('\r') || pszSubject[i] == _T('\n'))
				pszSubject[i] = _T(' ');
		}
		::TextOut(lpDrawItem->hDC, nSubjectPos, lpDrawItem->rcItem.top + (nHgh - metrics.tmHeight) / 2, pszSubject, _tcslen(pszSubject));
		free(pszSubject);
	}

	::DeleteObject(hBrush);
	::SetTextColor(lpDrawItem->hDC, clrTextSave);
	::SetBkColor(lpDrawItem->hDC, clrBkSave);

//	if (lpDrawItem->itemState & ODS_SELECTED)
	if (lpDrawItem->itemState & ODS_FOCUS)
		::DrawFocusRect(lpDrawItem->hDC, &lpDrawItem->rcItem);
//	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CLogDlg::OnOK() 
{
	int nCur = m_listNews.GetCaretIndex();
	if (nCur != LB_ERR && nCur < m_listNews.GetCount()) {
		CHistory* it = (CHistory*)m_listNews.GetItemData(nCur);
		m_nCurFunc = it->m_nFuncID;
		m_nCurObject = it->m_nObjectID;
		CDialog::OnOK();
	}
}

void CLogDlg::OnClrall() 
{
	int nCrt = m_listNews.GetCount();
	for (int i = 0; i < nCrt; ++i)
		m_listNews.SetSel(i, FALSE);
}

void CLogDlg::OnSelchangeNewslog() 
{
	SHORT nShift = GetKeyState(VK_LSHIFT) | GetKeyState(VK_RSHIFT);
	int nCur = m_listNews.GetCaretIndex();
	if (nShift & 0x8000) {
		int nLow = m_nLastSel;
		int nHgh = nCur;
		if (nLow > nHgh) {
			int n = nHgh;
			nHgh = nLow;
			nLow = n;
		}
		for (int i = nLow; i <= nHgh; ++i) {
			if (i != nCur) {
				int nSel = m_listNews.GetSel(i);
				m_listNews.SetSel(i, nSel == 0);
			}
		}
	}
	m_nLastSel = nCur;
	m_listNews.SetCaretIndex(nCur);
}
