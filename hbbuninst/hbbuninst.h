// hbbuninst.h : HBBUNINST �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_HBBUNINST_H__008897EA_2820_4575_9F1C_D484612A6AF4__INCLUDED_)
#define AFX_HBBUNINST_H__008897EA_2820_4575_9F1C_D484612A6AF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� hbbuninst.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CHbbuninstApp : public CWinApp
{
public:
	CHbbuninstApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHbbuninstApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CHbbuninstApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HBBUNINST_H__008897EA_2820_4575_9F1C_D484612A6AF4__INCLUDED_)