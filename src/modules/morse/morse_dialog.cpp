// Morse_Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "module.h"

#include "Morse_module.h"

#include "Morse_Dialog.h"
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
// Morse_Dialog dialog


Morse_Dialog::Morse_Dialog(Morse_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Morse_Dialog::IDD, pParent)
{
	this->thimod=thimod;
	//{{AFX_DATA_INIT(Morse_Dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Morse_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Morse_Dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Morse_Dialog, CDialog)
	//{{AFX_MSG_MAP(Morse_Dialog)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Morse_Dialog message handlers

void Morse_Dialog::OnChangeEdit1()
{
	this->GetDlgItemText(IDC_EDIT1,lachaine,512);
	thimod->SetTxt((char*)lachaine);
}

void Morse_Dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	this->SetDlgItemText(IDC_EDIT1,thimod->GetTxt());
}
