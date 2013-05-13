// ConstantDlg.cpp : implementation file
//

#include "stdafx.h"
#include "08150070.h"
#include "ConstantDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConstantDlg dialog


CConstantDlg::CConstantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConstantDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstantDlg)
	m_Constant = 0.0;
	//}}AFX_DATA_INIT
}


void CConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstantDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Constant);
	DDV_MinMaxDouble(pDX, m_Constant, 0., 255.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstantDlg, CDialog)
	//{{AFX_MSG_MAP(CConstantDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstantDlg message handlers
