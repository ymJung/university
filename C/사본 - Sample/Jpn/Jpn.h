// Jpn.h : main header file for the JPN DLL
//

#if !defined(AFX_JPN_H__45F84CA4_5CD5_43B6_84FF_1F61EDFE82E4__INCLUDED_)
#define AFX_JPN_H__45F84CA4_5CD5_43B6_84FF_1F61EDFE82E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJpnApp
// See Jpn.cpp for the implementation of this class
//

class CJpnApp : public CWinApp
{
public:
	CJpnApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJpnApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CJpnApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JPN_H__45F84CA4_5CD5_43B6_84FF_1F61EDFE82E4__INCLUDED_)
