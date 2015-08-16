#if !defined(AFX_LFO_MODULE_DIALOG_H__4CEB2DBE_0557_47ED_BC34_671483A133B0__INCLUDED_)
#define AFX_LFO_MODULE_DIALOG_H__4CEB2DBE_0557_47ED_BC34_671483A133B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LFO_module_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LFO_module_dialog dialog

class LFO_module_dialog : public CDialog
{
// Construction
	lfo_module * thimod;
public:
	LFO_module_dialog(lfo_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LFO_module_dialog)
	enum { IDD = IDD_MODULE_LFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LFO_module_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LFO_module_dialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LFO_MODULE_DIALOG_H__4CEB2DBE_0557_47ED_BC34_671483A133B0__INCLUDED_)
