// Mix_dialog.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"


#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"

#include "mix_module.h"

#include "mix_dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Mix_dialog dialog


Mix_dialog::Mix_dialog(mix_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Mix_dialog::IDD, pParent)
{
	this->thimod=thimod;

	//{{AFX_DATA_INIT(Mix_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Mix_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Mix_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Mix_dialog, CDialog)
	//{{AFX_MSG_MAP(Mix_dialog)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Mix_dialog message handlers

void Mix_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 2000));
	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE, (int)(thimod->GetBalance()+100)*10);
}

void Mix_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int result;

	result = SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);

	thimod->SetBalance((float)((result/10)-100));

	*pResult = 0;
}
