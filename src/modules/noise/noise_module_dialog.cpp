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
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER18, OnCustomdrawSliderPulseLenRand)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, OnCustomdrawSliderPulsePerRand)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER15, OnCustomdrawSliderMin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER16, OnCustomdrawSliderMax)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER17, OnCustomdrawSliderNoPulseValue)
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
	thimod->SetNoiseLen(pulselen);

	*pResult = 0;
}

void Noise_module_dialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 0x7FFF));	
	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE,thimod->GetNoiseLen());

	SendDlgItemMessage(IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG(0, 0x7FFF));	
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETPOS, TRUE,thimod->GetNoiseRepeat());

	SendDlgItemMessage(IDC_SLIDER3, TBM_SETRANGE, TRUE, MAKELONG(0, 0x7FFF));	
	SendDlgItemMessage(IDC_SLIDER3, TBM_SETPOS, TRUE,thimod->GetNoiseAttack()/2);

	SendDlgItemMessage(IDC_SLIDER17, TBM_SETRANGE, TRUE, MAKELONG(0, 0x7FFF));	
	SendDlgItemMessage(IDC_SLIDER17, TBM_SETPOS, TRUE,(thimod->GetNoiseNoPulseLevel()/2)+(0x7FFF/2));

	SendDlgItemMessage(IDC_SLIDER18, TBM_SETRANGE, TRUE, MAKELONG(0, 0x7FFF));	
	SendDlgItemMessage(IDC_SLIDER18, TBM_SETPOS, TRUE,thimod->GetNoisePulseLenRand());

	SendDlgItemMessage(IDC_SLIDER4, TBM_SETRANGE, TRUE, MAKELONG(0, 0x7FFF));	
	SendDlgItemMessage(IDC_SLIDER4, TBM_SETPOS, TRUE,thimod->GetNoisePulsePeriodRand());

	SendDlgItemMessage(IDC_SLIDER15, TBM_SETRANGE, TRUE, MAKELONG(0, 0x7FFF));	
	SendDlgItemMessage(IDC_SLIDER15, TBM_SETPOS, TRUE,(thimod->GetNoiseMinLevel()/2)+(0x7FFF/2));

	SendDlgItemMessage(IDC_SLIDER16, TBM_SETRANGE, TRUE, MAKELONG(0, 0x7FFF));	
	SendDlgItemMessage(IDC_SLIDER16, TBM_SETPOS, TRUE,(thimod->GetNoiseMaxLevel()/2)+(0x7FFF/2));

}

void Noise_module_dialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int repeatlen;
	
	repeatlen = SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);
	thimod->SetNoiseRepeat(repeatlen);
	
	*pResult = 0;
}

void Noise_module_dialog::OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int attack;
	
	attack = SendDlgItemMessage(IDC_SLIDER3,TBM_GETPOS, 0, 0);
	thimod->SetNoiseAttack(attack*2);
	
	*pResult = 0;
}

void Noise_module_dialog::OnCustomdrawSliderPulseLenRand(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int len;

	len = SendDlgItemMessage(IDC_SLIDER18,TBM_GETPOS, 0, 0);
	thimod->SetNoisePulseLenRand(len);
	*pResult = 0;
}

void Noise_module_dialog::OnCustomdrawSliderPulsePerRand(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int len;

	len = SendDlgItemMessage(IDC_SLIDER4,TBM_GETPOS, 0, 0);
	thimod->SetNoisePulsePeriodRand(len);
	
	*pResult = 0;
}

void Noise_module_dialog::OnCustomdrawSliderMin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int level;

	level = SendDlgItemMessage(IDC_SLIDER15,TBM_GETPOS, 0, 0)*2;
	thimod->SetNoiseMinLevel( level - 32767 );
	*pResult = 0;
}

void Noise_module_dialog::OnCustomdrawSliderMax(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int level;

	level = SendDlgItemMessage(IDC_SLIDER16,TBM_GETPOS, 0, 0)*2;
	thimod->SetNoiseMaxLevel( level - 32767 );
	*pResult = 0;
}

void Noise_module_dialog::OnCustomdrawSliderNoPulseValue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int level;

	level = SendDlgItemMessage(IDC_SLIDER17,TBM_GETPOS, 0, 0)*2;
	thimod->SetNoiseNoPulseLevel( level - 32767 );
	*pResult = 0;
}
