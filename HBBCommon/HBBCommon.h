// HBBCommon.h : HBBCOMMON �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_HBBCOMMON_H__C678D3B9_DFF7_46E3_A5DC_B82C475EEF95__INCLUDED_)
#define AFX_HBBCOMMON_H__C678D3B9_DFF7_46E3_A5DC_B82C475EEF95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��
#include "hbbexport.h"
#include "hotbizconnection.h"

/////////////////////////////////////////////////////////////////////////////
// CHBBCommonApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� HBBCommon.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CHBBCommonApp : public CWinApp
{
public:
	CHBBCommonApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHBBCommonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHBBCommonApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CHotBizConnection m_connection;
};

extern CLoginInfo g_loginInfo;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HBBCOMMON_H__C678D3B9_DFF7_46E3_A5DC_B82C475EEF95__INCLUDED_)
