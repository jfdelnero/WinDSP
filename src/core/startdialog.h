#if !defined(AFX_STARTDIALOG_H__C6CF1B3E_06D0_4DFA_B85A_19AD75DF1DDE__INCLUDED_)
#define AFX_STARTDIALOG_H__C6CF1B3E_06D0_4DFA_B85A_19AD75DF1DDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// startdialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// startdialog dialog

class startdialog : public CDialog
{
// Construction
public:
	startdialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(startdialog)
	enum { IDD = IDD_DIALOGSTART };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(startdialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(startdialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTDIALOG_H__C6CF1B3E_06D0_4DFA_B85A_19AD75DF1DDE__INCLUDED_)
