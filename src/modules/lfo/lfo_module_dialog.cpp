// LFO_module_dialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "lfo_module.h"

#include "lfo_module_dialog.h"
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
// LFO_module_dialog dialog


LFO_module_dialog::LFO_module_dialog(lfo_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(LFO_module_dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(LFO_module_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void LFO_module_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LFO_module_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LFO_module_dialog, CDialog)
	//{{AFX_MSG_MAP(LFO_module_dialog)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, OnCustomdrawSlider3)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnCustomdrawSlider5)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LFO_module_dialog message handlers


void LFO_module_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{

	char test[50];
	double freq,modulation;
	CDialog::OnShowWindow(bShow, nStatus);
	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 22050));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG(0, 1000));
	SendDlgItemMessage(IDC_SLIDER3, TBM_SETRANGE, TRUE, MAKELONG(0, 1000));
	SendDlgItemMessage(IDC_SLIDER5, TBM_SETRANGE, TRUE, MAKELONG(0, 32767));
	freq=thimod->GetFreq();
	modulation=thimod->GetModulation();
	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE,(int)freq);
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETPOS, TRUE,(long)((freq-(int)freq)*100));
	SendDlgItemMessage(IDC_SLIDER3, TBM_SETPOS, TRUE,(int)thimod->GetModulation()*10);

	SendDlgItemMessage(IDC_SLIDER5, TBM_SETPOS, TRUE,(int)thimod->GetAmpl());

	sprintf((char*)&test,"%.2f Hz",freq);
	this->SetDlgItemText(IDC_EDIT1,test);

	sprintf((char*)&test,"%.1f ",modulation/10);
	this->SetDlgItemText(IDC_EDIT3,test);

	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK7, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK8, BM_SETCHECK, BST_UNCHECKED, 0);

	switch(thimod->GetMode())
	{
		case 1:
			SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case 2:
			SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case 3:
			SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case 4:
			SendDlgItemMessage(IDC_CHECK7, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case 5:
			SendDlgItemMessage(IDC_CHECK8, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}
}

void LFO_module_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	double result;
	char test[50];

	result=thimod->GetFreq();
	result =(double) SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
	result = result+( (double)SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0)/(double)100);
	thimod->SetFreq(result);
	result=thimod->GetFreq();
	sprintf((char*)&test,"%.2f Hz",result);
	this->SetDlgItemText(IDC_EDIT1,test);
	*pResult = 0;

}

void LFO_module_dialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	double result;
	char test[50];

	result=thimod->GetFreq();
	result =(double) SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
	result =result+( (double)SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0)/(double)100);
	thimod->SetFreq(result);
	result=thimod->GetFreq();

	sprintf((char*)&test,"%.2f Hz",result);
	this->SetDlgItemText(IDC_EDIT1,test);
	*pResult = 0;


}

void LFO_module_dialog::OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	double result;
	char test[50];

	result=thimod->GetModulation();
	result =SendDlgItemMessage(IDC_SLIDER3,TBM_GETPOS, 0, 0);
	thimod->SetModulation(result/10);

	sprintf((char*)&test,"%.1f %%",result/10);
	this->SetDlgItemText(IDC_EDIT3,test);
	*pResult = 0;
}

void LFO_module_dialog::OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult)
{
	int result;
	result=SendDlgItemMessage(IDC_SLIDER5,TBM_GETPOS, 0, 0);
	thimod->SetAmpl(result);
	*pResult = 0;
}

void LFO_module_dialog::OnCheck3()
{
	SendDlgItemMessage(IDC_CHECK7, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK8, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_CHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
	thimod->SetMode(1);
}

void LFO_module_dialog::OnCheck4()
{
	SendDlgItemMessage(IDC_CHECK7, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK8, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_CHECKED, 0);
	SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
	thimod->SetMode(2);
}

void LFO_module_dialog::OnCheck5()
{
	SendDlgItemMessage(IDC_CHECK7, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK8, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_CHECKED, 0);
	thimod->SetMode(3);
}

void LFO_module_dialog::OnCheck7()
{
	SendDlgItemMessage(IDC_CHECK7, BM_SETCHECK, BST_CHECKED, 0);
	SendDlgItemMessage(IDC_CHECK8, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
	thimod->SetMode(4);
}

void LFO_module_dialog::OnCheck8()
{
	SendDlgItemMessage(IDC_CHECK7, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK8, BM_SETCHECK, BST_CHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
	thimod->SetMode(5);
}
