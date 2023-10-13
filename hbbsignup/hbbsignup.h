// hbbsignup.h : HBBSIGNUP アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_HBBSIGNUP_H__7045E856_7DD0_4904_89CB_CEB6AE92FA80__INCLUDED_)
#define AFX_HBBSIGNUP_H__7045E856_7DD0_4904_89CB_CEB6AE92FA80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CHbbsignupApp:
// このクラスの動作の定義に関しては hbbsignup.cpp ファイルを参照してください。
//

class CHbbsignupApp : public CWinApp
{
public:
	CHbbsignupApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHbbsignupApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CHbbsignupApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HBBSIGNUP_H__7045E856_7DD0_4904_89CB_CEB6AE92FA80__INCLUDED_)
