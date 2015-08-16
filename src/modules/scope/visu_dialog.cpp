// Visu_dialog.cpp : implementation file
//

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"


#include "visu_module.h"
#include "visu_dialog.h"

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

#define TAILLETFFTX 320
#define TAILLETFFTY 200

/////////////////////////////////////////////////////////////////////////////
// Visu_dialog dialog

void Visu_dialog::CopyVidBuffer(HWND hWnd2, unsigned char* buffer)
{
	RECT MyRect;
	if(buffervideo!=NULL && MyDC!=NULL)
	{
		GetClientRect(&MyRect);

		if(StretchDIBits(MyDC,0,0,MyRect.right,MyRect.bottom,0,0,TAILLETFFTX,TAILLETFFTY,buffervideo,bmapinfo,DIB_RGB_COLORS,SRCCOPY)==GDI_ERROR)
		{
		}
	}
}

void Visu_dialog::ClearBuffer(unsigned char *BufferVideo)
{
	__asm
	{
		pushad
		mov edi,BufferVideo
		mov ecx,(320*200)/4
		xor	eax,eax
		Boucle:
			mov ds:[edi],eax
			add edi,4
			dec ecx
		jnz boucle
		popad
	}
}


void Visu_dialog::BuildPallette(BITMAPINFO *bmapinfo,int viewmode)
{
	int i;

	switch(viewmode)
	{
		case 1:
		case 2:
		case 3:
			for(i=0;i<256;i++)
			{
				bmapinfo->bmiColors[i].rgbRed=i;
				bmapinfo->bmiColors[i].rgbGreen=i;
				bmapinfo->bmiColors[i].rgbBlue=i;
				bmapinfo->bmiColors[i].rgbReserved=0;
			}
		break;

		case 4:
			for(i=0;i<256;i++)
			{
				bmapinfo->bmiColors[i].rgbRed=i;
				bmapinfo->bmiColors[i].rgbGreen=i;
				bmapinfo->bmiColors[i].rgbBlue=i;
				bmapinfo->bmiColors[i].rgbReserved=0;
			}
		break;
	}
}

Visu_dialog::Visu_dialog(visu_module * thimod,CWnd* pParent /*=NULL*/)
	: CDialog(Visu_dialog::IDD, pParent)
{
	this->thimod=thimod;
	test=NULL;
	taillex=320;
	tailley=200;
	sizebuff=0;
	sizebuff2=0;
	sizebuff3=0;
	sizefft=0;
	posix=0;
	sizefft=2048;
	scroll=0;
	bmapinfo=NULL;
	buffer3=NULL;
	buffervideo=NULL;
	MyDC=NULL;
	sizebuff=0;

	//{{AFX_DATA_INIT(Visu_dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Visu_dialog::~Visu_dialog()
{
	if(buffervideo!=NULL)
		delete buffervideo;
}

void Visu_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Visu_dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Visu_dialog, CDialog)
	//{{AFX_MSG_MAP(Visu_dialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Visu_dialog message handlers

