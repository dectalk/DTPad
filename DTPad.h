// DTPad.h : main header file for the DTPAD application
//

#if !defined(AFX_DTPAD_H__44B51CA5_A9CA_49AB_9B9F_52C342B70600__INCLUDED_)
#define AFX_DTPAD_H__44B51CA5_A9CA_49AB_9B9F_52C342B70600__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDTPadApp:
// See DTPad.cpp for the implementation of this class
//

class CDTPadApp : public CWinApp
{
public:
	CDTPadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTPadApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDTPadApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTPAD_H__44B51CA5_A9CA_49AB_9B9F_52C342B70600__INCLUDED_)
