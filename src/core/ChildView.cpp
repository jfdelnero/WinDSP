/*
//
// Copyright (C) 2002-2015 Jean-François DEL NERO
// Email : jeanfrancoisdelnero -at- free.fr
//
// This file is part of the WinDSP software.
//
// WinDSP may be used and distributed without restriction provided
// that this copyright statement is not removed from the file and that any
// derivative work contains the original copyright notice and the associated
// disclaimer.
//
// WinDSP is free software; you can redistribute it
// and/or modify  it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// WinDSP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WinDSP; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
*/
///////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
//-----------H----H--X----X-----CCCCC----22222----0000-----0000------11----------//
//----------H----H----X-X-----C--------------2---0----0---0----0--1--1-----------//
//---------HHHHHH-----X------C----------22222---0----0---0----0-----1------------//
//--------H----H----X--X----C----------2-------0----0---0----0-----1-------------//
//-------H----H---X-----X---CCCCC-----222222----0000-----0000----1111------------//
//-------------------------------------------------------------------------------//
//----------------------------------------------------- http://hxc2001.free.fr --//
///////////////////////////////////////////////////////////////////////////////////
// File : ChildView.cpp
// Contains: implementation of the ChildView class
//
// Written by:	Jean-François DEL NERO 
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include <afxwin.h>
#include <mmsystem.h>
#include <string.h>

#include "module.h"

#include "delay_module.h"
#include "input_module.h"
#include "output_module.h"
#include "t_module.h"
#include "mix_module.h"
#include "lfo_module.h"
#include "volume_module.h"
#include "signal_transform_module.h"
#include "visu_module.h"
#include "reverb_module.h"
#include "filter_iir.h"
#include "filter_module.h"
#include "detector_module.h"
#include "info_module.h"
#include "morse_module.h"
#include "feedback.h"
#include "agent_module.h"

#include "sound_io.h"

#include "scheduler.h"

#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"

#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView Constructor /destructor
/////////////////////////////////////////////////////////////////////////////

CChildView::CChildView()
{
	x=0;
	y=0;
	moduleselected=1;
	BoutonL=0;
	moduleselct=0;
	actiontype=0;
	xtempline1=xtempline2=ytempline1=ytempline2=0;
	modules=new module*[100+1];
	for(int i=0;i<100;i++) modules[i]=NULL;
	sequenceur=new Scheduler();

}

CChildView::~CChildView()
{
	delete modules;

}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Evenement d'affichage du doc
/////////////////////////////////////////////////////////////////////////////

