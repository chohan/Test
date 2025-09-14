// SComm.h : main header file for the SCOMM application
//

#if !defined(AFX_SCOMM_H__2BEC2204_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
#define AFX_SCOMM_H__2BEC2204_96DD_11D2_B015_40DA42C100D5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSCommApp:
// See SComm.cpp for the implementation of this class
//

class CSCommApp : public CWinApp
{
public:
	CSCommApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCommApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSCommApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOMM_H__2BEC2204_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
