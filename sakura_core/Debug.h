/*!	@file
	@brief �f�o�b�O�p�֐�

	@author Norio Nakatani
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2007, kobake

	This source code is designed for sakura editor.
	Please contact the copyright holder to use this code for other purpose.
*/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <windows.h>
#include "global.h"

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                   ���b�Z�[�W�o�́F����                      //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
void DebugOutA( LPCSTR lpFmt, ...);
#ifdef _UNICODE
#define DebugOut DebugOutW
#else
#define DebugOut DebugOutA
#endif

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                 ���b�Z�[�W�{�b�N�X�F����                    //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //

//2007.10.02 kobake ���b�Z�[�W�{�b�N�X�̎g�p�̓f�o�b�O���Ɍ���Ȃ��̂ŁA�uDebug�`�v�Ƃ������O��p�~

//�e�L�X�g���`�@�\�t��MessageBox
int VMessageBoxF( HWND hwndOwner, UINT uType, LPCTSTR lpCaption, LPCTSTR lpText, va_list& v );
int MessageBoxF ( HWND hwndOwner, UINT uType, LPCTSTR lpCaption, LPCTSTR lpText, ... );

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                 �f�o�b�O�p���b�Z�[�W�o��                    //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
/*
	MYTRACE�̓����[�X���[�h�ł̓R���p�C���G���[�ƂȂ�悤�ɂ��Ă���̂ŁC
	MYTRACE���g���ꍇ�ɂ͕K��#ifdef _DEBUG �` #endif �ň͂ޕK�v������D
*/
#ifdef _DEBUG
	#define MYTRACE DebugOut
	#define MYTRACE_A DebugOutA
#else
	#define MYTRACE   Do_not_use_the_MYTRACE_function_if_release_mode
	#define MYTRACE_A Do_not_use_the_MYTRACE_A_function_if_release_mode
#endif

//#ifdef _DEBUG�`#endif�ň͂܂Ȃ��Ă��ǂ���
#ifdef _DEBUG
#define DBPRINT_A DebugOutA
#else
#if (defined(_MSC_VER) && 1400 <= _MSC_VER) || (defined(__GNUC__) && 3 <= __GNUC__ )
#define DBPRINT_A(...)
#else
// Not support C99 variable macro
inline void DBPRINT_A( ... ){}
#endif
#endif

#ifdef _UNICODE
#define DBPRINT DBPRINT_W
#else
#define DBPRINT DBPRINT_A
#endif

#define DEBUG_TRACE DBPRINT

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                ���[�U�p���b�Z�[�W�{�b�N�X                   //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//$$�����FDebug.h�ȊO�̒u���ꏊ���l����

//�f�o�b�O�p���b�Z�[�W�{�b�N�X
#define MYMESSAGEBOX MessageBoxF

//��ʂ̌x����
#define DefaultBeep()   MessageBeep(MB_OK)

//�G���[�F�ԊۂɁu�~�v[OK]
int ErrorMessage  (HWND hwnd, LPCTSTR format, ...);
//(TOPMOST)
int TopErrorMessage  (HWND hwnd, LPCTSTR format, ...);
#define ErrorBeep()     MessageBeep(MB_ICONSTOP)

//�x���F�O�p�Ɂu�I�v[OK]
int WarningMessage   (HWND hwnd, LPCTSTR format, ...);
int TopWarningMessage(HWND hwnd, LPCTSTR format, ...);
#define WarningBeep()   MessageBeep(MB_ICONEXCLAMATION)

//���F�ۂɁui�v[OK]
int InfoMessage   (HWND hwnd, LPCTSTR format, ...);
int TopInfoMessage(HWND hwnd, LPCTSTR format, ...);
#define InfoBeep()      MessageBeep(MB_ICONINFORMATION)

//�m�F�F�����o���́u�H�v [�͂�][������] �߂�l:IDYES,IDNO
int ConfirmMessage   (HWND hwnd, LPCTSTR format, ...);
int TopConfirmMessage(HWND hwnd, LPCTSTR format, ...);
#define ConfirmBeep()   MessageBeep(MB_ICONQUESTION)

//���̑����b�Z�[�W�\���p�{�b�N�X[OK]
int OkMessage  (HWND hwnd, LPCTSTR format, ...);
int TopOkMessage  (HWND hwnd, LPCTSTR format, ...);

//�^�C�v�w�胁�b�Z�[�W�\���p�{�b�N�X
int CustomMessage(HWND hwnd, UINT uType, LPCTSTR format, ...);
//(TOPMOST)
int TopCustomMessage(HWND hwnd, UINT uType, LPCTSTR format, ...);

//��҂ɋ����ė~�����G���[
int PleaseReportToAuthor(HWND hwnd, LPCTSTR format, ...);



// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
//                         �t���O��                            //
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- //
#ifdef _DEBUG
	//!	�ݒ肵�Ă���ꏊ�͂��邪�C�Q�Ƃ��Ă���ꏊ���Ȃ��ϐ�
	extern int gm_ProfileOutput;
#endif



///////////////////////////////////////////////////////////////////////
#endif /* _DEBUG_H_ */


/*[EOF]*/