void CChildView::OnPaint()
{
	int xt,yt,X1,X2,Y1,Y2,X3,Y3,ligne;
	HPEN pen;
	HGDIOBJ oldobj;
	HFONT fonttxt;
	COLORREF couleur;
	CPaintDC dc(this);
	HICON icone;
	char * ptrchaine1,* ptrchaine2;

	// Placement des icones (modules)
	dc.SetBkMode(TRANSPARENT);
	for(int i=0;i<100;i++)
	{
		if(modules[i]!=NULL)
		{
			modules[i]->GetGraphXCord(&xt,&yt);
			icone=LoadIcon(GetModuleHandle(NULL),(char*)modules[i]->GetIconeID());
			dc.DrawIcon(xt,yt,icone);

			// Affichage du txt sous l'icone
			if(modules[i]->GetInfoTxt()!=NULL)
			{
				ligne=0;
				fonttxt=CreateFont(10,5,0,0,200,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL);
				oldobj=dc.SelectObject(fonttxt);

				ptrchaine1 = modules[i]->GetInfoTxt();

				do
				{
					ptrchaine2=strchr(ptrchaine1,'\n');//Multiligne?
					if(ptrchaine2!=NULL)
					{
						ptrchaine2[0]=0;
						ptrchaine2++;
					}
					dc.TextOut(xt,yt+32+ligne*10,ptrchaine1);
					ptrchaine1=ptrchaine2;
					ligne++;
				}
				while (ptrchaine2!=NULL);

				dc.SelectObject(oldobj);
				DeleteObject(fonttxt);
			}
			DestroyIcon(icone);

		}
	}

	// Traçage du trait temporaire (rouge)
	if(xtempline1!=xtempline2!=ytempline1!=ytempline2)
	{
		couleur = 0x0000FF;
		pen = CreatePen(PS_SOLID,2,couleur);
		oldobj = dc.SelectObject(pen);
		dc.MoveTo(xtempline1,ytempline1);
		dc.LineTo(xtempline2,ytempline2);
		dc.SelectObject(oldobj);
		DeleteObject(pen);
	}

	// Traçage des interconnections
	for(i=0;i<100;i++)
	{
		if(modules[i]!=NULL)
		{
			for(int iu=0;iu<8;iu++)
			{
				// Le port existe ?
				if(modules[i]->GetConnection(iu, &tomodule2, &toport2)==MOD_OK)
				{	// Le module pointe un autre module?
					if(tomodule2!=-1 && modules[tomodule2]!=NULL )
					{	// Le port distant existe ?
						if(modules[tomodule2]->GetConnection(toport2,&frommodule2 ,&fromport2)==MOD_OK)
						{	// Les modules sont ils bien connecté entre eux?
							if(modules[frommodule2]!=NULL && frommodule2==i && fromport2==iu)
							{
								// Alors on traçe la connection
								couleur=0xFF0000;
								pen=CreatePen(PS_SOLID,2,couleur);
								oldobj=dc.SelectObject(pen);

								// Recuperation des coordonnees des modules et des ports
								// et traçage de l'interconnection
								modules[frommodule2]->GetConnectionGraphXCoord(fromport2,&X1,&Y1,&X2,&Y2);
								modules[frommodule2]->GetGraphXCord(&X3,&Y3);
								dc.MoveTo((X1+X2)/2+X3,(Y1+Y2)/2+Y3);//pt de depart

								modules[tomodule2]->GetConnectionGraphXCoord(toport2,&X1,&Y1,&X2,&Y2);
								modules[tomodule2]->GetGraphXCord(&X3,&Y3);
								dc.LineTo((X1+X2)/2+X3,(Y1+Y2)/2+Y3);//pt d'arrivé
								dc.SelectObject(oldobj);
								DeleteObject(pen);
							}
						}
					}
				}
			}
		}
	}
}


BOOL CChildView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	return CWnd ::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/////////////////////////////////////////////////////////////////////////////
// Gestions des evenements souris..
/////////////////////////////////////////////////////////////////////////////

