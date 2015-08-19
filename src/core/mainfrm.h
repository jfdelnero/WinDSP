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
// File:  mainfrm.h
// Contains: class CMainFrame declaration...
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__3C92C6A7_E7FD_4A21_9419_42DA2E27A133__INCLUDED_)
#define AFX_MAINFRM_H__3C92C6A7_E7FD_4A21_9419_42DA2E27A133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
private:

	int NeedRefresh;
	int CompteurTemps;

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	DECLARE_DYNAMIC(CMainFrame)

public:

	CChildView m_wndView;
	Sound_IO Gestio;
	virtual ~CMainFrame();
	CMainFrame();

	void Refresh();
	LRESULT Message_MM_WIM_OPEN(WPARAM wPara, LPARAM lPara);
	LRESULT Message_MM_WIM_CLOSE(WPARAM wPara, LPARAM lPara);
	LRESULT Message_MM_WIM_DATA(WPARAM wPara, LPARAM lPara);
	LRESULT Message_MM_WOM_OPEN(WPARAM wPara, LPARAM lPara);
	LRESULT Message_MM_WOM_CLOSE(WPARAM wPara, LPARAM lPara);
	LRESULT Message_MM_WOM_DONE(WPARAM wPara, LPARAM lPara);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnBmodule01();
	afx_msg void OnBmodule02();
	afx_msg void OnBmodule03();
	afx_msg void OnBmodule04();
	afx_msg void OnBmodule05();
	afx_msg void OnBmodule06();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBmodule08();
	afx_msg void OnBmodule09();
	afx_msg void OnBmodule10();
	afx_msg void OnBmodule11();
	afx_msg void OnBmodule12();
	afx_msg void OnBmodule13();
	afx_msg void OnFichierOuvrir();
	afx_msg void OnFichierEnregistrer();
	afx_msg void OnBstop();
	afx_msg void OnBmodule14();
	afx_msg void OnOptionsEsson();
	afx_msg void OnBMODULE15();
	afx_msg void OnBmix();
	afx_msg void OnClose();
	afx_msg void OnBmorse();
	afx_msg void OnBfb();
	afx_msg void OnBagent();
	afx_msg void OnBnoise();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3C92C6A7_E7FD_4A21_9419_42DA2E27A133__INCLUDED_)
