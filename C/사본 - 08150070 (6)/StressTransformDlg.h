#if !defined(AFX_STRESSTRANSFORMDLG_H__039640BD_EA58_4D2A_958C_6BF8D23B0A86__INCLUDED_)
#define AFX_STRESSTRANSFORMDLG_H__039640BD_EA58_4D2A_958C_6BF8D23B0A86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StressTransformDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStressTransformDlg dialog

class CStressTransformDlg : public CDialog
{
// Construction
public:
	CStressTransformDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStressTransformDlg)
	enum { IDD = IDD_DIALOG5 };
	int		m_StartPoint;
	int		m_EndPoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStressTransformDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStressTransformDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRESSTRANSFORMDLG_H__039640BD_EA58_4D2A_958C_6BF8D23B0A86__INCLUDED_)
