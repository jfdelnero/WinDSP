#if !defined(AFX_REVERB_DIALOG_H__EB4FD105_E1BC_423D_BDE4_7C18AB126546__INCLUDED_)
#define AFX_REVERB_DIALOG_H__EB4FD105_E1BC_423D_BDE4_7C18AB126546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// reverb_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// reverb_dialog dialog

class reverb_dialog : public CDialog
{
// Construction
	reverb_module * thimod;
public:
	reverb_dialog(reverb_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(reverb_dialog)
	enum { IDD = IDD_MODULE_REVERB };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(reverb_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(reverb_dialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REVERB_DIALOG_H__EB4FD105_E1BC_423D_BDE4_7C18AB126546__INCLUDED_)
