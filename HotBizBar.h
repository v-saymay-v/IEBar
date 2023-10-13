//HotBizBar.h : Declaration of the CHotBizBar

//***************************************************************************//
//                                                                           //
//  This file was created using the DeskBand ATL Object Wizard 2.0           //
//  By Erik Thompson © 2001                                                  //
//  Email questions and comments to erikt@radbytes.com						 //
//                                                                           //
//***************************************************************************//

#ifndef __HOTBIZBAR_H_
#define __HOTBIZBAR_H_

#include "resource.h"       // main symbols
#include "ReflectionWnd.h"

//
// These are needed for IDeskBand
//

#include <shlguid.h>
#include <shlobj.h>

#define EB_CLASS_NAME (TEXT("HotBizBarClass"))

/////////////////////////////////////////////////////////////////////////////
// CHotBizBar
class ATL_NO_VTABLE CHotBizBar : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHotBizBar, &CLSID_HotBizBar>,
	public IDeskBand,
	public IObjectWithSite,
//	public IPersistStream,
	public IInputObject, 
	public IDispatchImpl<IHotBizBar, &IID_IHotBizBar, &LIBID_HBIEBARLib>
{
public:
	CHotBizBar();

DECLARE_REGISTRY_RESOURCEID(IDR_HOTBIZBAR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_CATEGORY_MAP(CHotBizBar)
//	IMPLEMENTED_CATEGORY(CATID_InfoBand)
//	IMPLEMENTED_CATEGORY(CATID_CommBand)
	IMPLEMENTED_CATEGORY(CATID_DeskBand)
END_CATEGORY_MAP()

BEGIN_COM_MAP(CHotBizBar)
	COM_INTERFACE_ENTRY(IHotBizBar)
//	COM_INTERFACE_ENTRY(IInputObject)
	COM_INTERFACE_ENTRY(IOleWindow)
	COM_INTERFACE_ENTRY_IID(IID_IDockingWindow, IDockingWindow)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY_IID(IID_IDeskBand, IDeskBand)
//	COM_INTERFACE_ENTRY(IPersist)
//	COM_INTERFACE_ENTRY(IPersistStream)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDeskBand
public:
	STDMETHOD(GetBandInfo)(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi);

// IObjectWithSite
public:
	STDMETHOD(SetSite)(IUnknown* pUnkSite);
	STDMETHOD(GetSite)(REFIID riid, void **ppvSite);

// IOleWindow
public:
	STDMETHOD(GetWindow)(HWND* phwnd);
	STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);

// IDockingWindow
public:
	STDMETHOD(CloseDW)(unsigned long dwReserved);
	STDMETHOD(ResizeBorderDW)(const RECT* prcBorder, IUnknown* punkToolbarSite, BOOL fReserved);
	STDMETHOD(ShowDW)(BOOL fShow);

// IInputObject
public:
	STDMETHOD(HasFocusIO)(void);
	STDMETHOD(TranslateAcceleratorIO)(LPMSG lpMsg);
	STDMETHOD(UIActivateIO)(BOOL fActivate, LPMSG lpMsg);

// IPersist
public:
//	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
public:
//	STDMETHOD(IsDirty)(void);
//	STDMETHOD(Load)(IStream *pStm);
//	STDMETHOD(Save)(IStream *pStm, BOOL fClearDirty);
//	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IHotBizBar
public:
	void FocusChange(BOOL bHaveFocus);
	DWORD GetBandID(){return m_dwBandID;}
	IOleCommandTarget* GetCmdTarget(){return m_pCmdTarget;}
	void SetMinWidth(UINT nWid){m_nMinWidth = nWid;}
	void SetActualWidth(UINT nWid){m_nActualWidth = nWid;}

protected:
	BOOL RegisterAndCreateWindow();

protected:
	DWORD	m_dwBandID;
	DWORD	m_dwViewMode;
	BOOL	m_bShow;
	BOOL	m_bFocus;
	BOOL	m_bEnterHelpMode;
	HWND	m_hWndParent;
	UINT	m_nMinWidth;
	UINT	m_nActualWidth;
	IOleCommandTarget*	m_pCmdTarget;
	IInputObjectSite*	m_pSite;
	IWebBrowser2*		m_pBrowser;
	CReflectionWnd		m_ReflectWnd;
};

#endif //__HOTBIZBAR_H_
