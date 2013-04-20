/*!	@file
	@brief ���ʐݒ�_�C�A���O�{�b�N�X�A�u�^�u�o�[�v�y�[�W

	@author Norio Nakatani
	@date 2007.02.11 genta ���ʐݒ�ɐV�K�^�u��ǉ�
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2007, genta
	Copyright (C) 2001, MIK, genta
	Copyright (C) 2002, YAZAKI, MIK
	Copyright (C) 2003, KEITA
	Copyright (C) 2006, ryoji, fon
	Copyright (C) 2007, genta, ryoji
	Copyright (C) 2012, Moca
*/

#include "StdAfx.h"
#include "CPropCommon.h"
#include "sakura.hh"


static const DWORD p_helpids[] = {
	IDC_CHECK_DispTabWnd,			HIDC_CHECK_DispTabWnd,			//�^�u�E�C���h�E�\��	//@@@ 2003.05.31 MIK
	IDC_CHECK_SameTabWidth,			HIDC_CHECK_SameTabWidth,		//����	// 2006.08.06 ryoji
	IDC_CHECK_DispTabIcon,			HIDC_CHECK_DispTabIcon,			//�A�C�R���\��	// 2006.08.06 ryoji
	IDC_CHECK_SortTabList,			HIDC_CHECK_SortTabList,			//�^�u�ꗗ�\�[�g	// 2006.08.06 ryoji
	IDC_CHECK_DispTabWndMultiWin,	HIDC_CHECK_DispTabWndMultiWin,	//�^�u�E�C���h�E�\��	//@@@ 2003.05.31 MIK
	IDC_TABWND_CAPTION,				HIDC_TABWND_CAPTION,			//�^�u�E�C���h�E�L���v�V����	//@@@ 2003.06.15 MIK
	IDC_CHECK_RetainEmptyWindow,	HIDC_CHECK_RetainEmptyWindow,	//�Ō�̃t�@�C��������Ƃ�(����)�������c��	// 2007.02.13 ryoji
	IDC_CHECK_CloseOneWin,			HIDC_CHECK_CloseOneWin,			//�E�B���h�E�̕���{�^���͌��݂̃t�@�C���̂ݕ���	// 2007.02.13 ryoji
	IDC_CHECK_ChgWndByWheel,		HIDC_CHECK_ChgWndByWheel,		//�}�E�X�z�C�[���ŃE�B���h�E�؂�ւ� 2007.04.03 ryoji
	IDC_CHECK_OpenNewWin,			HIDC_CHECK_OpenNewWin,			//�O������N������Ƃ��͐V�����E�C���h�E�ŊJ�� 2009.06.19
	IDC_BUTTON_TABFONT,				HIDC_BUTTON_TABFONT,			//�^�u�t�H���g
	0, 0
};

//	From Here Jun. 2, 2001 genta
/*!
	@param hwndDlg[in] �_�C�A���O�{�b�N�X��Window Handle
	@param uMsg[in] ���b�Z�[�W
	@param wParam[in] �p�����[�^1
	@param lParam[in] �p�����[�^2
*/
INT_PTR CALLBACK CPropTab::DlgProc_page(
	HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return DlgProc( reinterpret_cast<pDispatchPage>(&CPropTab::DispatchEvent), hwndDlg, uMsg, wParam, lParam );
}
//	To Here Jun. 2, 2001 genta

