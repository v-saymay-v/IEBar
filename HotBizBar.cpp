//HotBizBar.cpp : Implementation of CHotBizBar

//***************************************************************************//
//                                                                           //
//  This file was created using the DeskBand ATL Object Wizard 2.0           //
//  By Erik Thompson © 2001                                                  //
//  Email questions and comments to erikt@radbytes.com						 //
//                                                                           //
//***************************************************************************//

#include "stdafx.h"
#include "HBIEBar.h"
#include "HotBizBar.h"

#ifndef DBIMF_USECHEVRON
#define DBIMF_USECHEVRON        0x0080
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotBizBar

CHotBizBar::CHotBizBar() : m_ReflectWnd(this)
{
ATLTRACE(_T("CHotBizBar constructor\r\n"));
	m_dwBandID = 0;
	m_dwViewMode = 0;
	m_bShow = FALSE;
	m_bFocus = FALSE;
	m_bEnterHelpMode = FALSE;
	m_hWndParent = NULL;
	m_pSite = NULL;
	m_pBrowser = NULL;
	m_pCmdTarget = NULL;
	m_nActualWidth = 200;
}

// IDeskBand
STDMETHODIMP CHotBizBar::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
{
ATLTRACE(_T("CHotBizBar GetBandInfo\r\n"));
	int nIconX;
	int nIconY;
	GetIconSize(nIconX, nIconY);
	m_dwBandID = dwBandID;
	m_dwViewMode = dwViewMode;
	if (pdbi) {
		if (pdbi->dwMask & DBIM_MINSIZE) {
			pdbi->ptMinSize.x = m_nMinWidth;
			pdbi->ptMinSize.y = nIconY + 6;
		}
		if (pdbi->dwMask & DBIM_MAXSIZE) {
			pdbi->ptMaxSize.x = 0; // ignored
			pdbi->ptMaxSize.y = nIconY + 6;	// width
		}
		if (pdbi->dwMask & DBIM_INTEGRAL) {
			pdbi->ptIntegral.x = 1; // ignored
			pdbi->ptIntegral.y = 1; // not sizeable
		}
		if (pdbi->dwMask & DBIM_ACTUAL) {
			pdbi->ptActual.x = m_nActualWidth;
			pdbi->ptActual.y = nIconY + 6;
		}
		if (pdbi->dwMask & DBIM_TITLE) {
		//	_tcscpy(pdbi->wszTitle, TITLE_CHotBizBar);
			pdbi->wszTitle[0] = 0;
		}
		if (pdbi->dwMask & DBIM_BKCOLOR) {
			//Use the default background color by removing this flag.
			pdbi->dwMask &= ~DBIM_BKCOLOR;
		}
		if (pdbi->dwMask & DBIM_MODEFLAGS) {
			pdbi->dwModeFlags = DBIMF_USECHEVRON | DBIMF_NORMAL;
		}
	}
	return S_OK;
}

// IOleWindow
STDMETHODIMP CHotBizBar::GetWindow(HWND* phwnd)
{
	HRESULT hr = S_OK;
	if (NULL == phwnd) {
		hr = E_INVALIDARG;
	} else {
		*phwnd = m_ReflectWnd.GetToolBar().m_hWnd;
	}
	return hr;
}

STDMETHODIMP CHotBizBar::ContextSensitiveHelp(BOOL fEnterMode)
{
	m_bEnterHelpMode = fEnterMode;
	return S_OK;
}

// IDockingWindow
STDMETHODIMP CHotBizBar::CloseDW(unsigned long dwReserved)
{
	ShowDW(FALSE);
	return S_OK;
}

STDMETHODIMP CHotBizBar::ResizeBorderDW(const RECT* prcBorder, IUnknown* punkToolbarSite, BOOL fReserved)
{
	// Not used by any band object.
	return E_NOTIMPL;
}

STDMETHODIMP CHotBizBar::ShowDW(BOOL fShow)
{
	m_bShow = fShow;
	m_ReflectWnd.GetToolBar().ShowWindow(m_bShow ? SW_SHOW : SW_HIDE);
	return S_OK;

}

BOOL CHotBizBar::RegisterAndCreateWindow()
{
	RECT rect;
	::GetClientRect(m_hWndParent, &rect);
	// The toolbar is the window that the host will be using so it is the window that is important.
	m_ReflectWnd.Create(m_hWndParent, rect, NULL, WS_CHILD);
	return m_ReflectWnd.GetToolBar().IsWindow();
}

