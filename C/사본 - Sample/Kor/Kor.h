// Kor.h : main header file for the KOR DLL
//

#if !defined(AFX_KOR_H__B4BEDA78_0060_4F1D_9C41_4F2E46DE0BD0__INCLUDED_)
#define AFX_KOR_H__B4BEDA78_0060_4F1D_9C41_4F2E46DE0BD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKorApp
// See Kor.cpp for the implementation of this class
//

class CKorApp : public CWinApp
{
public:
	CKorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKorApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KOR_H__B4BEDA78_0060_4F1D_9C41_4F2E46DE0BD0__INCLUDED_)
