#if !defined(AFX_POPUPDLG_H__D054EC65_9989_40D4_A240_FBD3640FF353__INCLUDED_)
#define AFX_POPUPDLG_H__D054EC65_9989_40D4_A240_FBD3640FF353__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupDlg.h : �w�b�_�[ �t�@�C��
//

#include "PopupMess.h"
#include "PopupTitle.h"
#include "HBBCommon.h"

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg �_�C�A���O

class CPopupDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CPopupDlg(int nIndex, UINT nFunc, long nObject, LPCTSTR pszTitle, LPCTSTR pszMess, HWND hLastFocus, CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPopupDlg)
	enum { IDD = IDD_POPUPDLG };
	CPopupTitle	m_stTitle;
	CPopupMess	m_stMess;
	CString		m_szMess;
	CString		m_szTitle;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPopupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPopupDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
//	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
	static BOOL LaunchHotBiz(HOTBIZFUNC nFunc, LPCTSTR pszOrg, IWebBrowser2* pBrowser);
	static BOOL DispFuncObj(HOTBIZFUNC nFunc, long nObject, IWebBrowser2* pBrowser);
	static bool WildcardCompareNoCase (LPCTSTR strWild, LPCTSTR strText);
	static IWebBrowser2* FindUsingTitle(LPCTSTR pszSearch);

public:
	BOOL Create(){return CDialog::Create(IDD_POPUPDLG);}
	static BOOL DispFuncObj(HOTBIZFUNC nFunc, long nObject);
	static BOOL NavigateBrowser(LPCTSTR pszURL);

protected:
	UINT	m_nStartX;
	UINT	m_nStartY;
	UINT	m_nFuncID;
	long	m_nObjectID;
	HWND	m_hLastFocus;
	int		m_size;
	BOOL	m_bChildHide;
	int		m_nIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_POPUPDLG_H__D054EC65_9989_40D4_A240_FBD3640FF353__INCLUDED_)
