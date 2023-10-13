// hbbuninstDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_HBBUNINSTDLG_H__EED2F93E_8B14_4E9D_B705_A8CAA8E27F0F__INCLUDED_)
#define AFX_HBBUNINSTDLG_H__EED2F93E_8B14_4E9D_B705_A8CAA8E27F0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstDlg �_�C�A���O

class CHbbuninstDlg : public CDialog
{
// �\�z
public:
	CHbbuninstDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CHbbuninstDlg)
	enum { IDD = IDD_HBBUNINST_DIALOG };
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHbbuninstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CHbbuninstDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void GetErrorMess(LPCTSTR pszMain, CString& szMess);
//	void AddToAutoRd(const char* pszDir, int& ndx);
	bool QuitAllBrowser();
	static BOOL CALLBACK EnumCountProc(HWND hwnd, LPARAM lParam);
	BOOL EnableShutdownPrivileges();
	BOOL DisableShutdownPrivileges();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HBBUNINSTDLG_H__EED2F93E_8B14_4E9D_B705_A8CAA8E27F0F__INCLUDED_)
