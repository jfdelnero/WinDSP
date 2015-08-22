#if !defined(AFX_NOISE_MODULE_DIALOG_H__4B648181_279E_44DE_BAD0_22DC885C7802__INCLUDED_)
#define AFX_NOISE_MODULE_DIALOG_H__4B648181_279E_44DE_BAD0_22DC885C7802__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Noise_module_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Noise_module_dialog dialog

class Noise_module_dialog : public CDialog
{
	noise_module * thimod;
// Construction
public:
	Noise_module_dialog(noise_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Noise_module_dialog)
	enum { IDD = IDD_MODULE_NOISE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Noise_module_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Noise_module_dialog)
	afx_msg void OnBnoise();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_NOISE_MODULE_DIALOG_H__4B648181_279E_44DE_BAD0_22DC885C7802__INCLUDED_)
