// CalendarDlg.h : header file
//

#if !defined(AFX_CALENDARDLG_H__1C79A205_0315_4FCE_A713_19385874B736__INCLUDED_)
#define AFX_CALENDARDLG_H__1C79A205_0315_4FCE_A713_19385874B736__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog

class CCalendarDlg : public CDialog
{
// Construction
public:
	void DatePrint();
	void BackGround();
	int m_nMonth;
	int m_nYear;
	CCalendarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarDlg)
	enum { IDD = IDD_CALENDAR_DIALOG };
	CComboBox	m_ctlMonth;
//	CString	m_nYear;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalendarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeComboMonth();
	afx_msg void OnButtonAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDLG_H__1C79A205_0315_4FCE_A713_19385874B736__INCLUDED_)
