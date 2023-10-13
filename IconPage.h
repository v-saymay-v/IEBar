// IconPage.h : CIconPage の宣言

#ifndef __ICONPAGE_H_
#define __ICONPAGE_H_

#include "resource.h"       // メイン シンボル

EXTERN_C const CLSID CLSID_IconPage;

/////////////////////////////////////////////////////////////////////////////
// CIconPage
class ATL_NO_VTABLE CIconPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIconPage, &CLSID_IconPage>,
	public IPropertyPageImpl<CIconPage>,
	public CDialogImpl<CIconPage>
{
private:
	ICON_ITEM m_stIconItem[ITEMTABLESIZE];

public:
	enum {IDD = IDD_ICONPAGE};

public:
	CIconPage();

DECLARE_REGISTRY_RESOURCEID(IDR_ICONPAGE)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIconPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CIconPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CIconPage>)
	COMMAND_HANDLER(IDC_DISPWHERE, BN_CLICKED, OnUIChange)
	COMMAND_HANDLER(IDC_DISPTC, BN_CLICKED, OnUIChange)
	COMMAND_HANDLER(IDC_BIGICON, BN_CLICKED, OnUIChange)
	COMMAND_HANDLER(IDC_SMALLICON, BN_CLICKED, OnUIChange)
	COMMAND_HANDLER(IDC_ADD, BN_CLICKED, OnAdd)
	COMMAND_HANDLER(IDC_DEL, BN_CLICKED, OnDel)
	COMMAND_HANDLER(IDC_UP, BN_CLICKED, OnUp)
	COMMAND_HANDLER(IDC_DOWN, BN_CLICKED, OnDown)
	MESSAGE_HANDLER(WM_MEASUREITEM, OnMeasureItem);
	MESSAGE_HANDLER(WM_COMPAREITEM, OnCompareItem);
	MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
END_MSG_MAP()
// ハンドラのプロトタイプ:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnUIChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnUp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDown(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCompareItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	STDMETHOD(Activate)(HWND hWndParent, LPCRECT prc, BOOL bModal);
	STDMETHOD(Deactivate)(void);
	STDMETHOD(Apply)(void);

private:
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	void UpdateHBBStatus(HWND hwnd);
	BOOL ApplyChange();
};

#endif //__ICONPAGE_H_
