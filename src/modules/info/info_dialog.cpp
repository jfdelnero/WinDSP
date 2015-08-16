// Info_Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "module.h"

#include "Info_module.h"

#include "Info_Dialog.h"
#include "Sound_IO.h"
#include "Scheduler.h"
#include "childView.h"
#include "MainFrm.h"
#include "WinDSP.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Info_Dialog dialog


Info_Dialog::Info_Dialog(info_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Info_Dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(Info_Dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Info_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Info_Dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Info_Dialog, CDialog)
	//{{AFX_MSG_MAP(Info_Dialog)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Info_Dialog message handlers

void Info_Dialog::OnChangeEdit1()
{
	this->GetDlgItemText(IDC_EDIT1,lachaine,512);
	thimod->SetTxt((char*)lachaine);
}

void Info_Dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	this->SetDlgItemText(IDC_EDIT1,thimod->GetTxt());
}
