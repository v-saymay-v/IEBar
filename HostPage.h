// HostPage.h : CHostPage の宣言

#ifndef __HOSTPAGE_H_
#define __HOSTPAGE_H_

#include "resource.h"       // メイン シンボル

EXTERN_C const CLSID CLSID_HostPage;

/////////////////////////////////////////////////////////////////////////////
// CHostPage
class ATL_NO_VTABLE CHostPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHostPage, &CLSID_HostPage>,
	public IPropertyPageImpl<CHostPage>,
	public CDialogImpl<CHostPage>
{
public:
	CHostPage();

	enum {IDD = IDD_HOSTPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_HOSTPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHostPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CHostPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CHostPage>)
	COMMAND_HANDLER(IDC_STARTHOST, BN_CLICKED, OnStartHost)
END_MSG_MAP()
// ハンドラのプロトタイプ:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnStartHost(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	STDMETHOD(Activate)(HWND hWndParent, LPCRECT prc, BOOL bModal);
	STDMETHOD(Apply)(void);

private:
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	BOOL UpdateButton();
};

#endif //__HOSTPAGE_H_
