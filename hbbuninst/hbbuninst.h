// hbbuninst.h : HBBUNINST アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_HBBUNINST_H__008897EA_2820_4575_9F1C_D484612A6AF4__INCLUDED_)
#define AFX_HBBUNINST_H__008897EA_2820_4575_9F1C_D484612A6AF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstApp:
// このクラスの動作の定義に関しては hbbuninst.cpp ファイルを参照してください。
//

class CHbbuninstApp : public CWinApp
{
public:
	CHbbuninstApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHbbuninstApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CHbbuninstApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HBBUNINST_H__008897EA_2820_4575_9F1C_D484612A6AF4__INCLUDED_)
