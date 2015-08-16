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
// File:  mainfrm.cpp
// Contains: implementation of the CMainFrame class...
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <mmsystem.h>
#include <process.h>
#include "module.h"

#include "delay_module.h"
#include "input_module.h"
#include "output_module.h"
#include "t_module.h"
#include "mix_module.h"
#include "visu_module.h"
#include "filter_iir.h"
#include "filter_module.h"

#include "sound_io.h"

#include "scheduler.h"

#include "ChildView.h"
#include "MainFrm.h"

#include "WinDSP.h"
#include <dlgs.h>

#include "Dialog_Config.h"
#include "startdialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


SoundINPUT Sound_IO::EntreSon[4];
SoundOUTPUT Sound_IO::SortieSon[4];
int Sound_IO::BufferSoundSize=4096*2*2;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_BMODULE01, OnBmodule01)
	ON_COMMAND(ID_BMODULE02, OnBmodule02)
	ON_COMMAND(ID_BMODULE03, OnBmodule03)
	ON_COMMAND(ID_BMODULE04, OnBmodule04)
	ON_COMMAND(ID_BMODULE05, OnBmodule05)
	ON_COMMAND(ID_BMODULE06, OnBmodule06)
	ON_WM_TIMER()
	ON_COMMAND(ID_BMODULE08, OnBmodule08)
	ON_COMMAND(ID_BMODULE09, OnBmodule09)
	ON_COMMAND(ID_BMODULE10, OnBmodule10)
	ON_COMMAND(ID_BMODULE11, OnBmodule11)
	ON_COMMAND(ID_BMODULE12, OnBmodule12)
	ON_COMMAND(ID_BMODULE13, OnBmodule13)
	ON_COMMAND(ID_FICHIER_OUVRIR, OnFichierOuvrir)
	ON_COMMAND(ID_FICHIER_ENREGISTRER, OnFichierEnregistrer)
	ON_COMMAND(ID_BSTOP, OnBstop)
	ON_COMMAND(ID_BMODULE14, OnBmodule14)
	ON_COMMAND(ID_OPTIONS_ESSON, OnOptionsEsson)
	ON_COMMAND(BMODULE15, OnBMODULE15)
	ON_COMMAND(ID_BMIX, OnBmix)
	ON_WM_CLOSE()
	ON_COMMAND(ID_BMORSE, OnBmorse)
	ON_COMMAND(ID_BFB, OnBfb)
	ON_COMMAND(ID_BAGENT, OnBagent)
	//}}AFX_MSG_MAP

	ON_MESSAGE(MM_WIM_OPEN,Message_MM_WIM_OPEN)
	ON_MESSAGE(MM_WIM_CLOSE,Message_MM_WIM_CLOSE)
	ON_MESSAGE(MM_WIM_DATA,Message_MM_WIM_DATA)
	ON_MESSAGE(MM_WOM_OPEN,Message_MM_WOM_OPEN)
	ON_MESSAGE(MM_WOM_CLOSE,Message_MM_WOM_CLOSE)
	ON_MESSAGE(MM_WOM_DONE,Message_MM_WOM_DONE)



END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	for(int i=0; i<4;i++)
	{
		Sound_IO::EntreSon[i].hwd=0;
		Sound_IO::EntreSon[i].UpdateFlag=0;
		Sound_IO::SortieSon[i].hwd=0;

	}
	NeedRefresh=0;
}

CMainFrame::~CMainFrame()
{

}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//		évènements système :
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Message d'ouverture d'un canal d'entrée son
////////////////////////////////////////////////////////////
LRESULT CMainFrame::Message_MM_WIM_OPEN(WPARAM wPara, LPARAM lPara)
{
	Gestio.Start_Aq_Sound_Input((HWAVEIN)wPara,(LPWAVEHDR)lPara);
	return true;
}


////////////////////////////////////////////////////////////
// Message de fermeture d'un canal d'entrée son
////////////////////////////////////////////////////////////
LRESULT CMainFrame::Message_MM_WIM_CLOSE(WPARAM wPara, LPARAM lPara)
{
//MessageBox("Cmainframe","Close",MB_OK);
return true;
}

////////////////////////////////////////////////////////////
// Message donnée prete d'un canal d'entrée son
////////////////////////////////////////////////////////////
LRESULT CMainFrame::Message_MM_WIM_DATA(WPARAM wPara, LPARAM lPara)
{

	Gestio.Continue_Aq_Sound_Input((HWAVEIN)wPara,(LPWAVEHDR)lPara);
	m_wndView.ContinueSequence(1);
		return true;
}

////////////////////////////////////////////////////////////
// Message d'ouverture d'un canal de sortie son
////////////////////////////////////////////////////////////
LRESULT CMainFrame::Message_MM_WOM_OPEN(WPARAM wPara, LPARAM lPara)
{
	Gestio.Start_Pl_Sound_Output((HWAVEOUT)wPara,(LPWAVEHDR)lPara);
	return true;
}

