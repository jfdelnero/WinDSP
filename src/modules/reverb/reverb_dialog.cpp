// reverb_dialog.cpp : implementation file
//

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "reverb_module.h"

#include "reverb_dialog.h"
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
// reverb_dialog dialog


reverb_dialog::reverb_dialog(reverb_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(reverb_dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(reverb_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void reverb_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(reverb_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(reverb_dialog, CDialog)
	//{{AFX_MSG_MAP(reverb_dialog)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// reverb_dialog message handlers

void reverb_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0,100));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG(40,250));


	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE,thimod->GetCutoff());
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETPOS, TRUE,thimod->GetDelay());
}


void reverb_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	char test[50];
	int val1;

	val1=SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
	thimod->SetCutoff(val1);
	sprintf((char*)&test,"%d  ",val1);
	this->SetDlgItemText(IDC_EDIT1,test);
	*pResult = 0;
}

void reverb_dialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	int val1;
	char test[50];

	val1=SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);
	thimod->SetDelay(val1);

	sprintf((char*)&test,"%d  ",val1);
	this->SetDlgItemText(IDC_EDIT2,test);
	*pResult = 0;
}
