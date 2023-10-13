#if !defined(AFX_LOGINDLG_H__26D0672A_C78A_41E8_A7C6_F5163BE0B882__INCLUDED_)
#define AFX_LOGINDLG_H__26D0672A_C78A_41E8_A7C6_F5163BE0B882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg �_�C�A���O

class CLoginDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CLoginDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGINDLG };
	BOOL	m_bAutoLogin;
	CString	m_szPassword;
	CString	m_szURL;
	CString	m_szUserName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CLoginDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL GetLoginResult(){return m_bLoginOK;}

private:
	BOOL	m_bLoginOK;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LOGINDLG_H__26D0672A_C78A_41E8_A7C6_F5163BE0B882__INCLUDED_)
