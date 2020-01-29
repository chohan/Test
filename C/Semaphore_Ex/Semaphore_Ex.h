// Semaphore_Ex.h : main header file for the SEMAPHORE_EX application
//

#if !defined(AFX_SEMAPHORE_EX_H__087C0595_84C8_4DCE_897C_DB5325CD5615__INCLUDED_)
#define AFX_SEMAPHORE_EX_H__087C0595_84C8_4DCE_897C_DB5325CD5615__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSemaphore_ExApp:
// See Semaphore_Ex.cpp for the implementation of this class
//

class CSemaphore_ExApp : public CWinApp
{
public:
	CSemaphore_ExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSemaphore_ExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSemaphore_ExApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEMAPHORE_EX_H__087C0595_84C8_4DCE_897C_DB5325CD5615__INCLUDED_)