void Visu_dialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
    char string1[128];

	sprintf(string1,"Scope n° %d :",thimod->ScopeNumber());
	this->SetWindowText(string1);
	this->SetRedraw(false);

	if(bShow)
	{
		sprintf(string1,"Scope n° %d :",thimod->ScopeNumber());
		this->SetWindowText(string1);
		this->SetRedraw(false);

		if(bmapinfo==NULL && buffervideo==NULL)
		{
			bmapinfo = (BITMAPINFO *) new char[(sizeof(BITMAPINFO) + sizeof(RGBQUAD) * 255)];

			bmapinfo->bmiHeader.biSize=sizeof(bmapinfo->bmiHeader);
			bmapinfo->bmiHeader.biWidth=TAILLETFFTX;
			bmapinfo->bmiHeader.biHeight=-TAILLETFFTY;
			bmapinfo->bmiHeader.biPlanes=1;
			bmapinfo->bmiHeader.biBitCount=8;
			bmapinfo->bmiHeader.biCompression=BI_RGB;
			bmapinfo->bmiHeader.biSizeImage=0;
			bmapinfo->bmiHeader.biXPelsPerMeter=0;
			bmapinfo->bmiHeader.biYPelsPerMeter=0;
			bmapinfo->bmiHeader.biClrUsed=0;
			bmapinfo->bmiHeader.biClrImportant=0;

			for(int i=0;i<256;i++){
				bmapinfo->bmiColors[i].rgbBlue=i;
				bmapinfo->bmiColors[i].rgbGreen=i;
				bmapinfo->bmiColors[i].rgbRed=i;
				bmapinfo->bmiColors[i].rgbReserved=0;
			}

			if(buffervideo==NULL)
			{
				buffervideo=new unsigned char[TAILLETFFTX*TAILLETFFTY+10];
				ClearBuffer(buffervideo);
				scroll=0;
			}
		}

		if(nStatus==SW_PARENTOPENING	)
		{
			this->ShowWindow(SW_SHOWNOACTIVATE);
			this->RedrawWindow();
		}
	}
	else
	{
		if(nStatus==SW_PARENTCLOSING)
		{
			this->ShowWindow(SW_HIDE);
		}
	}
}

void Visu_dialog::RefreshVisu(short * buffer,int size)
{
	sizebuff3=size;
	buffer3=buffer;

	if(thimod->GetMode()==2)
		this->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW	|RDW_NOERASE);
	else
		this->RedrawWindow();
}

void Visu_dialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(cy==0) cy=1;
	if(cx==0) cx=1;
	tailley=cy;
	taillex=cx;
	this->RedrawWindow();
}

void Visu_dialog::OnButton2()
{
	sizebuff=sizebuff+256;
	sizefft=sizefft+128;
}

void Visu_dialog::OnButton1()
{
	sizebuff=sizebuff-256;
	sizefft=sizefft-128;
}

void Visu_dialog::OnButton3()
{
	thimod->SetMode(thimod->GetMode()+1);
	if(thimod->GetMode()>2) thimod->SetMode(0);
}

void Visu_dialog::OnOK()
{
	CDialog::OnOK();
	if(buffervideo!=NULL) delete buffervideo;
	buffervideo=NULL;
	thimod->DestroyDialog();
}

