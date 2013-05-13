#if !defined(AFX_DOWNSAMPLEDLG_H__A6C4CE16_ED9C_4D14_BA1F_7F2004BAF94D__INCLUDED_)
#define AFX_DOWNSAMPLEDLG_H__A6C4CE16_ED9C_4D14_BA1F_7F2004BAF94D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DownSampleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDownSampleDlg dialog

class CDownSampleDlg : public CDialog
{
// Construction
public:
	CDownSampleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDownSampleDlg)
	enum { IDD = IDD_DIALOG1 };
	int		m_DownSampleRate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDownSampleDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNSAMPLEDLG_H__A6C4CE16_ED9C_4D14_BA1F_7F2004BAF94D__INCLUDED_)
