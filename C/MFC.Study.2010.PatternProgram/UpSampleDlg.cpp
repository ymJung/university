// UpSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "08150070.h"
#include "UpSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpSampleDlg dialog


CUpSampleDlg::CUpSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpSampleDlg)
	m_UpSampleRate = 0;
	//}}AFX_DATA_INIT
}


void CUpSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpSampleDlg)
	DDX_Text(pDX, IDC_EDIT1, m_UpSampleRate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CUpSampleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpSampleDlg message handlers