/* ���b�Z�[�W���� */
INT_PTR CPropTab::DispatchEvent( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	NMHDR*		pNMHDR;
	NM_UPDOWN*	pMNUD;
	int			idCtrl;

	switch( uMsg ){

	case WM_INITDIALOG:
		/* �_�C�A���O�f�[�^�̐ݒ� Tab */
		SetData( hwndDlg );
		// Modified by KEITA for WIN64 2003.9.6
		::SetWindowLongPtr( hwndDlg, DWLP_USER, lParam );

		/* ���[�U�[���G�f�B�b�g �R���g���[���ɓ��͂ł���e�L�X�g�̒����𐧌����� */

		return TRUE;
	case WM_NOTIFY:
		idCtrl = (int)wParam;
		pNMHDR = (NMHDR*)lParam;
		pMNUD  = (NM_UPDOWN*)lParam;
//		switch( idCtrl ){
//		default:
			switch( pNMHDR->code ){
			case PSN_HELP:
				OnHelp( hwndDlg, IDD_PROP_TAB );
				return TRUE;
			case PSN_KILLACTIVE:
				/* �_�C�A���O�f�[�^�̎擾 Tab */
				GetData( hwndDlg );
				return TRUE;
//@@@ 2002.01.03 YAZAKI �Ō�ɕ\�����Ă����V�[�g�𐳂����o���Ă��Ȃ��o�O�C��
			case PSN_SETACTIVE:
				m_nPageNum = ID_PAGENUM_TAB;
				return TRUE;
			}
//			break;	/* default */
//		}
		break;	/* WM_NOTIFY */

	case WM_COMMAND:
		{
			WORD wNotifyCode = HIWORD(wParam);	/* �ʒm�R�[�h */
			WORD wID = LOWORD(wParam);	/* ����ID� �R���g���[��ID� �܂��̓A�N�Z�����[�^ID */
			if( wNotifyCode == BN_CLICKED ){
				switch( wID ){
				case IDC_CHECK_DispTabWnd:
				case IDC_CHECK_DispTabWndMultiWin:
					EnableTabPropInput( hwndDlg );
					break;
				case IDC_BUTTON_TABFONT:
					LOGFONT   lf = m_Common.m_sTabBar.m_lf;
					INT nPointSize = m_Common.m_sTabBar.m_nPointSize;

					if( MySelectFont( &lf, &nPointSize, hwndDlg, false) ){
						m_Common.m_sTabBar.m_lf = lf;
						m_Common.m_sTabBar.m_nPointSize = nPointSize;
					}
					break;
				}
			}
		}
		break;
//@@@ 2001.02.04 Start by MIK: Popup Help
	case WM_HELP:
		{
			HELPINFO *p = (HELPINFO *)lParam;
			MyWinHelp( (HWND)p->hItemHandle, m_pszHelpFile, HELP_WM_HELP, (ULONG_PTR)(LPVOID)p_helpids );	// 2006.10.10 ryoji MyWinHelp�ɕύX�ɕύX
		}
		return TRUE;
		/*NOTREACHED*/
		//break;
//@@@ 2001.02.04 End

//@@@ 2001.12.22 Start by MIK: Context Menu Help
	//Context Menu
	case WM_CONTEXTMENU:
		MyWinHelp( hwndDlg, m_pszHelpFile, HELP_CONTEXTMENU, (ULONG_PTR)(LPVOID)p_helpids );	// 2006.10.10 ryoji MyWinHelp�ɕύX�ɕύX
		return TRUE;
//@@@ 2001.12.22 End

	}
	return FALSE;
}


/* �_�C�A���O�f�[�^�̐ݒ� */
void CPropTab::SetData( HWND hwndDlg )
{

	//	Feb. 11, 2007 genta�u�E�B���h�E�v�V�[�g���ړ�
	::CheckDlgButton( hwndDlg, IDC_CHECK_DispTabWnd, m_Common.m_sTabBar.m_bDispTabWnd );	//@@@ 2003.05.31 MIK
	::CheckDlgButton( hwndDlg, IDC_CHECK_SameTabWidth, m_Common.m_sTabBar.m_bSameTabWidth );	//@@@ 2006.01.28 ryoji
	::CheckDlgButton( hwndDlg, IDC_CHECK_DispTabIcon, m_Common.m_sTabBar.m_bDispTabIcon );	//@@@ 2006.01.28 ryoji
	::CheckDlgButton( hwndDlg, IDC_CHECK_SortTabList, m_Common.m_sTabBar.m_bSortTabList );			//@@@ 2006.03.23 fon
	::CheckDlgButton( hwndDlg, IDC_CHECK_DispTabWndMultiWin, ! m_Common.m_sTabBar.m_bDispTabWndMultiWin ); //@@@ 2003.05.31 MIK
	::SendMessage( ::GetDlgItem( hwndDlg, IDC_TABWND_CAPTION ), EM_LIMITTEXT, (WPARAM)(_countof( m_Common.m_sTabBar.m_szTabWndCaption ) - 1 ), (LPARAM)0 );
	::SetDlgItemText( hwndDlg, IDC_TABWND_CAPTION, m_Common.m_sTabBar.m_szTabWndCaption );

	//	Feb. 11, 2007 genta �V�K�쐬
	::CheckDlgButton( hwndDlg, IDC_CHECK_RetainEmptyWindow, m_Common.m_sTabBar.m_bTab_RetainEmptyWin );
	::CheckDlgButton( hwndDlg, IDC_CHECK_CloseOneWin, m_Common.m_sTabBar.m_bTab_CloseOneWin );
	::CheckDlgButton( hwndDlg, IDC_CHECK_ChgWndByWheel, m_Common.m_sTabBar.m_bChgWndByWheel );	// 2007.04.03 ryoji
	::CheckDlgButton( hwndDlg, IDC_CHECK_OpenNewWin, m_Common.m_sTabBar.m_bNewWindow ); // 2009.06.17

	EnableTabPropInput(hwndDlg);
	return;
}

