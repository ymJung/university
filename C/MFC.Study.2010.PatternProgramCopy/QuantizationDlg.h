#if !defined(AFX_QUANTIZATIONDLG_H__E982EF56_E70F_484C_A8F1_7A2652159B10__INCLUDED_)
#define AFX_QUANTIZATIONDLG_H__E982EF56_E70F_484C_A8F1_7A2652159B10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuantizationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuantizationDlg dialog

class CQuantizationDlg : public CDialog
{
// Construction
public:
	CQuantizationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQuantizationDlg)
	enum { IDD = IDD_DIALOG3 };
	int		m_QuantiBit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuantizationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQuantizationDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUANTIZATIONDLG_H__E982EF56_E70F_484C_A8F1_7A2652159B10__INCLUDED_)
