/*
//
// Copyright (C) 2002-2015 Jean-François DEL NERO
// Email : jeanfrancoisdelnero -at- free.fr
//
// This file is part of the WinDSP software.
//
// WinDSP may be used and distributed without restriction provided
// that this copyright statement is not removed from the file and that any
// derivative work contains the original copyright notice and the associated
// disclaimer.
//
// WinDSP is free software; you can redistribute it
// and/or modify  it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// WinDSP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WinDSP; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
*/
///////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
//-----------H----H--X----X-----CCCCC----22222----0000-----0000------11----------//
//----------H----H----X-X-----C--------------2---0----0---0----0--1--1-----------//
//---------HHHHHH-----X------C----------22222---0----0---0----0-----1------------//
//--------H----H----X--X----C----------2-------0----0---0----0-----1-------------//
//-------H----H---X-----X---CCCCC-----222222----0000-----0000----1111------------//
//-------------------------------------------------------------------------------//
//----------------------------------------------------- http://hxc2001.free.fr --//
///////////////////////////////////////////////////////////////////////////////////
// File:  dialog_config.cpp
// Contains: class Dialog_Config implementation
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "delay_module.h"

#include "delay_module_dialog.h"
#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"


#include "Dialog_Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Config dialog


CDialog_Config::CDialog_Config(CMainFrame * pParent2, Sound_IO * Gestio,CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Config::IDD, pParent)
{
	SoundIo=Gestio;
	pPar=pParent2;

	//{{AFX_DATA_INIT(CDialog_Config)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog_Config::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Config)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Config, CDialog)
	//{{AFX_MSG_MAP(CDialog_Config)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Config message handlers

void CDialog_Config::OnCheck1()
{
	if(pPar->m_wndView.sequenceur->GetStatusScheduler()==0)
	{
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_CHECKED, 0);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
		pPar->m_wndView.sequenceur->SetBufferSize(4096*2*2);
		pPar->Gestio.SetBufferSize(4096*2*2);
	}
	else
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
}

void CDialog_Config::OnCheck2()
{	if(pPar->m_wndView.sequenceur->GetStatusScheduler()==0)
	{
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_CHECKED, 0);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
		pPar->m_wndView.sequenceur->SetBufferSize(4096*2*2*2);
		pPar->Gestio.SetBufferSize(4096*2*2*2);
	}
	else
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
}

void CDialog_Config::OnCheck3()
{
	if(pPar->m_wndView.sequenceur->GetStatusScheduler()==0)
	{
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_CHECKED, 0);
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
		pPar->m_wndView.sequenceur->SetBufferSize(4096*2*2*4);
		pPar->Gestio.SetBufferSize(4096*2*2*4);
	}
	else
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);

}

void CDialog_Config::OnCheck4()
{
	if(pPar->m_wndView.sequenceur->GetStatusScheduler()==0)
	{
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_CHECKED, 0);
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
		pPar->m_wndView.sequenceur->SetBufferSize(4096*2*2*8);
		pPar->Gestio.SetBufferSize(4096*2*2*8);
	}
	else
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);

}

void CDialog_Config::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);

	switch(pPar->m_wndView.sequenceur->GetBufferSize())
	{
		case 2048*2*2:
			SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case 4096*2*2:
			SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_CHECKED, 0);
		break;

		case 4096*2*2*2:
			SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_CHECKED, 0);
		break;

		case 4096*2*2*4:
			SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_CHECKED, 0);
		break;

		case 4096*2*2*8:
			SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_CHECKED, 0);
		break;

		case 4096*2*2*16:
		break;
	};

}

void CDialog_Config::OnCheck5()
{
	if(pPar->m_wndView.sequenceur->GetStatusScheduler()==0)
	{
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_CHECKED, 0);
		pPar->m_wndView.sequenceur->SetBufferSize(2048*2*2);
		pPar->Gestio.SetBufferSize(2048*2*2);
	}
	else
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
}
