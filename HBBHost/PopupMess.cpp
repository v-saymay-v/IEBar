// PopupMess.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "HBBHost.h"
#include "PopupMess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef SetClassLongPtr
#define SetClassLongPtr	SetClassLong
#endif
#ifndef GetClassLongPtr
#define GetClassLongPtr	GetClassLong
#endif
#ifndef GCLP_HCURSOR
#define GCLP_HCURSOR	(-12)
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupMess

CPopupMess::CPopupMess()
{
	m_bInitialized = FALSE;
	m_bMouseOver = FALSE;
	m_hOldCursor = NULL;
	m_hHyperCursor = NULL;
}

CPopupMess::~CPopupMess()
{
	if (m_hHyperCursor)
		::DestroyCursor(m_hHyperCursor);
}


BEGIN_MESSAGE_MAP(CPopupMess, CStatic)
	//{{AFX_MSG_MAP(CPopupMess)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupMess メッセージ ハンドラ

BOOL CPopupMess::OnEraseBkgnd(CDC* pDC) 
{
	CRect oRect;
	GetClientRect(&oRect);
	CBrush* br = CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH));
	pDC->FillRect(&oRect, br);
	return TRUE;	
//	return CStatic::OnEraseBkgnd(pDC);
}

void CPopupMess::OnMouseMove(UINT nFlags, CPoint point) 
{
	CStatic::OnMouseMove(nFlags, point);
	if (m_bMouseOver) {
		CRect oRect;
		GetClientRect(&oRect);
		//check if the mouse is in the rect
		if (!PtInRect(&oRect, point)) {
			m_bMouseOver = FALSE;
			if (m_bInitialized)
				SetFont(&m_oldFont);
			//Release the Mouse capture previously take
			::SetCursor(m_hOldCursor);
			::SetClassLongPtr(m_hWnd, GCLP_HCURSOR, (LONG)m_hOldCursor);
			ReleaseCapture();
		}
	} else {
		m_bMouseOver = TRUE;
		SetCapture();
		m_hOldCursor = (HCURSOR)::GetClassLongPtr(m_hWnd, GCLP_HCURSOR);
		::SetClassLongPtr(m_hWnd, GCLP_HCURSOR, NULL);
		::SetCursor(m_hHyperCursor);
		if (m_bInitialized)
			SetFont(&m_staticFont);
	}
}

void CPopupMess::InitMess() 
{
	LOGFONT sLogFont;
	CFont* pFont = GetFont();
	pFont->GetLogFont(&sLogFont);
	m_oldFont.CreateFontIndirect(&sLogFont);
	sLogFont.lfUnderline = true;
	m_staticFont.CreateFontIndirect(&sLogFont);
	
	TCHAR szWindowsDir[MAX_PATH*2];
	GetWindowsDirectory(szWindowsDir, MAX_PATH*2);
	_tcscat_s(szWindowsDir, sizeof(szWindowsDir), _T("\\Winhlp32.exe"));
	HMODULE hModule = LoadLibrary(szWindowsDir);
	if (hModule){
		m_hHyperCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
		FreeLibrary(hModule);
	}
	m_bInitialized = TRUE;
}

BOOL CPopupMess::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	return CStatic::PreCreateWindow(cs);
}
