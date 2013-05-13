// CalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calendar.h"
#include "CalendarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog

CCalendarDlg::CCalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDlg)
//	m_nYear = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDlg)
	DDX_Control(pDX, IDC_COMBO_MONTH, m_ctlMonth);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_nYear);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalendarDlg, CDialog)
	//{{AFX_MSG_MAP(CCalendarDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_MONTH, OnSelchangeComboMonth)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg message handlers

BOOL CCalendarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	COleDateTime mm;
	mm = COleDateTime::GetCurrentTime();
	m_nYear=mm.GetYear(); //년출력

	m_nMonth=mm.GetMonth();
	m_ctlMonth.SetCurSel(m_nMonth-1); //월출력 콤보박스의 인덱스는 0부터 시작하기 때문

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalendarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalendarDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	BackGround();
	DatePrint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalendarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CCalendarDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	switch(nSBCode) //년도 수정시마다 WM_PAINT메시지 호출 . 수정.
	{
	case SB_LINELEFT:
		if(m_nYear<2100)
		{
			m_nYear++;	
		}
		break;
	case SB_LINERIGHT:
		if(m_nYear>1900)
		{
			m_nYear--;
		}
		break;
	}
	Invalidate(FALSE);
	UpdateData(FALSE);
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CCalendarDlg::OnSelchangeComboMonth() 
{
	// TODO: Add your control notification handler code here
	m_nMonth=m_ctlMonth.GetCurSel()+1;
	Invalidate(FALSE);

}

void CCalendarDlg::BackGround()
{
	CClientDC dc(this);

	dc.Rectangle(40,135,300,400);
	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(65,145,"일    월    화    수    목    금    토");
	//dc.Rectangle(40,135,300,170);




}

void CCalendarDlg::DatePrint()
{
	CClientDC dc(this);
	COleDateTime mm;
	mm = COleDateTime::GetCurrentTime();
	int w=0,b=0,c=0,t=0;
	char szText[3]="";
	
	t=mm.GetDay();
	
	mm.SetDate(m_nYear,m_nMonth,1);
	w=mm.GetDayOfWeek();

	for(int a=1; a<=6; a++)
	{
		for(b=w; b<=7; b++)
		{
			w=1;
			c=c+1;
			mm.SetDate(m_nYear,m_nMonth,c);
			if(mm.GetDay()!=-1)
			{
				if(c==t)
					dc.SetTextColor(RGB(0,0,255)); //오늘날짜.
				else if(mm.GetDayOfWeek()==1)
					dc.SetTextColor(RGB(255,0,0)); //일요일
				else
					dc.SetTextColor(RGB(0,0,0)); //평일.

				sprintf(szText,"%d",c);
			    dc.TextOut(38+b*32,130+a*40,szText); 
			}
		}
	}
}

void CCalendarDlg::OnButtonAbout() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}
