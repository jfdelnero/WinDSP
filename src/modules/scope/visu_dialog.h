#if !defined(AFX_VISU_DIALOG_H__EDB363BD_1781_41C3_8505_4468F8107BF5__INCLUDED_)
#define AFX_VISU_DIALOG_H__EDB363BD_1781_41C3_8505_4468F8107BF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Visu_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Visu_dialog dialog

class Visu_dialog : public CDialog
{
// Construction
	//visu_module
	visu_module * thimod;
	short * test;
	int taillex,tailley,posix;
	int sizebuff,sizebuff2,sizebuff3,sizefft;
	unsigned char * buffervideo;
	short* buffer3;
	int scroll;
	HDC MyDC;


public:
	BITMAPINFO * bmapinfo;

	Visu_dialog(visu_module * thimod,CWnd* pParent = NULL);   // standard constructor
	~Visu_dialog();
    void RefreshVisu(short * buffer,int size);   // standard constructor
	void CopyVidBuffer(HWND hWnd2, unsigned char* buffer);
	void ClearBuffer(unsigned char *BufferVideo);
	void BuildPallette(BITMAPINFO *bmapinfo,int viewmode);
	void RecalculFFTFrame(unsigned short * buffer,int size);
// Dialog Data
	//{{AFX_DATA(Visu_dialog)
	enum { IDD = IDD_MODULE_SCOPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Visu_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Visu_dialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISU_DIALOG_H__EDB363BD_1781_41C3_8505_4468F8107BF5__INCLUDED_)
