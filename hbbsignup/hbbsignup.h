// hbbsignup.h : HBBSIGNUP �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_HBBSIGNUP_H__7045E856_7DD0_4904_89CB_CEB6AE92FA80__INCLUDED_)
#define AFX_HBBSIGNUP_H__7045E856_7DD0_4904_89CB_CEB6AE92FA80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CHbbsignupApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� hbbsignup.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CHbbsignupApp : public CWinApp
{
public:
	CHbbsignupApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHbbsignupApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CHbbsignupApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HBBSIGNUP_H__7045E856_7DD0_4904_89CB_CEB6AE92FA80__INCLUDED_)
