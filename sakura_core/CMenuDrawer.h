/*!	@file
	@brief ���j���[�Ǘ����\��

	@author Norio Nakatani
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2000, genta
	Copyright (C) 2002, YAZAKI, MIK, aroka
	Copyright (C) 2003, MIK
	Copyright (C) 2005, aroka, genta
	Copyright (C) 2007, ryoji
	Copyright (C) 2010, syat

	This source code is designed for sakura editor.
	Please contact the copyright holder to use this code for other purpose.
*/


#ifndef _CMENUDRAWER_H_
#define _CMENUDRAWER_H_

#include "CShareData.h" // MAX_TOOLBARBUTTONS

class CMenuDrawer;

class CImageListMgr;// 2002/2/10 aroka

//#define MAX_MENUPOS	10
//	Jul. 2, 2005 genta : �}�N������������o�^����Ə���𒴂��Ă��܂��̂�
//	�����l��300���瑝�₷
#define MAX_MENUITEMS	400

//�c�[���o�[�̊g��	//@@@ 2002.06.15 MIK
#define TBSTYLE_COMBOBOX	((BYTE)0x40)	//�c�[���o�[�ɃR���{�{�b�N�X
#ifndef TBSTYLE_DROPDOWN	//IE3�ȏ�
	#define TBSTYLE_DROPDOWN	0x0008
#endif
#ifndef TB_SETEXTENDEDSTYLE	//IE4�ȏ�
	#define TB_SETEXTENDEDSTYLE     (WM_USER + 84)  // For TBSTYLE_EX_*
#endif
#ifndef TBSTYLE_EX_DRAWDDARROWS	//IE4�ȏ�
	#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
#endif

/*-----------------------------------------------------------------------
�N���X�̐錾
-----------------------------------------------------------------------*/
/*!
	@brief ���j���[�\�����Ǘ�

	@date 2002.2.17 YAZAKI CShareData�̃C���X�^���X�́ACProcess�ɂЂƂ���̂݁B
	@date 20050809 aroka �N���X�O������A�N�Z�X����Ȃ������o��private�ɂ����B
*/
class CMenuDrawer
{
public:
	/*
	||  Constructors
	*/
	CMenuDrawer();
	~CMenuDrawer();
	void Create( HINSTANCE, HWND, CImageListMgr* );


	/*
	||  Attributes & Operations
	*/
	void ResetContents( void );
	//void MyAppendMenu( HMENU , int , int , const char*, BOOL = TRUE );	/* ���j���[���ڂ�ǉ� */
	void MyAppendMenu( HMENU hMenu, int nFlag, int nFuncId, const TCHAR*, const TCHAR* pszKey, BOOL bAddKeyStr = TRUE, int nForceIconId = -1 );	/* ���j���[���ڂ�ǉ� */	//���C�ɓ���	//@@@ 2003.04.08 MIK
	int MeasureItem( int, int* );	/* ���j���[�A�C�e���̕`��T�C�Y���v�Z */
	void DrawItem( DRAWITEMSTRUCT* );	/* ���j���[�A�C�e���`�� */
	LRESULT OnMenuChar( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	int FindToolbarNoFromCommandId( int idCommand, bool bOnlyFunc = true )const; // �c�[���o�[Index�̎擾 // 20050809 aroka

	TBBUTTON getButton( int index ) const; // 20050809 aroka

	// �Â��R���p�C����static const int���T�|�[�g
	enum {
		TOOLBAR_BUTTON_F_TOOLBARWRAP = 384,	//�c�[���o�[�ܕԂ��A�C�R���i�_�~�[�j
	};

private:
	int Find( int nFuncID );
	const TCHAR* GetLabel( int nFuncID );
	TCHAR GetAccelCharFromLabel( const TCHAR* pszLabel );
	int GetIconId( int nIndex ){ return ( 0 <= nIndex && nIndex < m_nMyButtonNum )? m_tbMyButton[nIndex].iBitmap: -1; }	// 2007.11.02 ryoji �͈͊O�`�F�b�N

	int MyDrawText( int nMode, HDC hDC, LPCTSTR lpItemStr, LPRECT rc, UINT uFormat );

private:
	DLLSHAREDATA*	m_pShareData;

	HINSTANCE		m_hInstance;
	HWND			m_hWndOwner;
	int				(WINAPI *m_pfnDrawTextW)( HDC, LPCWSTR, int, LPRECT, UINT );

	int				m_nMenuItemNum;
//@@@ 2002.01.03 YAZAKI m_tbMyButton�Ȃǂ�CShareData����CMenuDrawer�ֈړ��������Ƃɂ��C���B
	TBBUTTON		m_tbMyButton[MAX_TOOLBAR_ICON_COUNT+1];	/* �c�[���o�[�̃{�^�� +1�̓Z�p���[�^ */
	int				m_nMyButtonNum;

	int				m_nMenuItemBitmapIdxArr[MAX_MENUITEMS];
	int				m_nMenuItemFuncArr[MAX_MENUITEMS];
	CMemory			m_cmemMenuItemStrArr[MAX_MENUITEMS];
	int				m_nMenuHeight;
	HFONT			m_hFontMenu;
	HFONT			m_hFontMenuUndelLine;

public:
	// 2010.01.30 syat �A�C�R���C���[�W���X�g��private->public
	//	Oct. 16, 2000 genta
	CImageListMgr	*m_pcIcons;	//	Image List

protected:
	/*
	||  �����w���p�֐�
	*/
	int GetData( void );	/* �_�C�A���O�f�[�^�̎擾 */

//@@@ 2002.01.03 YAZAKI m_tbMyButton�Ȃǂ�CShareData����CMenuDrawer�ֈړ��������Ƃɂ��C���B
	void SetTBBUTTONVal( TBBUTTON*, int, int, BYTE, BYTE, DWORD_PTR, INT_PTR ) const;	/* TBBUTTON�\���̂Ƀf�[�^���Z�b�g */
};



///////////////////////////////////////////////////////////////////////
#endif /* _CMENUDRAWER_H_ */


/*[EOF]*/