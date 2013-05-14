// DownSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "08150070.h"
#include "DownSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDownSampleDlg dialog


CDownSampleDlg::CDownSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDownSampleDlg)
	m_DownSampleRate = 0;
	//}}AFX_DATA_INIT
}


void CDownSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDownSampleDlg)
	DDX_Text(pDX, IDC_EDIT1, m_DownSampleRate);
	DDV_MinMaxInt(pDX, m_DownSampleRate, 1, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDownSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CDownSampleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDownSampleDlg message handlers
