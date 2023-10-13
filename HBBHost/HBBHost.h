// HBBHost.h : HBBHOST アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_HBBHOST_H__DB7F4502_3227_49F1_8545_6C25C9A5FF67__INCLUDED_)
#define AFX_HBBHOST_H__DB7F4502_3227_49F1_8545_6C25C9A5FF67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "HBBHostDlg.h"

#ifndef TPM_VERPOSANIMATION
#define TPM_VERPOSANIMATION 0x1000L
#endif

/////////////////////////////////////////////////////////////////////////////
// CHBBHostApp:
// このクラスの動作の定義に関しては HBBHost.cpp ファイルを参照してください。
//

class CHBBHostApp : public CWinApp
{
public:
	CHBBHostApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHBBHostApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CHBBHostApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void AddTrayIcon();
	void DelTrayIcon();

private:
	CHBBHostDlg	m_dlgMain;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HBBHOST_H__DB7F4502_3227_49F1_8545_6C25C9A5FF67__INCLUDED_)
