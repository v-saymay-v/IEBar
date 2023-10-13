// PopupTitle.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "HBBHost.h"
#include "PopupTitle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupTitle

CPopupTitle::CPopupTitle()
{
}

CPopupTitle::~CPopupTitle()
{
}


BEGIN_MESSAGE_MAP(CPopupTitle, CStatic)
	//{{AFX_MSG_MAP(CPopupTitle)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupTitle メッセージ ハンドラ

BOOL CPopupTitle::OnEraseBkgnd(CDC* pDC) 
{
	CRect oRect;
	GetClientRect(&oRect);
	CBrush* br = CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH));
	pDC->FillRect(&oRect, br);
	return TRUE;	
//	return CStatic::OnEraseBkgnd(pDC);
}