LRESULT CChildView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	int i=0,i2=0,xt,yt,X1,X2,Y1,Y2;

	switch(message)
	{
		/////////////////////////////////////////////////////////////////////////////
		//Double click -> fenetre de configuration
		/////////////////////////////////////////////////////////////////////////////
		case WM_LBUTTONDBLCLK:
			x=(lParam&0xffff)-16;
			y=((lParam&0xffff0000)>>16)-16;

			for(i=0;i<100;i++)
			{
				if(modules[i]!=NULL)
				{
					modules[i]->GetGraphXCord(&xt,&yt);
					if( (xt>=x-16 && xt<=x+16) && (yt>=y-16 && yt<=y+16))
					{
						modules[i]->OpenConfigWindow();
						actiontype=0;
					}
				}
			}
			break;

		/////////////////////////////////////////////////////////////////////////////
		//Deplacement souris -> deplacement objet
		/////////////////////////////////////////////////////////////////////////////
		case WM_MOUSEMOVE:
			x=(lParam&0xffff)-16;
			y=((lParam&0xffff0000)>>16)-16;
			if(actiontype==1)
			{
				modules[moduleselct]->SetGraphXCord(x,y);
				this->RedrawWindow();
			}

			if(actiontype==2)
			{
				modules[frommodule]->GetConnectionGraphXCoord(fromport,&X1,&Y1,&X2,&Y2);
				xtempline2=x+16;
				ytempline2=y+16;
				this->RedrawWindow();
			}
		break;

		/////////////////////////////////////////////////////////////////////////////
		//laché du bouton gauche souris -> ajout éventuel d'une connexion...
		/////////////////////////////////////////////////////////////////////////////
		case WM_LBUTTONUP:

			if(actiontype==2)
			{
				x=(lParam&0xffff)-16;
				y=((lParam&0xffff0000)>>16)-16;

				for(i=0;i<100;i++)
				{
					if(modules[i]!=NULL)
					{
						modules[i]->GetGraphXCord(&xt,&yt);
						if( (xt>=x-16 && xt<=x+16) && (yt>=y-16 && yt<=y+16))
						{
							for(int iu=0;iu<8;iu++)
							{
								if(modules[i]->GetConnectionGraphXCoord(iu,&X1,&Y1,&X2,&Y2)==MOD_OK)
								{
									if( ((xt+X1)<=(x+16) && (xt+X2)>=(x+16)) && ((yt+Y1)<=(y+16) && (yt+Y2)>=(y+16)) )
									{
										if((fromport<=3 && iu>=4) || (iu<=3 && fromport>=4))
										{
											toport=iu;
											tomodule=i;

											if(modules[frommodule]->GetConnection(fromport,&frommodule2 , &fromport2)==MOD_OK)
											{
												if(modules[frommodule2]!=NULL) modules[frommodule2]->SetConnection(fromport2,-1, 0);
											}

											if(modules[tomodule]->GetConnection(toport,&tomodule2 , &toport2)==MOD_OK)
											{
												if(modules[tomodule2]!=NULL) modules[tomodule2]->SetConnection(toport2,-1, 0);
											}

											modules[frommodule]->SetConnection(fromport,tomodule , toport);
											modules[tomodule]->SetConnection(toport,frommodule , fromport);

											/*if(sequenceur->CheckInfBoucle(modules,100)==1)
											{
												modules[frommodule]->SetConnection(fromport,-1 , 0);
												modules[tomodule]->SetConnection(toport,-1 , 0);
												MessageBox("Boucle Infinie !!!","Erreur !!",MB_OK|MB_ICONHAND);
											}*/
										}
									}
								}
							}
						}
					}
				}
			}

			xtempline1=xtempline2=ytempline1=ytempline2=0;

			BoutonL=0;
			actiontype=0;
			this->RedrawWindow();
		break;

		/////////////////////////////////////////////////////////////////////////////
		// Bouton gauche -> ajout module, fil, ou deplacement
		/////////////////////////////////////////////////////////////////////////////
		case WM_LBUTTONDOWN:
		{
			BoutonL=1;

			x=(lParam&0xffff)-16;
			y=((lParam&0xffff0000)>>16)-16;

			for(i=0;i<100;i++)
			{
				if(modules[i]!=NULL)
				{
					modules[i]->GetGraphXCord(&xt,&yt);
					if( (xt>=x-16 && xt<=x+16) && (yt>=y-16 && yt<=y+16))
					{

						for(int iu=0;iu<8;iu++)
						{

							if(modules[i]->GetConnectionGraphXCoord(iu,&X1,&Y1,&X2,&Y2)==MOD_OK)
							{
								if( ((xt+X1)<=(x+16) && (xt+X2)>=(x+16)) && ((yt+Y1)<=(y+16) && (yt+Y2)>=(y+16)) )
								{
									actiontype=actiontype|2;
									fromport=iu;
									frommodule=i;
									xtempline1=xtempline2=(X1+X2)/2+xt;
									ytempline1=ytempline2=(Y1+Y2)/2+yt;
								}
							}
						}

						if(actiontype==0)
						{
							moduleselct=i;
							actiontype=actiontype|1;
						}
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////
			//  ajout module
			/////////////////////////////////////////////////////////////////////////////

			if(actiontype==0)
			{
				while(i2<100 && modules[i2]!=NULL)
					i2++;

				switch(moduleselected)
				{
					case 3:
						modules[i2]=new Delay_module(x,y);
					break;

					case 1:
						if(sequenceur->GetSynchroScheduler()!=1 && sequenceur->GetSynchroScheduler()!=3)
						{
							if(sequenceur->GetSynchroScheduler()==2)
								sequenceur->SetSynchroScheduler(3);
							else
								sequenceur->SetSynchroScheduler(1);
							modules[i2]=new input_module(x,y);
						}
					break;

					case 2:
						if(sequenceur->GetSynchroScheduler()!=2 && sequenceur->GetSynchroScheduler()!=3)
						{
							modules[i2]=new output_module(x,y);
							if(sequenceur->GetSynchroScheduler()==1)
								sequenceur->SetSynchroScheduler(3);
							else
								sequenceur->SetSynchroScheduler(2);
								modules[i2]=new output_module(x,y);
						}
					break;

					case 4:
						modules[i2]=new mix_module(x,y);
					break;

					case 5:
						modules[i2]=new t_module(x,y);
					break;

					case 6:
						modules[i2]=new lfo_module(x,y);
					break;

					case 7:
						modules[i2]=new Volume_module(x,y);
					break;

					case 8:
						modules[i2]=new SignalTransform_module(x,y);
					break;
					case 9:
						modules[i2]=new visu_module(x,y);
					break;
					case 10:
						modules[i2]=new reverb_module(x,y);
					break;
					case 11:
						modules[i2]=new Filter_module(x,y);
					break;
					case 12:
						modules[i2]=new Detector_module(x,y);
					break;
					case 13:
						modules[i2]=new info_module(x,y);
					break;
					case 14:
						modules[i2]=new Morse_module(x,y);
					break;
					case 15:
						modules[i2]=new feedback_module(x,y);
					break;
					case 16:
						modules[i2]=new Agent_module(x,y);
					break;
				}

				if(sequenceur!=NULL && sequenceur->GetStatusScheduler()==1 && modules[i2]!=NULL)
				{
					modules[i2]->SetProcessFlag(0);
					modules[i2]->PrepareProcess(sequenceur->GetBufferSize());
				}
			}

			this->RedrawWindow();
		}
		break;

		/////////////////////////////////////////////////////////////////////////////
		//Bouton droit souris -> effacement
		/////////////////////////////////////////////////////////////////////////////
		case WM_RBUTTONDOWN:

			BoutonL=0;
			actiontype=0;
			x=(lParam&0xffff)-16;
			y=((lParam&0xffff0000)>>16)-16;

			for(i=0;i<100;i++)
			{
				if(modules[i]!=NULL)
				{
					modules[i]->GetGraphXCord(&xt,&yt);
					if( (xt>=x-16 && xt<=x+16) && (yt>=y-16 && yt<=y+16))
					{
						// Il faut supprimer toutes les connections venant sur ce module !
						for(int k=0;k<8;k++)
						{
							if(modules[i]->GetConnection(k,&tomodule2 ,&toport2)==MOD_OK)
							{
								modules[tomodule2]->SetConnection(toport2,-1,0);
							}
						}

						if(sequenceur!=NULL)
							modules[i]->CloseProcess();

						if(modules[i]->GetIconeID()==IDI_ICON2)
						{
								if(sequenceur->GetSynchroScheduler()==3)
									sequenceur->SetSynchroScheduler(2);
								else
									sequenceur->SetSynchroScheduler(0);
						}

						if(modules[i]->GetIconeID()==IDI_ICON4)
						{
								if(sequenceur->GetSynchroScheduler()==3)
									sequenceur->SetSynchroScheduler(1);
								else
									sequenceur->SetSynchroScheduler(0);
						}

						delete modules[i];
						modules[i]=NULL;
					}
				}
			}
			this->RedrawWindow();
		break;
	};

	return CWnd ::DefWindowProc(message, wParam, lParam);
}



/////////////////////////////////////////////////////////////////////////////
// Refresh
/////////////////////////////////////////////////////////////////////////////

void CChildView::Refresh()
{
	this->RedrawWindow();
}

/////////////////////////////////////////////////////////////////////////////
// Selection du module a placer...
/////////////////////////////////////////////////////////////////////////////

void CChildView::SelectModule(int module)
{
	moduleselected=module;
}

/////////////////////////////////////////////////////////////////////////////
// Fonctions de commandes du sequenceur
/////////////////////////////////////////////////////////////////////////////

int CChildView::StartSequence()
{
	int temp;
	if(sequenceur->GetStatusScheduler()==0)
	{
		sequenceur->SetStatusScheduler(1);
		temp=sequenceur->DoOneSequence(modules,100);
	}

	return 0;
}


int CChildView::StopSequence()
{
	if(sequenceur!=NULL)
	{
		sequenceur->SetStatusScheduler(0);
		sequenceur->CloseScheduler();

		for(int i=0;i<100;i++)
		{
			if(modules[i]!=NULL)
			{
				modules[i]->CloseProcess();
			}
		}
	}
	return 0;
}

int CChildView::ContinueSequence(int call)
{
	if(sequenceur->GetStatusScheduler()==1)
	{
		if(((sequenceur->GetSynchroScheduler()==1) || (sequenceur->GetSynchroScheduler()==3)) && call==1)
			sequenceur->DoOneSequence(modules,100);

		if((sequenceur->GetSynchroScheduler()==2) && call==2)
			sequenceur->DoOneSequence(modules,100);

		if((sequenceur->GetSynchroScheduler()==0) && call==4)
			sequenceur->DoOneSequence(modules,100);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//  Sauvegarde du fichier
/////////////////////////////////////////////////////////////////////////////

int CChildView::SaveDsp(char* t)
{
	char buffer[5120];
	int type,taille;
	char dspmod[512];

	ofstream f(t) ;

	f.setmode(filebuf::binary);

	for(int i=0;i<100;i++)
	{
		if(modules[i]!=NULL)
		{
			taille=modules[i]->GetParamData((void*)&buffer,512,&type);
			sprintf(dspmod,"DSPMOD");
			f.write(dspmod,strlen(dspmod));
			f.write((char*)&i,sizeof(i));
			f.write((char*)&type,sizeof(type));
			f.write((char*)&taille,sizeof(taille));
			f.write(buffer,taille);
		}
	}

	f.close();

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//  Chargement d'un fichier
/////////////////////////////////////////////////////////////////////////////

int CChildView::LoadDsp(char* t)
{
	char buffer[5120];
	int type,taille,i;

	sequenceur->SetStatusScheduler(0);
	sequenceur->CloseScheduler();

	for( i=0;i<100;i++)
	{
		if(modules[i]!=NULL)
		{
			if(sequenceur!=NULL) modules[i]->CloseProcess();
			delete modules[i];
			modules[i]=NULL;
		}
	}

	sequenceur->SetSynchroScheduler(0);

	ifstream f(t) ;

	f.setmode(filebuf::binary);

	while(!f.eof())
	{
		f.read(buffer,sizeof("DSPMO"));
		buffer[6]=0;

		if(strcmp(buffer,"DSPMOD")==0)
		{
			f.read((char*)&i,sizeof(i));
			f.read((char*)&type,sizeof(type));
			f.read((char*)&taille,sizeof(taille));
			f.read(buffer,taille);
			switch(type)
			{
				case 1:
					modules[i]=new input_module(0,0);
					if(sequenceur->GetSynchroScheduler()==2)
						sequenceur->SetSynchroScheduler(3);
					else
						sequenceur->SetSynchroScheduler(1);
				break;

				case 2:
					modules[i]=new output_module(0,0);
					if(sequenceur->GetSynchroScheduler()==1)
						sequenceur->SetSynchroScheduler(3);
					else
						sequenceur->SetSynchroScheduler(2);
				break;

				case 3:
					modules[i]=new Delay_module(0,0);
				break;

				case 4:
					modules[i]=new mix_module(0,0);
				break;
				case 5:
					modules[i]=new t_module(0,0);
				break;
				case 6:
					modules[i]=new lfo_module(0,0);
				break;
				case 7:
					modules[i]=new Volume_module(0,0);
				break;
				case 8:
					modules[i]=new SignalTransform_module(0,0);
				break;
				case 9:
					modules[i]=new visu_module(0,0);
				break;
				case 10:
					modules[i]=new reverb_module(0,0);
				break;
				case 11:
					modules[i]=new Filter_module(0,0);
				break;
				case 12:
					modules[i]=new Detector_module(0,0);
				break;
				case 13:
					modules[i]=new info_module(0,0);
				break;
				case 14:
					modules[i]=new Morse_module(0,0);
				break;

				case 15:
					modules[i]=new feedback_module(0,0);
				break;
				case 16:
					modules[i]=new Agent_module(0,0);
				break;
			}

			modules[i]->SetParamData(buffer,taille,&type );
		}
	}

	f.close();

	this->RedrawWindow();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
