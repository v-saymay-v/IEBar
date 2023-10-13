// HBBCommon.h : HBBCOMMON アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_HBBCOMMON_H__C678D3B9_DFF7_46E3_A5DC_B82C475EEF95__INCLUDED_)
#define AFX_HBBCOMMON_H__C678D3B9_DFF7_46E3_A5DC_B82C475EEF95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "hbbexport.h"
#include "hotbizconnection.h"

/////////////////////////////////////////////////////////////////////////////
// CHBBCommonApp
// このクラスの動作の定義に関しては HBBCommon.cpp ファイルを参照してください。
//

class CHBBCommonApp : public CWinApp
{
public:
	CHBBCommonApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHBBCommonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHBBCommonApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CHotBizConnection m_connection;
};

extern CLoginInfo g_loginInfo;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HBBCOMMON_H__C678D3B9_DFF7_46E3_A5DC_B82C475EEF95__INCLUDED_)
