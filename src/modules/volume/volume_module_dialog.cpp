// Volume_module_dialog.cpp : implementation file
//

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "volume_module.h"

#include "volume_module_dialog.h"
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
// Volume_module_dialog dialog


Volume_module_dialog::Volume_module_dialog(Volume_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Volume_module_dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(Volume_module_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Volume_module_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Volume_module_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Volume_module_dialog, CDialog)
	//{{AFX_MSG_MAP(Volume_module_dialog)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, OnReleasedcaptureSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Volume_module_dialog message handlers

void Volume_module_dialog::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void Volume_module_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	char test[50];
	int vol1,vol2;

	vol1= SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
	vol2= SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);

	if(thimod->GetVolume(0)<50) thimod->SetVolume(-(vol1-40),0);
	if(thimod->GetVolume(1)<50) thimod->SetVolume(-(vol2-40),1);

	sprintf((char*)&test,"%d Db ",-(vol1-40));
	this->SetDlgItemText(IDC_EDIT1,test);

	sprintf((char*)&test,"%d Db ",-(vol2-40));
	this->SetDlgItemText(IDC_EDIT2,test);

	*pResult = 0;
}

void Volume_module_dialog::OnReleasedcaptureSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}

void Volume_module_dialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	char test[50];
	int vol1,vol2;

	vol1= SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
	vol2= SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);

	if(thimod->GetVolume(0)<50) thimod->SetVolume(-(vol1-40),0);
	if(thimod->GetVolume(1)<50) thimod->SetVolume(-(vol2-40),1);

	sprintf((char*)&test,"%d Db ",-(vol1-40));
	this->SetDlgItemText(IDC_EDIT1,test);

	sprintf((char*)&test,"%d Db ",-(vol2-40));
	this->SetDlgItemText(IDC_EDIT2,test);

	*pResult = 0;
}

void Volume_module_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	char test[50];
	int vol1,vol2;
	CDialog::OnShowWindow(bShow, nStatus);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 80));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG(0, 80));

	vol1=thimod->GetVolume(0);
	vol2=thimod->GetVolume(1);

	if (thimod->GetVolume(0)==99999999)
	{
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_CHECKED, 0);
		vol1=0;
	}

	if (thimod->GetVolume(1)==99999999)
	{
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_CHECKED, 0);
		vol2=0;
	}

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE,(int)(-vol1+40));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETPOS, TRUE,(int)(-vol2+40));

	sprintf((char*)&test,"%d Db ",vol1-40);
	this->SetDlgItemText(IDC_EDIT1,test);

	sprintf((char*)&test,"%d Db ",vol2-40);
	this->SetDlgItemText(IDC_EDIT2,test);

	if(thimod->GetSwap()==1)
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_CHECKED, 0);
	else
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);

	if(thimod->GetMono()==1)
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_CHECKED, 0);
	else
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
}

void Volume_module_dialog::OnCheck3()
{
	if(thimod->GetSwap()==1)
	{
		thimod->SetSwap(0);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else
	{
		thimod->SetSwap(1);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_CHECKED, 0);
	}
}

void Volume_module_dialog::OnCheck4()
{
	if (thimod->GetVolume(0)==99999999)
		thimod->SetVolume(0,0);
	else
		thimod->SetVolume(99999999,0);

}

void Volume_module_dialog::OnCheck2()
{
	if (thimod->GetVolume(1)==99999999)
		thimod->SetVolume(0,1);
	else
		thimod->SetVolume(99999999,1);
}

void Volume_module_dialog::OnCheck5()
{
	if (thimod->GetMono())
		thimod->SetMono(0);
	else
		thimod->SetMono(1);
}
