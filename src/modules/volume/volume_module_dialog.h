#if !defined(AFX_VOLUME_MODULE_DIALOG_H__F492A833_C8CB_4AFB_98F8_E511A3E3BD41__INCLUDED_)
#define AFX_VOLUME_MODULE_DIALOG_H__F492A833_C8CB_4AFB_98F8_E511A3E3BD41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Volume_module_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Volume_module_dialog dialog

class Volume_module_dialog : public CDialog
{
// Construction
	Volume_module * thimod;
public:
	Volume_module_dialog(Volume_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Volume_module_dialog)
	enum { IDD = IDD_MODULE_VOLUME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Volume_module_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Volume_module_dialog)
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck2();
	afx_msg void OnCheck5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUME_MODULE_DIALOG_H__F492A833_C8CB_4AFB_98F8_E511A3E3BD41__INCLUDED_)