void Visu_dialog::OnPaint()
{
	CPaintDC dc(this);
	HGDIOBJ oldobj;
	int i;
	i=0;
	int x1,y1,x2,y2;
	short val,val2;
	HPEN pen;
	COLORREF couleur;

	if(sizebuff>sizebuff3 || sizebuff==0)
	{
		sizebuff=sizebuff3;
		sizebuff2=sizebuff;
	}

	test=buffer3;

	if(test!=NULL)
	{
		MyDC=dc.GetSafeHdc();

		switch( thimod->GetMode() )
		{
			case 0:
				// Mode oscilloscope

				//création d'un nouveau stylo
				couleur=0xFF0000;//Rouge
				pen=CreatePen(PS_DASHDOT,1,couleur);
				oldobj=dc.SelectObject(pen);

				//On trace les 2 axes
				dc.MoveTo(0,(tailley/4));
				dc.LineTo((taillex),(tailley/4));

				dc.MoveTo(0,(3*tailley/4));
				dc.LineTo((taillex),(3*tailley/4));

				dc.SelectObject(oldobj);
				DeleteObject(pen);

				//Ici on trace la separation
				couleur=0x3333FF;
				pen=CreatePen(PS_SOLID,2,couleur);
				oldobj=dc.SelectObject(pen);
				dc.MoveTo(0,(tailley/2));
				dc.LineTo((taillex),(tailley/2));
				dc.SelectObject(oldobj);
				DeleteObject(pen);

				// Stylo pour les courbes : noire
				couleur=0x000000;
				pen=CreatePen(PS_SOLID,1,couleur);
				oldobj=dc.SelectObject(pen);

				x1=0;
				y1=100;
				x2=0;
				y2=0;

				if(test!=NULL)
				{
					y1=val=(-*(test+((sizebuff/4)/taillex)))/(2*65365/tailley)+(tailley/4);
					y2=val2=(-*(test+1+((sizebuff/4)/taillex)))/(2*65365/tailley)+(tailley/2);

					// Parcour du buffer et remise a l'echelle des valeur + affichage
					for(i=0;i<taillex;i++)
					{

						val=(-*(test+1+(1|(int)((float)i*2*((float)sizebuff/4)/(float)taillex)))/(2*65365/tailley));
						val2=(-*(test+1+((0xfffffe) &(int)((float)i*2*((float)sizebuff/4)/(float)taillex)))/(2*65365/tailley));

						dc.MoveTo(x1,y1);
						dc.LineTo(i,val+(tailley/4));

						dc.MoveTo(x1,y2+(tailley/4));
						dc.LineTo(i,val2+(3*tailley/4));

						y1=val+(tailley/4);
						y2=val2+(tailley/2);
						x1=i;

					}

					dc.SelectObject(oldobj);
					DeleteObject(pen);

				}
			break;

			case 1:

				// Mode FFT
				// Séparation
				couleur=0x3333FF;
				pen=CreatePen(PS_SOLID,2,couleur);
				oldobj=dc.SelectObject(pen);
				dc.MoveTo(0,(tailley/2));
				dc.LineTo((taillex),(tailley/2));
				dc.SelectObject(oldobj);
				DeleteObject(pen);

				couleur=0x000000;
				pen=CreatePen(PS_SOLID,1,couleur);
				oldobj=dc.SelectObject(pen);

				x1=taillex;
				y1=tailley/2;
				x2=taillex;
				y2=tailley/2;

				if(test!=NULL)
				{
					y1=val=(-*(test+taillex))/5;
					y2=val2=(-*(test+sizebuff+taillex))/5;

					for(i=taillex;i!=0;i--)
					{
						// Parcour du buffer fft  et remise a l'echelle des valeur + affichage

						val=(short)(-*(test+	       (short)(i*((sizefft/2)/(float)taillex)))/(float)(65365/(32*(float)tailley/2)));
						val2=(short)(-*(test+sizebuff2+(short)(i*((sizefft/2)/(float)taillex)))/(float)(65365/(32*(float)tailley/2)));

						if(val<-(tailley/2))val=-(tailley/2);
						if(val2<-(tailley/2))val2=-(tailley/2);

						if((test+i*((2048/2)/taillex))-test<2048*2)
						{
							dc.MoveTo(x1,y1);

							dc.LineTo(i,val+(tailley/2));

							dc.MoveTo(x1,y2);
							dc.LineTo(i,val2+(tailley));
						}

						y1=val+(tailley/2);
						y2=val2+(tailley);
						x1=i;

					}

					dc.SelectObject(oldobj);
					DeleteObject(pen);

				}
			break;

			case 2:
				BuildPallette(bmapinfo,1);
				CopyVidBuffer(NULL,buffervideo);
			break;
		}
	}
}

void Visu_dialog::RecalculFFTFrame(unsigned short * buffer,int size)
{
	int i1;
	unsigned long pixval;

	if(buffervideo!=NULL && test!=NULL)
	{
		for(i1=0;i1<TAILLETFFTY;i1++)
		{
			pixval = (unsigned long)((double)(*(test+((sizefft/2))-(int)((double)i1*(double)((double)(sizefft/2)/(double)TAILLETFFTY)))/*/(double)2*/));

			if(pixval >255) pixval = 255;

			*(buffervideo+(TAILLETFFTX*i1)+scroll) = (unsigned char)pixval;
		}

		scroll++;
		if(scroll>=TAILLETFFTX) scroll=0;

		for(i1=0;i1<TAILLETFFTY;i1++)
		{
			*((unsigned char*)buffervideo+(TAILLETFFTX*i1)+scroll) = 222;
		}
	}
}
