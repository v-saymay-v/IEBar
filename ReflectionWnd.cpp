//ReflectionWnd.cpp : Implementation of CReflectionWnd

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson © 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#include "stdafx.h"
#include "ReflectionWnd.h"
#include "HBIEBar.h"
#include "HotBizBar.h"

const DWORD DEFAULT_TOOLBAR_STYLE = 
		WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WS_TABSTOP |			// Window styles
		TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_TRANSPARENT |			// Toolbar styles
		TBSTYLE_LIST | /*TBSTYLE_CUSTOMERASE | TBSTYLE_WRAPABLE |*/
		CCS_TOP | CCS_NODIVIDER /*| CCS_NOPARENTALIGN*/ | CCS_NORESIZE;		// Common Control styles

/////////////////////////////////////////////////////////////////////////////
// CReflectionWnd

CReflectionWnd::CReflectionWnd(CHotBizBar* pBar) : m_ToolbarWnd(pBar)
{
}

CReflectionWnd::~CReflectionWnd()
{
	if (IsWindow())
		DestroyWindow();
}

LRESULT CReflectionWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RECT rect;
	GetClientRect(&rect);
	m_ToolbarWnd.Create(m_hWnd, rect, NULL, DEFAULT_TOOLBAR_STYLE);
	return 0;
}

/*
LRESULT CReflectionWnd::OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}
*/
