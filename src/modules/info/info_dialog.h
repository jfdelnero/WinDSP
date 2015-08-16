#if !defined(AFX_INFO_DIALOG_H__DE9082E6_1AA9_47AF_875B_B43413370E14__INCLUDED_)
#define AFX_INFO_DIALOG_H__DE9082E6_1AA9_47AF_875B_B43413370E14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Info_Dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Info_Dialog dialog

class Info_Dialog : public CDialog
{
// Construction
	info_module * thimod;
	char lachaine[512+1];
public:
	Info_Dialog(info_module * thimod,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Info_Dialog)
	enum { IDD = IDD_MODULE_MINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Info_Dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Info_Dialog)
	afx_msg void OnChangeEdit1();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFO_DIALOG_H__DE9082E6_1AA9_47AF_875B_B43413370E14__INCLUDED_)