/* �_�C�A���O�f�[�^�̎擾 */
int CPropTab::GetData( HWND hwndDlg )
{
	//	Feb. 11, 2007 genta�u�E�B���h�E�v�V�[�g���ړ�
	m_Common.m_sTabBar.m_bDispTabWnd = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_DispTabWnd );
	m_Common.m_sTabBar.m_bSameTabWidth = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_SameTabWidth );		// 2006.01.28 ryoji
	m_Common.m_sTabBar.m_bDispTabIcon = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_DispTabIcon );		// 2006.01.28 ryoji
	m_Common.m_sTabBar.m_bSortTabList = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_SortTabList );		// 2006.03.23 fon
	m_Common.m_sTabBar.m_bDispTabWndMultiWin =
		( ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_DispTabWndMultiWin ) == BST_CHECKED ) ? FALSE : TRUE;
	::GetDlgItemText( hwndDlg, IDC_TABWND_CAPTION, m_Common.m_sTabBar.m_szTabWndCaption, _countof( m_Common.m_sTabBar.m_szTabWndCaption ) );

	//	Feb. 11, 2007 genta �V�K�쐬
	m_Common.m_sTabBar.m_bTab_RetainEmptyWin = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_RetainEmptyWindow );
	m_Common.m_sTabBar.m_bTab_CloseOneWin = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_CloseOneWin );
	m_Common.m_sTabBar.m_bChgWndByWheel = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_ChgWndByWheel );	// 2007.04.03 ryoji
	m_Common.m_sTabBar.m_bNewWindow = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_OpenNewWin );  // 2009.06.17

	return TRUE;
}

/*! �u�^�u�o�[�v�V�[�g��̃A�C�e���̗L���E������K�؂ɐݒ肷��

	@date 2007.02.12 genta �V�K�쐬
*/
void CPropTab::EnableTabPropInput(HWND hwndDlg)
{

	BOOL bTabWnd = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_DispTabWnd );
	BOOL bMultiWin = FALSE;
	if( bTabWnd ){
		bMultiWin = ::IsDlgButtonChecked( hwndDlg, IDC_CHECK_DispTabWndMultiWin );
	}
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_CHECK_DispTabWndMultiWin ), bTabWnd );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_CHECK_RetainEmptyWindow  ), bMultiWin );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_CHECK_CloseOneWin        ), bMultiWin );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_CHECK_OpenNewWin         ), bMultiWin );	// 2009.06.17
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_CHECK_DispTabIcon        ), bTabWnd );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_CHECK_SameTabWidth       ), bTabWnd );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_BUTTON_TABFONT           ), bTabWnd );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_CHECK_SortTabList        ), bTabWnd );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_TABWND_CAPTION           ), bTabWnd );
	::EnableWindow( ::GetDlgItem( hwndDlg, IDC_CHECK_ChgWndByWheel      ), bTabWnd );	// 2007.04.03 ryoji
}
/*[EOF]*/