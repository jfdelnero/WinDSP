// Output_dialog.cpp : implementation file
//

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "output_module.h"

#include "Output_dialog.h"
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
// Output_dialog dialog


Output_dialog::Output_dialog(output_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Output_dialog::IDD, pParent)
{
	this->thimod=thimod;

	//{{AFX_DATA_INIT(Output_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void Output_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Output_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Output_dialog, CDialog)
	//{{AFX_MSG_MAP(Output_dialog)
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelchangeList2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Output_dialog message handlers

void Output_dialog::OnSelchangeList2()
{

}

void Output_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(thimod->getoutsoundcard()==1)
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_CHECKED, 0);

	if(thimod->getoutfile()==1)
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_CHECKED, 0);

}

void Output_dialog::OnCheck1()
{
	// TODO: Add your control notification handler code here
	if(thimod->getoutsoundcard()==1)
	{
		thimod->setoutsoundcard(0);
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else
	{
		thimod->setoutsoundcard(1);
		SendDlgItemMessage(IDC_CHECK1, BM_SETCHECK, BST_CHECKED, 0);
	}
}

void Output_dialog::OnCheck2()
{
	// TODO: Add your control notification handler code here
	if(thimod->getoutfile()==1)
	{
		thimod->setoutfile(0);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else
	{
		thimod->setoutfile(1);
		SendDlgItemMessage(IDC_CHECK2, BM_SETCHECK, BST_CHECKED, 0);
	}
}

void Output_dialog::OnButton1()
{
	CFileDialog fileDlg(FALSE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, "wav File (*.wav)|*.wav||", this);
	fileDlg.m_ofn.lpstrTitle = "Save a wav file...";

	if ( fileDlg.DoModal() == IDOK)
	{
		strcpy(thimod->getfilenameptr(),fileDlg.GetPathName().GetBuffer(1));
	}
}
