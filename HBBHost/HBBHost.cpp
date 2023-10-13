// HBBHost.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "HBBHost.h"
#include "HBBCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// �B��� CHBBHostApp �I�u�W�F�N�g

CHBBHostApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHBBHostApp

BEGIN_MESSAGE_MAP(CHBBHostApp, CWinApp)
	//{{AFX_MSG_MAP(CHBBHostApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHBBHostApp �N���X�̍\�z

CHBBHostApp::CHBBHostApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

void CHBBHostApp::AddTrayIcon()
{
	CString szMess, szTip;
	UINT nIcon, nMess;
	if (AlreadyLoggedin()) {
		BOOL bRecvInfo;
		DWORD nInterval;
		DWORD nPopupTime;
		BOOL bPlaySound;
		TCHAR szFile[MAX_PATH];
		GetNewsInfo(bRecvInfo, nInterval, nPopupTime, bPlaySound, szFile);
		if (bRecvInfo) {
			nIcon = IDI_LOGGEDIN;
			nMess = IDS_LOGGEDIN;
		} else {
			nIcon = IDI_STOPPED;
			nMess = IDS_STOPPED;
		}
	} else {
		nIcon = IDR_MAINFRAME;
		nMess = IDS_NOTLOGGEDIN;
	}

	szTip.LoadString(AFX_IDS_APP_TITLE);
	AfxFormatString1(szMess, nMess, szTip);

	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_dlgMain.m_hWnd; 
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_MY_NOTIFYICON;
	nid.hIcon = (HICON)LoadImage(theApp.m_hInstance, MAKEINTRESOURCE(nIcon), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	lstrcpy(nid.szTip, szMess);
	Shell_NotifyIcon(NIM_ADD, &nid);
	if (nid.hIcon) 
		DestroyIcon(nid.hIcon); 
}

void CHBBHostApp::DelTrayIcon()
{
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_dlgMain.m_hWnd; 
	nid.uID = IDR_MAINFRAME;
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

/////////////////////////////////////////////////////////////////////////////
// CHBBHostApp �N���X�̏�����

BOOL CHBBHostApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDS_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CoInitialize(NULL);

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
//	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	m_pMainWnd = &m_dlgMain;
	m_dlgMain.Create(NULL);
	AddTrayIcon();

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return TRUE;
}

int CHBBHostApp::ExitInstance() 
{
	CoUninitialize();
	DelTrayIcon();
	m_dlgMain.DestroyWindow();
	return CWinApp::ExitInstance();
}
