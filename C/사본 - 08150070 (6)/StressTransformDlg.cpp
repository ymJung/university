// StressTransformDlg.cpp : implementation file
//

#include "stdafx.h"
#include "08150070.h"
#include "StressTransformDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStressTransformDlg dialog


CStressTransformDlg::CStressTransformDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStressTransformDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStressTransformDlg)
	m_StartPoint = 0;
	m_EndPoint = 0;
	//}}AFX_DATA_INIT
}


void CStressTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStressTransformDlg)
	DDX_Text(pDX, IDC_EDIT1, m_StartPoint);
	DDV_MinMaxInt(pDX, m_StartPoint, 0, 255);
	DDX_Text(pDX, IDC_EDIT2, m_EndPoint);
	DDV_MinMaxInt(pDX, m_EndPoint, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStressTransformDlg, CDialog)
	//{{AFX_MSG_MAP(CStressTransformDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStressTransformDlg message handlers
