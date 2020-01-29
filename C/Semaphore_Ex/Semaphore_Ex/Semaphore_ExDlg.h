// Semaphore_ExDlg.h : header file
//

#if !defined(AFX_SEMAPHORE_EXDLG_H__D964BC78_F617_4508_B6C1_A06F86E6C098__INCLUDED_)
#define AFX_SEMAPHORE_EXDLG_H__D964BC78_F617_4508_B6C1_A06F86E6C098__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPercentBar.h"

/////////////////////////////////////////////////////////////////////////////
// CSemaphore_ExDlg dialog

class CSemaphore_ExDlg : public CDialog
{
// Construction
public:
	CSemaphore_ExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSemaphore_ExDlg)
	enum { IDD = IDD_SEMAPHORE_EX_DIALOG };
	CStatic	m_statNew;
	CPercentBar	m_ctrlProd;
	CPercentBar	m_ctrlCons;
	CButton	m_butCons;
	CButton	m_butProd;
	//}}AFX_DATA
	

	void Initialize();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSemaphore_ExDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSemaphore_ExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConsumption();
	afx_msg void OnProduction();
	virtual void OnCancel();
	virtual void OnOK();		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEMAPHORE_EXDLG_H__D964BC78_F617_4508_B6C1_A06F86E6C098__INCLUDED_)
