// Agent_module_dialog3.cpp : implementation file
//

#include "resource.h" 
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "agent_module.h"

#include "agent_module_dialog.h"
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
// Agent_module_dialog3 dialog


Agent_module_dialog3::Agent_module_dialog3(Agent_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Agent_module_dialog3::IDD, pParent)
{
	this->thimod=thimod;
		
	//{{AFX_DATA_INIT(Agent_module_dialog3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Agent_module_dialog3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Agent_module_dialog3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Agent_module_dialog3, CDialog)
	//{{AFX_MSG_MAP(Agent_module_dialog3)
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
// Agent_module_dialog3 message handlers

void Agent_module_dialog3::OnOutofmemorySlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;	
}

void Agent_module_dialog3::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
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

void Agent_module_dialog3::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int result;

	result = SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);
			
	thimod->SetDelay(result,SendDlgItemMessage(IDC_SLIDER14,TBM_GETPOS, 0, 0));
	result=thimod->GetDelay();
	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE, result);
	*pResult = 0;
}

int Agent_module_dialog3::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void Agent_module_dialog3::OnShowWindow(BOOL bShow, UINT nStatus) 
{
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
}


void Agent_module_dialog3::OnReleasedcaptureSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{		
	int result;
	
	result = SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);
			
	thimod->SetVariation((float)result/10);

	*pResult = 0;
}

void Agent_module_dialog3::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{		
	int result;
	
	result = SendDlgItemMessage(IDC_SLIDER2,TBM_GETPOS, 0, 0);
			
	thimod->SetVariation((float)result/10);

	*pResult = 0;
}

void Agent_module_dialog3::OnReleasedcaptureSlider4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int result;
	
	result = SendDlgItemMessage(IDC_SLIDER4,TBM_GETPOS, 0, 0);
			
	thimod->SetRejection((float)result/10);

	*pResult = 0;
}

void Agent_module_dialog3::OnCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int result;

	result = SendDlgItemMessage(IDC_SLIDER4,TBM_GETPOS, 0, 0);
			
	thimod->SetRejection((float)result/10);

	*pResult = 0;
}

void Agent_module_dialog3::OnCustomdrawSlider14(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int result;
		
	result = SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0);	
	thimod->SetDelay(result,SendDlgItemMessage(IDC_SLIDER14,TBM_GETPOS, 0, 0));
	
	
	*pResult = 0;
}

void Agent_module_dialog3::Test(int i,int v)
{
	char test[100];

	switch(i+1)
	{
		case 1:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT1,test);
		break;
		case 2:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT2,test);
		break;
		case 3:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT4,test);
		break;
		case 4:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT5,test);
		break;
		case 5:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT6,test);
		break;
		case 6:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT7,test);
		break;
		case 7:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT8,test);
		break;
		case 8:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT9,test);
		break;
		case 9:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT10,test);
		break;
		case 10:
			sprintf((char*)&test,"%d",v);
			this->SetDlgItemText(IDC_EDIT11,test);
		break;
	}
}


