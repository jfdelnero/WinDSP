// Delay_module_dialog.cpp : implementation file
//

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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Delay_module_dialog dialog


Delay_module_dialog::Delay_module_dialog(Delay_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Delay_module_dialog::IDD, pParent)
{
	this->thimod=thimod;

	//{{AFX_DATA_INIT(Delay_module_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Delay_module_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Delay_module_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Delay_module_dialog, CDialog)
	//{{AFX_MSG_MAP(Delay_module_dialog)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER1, OnOutofmemorySlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, OnReleasedcaptureSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER4, OnReleasedcaptureSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, OnCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER14, OnCustomdrawSlider14)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Delay_module_dialog message handlers



void Delay_module_dialog::OnOutofmemorySlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}

void Delay_module_dialog::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int result;
	char test[50];

	result = SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);

	thimod->SetDelay(result, SendDlgItemMessage(IDC_SLIDER14,TBM_GETPOS, 0, 0));
	result=thimod->GetDelay();
	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE, result);
	sprintf((char*)&test,"%d ms",result);
	this->SetDlgItemText(IDC_EDIT1,test);
	*pResult = 0;
}

void Delay_module_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int result;
	char test[50];

	result = SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);

	thimod->SetDelay(result,SendDlgItemMessage(IDC_SLIDER14,TBM_GETPOS, 0, 0));
	result=thimod->GetDelay();
	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE, result);
	sprintf((char*)&test,"%d ms",result);
	this->SetDlgItemText(IDC_EDIT1,test);
	*pResult = 0;
}

int Delay_module_dialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void Delay_module_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	char test[50];
	int delay;
	float varia,rejection;
	CDialog::OnShowWindow(bShow, nStatus);
	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 5000));
	SendDlgItemMessage(IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG(0, 1000));
	SendDlgItemMessage(IDC_SLIDER4, TBM_SETRANGE, TRUE, MAKELONG(0, 1000));
	SendDlgItemMessage(IDC_SLIDER14, TBM_SETRANGE, TRUE, MAKELONG(0, 100));

	delay=thimod->GetDelay();
	varia=thimod->GetVariation();
	rejection=thimod->GetRejection();

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE, delay);

	SendDlgItemMessage(IDC_SLIDER2, TBM_SETPOS, TRUE, (int)(varia*10));

	SendDlgItemMessage(IDC_SLIDER4, TBM_SETPOS, TRUE, (int)(rejection*10));

	SendDlgItemMessage(IDC_SLIDER14, TBM_SETPOS, TRUE, (int)thimod->GetOffset()/2);


	sprintf((char*)&test,"%d ms",delay);
	this->SetDlgItemText(IDC_EDIT1,test);

	sprintf((char*)&test,"%.1f %%",varia);
	this->SetDlgItemText(IDC_EDIT2,test);

	sprintf((char*)&test,"%.1f %%",rejection);
	this->SetDlgItemText(IDC_EDIT4,test);

}

void Delay_module_dialog::OnReleasedcaptureSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{

	int result;
	char test[50];

	result = SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);

	thimod->SetVariation((float)result/10);

	sprintf((char*)&test,"%.1f %%",(float)result/10);
	this->SetDlgItemText(IDC_EDIT2,test);
	*pResult = 0;
}

void Delay_module_dialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{

	int result;
	char test[50];

	result = SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);

	thimod->SetVariation((float)result/10);

	sprintf((char*)&test,"%.1f %%",(float)result/10);
	this->SetDlgItemText(IDC_EDIT2,test);
	*pResult = 0;
}

void Delay_module_dialog::OnReleasedcaptureSlider4(NMHDR* pNMHDR, LRESULT* pResult)
{
	int result;
	char test[50];

	result = SendDlgItemMessage(IDC_SLIDER4,TBM_GETPOS, 0, 0);

	thimod->SetRejection((float)result/10);

	sprintf((char*)&test,"%.1f %%",(float)result/10);

	this->SetDlgItemText(IDC_EDIT4,test);
	*pResult = 0;
}

void Delay_module_dialog::OnCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult)
{
	int result;
	char test[50];

	result = SendDlgItemMessage(IDC_SLIDER4,TBM_GETPOS, 0, 0);

	thimod->SetRejection((float)result/10);

	sprintf((char*)&test,"%.1f %%",(float)result/10);
	this->SetDlgItemText(IDC_EDIT4,test);
	*pResult = 0;
}

void Delay_module_dialog::OnCustomdrawSlider14(NMHDR* pNMHDR, LRESULT* pResult)
{
	int result;

	result = SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
	thimod->SetDelay(result,SendDlgItemMessage(IDC_SLIDER14,TBM_GETPOS, 0, 0));

	*pResult = 0;
}
