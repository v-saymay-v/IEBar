#if !defined(AFX_PROGRESSDLG_H__2A343DEE_D1B3_4054_8AAC_B60FB97E387E__INCLUDED_)
#define AFX_PROGRESSDLG_H__2A343DEE_D1B3_4054_8AAC_B60FB97E387E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg �_�C�A���O

class CProgressDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CProgressDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESSDLG_DIALOG };
	CProgressCtrl	m_ctlProgress;
	CString	m_szName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CProgressDlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetMax(UINT nMax);
	void SetCur(LPCTSTR pszName, UINT nCur);
	BOOL Canceled(){return m_bCanceled;}

private:
	BOOL	m_bCanceled;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PROGRESSDLG_H__2A343DEE_D1B3_4054_8AAC_B60FB97E387E__INCLUDED_)
