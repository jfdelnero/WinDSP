#if !defined(AFX_FILTER_DIALOG_H__D15D8722_D859_45A3_B2C3_787D9DAC5477__INCLUDED_)
#define AFX_FILTER_DIALOG_H__D15D8722_D859_45A3_B2C3_787D9DAC5477__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Filter_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Filter_dialog dialog

class Filter_dialog : public CDialog
{
// Construction
	Filter_module * thimod;
public:
	Filter_dialog(Filter_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Filter_dialog)
	enum { IDD = IDD_MODULE_FILTER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Filter_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Filter_dialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider7(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider8(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider9(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider10(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider11(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTER_DIALOG_H__D15D8722_D859_45A3_B2C3_787D9DAC5477__INCLUDED_)
