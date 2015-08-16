// detector_dialog.cpp : implementation file
//

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "detector_module.h"

#include "detector_dialog.h"
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
// detector_dialog dialog

detector_dialog::detector_dialog(Detector_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(detector_dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(detector_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void detector_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(detector_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(detector_dialog, CDialog)
	//{{AFX_MSG_MAP(detector_dialog)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER12, OnCustomdrawSlider12)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER13, OnCustomdrawSlider13)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// detector_dialog message handlers

void detector_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 32000));
	SendDlgItemMessage(IDC_SLIDER12, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER13, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG(0, 32000));
	SendDlgItemMessage(IDC_SLIDER5, TBM_SETRANGE, TRUE, MAKELONG(0, 32000));

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE,(int)thimod->GetConfig(0));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETPOS, TRUE,(int)thimod->GetConfig(1)/2+16000);
	SendDlgItemMessage(IDC_SLIDER5, TBM_SETPOS, TRUE,(int)thimod->GetConfig(2)/2+16000);
	SendDlgItemMessage(IDC_SLIDER12, TBM_SETPOS, TRUE,(int)thimod->GetConfig(3));
	SendDlgItemMessage(IDC_SLIDER13, TBM_SETPOS, TRUE,(int)thimod->GetConfig(4));
}

void detector_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int val1;
	val1=SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
	thimod->SetConfig(0,val1);

}

void detector_dialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	int val1;
	val1=SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);
	thimod->SetConfig(1,(val1-16000)*2);
	*pResult = 0;
}

void detector_dialog::OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult)
{
	int val1;
	val1=SendDlgItemMessage(IDC_SLIDER5,TBM_GETPOS, 0, 0);
	thimod->SetConfig(2,(val1-16000)*2);
	*pResult = 0;
}

void detector_dialog::OnCustomdrawSlider12(NMHDR* pNMHDR, LRESULT* pResult)
{
	int val1;
	val1=SendDlgItemMessage(IDC_SLIDER12,TBM_GETPOS, 0, 0);
	thimod->SetConfig(3,val1);
}

void detector_dialog::OnCustomdrawSlider13(NMHDR* pNMHDR, LRESULT* pResult)
{
	int val1;
	val1=SendDlgItemMessage(IDC_SLIDER13,TBM_GETPOS, 0, 0);
	thimod->SetConfig(4,val1);
}
