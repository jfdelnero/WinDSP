#if !defined(AFX_DETECTOR_DIALOG_H__05244678_FCD0_492E_AC92_77B57D42F90F__INCLUDED_)
#define AFX_DETECTOR_DIALOG_H__05244678_FCD0_492E_AC92_77B57D42F90F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// detector_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// detector_dialog dialog

class detector_dialog : public CDialog
{
// Construction
	Detector_module * thimod;
public:
	detector_dialog(Detector_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(detector_dialog)
	enum { IDD = IDD_MODULE_DETECTOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(detector_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(detector_dialog)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider12(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider13(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETECTOR_DIALOG_H__05244678_FCD0_492E_AC92_77B57D42F90F__INCLUDED_)
