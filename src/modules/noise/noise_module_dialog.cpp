// Noise_module_dialog.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"
#include "noise_module.h"

#include "noise_module_dialog.h"
#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Noise_module_dialog dialog


Noise_module_dialog::Noise_module_dialog(noise_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Noise_module_dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(Noise_module_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Noise_module_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Noise_module_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Noise_module_dialog, CDialog)
	//{{AFX_MSG_MAP(Noise_module_dialog)
	ON_COMMAND(ID_BNOISE, OnBnoise)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, OnCustomdrawSlider3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Noise_module_dialog message handlers

void Noise_module_dialog::OnBnoise() 
{
	// TODO: Add your command handler code here
	
}

void Noise_module_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int pulselen;

	// TODO: Add your control notification handler code here
	
	pulselen = SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
	this->thimod->SetNoiseLen(pulselen);

	*pResult = 0;
}

void Noise_module_dialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here

	CDialog::OnShowWindow(bShow, nStatus);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 30000));	
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG(0, 30000));	
	SendDlgItemMessage(IDC_SLIDER3, TBM_SETRANGE, TRUE, MAKELONG(0, 3000));	
}

void Noise_module_dialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int repeatlen;
	
	repeatlen = SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);
	this->thimod->SetNoiseRepeat(repeatlen);
	
	*pResult = 0;
}

void Noise_module_dialog::OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int attack;
	
	attack = SendDlgItemMessage(IDC_SLIDER3,TBM_GETPOS, 0, 0);
	this->thimod->SetNoiseAttack(attack);
	
	*pResult = 0;
}