////////////////////////////////////////////////////////////
// Message de fermeture d'un canal de sortie son
////////////////////////////////////////////////////////////
LRESULT CMainFrame::Message_MM_WOM_CLOSE(WPARAM wPara, LPARAM lPara)
{
	//MessageBox("WaveOut","Close",MB_OK);
	return true;
}

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Message son fini d'un canal de sortie son
////////////////////////////////////////////////////////////
LRESULT CMainFrame::Message_MM_WOM_DONE(WPARAM wPara, LPARAM lPara)
{

	m_wndView.ContinueSequence(2);

	Gestio.Continue_Pl_Sound_Output((HWAVEOUT)wPara,(LPWAVEHDR)lPara);
	return true;

}

////////////////////////////////////////////////////////////
// Message Timer (20 f/s)
////////////////////////////////////////////////////////////
void CMainFrame::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==0)
	{
		if(NeedRefresh==5)
		{
			m_wndView.Refresh();
			NeedRefresh=0;
		}
		NeedRefresh++;
		CFrameWnd::OnTimer(nIDEvent);
		m_wndView.ContinueSequence(4);
	}

	if(nIDEvent==1)
	{
	}
}

////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////

void CMainFrame::Refresh()
{
	NeedRefresh=1;
}


////////////////////////////////////////////////////////////
// Fonction d'initalisation de la fernetre
////////////////////////////////////////////////////////////
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	startdialog * sdiag;

	CompteurTemps=0;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetTimer(0,100,NULL);

	sdiag=new startdialog();
	sdiag->Create(IDD_DIALOGSTART);
	sdiag->ShowWindow(SW_SHOW);
	SetTimer(1,1000,NULL);
	sdiag->SetWindowPos(NULL,(GetSystemMetrics(SM_CXFULLSCREEN)/2)-160,(GetSystemMetrics(SM_CYFULLSCREEN)/2)-100,0,0,SWP_NOSIZE);
	sdiag->SetFocus();

return 0;
}

////////////////////////////////////////////////////////////
// Fonction d'initalisation de la fernetre
////////////////////////////////////////////////////////////
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/////////////////////////////////////////////////////////////////////////////
// Gestion des boutons ,menu , et co :
/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnBmodule01()
{
	m_wndView.SelectModule(1);
}

void CMainFrame::OnBmodule02()
{
	m_wndView.SelectModule(2);
}

void CMainFrame::OnBmodule03()
{
	m_wndView.SelectModule(3);
}

void CMainFrame::OnBmodule04()
{
	m_wndView.SelectModule(4);
}

void CMainFrame::OnBmodule05()
{
	m_wndView.SelectModule(5);
}

void CMainFrame::OnBmodule08()
{
	m_wndView.SelectModule(6);
}

void CMainFrame::OnBmodule09()
{
	m_wndView.SelectModule(7);
}

void CMainFrame::OnBmodule10()
{
	m_wndView.SelectModule(8);
}

void CMainFrame::OnBmodule11()
{
	m_wndView.SelectModule(9);
}

void CMainFrame::OnBmodule12()
{
	m_wndView.SelectModule(10);
}

void CMainFrame::OnBmodule13()
{
	m_wndView.SelectModule(11);
}

void CMainFrame::OnBmodule14()
{
	m_wndView.SelectModule(12);
}

void CMainFrame::OnBMODULE15()
{
	m_wndView.SelectModule(13);
}

void CMainFrame::OnBfb()
{
	m_wndView.SelectModule(15);
}

void CMainFrame::OnBmorse()
{
	m_wndView.SelectModule(14);
}

void CMainFrame::OnBagent()
{
	m_wndView.SelectModule(16);
}

void CMainFrame::OnBmodule06()
{
	m_wndView.StartSequence();
}

void CMainFrame::OnBstop()
{
	m_wndView.StopSequence();
}

void CMainFrame::OnBmix()
{
	ShellExecute(NULL, "open", "sndvol32.exe", NULL, NULL, SW_SHOWNORMAL);
}

void CMainFrame::OnFichierOuvrir()
{
	CFileDialog fileDlg( TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, "dsp Files (*.dsp)|*.dsp||", this);
	fileDlg.m_ofn.lpstrTitle = "Open a DSP file";

	if ( fileDlg.DoModal() == IDOK)
   		m_wndView.LoadDsp(fileDlg.GetPathName().GetBuffer(1));
}

void CMainFrame::OnFichierEnregistrer()
{
	CFileDialog fileDlg(FALSE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, "dsp Files (*.dsp)|*.dsp||", this);
	fileDlg.m_ofn.lpstrTitle = "Save a DSP file";

	if ( fileDlg.DoModal() == IDOK)
		m_wndView.SaveDsp(fileDlg.GetPathName().GetBuffer(1));
}

void CMainFrame::OnOptionsEsson()
{
	CDialog_Config * BoiteDialogue;
	BoiteDialogue=new CDialog_Config(this,&Gestio,this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_DIALOG_CONFIG);
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
}

void CMainFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_wndView.StopSequence();
	CFrameWnd::OnClose();
}
