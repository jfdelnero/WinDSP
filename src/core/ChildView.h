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
// File : ChildView.h
// Contains: interface of the ChildView class
//
// Written by:	Jean-François DEL NERO 
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//
#if !defined(AFX_CHILDVIEW_H__8EF38C80_BB78_4D4B_AE2E_6679FD68372E__INCLUDED_)
#define AFX_CHILDVIEW_H__8EF38C80_BB78_4D4B_AE2E_6679FD68372E__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//AFX//


/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
private:

	module ** modules;

	int x;
	int y;
	int moduleselected;

	int BoutonL;

	int moduleselct;
	int actiontype;

	int frommodule;
	int fromport;
	int tomodule;
	int toport;

	int frommodule2;
	int fromport2;
	int tomodule2;
	int toport2;

	int xtempline1, ytempline1,xtempline2,ytempline2;

public:
	Scheduler * sequenceur;

	virtual ~CChildView();
	CChildView();
	void SelectModule(int);
	int StartSequence();
	int ContinueSequence(int);
	int StopSequence();

	int SaveDsp(char*);
	int LoadDsp(char*);
	void Refresh();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}


#endif // !defined(AFX_CHILDVIEW_H__8EF38C80_BB78_4D4B_AE2E_6679FD68372E__INCLUDED_)
