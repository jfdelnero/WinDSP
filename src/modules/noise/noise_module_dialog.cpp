// Noise_module_dialog.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

//#include "volume_module.h"

#include "Noise_module_dialog.h"
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
// Noise_module_dialog dialog


Noise_module_dialog::Noise_module_dialog(CWnd* pParent /*=NULL*/)
	: CDialog(Noise_module_dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(Noise_module_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Noise_module_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Noise_module_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Noise_module_dialog, CDialog)
	//{{AFX_MSG_MAP(Noise_module_dialog)
	ON_COMMAND(ID_BNOISE, OnBnoise)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Noise_module_dialog message handlers

void Noise_module_dialog::OnBnoise() 
{
	// TODO: Add your command handler code here
	
}
/////////////////////////////////////////////////////////////////////////////
// Noice_module_dialog dialog


Noice_module_dialog::Noice_module_dialog(CWnd* pParent /*=NULL*/)
	: CDialog(Noice_module_dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(Noice_module_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Noice_module_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Noice_module_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Noice_module_dialog, CDialog)
	//{{AFX_MSG_MAP(Noice_module_dialog)
	ON_COMMAND(ID_BNOISE, OnBnoise)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Noice_module_dialog message handlers

void Noice_module_dialog::OnBnoise() 
{
	// TODO: Add your command handler code here
	
}
