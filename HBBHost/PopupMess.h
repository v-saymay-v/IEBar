#if !defined(AFX_POPUPMESS_H__D33D03EF_1F1D_41FC_898E_0CB43207642C__INCLUDED_)
#define AFX_POPUPMESS_H__D33D03EF_1F1D_41FC_898E_0CB43207642C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupMess.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CPopupMess ウィンドウ

class CPopupMess : public CStatic
{
// コンストラクション
public:
	CPopupMess();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPopupMess)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CPopupMess();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CPopupMess)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	void InitMess();
	BOOL GetMouseOver(){return m_bMouseOver;}

private:
	BOOL	m_bInitialized;
	BOOL	m_bMouseOver;
	CFont	m_staticFont;
	CFont	m_oldFont;
	HCURSOR	m_hOldCursor;
	HCURSOR	m_hHyperCursor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_POPUPMESS_H__D33D03EF_1F1D_41FC_898E_0CB43207642C__INCLUDED_)
