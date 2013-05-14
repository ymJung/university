// QuantizationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "08150070.h"
#include "QuantizationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuantizationDlg dialog


CQuantizationDlg::CQuantizationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuantizationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuantizationDlg)
	m_QuantiBit = 0;
	//}}AFX_DATA_INIT
}


void CQuantizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuantizationDlg)
	DDX_Text(pDX, IDC_EDIT1, m_QuantiBit);
	DDV_MinMaxInt(pDX, m_QuantiBit, 1, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuantizationDlg, CDialog)
	//{{AFX_MSG_MAP(CQuantizationDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuantizationDlg message handlers
