#if !defined(AFX_POPUPMESS_H__D33D03EF_1F1D_41FC_898E_0CB43207642C__INCLUDED_)
#define AFX_POPUPMESS_H__D33D03EF_1F1D_41FC_898E_0CB43207642C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupMess.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPopupMess �E�B���h�E

class CPopupMess : public CStatic
{
// �R���X�g���N�V����
public:
	CPopupMess();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPopupMess)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CPopupMess();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_POPUPMESS_H__D33D03EF_1F1D_41FC_898E_0CB43207642C__INCLUDED_)
