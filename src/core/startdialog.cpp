// startdialog.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "startdialog.h"
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
// startdialog dialog


startdialog::startdialog(CWnd* pParent /*=NULL*/)
	: CDialog(startdialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(startdialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void startdialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(startdialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(startdialog, CDialog)
	//{{AFX_MSG_MAP(startdialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// startdialog message handlers
