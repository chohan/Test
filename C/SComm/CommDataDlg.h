#if !defined(AFX_COMMDATADLG_H__558E4861_7152_11D1_86D5_444553540000__INCLUDED_)
#define AFX_COMMDATADLG_H__558E4861_7152_11D1_86D5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CommDataDlg.h : header file
//
#include "termedit.h"

/////////////////////////////////////////////////////////////////////////////
// CCommDataDlg dialog

class CCommDataDlg : public CDialog
{
// Construction
public:
	CCommDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommDataDlg)
	enum { IDD = IDD_COMM_DATA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

public:
	CTermEdit   m_edit;

	// Generated message map functions
	//{{AFX_MSG(CCommDataDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMDATADLG_H__558E4861_7152_11D1_86D5_444553540000__INCLUDED_)
