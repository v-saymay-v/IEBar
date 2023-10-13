// HBBHost.h : HBBHOST �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_HBBHOST_H__DB7F4502_3227_49F1_8545_6C25C9A5FF67__INCLUDED_)
#define AFX_HBBHOST_H__DB7F4502_3227_49F1_8545_6C25C9A5FF67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��
#include "HBBHostDlg.h"

#ifndef TPM_VERPOSANIMATION
#define TPM_VERPOSANIMATION 0x1000L
#endif

/////////////////////////////////////////////////////////////////////////////
// CHBBHostApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� HBBHost.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CHBBHostApp : public CWinApp
{
public:
	CHBBHostApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHBBHostApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CHBBHostApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void AddTrayIcon();
	void DelTrayIcon();

private:
	CHBBHostDlg	m_dlgMain;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HBBHOST_H__DB7F4502_3227_49F1_8545_6C25C9A5FF67__INCLUDED_)
