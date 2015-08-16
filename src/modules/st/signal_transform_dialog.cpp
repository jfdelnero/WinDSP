// SignalTransform_dialog.cpp : implementation file
//

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "signal_transform_module.h"

#include "signal_transform_dialog.h"
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
// SignalTransform_dialog dialog


SignalTransform_dialog::SignalTransform_dialog(SignalTransform_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(SignalTransform_dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(SignalTransform_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SignalTransform_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SignalTransform_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SignalTransform_dialog, CDialog)
	//{{AFX_MSG_MAP(SignalTransform_dialog)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SignalTransform_dialog message handlers

void SignalTransform_dialog::OnCheck1()
{


	if(thimod->GetConfig(0)==1)
	{
		thimod->SetConfig(0,0);
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else
	{
		thimod->SetConfig(0,1);
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_CHECKED, 0);
	}
	SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);

}

void SignalTransform_dialog::OnCheck2()
{
	SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);

	if(thimod->GetConfig(0)==2)
	{
		thimod->SetConfig(0,0);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else
	{
		thimod->SetConfig(0,2);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_CHECKED, 0);
	}

	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
}

void SignalTransform_dialog::OnCheck3()
{
	SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);

	if(thimod->GetConfig(0)==3)
	{
		thimod->SetConfig(0,0);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else
	{
		thimod->SetConfig(0,3);
		SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_CHECKED, 0);
	}

	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
}

void SignalTransform_dialog::OnCheck4()
{
	SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	if(thimod->GetConfig(0)==4)
	{
		thimod->SetConfig(0,0);
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else
	{
		thimod->SetConfig(0,4);
		SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_CHECKED, 0);
	}
}

void SignalTransform_dialog::OnCheck5()
{
	if(thimod->GetConfig(1)==1)
	{
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_UNCHECKED, 0);
		thimod->SetConfig(1,0);
	}
	else
	{
		thimod->SetConfig(1,1);
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_CHECKED, 0);
	}
}

void SignalTransform_dialog::OnCheck6()
{
	if(thimod->GetConfig(2)==1)
	{
		SendDlgItemMessage(IDC_CHECK6, BM_SETCHECK, BST_UNCHECKED, 0);
		thimod->SetConfig(2,0);
	}
	else
	{
		thimod->SetConfig(2,1);
		SendDlgItemMessage(IDC_CHECK6, BM_SETCHECK, BST_CHECKED, 0);
	}
}

void SignalTransform_dialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	char test[50];
	int val1;

	val1= (SendDlgItemMessage(IDC_SLIDER1,TBM_GETPOS, 0, 0)*10-32760);

    thimod->SetConfig(3,val1);

	sprintf((char*)&test,"%d  ",val1);
	this->SetDlgItemText(IDC_EDIT1,test);

	*pResult = 0;

}

void SignalTransform_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	char test[50];
	int val1;

	SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_UNCHECKED, 0);
	SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_UNCHECKED, 0);
	switch(thimod->GetConfig(0))
	{
		case 0:
		break;
		case 1:
			SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case 2:
			SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case 3:
			SendDlgItemMessage(IDC_CHECK3, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case 4:
			SendDlgItemMessage(IDC_CHECK4, BM_SETCHECK, BST_CHECKED, 0);
		break;
	}

	if(thimod->GetConfig(1)==1)
		SendDlgItemMessage(IDC_CHECK5, BM_SETCHECK, BST_CHECKED, 0);

	if(thimod->GetConfig(2)==1)
		SendDlgItemMessage(IDC_CHECK6, BM_SETCHECK, BST_CHECKED, 0);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG(0, 6553));

	val1=thimod->GetConfig(3);

	SendDlgItemMessage(IDC_SLIDER1, TBM_SETPOS, TRUE,(int)(val1+32765)/10);

	sprintf((char*)&test,"%d  ",val1);
	this->SetDlgItemText(IDC_EDIT1,test);

}
