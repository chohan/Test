//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGCOMM_H__2BEC2215_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
#define AFX_DLGCOMM_H__2BEC2215_96DD_11D2_B015_40DA42C100D5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgComm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgComm dialog

class CDlgComm : public CDialog
{
// Construction
public:
	CDlgComm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgComm)
	enum { IDD = IDD_COMM };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgComm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgComm)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMM_H__2BEC2215_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
