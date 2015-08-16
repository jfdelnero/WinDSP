#if !defined(AFX_OUTPUT_DIALOG_H__4AD54DE1_6103_41D8_B122_0F93668D47C5__INCLUDED_)
#define AFX_OUTPUT_DIALOG_H__4AD54DE1_6103_41D8_B122_0F93668D47C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Output_dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Output_dialog dialog

class Output_dialog : public CDialog
{
	output_module * thimod;
// Construction
public:
	Output_dialog(output_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Output_dialog)
	enum { IDD = IDD_MODULE_OUTPUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Output_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Output_dialog)
	afx_msg void OnSelchangeList2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUT_DIALOG_H__4AD54DE1_6103_41D8_B122_0F93668D47C5__INCLUDED_)
