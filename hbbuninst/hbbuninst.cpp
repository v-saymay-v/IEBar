// hbbuninst.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "hbbuninst.h"
#include "hbbuninstDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstApp

BEGIN_MESSAGE_MAP(CHbbuninstApp, CWinApp)
	//{{AFX_MSG_MAP(CHbbuninstApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstApp �N���X�̍\�z

CHbbuninstApp::CHbbuninstApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CHbbuninstApp �I�u�W�F�N�g

CHbbuninstApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHbbuninstApp �N���X�̏�����

BOOL CHbbuninstApp::InitInstance()
{
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B
	CString szCmdLine = m_lpCmdLine;
	if (szCmdLine.IsEmpty()) {
		TCHAR szTmp[MAX_PATH];
		TCHAR szDir[MAX_PATH];
		TCHAR szSrc[MAX_PATH];
		TCHAR szDest[MAX_PATH];
		TCHAR szCmd[1024];
		LPTSTR pstr;
		GetTempPath(MAX_PATH, szDest);
		GetTempFileName(szDest, _T("hbb"), 0, szDest);
		GetModuleFileName(m_hInstance, szSrc, MAX_PATH);
		if (!CopyFile(szSrc, szDest, FALSE)) {
			MessageBox(NULL, _T("�A���C���X�g�[���Ɏ��s���܂����B"), _T("�G���["), MB_ICONSTOP|MB_OK);
			return FALSE;
		}

		pstr = _tcsrchr(szSrc, _T('\\'));
		++pstr;
		_tcsncpy_s(szTmp, sizeof(szTmp), szSrc, pstr-szSrc);
		szTmp[pstr-szSrc] = _T('\0');
		GetShortPathName(szTmp, szDir, sizeof(szDir));
		_stprintf_s(szCmd, sizeof(szCmd), "%s %s", szDest, szDir);

		PROCESS_INFORMATION processInformation;
		STARTUPINFO startupInfo;
		memset(&startupInfo, 0, sizeof(startupInfo));
		memset(&processInformation, 0, sizeof(processInformation));
		startupInfo.cb = sizeof(startupInfo);
		startupInfo.dwFlags = STARTF_USESHOWWINDOW;
		startupInfo.wShowWindow = SW_SHOW;
		if (!CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInformation)) {
			MessageBox(NULL, _T("�A���C���X�g�[���Ɏ��s���܂����B"), _T("�G���["), MB_ICONSTOP|MB_OK);
			return FALSE;
		}
		return FALSE;
	}

	CoInitialize(NULL);

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
//	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	CHbbuninstDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	CoUninitialize();

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}
