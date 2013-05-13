#include "stdafx.h"
#include "Sample.h"
#include "SampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleApp

BEGIN_MESSAGE_MAP(CSampleApp, CWinApp)
    //{{AFX_MSG_MAP(CSampleApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleApp construction

CSampleApp::CSampleApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSampleApp object

CSampleApp theApp;
HINSTANCE g_hPrevResource;
HINSTANCE g_hCurrResource;
/////////////////////////////////////////////////////////////////////////////
// CSampleApp initialization

BOOL CSampleApp::InitInstance()
{
    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();         // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif

    g_hPrevResource = AfxGetResourceHandle();     /* ���� ���ҽ� �ڵ��� �����մϴ�. */
    g_hCurrResource = LoadLibrary("C:\\Kor.dll"); /* �� �κ��� ���� �Ŀ� �����մϴ�. */
    
    if ( g_hCurrResource )
        AfxSetResourceHandle(g_hCurrResource);

    CSampleDlg dlg;
    m_pMainWnd = &dlg;
    int nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
    }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
