#if !defined(AFX_POPUPTITLE_H__4FA4DA88_1D34_4390_93A5_985FD367114C__INCLUDED_)
#define AFX_POPUPTITLE_H__4FA4DA88_1D34_4390_93A5_985FD367114C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupTitle.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPopupTitle �E�B���h�E

class CPopupTitle : public CStatic
{
// �R���X�g���N�V����
public:
	CPopupTitle();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPopupTitle)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CPopupTitle();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CPopupTitle)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_POPUPTITLE_H__4FA4DA88_1D34_4390_93A5_985FD367114C__INCLUDED_)
