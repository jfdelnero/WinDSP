#if !defined(AFX_MIX_DIALOG_H__FA34E5C3_78B4_4A08_8174_988B5C84703E__INCLUDED_)
#define AFX_MIX_DIALOG_H__FA34E5C3_78B4_4A08_8174_988B5C84703E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mix_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Mix_dialog dialog

class Mix_dialog : public CDialog
{
// Construction
	mix_module * thimod;
public:
	Mix_dialog(mix_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Mix_dialog)
	enum { IDD = IDD_MODULE_MIX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Mix_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Mix_dialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIX_DIALOG_H__FA34E5C3_78B4_4A08_8174_988B5C84703E__INCLUDED_)
