#if !defined(AFX_SIGNALTRANSFORM_DIALOG_H__9AC8DD40_240C_4554_8707_E0CC27FD6A99__INCLUDED_)
#define AFX_SIGNALTRANSFORM_DIALOG_H__9AC8DD40_240C_4554_8707_E0CC27FD6A99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SignalTransform_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SignalTransform_dialog dialog

class SignalTransform_dialog : public CDialog
{
// Construction
SignalTransform_module * thimod;
public:
	SignalTransform_dialog(SignalTransform_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SignalTransform_dialog)
	enum { IDD = IDD_MODULE_SIGNALTRANSFORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SignalTransform_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SignalTransform_dialog)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGNALTRANSFORM_DIALOG_H__9AC8DD40_240C_4554_8707_E0CC27FD6A99__INCLUDED_)
