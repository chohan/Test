// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2BEC2208_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
#define AFX_MAINFRM_H__2BEC2208_96DD_11D2_B015_40DA42C100D5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TermEdit.h"
#include "MSComm.h"
#include "CommDataDlg.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
#ifdef _COMM
	CToolBar    m_wndCommBar;
	CTermEdit   m_edit;
	CMSComm		m_commctrl;
	CCommDataDlg	m_dlgCommData;
	CFile       m_file;
	CString     m_strLogFile;
	CString     m_strPhoneNum;

public:
	void		Dialer();
	CTermEdit*	GetEditCtrl(){return &m_dlgCommData.m_edit;}
	CMSComm*	GetCommCtrl(){return &m_commctrl;}
	void		ShowData(VARIANT pchData);
	void		DoEvents();
	void		DataExtractor(CString str);
	BOOL		Stringer(char *szIn, char *szOut);
	void		Feeder(CString sEntry);

	BOOL		m_bCancel;
#endif	//_COMM

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnUpdateFile(CCmdUI* pCmdUI);
	afx_msg void OnFileOpenlog();
	afx_msg void OnFileCloselog();
	afx_msg void OnFileTransmit();
	afx_msg void OnUpdateCommPort(CCmdUI* pCmdUI);
	afx_msg void OnCommPort(UINT nID);
	afx_msg void OnUpdatePropDTREnable(CCmdUI* pCmdUI);
	afx_msg void OnProperties(UINT nID);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	afx_msg void OnCommEvent();
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2BEC2208_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
