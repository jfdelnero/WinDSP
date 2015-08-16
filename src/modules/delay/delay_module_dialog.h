#if !defined(AFX_DELAY_MODULE_DIALOG3_H__9CCA19A8_8021_46E4_BFEE_711D72A435DF__INCLUDED_)
#define AFX_DELAY_MODULE_DIALOG3_H__9CCA19A8_8021_46E4_BFEE_711D72A435DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Delay_module_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Delay_module_dialog dialog

class Delay_module_dialog : public CDialog
{
// Construction
	Delay_module * thimod;
public:
	Delay_module_dialog(Delay_module *thimod =NULL,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Delay_module_dialog)
	enum { IDD = IDD_MODULE_DELAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Delay_module_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Delay_module_dialog)
	afx_msg void OnOutofmemorySlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnReleasedcaptureSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider14(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELAY_MODULE_DIALOG3_H__9CCA19A8_8021_46E4_BFEE_711D72A435DF__INCLUDED_)