// IObjectWithSite
STDMETHODIMP CHotBizBar::SetSite(IUnknown* pUnkSite)
{
	//If a site is being held, release it.
	if (m_pSite) {
		m_ReflectWnd.GetToolBar().SetBrowser(NULL);
		m_pSite->Release();
		m_pSite = NULL;
	}

	//If punkSite is not NULL, a new site is being set.
	if(pUnkSite) {
		//Get the parent window.
		IOleWindow  *pOleWindow = NULL;
		m_hWndParent = NULL;
		if (SUCCEEDED(pUnkSite->QueryInterface(IID_IOleWindow, (LPVOID*)&pOleWindow))) {
			pOleWindow->GetWindow(&m_hWndParent);
			pOleWindow->Release();
		}

		if (!::IsWindow(m_hWndParent))
			return E_FAIL;
		if (!RegisterAndCreateWindow())
			return E_FAIL;
		if (FAILED(pUnkSite->QueryInterface(IID_IInputObjectSite, (LPVOID*)&m_pSite)))
			return E_FAIL;

		IWebBrowser2* s_pFrameWB = NULL;
		HRESULT hr = pUnkSite->QueryInterface(IID_IOleCommandTarget, (LPVOID*)&m_pCmdTarget);
		if (SUCCEEDED(hr)) {
			IServiceProvider* pSP;
			hr = m_pCmdTarget->QueryInterface(IID_IServiceProvider, (LPVOID*)&pSP);
			if (SUCCEEDED(hr)) {
				hr = pSP->QueryService(SID_SWebBrowserApp, IID_IWebBrowser2, (LPVOID*)&s_pFrameWB);
				pSP->Release();
				if (FAILED(hr))
					return E_FAIL;
				m_ReflectWnd.GetToolBar().SetBrowser(s_pFrameWB);
				if (m_pBrowser)
					m_pBrowser->Release();
				m_pBrowser = s_pFrameWB;
				if (m_pBrowser)
					m_pBrowser->AddRef();
				s_pFrameWB->Release();
				m_ReflectWnd.GetToolBar().SetBandRebar();

				m_nMinWidth = m_ReflectWnd.GetToolBar().GetMinWidth();
				m_nActualWidth = m_ReflectWnd.GetToolBar().GetActualWidth();
				_variant_t vaIn((long)m_dwBandID);
				VARIANTARG vaOut;
				m_pCmdTarget->Exec(&CGID_DeskBand, DBID_BANDINFOCHANGED, OLECMDEXECOPT_DODEFAULT, &vaIn, &vaOut);
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CHotBizBar::GetSite(REFIID riid, void **ppvSite)
{
	*ppvSite = NULL;
	if(m_pSite) {
	   return m_pSite->QueryInterface(riid, ppvSite);
	}
	return E_FAIL;
}

/*
// IPersist
STDMETHODIMP CHotBizBar::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_HotBizBar;
	return S_OK;
}

// IPersistStream
STDMETHODIMP CHotBizBar::IsDirty(void)
{
	return S_FALSE;
}

STDMETHODIMP CHotBizBar::Load(IStream *pStm)
{
	return S_OK;
}

STDMETHODIMP CHotBizBar::Save(IStream *pStm, BOOL fClearDirty)
{
	return S_OK;
}

STDMETHODIMP CHotBizBar::GetSizeMax(ULARGE_INTEGER *pcbSize)
{
	return E_NOTIMPL;
}
*/

void CHotBizBar::FocusChange(BOOL bHaveFocus)
{
    m_bFocus = bHaveFocus;
	if (m_pSite) {
		IUnknown* pUnk = NULL;
		if (SUCCEEDED(QueryInterface(IID_IUnknown, (LPVOID*)&pUnk)) && pUnk != NULL) {
			m_pSite->OnFocusChangeIS(pUnk, bHaveFocus);
			pUnk->Release();
			pUnk = NULL;
		}
	}
}

STDMETHODIMP CHotBizBar::HasFocusIO(void)
{
	if (m_bFocus)
		return S_OK;
	return S_FALSE;
}


STDMETHODIMP CHotBizBar::TranslateAcceleratorIO(LPMSG lpMsg)
{
	// the only window that needs to translate messages is our edit box so forward them.
	return S_FALSE;
}

STDMETHODIMP CHotBizBar::UIActivateIO(BOOL fActivate, LPMSG lpMsg)
{
	if (fActivate)
		m_ReflectWnd.GetToolBar().SetFocus();
	return S_OK;
}
