// Filter_dialog.cpp : implementation file
//

#include "resource.h"
#include "filter_iir.h"
#include "module.h"
#include "filter_module.h"
#include "filter_dialog.h"
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
// Filter_dialog dialog


Filter_dialog::Filter_dialog(Filter_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Filter_dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(Filter_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Filter_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Filter_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Filter_dialog, CDialog)
	//{{AFX_MSG_MAP(Filter_dialog)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, OnCustomdrawSlider3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, OnCustomdrawSlider6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER7, OnCustomdrawSlider7)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER8, OnCustomdrawSlider8)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER9, OnCustomdrawSlider9)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER10, OnCustomdrawSlider10)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER11, OnCustomdrawSlider11)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Filter_dialog message handlers

void Filter_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER3, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER11, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER5, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER6, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER7, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER8, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER9, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER10, TBM_SETRANGE, TRUE, MAKELONG(0, 100));

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(0)*100));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(1)*100));
	SendDlgItemMessage(IDC_SLIDER3, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(2)*100));
	SendDlgItemMessage(IDC_SLIDER5, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(3)*100));
	SendDlgItemMessage(IDC_SLIDER6, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(4)*100));
	SendDlgItemMessage(IDC_SLIDER7, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(5)*100));
	SendDlgItemMessage(IDC_SLIDER8, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(6)*100));
	SendDlgItemMessage(IDC_SLIDER9, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(7)*100));
	SendDlgItemMessage(IDC_SLIDER10, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(8)*100));
	SendDlgItemMessage(IDC_SLIDER11, TBM_SETPOS, TRUE,100-(int)(thimod->GetBand(9)*100));
}


void Filter_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	thimod->SetBand(0,(float)(100-SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0))/(float)100);
	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(1,(float)(100-SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(2,(float)(100-SendDlgItemMessage(IDC_SLIDER3,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(3,(float)(100-SendDlgItemMessage(IDC_SLIDER5,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(4,(float)(100-SendDlgItemMessage(IDC_SLIDER6,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider7(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(5,(float)(100-SendDlgItemMessage(IDC_SLIDER7,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider8(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(6,(float)(100-SendDlgItemMessage(IDC_SLIDER8,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider9(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(7,(float)(100-SendDlgItemMessage(IDC_SLIDER9,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider10(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(8,(float)(100-SendDlgItemMessage(IDC_SLIDER10,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}

void Filter_dialog::OnCustomdrawSlider11(NMHDR* pNMHDR, LRESULT* pResult)
{
	thimod->SetBand(9,(float)(100-SendDlgItemMessage(IDC_SLIDER11,TBM_GETPOS, 0, 0))/(float)100);

	*pResult = 0;
}
