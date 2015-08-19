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
// Construction
public:
	Noise_module_dialog(CWnd* pParent = NULL);   // standard constructor

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Noice_module_dialog dialog

class Noice_module_dialog : public CDialog
{
// Construction
public:
	Noice_module_dialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Noice_module_dialog)
	enum { IDD = IDD_MODULE_NOISE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Noice_module_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Noice_module_dialog)
	afx_msg void OnBnoise();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOISE_MODULE_DIALOG_H__4B648181_279E_44DE_BAD0_22DC885C7802__INCLUDED_)
