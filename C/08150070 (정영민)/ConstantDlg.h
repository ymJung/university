#if !defined(AFX_CONSTANTDLG_H__0B3EF15C_068D_4975_A10C_837DB71E7D90__INCLUDED_)
#define AFX_CONSTANTDLG_H__0B3EF15C_068D_4975_A10C_837DB71E7D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConstantDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConstantDlg dialog

class CConstantDlg : public CDialog
{
// Construction
public:
	CConstantDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConstantDlg)
	enum { IDD = IDD_DIALOG4 };
	double	m_Constant;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstantDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConstantDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTANTDLG_H__0B3EF15C_068D_4975_A10C_837DB71E7D90__INCLUDED_)
