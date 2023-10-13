#if !defined(AFX_POPUPTITLE_H__4FA4DA88_1D34_4390_93A5_985FD367114C__INCLUDED_)
#define AFX_POPUPTITLE_H__4FA4DA88_1D34_4390_93A5_985FD367114C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupTitle.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CPopupTitle ウィンドウ

class CPopupTitle : public CStatic
{
// コンストラクション
public:
	CPopupTitle();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPopupTitle)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CPopupTitle();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CPopupTitle)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_POPUPTITLE_H__4FA4DA88_1D34_4390_93A5_985FD367114C__INCLUDED_)
