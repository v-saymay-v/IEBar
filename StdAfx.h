// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���A
//            �܂��͎Q�Ɖ񐔂������A�����܂�ύX����Ȃ�
//            �v���W�F�N�g��p�̃C���N���[�h �t�@�C�����L�q���܂��B

#if !defined(AFX_STDAFX_H__F53ACB96_89CF_4312_84AD_FE6B2D6CF2C4__INCLUDED_)
#define AFX_STDAFX_H__F53ACB96_89CF_4312_84AD_FE6B2D6CF2C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4100)
#pragma warning(disable: 4511)
#pragma warning(disable: 4512)
#pragma warning(disable: 4530)
#pragma warning(disable: 4663)
#pragma warning(disable: 4786)

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#define HBBICONXS	16
#define HBBICONYS	16
#define HBBICONXB	24
#define HBBICONYB	24
#define HBBLOGOXS	60
#define HBBLOGOYS	16
#define HBBLOGOXB	72
#define HBBLOGOYB	24
//#define ARRAYSIZE(array) (sizeof(array) / sizeof(array[0]))
#define HOTBIZBARCLASS	"HotBizBar"

#include <time.h>
#include <atlbase.h>
#include <CommCtrl.h>
#include <WINUSER.H>

// CComModule �N���X����h�������N���X���g�p���āA�I�[�o�[���C�h����ꍇ
// _Module �̖��O�͕ύX���Ȃ��ł��������B
extern CComModule _Module;
#include <atlcom.h>
#include <atlwin.h>

// These are needed for IDeskBand
#include <shlguid.h>
#include <shlobj.h>

// needed for IInputObject and _bstr_t
#include <comdef.h>
#include <atlctl.h>

#include <vector>
#include <string>
#include <map>
using std::string;
using std::vector;
using std::map;

#ifndef EXPORT
	#define EXPORT
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STDAFX_H__F53ACB96_89CF_4312_84AD_FE6B2D6CF2C4__INCLUDED)
